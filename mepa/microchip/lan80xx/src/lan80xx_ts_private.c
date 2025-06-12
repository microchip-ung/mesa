// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
// Author : Sushovan Dec 2022
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_regs_util.h"
//#include "../../microchip/lan8042/src/regs/regs_la8042.h"
#include "regs_lan8042.h"
#include "lan80xx_ts.h"
#include "regs_lan80xx_ts_dump.h"


static lan80xx_phy_ts_pll_map_t phy25g_ts_pll_map[] = {
    [LAN80XX_PHY_TS_CLOCK_SRC_INTERNAL] = {
        .pll_r = 25,
        .pll_div_fi = 50,
        .pll_divff_hi = 237,
        .pll_divff_lo = 63762,
        .pll_divq = 8,
        .clk_sel = 9
    },
    [LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_25MHZ] = {
        .pll_r = 4,
        .pll_div_fi = 62,
        .pll_divff_hi = 0xa9,
        .pll_divff_lo = 0x7757,
        .pll_divq = 8,
        .clk_sel = 9
    },
    [LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_50MHZ] = {
        .pll_r = 9,
        .pll_div_fi = 62,
        .pll_divff_hi = 0xa9,
        .pll_divff_lo = 0x7757,
        .pll_divq = 8,
        .clk_sel = 9
    },
    [LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_125MHZ] = {
        .pll_r = 24,
        .pll_div_fi = 62,
        .pll_divff_hi = 0xA9,
        .pll_divff_lo = 0x7757,
        .pll_divq = 8,
        .clk_sel = 9
    },
};

static lan80xx_phy_ts_biu_addr_map_t phy25g_ts_biu_addr_map [] = {
    {
        .dev_id = LAN80XX_DEV_ID_8042, // base SKU ID of LAN8042 Phy
        .mmd_addr = 0x0A,
        .mdio_address = {
            [LAN80XX_PHY_TS_ANA_BLK_ID_ING_0] = 0xA000,
            [LAN80XX_PHY_TS_ANA_BLK_ID_EGR_0] = 0xA800,
            [LAN80XX_PHY_TS_ANA_BLK_ID_ING_1] = 0xB000,
            [LAN80XX_PHY_TS_ANA_BLK_ID_EGR_1] = 0xB800,
            [LAN80XX_PHY_TS_ANA_BLK_ID_ING_2] = 0xC000,
            [LAN80XX_PHY_TS_ANA_BLK_ID_EGR_2] = 0xC800,
            [LAN80XX_PHY_TS_PROC_BLK_ID_0]    = 0x9000,
        },
    },
};


static phy25g_phy_ts_local_latency phy25g_ts_local_latency [] = {
    {SPEED_25G, FALSE, PCS_RETIMER, FALSE, 0x0,  0x0,   0x0,  0x62,  0x6104,  0x9d},
    {SPEED_25G, FALSE, PCS_RETIMER, TRUE, 0x1B, 0x0,  0x30,  0x5A,  0x6104,  0x9d},
    {SPEED_25G, FALSE, MAC_RETIMER, FALSE, 0x0,  0x0,   0x0,  0x62,  0x6104,  0x9d},
    {SPEED_25G, FALSE, MAC_RETIMER, TRUE,  0x1A, 0x0,   0x78, 0x5A,  0x6104,  0x9d},

    {SPEED_10G, FALSE, PCS_RETIMER, FALSE, 0x0,  0x0,  0x0,   0x62,  0x1104,  0x9d},
    {SPEED_10G, FALSE, PCS_RETIMER, TRUE,  0x1B, 0x0,  0x30,  0x5A,  0x1104,  0x9d},
    {SPEED_10G, FALSE, MAC_RETIMER, FALSE, 0x0,  0x0,  0x0,   0x62,  0x1104,  0x9d},
    {SPEED_10G, FALSE, MAC_RETIMER, TRUE,  0x1A, 0x0,  0x78,  0x5A,  0x1104,  0x9d},

    {SPEED_1G,  FALSE, PCS_RETIMER, FALSE, 0xB4,  0x1,  0x0,    0x74,  0x104,   0xdb},
    {SPEED_1G,  FALSE, PCS_RETIMER, TRUE, 0x6B1,   0x1A,  0xC00,  0x0,   0x104,   0xdb},
    {SPEED_1G,  FALSE, MAC_RETIMER, FALSE, 0x1D74, 0x0,  0x0,   0x74,  0x104,   0xdb},
    {SPEED_1G,  FALSE, MAC_RETIMER, TRUE,  0x2170, 0x1A, 0x1E00, 0x0,  0x104,   0xdb},

    {SPEED_25G, TRUE, PCS_RETIMER, FALSE, 0x0,  0x0,   0x0,    0x0,  0x6104,  0xbf},
    {SPEED_25G, TRUE,  PCS_RETIMER, TRUE,  0x1B, 0xC,  0x78,    0x5A, 0x6104,  0xbf},
    {SPEED_25G, TRUE,  MAC_RETIMER, FALSE, 0x0,  0x0,  0x0,     0x61,  0x6104,  0xbf},
    {SPEED_25G, TRUE,  MAC_RETIMER, TRUE,  0x1A, 0xC,  0x78,    0x5A, 0x6104,  0xbf},

};


typedef enum {
    LAN80XX_PHY_TS_NEXT_COMP_NONE    = 0,
    LAN80XX_PHY_TS_NEXT_COMP_ETH2    = 1,
    LAN80XX_PHY_TS_NEXT_COMP_IP1     = 2,
    LAN80XX_PHY_TS_NEXT_COMP_IP2     = 3,
    LAN80XX_PHY_TS_NEXT_COMP_MPLS    = 4,
    LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM = 5,
    LAN80XX_PHY_TS_NEXT_COMP_RES     = 7 /* Reserved comparator */
} phy25g_ts_next_comp_t;

typedef enum {
    PTP_ACTION_CMD_NOP = 0,
    PTP_ACTION_CMD_SUB = 1,
    PTP_ACTION_CMD_ADD = 3,
    PTP_ACTION_CMD_SUB_ADD = 4,
    PTP_ACTION_CMD_WRITE_1588 = 5,
    PTP_ACTION_CMD_WRITE_NS = 7,
    PTP_ACTION_CMD_WRITE_NS_P2P = 8,
    PTP_ACTION_CMD_ADD_2 = 9,
    PTP_ACTION_CMD_SUB_2 = 10,
    PTP_ACTION_CMD_SAVE_IN_TS_FIFO, /* not the 1588 command */
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
    PTP_ACTION_CMD_DCE, /* not the 1588 command */
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
} phy25g_ts_ptp_action_cmd_t;

typedef enum {
    PTP_ACTION_ASYM_NONE,
    PTP_ACTION_ASYM_ADD,
    PTP_ACTION_ASYM_SUB,
} phy25g_ts_ptp_action_asym_t;

#if 0 // to be used next PR as of now commented to fix jenkins error

phy25g_phy_ts_tc_op_mode_t mepa_to_mesa_tc_opmode(mepa_ts_tc_op_mode_t tc_opmode)
{
    phy25g_phy_ts_tc_op_mode_t ret;
    switch (tc_opmode) {
    case MEPA_TS_TC_OP_MODE_A:
        ret = LAN80XX_PHY_TS_TC_OP_MODE_A;
        break;
    case MEPA_TS_TC_OP_MODE_B:
        ret = LAN80XX_PHY_TS_TC_OP_MODE_B;
        break;
    case MEPA_TS_TC_OP_MODE_C:
        ret = LAN80XX_PHY_TS_TC_OP_MODE_C;
        break;
    default:
        ret = LAN80XX_PHY_TS_TC_OP_MODE_A;
        break;
    }
    return ret;
}


static mepa_rc lan8042_ts_macsec_bypass(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    // Some doubts about MACsec registers (TODO MACSEC developer will look closely on values.
    // As of now keep it as ot is.Ref Values taken from
    // https://bitbucket.microchip.com/projects/UVS/repos/mb25_sw/browse/scripts/PTP_1588/configurations/general/ptp_ltc_bringup_25g_fpga_xgmii.csv?at=refs%2Fheads%2F1588 )
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_MAC_FC_BUFF, 0, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    // Bit 4 and Bit 20 Set
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_MAC_FC_BUFF, 0, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_DROP_BEHAVIOUR |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_MODE_CFG_TX_CTRL_QUEUE_ENA);

    // Doubts why 0x6006 is written ?
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_MAC_FC_BUFF, 0, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_READ_THRESH_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_MAC_FC_BUFF, 0, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_PPM_RATE_ADAPT_THRESH_CFG),
                   0x3200028);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_MAC_FC_BUFF, 0, LAN80XX_MAC_FC_BUFFER_MAC_FC_BUFFER_STICKY),
                   0x320002);

    // Doubt How this 32 bit address accomodated ?
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADDRESS_LSB),
                   0x4864995b);

    // Upper 16 bit of mac address (should come from config)
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADDRESS_MSB),
                   0x678d);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG),
                   0x1110111);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_ENA_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_LFS_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_MAXLEN_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_MODE_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_NUM_TAGS_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_PKTINF_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(0)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(1)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(1)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(2)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_TAGS_CFG(2)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_PAUSE_TX_FRAME_CONTROL_2),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_LSB),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADDRESS_MSB),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_ENA_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_LFS_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_NUM_TAGS_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_PKTINF_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(0)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(1)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_TAGS_CFG(2)),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_PAUSE_TX_FRAME_CONTROL_2),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_ENABLE_CONFIG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_ADV_CHK_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_ADV_CHK_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_HOST_MAC, 0, LAN80XX_HOST_MAC_HOST_MAC_MAC_MODE_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_LINE_MAC, 0, LAN80XX_LINE_MAC_LINE_MAC_MAC_MODE_CFG),
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_TX_ENA |
                   LAN80XX_M_MAC_FC_BUFFER_MAC_FC_BUFFER_FC_ENA_CFG_RX_ENA);

    return MEPA_RC_OK;

}


//Register configuration to bypass ptp block
static mepa_rc lan8042_ts_ptp_bypass(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    // INGR DF Depth must be less than 20
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INGR_DF_CTRL),
                   0xe);

    //Final mode for 1588 will be this 3-bit register ORed with 2-bit MII_MODE of INTERFACE_CTL
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_MODE_CTL),
                   0x4);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INTERFACE_CTL),
                   (LAN80XX_M_PTP_PROC_INTERFACE_CTL_SPLIT_BYPASS |
                    LAN80XX_M_PTP_PROC_INTERFACE_CTL_CLK_ENA |
                    LAN80XX_M_PTP_PROC_INTERFACE_CTL_INGR_BYPASS |
                    LAN80XX_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS));

    // No Ingress Preemption + MAC retimer Mode (Packet interface with Macsec)
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE),
                   0x0);

    return MEPA_RC_OK;
}

//Register configuration for ptp ip control
static mepa_rc lan8042_ts_ptp_ip_control(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    //enable ingress & egress bypass and enable clock
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INTERFACE_CTL),
                   LAN80XX_M_PTP_PROC_INTERFACE_CTL_CLK_ENA |
                   LAN80XX_M_PTP_PROC_INTERFACE_CTL_INGR_BYPASS |
                   LAN80XX_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS);

    // in between Some clarification asked. Will update after that

    //PCS timing mode
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_MODE_CTL),
                   0x00);

    //enable clock, bypass disabled, MII_PROTOCOL = 0
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INTERFACE_CTL),
                   LAN80XX_M_PTP_PROC_INTERFACE_CTL_CLK_ENA |
                   (~LAN80XX_M_PTP_PROC_INTERFACE_CTL_INGR_BYPASS) |
                   (~LAN80XX_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS));

    //Egress (PTP 0) engine Enabled
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_ANALYZER_MODE),
                   0x10);

    //EGR_DF_DEPTH = 19
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_DF_CTRL),
                   0x13);


    return MEPA_RC_OK;
}

//Register configuration for egress frame
// TODO: <will update code based on port number >
static mepa_rc lan8042_ts_egress_frame_config(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    //EGR0_ETH1_NXT_COMPARATOR = PTP comparator , EGR0_ETH1_FRAME_SIG_OFFSET = 0
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_NXT_PROTOCOL_REG),
                   0x5);

    // Configure ethertype verification
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_ETYPE_MATCH),
                   LAN80XX_M_PTP_ANA0_EGR_CFG_EGR0_ETH1_ETYPE_MATCH_EGR0_ETH1_ETYPE_MATCH_ENA);

    //EGR0_ETH1_ETYPE_MATCH = 88f7 (PTP Protocol) , EGR0_ETH1_ETYPE_MATCH_ENA = 1
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_ETYPE_MATCH),
                   0x188F7);

    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_MATCH_MODE(0)),
                   LAN80XX_M_PTP_ANA0_EGR_CFG_EGR0_ETH1_MATCH_MODE_EGR0_ETH1_VLAN_TAG2_TYPE |
                   LAN80XX_M_PTP_ANA0_EGR_CFG_EGR0_ETH1_MATCH_MODE_EGR0_ETH1_ETHERTYPE_MODE);

    //EGR0_ETH1_ADDR_MATCH_1 = CCCCCCCC ; First 32 bits of the address match value
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_ADDR_MATCH_1(0)),
                   0xcccccccc);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_ADDR_MATCH_2(0)),
                   0x10cccc);
    //EGR0_ETH1_ADDR_MATCH_2 = CCCC;Last 16 bits of the Ethernet address match field.
    //EGR0_ETH1_ADDR_MATCH_SELECT = 00; Match the destination address
    //EGR0_ETH1_ADDR_MATCH_MODE = 1; Match any unicast address
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_ADDR_MATCH_2(0)),
                   0x11cccc); // Is this needed ? <TODO> Ask Vidhya when in office

    //PTP_ANA0_EGR_CFG (Device 0xA slice registers):EGR0_ETH1_FLOW_CFG[0-7]:EGR0_ETH1_FLOW_ENABLE
    //EGR0_ETH1_FLOW_ENABLE = 1, EGR0_ETH1_CHANNEL_MASK = 3
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_ETH1_FLOW_ENABLE(0)),
                   0x301);

    //#EGR0_PTP_COMMAND = 5, WRITE_1588; write capture local time to time storage Field in frame
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_ACTION(0)),
                   0x5);
    //Enable: save Local Time to Egress TS FIFO
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_ACTION(0)),
                   0x105);
    //EGR0_PTP_CORR_FIELD_OFFSET = 8  # Correction field starting
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_ACTION(0)),
                   0x415);
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_ACTION(0)),
                   0x41115);


    //PTP_ANA0_EGR_CFG (Device 0xA slice registers):EGR0_PTP_FLOW[0-5]:EGR0_PTP_FLOW_ENA
    //EGR0_PTP_FLOW_ENA = 1; EGR0_PTP_CHANNEL_MASK = 3 (Default)
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_FLOW_ENA(0)),
                   0x30);
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_FLOW_ENA(0)),
                   0x31);

    //EGR0_PTP_REWRITE_BYTES(3: 0) = 10(0xa): Number of bytes in the PTP or OAM frame that must be modified by the rewriter for the timestamp
    //EGR0_PTP_REWRITE_OFFSET(15: 8)  = 34(0x22) Origin Timestamp: Points to where in the frame relative to the SFD that the timestamp should be updated
    //EGR0_PTP_NEW_CF_LOC(23: 16) = 0 Location of the new correction field relative to the PTP header start. Only even values are allowed.


    //EGR0_PTP_ZERO_FIELD_OFFSET = 16, 0x10
    //EGR0_PTP_ZERO_FIELD_BYTE_CNT = 0
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_EGR_CFG_EGR0_PTP_ZERO_FIELD_CTL(0)),
                   0x1000);



    return MEPA_RC_OK;
}


//Register configuration for ingress frame
// TODO: <will update code based on port number >
static mepa_rc lan8042_ts_ingress_frame_config(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    //EGR0_ETH1_NXT_COMPARATOR = PTP comparator , EGR0_ETH1_FRAME_SIG_OFFSET = 0
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_NXT_PROTOCOL_REG),
                   0x5);

    // Configure ethertype verification
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_ETYPE_MATCH),
                   LAN80XX_M_PTP_ANA0_INGR_CFG_INGR0_ETH1_ETYPE_MATCH_INGR0_ETH1_ETYPE_MATCH_ENA);

    //EGR0_ETH1_ETYPE_MATCH = 88f7 (PTP Protocol) , EGR0_ETH1_ETYPE_MATCH_ENA = 1
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_ETYPE_MATCH),
                   0x188F7);

    //EGR0_ETH1_ETHERTYPE_MODE = 1(VLAN tag verification)
    //EGR0_ETH1_VLAN_VERIFY_EN = 0
    //EGR0_ETH1_VLAN_TAGS = 0
    //EGR0_ETH1_VLAN_TAG1_TYPE = 0
    //EGR0_ETH1_VLAN_TAG2_TYPE = 1
    //EGR0_ETH1_VLAN_TAG_MODE = 0
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_MATCH_MODE(0)),
                   LAN80XX_M_PTP_ANA0_EGR_CFG_EGR0_ETH1_MATCH_MODE_EGR0_ETH1_VLAN_TAG2_TYPE |
                   LAN80XX_M_PTP_ANA0_EGR_CFG_EGR0_ETH1_MATCH_MODE_EGR0_ETH1_ETHERTYPE_MODE);

    //EGR0_ETH1_ADDR_MATCH_1 = CCCCCCCC ; First 32 bits of the address match value
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_ADDR_MATCH_1(0)),
                   0xcccccccc);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_ADDR_MATCH_2(0)),
                   0x10cccc);

    //EGR0_ETH1_ADDR_MATCH_2 = CCCC;Last 16 bits of the Ethernet address match field.
    //EGR0_ETH1_ADDR_MATCH_SELECT = 00; Match the destination address
    //EGR0_ETH1_ADDR_MATCH_SELECT = 01; Match the Source address
    //EGR0_ETH1_ADDR_MATCH_MODE = 1; Match any unicast address
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_ADDR_MATCH_2(0)),
                   0x11cccc); // Is this needed ? <TODO> Ask Vidhya when in office

    //PTP_ANA0_EGR_CFG (Device 0xA slice registers):EGR0_ETH1_FLOW_CFG[0-7]:EGR0_ETH1_FLOW_ENABLE
    //EGR0_ETH1_FLOW_ENABLE = 1, EGR0_ETH1_CHANNEL_MASK = 3
    //EGR0_PTP_FLOW_ENA = 1, EGR0_PTP_CHANNEL_MASK = 3 (Default)
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_ETH1_FLOW_ENABLE(0)),
                   0x301);

    //INGR0_PTP_COMMAND(3: 0):  0x8
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ACTION(0)),
                   0x8);
    //Enable: save Local Time to Egress TS FIFO
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ACTION(0)),
                   0x108);
    //EGR0_PTP_CORR_FIELD_OFFSET = 8  # Correction field starting
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ACTION(0)),
                   0x4108);

    //WRITE_NS_P2P: Write local time in nanoseconds to the new field
    //INGR0_PTP_TIME_STRG_FIELD_OFFSET(15: 10): 0x10(16): End of Correction field Points to a location in a PTP frame where a time value can be stored or read.
    //INGR0_PTP_DLY_STRG_FIELD_OFFSET(16) = 0
    //INGR0_PTP_ADD_DELAY_ASYM_ENA(20) = 0
    //INGR0_PTP_SUB_DELAY_ASYM_ENA(21) = 0
    //INGR0_PTP_MOD_FRAME_BYTE_OFFSET(26: 24) = 0
    //INGR0_PTP_MOD_FRAME_STAT_UPDATE(28) = 0


    //PTP_ANA0_INGR_CFG (Device 0xA slice registers):INGR0_PTP_FLOW[0-5]:INGR0_PTP_FLOW_ENA
    //# IGR0_PTP_FLOW_ENA = 1, IGR0_PTP_CHANNEL_MASK = 3 (Default)
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_FLOW_ENA(0)),
                   0x30);
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_FLOW_ENA(0)),
                   0x31);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ACTION_2(0)),
                   0x4);
    //INGR0_PTP_REWRITE_BYTES (3:0)    =  4  Number of bytes in the PTP or OAM frame that must be modified by the Rewriter for the time stamp
    //INGR0_PTP_REWRITE_OFFSET (15:8) =  0x22 (34) Origin Timestamp Points to where in the frame relative to the SFD that the time stamp should be updated
    //INGR0_PTP_NEW_CF_LOC(23: 16)   = 0    LAN80XX_CSR_WR(dev, port_no,
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ACTION_2(0)),
                   0x2204);


    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_ANAx, 0, LAN80XX_PTP_ANA0_INGR_CFG_INGR0_PTP_ZERO_FIELD_CTL(0)),
                   0x1000);


    return MEPA_RC_OK;
}


// Configuration for 1588 IP Control registers
static mepa_rc lan8042_ts_ip_control_1588(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    //mepa_port_no_t port = port_no;

    //Enables for the egress and ingress encapsulation engine
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_ANALYZER_MODE),
                   LAN80XX_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA |
                   LAN80XX_M_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA);
    return MEPA_RC_OK;
}

#if 0
// Configuration for ingress Delay FIFO registers
static mepa_rc lan8042_ts_ingress_delay_fifo_config(const mepa_device_t  *dev,
                                                    const mepa_port_no_t port_no,
                                                    u32 df_depth)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    mepa_port_no_t port = port_no;
    u8 value = 0;

    // INGR DF Depth must be less than 20
    value = LAN80XX_F_PTP_PROC_INGR_DF_CTRL_INGR_DF_DEPTH(df_depth);
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INGR_DF_CTRL), value);
    //0xe);
    return MEPA_RC_OK;
}

// Configuration for egress Delay FIFO registers
static mepa_rc lan8042_ts_egress_delay_fifo_config(const mepa_device_t  *dev,
                                                   const mepa_port_no_t port_no,
                                                   u32 df_depth)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    mepa_port_no_t port = port_no;
    u8 value = 0;

    // INGR DF Depth must be less than 20
    value = LAN80XX_F_PTP_PROC_EGR_DF_CTRL_EGR_DF_DEPTH(df_depth);
    LAN80XX_CSR_WR(dev, port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_DF_CTRL), value);
    //0xe);
    return MEPA_RC_OK;
}
#endif

// Configuration for for egress tsp
static mepa_rc lan8042_ts_egress_tsp_config(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    //mepa_port_no_t port = port_no;

    //(Delay Asymmetry in ns)  = 1ns
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_DELAY_ASYMMETRY),
                   0x1);

    //# (Local Latency in ns) = 3.517ms from TSP to PCS RSFEC module
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_LOCAL_LATENCY),
                   0x35abcd);
    //(Path Delay in ns) = 44 usec (TODO: to be updated)
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_PATH_DELAY),
                   0xabfe);

    //EGR_LOAD_DELAYS = 1; One - shot loads local latency, path delay, and DelayAsymmetry values into the timestamp processor
    //EGR_TS_FRAME_TYPE(10: 9) = 01: e - frame
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_TSP_CTRL),
                   0x201);


    return MEPA_RC_OK;
}

static mepa_rc lan8042_ts_phase_detection_ctrl(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    //mepa_port_no_t port = port_no;

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_INGR_SOF_PHAD_CTRL),
                   0x58041);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_SOF_PHAD_CTRL),
                   0x58041);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 0, LAN80XX_PTP_PROC_EGR_SOF_PHAD_CTRL),
                   0x58041);

    return MEPA_RC_OK;

}
#endif

static mepa_rc lan80xx_ts_base_port_get_priv(const mepa_device_t *dev,
                                             mepa_port_no_t     *const base_port_no, phy25g_phy_state_t **ptrbase_data)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    if (data->base_dev == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "Base port not assigned for port %s: %u", __FUNCTION__, data->port_no);
        return MEPA_RC_ERROR;
    }

    if (ptrbase_data == NULL) {
        return MEPA_RC_ERROR;
    }

    phy25g_phy_state_t *base_data = (phy25g_phy_state_t *)data->base_dev->data;

    *base_port_no = base_data->port_no;
    *ptrbase_data = (phy25g_phy_state_t *)data->base_dev->data;
    T_D(MEPA_TRACE_GRP_TS, "Pcs retiming mode enabling in port %u, Baseport=%u, base_addr=%x", data->port_no, *base_port_no, data->base_dev->data);
    return MEPA_RC_OK;
}


/* This function gives information about the 1588 supported devices */
mepa_rc lan80xx_ts_is_1588_supported(const mepa_device_t *dev,
                                     mepa_bool_t *gen, mepa_bool_t *support)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    u32 dev_id = 0;
    mepa_bool_t is_supported = FALSE;

    dev_id = data->dev.devid;


    switch (dev_id) {
    case LAN80XX_DEV_ID_8044: // 1G/10G/25G
    case LAN80XX_DEV_ID_8043: // 1G/10G/25G
    case LAN80XX_DEV_ID_8024: // 1G/10G/25G
    case LAN80XX_DEV_ID_8023: // 1G/10G/25G
    case LAN80XX_DEV_ID_8268: // 1G/10G
    case LAN80XX_DEV_ID_8267: // 1G/10G
    case LAN80XX_DEV_ID_8264: // 1G/10G
        is_supported = TRUE;
        break;
    case LAN80XX_DEV_ID_8042: // 1G/10G/25G
    case LAN80XX_DEV_ID_8022: // 1G/10G/25G
    default:
        is_supported = FALSE;
        break;
    }

    *support = is_supported;
    *gen = FALSE;
    /*
    if ((dev_id == LAN80XX_PHY_TYPE_8489) ||
            (dev_id == LAN80XX_PHY_TYPE_8489_15) ||
            (dev_id == LAN80XX_PHY_TYPE_8490) ||
            (dev_id == LAN80XX_PHY_TYPE_8491) ||
            (dev_id == LAN80XX_PHY_TYPE_8491) ||
            (dev_id == LAN80XX_PHY_TYPE_8257) ||
            (dev_id == LAN80XX_PHY_TYPE_8258) ||
            (dev_id == LAN80XX_PHY_TYPE_8254)) {

        *gen = TRUE;
    }
    */
    return MEPA_RC_OK;
}

mepa_rc lan80xx_ts_get_1588_version(const mepa_device_t *dev,
                                    const mepa_port_no_t port_no, u32 *version)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    u32 rev_id = 0 ;


    LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_VERSION_CODE, &rev_id);


    *version = rev_id;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_ts_write_csr(const mepa_device_t *dev,
                                 const mepa_port_no_t port_no,
                                 const phy25g_ts_blk_id_t blk_id,
                                 const u16 csr_address,
                                 const u32 *const value)
{
    phy25g_phy_state_t     *data = (phy25g_phy_state_t *)dev->data;
    lan80xx_phy_ts_biu_addr_map_t *biu_addr_map_ptr = &phy25g_ts_biu_addr_map[0];
//    printf("lan80xx_phy_ts_write_csr\n");
    //if (data->phy_ts_port_conf.port_ts_init_done != FALSE) {
    //printf("performing lan80xx_csr_wr addr =%x value=%x\n",biu_addr_map_ptr->mdio_address[blk_id] | csr_address,*value);
    LAN80XX_CSR_WR(dev, data->port_no,
                   LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, (biu_addr_map_ptr->mdio_address[blk_id] | csr_address)), *value);
    //}

    return MEPA_RC_OK;

}


mepa_rc lan80xx_phy_ts_read_csr(const mepa_device_t *dev,
                                const mepa_port_no_t port_no,
                                const phy25g_ts_blk_id_t blk_id,
                                const u16 csr_address,
                                u32 *const value)
{
    phy25g_phy_state_t     *data = (phy25g_phy_state_t *)dev->data;
    lan80xx_phy_ts_biu_addr_map_t *biu_addr_map_ptr = &phy25g_ts_biu_addr_map[0];
    if (data->phy_ts_port_conf.port_ts_init_done != FALSE) {
        LAN80XX_CSR_RD(dev, data->port_no,
                       LAN80XX_IOREG(MMD_ID_PTP_BLOCK, 1, (biu_addr_map_ptr->mdio_address[blk_id] | csr_address)), value);
    }
    return MEPA_RC_OK;

}




// Configuration for egress Delay FIFO registers
static mepa_rc lan80xx_ts_egress_delay_fifo_config(const mepa_device_t  *dev,
                                                   const mepa_port_no_t port_no,
                                                   u32 df_depth)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    //mepa_port_no_t port = port_no;
    u8 value = 0;

    // INGR DF Depth must be less than 20
    value = LAN80XX_F_PTP_PROC_EGR_DF_CTRL_EGR_DF_DEPTH(df_depth);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_PTP_PROC_EGR_DF_CTRL, value);


    return MEPA_RC_OK;
}


// Configuration for ingress Delay FIFO registers
static mepa_rc lan80xx_ts_ingress_delay_fifo_config(const mepa_device_t  *dev,
                                                    const mepa_port_no_t port_no,
                                                    u32 df_depth)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // Removes Const
    //mepa_port_no_t port = port_no;
    u8 value = 0;

    // INGR DF Depth must be less than 20
    value = LAN80XX_F_PTP_PROC_INGR_DF_CTRL_INGR_DF_DEPTH(df_depth);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_PTP_PROC_INGR_DF_CTRL, value);

    return MEPA_RC_OK;
}


static mepa_rc lan80xx_ts_block_init(const mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data;
    mepa_port_no_t      base_port = 0;
    // Removes Const
    mepa_port_no_t port = port_no;
    u16 clk_src = 0;
    mepa_rc      rc = MEPA_RC_OK;
    u32 value = 0;

    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    clk_src =  base_data->phy_ts_port_conf.clk_src;

    /* Check mch enabled or not */
    if (data->phy_ts_port_conf.mch_conf.mch_en) {

        LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL, LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_CRC_GEN_SEL(0), LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_CRC_GEN_SEL);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL, LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR(!data->phy_ts_port_conf.mch_conf.save_ts_with_crc_err),
                        LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR);

        /* Enable MCH in igress side */
        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL, LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(1),
                        LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL,
                        LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_IGTS_FMT_SEL(data->phy_ts_port_conf.mch_conf.ts_len_ing),
                        LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_IGTS_FMT_SEL);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL, LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_CRC_GEN_SEL(0), LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_CRC_GEN_SEL);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL, LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(!data->phy_ts_port_conf.mch_conf.save_ts_with_crc_err),
                        LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR);

        /*Enable MCH in egress side */
        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL, LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(1),
                        LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL,
                        LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_IGTS_FMT_SEL(data->phy_ts_port_conf.mch_conf.ts_len_egr),
                        LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_IGTS_FMT_SEL);

        /* In packet Interface Mode the MCH Header CRC is calculated by HOST MAC TX Merge block, so MM_TX_ENA bit in HOST_MAC
         * should be set when MCH is enabled regardless of frame preemption state
         */
        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG, LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA, LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA);
    } else {

        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_LINE_SLICE_SLICE_CONFIG, 0, LAN80XX_M_LINE_SLICE_SLICE_CONFIG_MCH_ENABLE);
        /* Disable MCH in igress side */
        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL, LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA(0), LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_ENA);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_INGR_MCH_CTRL, LAN80XX_F_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR(0),
                        LAN80XX_M_PTP_PROC_INGR_MCH_CTRL_INGR_MCH_DROP_CRC_ERROR);
        /* Disable MCH in egress side */
        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL, LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA(0), LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_ENA);

        LAN80XX_CSR_WRM(port, LAN80XX_PTP_PROC_EGR_MCH_CTRL, LAN80XX_F_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR(0),
                        LAN80XX_M_PTP_PROC_EGR_MCH_CTRL_EGR_MCH_DROP_CRC_ERROR);

        LAN80XX_CSR_WRM(port_no, LAN80XX_HOST_MAC_HOST_MAC_ENABLE_CONFIG, LAN80XX_F_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA(data->frame_preempt_ena), LAN80XX_M_HOST_MAC_HOST_MAC_ENABLE_CONFIG_MM_TX_ENA);
    }


    //LTC PLL is shared resource for all port, so init only once for baseport.
    if (!base_data->ptp_shared_ltc_pll_init) {
        /*setting the LTC clock src*/
        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_CMD_REG, LAN80XX_F_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN(1),
                        LAN80XX_M_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN);
        //check some delay required.

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_CMD_REG, LAN80XX_F_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN(0),
                        LAN80XX_M_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_POWERDOWN);

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_DIVR_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_DIVR_REG_LTCPLL_DIVR(phy25g_ts_pll_map[clk_src].pll_r),
                        LAN80XX_M_CLK_CFG_LTCPLL_DIVR_REG_LTCPLL_DIVR);
        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_DIVFI_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_DIVFI_REG_LTCPLL_DIVFI((phy25g_ts_pll_map[clk_src].pll_div_fi)),
                        LAN80XX_M_CLK_CFG_LTCPLL_DIVFI_REG_LTCPLL_DIVFI);

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_DIVFF_HI_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_DIVFF_HI_REG_LTCPLL_DIVFF_HI(phy25g_ts_pll_map[clk_src].pll_divff_hi),
                        LAN80XX_M_CLK_CFG_LTCPLL_DIVFF_HI_REG_LTCPLL_DIVFF_HI);

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_DIVFF_LO_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_DIVFF_LO_REG_LTCPLL_DIVFF_LO(phy25g_ts_pll_map[clk_src].pll_divff_lo),
                        LAN80XX_M_CLK_CFG_LTCPLL_DIVFF_LO_REG_LTCPLL_DIVFF_LO);

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_DIVQ_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_DIVQ_REG_LTCPLL_DIVQ(phy25g_ts_pll_map[clk_src].pll_divq),
                        LAN80XX_M_CLK_CFG_LTCPLL_DIVQ_REG_LTCPLL_DIVQ);

        if ((clk_src == MEPA_TS_CLOCK_SRC_EXTERNAL) || (clk_src == MEPA_TS_CLOCK_SRC_EXT_1588_REF_CLOCK)) {

            //configure the LSC differential pin.
            value = PTP1588_LSC_3_P_N;
            LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_CLK_REF_CFG, LAN80XX_F_PTP_LTC_PTP_CLK_REF_CFG_PTP_CLK_REF_SELECT(value),
                            LAN80XX_M_PTP_LTC_PTP_CLK_REF_CFG_PTP_CLK_REF_SELECT);

        }
        //Recovered clock configuration selection.


        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTC_CLK_CFG_REG,
                        LAN80XX_F_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_SEL(phy25g_ts_pll_map[clk_src].clk_sel),
                        LAN80XX_M_CLK_CFG_LTC_CLK_CFG_REG_LTC_CLK_SEL);

        LAN80XX_CSR_WRM(base_port, LAN80XX_CLK_CFG_LTCPLL_CMD_REG,
                        LAN80XX_F_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_UPDATE(1),
                        LAN80XX_M_CLK_CFG_LTCPLL_CMD_REG_LTCPLL_UPDATE);

    }


    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value));

    /* Default BIT::17 = 0, full 10 byte timestamp is stored,
     * Signature length is set to 16 bytes; Reset the FIFO
     * Generate the timestamp interrrupt for each timestamp update
     */
    value = LAN80XX_PHY_TS_CLR_BITS(value,
                                    LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_SIGNAT_BYTES);
    value |= LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_SIGNAT_BYTES(0x1c);

    value |= LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET;
    value = LAN80XX_PHY_TS_CLR_BITS(value,
                                    LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_THRESH);
    value |= LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_THRESH(8);


    value =  LAN80XX_PHY_TS_CLR_BITS(value,
                                     LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_4BYTES);

    value |= LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_4BYTES(2);


    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value));


    /* clear the reset*/
    value =  LAN80XX_PHY_TS_CLR_BITS(value,
                                     LAN80XX_M_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value));

    value = LAN80XX_F_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_FIFO_RESET(1);


    if (!base_data->ptp_shared_ltc_pll_init) {
        /* setting the clock value */
        LAN80XX_CSR_WR(dev, port, LAN80XX_PTP_LTC_CLK_PER_CFG(1), 0x1921fb54);
        LAN80XX_CSR_WR(dev, port, LAN80XX_PTP_LTC_CLK_PER_CFG(0), 0x7F9EAE35);
    }

    base_data->ptp_shared_ltc_pll_init = TRUE;

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ts_port_init(const mepa_device_t  *dev, const mepa_port_no_t port_no,
                                    const phy25g_phy_ts_init_conf_t  *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc rc = MEPA_RC_OK;
    u32  df_depth = 0, value = 0, cfg_stall_latency = 0;
    u8  latency_table_physpeed_index = 0, latency_table_matchindex = 0, port_clk_div_mode = 0, index_value = 0, cfg_stall_latency_sns = 0;
    mepa_bool_t macsec_enable = 0, macsec_bypass = 0, rs_fec_25g = 0, speed = SPEED_1G;
    macsec_enable = data->macsec_conf.glb.init.enable;
    macsec_bypass = !data->macsec_conf.glb.init.enable;
    rs_fec_25g = data->conf.conf_25g.rs_fec_25g;
    u8 index = 0;


    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }


    if (data->port_state.speed == SPEED_1G) {
        speed = 0;
        latency_table_physpeed_index = 8;
        port_clk_div_mode = 2;
    } else if (data->port_state.speed == SPEED_10G) {
        speed = 1;
        latency_table_physpeed_index = 4;
        port_clk_div_mode = 3;
    } else {
        speed = 2;
        if (data->conf.conf_25g.rs_fec_25g) {
            latency_table_physpeed_index = 12;
        } else {
            latency_table_physpeed_index = 0;
        }
        port_clk_div_mode = 6;
    }


    //Ingress port index in the latency table.
    latency_table_matchindex = latency_table_physpeed_index + (data->port_state.port_mode.oper_mode * 2);


    //Configure the EGR_SOF_PHAD_CTRL for all phy speeds with Non-RFFEC spec.
    if (!data->conf.conf_25g.rs_fec_25g) {
        // Configure EGR_IP_1588_SOF_PHAD,
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_SOF_PHAD_CTRL,
                        LAN80XX_F_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_DIV_MODE(port_clk_div_mode),
                        LAN80XX_M_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_CFG_DIV_MODE);


        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_SOF_PHAD_CTRL,
                        LAN80XX_F_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_DIV_MODE(port_clk_div_mode),
                        LAN80XX_M_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_CFG_DIV_MODE);
    } else {
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_RSFEC_PHAD_CTRL,
                        LAN80XX_F_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_DIV_MODE(port_clk_div_mode),
                        LAN80XX_M_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_CFG_DIV_MODE);

        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_RSFEC_PHAD_CTRL,
                        LAN80XX_F_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_DIV_MODE(port_clk_div_mode),
                        LAN80XX_M_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_CFG_DIV_MODE);

    }

    //configure the stall latency for egress path.

    if (data->port_state.port_mode.oper_mode == MAC_RETIMER) {
        //For egress path index.
        index_value  =  latency_table_matchindex + 1;

        cfg_stall_latency  =  phy25g_ts_local_latency[index_value].cfg_stall_latency;
        value = LAN80XX_F_PTP_PROC_EGR_CFG_STALL_LATENCY_EGR_CFG_STALL_LATENCY(cfg_stall_latency);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_CFG_STALL_LATENCY, &value));

        //Configure sub nanosecond sns.
        cfg_stall_latency_sns = phy25g_ts_local_latency[index_value].cfg_stall_latency_sns;
        value = LAN80XX_F_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS_EGR_CFG_STALL_LATENCY_SNS(cfg_stall_latency_sns);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_CFG_STALL_LATENCY_SNS, &value));


    }

    //configure the Local latency for ingress.

    index_value = latency_table_matchindex;

    value  =  phy25g_ts_local_latency[index_value].local_latency_ns;

    value = LAN80XX_F_PTP_PROC_INGR_LOCAL_LATENCY_INGR_LOCAL_LATENCY(value);
    /* update the ingress latency in the ingr local latency register
     */
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_INGR_LOCAL_LATENCY, &value));


    value = phy25g_ts_local_latency[index_value].local_latency_sns;

    value = LAN80XX_F_PTP_PROC_INGR_LOCAL_LATENCY_SNS_INGR_LOCAL_LATENCY_SNS(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_INGR_LOCAL_LATENCY_SNS, &value));


    //configure the Local latency Egress.
    index_value = latency_table_matchindex + 1;

    value = phy25g_ts_local_latency[index_value].local_latency_ns;

    value = LAN80XX_F_PTP_PROC_EGR_LOCAL_LATENCY_EGR_LOCAL_LATENCY(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_LOCAL_LATENCY, &value));


    value = phy25g_ts_local_latency[index_value].local_latency_sns;
    value = LAN80XX_F_PTP_PROC_EGR_LOCAL_LATENCY_SNS_EGR_LOCAL_LATENCY_SNS(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_LOCAL_LATENCY_SNS, &value));


    // configure the ps_local_latency , ps_local_latency_sns for ingress.
    index_value = latency_table_matchindex;

    value = phy25g_ts_local_latency[index_value].pslocal_latency_ns;

    value = LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY, &value));

    value =  phy25g_ts_local_latency[index_value].pslocal_latency_sns;
    value = LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS, &value));

    // configure the ps_local_latency , ps_local_latency_sns for egress.
    index_value = latency_table_matchindex + 1;
    value = phy25g_ts_local_latency[index_value].pslocal_latency_ns;

    value = LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_EGR_PS_LOCAL_LATENCY(value);
    /* update the egress latency in the egr local latency register*/

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY, &value));

    value =  phy25g_ts_local_latency[index_value].pslocal_latency_sns;

    value  =  LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS_EGR_PS_LOCAL_LATENCY_SNS(value);

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                     LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS, &value));



    df_depth = 0xe;
    MEPA_RC(lan80xx_ts_ingress_delay_fifo_config(dev, port_no, df_depth));
    df_depth = 0x13;
    MEPA_RC(lan80xx_ts_egress_delay_fifo_config(dev, port_no, df_depth));
    /* FIFO mode register */
    if (data->port_state.port_mode.oper_mode == PCS_RETIMER) {
        LAN80XX_CSR_WR (dev, port_no, LAN80XX_PTP_PROC_MODE_CTL, 0x0); //XGMII-64, used in M25 PCS timing mode
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE,
                        LAN80XX_F_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE(1),
                        LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE);
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE,
                        LAN80XX_F_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE(1),
                        LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE);
        T_D(MEPA_TRACE_GRP_TS, "Pcs retiming mode enabling in port %u", (u32)port_no);
    } else {
        LAN80XX_CSR_WR (dev, port_no, LAN80XX_PTP_PROC_MODE_CTL, 0x4); //PKT_MODE, used in M25 MAC timing mode
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_EGR_CFG_OPERATION_MODE,
                        LAN80XX_F_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE(0),
                        LAN80XX_M_PTP_PROC_EGR_CFG_OPERATION_MODE_EGR_CFG_RETIMING_MODE);
        LAN80XX_CSR_WRM(port_no, LAN80XX_PTP_PROC_INGR_CFG_OPERATION_MODE,
                        LAN80XX_F_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE(0),
                        LAN80XX_M_PTP_PROC_INGR_CFG_OPERATION_MODE_INGR_CFG_RETIMING_MODE);
        T_D(MEPA_TRACE_GRP_TS, "Mac retiming mode enabling in port %u", (u32)port_no);
    }

    value = 0;

    //configure Nano second bit configuration.
    if (conf->rx_ts_len == LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_30BIT) {
        value |= LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_FRACT_NS_MODE(1);
    } else {
        value |= LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_FRACT_NS_MODE(0);
    }

    value |= LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS(1);


    LAN80XX_CSR_WR (dev, port_no, LAN80XX_PTP_PROC_INGR_TSP_CTRL_REG,
                    LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_TS_FRAME_TYPE(3) |
                    LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_BYPASS(macsec_bypass) |
                    LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_MACSEC_ENABLE(macsec_enable) |
                    LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_SPEED_25G(speed) |
                    LAN80XX_F_PTP_PROC_INGR_TSP_CTRL_INGR_RSFEC_ENABLE(rs_fec_25g) |
                    value);


    value = 0;

    if (conf->rx_ts_len == LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_30BIT) {
        value |= LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_FRACT_NS_MODE(1);
    } else {
        value |= LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_FRACT_NS_MODE(0);
    }

    value |= LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_LOAD_DELAYS(1);

    LAN80XX_CSR_WR (dev, port_no, LAN80XX_PTP_PROC_EGR_TSP_CTRL_REG,
                    LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_TS_FRAME_TYPE(3) |
                    LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_BYPASS(macsec_bypass) |
                    LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_MACSEC_ENABLE(macsec_enable) |
                    LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_SPEED_25G(speed)  |
                    LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_RSFEC_ENABLE(rs_fec_25g) |
                    value);
    if (!base_data->ptp_shared_sti_interface_init) {

        if (conf->tx_fifo_spi_conf == TRUE) {
            value = 0;
            LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_STI_TS_FIFO_SI_CFG, &value);
            /* clearing bitfeilds SI_CLK_HI_CYCS(10:6),SI_CLK_LO_CYCS(5:1) */
            value = LAN80XX_PHY_TS_CLR_BITS(value, 0x7fe);
            value |= LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_HI_CYCS(conf->tx_fifo_hi_clk_cycs);
            value |= LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_LO_CYCS(conf->tx_fifo_lo_clk_cycs);

            LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_STI_TS_FIFO_SI_CFG, value, LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_LO_CYCS |
                            LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_CLK_HI_CYCS);
            T_D(MEPA_TRACE_GRP_GEN, "custom SPI configuration on port %u , do Conf %s hi_clk_cycs %u lo_clk_cycs %u\n", port_no, conf->tx_fifo_spi_conf ? "TRUE" : "NO", conf->tx_fifo_hi_clk_cycs, conf->tx_fifo_lo_clk_cycs);
        }


        /* Set the serial FIFO mode */
        /* FIFO mode register */
        value = 0;
        /* Set the serial FIFO mode */
        if (conf->tx_fifo_mode == LAN80XX_PHY_TS_FIFO_MODE_SPI) {
            value |= LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA(1);
            value |= LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_SI_EN_DES_CYCS(2);
        } else {
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_F_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA(1));
        }

        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_STI_TS_FIFO_SI_CFG, value, LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_TS_FIFO_SI_ENA |
                        LAN80XX_M_PTP_STI_TS_FIFO_SI_CFG_SI_EN_DES_CYCS );

        base_data->ptp_shared_sti_interface_init = TRUE;
    }

    /* Set the Rx timestamp position */
    if (conf->rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {

#if defined(LAN8042_FEATURE_MACSEC)

#endif

        /* ingress */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));
        /* No preamble modification */
        value &= (~LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_REDUCE_PREAMBLE(1));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));

    } else {

#if defined(LAN8042_FEATURE_MACSEC)

#endif

        /* ingress */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));
        /* No preamble modification */
        value |= (LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_REDUCE_PREAMBLE(1));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));
    }

    if (data->phy_ts_port_conf.chk_ing_modified) {
        /* ingress */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));
        /* Byte offset of the bit to be modified */
        value |= LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_BIT(7);
        /*Value to be written to the bit "1"*/
        value |= LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_VAL(1);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_RW_CTRL, &value));

        /* Egress */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_RW_CTRL, &value));

        /* Byte offset of the bit to be modified */
        value |= LAN80XX_F_PTP_PROC_EGR_RW_CTRL_EGR_RW_FLAG_BIT(7);
        /*Value to be written to the bit "0"*/
        value &= ~LAN80XX_F_PTP_PROC_INGR_RW_CTRL_INGR_RW_FLAG_VAL(1);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_RW_CTRL, &value));

    }
    /* Time Stamp length configuration
     */
    /* Enable the Egress timestamp length configuration
    */
    /* ingress prediction block enable */
    /* egress prediction block enable */
    /* used same macro for egress tmpa calculation,as of ingress
        to limit lines of code*/
    /* used same macro for egress tmpa calculation,as of ingress
        to limit lines of code*/
    /* write egress prediction block enable */
    /* Load the default ingress latency in the ingress local latency register
     */
    /* Load the Values in the ingress time stamp block
     */
    /* Load the default egress latency in the egress local latency register
     */
    /* Load the Values in the egress time stamp block
     */
    /* Set the Egress timestamp FIFO configuration and status register
     * Set timestamp bytes to 16 as default, it can be changed later
     * The TS FIFO popsout the data everytime we read the FIFO,
     */
    /* Default BIT::17 = 0, full 10 byte timestamp is stored,
     * Signature length is set to 16 bytes; Reset the FIFO
     * Generate the timestamp interrrupt for each timestamp update
     */
    /* clear the reset*/
    /* Enable the interface control register */
    /* Bit 6 :: CLK_ENA = 1, CLK_DIS = 0,   Init:CLK_ENA
     * Bit 2 :: BYPASS_DIS  = 0, BYPASS_ENA = 1, Init:BYPASS_ENA
     * Bit 1:0 :: MII protocol : 0 XGMII-64
     */
    /* Below setting bypasses complete 1588 block for Gen1 devices
     * LAN80XX_F_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL_BYPASS
     */

    if (!base_data-> ptp_shared_ltc_resource) {
        value = 0x802B;
        //configure the phase detector.
        for (index = LAN80XX_PTP_LS_CTRL_0; index <= LAN80XX_PTP_LS_CTRL_3; index++) {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_PTP_LTC_PHAD_CTRL(index), value);

        }

        base_data-> ptp_shared_ltc_resource = TRUE;
    }

    if (!data->conf.conf_25g.rs_fec_25g) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_EGR_SOF_PHAD_CTRL, &value);
        //for debugging only.
#if INTERAL_DEBUG
        //Lock not setting at this point so commenting the condition checking.
        if (!LAN80XX_X_PTP_PROC_EGR_SOF_PHAD_CTRL_EGR_STAT_LOCKED(value)) {
            T_E(MEPA_TRACE_GRP_GEN, "SOF Egress phad control lock failed for port %u value=%x\n", __FUNCTION__, port_no, value);
        }
#endif
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_INGR_SOF_PHAD_CTRL, &value);

#if INTERAL_DEBUG
        if (!LAN80XX_X_PTP_PROC_INGR_SOF_PHAD_CTRL_INGR_STAT_LOCKED(value)) {
            T_E(MEPA_TRACE_GRP_GEN, "SOF Ingress phad control lock failed for port %u value=%x\n", __FUNCTION__, port_no, value);
        }
#endif

    } else {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_EGR_RSFEC_PHAD_CTRL, &value);
#if INTERAL_DEBUG
        if (!LAN80XX_X_PTP_PROC_EGR_RSFEC_PHAD_CTRL_EGR_STAT_LOCKED(value)) {
            T_E(MEPA_TRACE_GRP_GEN, "Egress RSFEC phad control lock failed for port %u value=%x\n", __FUNCTION__, port_no, value);
        }


        LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_INGR_RSFEC_PHAD_CTRL, &value);

        if (!LAN80XX_X_PTP_PROC_INGR_RSFEC_PHAD_CTRL_INGR_STAT_LOCKED(value)) {
            T_E(MEPA_TRACE_GRP_GEN, "Ingress RSFEC  phad control lock failed for port %u value=%x\n", __FUNCTION__, port_no, value);
        }
#endif
    }



    return MEPA_RC_OK;
}


mepa_rc lan80xx_ts_hard_reset_private(mepa_device_t *dev, mepa_port_no_t port_no)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    LAN80XX_CSR_COLD_WR(port_no, LAN80XX_LINE_SLICE_LINE_IP1588_RESET,
                        LAN80XX_M_LINE_SLICE_LINE_IP1588_RESET_IP1588_INGR_RST |
                        LAN80XX_M_LINE_SLICE_LINE_IP1588_RESET_IP1588_EGR_RST );

    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_ts_init_conf_get(mepa_device_t *dev, mepa_port_no_t port_no,
                                     mepa_bool_t  *const   port_ts_init_done,
                                     phy25g_phy_ts_init_conf_t         *const conf)
{
    mepa_rc      rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    memset(conf, 0, sizeof(phy25g_phy_ts_init_conf_t));
    *port_ts_init_done = data->phy_ts_port_conf.port_ts_init_done;
    conf->clk_freq  = data->phy_ts_port_conf.clk_freq;
    conf->clk_src   = data->phy_ts_port_conf.clk_src;
    conf->rx_ts_pos = data->phy_ts_port_conf.rx_ts_pos;
    conf->rx_ts_len = data->phy_ts_port_conf.rx_ts_len;
    conf->tx_fifo_mode = data->phy_ts_port_conf.tx_fifo_mode;
    conf->tx_ts_len = data->phy_ts_port_conf.tx_ts_len;
    conf->tc_op_mode = data->phy_ts_port_conf.tc_op_mode;
    conf->one_step_txfifo = data->phy_ts_port_conf.one_step_txfifo;

    return rc;
}


mepa_rc lan80xx_phy_ts_init(const mepa_device_t *dev,
                            const  mepa_port_no_t port_no,
                            const phy25g_phy_ts_init_conf_t  *const conf)
{
    mepa_rc  rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data;
    mepa_port_no_t           base_port_no = port_no ; // (TODO : to be fixed next PR)
    phy25g_phy_ts_init_conf_t  base_conf;
    u32  revision = 0, value = 0, mask = 0;


    T_I(MEPA_TRACE_GRP_GEN, "Port: %u:: ts_init", (u32)port_no);
    MEPA_ASSERT(conf == NULL);
    memset(&base_conf, 0, sizeof(phy25g_phy_ts_init_conf_t));
    memset(&data->phy_ts_port_conf, 0, sizeof(phy25g_phy_ts_port_conf_t));

    do {


        if ((rc = lan80xx_ts_get_1588_version(dev, port_no, &revision)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "1588 version check failed %s,  port %u\n", __FUNCTION__, port_no);
            break;
        }

        if ((rc = lan80xx_ts_base_port_get_priv(dev, &base_port_no, &base_data)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Base port not assigned for port %u\n", __FUNCTION__, port_no);
            break;
        } else {
            T_I(MEPA_TRACE_GRP_GEN, "port base port mapping port %u , baseport %u \n", port_no, base_port_no);
        }


        if (base_port_no == port_no) {
            /*Reset the 1588 clock gen, STI, LTC module.*/

            value = LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_CLKGEN(1);
            value |= LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_STI(1);
            value |= LAN80XX_F_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_LTC(1);

            mask = (LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_CLKGEN |
                    LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_STI | LAN80XX_M_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1_SW_RESET_1588_LTC);

            LAN80XX_CSR_WRM(base_port_no, LAN80XX_GLOBAL_BLOCK_LEVEL_SOFTWARE_RESET1, value, mask);

            //Init the base dev datastructure.
            base_data->ptp_shared_ltc_pll_init =  0;
            base_data->ptp_shared_sti_interface_init = 0;
            base_data->ptp_shared_ltc_resource = 0;
            memset(&base_data->ptp_lsc_input_config, 0, sizeof(phy25g_ptp_lsc_input));
            memset(&base_data->ptp_lsc_output_config, 0, sizeof(phy25g_ptp_lsc_output));
            T_D(MEPA_TRACE_GRP_TS, "LTC reset, port init for baseport=%u port=%u", base_port_no, port_no);

        }


        base_conf.clk_freq  = base_data->phy_ts_port_conf.clk_freq;
        base_conf.clk_src   = base_data->phy_ts_port_conf.clk_src;
        base_conf.rx_ts_pos = base_data->phy_ts_port_conf.rx_ts_pos;
        base_conf.rx_ts_len = base_data->phy_ts_port_conf.rx_ts_len;
        base_conf.tx_fifo_mode = base_data->phy_ts_port_conf.tx_fifo_mode;
        base_conf.tx_ts_len = base_data->phy_ts_port_conf.tx_ts_len;
        base_conf.tc_op_mode = base_data->phy_ts_port_conf.tc_op_mode;
        base_conf.auto_clear_ls = base_data->phy_ts_port_conf.auto_clear_ls;
        base_conf.chk_ing_modified = base_data->phy_ts_port_conf.chk_ing_modified;
        base_conf.one_step_txfifo = base_data->phy_ts_port_conf.one_step_txfifo;


        if ((port_no != base_port_no) && (!data->phy_ts_port_conf.port_ts_init_done)) {

#if 0
            if (memcmp(&base_conf, conf, sizeof(phy25g_phy_ts_init_conf_t)) != 0) {
                rc = MEPA_RC_ERROR;
                T_E(MEPA_TRACE_GRP_GEN, "conf not compatible with base port's, port_no %u, base_port %u", port_no, base_port_no);
                break;
            }
#endif
            if (conf->clk_src != base_data->phy_ts_port_conf.clk_src) {
                T_D(MEPA_TRACE_GRP_TS, "clk source differ for baseport=%u port=%u", base_port_no, port_no);
                rc = MEPA_RC_ERROR;
                break;
            }
        }

        T_D(MEPA_TRACE_GRP_TS, "phy_ts_init init for port=%u clk_src=%u", port_no, conf->clk_src);
        // data->phy_ts_port_conf.port_ts_init_done = TRUE;
        data->phy_ts_port_conf.clk_freq      = conf->clk_freq;
        data->phy_ts_port_conf.clk_src       = conf->clk_src;
        data->phy_ts_port_conf.rx_ts_pos     = conf->rx_ts_pos;
        data->phy_ts_port_conf.rx_ts_len     = conf->rx_ts_len;
        data->phy_ts_port_conf.tx_fifo_mode  = conf->tx_fifo_mode;
        data->phy_ts_port_conf.tx_ts_len     = conf->tx_ts_len;
        data->phy_ts_port_conf.chk_ing_modified  = conf->chk_ing_modified;
        data->phy_ts_port_conf.one_step_txfifo = conf->one_step_txfifo;
        data->phy_ts_port_conf.mch_conf        = conf->mch_conf;
        if (data->phy_ts_port_conf.is_gen2 == TRUE) {
#if defined(LAN80XX_FEATURE_MACSEC)
            if (data->macsec_conf[port_no].glb.init.enable == TRUE) {
                data->phy_ts_port_conf.macsec_ena = TRUE;
            }
#endif
            data->phy_ts_port_conf.auto_clear_ls = conf->auto_clear_ls;
            data->phy_ts_port_conf.pps_conf.pps_pulse_width = 0x1DCD6500;
        }
        switch (conf->tc_op_mode) {
        case LAN80XX_PHY_TS_TC_OP_MODE_A:
            data->phy_ts_port_conf.tc_op_mode = LAN80XX_PHY_TS_TC_OP_MODE_A;
            break;
        case LAN80XX_PHY_TS_TC_OP_MODE_B:
            data->phy_ts_port_conf.tc_op_mode = LAN80XX_PHY_TS_TC_OP_MODE_B;
            break;
        case LAN80XX_PHY_TS_TC_OP_MODE_C:
            data->phy_ts_port_conf.tc_op_mode = LAN80XX_PHY_TS_TC_OP_MODE_C;
            break;

        default:
            /* Keep backward compatibility in case user doesn't pass this parameter */
            data->phy_ts_port_conf.tc_op_mode = LAN80XX_PHY_TS_TC_OP_MODE_B;
            break;
        }

        //data->phy_ts_port_conf.xaui_sel_8487 = conf->xaui_sel_8487; // Is it needed ?

        data->phy_ts_port_conf.base_port     = base_port_no;
        data->phy_ts_port_conf.ingress_latency = 0;
        data->phy_ts_port_conf.egress_latency  = 0;
        if (port_no != base_port_no) {
            data->phy_ts_port_conf.alt_port = port_no;
            data->phy_ts_port_conf.alt_port = port_no;
        }

        /* Initialize the 1588 block */
        if ((rc = LAN80XX_RC_COLD(lan80xx_ts_block_init(dev, port_no))) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "block init failed, port_no %u, base_port %u", port_no, base_port_no);
            break;
        }


        if ((rc = LAN80XX_RC_COLD(lan80xx_ts_port_init(dev, port_no, conf))) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "ts port init failed, port_no %u", port_no);
            break;
        }



    } while (0);


    if (rc != MEPA_RC_OK) {
        data->phy_ts_port_conf.port_ts_init_done = FALSE;
        T_D(MEPA_TRACE_GRP_GEN, "Port: %u:: ts_init failed!", (u32)port_no);
        return rc;
    }
    T_I(MEPA_TRACE_GRP_GEN, "intilizing the ts block %s,  %u", __FUNCTION__, port_no);
    data->phy_ts_port_conf.port_ts_init_done = TRUE;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_get_eng_flow_info(u16 in_flow, phy25g_ts_engine_t *eng_id, u16 *eng_flow)
{
    if (in_flow < TS_FLOWS_PER_ENG * (LAN80XX_PHY_TS_PTP_ENGINE_ID_0 + 1)) {
        *eng_id = LAN80XX_PHY_TS_PTP_ENGINE_ID_0;
    } else if (in_flow >= (TS_FLOWS_PER_ENG * LAN80XX_PHY_TS_PTP_ENGINE_ID_1) &&
               in_flow <  (TS_FLOWS_PER_ENG * LAN80XX_PHY_TS_OAM_ENGINE_ID_2A)) {
        *eng_id = LAN80XX_PHY_TS_PTP_ENGINE_ID_1;
    } else if (in_flow >= (TS_FLOWS_PER_ENG * LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) &&
               in_flow <  (TS_FLOWS_PER_ENG * (LAN80XX_PHY_TS_OAM_ENGINE_ID_2A + 1))) {
        *eng_id = LAN80XX_PHY_TS_OAM_ENGINE_ID_2A;
    } else {
        *eng_id = LAN80XX_PHY_TS_ENGINE_ID_INVALID;
        return MEPA_RC_ERROR;
    }
    *eng_flow = in_flow % TS_FLOWS_PER_ENG;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_ts_ana_blk_id_get(phy25g_ts_engine_t eng_id,
                                             BOOL                 ingress,
                                             phy25g_ts_blk_id_t *blk_id)
{
    mepa_rc rc = MEPA_RC_OK;

    switch (eng_id) {
    case LAN80XX_PHY_TS_PTP_ENGINE_ID_0:
        *blk_id = (ingress ? LAN80XX_PHY_TS_ANA_BLK_ID_ING(0) : LAN80XX_PHY_TS_ANA_BLK_ID_EGR(0));
        break;
    case LAN80XX_PHY_TS_PTP_ENGINE_ID_1:
        *blk_id = (ingress ? LAN80XX_PHY_TS_ANA_BLK_ID_ING(1) :
                   LAN80XX_PHY_TS_ANA_BLK_ID_EGR(1));
        break;
    case LAN80XX_PHY_TS_OAM_ENGINE_ID_2A:
    case LAN80XX_PHY_TS_OAM_ENGINE_ID_2B:
        *blk_id = (ingress ? LAN80XX_PHY_TS_ANA_BLK_ID_ING(2) :
                   LAN80XX_PHY_TS_ANA_BLK_ID_EGR(2));
        break;
    default:
        /* should never reach here */
        *blk_id = LAN80XX_PHY_TS_ANA_BLK_ID_ING(0);
        T_E(MEPA_TRACE_GRP_GEN, "Invalid engine id (%d), ingress %d", eng_id, ingress);
        rc = MEPA_RC_ERROR;
        break;
    }
    return rc;
}

static mepa_rc lan80xx_phy_ts_ip1_different_offset_set(
    mepa_device_t *dev,
    const mepa_port_no_t        port_no,
    const phy25g_ts_blk_id_t  blk_id,
    const u8                    ip_mode,
    BOOL                        double_ip)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value, temp;
    switch (ip_mode) {
    case LAN80XX_PHY_TS_IP_VER_4:
        /* IP mode */
        value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_MODE_IP1_MODE(0);
        value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_MODE_IP1_FLOW_OFFSET(0x0C);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_MODE, &value));
        if (double_ip) {
            /* IP1_PROT_MATCH_1 */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_OFFSET_1(9);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MASK_1(0xFF);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MATCH_1(4);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1, &value));

            /* No need of PROT_OFFSET_2 */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2, &value));
            /* checksum: no UDP for IP-IP */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
        } else {
            /* IP1_PROT_MATCH_1 */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_OFFSET_1(9);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MASK_1(0xFF);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MATCH_1(17);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1, &value));

            /* UDP port number offset from IP header */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2_IP1_PROT_OFFSET_2(20);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2, &value));

            /* checksum */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
            temp = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_OFFSET(26);
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_OFFSET) | temp;
            temp = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_WIDTH(2);
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_WIDTH) | temp;
            value &= ~LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_UPDATE_ENA;
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_CLEAR_ENA;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
        }
        break;
    case LAN80XX_PHY_TS_IP_VER_6:
        /* IP mode */
        value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_MODE_IP1_MODE(1);
        value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_MODE_IP1_FLOW_OFFSET(8);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_MODE, &value));
        if (double_ip) {
            /* IP1_PROT_MATCH_1 */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_OFFSET_1(6);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MASK_1(0xFF);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MATCH_1(41);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1, &value));

            /* No need of PROT_OFFSET_2 */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2, &value));
            /* checksum: no UDP for IP-IP */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
        } else {
            /* IP1_PROT_MATCH_1 */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_OFFSET_1(6);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MASK_1(0xFF);
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1_IP1_PROT_MATCH_1(17);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_1, &value));

            /* UDP port number offset from IP header */
            value = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2_IP1_PROT_OFFSET_2(40);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_OFFSET_2, &value));
            /* checksum */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
            temp = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_OFFSET(46);
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_OFFSET) | temp;
            temp = LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_WIDTH(2);
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_WIDTH) | temp;
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_UPDATE_ENA;
            value &= ~LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG_IP1_UDP_CHKSUM_CLEAR_ENA;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));
        }
        break;

    default:
        return MEPA_RC_ERROR;
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_ts_ip2_different_offset_set(
    mepa_device_t *dev,
    const mepa_port_no_t        port_no,
    const phy25g_ts_blk_id_t    blk_id,
    const u8                    ip_mode)
{
    u32 value = 0, temp = 0;

    switch (ip_mode) {
    case LAN80XX_PHY_TS_IP_VER_4:
        /* IP mode */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_MODE_IP2_MODE(0);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_MODE_IP2_FLOW_OFFSET(0x0C);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_MODE, &value));
        /* IP2_PROT_MATCH_1 */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_OFFSET_1(9);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_MASK_1(0xFF);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_MATCH_1(0x11);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1, &value));

        /* UDP port number offset from IP header */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_OFFSET_2_IP2_PROT_OFFSET_2(20);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_PROT_OFFSET_2, &value));
        /* checksum */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG, &value));
        temp = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_OFFSET(26);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_OFFSET) | temp;
        temp = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_WIDTH(2);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_WIDTH) | temp;
        value &= ~LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_UPDATE_ENA;
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_CLEAR_ENA;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG, &value));
        break;
    case LAN80XX_PHY_TS_IP_VER_6:
        /* IP mode */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_MODE_IP2_MODE(1);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_MODE_IP2_FLOW_OFFSET(8);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_MODE, &value));
        /* IP2_PROT_MATCH_1 */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_OFFSET_1(6);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_MASK_1(0xFF);
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1_IP2_PROT_MATCH_1(0x11);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_PROT_MATCH_1, &value));

        /* UDP port number offset from IP header */
        value = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_PROT_OFFSET_2_IP2_PROT_OFFSET_2(40);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_PROT_OFFSET_2, &value));
        /* checksum */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG, &value));
        temp = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_OFFSET(46);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_OFFSET) | temp;
        temp = LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_WIDTH(2);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_WIDTH) | temp;
        value &= ~LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_UPDATE_ENA;
        value |= LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG_IP2_UDP_CHKSUM_CLEAR_ENA;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_UDP_CHKSUM_CFG, &value));
        break;
    default:
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}


#if 1
static mepa_rc lan80xx_ts_mpls_flow_conf(mepa_device_t *dev,
                                         const phy25g_ts_engine_t eng_id,
                                         const u16 flow_index,
                                         BOOL ingress,
                                         const phy25g_ts_next_comp_t next_comp,
                                         phy25g_ts_engine_flow_conf_t *const flow_conf,
                                         phy25g_ts_eng_conf_t *eng_conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_blk_id_t blk_id;
    u32 value = 0, temp = 0;
    u8 stack_ref_point = 0;

    mepa_bool_t  bool2, bool3, bool4;
    phy25g_ts_mpls_conf_t *old_mpls_conf;
    phy25g_ts_mpls_conf_t *new_mpls_conf;

    const mepa_port_no_t       port_no = data->port_no;
    BOOL cw_present = FALSE;

    old_mpls_conf = &flow_conf->flow_conf.ptp.mpls_opt;
    new_mpls_conf = &eng_conf->flow_conf.flow_conf.ptp.mpls_opt;

#if 1
    if (((eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP) ||
         (eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP)) && (new_mpls_conf->comm_opt.cw_en)) {
        //  printf("Port: %u engine: %u:: Wrong control word configuration for encaptype : %d",(u32)port_no, (u32)eng_id, eng_conf->encap_type);
        cw_present = new_mpls_conf->comm_opt.cw_en;
    }
#endif


    if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
        return MEPA_RC_ERROR;
    }



    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 ||
        eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1 || eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
        if (old_mpls_conf->comm_opt.cw_en != new_mpls_conf->comm_opt.cw_en) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_NXT_COMPARATOR_MPLS_NXT_COMPARATOR, &value));
            if (cw_present) {
                value |= LAN80XX_F_ANA_MPLS_NXT_COMPARATOR_MPLS_NXT_COMPARATOR_MPLS_CTL_WORD;
            } else {
                value &= ~LAN80XX_F_ANA_MPLS_NXT_COMPARATOR_MPLS_NXT_COMPARATOR_MPLS_CTL_WORD;
            }
            value |= next_comp;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_NXT_COMPARATOR_MPLS_NXT_COMPARATOR, &value));
        }
        /* PTP engine MPLS config */
        /* channel map, flow enable, stack depth and stack ref point config */
        bool2 = (new_mpls_conf->flow_opt[flow_index].flow_en != old_mpls_conf->flow_opt[flow_index].flow_en);
        bool3 = (new_mpls_conf->flow_opt[flow_index].stack_depth != old_mpls_conf->flow_opt[flow_index].stack_depth);
        bool4 = (new_mpls_conf->flow_opt[flow_index].stack_ref_point != old_mpls_conf->flow_opt[flow_index].stack_ref_point);
        if (bool2 || bool3 || bool4) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL(flow_index), &value));

            temp = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_CHANNEL_MASK(3);

            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_CHANNEL_MASK) | temp;

            if (bool2) {
                if (new_mpls_conf->flow_opt[flow_index].flow_en) {
                    value |=  LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_FLOW_ENA;
                } else {
                    value &=  ~LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_FLOW_ENA;
                }
            }
            if (bool3) {
                temp = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_STACK_DEPTH(new_mpls_conf->flow_opt[flow_index].stack_depth);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_STACK_DEPTH) | temp;
            }
            if (bool4) {
                if (new_mpls_conf->flow_opt[flow_index].stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_END) {
                    stack_ref_point = LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_END;
                    value |=  LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_REF_PNT;
                } else {
                    stack_ref_point = LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP;
                    value &=  ~LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL_MPLS_REF_PNT;
                }
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL(flow_index), &value));
        }


//      (LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_FLOW_CONTROL(flow_index), &value)

        /* configure stack levels based on ref point */
        /* top-of-stack referenced */
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.top.lower :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.thrd_lvl_before_end.lower;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_0_MPLS_LABEL_RANGE_LOWER_0(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_0(flow_index), &value));
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.top.upper :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.thrd_lvl_before_end.upper;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_0_MPLS_LABEL_RANGE_UPPER_0(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_0(flow_index), &value));
        /* 1st after top */
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.frst_lvl_after_top.lower :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.snd_lvl_before_end.lower;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_1_MPLS_LABEL_RANGE_LOWER_1(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_1(flow_index), &value));
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.frst_lvl_after_top.upper :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.snd_lvl_before_end.upper;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_1_MPLS_LABEL_RANGE_UPPER_1(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_1(flow_index),  &value));
        /* 2nd after top */
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.snd_lvl_after_top.lower :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.frst_lvl_before_end.lower;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_2_MPLS_LABEL_RANGE_LOWER_2(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_2(flow_index),  &value));
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.snd_lvl_after_top.upper :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.frst_lvl_before_end.upper;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_2_MPLS_LABEL_RANGE_UPPER_2(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_2(flow_index),  &value));
        /* 3rd after top */
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.thrd_lvl_after_top.lower :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.end.lower;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_3_MPLS_LABEL_RANGE_LOWER_3(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_LOWER_3(flow_index),  &value));
        temp = (stack_ref_point == LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP) ?
               new_mpls_conf->flow_opt[flow_index].stack_level.top_down.thrd_lvl_after_top.upper :
               new_mpls_conf->flow_opt[flow_index].stack_level.bottom_up.end.upper;
        value = LAN80XX_F_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_3_MPLS_LABEL_RANGE_UPPER_3(temp);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_LABEL_RANGE_UPPER_3(flow_index),  &value));


        value = 0;

        value |=  new_mpls_conf->flow_opt[flow_index].stack_level.top_down.frst_lvl_after_top.match_mode << LAN80XX_8_BIT_SHIFT |
                  new_mpls_conf->flow_opt[flow_index].stack_level.top_down.top.match_mode;

        value |= new_mpls_conf->flow_opt[flow_index].stack_level.top_down.snd_lvl_after_top.match_mode << LAN80XX_16_BIT_SHIFT;

        value |= new_mpls_conf->flow_opt[flow_index].stack_level.top_down.thrd_lvl_after_top.match_mode << LAN80XX_24_BIT_SHIFT;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_MPLS_FLOW_CFG_MPLS_FLOW_MATCH_MODE(flow_index), &value));

    }

    return MEPA_RC_OK;
}
#endif

static mepa_rc lan80xx_ts_eth1_flow_conf(mepa_device_t *dev,
                                         const phy25g_ts_engine_t eng_id,
                                         const u16 flow_index,
                                         BOOL ingress,
                                         const phy25g_ts_next_comp_t next_comp,
                                         phy25g_ts_engine_flow_conf_t *const flow_conf,
                                         phy25g_ts_eth_conf_t *const eth_conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_blk_id_t blk_id;
    phy25g_ts_eth_conf_t *old_eth_conf;
    u32 value = 0, temp = 0;
    BOOL bool1, bool2, bool3;
    old_eth_conf = &flow_conf->flow_conf.ptp.eth1_opt;
    u32 match_mode_val      = 0;
    u32 tag_rng_i_tag_lower = 0, tag_rng_i_tag_upper = 0;
    u32 tag2_i_tag_lower    = 0, tag2_i_tag_upper    = 0;
    u32 tag1_lower          = 0, tag1_upper          = 0;

    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID_0,
                                    LAN80XX_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE, &value));

    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 || eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
        temp |= ((u32)(0x01 << eng_id));  /* do the typecast to make lint happy! */

    } else {
        //#{TBD}
    }
    if (ingress == FALSE) {

        //Shift engine id to egress bit position.
        temp = temp << LAN80XX_4_BIT_SHIFT;
        // value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA) | temp;
    }

    //Enable Ingress, Egress individual Encap flow.
    value |= 0x1000000 | temp ;

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID_0,
                                     LAN80XX_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE, &value));

    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 ||
        eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1 ||
        eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
        if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }

        if (eth_conf->comm_opt.pbb_en) {

            if (eth_conf->flow_opt[flow_index].num_tag == 0) {
                return MEPA_RC_ERROR;
            }
            if (eth_conf->flow_opt[flow_index].tag_range_mode != LAN80XX_PHY_TS_TAG_RANGE_NONE) {
                return MEPA_RC_ERROR;
            }
            /* For single tag, inner_tag is always I-tag, for double tag, inner is
               I-tag, outer is B-tag always */
            if (eth_conf->flow_opt[flow_index].inner_tag_type != LAN80XX_PHY_TS_TAG_TYPE_I ||
                (eth_conf->flow_opt[flow_index].num_tag == 2 &&
                 eth_conf->flow_opt[flow_index].outer_tag_type != LAN80XX_PHY_TS_TAG_TYPE_B)) {
                return MEPA_RC_ERROR;
            }

        }

        if (old_eth_conf->comm_opt.pbb_en != eth_conf->comm_opt.pbb_en) {
            value = (eth_conf->comm_opt.pbb_en ?
                     LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_TAG_MODE_ETH1_PBB_ENA : 0);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_TAG_MODE, &value));
        }
        if (old_eth_conf->comm_opt.tpid != eth_conf->comm_opt.tpid) {
            value = eth_conf->comm_opt.tpid;
            value = LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_VLAN_TPID_CFG_ETH1_VLAN_TPID_CFG(value);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_VLAN_TPID_CFG, &value));
        }
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));
        temp = LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_NXT_COMPARATOR(next_comp);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_NXT_COMPARATOR) | temp;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));

        /* etype match */
        value = 0;
        if (old_eth_conf->comm_opt.etype != eth_conf->comm_opt.etype) {
            value = (LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_ETYPE_MATCH_ETH1_ETYPE_MATCH_ENA |
                     LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_ETYPE_MATCH_ETH1_ETYPE_MATCH(eth_conf->comm_opt.etype));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_ETYPE_MATCH, &value));
        }

        temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE_ETH1_CHANNEL_MASK(3);
        value =  LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE_ETH1_FLOW_ENABLE | temp;

        if (eth_conf->flow_opt[flow_index].flow_en != old_eth_conf->flow_opt[flow_index].flow_en) {
            if (eth_conf->flow_opt[flow_index].flow_en) {
                value =  LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE_ETH1_FLOW_ENABLE | temp;
            } else {
                value =  ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE_ETH1_FLOW_ENABLE | temp;
            }
        }

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE(flow_index), &value));

        /* addr match mode, match select and last 2 bytes of MAC */
        bool1 = (old_eth_conf->flow_opt[flow_index].addr_match_mode != eth_conf->flow_opt[flow_index].addr_match_mode);
        bool2 = (old_eth_conf->flow_opt[flow_index].addr_match_select != eth_conf->flow_opt[flow_index].addr_match_select);
        bool3 = (old_eth_conf->flow_opt[flow_index].mac_addr[5] != eth_conf->flow_opt[flow_index].mac_addr[5]) ||
                (old_eth_conf->flow_opt[flow_index].mac_addr[4] != eth_conf->flow_opt[flow_index].mac_addr[4]);

        if (bool1 || bool2 || bool3) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2(flow_index), &value));
            if (bool1) {
                temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_MODE(eth_conf->flow_opt[flow_index].addr_match_mode);
                value =  LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_MODE) | temp;
            }
            if (bool2) {
                temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_SELECT(eth_conf->flow_opt[flow_index].addr_match_select);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_SELECT) | temp;
            }
            if (bool3) {
                temp = (eth_conf->flow_opt[flow_index].mac_addr[4] << 8) | eth_conf->flow_opt[flow_index].mac_addr[5];
                temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_2(temp);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2_ETH1_ADDR_MATCH_2) | temp;
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_2(flow_index), &value));
        }
        /* first 4 bytes of MAC */
        if (memcmp(old_eth_conf->flow_opt[flow_index].mac_addr, eth_conf->flow_opt[flow_index].mac_addr, 4) != 0) {
            value = eth_conf->flow_opt[flow_index].mac_addr[0] << 24 |
                    eth_conf->flow_opt[flow_index].mac_addr[1] << 16 |
                    eth_conf->flow_opt[flow_index].mac_addr[2] << 8 |
                    eth_conf->flow_opt[flow_index].mac_addr[3];
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_ADDR_MATCH_1(flow_index), &value));
        }

        /* ETH1_MATCH_MODE, VLAN_TAG_RANGE_I_TAG, VLAN_TAG1 and VLAN_TAG2_I_TAG
           has different config based on combination of number of tag, tag_type
           and tag range. So it's better to set these reg everytime flow config
           is set. This will be set only for enabled flow */
        /* ETH1_MATCH_MODE */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE(flow_index), &match_mode_val));
        temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAGS(eth_conf->flow_opt[flow_index].num_tag);
        match_mode_val = LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAGS) | temp;

        if (eth_conf->flow_opt[flow_index].vlan_check) {
            match_mode_val |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_VERIFY_ENA;
        } else {
            match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_VERIFY_ENA;
        }

        if (eth_conf->flow_opt[flow_index].flow_en == FALSE) {
            match_mode_val = 0;
            tag_rng_i_tag_lower = 0;
            tag_rng_i_tag_upper = 0;
            tag1_lower = 0;
            tag1_upper = 0;
            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;

        } else if (eth_conf->comm_opt.pbb_en) {
            /* flow en and pbb en */
            /* ETH1_MATCH_MODE */
            temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE(0); /* no range check */
            match_mode_val =  LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE) | temp;
            /* tag2_type is always I-tag: set the bit, DSH is not correct! */
            match_mode_val |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG2_TYPE;
            /* tag1_type is always B-tag: clear the bit, DSH is not correct! */
            match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;

            /* TAG_RANGE_I_TAG and TAG2_I_TAG contains I-tag */
            tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.i_tag.val & 0xFFF;  /* lower 12-bits */
            tag_rng_i_tag_upper = (eth_conf->flow_opt[flow_index].inner_tag.i_tag.val & 0xFFF000) >> 12; /* upper 12-bits */
            tag2_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.i_tag.mask & 0xFFF; /* lower 12-bits */
            tag2_i_tag_upper = temp = (eth_conf->flow_opt[flow_index].inner_tag.i_tag.mask & 0xFFF000) >> 12; /* upper 12-bits */
            /* VLAN_TAG1 */
            if (eth_conf->flow_opt[flow_index].num_tag == 2) {
                tag1_lower = eth_conf->flow_opt[flow_index].outer_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].outer_tag.value.mask & 0xFFF; /* 12-bits */
            } else {
                tag1_lower = 0;
                tag1_upper = 0;
            }
        } else if (eth_conf->flow_opt[flow_index].num_tag == 2) { /* flow en, pbb dis and num-tag = 2 */
            /* ETH1_MATCH_MODE */
            temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE(eth_conf->flow_opt[flow_index].num_tag);
            match_mode_val =  LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE) | temp;

            /* tag1_type */
            if (eth_conf->flow_opt[flow_index].outer_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].outer_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;
            }
            /* tag2_type */
            if (eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG2_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG2_TYPE;
            }
            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_OUTER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].outer_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].outer_tag.range.upper & 0xFFF; /* 12-bits */
                tag1_lower = 0;
                tag1_upper = 0;
                tag2_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag2_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            } else if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.range.upper & 0xFFF; /* 12-bits */
                tag2_i_tag_lower = 0;
                tag2_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].outer_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].outer_tag.value.mask & 0xFFF; /* 12-bits */
            } else { /* No range only for particular value */
                tag_rng_i_tag_lower = 0;
                tag_rng_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].outer_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].outer_tag.value.mask & 0xFFF; /* 12-bits */
                tag2_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag2_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            }
        } else if (eth_conf->flow_opt[flow_index].num_tag == 1) {
            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE(1); /* Tag1 range check */
            } else {
                temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE(0); /* no range check */
            }
            match_mode_val = LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE) | (temp |  LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAGS(1));
            /* tag1_type */
            if (eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;
            }
            /* tag2_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG2_TYPE;
            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;

            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.range.upper & 0xFFF; /* 12-bits */
                tag1_lower = 0;
                tag1_upper = 0;
            } else {
                tag_rng_i_tag_lower = 0;
                tag_rng_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            }
        } else {
            /* flow en, pbb dis and num-tag = 0 */
            /* ETH1_MATCH_MODE */
            temp = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE(0); /* no range check */
            match_mode_val =  LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG_MODE) | temp;

            /* tag1_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG1_TYPE;
            /* tag2_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE_ETH1_VLAN_TAG2_TYPE;

            tag_rng_i_tag_lower = 0;
            tag_rng_i_tag_upper = 0;
            tag1_lower = 0;
            tag1_upper = 0;
            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;
        }



        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_MATCH_MODE(flow_index), &match_mode_val));
        /* TAG_RANGE_I_TAG */
        value = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG_RANGE_I_TAG_ETH1_VLAN_TAG_RANGE_LOWER(tag_rng_i_tag_lower);
        value |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG_RANGE_I_TAG_ETH1_VLAN_TAG_RANGE_UPPER(tag_rng_i_tag_upper);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG_RANGE_I_TAG(flow_index), &value));

        /* TAG1 */
        value = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG1_ETH1_VLAN_TAG1_MATCH(tag1_lower);
        value |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG1_ETH1_VLAN_TAG1_MASK(tag1_upper);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG1(flow_index), &value));
        /* TAG2_I_TAG */
        value = LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG2_I_TAG_ETH1_VLAN_TAG2_MATCH(tag2_i_tag_lower);
        value |= LAN80XX_F_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG2_I_TAG_ETH1_VLAN_TAG2_MASK(tag2_i_tag_upper);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_VLAN_TAG2_I_TAG(flow_index), &value));


    }
    return MEPA_RC_OK;
}

static  mepa_rc lan80xx_ts_eth2_flow_conf(mepa_device_t *dev,
                                          const phy25g_ts_engine_t eng_id,
                                          const u16 flow_index,
                                          BOOL ingress,
                                          const phy25g_ts_next_comp_t next_comp,
                                          phy25g_ts_engine_flow_conf_t *const flow_conf,
                                          phy25g_ts_eth_conf_t *const eth_conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_blk_id_t blk_id;
    phy25g_ts_eth_conf_t *old_eth_conf;
    u32 value, temp;
    BOOL bool1, bool2, bool3;
    old_eth_conf = &flow_conf->flow_conf.ptp.eth2_opt;
    u32 match_mode_val      = 0;
    u32 tag_rng_i_tag_lower = 0, tag_rng_i_tag_upper = 0;
    u32 tag2_i_tag_lower    = 0, tag2_i_tag_upper    = 0;
    u32 tag1_lower          = 0, tag1_upper          = 0;
    const mepa_port_no_t       port_no = data->port_no;



    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 ||
        eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1 ||
        eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
        if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }

        if (old_eth_conf->comm_opt.tpid != eth_conf->comm_opt.tpid) {
            value = eth_conf->comm_opt.tpid;
            value = LAN80XX_F_ANA_ETH2_NXT_PROTOCOL_ETH2_VLAN_TPID_CFG_ETH2_VLAN_TPID_CFG(value);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_NXT_PROTOCOL_ETH2_VLAN_TPID_CFG, &value));
        }
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_NXT_PROTOCOL_ETH2_NXT_PROTOCOL, &value));
        temp = LAN80XX_F_ANA_ETH2_NXT_PROTOCOL_ETH2_NXT_PROTOCOL_ETH2_NXT_COMPARATOR(next_comp);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH2_NXT_PROTOCOL_ETH2_NXT_PROTOCOL_ETH2_NXT_COMPARATOR) | temp;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_NXT_PROTOCOL_ETH2_NXT_PROTOCOL, &value));

        /* etype match */
        value = 0;
        if (old_eth_conf->comm_opt.etype != eth_conf->comm_opt.etype) {
            value = (LAN80XX_F_ANA_ETH2_NXT_PROTOCOL_ETH2_ETYPE_MATCH_ETH2_ETYPE_MATCH_ENA |
                     LAN80XX_F_ANA_ETH2_NXT_PROTOCOL_ETH2_ETYPE_MATCH_ETH2_ETYPE_MATCH(eth_conf->comm_opt.etype));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_NXT_PROTOCOL_ETH2_ETYPE_MATCH, &value));
        }

        temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_FLOW_ENABLE_ETH2_CHANNEL_MASK(3);
        value =  LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_FLOW_ENABLE_ETH2_FLOW_ENABLE | temp;

        if (eth_conf->flow_opt[flow_index].flow_en != old_eth_conf->flow_opt[flow_index].flow_en) {
            if (eth_conf->flow_opt[flow_index].flow_en) {
                value =  LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_FLOW_ENABLE_ETH2_FLOW_ENABLE | temp;
            } else {
                value =  ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_FLOW_ENABLE_ETH2_FLOW_ENABLE | temp;
            }

            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_FLOW_ENABLE(flow_index), &value));
        }


        /* addr match mode, match select and last 2 bytes of MAC */
        bool1 = (old_eth_conf->flow_opt[flow_index].addr_match_mode != eth_conf->flow_opt[flow_index].addr_match_mode);
        bool2 = (old_eth_conf->flow_opt[flow_index].addr_match_select != eth_conf->flow_opt[flow_index].addr_match_select);
        bool3 = (old_eth_conf->flow_opt[flow_index].mac_addr[5] != eth_conf->flow_opt[flow_index].mac_addr[5]) ||
                (old_eth_conf->flow_opt[flow_index].mac_addr[4] != eth_conf->flow_opt[flow_index].mac_addr[4]);

        if (bool1 || bool2 || bool3) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2(flow_index), &value));
            if (bool1) {
                temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_MODE(eth_conf->flow_opt[flow_index].addr_match_mode);
                value =  LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_MODE) | temp;
            }
            if (bool2) {
                temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_SELECT(eth_conf->flow_opt[flow_index].addr_match_select);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_SELECT) | temp;
            }
            if (bool3) {
                temp = (eth_conf->flow_opt[flow_index].mac_addr[4] << 8) | eth_conf->flow_opt[flow_index].mac_addr[5];
                temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_2(temp);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2_ETH2_ADDR_MATCH_2) | temp;
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_2(flow_index), &value));
        }
        /* first 4 bytes of MAC */
        if (memcmp(old_eth_conf->flow_opt[flow_index].mac_addr, eth_conf->flow_opt[flow_index].mac_addr, 4) != 0) {
            value = eth_conf->flow_opt[flow_index].mac_addr[0] << 24 |
                    eth_conf->flow_opt[flow_index].mac_addr[1] << 16 |
                    eth_conf->flow_opt[flow_index].mac_addr[2] << 8 |
                    eth_conf->flow_opt[flow_index].mac_addr[3];
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_ADDR_MATCH_1(flow_index), &value));
        }

        /* ETH2_MATCH_MODE, VLAN_TAG_RANGE_I_TAG, VLAN_TAG1 and VLAN_TAG2_I_TAG
               has different config based on combination of number of tag, tag_type
               and tag range. So it's better to set these reg everytime flow config
               is set. This will be set only for enabled flow */
        /* ETH2_MATCH_MODE */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE(flow_index), &match_mode_val));
        temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAGS(eth_conf->flow_opt[flow_index].num_tag);
        match_mode_val = LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAGS) | temp;

        if (eth_conf->flow_opt[flow_index].vlan_check) {
            match_mode_val |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_VERIFY_ENA;
        } else {
            match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_VERIFY_ENA;
        }

        if (eth_conf->flow_opt[flow_index].flow_en == FALSE) {
            match_mode_val = 0;
            tag_rng_i_tag_lower = 0;
            tag_rng_i_tag_upper = 0;
            tag1_lower = 0;
            tag1_upper = 0;
            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;
        } else if (eth_conf->flow_opt[flow_index].num_tag == 2) { /* flow en, pbb dis and num-tag = 2 */
            /* ETH2_MATCH_MODE */
            temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE(eth_conf->flow_opt[flow_index].tag_range_mode);
            match_mode_val =  LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE) | temp;

            /* tag1_type */
            if (eth_conf->flow_opt[flow_index].outer_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].outer_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG1_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG1_TYPE;
            }
            /* tag2_type */
            if (eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG2_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG2_TYPE;
            }
            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_OUTER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].outer_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].outer_tag.range.upper & 0xFFF; /* 12-bits */
                tag1_lower = 0;
                tag1_upper = 0;
                tag2_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag2_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            } else if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.range.upper & 0xFFF; /* 12-bits */
                tag2_i_tag_lower = 0;
                tag2_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].outer_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].outer_tag.value.mask & 0xFFF; /* 12-bits */
            } else {
                /* No range only for particular value */
                tag_rng_i_tag_lower = 0;
                tag_rng_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].outer_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].outer_tag.value.mask & 0xFFF; /* 12-bits */
                tag2_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag2_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            }
        } else if (eth_conf->flow_opt[flow_index].num_tag == 1) {
            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE(1); /* Tag1 range check */
            } else {
                temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE(0); /* no range check */
            }
            match_mode_val = LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE) | (temp |  LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAGS(1));
            /* tag1_type */
            if (eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_S ||
                eth_conf->flow_opt[flow_index].inner_tag_type == LAN80XX_PHY_TS_TAG_TYPE_B) {
                match_mode_val |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG1_TYPE;
            } else {
                match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG1_TYPE;
            }
            /* tag2_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG2_TYPE;

            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;

            if (eth_conf->flow_opt[flow_index].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
                tag_rng_i_tag_lower = eth_conf->flow_opt[flow_index].inner_tag.range.lower & 0xFFF; /* 12-bits */
                tag_rng_i_tag_upper = eth_conf->flow_opt[flow_index].inner_tag.range.upper & 0xFFF; /* 12-bits */
                tag1_upper = 0 ;
                tag1_lower = 0;
            } else {
                tag_rng_i_tag_lower = 0;
                tag_rng_i_tag_upper = 0;
                tag1_lower = eth_conf->flow_opt[flow_index].inner_tag.value.val & 0xFFF; /* 12-bits */
                tag1_upper = eth_conf->flow_opt[flow_index].inner_tag.value.mask & 0xFFF; /* 12-bits */
            }
        } else {
            /* flow en and num-tag = 0 */
            /* ETH2_MATCH_MODE */
            temp = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE(0); /* no range check */
            match_mode_val =  LAN80XX_PHY_TS_CLR_BITS(match_mode_val, LAN80XX_M_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG_MODE) | temp;
            /* tag1_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG1_TYPE;
            /* tag2_type */
            match_mode_val &= ~LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE_ETH2_VLAN_TAG2_TYPE;

            tag_rng_i_tag_lower = 0;
            tag_rng_i_tag_upper = 0;
            tag1_lower = 0;
            tag1_upper = 0;
            tag2_i_tag_lower = 0;
            tag2_i_tag_upper = 0;

        }

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_MATCH_MODE(flow_index), &match_mode_val));
        /* TAG_RANGE_I_TAG */
        value = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG_RANGE_I_TAG_ETH2_VLAN_TAG_RANGE_LOWER(tag_rng_i_tag_lower);
        value |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG_RANGE_I_TAG_ETH2_VLAN_TAG_RANGE_UPPER(tag_rng_i_tag_upper);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG_RANGE_I_TAG(flow_index), &value));
        /* TAG1 */
        value = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG1_ETH2_VLAN_TAG1_MATCH(tag1_lower);
        value |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG1_ETH2_VLAN_TAG1_MASK(tag1_upper);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG1(flow_index), &value));
        /* TAG2_I_TAG */
        value = LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG2_I_TAG_ETH2_VLAN_TAG2_MATCH(tag2_i_tag_lower);
        value |= LAN80XX_F_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG2_I_TAG_ETH2_VLAN_TAG2_MASK(tag2_i_tag_upper);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_ETH2_FLOW_CFG_ETH2_VLAN_TAG2_I_TAG(flow_index), &value));


    }
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_ts_ip2_flow_conf(mepa_device_t *dev,
                                        const phy25g_ts_engine_t eng_id,
                                        const u16 flow_index,
                                        BOOL ingress,
                                        const phy25g_ts_next_comp_t next_comp,
                                        phy25g_ts_engine_flow_conf_t *const flow_conf,
                                        phy25g_ts_ip_conf_t *const ip_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    const phy25g_ts_ip_conf_t  *old_ip_conf;
    phy25g_ts_blk_id_t blk_id;
    mepa_rc rc;
    u32 temp, value;
    BOOL bool2, bool3;
    old_ip_conf = &flow_conf->flow_conf.ptp.ip2_opt;

    if ((ip_conf->comm_opt.ip_mode != LAN80XX_PHY_TS_IP_VER_4) && (ip_conf->comm_opt.ip_mode != LAN80XX_PHY_TS_IP_VER_6)) {
        return MEPA_RC_ERROR;
    }

    if (eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A ||
        eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2B) {
        return MEPA_RC_ERROR;

    } else {
        if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }
        if (old_ip_conf->comm_opt.ip_mode != ip_conf->comm_opt.ip_mode) {
            if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_4) {
                /* IP1 next protocol i.e. number of bytes in this header */
                MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR, &value));
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_COMPARATOR) |
                        LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_COMPARATOR(next_comp);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_PROTOCOL)
                        | LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_PROTOCOL(28);
                MEPA_RC(lan80xx_phy_ts_ip2_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_4))
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR, &value));
            } else if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_6) {
                /* IP1 next protocol i.e. number of bytes in this header */
                MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR, &value));
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_COMPARATOR) |
                        LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_COMPARATOR(next_comp);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_PROTOCOL)
                        | LAN80XX_F_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR_IP2_NXT_PROTOCOL(48);
                MEPA_RC(lan80xx_phy_ts_ip2_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_6));
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_NXT_PROTOCOL_IP2_NXT_COMPARATOR, &value));
            }


            bool2 = (ip_conf->flow_opt[flow_index].flow_en != old_ip_conf->flow_opt[flow_index].flow_en);
            bool3 = (ip_conf->flow_opt[flow_index].match_mode != old_ip_conf->flow_opt[flow_index].match_mode);
            if (bool2 || bool3) {
                MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA(flow_index), &value));
                if (bool2) {
                    if (ip_conf->flow_opt[flow_index].flow_en) {
                        value |=  LAN80XX_F_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA_IP2_FLOW_ENA;
                    } else {
                        value &=  ~LAN80XX_F_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA_IP2_FLOW_ENA;
                    }
                }
                if (bool3) {
                    temp = LAN80XX_F_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA_IP2_FLOW_MATCH_MODE(ip_conf->flow_opt[flow_index].match_mode);
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA_IP2_FLOW_MATCH_MODE) | temp;
                }
                value = value | LAN80XX_F_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA_IP2_CHANNEL_MASK(3);
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_ENA(flow_index), &value));
            }

            /* IP address */
            if (memcmp(&old_ip_conf->flow_opt[flow_index].ip_addr, &ip_conf->flow_opt[flow_index].ip_addr, sizeof(old_ip_conf->flow_opt[flow_index].ip_addr)) != 0) {
                if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_4) {
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv4.addr;
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MATCH_UPPER(flow_index), &value));
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv4.mask;
                    /* As suggested by HW team, mask set to '0' should log error message and further continue with configuration */
                    if (!ip_conf->flow_opt[flow_index].ip_addr.ipv4.mask) {
                        T_I(MEPA_TRACE_GRP_GEN, "1588 IP mask is set to zero");
                    }
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_UPPER(flow_index), &value));
                    /* clear the other mask register */
                    value = 0;
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_UPPER_MID(flow_index), &value));
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_LOWER_MID(flow_index), &value));
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_LOWER(flow_index), &value));
                }

                else {
                    /* Upper 32-bit of ipv6 address */
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[3];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MATCH_UPPER(flow_index), &value));
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[3];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_UPPER(flow_index), &value));
                    /* Upper mid 32-bit of ipv6 address */
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[2];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MATCH_UPPER_MID(flow_index), &value));
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[2];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_UPPER_MID(flow_index), &value));

                    /* Lower mid 32-bit of ipv6 address */
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[1];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MATCH_LOWER_MID(flow_index), &value));
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[1];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_LOWER_MID(flow_index), &value));
                    /* Lower 32-bit of ipv6 address */
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[0];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MATCH_LOWER(flow_index), &value));
                    value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[0];
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP2_FLOW_CFG_IP2_FLOW_MASK_LOWER(flow_index), &value));
                }
            }
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ts_ip1_flow_conf(mepa_device_t *dev,
                                        const phy25g_ts_engine_t eng_id,
                                        const u16 flow_index,
                                        BOOL ingress,
                                        const phy25g_ts_next_comp_t next_comp,
                                        BOOL double_ip,
                                        phy25g_ts_engine_flow_conf_t *const flow_conf,
                                        phy25g_ts_ip_conf_t *const ip_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    const phy25g_ts_ip_conf_t  *old_ip_conf;
    phy25g_ts_blk_id_t blk_id;
    mepa_rc rc;
    old_ip_conf = &flow_conf->flow_conf.ptp.ip1_opt;
    u32 temp, value;
    BOOL bool1, bool2, bool3;

    if ((ip_conf->comm_opt.ip_mode != LAN80XX_PHY_TS_IP_VER_4) && (ip_conf->comm_opt.ip_mode != LAN80XX_PHY_TS_IP_VER_6)) {
        return MEPA_RC_ERROR;
    }

    if (eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A ||
        eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2B) {
        return MEPA_RC_ERROR;

    } else {
        if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }

        if (double_ip) {
            if (old_ip_conf->comm_opt.ip_mode != ip_conf->comm_opt.ip_mode) {
                if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_4) {
                    /* IP1 next protocol i.e. number of bytes in this header */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR) |
                            LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR(next_comp);
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL)
                            | LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL(20);    /* default IP4 header length */
                    MEPA_RC(lan80xx_phy_ts_ip1_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_4, TRUE))
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                } else if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_6) {
                    /* IP1 next protocol i.e. number of bytes in this header */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR) |
                            LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR(next_comp);
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL)
                            | LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL(40);
                    MEPA_RC(lan80xx_phy_ts_ip1_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_6, TRUE));
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                }

            }

            /* Src and dest port number is not valid for IP1 i.e. IP over IP,
            so PROT_MATCH_2 no need to config, already set to default from
            def conf */

        } else {
            if (old_ip_conf->comm_opt.ip_mode != ip_conf->comm_opt.ip_mode) {
                if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_4) {
                    /* IP1 next protocol i.e. number of bytes in this header */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR) |
                            LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR(next_comp);
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL)
                            | LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL(28);
                    MEPA_RC(lan80xx_phy_ts_ip1_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_4, FALSE))
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                } else if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_6) {
                    /* IP1 next protocol i.e. number of bytes in this header */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR) |
                            LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_COMPARATOR(next_comp);
                    value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL)
                            | LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR_IP1_NXT_PROTOCOL(48);
                    MEPA_RC(lan80xx_phy_ts_ip1_different_offset_set(dev, data->port_no, blk_id, LAN80XX_PHY_TS_IP_VER_6, FALSE));
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
                }

                /* Src and dest port number */
                bool1 = (old_ip_conf->comm_opt.sport_val != ip_conf->comm_opt.sport_val);
                bool2 = (old_ip_conf->comm_opt.dport_val != ip_conf->comm_opt.dport_val);
                if (bool1 || bool2) {
                    value = ip_conf->comm_opt.sport_val << 16 | ip_conf->comm_opt.dport_val;
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MATCH_2_UPPER, &value));
                }
                bool1 = (old_ip_conf->comm_opt.sport_mask != ip_conf->comm_opt.sport_mask);
                bool2 = (old_ip_conf->comm_opt.dport_mask != ip_conf->comm_opt.dport_mask);

                if (bool1 || bool2) {
                    value = ip_conf->comm_opt.sport_mask << 16 | ip_conf->comm_opt.dport_mask;
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_PROT_MASK_2_UPPER, &value));
                }
                //please review below st in M10G.
                /* UDP port number offset from IP header: taken care in def conf */
            }

        }


        bool2 = (ip_conf->flow_opt[flow_index].flow_en != old_ip_conf->flow_opt[flow_index].flow_en);
        bool3 = (ip_conf->flow_opt[flow_index].match_mode != old_ip_conf->flow_opt[flow_index].match_mode);
        if (bool2 || bool3) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA(flow_index), &value));

            if (bool2) {
                if (ip_conf->flow_opt[flow_index].flow_en) {
                    value |=  LAN80XX_F_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA_IP1_FLOW_ENA;
                } else {
                    value &=  ~LAN80XX_F_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA_IP1_FLOW_ENA;
                }
            }

            if (bool3) {
                temp = LAN80XX_F_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA_IP1_FLOW_MATCH_MODE(ip_conf->flow_opt[flow_index].match_mode);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA_IP1_FLOW_MATCH_MODE) | temp;
            }
            value = value | LAN80XX_F_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA_IP1_CHANNEL_MASK(3);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA(flow_index), &value));
        }

        /* IP address */
        if (memcmp(&old_ip_conf->flow_opt[flow_index].ip_addr, &ip_conf->flow_opt[flow_index].ip_addr, sizeof(old_ip_conf->flow_opt[flow_index].ip_addr)) != 0) {
            if (ip_conf->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_4) {
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv4.addr;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MATCH_UPPER(flow_index), &value));
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv4.mask;
                /* As suggested by HW team, mask set to '0' should log error message and further continue with configuration */
                if (!ip_conf->flow_opt[flow_index].ip_addr.ipv4.mask) {
                    T_I(MEPA_TRACE_GRP_GEN, "1588 IP mask is set to zero");
                }
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_UPPER(flow_index), &value));
                /* clear the other mask register */
                value = 0;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_UPPER_MID(flow_index), &value));
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_LOWER_MID(flow_index), &value));
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_LOWER(flow_index), &value));
            } else {
                /* Upper 32-bit of ipv6 address */
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[3];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MATCH_UPPER(flow_index), &value));
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[3];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_UPPER(flow_index), &value));
                /* Upper mid 32-bit of ipv6 address */
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[2];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MATCH_UPPER_MID(flow_index), &value));
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[2];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_UPPER_MID(flow_index), &value));

                /* Lower mid 32-bit of ipv6 address */
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[1];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MATCH_LOWER_MID(flow_index), &value));
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[1];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_LOWER_MID(flow_index), &value));
                /* Lower 32-bit of ipv6 address */
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.addr[0];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MATCH_LOWER(flow_index), &value));
                value = ip_conf->flow_opt[flow_index].ip_addr.ipv6.mask[0];
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_MASK_LOWER(flow_index), &value));
            }

        }

    }

    return MEPA_RC_OK;
}



static mepa_rc lan80xx_phy_ts_engine_clear_priv(
    mepa_device_t *dev,
    const BOOL  ingress,
    const mepa_port_no_t       port_no,
    const phy25g_ts_engine_t eng_id)
{
    mepa_rc rc = MEPA_RC_OK;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_blk_id_t blk_id;
    u32 value, temp, i;
    //BOOL eng_mode, alt_eng_mode;

    if (ingress) {
        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
    } else {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
    }
    if (!eng_conf->eng_used) {
        return MEPA_RC_ERROR;

    }
    if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, FALSE, &blk_id)) != MEPA_RC_OK) {
        return MEPA_RC_ERROR;
    }
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID_0,
                                    LAN80XX_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE, &value));
    if (ingress) {
        //temp = LAN80XX_X_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(value);
        temp = LAN80XX_X_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(value);
    } else {
        //temp = LAN80XX_X_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(value);
        temp = LAN80XX_X_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(value);
    }
    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 || eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
        temp &= ~((u32)(0x01 << eng_id));  /* do the typecast to make lint happy! */
    } else {
        //#{TBD}
    }
    if (ingress) {
        temp = LAN80XX_F_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA(temp);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_PTP_PROC_ANALYZER_MODE_INGR_ENCAP_ENGINE_ENA) | temp;
    } else {
        temp = LAN80XX_F_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA(temp);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_PTP_PROC_ANALYZER_MODE_EGR_ENCAP_ENGINE_ENA) | temp;
    }
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID_0,
                                     LAN80XX_PTP_IP_1588_TOP_CFG_STAT_ANALYZER_MODE, &value));


    /* clear eth1 next comparator */
    /* PTP and OAM engine use different register naming */
    if (eng_id <= LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));
        temp = LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_NXT_COMPARATOR(0);
        value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_NXT_COMPARATOR) | temp;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));
    }
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_NXT_COMPARATOR, &value));
    /* clear IP1 UDP Checksum Configuration to default value */
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_UDP_CHKSUM_CFG, &value));

    /* disable each flow in ETH1 comparator */
    for (i = 0; i <= 8; i++) {
        value = 0;
        if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 ||
            eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE(i), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_IP1_FLOW_CFG_IP1_FLOW_ENA(i), &value));
        }

        else {
            //MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_ETH1_FLOW_CFG_ETH1_FLOW_ENABLE(i), &value));
        }
    }

    return MEPA_RC_OK;
}

/* PTP action is applicable to PTP engine which is handled by action_ptp field */
static mepa_rc lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(
    mepa_device_t *dev,
    const mepa_port_no_t              port_no,
    const phy25g_ts_blk_id_t          blk_id,
    const u8                          flow_index,
    const phy25g_ts_ptp_action_cmd_t  cmd,
    phy25g_ts_ptp_action_asym_t       asym)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value;
    u8  rx_ts_pos = 0;

    if (data->phy_ts_port_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {
        rx_ts_pos = 16; /* timestamp at reserved bytes */
    }
#if 0
    if (blk_id != LAN80XX_PHY_TS_ANA_BLK_ID_ING_2 && blk_id != LAN80XX_PHY_TS_ANA_BLK_ID_EGR_2) {
        /* by default no need to clear any field */
        value = 0;
        value |= LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_OAM_FRAME; /*Enable for PTP frame*/
        value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_RSVD_CHK_EN;/* Enabling check for the non zero of 4-byte reserved field */
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));

        switch (cmd) {
        case PTP_ACTION_CMD_NOP:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* NOP */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* SUB */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* CF bytes length */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_ADD:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(0); /* nothing to clear in Mode A */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB_ADD:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(rx_ts_pos); /* Ingress stored timestamp location */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* sub_add */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /* nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_OFFSET(rx_ts_pos); /* stored timestamp in reserved btes should be clear */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(4); /* 4 bytes stored timestamp */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_1588:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_1588 */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(34); /* origintimestamp offset */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(10); /* full timestamp */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_NS:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_ns */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            if (data->phy_ts_port_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(rx_ts_pos); /* reserved bytes offset */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(4); /* rsvd bytes length */
            } else {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no use */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0xE); /* Append at end */
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_NS_P2P:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_ns_p2p */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            if (data->phy_ts_port_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(rx_ts_pos); /* reserved bytes offset */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(4); /* rsvd bytes length */
            } else {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no use */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0xE); /* Append at end */
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SAVE_IN_TS_FIFO:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SAVE_LOCAL_TIME; /* save in FIFO */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_NOP); /* need to save in FIFO only, no write */
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no rewrite */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0); /* no rewrite */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_ADD_2:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));

            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(0); /* nothing to clear in Mode C */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB_2:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* SUB */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* CF bytes length */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;

#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
        case PTP_ACTION_CMD_DCE:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_NOP);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));

            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0x22); /* no rewrite */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0); /* no rewrite */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
        default:
            break;
        }
    } else
#endif
    {
        /* by default no need to clear any field */
        value = 0;
        value |= LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_OAM_FRAME; /*Enable for PTP frame*/
        value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_RSVD_CHK_EN;/* Enabling check for the non zero of 4-byte reserved field */
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));

        switch (cmd) {
        case PTP_ACTION_CMD_NOP:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* NOP */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* SUB */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* CF bytes length */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_ADD:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(0); /* nothing to clear in Mode A */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB_ADD:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(rx_ts_pos); /* Ingress stored timestamp location */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* sub_add */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /* nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_OFFSET(rx_ts_pos); /* stored timestamp in reserved btes should be clear */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(4); /* 4 bytes stored timestamp */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_1588:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_1588 */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(34); /* origintimestamp offset */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(10); /* full timestamp */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_NS:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_ns */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            if (data->phy_ts_port_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(rx_ts_pos); /* reserved bytes offset */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(4); /* rsvd bytes length */
            } else {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no use */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0xE); /* Append at end */
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_WRITE_NS_P2P:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* write_ns_p2p */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            if (data->phy_ts_port_conf.rx_ts_pos == LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP) {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(rx_ts_pos); /* reserved bytes offset */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(4); /* rsvd bytes length */
            } else {
                value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no use */
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0xE); /* Append at end */
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_SUB_2:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd); /* SUB */
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* CF bytes length */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
        case PTP_ACTION_CMD_ADD_2:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(cmd);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
            }
            if (data->phy_ts_port_conf.chk_ing_modified) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_STAT_UPDATE;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_MOD_FRAME_BYTE_OFFSET(6);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(8); /*  nothing to write */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(8); /* for CF */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            /* clear frame bytes */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL_PTP_ZERO_FIELD_BYTE_CNT(0); /* nothing to clear
                                                                                                  in Mode C */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
            break;

        case PTP_ACTION_CMD_SAVE_IN_TS_FIFO:

            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SAVE_LOCAL_TIME; /* save in FIFO */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);


            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_NOP); /* need to save in FIFO only, no write */
            }

            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));


#if 0
            value = 0x2400;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                             LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value));


            printf("Action saved to the PTP Action =%x, flowindex=%x\n", value, flow_index);
#endif

#if 1
            value = 0;

            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0); /* no rewrite */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0); /* no rewrite */

            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
#endif



#if 0
            value = 0x002300;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                             LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value))

            value = 0x214115;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
            printf("PTP write Fifo value %x\n", value);
            value = 0x220a;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            printf("PTP write Fifo value %x\n", value);
#endif
#if 0
            ioreg_blk *io_reg = (ioreg_blk *)malloc(sizeof(ioreg_blk));
            io_reg->mmd = 0xa;
            io_reg->is32 = 1;
            io_reg->addr = 0xab32;
            value = 0;
            value = 0 | 1 << 5 | 2 << 10 | 3 << 15 | 4 << 20;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);
            value = 0;
            value = 5 | 6 << 5 | 7 << 10 | 8 << 15 | 9 << 20;
            io_reg->addr = 0xab33;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);

            value = 0;
            value = 10 | 11 << 5 | 12 << 10 | 13 << 15 | 14 << 20;
            io_reg->addr = 0xab34;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);
            value = 0;
            value = 15 | 16 << 5 | 17 << 10 | 18 << 15 | 19 << 20;
            io_reg->addr = 0xab35;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);

            value = 0;
            value = 20 | 21 << 5 | 22 << 10 | 23 << 15 | 24 << 20;
            io_reg->addr = 0xab36;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);

            value = 0;
            value = 25 | 26 << 5 | 27 << 10 ;
            io_reg->addr = 0xab36;
            LAN80XX_CSR_WR(dev, port_no, io_reg, value);
#endif
            break;
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
        case PTP_ACTION_CMD_DCE:
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_TIME_STRG_FIELD_OFFSET(8);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_CORR_FIELD_OFFSET(8);
            if (asym == PTP_ACTION_ASYM_ADD) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_ADD_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else if (asym == PTP_ACTION_ASYM_SUB) {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_SUB_DELAY_ASYM_ENA;
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_WRITE_1588); /* To write CF, cmd NOP not work */
            } else {
                value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_PTP_COMMAND(PTP_ACTION_CMD_NOP);
            }
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));

            /* action_2 setting */
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_OFFSET(0x22); /* no rewrite */
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_ACTION_2_PTP_REWRITE_BYTES(0); /* no rewrite */
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
            break;
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
        default:
            break;
        }
    }

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_ts_engine_ptp_action_flow_add_priv (mepa_device_t *dev,
                                                           mepa_bool_t    ingress,
                                                           const mepa_port_no_t                port_no,
                                                           const phy25g_ts_engine_t            eng_id,
                                                           const phy25g_ts_ptp_msg_type_t      msg_type,
                                                           const u16                           flow_index,
                                                           const phy25g_ts_ptp_engine_action_t *const action_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value;
    phy25g_ts_blk_id_t          blk_id = 0;
    mepa_rc rc = MEPA_RC_OK;
    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 || eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
        /* flow enable */
        value = LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_FLOW_ENA;
        if ((rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id)) != MEPA_RC_OK) {
            return MEPA_RC_ERROR;
        }
        value |= LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_CHANNEL_MASK(3);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));

        /* domain config */
        if (action_conf->ptp_conf.range_en) {
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_ENA;
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_OFFSET(4);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_UPPER(action_conf->ptp_conf.domain.range.upper);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_LOWER(action_conf->ptp_conf.domain.range.lower);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            /* clear mask related to domain */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        } else {
            /* disable domain range */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            value &= ~LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_ENA;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            /* set mask */
            /* PTP_FLOW_MATCH_UPPER: msg type to msg length with msg type in MS bytes
               PTP_FLOW_MATCH_LOWER: domain number which will be MB byte */
            value = action_conf->ptp_conf.domain.value.mask << 24;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            value = action_conf->ptp_conf.domain.value.val << 24;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        }

        if (data->phy_ts_port_conf.chk_ing_modified && !ingress) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            //value |= 0x8000;
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            //MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            value |= 0xf000;
            //MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
        }

        /* set message type in flow match lower */
        /* PTP_FLOW_MATCH_UPPER: msg type to msg length with msg type in MS bytes
           PTP_FLOW_MATCH_LOWER: domain number which will be MB byte */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        value = ~0x0F000000;
        value |= (msg_type << 24);
        //value = 0xffffffff;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
        value = 0x0F000000;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
    } else {
        /* flow enable */
        value = LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_FLOW_ENA;
        value |= LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_CHANNEL_MASK(3);
        if (eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
            //value |= LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK(0x01);
        } else {
            //value |= LAN80XX_F_ANA_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK(0x02);
        }
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));

        /* domain config */
        if (action_conf->ptp_conf.range_en) {
            value = LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_ENA;
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_OFFSET(4);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_UPPER(action_conf->ptp_conf.domain.range.upper);
            value |= LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_LOWER(action_conf->ptp_conf.domain.range.lower);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            /* clear mask related to domain */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        } else {
            /* disable domain range */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            value &= ~LAN80XX_F_ANA_PTP_FLOW_PTP_DOMAIN_RANGE_PTP_DOMAIN_RANGE_ENA;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
            /* set mask */
            /* PTP_FLOW_MATCH_UPPER: msg type to msg length with msg type in MS bytes
               PTP_FLOW_MATCH_LOWER: domain number which will be MB byte */
            value = action_conf->ptp_conf.domain.value.mask << 24;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            value = action_conf->ptp_conf.domain.value.val << 24;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        }

        if (data->phy_ts_port_conf.chk_ing_modified && !ingress) {
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            value |= 0x8000;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
            value |= 0xf000;
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
        }

        /* set message type in flow match lower */
        /* PTP_FLOW_MATCH_UPPER: msg type to msg length with msg type in MS bytes
           PTP_FLOW_MATCH_LOWER: domain number which will be MB byte */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        value &= ~0x0F000000;
        value |= (msg_type << 24);
        //value = 0xffffffff;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));

        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
        value = 0x0F000000;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
    }
    switch (msg_type) {
    case PTP_MSG_TYPE_SYNC:
        if (ingress) {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved), add(PathDelay+Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS_P2P,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField); add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField); add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_ADD));

                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField); add(PathDelay + Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved), add(PathDelay+Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS_P2P,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField); add(PathDelay + Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_ADD));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /*LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        } else {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (action_conf->cf_update == FALSE) {
                    /* write(TX_timestamp, originTimestamp) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_1588,
                                                                            PTP_ACTION_ASYM_NONE));
                } else {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (action_conf->cf_update == FALSE) {
                    /* write(TX_timestamp, originTimestamp) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_1588,
                                                                            PTP_ACTION_ASYM_NONE));
                } else {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* save(TX_timestamp, TXFifo) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* save(TX_timestamp, TXFifo) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* Subtract_add(TX_timestamp, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp, TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp, TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /*LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */

            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        }
        break;
    case PTP_MSG_TYPE_DELAY_REQ:
        if (ingress) {
            if (action_conf->delay_req_recieve_timestamp &&
                (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP ||
                 action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP)) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_1588,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* write(RX_timestamp,  Reserved) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* write(RX_timestamp,  Reserved) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                } else  if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }

            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        } else {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.one_step_txfifo == TRUE) {
                    /* save(TX_timestamp, TXFiFo);sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_SUB));
                } else {
                    /* Subtract_add(TX_timestamp - Asymmetry, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                /* save(TX_timestamp, TXFiFo) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField); sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* Subtract_add(TX_timestamp - Asymmetry, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* add(TX_timestamp, correctionField); sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_SUB));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp, TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /*LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        }
        break;
    case PTP_MSG_TYPE_PDELAY_REQ:
        if (ingress) {
            //if (action_conf->delay_req_recieve_timestamp &&
            //    (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP ||
            //     action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP)) {
            //    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
            //                                                         blk_id, flow_index,
            //                                                         PTP_ACTION_CMD_WRITE_1588,
            //                                                         PTP_ACTION_ASYM_NONE));
            //} else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));

                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        } else {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.one_step_txfifo == TRUE) {
                    /* save(TX_timestamp, TXFiFo);sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_SUB));
                } else {
                    /* Subtract_add(TX_timestamp - Asymmetry, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* save(TX_timestamp,  TXFiFo) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField); sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* Subtract_add(TX_timestamp - Asymmetry, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* add(TX_timestamp, correctionField); sub(Asymmetry, correctionField) */

                    /* add(TX_timestamp, correctionField); sub(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_SUB));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.one_step_txfifo == TRUE) {
                    if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                        (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                        (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                        /* save(TX_timestamp, TXFiFo);sub(Asymmetry, correctionField) */
                        MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                                blk_id, flow_index,
                                                                                PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                                PTP_ACTION_ASYM_SUB));
                    }
                } else {
                    /* Subtract_add(TX_timestamp - Asymmetry, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_SUB));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp, TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp,  TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        }
        break;
    case PTP_MSG_TYPE_PDELAY_RESP:
        if (ingress) {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_WRITE_NS,
                                                                        PTP_ACTION_ASYM_ADD));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* sub(RX_timestamp, correctionField); add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_ADD));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* sub(RX_timestamp, correctionField); add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_2,
                                                                            PTP_ACTION_ASYM_ADD));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS, PTP_ACTION_ASYM_ADD));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* write(RX_timestamp,  Reserved), add(Asymmetry, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_WRITE_NS,
                                                                            PTP_ACTION_ASYM_ADD));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif  /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        } else {
            if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
                action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* Subtract_add(TX_timestamp, Reserved, correctionField) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SUB_ADD,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                /* save(TX_timestamp,  TXFiFo) */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,

                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                        PTP_ACTION_ASYM_NONE));
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* Subtract_add(TX_timestamp, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) {
                    /* Subtract_add(TX_timestamp, Reserved, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SUB_ADD,
                                                                            PTP_ACTION_ASYM_NONE));
                } else if (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C) {
                    /* add(TX_timestamp, correctionField) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_ADD_2,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp, TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
            } else if (action_conf->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                       action_conf->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
                if ((data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_A) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_B) ||
                    (data->phy_ts_port_conf.tc_op_mode == LAN80XX_PHY_TS_TC_OP_MODE_C)) {
                    /* save(TX_timestamp,  TXFiFo) */
                    MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                            blk_id, flow_index,
                                                                            PTP_ACTION_CMD_SAVE_IN_TS_FIFO,
                                                                            PTP_ACTION_ASYM_NONE));
                }
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
            } else if (action_conf->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_DCE,
                                                                        PTP_ACTION_ASYM_ADD));
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
            } else {
                /* NOP */
                MEPA_RC(lan80xx_phy_ts_engine_ptp_action_flow_conf_priv(dev, port_no,
                                                                        blk_id, flow_index,
                                                                        PTP_ACTION_CMD_NOP,
                                                                        PTP_ACTION_ASYM_NONE));
            }
        }
        break;
    default:
        break;
    }
    return MEPA_RC_OK;
}

/* PTP action is only on PTP engine */
static mepa_rc lan80xx_phy_ts_engine_ptp_action_flow_delete_priv(
    mepa_device_t *dev,
    const mepa_port_no_t       port_no,
    const phy25g_ts_blk_id_t blk_id,
    const phy25g_ts_engine_t eng_id,
    const u8                   flow_index)
{
    u32 value;

    if (eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_0 || eng_id == LAN80XX_PHY_TS_PTP_ENGINE_ID_1) {
        /* flow disable */
        value = 0;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));
        /* clear other action registers */
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
    }
#if 0
    else {
        /* For OAM engine, action may be shared, check before disable the flow */
        LAN80XX_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));
        temp = LAN80XX_X_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK(value);
        if (eng_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
            /* Gr 2B is set, don't delete the entry, just remove Gr 2A */
            if (temp & 0x02) {
                temp = LAN80XX_F_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK(0x02);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK) | temp;
                LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));
                return LAN80XX_RC_OK;
            }
        } else {
            /* Gr 2A is set, don't delete the entry, just remove Gr 2B */
            if (temp & 0x01) {
                temp = LAN80XX_F_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK(0x01);
                value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA_PTP_NXT_PROT_GRP_MASK) | temp;
                LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));
                return LAN80XX_RC_OK;
            }
        }

        /* that means flow is not shared, so need to be removed */
        /* flow disable */
        value = 0;
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_ENA(flow_index), &value));
        /* clear other action registers */
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_DOMAIN_RANGE(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_MASK_UPPER(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_MASK_LOWER(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_MATCH_UPPER(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_FLOW_MATCH_LOWER(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_ACTION(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_ACTION_2(flow_index), &value));
        LAN80XX_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id, LAN80XX_ANA_OAM_PTP_FLOW_PTP_ZERO_FIELD_CTL(flow_index), &value));
    }
#endif
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_ts_engine_action_set_priv(
    mepa_device_t                   *dev,
    BOOL  ingress,
    mepa_port_no_t                    port_no,
    phy25g_ts_engine_t              eng_id,
    phy25g_ts_eng_conf_t            *eng_conf,
    const phy25g_ts_engine_action_t *const new_action_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    // phy25g_ts_eng_conf_t *eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
    phy25g_ts_ptp_engine_action_t *action = &eng_conf->action_conf.action.ptp_conf;
    phy25g_ts_blk_id_t blk_id;
    u32 action_index = 0;
    mepa_rc rc = MEPA_RC_OK;

    if (!action->enable) {
        rc = lan80xx_phy_ts_ana_blk_id_get(eng_id, ingress, &blk_id);

        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Invalid engine id (%d), ingress %d", eng_id, ingress);
            return MEPA_RC_ERROR;
        }

        for (int i = 0; i < LAN80XX_PTP_MAX_FLOW; i++) {
            MEPA_RC(LAN80XX_RC_COLD(lan80xx_phy_ts_engine_ptp_action_flow_delete_priv(dev, port_no, blk_id, eng_id, i)));
        }
        return MEPA_RC_OK;
    }
    if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
        action->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
        //implementation of BC1STEP sync and dreq.
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_DELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = 2;
    } else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC1STEP &&
               action->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
    } else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
               action->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_DELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
    }  else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_BC2STEP &&
                action->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
    } else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
               action->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0,  &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_DELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_3, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_3] = action_index + 1;
    } else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC1STEP &&
               action->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
    } else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
               action->delaym_type == MEPA_TS_PTP_DELAYM_E2E) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_DELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_3, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_3] = action_index + 1;
    }  else if (action->clk_mode == MEPA_TS_PTP_CLOCK_MODE_TC2STEP &&
                action->delaym_type == MEPA_TS_PTP_DELAYM_P2P) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
#ifdef LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE
    } else if (action->clk_mode == LAN80XX_PHY_TS_PTP_DELAY_COMP_ENGINE) {
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_SYNC, LAN80XX_PTP_FLOW_INDEX_0, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_0] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_DELAY_REQ, LAN80XX_PTP_FLOW_INDEX_1, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_1] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_REQ, LAN80XX_PTP_FLOW_INDEX_2, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_2] = action_index + 1;
        MEPA_RC(LAN80XX_RC_COLD(lan80xx_ts_engine_ptp_action_flow_add_priv(dev, ingress,
                                                                           port_no, eng_id, PTP_MSG_TYPE_PDELAY_RESP, LAN80XX_PTP_FLOW_INDEX_3, &eng_conf->action_conf.action.ptp_conf)));
        eng_conf->action_flow_map[LAN80XX_PTP_FLOW_INDEX_3] = action_index + 1;
#endif /* LAN80XX_FEATURE_PTP_DELAY_COMP_ENGINE */
    }


    return MEPA_RC_OK;
}

mepa_rc lan80xx_ts_egress_engine_clear(mepa_device_t *dev,
                                       const mepa_port_no_t port_no,
                                       const phy25g_ts_engine_t eng_id)
{

    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf = NULL;
    phy25g_ts_engine_flow_conf_t *flow_conf = NULL;
    //phy25g_ts_engine_action_t *action_conf = NULL;
    phy25g_ts_blk_id_t blk_id;
#if 0
    if (!LAN80XX_PHY_TS_ENGINE_ID_VALID(eng_id)) {
        LAN80XX_E("invalid engine ID");
        return LAN80XX_RC_ERROR;
    }
#endif
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];

        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        flow_conf = &eng_conf->flow_conf;
        //action_conf = &eng_conf->action_conf;

        if (lan80xx_phy_ts_ana_blk_id_get(eng_id, FALSE, &blk_id) != MEPA_RC_OK) {
            rc = MEPA_RC_ERROR;
            break;
        }

        //LAN80XX_PHY_TS_SPI_PAUSE_COLD(port_no);
        rc = lan80xx_phy_ts_engine_clear_priv(dev, FALSE, port_no, eng_id);
        /* clear the engine config */
        memset(flow_conf, 0, sizeof(phy25g_ts_engine_flow_conf_t));
        eng_conf->eng_used = FALSE;
        //eng_conf->flow_st_index = 0;
        //eng_conf->flow_end_index = 0;
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_ts_egress_engine_conf_set(mepa_device_t *dev,
                                          const phy25g_ts_engine_t eng_id,
                                          const u16 flow_index,
                                          phy25g_ts_engine_flow_conf_t *const flow_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_eth_conf_t *eth_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
        eth_conf = &eng_conf->flow_conf.flow_conf.ptp.eth1_opt;
        if (eth_conf->comm_opt.pbb_en) {
            if (eth_conf->flow_opt[flow_index].flow_en == FALSE) {
                break;
            }
            if (eth_conf->flow_opt[flow_index].num_tag == 0) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: PBB requires at least I-tag", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }

            if (eth_conf->flow_opt[flow_index].tag_range_mode != LAN80XX_PHY_TS_TAG_RANGE_NONE) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: Tag range not supported when PBB enabled", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }
            if (eth_conf->flow_opt[flow_index].inner_tag_type != LAN80XX_PHY_TS_TAG_TYPE_I ||
                (eth_conf->flow_opt[flow_index].num_tag == 2 &&
                 eth_conf->flow_opt[flow_index].outer_tag_type != LAN80XX_PHY_TS_TAG_TYPE_B)) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: Wrong tag type for PBB", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }

        }
        switch (eng_conf->encap_type) {
        case LAN80XX_PHY_TS_ENCAP_ETH_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            /*Configure IP flow */
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            /*Configure IP flow */
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP2, TRUE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            lan80xx_ts_ip2_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, eng_conf);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;


        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, eng_conf);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, eng_conf);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, FALSE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;


        default:
            break;
        }

    } while (0);
    MEPA_EXIT(dev);
    return MEPA_RC_OK;


}

mepa_rc lan80xx_ts_egress_engine_action_set(mepa_device_t *dev, mepa_port_no_t port_no,
                                            phy25g_ts_engine_t eng_id, const phy25g_ts_engine_action_t *const action_conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf;
#if 0
    LAN80XX_PHY_TS_ASSERT(action_conf == NULL);
    if (!LAN80XX_PHY_TS_ENGINE_ID_VALID(eng_id)) {
        return LAN80XX_RC_ERROR;
    }
#endif
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        //LAN80XX_PHY_TS_SPI_PAUSE_COLD(port_no);
        rc = lan80xx_phy_ts_engine_action_set_priv(dev, FALSE, port_no,
                                                   eng_id, eng_conf, action_conf);
        //LAN80XX_PHY_TS_SPI_UNPAUSE_COLD(port_no);
        /* save the action config */
#if 0
        if (rc == MEPA_RC_OK) {
            //memcpy(&eng_conf->action_conf, action_conf, sizeof(phy25g_ts_engine_action_t));
        }
#endif
    } while (0);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_ts_ingress_engine_conf_set(mepa_device_t *dev,
                                           const phy25g_ts_engine_t eng_id,
                                           const u16 flow_index,
                                           phy25g_ts_engine_flow_conf_t *const flow_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_eth_conf_t *eth_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
        eth_conf = &eng_conf->flow_conf.flow_conf.ptp.eth1_opt;
        if (eth_conf->comm_opt.pbb_en) {
            if (eth_conf->flow_opt[flow_index].flow_en == FALSE) {
                break;
            }
            if (eth_conf->flow_opt[flow_index].num_tag == 0) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: PBB requires at least I-tag", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }
            if (eth_conf->flow_opt[flow_index].tag_range_mode != LAN80XX_PHY_TS_TAG_RANGE_NONE) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: Tag range not supported when PBB enabled", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }
            /* For single tag, inner_tag is always I-tag, for double tag, inner is
              I-tag, outer is B-tag always */
            if (eth_conf->flow_opt[flow_index].inner_tag_type != LAN80XX_PHY_TS_TAG_TYPE_I ||
                (eth_conf->flow_opt[flow_index].num_tag == 2 &&
                 eth_conf->flow_opt[flow_index].outer_tag_type != LAN80XX_PHY_TS_TAG_TYPE_B)) {
                T_E(MEPA_TRACE_GRP_GEN, "Port: %u engine: %u:: Wrong tag type for PBB", (u32)data->port_no, (u32)eng_id);
                return MEPA_RC_ERROR;
            }

        }
        switch (eng_conf->encap_type) {
        case LAN80XX_PHY_TS_ENCAP_ETH_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            break;
        case LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index,  TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            /*Configure IP flow */
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP2, TRUE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            lan80xx_ts_ip2_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index,  TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP:
            /*configure eth flow */
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, eng_conf);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index,  TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;


        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP:
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, eng_conf);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            break;

        case LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP:
            lan80xx_ts_eth1_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_MPLS, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth1_opt);
            lan80xx_ts_mpls_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_ETH2, flow_conf, eng_conf);
            lan80xx_ts_eth2_flow_conf(dev, eng_id, flow_index, TRUE, LAN80XX_PHY_TS_NEXT_COMP_IP1, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.eth2_opt);
            lan80xx_ts_ip1_flow_conf(dev, eng_id, flow_index,  TRUE, LAN80XX_PHY_TS_NEXT_COMP_PTP_OAM, FALSE, flow_conf, &eng_conf->flow_conf.flow_conf.ptp.ip1_opt);
            break;



        default:
            break;
        }


    } while (0);

    MEPA_EXIT(dev);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_ts_ingress_engine_action_set(mepa_device_t *dev, mepa_port_no_t port_no,
                                             phy25g_ts_engine_t eng_id, const phy25g_ts_engine_action_t *const action_conf)
{
    mepa_rc rc;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_eng_conf_t *eng_conf;
    MEPA_ASSERT(action_conf == NULL);
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        //LAN80XX_PHY_TS_SPI_PAUSE_COLD(port_no);
        rc = lan80xx_phy_ts_engine_action_set_priv(dev, TRUE, port_no,
                                                   eng_id, eng_conf, action_conf);
        //LAN80XX_PHY_TS_SPI_UNPAUSE_COLD(port_no);
        /* save the action config */
        if (rc == MEPA_RC_OK) {
            //memcpy(&eng_conf->action_conf, action_conf, sizeof(phy25g_ts_engine_action_t));
        }
    } while (0);
    MEPA_EXIT(dev);

    return rc;
}

static void lan80xx_get_clk_from_action(mepa_device_t *dev,
                                        const phy25g_ts_ptp_engine_action_t *action,
                                        mepa_ts_ptp_clock_conf_t *const clk_conf)
{
    mepa_ts_match_uint8_t sdoid = {0};
    clk_conf->enable = action->enable ? TRUE : FALSE;
    clk_conf->clk_mode = action->clk_mode;
    clk_conf->delaym_type = action->delaym_type;
    clk_conf->ptp_class_conf.version.lower = 2; // unused
    clk_conf->ptp_class_conf.version.upper = 2; // unused
    clk_conf->ptp_class_conf.minor_version.lower = 0; // unused
    clk_conf->ptp_class_conf.minor_version.upper = 0; // unused
    clk_conf->ptp_class_conf.domain.mode = action->ptp_conf.range_en ? MEPA_TS_MATCH_MODE_RANGE : MEPA_TS_MATCH_MODE_VALUE;
    if (clk_conf->ptp_class_conf.domain.mode == MEPA_TS_MATCH_MODE_RANGE) {
        clk_conf->ptp_class_conf.domain.match.range.upper = action->ptp_conf.domain.range.upper;
        clk_conf->ptp_class_conf.domain.match.range.lower = action->ptp_conf.domain.range.lower;
    } else {
        clk_conf->ptp_class_conf.domain.match.value.val = action->ptp_conf.domain.value.val;
        clk_conf->ptp_class_conf.domain.match.value.mask = action->ptp_conf.domain.value.mask;
    }
    clk_conf->ptp_class_conf.sdoid = sdoid; // unused
}

mepa_rc lan80xx_ts_egress_engine_action_get(mepa_device_t  *dev,
                                            const mepa_port_no_t            port_no,
                                            const phy25g_ts_engine_t      eng_id,
                                            phy25g_ts_engine_action_t *const action_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    phy25g_ts_eng_conf_t *eng_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        memcpy(action_conf, &eng_conf->action_conf, sizeof(phy25g_ts_engine_action_t));
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_ts_ingress_engine_action_get(mepa_device_t  *dev,
                                             const mepa_port_no_t            port_no,
                                             const phy25g_ts_engine_t      eng_id,
                                             phy25g_ts_engine_action_t *const action_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    phy25g_ts_eng_conf_t *eng_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        memcpy(action_conf, &eng_conf->action_conf, sizeof(phy25g_ts_engine_action_t));
    } while (0);
    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_ts_tx_clock_conf_get_priv(mepa_device_t *dev,
                                          u16 clock_id, mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_ts_engine_action_t action_conf;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_engine_t eng_id = 0;
    mepa_rc rc = MEPA_RC_OK;
    eng_id = clock_id;
    eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
    // Check whether engine is used.
    if (!eng_conf->eng_used) {
        T_E(MEPA_TRACE_GRP_TS, "No action configured");
        return MEPA_RC_ERROR;
    } else {
        rc = lan80xx_ts_egress_engine_action_get(dev, data->port_no, eng_id, &action_conf);
        if (rc == MEPA_RC_OK) {
            lan80xx_get_clk_from_action(dev, &action_conf.action.ptp_conf, ptpclock_conf);
        } else {
            rc = MEPA_RC_ERR_TS_ACTION_GET_FAIL;
        }
    }
    //dump_ptp_action(&action_conf);
    //dump_chip_ptp_flow(dev, FALSE);
    return rc;
}

mepa_rc lan80xx_ts_rx_clock_conf_get_priv(mepa_device_t *dev,
                                          u16 clock_id, mepa_ts_ptp_clock_conf_t *ptpclock_conf)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *) dev->data;
    phy25g_ts_engine_action_t action_conf;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_engine_t eng_id = 0;
    mepa_rc rc = MEPA_RC_OK;
    eng_id = clock_id;
    eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
    // Check whether engine is used.
    if (!eng_conf->eng_used) {
        T_E(MEPA_TRACE_GRP_TS, "No action configured");
        return MEPA_RC_ERROR;
    } else {
        rc = lan80xx_ts_ingress_engine_action_get(dev, data->port_no, eng_id, &action_conf);
        if (rc == MEPA_RC_OK) {
            lan80xx_get_clk_from_action(dev, &action_conf.action.ptp_conf, ptpclock_conf);
        } else {
            rc = MEPA_RC_ERR_TS_ACTION_GET_FAIL;
        }
    }
    //dump_ptp_action(&action_conf);
    //dump_chip_ptp_flow(dev, FALSE);
    return rc;
}

mepa_rc lan80xx_ts_ingress_engine_conf_get(mepa_device_t  *dev,
                                           const mepa_port_no_t            port_no,
                                           const phy25g_ts_engine_t      eng_id,
                                           phy25g_ts_engine_flow_conf_t  *const flow_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    phy25g_ts_eng_conf_t *eng_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        memcpy(flow_conf, &eng_conf->flow_conf, sizeof(phy25g_ts_engine_flow_conf_t));
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_ts_egress_engine_conf_get(mepa_device_t  *dev,
                                          const mepa_port_no_t            port_no,
                                          const phy25g_ts_engine_t      eng_id,
                                          phy25g_ts_engine_flow_conf_t  *const flow_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc                rc = MEPA_RC_OK;
    phy25g_ts_eng_conf_t *eng_conf;
    MEPA_ENTER(dev);
    do {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
        if (!eng_conf->eng_used) {
            rc = MEPA_RC_ERROR;
            break;
        }
        memcpy(flow_conf, &eng_conf->flow_conf, sizeof(phy25g_ts_engine_flow_conf_t));
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

static mepa_ts_mac_match_mode_t lan80xx_get_mepa_eth_match_mode(u8 match_mode)
{
    mepa_ts_mac_match_mode_t ret = MEPA_TS_ETH_ADDR_MATCH_ANY;
    if ((match_mode & LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST) &&
        (match_mode & LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST)) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY;
    } else if (match_mode & LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY_UNICAST;
    } else if (match_mode & LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST) {
        ret = MEPA_TS_ETH_ADDR_MATCH_ANY_MULTICAST;
    } else if (match_mode & LAN80XX_PHY_TS_ETH_ADDR_MATCH_48BIT) {
        ret = MEPA_TS_ETH_ADDR_MATCH_48BIT;
    }
    return ret;
}

static mepa_ts_mac_match_select_t lan80xx_get_mepa_eth_match_select(u8 match_sel)
{
    mepa_ts_mac_match_select_t ret = MEPA_TS_ETH_MATCH_NONE;
    if (match_sel == LAN80XX_PHY_TS_ETH_MATCH_DEST_ADDR) {
        ret = MEPA_TS_ETH_MATCH_DEST_ADDR;
    } else if (match_sel == LAN80XX_PHY_TS_ETH_MATCH_SRC_ADDR) {
        ret = MEPA_TS_ETH_MATCH_SRC_ADDR;
    } else if (match_sel == LAN80XX_PHY_TS_ETH_MATCH_SRC_OR_DEST) {
        ret = MEPA_TS_ETH_MATCH_SRC_OR_DEST;
    }
    return ret;
}

static mepa_ts_ip_match_select_t lan80xx_get_mepa_ip_match_mode(u8 match)
{
    mepa_ts_ip_match_select_t ret = MEPA_TS_IP_MATCH_NONE;
    if (match == LAN80XX_PHY_TS_IP_MATCH_SRC) {
        ret = MEPA_TS_IP_MATCH_SRC;
    } else if (match == LAN80XX_PHY_TS_IP_MATCH_DEST) {
        ret = MEPA_TS_IP_MATCH_DEST;
    } else if (match == LAN80XX_PHY_TS_IP_MATCH_SRC_OR_DEST) {
        ret = MEPA_TS_IP_MATCH_SRC_OR_DEST;
    }
    return ret;
}

static void lan80xx_get_eth_class_from_flow(const phy25g_ts_eth_conf_t *flow, u8 flow_id,
                                            mepa_ts_classifier_eth_t *const cls_eth)
{
    cls_eth->mac_match_mode = lan80xx_get_mepa_eth_match_mode(flow->flow_opt[flow_id].addr_match_mode);
    cls_eth->mac_match_select = lan80xx_get_mepa_eth_match_select(flow->flow_opt[flow_id].addr_match_select);
    memcpy(cls_eth->mac_addr, flow->flow_opt[flow_id].mac_addr, sizeof(cls_eth->mac_addr));
    cls_eth->vlan_check = flow->flow_opt[flow_id].vlan_check;
    cls_eth->vlan_conf.pbb_en = flow->comm_opt.pbb_en; //common option
    cls_eth->vlan_conf.tpid = flow->comm_opt.tpid;  //common option
    cls_eth->vlan_conf.etype = flow->comm_opt.etype; //common option
    cls_eth->vlan_conf.num_tag = flow->flow_opt[flow_id].num_tag;
    cls_eth->vlan_conf.outer_tag.mode = MEPA_TS_MATCH_MODE_VALUE;
    cls_eth->vlan_conf.inner_tag.mode = MEPA_TS_MATCH_MODE_VALUE;
    if (flow->flow_opt[flow_id].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_OUTER) {
        cls_eth->vlan_conf.outer_tag.mode = MEPA_TS_MATCH_MODE_RANGE;
        cls_eth->vlan_conf.outer_tag.match.range.lower = flow->flow_opt[flow_id].outer_tag.range.lower;
        cls_eth->vlan_conf.outer_tag.match.range.upper = flow->flow_opt[flow_id].outer_tag.range.upper;
    } else {
        cls_eth->vlan_conf.outer_tag.match.value.val  = flow->flow_opt[flow_id].outer_tag.value.val;
        cls_eth->vlan_conf.outer_tag.match.value.mask = flow->flow_opt[flow_id].outer_tag.value.mask;
    }
    if (flow->flow_opt[flow_id].tag_range_mode == LAN80XX_PHY_TS_TAG_RANGE_INNER) {
        cls_eth->vlan_conf.inner_tag.mode = MEPA_TS_MATCH_MODE_RANGE;
        cls_eth->vlan_conf.inner_tag.match.range.lower = flow->flow_opt[flow_id].inner_tag.range.lower;
        cls_eth->vlan_conf.inner_tag.match.range.upper = flow->flow_opt[flow_id].inner_tag.range.upper;
    } else {
        cls_eth->vlan_conf.inner_tag.match.value.val  = flow->flow_opt[flow_id].inner_tag.value.val;
        cls_eth->vlan_conf.inner_tag.match.value.mask = flow->flow_opt[flow_id].inner_tag.value.mask;
    }
}

static void lan80xx_get_ip_class_from_flow(const phy25g_ts_ip_conf_t *ip, u8 flow_id,
                                           mepa_ts_classifier_ip_t *const cls_ip)
{
    cls_ip->ip_ver = ip->comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_6 ? MEPA_TS_IP_VER_6 : MEPA_TS_IP_VER_4;
    cls_ip->ip_match_mode = lan80xx_get_mepa_ip_match_mode(ip->flow_opt[flow_id].match_mode);
    if (cls_ip->ip_ver == MEPA_TS_IP_VER_6) {
        memcpy(cls_ip->ip_addr.ipv6.addr, ip->flow_opt[flow_id].ip_addr.ipv6.addr, sizeof(cls_ip->ip_addr.ipv6.addr));
        memcpy(cls_ip->ip_addr.ipv6.mask, ip->flow_opt[flow_id].ip_addr.ipv6.mask, sizeof(cls_ip->ip_addr.ipv6.mask));
    } else {
        cls_ip->ip_addr.ipv4.addr = ip->flow_opt[flow_id].ip_addr.ipv4.addr;
        cls_ip->ip_addr.ipv4.mask = ip->flow_opt[flow_id].ip_addr.ipv4.mask;
    }

    cls_ip->udp_sport_en = ip->comm_opt.sport_mask ? TRUE : FALSE;
    cls_ip->udp_dport_en = ip->comm_opt.dport_mask ? TRUE : FALSE;
    cls_ip->udp_sport = ip->comm_opt.sport_val;
    cls_ip->udp_dport = ip->comm_opt.dport_val;
}

static void lan80xx_get_class_from_flow(const phy25g_ts_engine_flow_conf_t *flow, u8 flow_id,
                                        mepa_ts_classifier_t *const cls_conf)
{
    lan80xx_get_eth_class_from_flow(&flow->flow_conf.ptp.eth1_opt, flow_id, &cls_conf->eth_class_conf);
    lan80xx_get_ip_class_from_flow(&flow->flow_conf.ptp.ip1_opt, flow_id, &cls_conf->ip_class_conf);
}

static mepa_rc lan80xx_rx_classifier_conf_get_priv( mepa_device_t *dev, u16 in_flow,
                                                    mepa_ts_classifier_t *const out_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_engine_t eng_id;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_engine_flow_conf_t flow_conf;
    u16 flow_id = 0;
    mepa_rc rc;
    rc = lan80xx_get_eng_flow_info(in_flow, &eng_id, &flow_id);

    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_TS, "\nInvalid PTP Engine Selected on port : %d", data->port_no);
        return MEPA_RC_ERROR;
    }

    eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
    if (!eng_conf->eng_used) {
        T_E(MEPA_TRACE_GRP_TS, "Engine not used")
        return MEPA_RC_ERROR;
    } else {
        // Get conf from engine
        rc = lan80xx_ts_ingress_engine_conf_get(dev, data->port_no, eng_id, &flow_conf);
        if (rc != MEPA_RC_OK) {
            return MEPA_RC_ERR_TS_FLOW_GET_FAIL;
        }
        out_conf->pkt_encap_type = (eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_PTP) ? MEPA_TS_ENCAP_ETH_PTP :
                                   (eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP) ? MEPA_TS_ENCAP_ETH_IP_PTP :
                                   MEPA_TS_ENCAP_NONE;
        out_conf->enable = TRUE;
        lan80xx_get_class_from_flow(&flow_conf, flow_id, out_conf);
        out_conf->clock_id = eng_id; // 1 clock per engine
    }
    //lan8042_dump_flow_conf(&flow_conf);
    //lan8042_dump_chip_matching_flow(dev, TRUE);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_tx_classifier_conf_get_priv( mepa_device_t *dev, u16 in_flow,
                                                    mepa_ts_classifier_t *const out_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_ts_engine_t eng_id;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_engine_flow_conf_t flow_conf;
    u16 flow_id;
    mepa_rc rc;
    in_flow = 0;
    rc = lan80xx_get_eng_flow_info(in_flow, &eng_id, &flow_id);
    if (rc != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_TS, "\n Invlaid PTP Engine Selected on port : %d", data->port_no);
        return MEPA_RC_ERROR;
    }

    eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
    if (!eng_conf->eng_used) {
        T_E(MEPA_TRACE_GRP_TS, "Engine not used")
        return MEPA_RC_ERROR;
    } else {
        // Get conf from engine
        rc = lan80xx_ts_egress_engine_conf_get(dev, data->port_no, eng_id, &flow_conf);
        if (rc != MEPA_RC_OK) {
            return MEPA_RC_ERR_TS_FLOW_GET_FAIL;
        }
        out_conf->pkt_encap_type = (eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_PTP) ? MEPA_TS_ENCAP_ETH_PTP :
                                   (eng_conf->encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP) ? MEPA_TS_ENCAP_ETH_IP_PTP :
                                   MEPA_TS_ENCAP_NONE;
        out_conf->enable = TRUE;
        lan80xx_get_class_from_flow(&flow_conf, flow_id, out_conf);
        out_conf->clock_id = eng_id; // 1 clock per engine
    }
    //lan8042_dump_flow_conf(&flow_conf);
    //lan8042_dump_chip_matching_flow(dev, TRUE);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_rx_classifier_conf_get(mepa_device_t *dev, u16 in_flow,
                                           mepa_ts_classifier_t *const out_conf)
{
    return lan80xx_rx_classifier_conf_get_priv(dev, in_flow, out_conf);
}

mepa_rc lan80xx_phy_tx_classifier_conf_get(mepa_device_t *dev, u16 in_flow,
                                           mepa_ts_classifier_t *const out_conf)
{
    return lan80xx_tx_classifier_conf_get_priv(dev, in_flow, out_conf);
}

mepa_rc lan80xx_ts_csr_ptptime_set_priv( mepa_device_t *dev,
                                         const mepa_port_no_t port_no,
                                         const phy25g_phy_timestamp_t  *const ts)
{
    u32          value = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc rc = MEPA_RC_OK;

    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }


    /* Write the timestamp in the phy*/
    value = (ts->seconds.high & 0xffff);
    //value = LAN80XX_F_PTP_LTC_PTP_TOD_SEC_MSB_PTP_TOD_SEC_MSB(value);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_SEC_MSB(base_data->lsc_select), value);

    value = (ts->seconds.low & 0xffffffff);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_SEC_LSB(base_data->lsc_select), value);

    value = (ts->nanoseconds & 0xffffffff);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC(base_data->lsc_select), value);

    value = (ts->subnanoseconds & 0xff);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC_FRAC(base_data->lsc_select), value);
    /* Signal the PHY to load the Timestamp from the LTC save registers
     * Read the LTC_CTRL, update the Load operation, write the regsiter
     */
#if 0
    value = 0;
    // Keep PTP_PIN_OPT = 0 so that action actions will be executed immediately
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_LTC, 0, LAN80XX_PTP_LTC_PTP_PIN_CFG(port_no)), value);

    // read the value
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_LTC, 0, LAN80XX_PTP_LTC_PTP_PIN_CFG(port_no)), &value);

    // [BIT 31:29] = b'010 = load the value
    value = value |  0x01000000;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_IOREG(MMD_ID_PTP_LTC, 0, LAN80XX_PTP_LTC_PTP_PIN_CFG(port_no)), value);
#endif
    return MEPA_RC_OK;
}


mepa_rc lan80xx_ts_csr_ptptime_get_priv(mepa_device_t *dev,
                                        const mepa_port_no_t port_no,
                                        phy25g_phy_timestamp_t  *const ts)
{
    u32          value = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc rc = MEPA_RC_OK;

    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }


    LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_SEC_LSB(base_data->lsc_select), &value);
    ts->seconds.low = (value & 0xffffffff);

    LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_SEC_MSB(base_data->lsc_select), &value);
    ts->seconds.high = (value & 0xffff) ;

    LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC(base_data->lsc_select), &value);
    ts->nanoseconds = (value & 0xffffffff);

    LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC_FRAC(base_data->lsc_select), &value);
    ts->subnanoseconds = (value & 0xff);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_phy_ts_fifo_read_install( mepa_device_t *dev,
                                          lan80xx_phy_ts_fifo_read  rd_cb,
                                          void  *cntxt)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    data->ts_fifo_cb = rd_cb;
    data->cntxt = cntxt;
    MEPA_EXIT(dev);

    return rc;
}

/*
 * TS FIFO service algorithm: 2R TSFIFO_0 with optimization as par TIMM algorithm
 */
mepa_rc lan80xx_phy_ts_fifo_empty_priv(mepa_device_t *dev,
                                       const mepa_port_no_t port_no,
                                       phy25g_ts_fifo_entry_t ts_list[],
                                       u32                 *const num,
                                       BOOL                     callback)
{
    u32   value = 0;
    u32   loop_cnt = 5;
    u32   depth = 0;
    u8    sig[39], id_cnt = 0;
    BOOL  entry_found = FALSE;
    mepa_rc rc = MEPA_RC_OK;
    u32    pos = 0;
    phy25g_phy_timestamp_t        ts;
    phy25g_ts_fifo_sig_mask_t sig_mask;
    phy25g_ts_fifo_sig_t    signature;
    mepa_ts_fifo_status_t   status = MEPA_TS_FIFO_SUCCESS;
    u32   val_1st = 0, val_2nd = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    lan80xx_phy_ts_fifo_read cb = NULL;
    void *cx = NULL;;
    if (callback) {
        if (data->ts_fifo_cb == NULL) {
            return MEPA_RC_ERROR;
        }
        cb = data->ts_fifo_cb;
        cx = data->cntxt;
    } else {
        *num = 0;
    }

    sig_mask = data->phy_ts_port_conf.sig_mask;
    /* Step 1:: Loop reading the TSFIFO_0 register, until TS_EMPTY bit = 0 */
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    0x7a, &val_2nd));
#if 1
    do {
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                        LAN80XX_PTP_PROC_EGR_TSFIFO_0, &val_1st));
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                        LAN80XX_PTP_PROC_EGR_TSFIFO_0, &val_2nd));

        if ((!(val_1st & LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY)) &&
            (!(val_2nd & LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY))) {
            /* Entries found */

            entry_found = TRUE;
            break;
        }
        loop_cnt--;

    } while (loop_cnt > 0);
#endif
    if (entry_found) {
        do {
            value = 0;
            pos = 0;
            /* Step 2:: Read the TSFIFO_0 register again to get valid timestamp[15:0] data and valid flags[2:0] data */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_0, &val_1st));

            if (val_1st & LAN80XX_M_PTP_PROC_EGR_TSFIFO_0_EGR_TS_EMPTY) {
                break;
            }



#if 0

            //         printf("Breaking from partial ts check, valid ts is %d\n", LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS(value));
            //if (LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS(value) != 9) {
            /* Partial time stamps are invalid, empty the FIFO */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_1, &value));
            printf("The value of TSFIFO_0 is %x\n", val_1st);

            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_1, &value));

            printf("The value of TSFIFO_1 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_2, &value));
            printf("The value of TSFIFO_2 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_3, &value));
            printf("The value of TSFIFO_3 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_4, &value));
            printf("The value of TSFIFO_4 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_5, &value));
            printf("The value of TSFIFO_5 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_6, &value));
            printf("The value of TSFIFO_6 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_7, &value));
            printf("The value of TSFIFO_7 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_8, &value));
            printf("The value of TSFIFO_8 is %x\n", value);
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_9, &value));
            printf("The value of TSFIFO_9 is %x\n", value);
            //           printf("Breaking from partial ts check, valid ts is %d\n", LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TS_FLAGS(value));
            // break;
            //}
#endif
            memset(&signature, 0, sizeof(phy25g_ts_fifo_sig_t));
            memset(&ts, 0, sizeof(phy25g_phy_timestamp_t));

#if 1
            sig[0] = LAN80XX_PHY_TS_EXTRACT_BYTE(val_1st, 0);
            sig[1] = LAN80XX_PHY_TS_EXTRACT_BYTE(val_1st, 8);
            sig[2] = LAN80XX_PHY_TS_EXTRACT_BYTE(val_1st, 16);
            //sig[1] = (LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TSFIFO_0(val_1st) & 0xff00) >> 8;
            //sig[0] = LAN80XX_X_PTP_PROC_EGR_TSFIFO_0_EGR_TSFIFO_0(val_1st) & 0xff;
            /* Step 3:: Read the TSFIFO_1 to TSFIFO_9 registers to get valid timestamp[207:16] data;
                        must always read the TSFIFO_9 register and it must be read last */
            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_1, &value));
            sig[3] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[4] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[5] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[6] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_2, &value));
            sig[7] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[8] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[9] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[10] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);


            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_3, &value));
            sig[11] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[12] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[13] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[14] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_4, &value));
            sig[15] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[16] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[17] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[18] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_5, &value));
            sig[19] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[20] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[21] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[22] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            value = 0;
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_6, &value));
            sig[23] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[24] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[25] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[26] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_7, &value));
            sig[27] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[28] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[29] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[30] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_8, &value));
            sig[31] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[32] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[33] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[34] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_9, &value));
            sig[35] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 0);
            sig[36] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 8);
            sig[37] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 16);
            sig[38] = LAN80XX_PHY_TS_EXTRACT_BYTE(value, 24);

#endif
            /* Step 4:: Read the TSFIFO_CSR register and check the value of TS_FIFO_LEVEL */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                            LAN80XX_PTP_PROC_EGR_TSFIFO_CSR, &value));



            depth = LAN80XX_X_PTP_PROC_EGR_TSFIFO_CSR_EGR_TS_LEVEL(value);



            signature.sig_mask = sig_mask;
            ts.subnanoseconds = sig[0];
            ts.nanoseconds = (sig[4] << 24) | (sig[3] << 16) | (sig[2] << 8)  | sig[1];
            ts.seconds.low = (sig[8] << 24) | (sig[7] << 16) | (sig[6] << 8)  | sig[5];
            ts.seconds.high = (sig[10] << 8) | sig[9];

//            printf("Time sh: %d ,sl: %d ns: %d fns=%d\n", ts.seconds.high, ts.seconds.low, ts.nanoseconds,ts.subnanoseconds);
#if 1
            pos += LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN; /* 11 Byte Timestamp length */
            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SEQ_ID) {
                MEPA_ASSERT((pos + LAN80XX_PHY_TS_SIG_SEQUENCE_ID_LEN) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                signature.sequence_id = (sig[pos + 1] << 8) | sig[pos];
                pos += LAN80XX_PHY_TS_SIG_SEQUENCE_ID_LEN;
            }

            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SOURCE_PORT_ID) {
                MEPA_ASSERT((pos + LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                for (id_cnt = 0; id_cnt <= 9; id_cnt++) { /* 0 - 9, Total 10 Byte Source Port ID */
                    signature.src_port_identity[id_cnt] = sig[pos + (9 - id_cnt)];
                }
                pos += LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN;
            }

            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DOMAIN_NUM) {
                MEPA_ASSERT((pos + 1) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                signature.domain_num = sig[pos++];
            }

            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_MSG_TYPE) {
                /* message_type field is only the lower nibble
                 */
                MEPA_ASSERT((pos + 1) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                signature.msg_type = sig[pos++] & 0x0f;
            }

            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP) {
                MEPA_ASSERT((pos + LAN80XX_PHY_TS_SIG_DEST_IP_LEN) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                signature.dest_ip = (sig[pos + 3] << 24) | (sig[pos + 2] << 16) | (sig[pos + 1] << 8) | sig[pos];
                pos += LAN80XX_PHY_TS_SIG_DEST_IP_LEN;
            }
            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP) {
                MEPA_ASSERT((pos + LAN80XX_PHY_TS_SIG_SRC_IP_LEN) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                signature.src_ip = (sig[pos + 3] << 24) | (sig[pos + 2] << 16) | (sig[pos + 1] << 8) | sig[pos];
                pos += LAN80XX_PHY_TS_SIG_SRC_IP_LEN;
            }

            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC) {
                MEPA_ASSERT((pos + LAN80XX_PHY_TS_SIG_DEST_MAC_LEN) > (LAN80XX_PTP_SIGNATURE_LEN + LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN)); /* LINT */
                for (loop_cnt = 0; loop_cnt < LAN80XX_PHY_TS_SIG_DEST_MAC_LEN; loop_cnt++) {
                    signature.dest_mac[loop_cnt] = sig[pos + loop_cnt];
                }
                pos += LAN80XX_PHY_TS_SIG_DEST_MAC_LEN;
            }
            T_D(MEPA_TRACE_GRP_TS, "Signature  :: ");
            T_D(MEPA_TRACE_GRP_TS, "    Message Type  :: %x ", signature.msg_type);
            T_D(MEPA_TRACE_GRP_TS, "    Domain Number :: %x ", signature.domain_num);
            T_D(MEPA_TRACE_GRP_TS, "    Source portId :: %x::%x::%x::%x::%x::%x::%x::%x::%x::%x", signature.src_port_identity[0], signature.src_port_identity[1],
                signature.src_port_identity[2], signature.src_port_identity[3], signature.src_port_identity[4],
                signature.src_port_identity[5], signature.src_port_identity[6], signature.src_port_identity[7],
                signature.src_port_identity[8], signature.src_port_identity[9]);
            T_D(MEPA_TRACE_GRP_TS, "    SequenceId    :: %x", signature.sequence_id);
            T_D(MEPA_TRACE_GRP_TS, "    Source IP     :: %x", (unsigned int)signature.src_ip);
            T_D(MEPA_TRACE_GRP_TS, "    Destination IP:: %x", (unsigned int)signature.dest_ip);
            T_D(MEPA_TRACE_GRP_TS, "    Destination MAC :: %2.2x:%2.2x:%2.2x:%2.2x:%2.2x:%2.2x", signature.dest_mac[0],
                signature.dest_mac[1],
                signature.dest_mac[2],
                signature.dest_mac[3],
                signature.dest_mac[4],
                signature.dest_mac[5]);

            if (callback) {
                status = LAN80XX_PHY_TS_FIFO_SUCCESS;
                /* avoid using vtss_state while outside the API lock, as the API may be called from an other thread */
                MEPA_EXIT(dev);
                /* call out of the API */
                cb(dev, port_no, &ts, &signature, cx, status);
                MEPA_ENTER(dev);
            } else {
                ts_list[*num].sig = signature;
                ts_list[*num].ts = ts;
                (*num)++;
                if (*num >= LAN80XX_PHY_TS_FIFO_MAX_ENTRIES) {
                    break;
                }
            }
#endif
        } while (depth > 1);  /* Step 4a:: If TS_FIFO_LEVEL > 1, go back and repeat steps 2 through 4 */

        /* Step 4b:: If TS_FIFO_LEVEL = 1, finished handling the TS_FIFO */
    }
    return rc;
}

static mepa_rc lan80xx_phy_ts_ip1_sig_mask_set_priv(
    mepa_device_t *dev,
    const mepa_port_no_t              port_no,
    const phy25g_ts_engine_t        engine_id,
    const phy25g_ts_blk_id_t        blk_id)
{
    u32 value = 0;
    phy25g_ts_fifo_sig_mask_t sig_mask;
    phy25g_ts_engine_flow_conf_t *flow_conf = NULL;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    sig_mask = data->phy_ts_port_conf.sig_mask ;
    flow_conf = &data->phy_ts_port_conf.egress_eng_conf[engine_id].flow_conf;
    if (sig_mask & (LAN80XX_PHY_TS_FIFO_SIG_DEST_IP | LAN80XX_PHY_TS_FIFO_SIG_SRC_IP)) {
        /* select the offset */
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                        LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG, &value));
        value = LAN80XX_PHY_TS_CLR_BITS(value,
                                        LAN80XX_M_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG_IP1_FRAME_SIG_OFFSET);
        if (flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode
            == LAN80XX_PHY_TS_IP_VER_4) {
            value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG_IP1_FRAME_SIG_OFFSET(12);
        } else if (flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode == LAN80XX_PHY_TS_IP_VER_6) {

            if ((sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP) && (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP)) {
                T_E(MEPA_TRACE_GRP_TS, "For IPv6 frames, either source IP or destination IP can be selected"
                    " but not both, engine_id : %d", engine_id);
            }
            if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP) {
                value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG_IP1_FRAME_SIG_OFFSET(32);
            } else if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP) {
                value |= LAN80XX_F_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG_IP1_FRAME_SIG_OFFSET(20);
            }

            T_D(MEPA_TRACE_GRP_TS, "IPV6 _IP1_FRAME_SIG_OFFSET : %d ipv6 mode=%d", value, flow_conf->flow_conf.ptp.ip1_opt.comm_opt.ip_mode);
        }
    }


    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                     LAN80XX_ANA_IP1_NXT_PROTOCOL_IP1_FRAME_SIG_CFG, &value));
    /* select the IP1 comparator */
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                    LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));
    value = LAN80XX_PHY_TS_CLR_BITS(value,
                                    LAN80XX_M_ANA_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL);
    value |= LAN80XX_F_ANA_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL(2) ;
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                     LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_phy_ts_eth1_sig_mask_set_priv(
    mepa_device_t *dev,
    const mepa_port_no_t              port_no,
    const phy25g_ts_engine_t        engine_id,
    const phy25g_ts_blk_id_t        blk_id)
{
    u32 value;
    phy25g_ts_fifo_sig_mask_t sig_mask;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    sig_mask = data->phy_ts_port_conf.sig_mask ;
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC) {
        if (engine_id < LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
            /* select the offset */
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                            LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));
            value = LAN80XX_PHY_TS_CLR_BITS(value,
                                            LAN80XX_M_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_FRAME_SIG_OFFSET);
            value |= LAN80XX_F_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL_ETH1_FRAME_SIG_OFFSET(0);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                             LAN80XX_ANA_ETH1_NXT_PROTOCOL_ETH1_NXT_PROTOCOL, &value));

            /* select the ETH1 comparator in Frame Signature builder mode config register*/
            MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                            LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));
            value = LAN80XX_PHY_TS_CLR_BITS(value,
                                            LAN80XX_M_ANA_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL);
            value |= LAN80XX_F_ANA_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL(0);
            MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                             LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));
        }
#if 0
        else if (engine_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A ||
                 engine_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2B) {
            if (vtss_state->phy_ts_port_conf.is_gen2 == TRUE) {
                if (engine_id == LAN80XX_PHY_TS_OAM_ENGINE_ID_2A) {
                    /*Select the offset */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                                    LAN80XX_ANA_ETH1_NXT_PROTOCOL_A_ETH1_NXT_PROTOCOL_A, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value,
                                                    LAN80XX_M_ANA_OAM_ETH1_NXT_PROTOCOL_A_ETH1_NXT_PROTOCOL_A_ETH1_FRAME_SIG_OFFSET_A);
                    value |= LAN80XX_F_ANA_OAM_ETH1_NXT_PROTOCOL_A_ETH1_NXT_PROTOCOL_A_ETH1_FRAME_SIG_OFFSET_A(0);
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                     LAN80XX_ANA_ETH1_NXT_PROTOCOL_A_ETH1_NXT_PROTOCOL_A, &value));
                } else {
                    /*Select the offset */
                    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                                    LAN80XX_ANA_ETH1_NXT_PROTOCOL_B_ETH1_NXT_PROTOCOL_B, &value));
                    value = LAN80XX_PHY_TS_CLR_BITS(value,
                                                    LAN80XX_M_ANA_OAM_ETH1_NXT_PROTOCOL_B_ETH1_NXT_PROTOCOL_B_ETH1_FRAME_SIG_OFFSET_B);
                    value |= LAN80XX_F_ANA_OAM_ETH1_NXT_PROTOCOL_B_ETH1_NXT_PROTOCOL_B_ETH1_FRAME_SIG_OFFSET_B(0);
                    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                     LAN80XX_ANA_ETH1_NXT_PROTOCOL_B_ETH1_NXT_PROTOCOL_B, &value));
                }

                /* select the ETH1 comparator in Frame Signature builder mode config register*/
                MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, blk_id,
                                                LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));
                value = LAN80XX_PHY_TS_CLR_BITS(value,
                                                LAN80XX_M_ANA_OAM_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL);
                value |= LAN80XX_F_ANA_OAM_FRAME_SIG_CFG_FSB_CFG_FSB_ADR_SEL(0) ;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                 LAN80XX_ANA_FRAME_SIG_CFG_FSB_CFG, &value));
            }
        }
#endif
    }
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_phy_ts_signature_set_priv(mepa_device_t *dev,
                                                 const mepa_port_no_t port_no)
{
    u32 value = 0, pos = 0;
    i32 byte_ct = 0;
    u8 sig_sel[LAN80XX_PTP_SIGNATURE_LEN];
    phy25g_ts_blk_id_t blk_id;
    phy25g_ts_engine_t engine_id;
    phy25g_ts_encap_t  encap_type;
    phy25g_ts_fifo_sig_mask_t sig_mask;
    //mepa_port_no_t       port_no;

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    /* Configure the signature bytes in each of the 3 engines */
    /* If the engine is not able to generate the signature than Ignore the sig_mask
     * E.G : getting the Source / Destination IP address from the Packet in case of
     * Engine 2A/2B
     */
    /* All these signature bits are based on the PTP header fields */
    /* Algorithm: 1. Go through all egress analyzers configuration and get
     *                the engine Id corresponding to the PTP engine.
     *            2. Based on the Signature mask bits select the bytes in
     *                the PTP header to extract the signature.
     */
    sig_mask = data->phy_ts_port_conf.sig_mask;
    memset(&sig_sel[0], 0, LAN80XX_PTP_SIGNATURE_LEN);


    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SEQ_ID) {
        /* sequene_id is 2 Bytes long, it starts from 30th byte in PTP header
         * [0 - based byte count]
         * use 0, 1
         */
        sig_sel[pos++] = 0;
        sig_sel[pos++] = 1;
    }

    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SOURCE_PORT_ID) {
        /* source_port_id is 10 Bytes long, it starts from 28th byte in PTP header
         * [0 - based byte count]
         * use 2,3,4,5,6,7,8,9,10,11
         */
        for (byte_ct = 0; byte_ct < 10; byte_ct++) {
            /* Select Byte starting is 2 and ending is 11 */
            sig_sel[pos + byte_ct] = 2 + byte_ct;
        }
        pos += LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN;
    }

    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DOMAIN_NUM) {
        /* domain_num is the 4th byte in PTP header [0 - based byte count]
         * use 25
         */
        sig_sel[pos++] = 25;

    }

    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_MSG_TYPE) {
        /* msg_type is 1 nibble in 0 byte in PTP header [0 - based byte count]
         * use 26
         */
        sig_sel[pos++] = 26;
    }

    if (sig_mask & (LAN80XX_PHY_TS_FIFO_SIG_DEST_IP | LAN80XX_PHY_TS_FIFO_SIG_SRC_IP)) {
        /* configure both the IP comparators for all the three engines */
        /* read the auto adjust update value register */
        value = 0;
        /* Irrespective of the engine configuration just configure signature
         * bytes for both the IP comparators and the offset is always 12 bytes
         * that is the location in the ip header where the source and
         * destination IP address are stored, since 8 bytes are taken from the
         * starting byte of offset in the ip header for determination of the
         * signature
         */
        /* Signature bytes are always taken from the egress analyzer
         */
        /* IP comparater block is only present in engine-1 and engine-2
         */
        for (engine_id = LAN80XX_PHY_TS_PTP_ENGINE_ID_0; engine_id <= LAN80XX_PHY_TS_PTP_ENGINE_ID_1;
             engine_id++) {
            encap_type = data->phy_ts_port_conf.egress_eng_conf[engine_id].encap_type;
            MEPA_RC(lan80xx_phy_ts_ana_blk_id_get(engine_id, FALSE, &blk_id));
            if (data->phy_ts_port_conf.egress_eng_conf[engine_id].eng_used == TRUE) {

                if ((encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP)) {
                    MEPA_RC(lan80xx_phy_ts_ip1_sig_mask_set_priv(dev, port_no, engine_id, blk_id));
                }
#if 0
                else if (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP) {
                    //MEPA_RC(lan80xx_phy_ts_ip2_sig_mask_set_priv(dev, port_no, engine_id, blk_id));
                }
#endif
            }
        }
        /* If source IP is selected for signature then use next position storing
         * the IP address */
        /* Note :: no need to check for the position because the length of the
         * signature is taken care before calling this function itself
         * All the checks that have been done are to satisfy LINT
         */
        if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP) {
            /* Dest_IP is 4 Bytes long, it starts from 16th byte in IP header
             * [0 - based byte count]
             * use 28,29,30,31
             */
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 36;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 37;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 38;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 39;
        }

        if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP) {
            /* src_IP is 4 Bytes long, it starts from 12th byte in IP header
             * [0 - based byte count]
             * use 32,33,34,35
             */
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 40;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 41;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 42;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 43;
        }
    }

    if (sig_mask & (LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC)) {
        /* configure both the ETH comparators */

        for (engine_id = LAN80XX_PHY_TS_PTP_ENGINE_ID_0; engine_id <= LAN80XX_PHY_TS_PTP_ENGINE_ID_1;
             engine_id++) {
            encap_type = data->phy_ts_port_conf.egress_eng_conf[engine_id].encap_type;
            MEPA_RC(lan80xx_phy_ts_ana_blk_id_get(engine_id, FALSE, &blk_id));
            if (data->phy_ts_port_conf.egress_eng_conf[engine_id].eng_used == TRUE) {
                if ((encap_type == LAN80XX_PHY_TS_ENCAP_ETH_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP) ||
                    (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP)) {
                    MEPA_RC(lan80xx_phy_ts_eth1_sig_mask_set_priv(dev, port_no, engine_id, blk_id));
                }
#if 0
                else if (((encap_type == LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP)      ||
                          (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP)   ||
                          (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP) ||
                          (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP)) &&
                         (engine_id != LAN80XX_PHY_TS_OAM_ENGINE_ID_2B)) {
                    //MEPA_RC(lan80xx_phy_ts_eth2_sig_mask_set_priv(dev, port_no, engine_id, blk_id));
                }
#endif
            }
        }
        /* If Destination MAC is selected for signature then use next position storing
         * the MAC address */
        /* Note :: no need to check for the position because the length of the
         * signature is taken care before calling this function itself
         * All the checks that have been done are to satisfy LINT
         */
        if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC) {
            /* Dest_MAC is 6 Bytes long
             * [0 - based byte count]
             * use 30,31,32,33,34,35
             */
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 35;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 34;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 33;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 32;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 31;
            MEPA_ASSERT(pos > LAN80XX_PTP_SIGNATURE_LEN);
            sig_sel[pos++] = 30;
        }
    }
    /* configure the signature selection
     * This signature selection is only valid for Engine-1 and Engine-2
     */
    for (engine_id = LAN80XX_PHY_TS_PTP_ENGINE_ID_0; engine_id <= LAN80XX_PHY_TS_PTP_ENGINE_ID_1;
         engine_id++) {
        encap_type = data->phy_ts_port_conf.egress_eng_conf[engine_id].encap_type;
        MEPA_RC(lan80xx_phy_ts_ana_blk_id_get(engine_id, FALSE, &blk_id));
#if 0
        if ((data->phy_ts_port_conf.egress_eng_conf[engine_id].eng_used == TRUE) &&
            ((encap_type == LAN80XX_PHY_TS_ENCAP_ETH_OAM) ||
             (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_ETH_OAM) ||
             (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM) ||
             (encap_type == LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM))) {
            continue;
        }
#endif
        value = 0;
        pos = 0;
        for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
            value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
        }
        pos += 5;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                         LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_0, &value));

        value = 0;
        for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
            value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
        }
        pos += 5;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                         LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_1, &value));

        value = 0;
        for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
            value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
        }
        pos += 5;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                         LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_2, &value));

        value = 0;
        value = (sig_sel[pos++] & 0x3f);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                         LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_3, &value));
    }
#if 0
    if (data->phy_ts_port_conf.is_gen2 == TRUE) {
        for (engine_id =  LAN80XX_PHY_TS_OAM_ENGINE_ID_2A; engine_id <= LAN80XX_PHY_TS_OAM_ENGINE_ID_2B;
             engine_id++) {
            encap_type = data->phy_ts_port_conf.egress_eng_conf[engine_id].encap_type;
            MEPA_RC(lan80xx_phy_ts_ana_blk_id_get(engine_id, FALSE, &blk_id));

            if ((data->phy_ts_port_conf.egress_eng_conf[engine_id].eng_used == TRUE) &&
                (encap_type != LAN80XX_PHY_TS_ENCAP_ETH_OAM) &&
                (encap_type != LAN80XX_PHY_TS_ENCAP_ETH_ETH_OAM) &&
                (encap_type != LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_OAM) &&
                (encap_type != LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ACH_OAM)) {
                value = 0;
                pos = 0;
                for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
                    value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
                }
                pos += 5;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                 LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_0, &value));

                value = 0;
                for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
                    value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
                }
                pos += 5;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                 LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_1, &value));

                value = 0;
                for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
                    value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
                }
                pos += 5;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                 LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_2, &value));

                value = 0;
                for (byte_ct = 4; byte_ct >= 0; byte_ct--) {
                    value = (value << 6) | (sig_sel[pos + byte_ct] & 0x3f);
                }
                pos += 5;
                MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, blk_id,
                                                 LAN80XX_ANA_FRAME_SIG_CFG_FSB_MAP_REG_3, &value));
            }
        }
    }
#endif

    return MEPA_RC_OK;
}

/* Note :: The application should take care of passing the correct signature mask.
 */
mepa_rc lan80xx_phy_ts_fifo_sig_set(mepa_device_t *dev,
                                    const mepa_port_no_t              port_no,
                                    const phy25g_ts_fifo_sig_mask_t sig_mask)
{
    mepa_rc        rc = MEPA_RC_OK;
    u8             len = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;


    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_MSG_TYPE) {
        len += 1;    /* PTP Msg Type = 1Byte */
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DOMAIN_NUM) {
        len += 1;    /* PTP Dom Nm = 1Byte */
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SOURCE_PORT_ID) {
        len += LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN;    /* SRC Port Identity = 10 Bytes */
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SEQ_ID) {
        len += LAN80XX_PHY_TS_SIG_SEQUENCE_ID_LEN;    /* Sequence Number = 2 Bytes*/
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP) {
        len += LAN80XX_PHY_TS_SIG_DEST_IP_LEN;    /* Dest IP = 4 Bytes */
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP) {
        len += LAN80XX_PHY_TS_SIG_SRC_IP_LEN;    /* Src IP = 4 Bytes */
    }
    if (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC) {
        len += LAN80XX_PHY_TS_SIG_DEST_MAC_LEN;    /* Dest MAC = 6 Bytes */
    }

    if (((sig_mask & LAN80XX_PHY_TS_FIFO_SIG_SRC_IP) || (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_IP)) &&
        (sig_mask & LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC)) {
        return MEPA_RC_ERROR;
    }

    if (len > LAN80XX_PTP_SIGNATURE_LEN) {
        T_D(MEPA_TRACE_GRP_TS, "Length greater than max signature allowed");
        return MEPA_RC_ERROR;
    }

    /* inst check done inside this func */
    MEPA_ENTER(dev);
    do {
        T_D(MEPA_TRACE_GRP_TS, "port_ts_init =%d port %u mask=%d\n", data->phy_ts_port_conf.port_ts_init_done, port_no, sig_mask);
        if (data->phy_ts_port_conf.port_ts_init_done == TRUE) {
            data->phy_ts_port_conf.sig_mask = sig_mask;
            //LAN80XX_PHY_TS_SPI_PAUSE(port_no);
            /* configure the analyzer to extract the signature bytes from the packet
             */
            /* set the signature timestamp bytes based on the signature mask config */

            if ((rc = lan80xx_phy_ts_signature_set_priv(dev, port_no)) != MEPA_RC_OK) {
                T_D(MEPA_TRACE_GRP_TS, "Signature set fail, port %u", port_no);
                /* don't break, needs to unpause */
            }
            // LAN80XX_PHY_TS_SPI_UNPAUSE(port_no);
        }
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_fifo_empty( mepa_device_t *dev,
                                   const mepa_port_no_t    port_no,
                                   phy25g_ts_fifo_entry_t ts_list[],
                                   u32                 *const num,
                                   BOOL                     callback)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        if (data->phy_ts_port_conf.tx_fifo_mode != LAN80XX_PHY_TS_FIFO_MODE_NORMAL) {
            rc = MEPA_RC_ERROR;
            break;
        }
        rc = lan80xx_phy_ts_fifo_empty_priv(dev, data->port_no, ts_list, num, callback);
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_fifo_get(mepa_device_t *dev, const mepa_port_no_t    port_no, phy25g_ts_fifo_entry_t ts_list[],
                                const size_t   size,
                                uint32_t   *const num)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        if (data->phy_ts_port_conf.tx_fifo_mode != LAN80XX_PHY_TS_FIFO_MODE_NORMAL) {
            rc = MEPA_RC_ERROR;
            break;
        }
        rc = lan80xx_phy_ts_fifo_empty_priv(dev, port_no, ts_list, num, FALSE);
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}



static mepa_rc lan80xx_ts_csr_set_priv(mepa_device_t *dev,
                                       const mepa_port_no_t port_no,
                                       const phy25g_ts_proc_conf_t conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;

    mepa_port_no_t base_port = 0;

    mepa_rc      rc = MEPA_RC_OK;
    phy25g_timeinterval_t ti;
    u32 value, mask = 0, ingr_latency = 0, egr_latency = 0;
    mepa_bool_t enable;
    phy25g_ts_event_t event = 0;
    i64 adj;
    u64 tod_inc, val, tod_delta, tod_trunk;
    i32 svalue = 0, egress_default = 0, ingress_default = 0;
    u8 ingr_latency_sns = 0, egr_latency_sns = 0, latency_table_physpeed_index = 0, latency_table_matchindex = 0 ;

    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    if ((conf == LAN80XX_PHY_TS_EGR_LATENCY_SET) || (conf == LAN80XX_PHY_TS_ING_LATENCY_SET)) {

        switch (data->port_state.speed) {
        case SPEED_1G:
            latency_table_physpeed_index = 8;
            break;

        case SPEED_10G:
            latency_table_physpeed_index = 4;
            break;


        case SPEED_25G:
            if (data->conf.conf_25g.rs_fec_25g) {
                latency_table_physpeed_index = 12;
            } else {
                latency_table_physpeed_index = 0;
            }
            break;

        case SPEED_NONE:
            break;

        }
    }

    switch (conf) {

    case  LAN80XX_PHY_TS_ING_LATENCY_SET:
        latency_table_matchindex = latency_table_physpeed_index  + (data->port_state.port_mode.oper_mode * 2);
        ingr_latency =  phy25g_ts_local_latency[latency_table_matchindex].pslocal_latency_ns;
        ingr_latency_sns =  phy25g_ts_local_latency[latency_table_matchindex].pslocal_latency_sns;

        ingress_default = ((ingr_latency & 0xff) << 8) | (ingr_latency_sns);

        ti = data->phy_ts_port_conf.ingress_latency;

        svalue = LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti);

        //predicton adjustment
        if (svalue > ingress_default) {
            svalue = svalue - ingress_default;
        } else {
            svalue = ingress_default - svalue;
        }

        if (svalue > 0) {
            ingr_latency_sns = svalue & 0xff;
            svalue = svalue >> 8;
            svalue = svalue | 0x100 ;
        } else {
            ingr_latency_sns = svalue & 0xff;
            svalue = svalue >> 8;
        }

        //donot distrube the bits 8 through 22 from default egress latency because it contain default design UI and clock diffrence.
        ingr_latency = (ingr_latency & 0x7FFF00) | (svalue & 0x1FF);

        value = ingr_latency;

        value = LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY(value);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                         LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY, &value));

        value = LAN80XX_F_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS(ingr_latency_sns);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                         LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS, &value));


        break;

    case LAN80XX_PHY_TS_EGR_LATENCY_SET:
        latency_table_matchindex = latency_table_physpeed_index + (data->port_state.port_mode.oper_mode * 2) + 1;
        egr_latency =      phy25g_ts_local_latency[latency_table_matchindex].pslocal_latency_ns;
        egr_latency_sns =  phy25g_ts_local_latency[latency_table_matchindex].pslocal_latency_sns;

        egress_default = ((egr_latency & 0xff) << 8) | (egr_latency_sns);

        ti = data->phy_ts_port_conf.egress_latency;
        svalue = LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti);

        //predicton adjustment
        if (svalue > egress_default) {
            svalue = svalue - egress_default;
        } else {
            svalue = egress_default - svalue;
        }

        if (svalue > 0) {
            egr_latency_sns = svalue & 0xff;
            svalue = svalue >> 8;
            svalue = svalue | 0x100 ;
        } else {
            egr_latency_sns = svalue & 0xff;
            svalue = svalue >> 8;
        }

        //donot distrube the bits 8 through 22 from default egress latency because it contain default design UI and clock diffrence.
        egr_latency = (egr_latency & 0x7FFF00) | (svalue & 0x1FF);


        value = egr_latency;
        value = LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_EGR_PS_LOCAL_LATENCY(value);
        /* update the egress latency in the egr local latency register
             */
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                         LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY, &value));

        value  =  LAN80XX_F_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS_EGR_PS_LOCAL_LATENCY_SNS(egr_latency_sns);

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                         LAN80XX_PTP_PROC_EGR_PCS_SERDES_LOCAL_LATENCY_SNS, &value));

        /* Load the Values in the time stamp block
          */
        value = 0;
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                        LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));
        value |= LAN80XX_F_PTP_PROC_EGR_TSP_CTRL_EGR_LOAD_DELAYS(1);
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                         LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));

        break;

    case LAN80XX_PHY_TS_PATH_DELAY_SET: /* context: mepa_ts_path_delay_set*/
        ti = data->phy_ts_port_conf.path_delay;
        value = LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti) & LAN80XX_M_PTP_PROC_INGR_PATH_DELAY_SNS_INGR_PATH_DELAY_SNS;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PATH_DELAY_SNS, &value));

        value = (LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti) >> 0x8) &  LAN80XX_M_PTP_PROC_INGR_PATH_DELAY_INGR_PATH_DELAY;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PATH_DELAY, &value));

        value = LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti) & LAN80XX_M_PTP_PROC_EGR_PATH_DELAY_SNS_EGR_PATH_DELAY_SNS;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_PATH_DELAY_SNS, &value));

        value = (LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti) >> 0x8) & LAN80XX_M_PTP_PROC_EGR_PATH_DELAY_EGR_PATH_DELAY;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_PATH_DELAY, &value));

        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_TSP_CTRL, &value));
        value |= LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_TSP_CTRL, &value));
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));
        value |= LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));
        break;

    case LAN80XX_PHY_TS_PORT_ENA_SET: /* context: lan8042_phy_ts_mode_set*/
        value = 0;
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_PTP_PROC_INTERFACE_CTL, &value);

        enable = data->phy_ts_port_conf.port_ena;
        if (enable) {
            /* ENABLE :: disable the bypass mode in the timestamp processor */
            /* For Gen1 LAN80XX_F_PTP_IP_1588_TOP_CFG_STAT_INTERFACE_CTL_BYPASS */
            value = LAN80XX_PHY_TS_CLR_BITS(value, LAN80XX_M_PTP_PROC_INTERFACE_CTL_EGR_BYPASS);
        }
        /* Bit 6 :: CLK_ENA = 1, CLK_DIS = 0,   Init:CLK_ENA
         * Bit 2 :: BYPASS_DIS  = 0, BYPASS_ENA = 1, Init:BYPASS_ENA
         * Bit 1:0 :: MII protocol : 0 XGMII-64
         * update the interface control register */

        LAN80XX_CSR_WR(dev, data->port_no, LAN80XX_PTP_PROC_INTERFACE_CTL,
                       LAN80XX_F_PTP_PROC_INTERFACE_CTL_CLK_ENA(1) |
                       LAN80XX_F_PTP_PROC_INTERFACE_CTL_INGR_BYPASS(0) |
                       LAN80XX_F_PTP_PROC_INTERFACE_CTL_EGR_BYPASS(0));




        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_PTP_DOM_CFG, LAN80XX_F_PTP_LTC_PTP_DOM_CFG_PTP_ENA(1),
                        LAN80XX_M_PTP_LTC_PTP_DOM_CFG_PTP_ENA);

        break;

    case LAN80XX_PHY_TS_PORT_EVT_MASK_SET:

        event = data->phy_ts_port_conf.event_mask;
        /* ingress interrupt mask register */
        mask = 0;
        if (event & LAN80XX_PHY_TS_INGR_ENGINE_ERR) {
            mask |= LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_ANALYZER_ERROR_MASK(1);
        }
        if (event & LAN80XX_PHY_TS_INGR_RW_PREAM_ERR) {
            mask |= LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_PREAMBLE_ERR_MASK(1);
        }
        if (event & LAN80XX_PHY_TS_INGR_RW_FCS_ERR) {
            mask |= LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_FCS_ERR_MASK(1);
        }

        data->phy_ts_port_conf.ingr_reg_mask = mask;

        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_INT_MASK, &value));

        value |= mask;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_INT_MASK, &value));

        mask = 0;

        if (event & LAN80XX_PHY_TS_EGR_ENGINE_ERR) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_ANALYZER_ERROR_MASK(1);
        }

        if (event & LAN80XX_PHY_TS_EGR_RW_PREAMBLE_ERR) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_PREAMBLE_ERR_MASK(1);
        }

        if (event & LAN80XX_PHY_TS_EGR_RW_FCS_ERR) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_FCS_ERR_MASK(1);
        }

        if (event & LAN80XX_PHY_TS_EGR_TS_LEVEL) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LEVEL_MASK(1);
        }

        if (event & LAN80XX_PHY_TS_EGR_TS_LOADED) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LOADED_MASK(1);
        }

        if (event & LAN80XX_PHY_TS_EGR_TS_OVERFLOW) {
            mask |= LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_OVERFLOW_MASK(1);
        }

        data->phy_ts_port_conf.egr_reg_mask = mask;

        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_INT_MASK, &value));

        value |= mask;

        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_INT_MASK, &value));

        mask = 0;

        if (event & LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC0) {
            mask |= LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1);
        }

        if (event & LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC1) {
            mask |= LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(2);
        }

        if (event & LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC2) {
            mask |= LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(4);
        }

        if (event & LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC3) {
            mask |= LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(8);
        }

        data->phy_ts_port_conf.ltc_reg_mask = mask;

        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_PTP_PIN_INTR_ENA, mask, LAN80XX_M_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA);

        mask = 0;

        if (event & LAN80XX_PHY_TS_PTP_LTC_MEAS_INTR) {
            mask |= LAN80XX_F_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA(1);
        }

        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_LTC_MEAS_INTR_ENA, mask, LAN80XX_M_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA);

        data->phy_ts_port_conf.ltc_reg_mask |= mask < 4;

        mask = 0;

        if (event & LAN80XX_PHY_TS_PTP_SER_TOD_LOAD_INTR_ENA) {
            mask |= LAN80XX_F_PTP_LTC_SER_TOD_LOAD_INT_ENA_SER_TOD_LOAD_INTR_ENA(1);
        }

        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_SER_TOD_LOAD_INT_ENA, mask, LAN80XX_M_PTP_LTC_SER_TOD_LOAD_INT_ENA_SER_TOD_LOAD_INTR_ENA );

        data->phy_ts_port_conf.ltc_reg_mask |= mask < 6;

        mask = 0;

        if (event & LAN80XX_PHY_TS_PTP_SER_TOD_STORE_INTR_ENA) {
            mask |= LAN80XX_F_PTP_LTC_SER_TOD_STORE_INT_ENA_SER_TOD_STORE_INTR_ENA(1);
        }

        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_SER_TOD_STORE_INT_ENA, mask, LAN80XX_M_PTP_LTC_SER_TOD_STORE_INT_ENA_SER_TOD_STORE_INTR_ENA);

        data->phy_ts_port_conf.ltc_reg_mask |= mask < 5;

        mask = 0;

        break;

    case LAN80XX_PHY_TS_DELAY_ASYM_SET: /* context: mepa_ts_delay_asymmetry_set*/
        ti = data->phy_ts_port_conf.delay_asym;
        value = LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti);
        /* update the path delay in both ingress and egress directions */
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_DELAY_ASYMMETRY, &value));
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_DELAY_ASYMMETRY, &value));
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_TSP_CTRL, &value));
        value |= LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_TSP_CTRL, &value));
        MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));
        value |= LAN80XX_M_PTP_PROC_INGR_TSP_CTRL_INGR_LOAD_DELAYS;
        MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_TSP_CTRL, &value));
        break;
    case LAN80XX_PHY_TS_RATE_ADJ_SET:
        tod_inc = NOM_TOD_VAL;
        adj = data->phy_ts_port_conf.rate_adj;
        val = (u64)MEPA_LLABS(adj);
        /* Calculate the TOD increment delta value, that is a fraction of the nominal TOD increment. */
        /* The fraction is given by 'adj' in 1E-9. The calculation is: tod_delta = tod_inc * (adj / 1E9) */
        tod_trunk = tod_inc % 1000000000LL;   /* We will divide before multiplying to avoid overrun. The TOD truncated part is saved in 'tod_trunk' */
        tod_delta = (tod_inc / 1000000000LL) * val;    /* Divide(to make tod_inc in 1 ppb) and then multiply */
        tod_delta += (tod_trunk * val) / 1000000000LL; /* Now the truncated part is multiplied and then divided. Result is added to 'tod_delta' */
        /* Adjust the TOD increment with the delta value */
        if (adj > 0) {
            tod_inc += tod_delta;
        } else {
            tod_inc -= tod_delta;
        }
        /* Configure the new adjusted TOD increment value */
        u32 value;
        LAN80XX_CSR_RD(dev, base_data->port_no, LAN80XX_PTP_LTC_PTP_DOM_CFG,  &value);
        LAN80XX_CSR_WRM(base_data->port_no, LAN80XX_PTP_LTC_PTP_DOM_CFG,  (value | LAN80XX_M_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS), LAN80XX_M_PTP_LTC_PTP_DOM_CFG_PTP_CLKCFG_DIS);
        LAN80XX_CSR_WR(dev, base_data->port_no, LAN80XX_PTP_LTC_CLK_PER_CFG(0), (u32)(tod_inc & 0xFFFFFFFF));
        LAN80XX_CSR_WR(dev, base_data->port_no, LAN80XX_PTP_LTC_CLK_PER_CFG(1), (u32)(tod_inc >> 32));
        break;

    case LAN80XX_PHY_TS_PPS_OUTPUT_CONF_SET:

        if (data->ptp_lsc_output_config.pps_conf.pin_select == LAN80XX_PTP_LS_CTRL_3) {
            T_E(MEPA_TRACE_GRP_GEN, "no o/p support in ls ctrl 3");
            return MEPA_RC_ERROR;
        }

        value = 0;
        value = data->ptp_lsc_output_config.pps_conf.pps_pulse_width & LAN80XX_M_PTP_LTC_PIN_WF_HIGH_PERIOD_PIN_WFH;
        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PIN_WF_HIGH_PERIOD(data->ptp_lsc_output_config.pps_conf.pin_select), value);

        value = data->ptp_lsc_output_config.pps_conf.pps_pulse_interval & LAN80XX_M_PTP_LTC_PIN_WF_LOW_PERIOD_PIN_WFL;
        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PIN_WF_LOW_PERIOD(data->ptp_lsc_output_config.pps_conf.pin_select), value);


        value = 0;
        mask = 0;

        value = LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(base_data->ptp_lsc_output_config.pps_conf.clk_select);


        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(base_data->ptp_lsc_output_config.pps_conf.pin_select);


        if (base_data->ptp_lsc_output_config.pps_conf.pin_inv_pol) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(1);
        }


        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(base_data->ptp_lsc_output_config.pps_conf.pin_sync_mode);


        if (base_data->ptp_lsc_output_config.pps_conf.nanosec_bitout_enable) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT(1);
        }


        mask = (LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT | LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC | LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT );


        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->ptp_lsc_output_config.pps_conf.pin_select), value, mask);


        break;

    case LAN80XX_PHY_TS_SERTOD_INPUT_SET:
        value = 0;
        mask = 0;


        //configur No Clock.
        value = LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(4);

        //LSC pin config only for input. output pin config is fixed.

        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(base_data->ptp_lsc_input_config.sertod_conf.pin_select);


        if (base_data->ptp_lsc_input_config.sertod_conf.pin_inv_pol) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(1);
        }

        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(base_data->ptp_lsc_input_config.sertod_conf.pin_sync_mode);

        mask = (LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT |  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC);


        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->ptp_lsc_input_config.sertod_conf.ls_unit_sel), value, mask);

        //configure the serial tod Load period config.
        value = 0;

        if (base_data->ptp_lsc_input_config.sertod_conf.Ld_period_cfg.one_sec_wait_period_cfg != 0) {
            value = LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_SECOND_WAIT_PERIOD_CFG(base_data->ptp_lsc_input_config.sertod_conf.Ld_period_cfg.one_sec_wait_period_cfg);

        }

        if (base_data->ptp_lsc_input_config.sertod_conf.Ld_period_cfg.one_microsec_period_cfg != 0) {
            value |= LAN80XX_S_F_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG_PIN_SER_TOD_ONE_MICROSECOND_PERIOD_CFG(base_data->ptp_lsc_input_config.sertod_conf.Ld_period_cfg. one_microsec_period_cfg);

        }

        if (value != 0) {
            LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_SER_TOD_LOAD_PERIOD_CFG, value);
        }

        //serial tod config
        value = 0;

        if (base_data->ptp_lsc_input_config.sertod_conf.load_enable) {
            value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_EN(1);
        }

        if (base_data->ptp_lsc_input_config.sertod_conf.store_enable) {
            value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_STORE_EN(1);
        }

        if (data->phy_ts_port_conf.auto_clear_ls) {
            value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LOAD_STORE_AUTO_CLR(1);
        }

        if (base_data->ptp_lsc_input_config.sertod_conf.msb_byte_first) {
            value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BYTE_FIRST(1);
        }

        if (base_data->ptp_lsc_input_config.sertod_conf.msb_bit_first) {
            value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_INPUT_MSB_BIT_FIRST(1);
        }


        value |= LAN80XX_F_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG_SER_TOD_LS_UNIT_SEL(base_data->ptp_lsc_input_config.sertod_conf.ls_unit_sel);


        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_SER_TOD_LOAD_STORE_CFG, value);

        break;


    case LAN80XX_PHY_TS_SERTOD_OUTPUT_SET:

        value = 0;
        mask = 0;

        if (data->ptp_lsc_output_config.sertod_conf.pin_select == LAN80XX_PTP_LS_CTRL_3) {
            T_E(MEPA_TRACE_GRP_GEN, "no o/p support in ls ctrl 3");
            return MEPA_RC_ERROR;
        }


        //configur No Clock.
        value = LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(4);

        //LSC pin config only for input. output pin config is fixed.

        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(base_data->ptp_lsc_output_config.sertod_conf.pin_select);


        if (base_data->ptp_lsc_output_config.sertod_conf.pin_inv_pol) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(1);
        }

        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(base_data->ptp_lsc_output_config.sertod_conf.pin_sync_mode);

        if (base_data->ptp_lsc_output_config.sertod_conf.msb_byte_first) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT(2);
        }

        if (base_data->ptp_lsc_output_config.sertod_conf.msb_bit_first) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT(1);
        }

        mask = (LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT |  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC |  LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_OPT);


        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->ptp_lsc_output_config.sertod_conf.pin_select), value, mask);

        //configure the serial tod WFH,WFL period config.
        value = 0;


        value = LAN80XX_F_PTP_LTC_PIN_WF_HIGH_PERIOD_PIN_WFH(base_data->ptp_lsc_output_config.sertod_conf.pin_wfh_period);



        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PIN_WF_HIGH_PERIOD(data->ptp_lsc_output_config.pps_conf.pin_select), value);


        value = LAN80XX_F_PTP_LTC_PIN_WF_LOW_PERIOD_PIN_WFL(base_data->ptp_lsc_output_config.sertod_conf.pin_wfl_period);


        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PIN_WF_LOW_PERIOD(data->ptp_lsc_output_config.pps_conf.pin_select), value);

        break;



    case LAN80XX_PHY_TS_PPS_INPUT_CONG_SET:

        value = 0;
        mask = 0;

        value = LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(base_data->ptp_lsc_input_config.pps_conf.clk_select);



        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT(base_data->ptp_lsc_input_config.pps_conf.pin_select);


        if (base_data->ptp_lsc_input_config.pps_conf.pin_inv_pol) {
            value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL(1);
        }


        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(base_data->ptp_lsc_input_config.pps_conf.pin_sync_mode);



        mask = (LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT | LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SELECT |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_INV_POL |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC );


        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->ptp_lsc_input_config.pps_conf.lsc_select), value, mask);
        break;


    case LAN80XX_PHY_TS_EPPS_SET:

        value = 0;
        mask = 0;

        value = LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK(1);

        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT(base_data->ptp_lsc_input_config.epps_conf.clk_select);


        value |= LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC(base_data->ptp_lsc_input_config.epps_conf.pin_sync_mode);


        mask = (LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_EMBEDDED_CLK | LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_CLK_SELECT |
                LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_SYNC);


        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->ptp_lsc_input_config.epps_conf.lsc_select), value, mask);

        LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_EPPS_DET_ADJ(base_data->ptp_lsc_input_config.epps_conf.lsc_select), base_data->ptp_lsc_input_config.epps_conf.epps_event_detect_adjust & LAN80XX_M_PTP_EPPS_DEG_CFG);

        break;



    default:
        rc = MEPA_RC_ERROR;
    }
    return rc;
}

mepa_rc lan80xx_phy_ts_load_store_contoller_set(mepa_device_t *dev, const mepa_port_no_t  port_no, uint8_t  ls_controller_sel)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_D(MEPA_TRACE_GRP_TS, "TS Init not done ");
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

        base_data->lsc_select = ls_controller_sel;

    } while (0);

    MEPA_EXIT(dev);

    return rc;
}

mepa_rc lan80xx_phy_ts_pps_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_pps_input_conf_t *const pin_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(pin_conf == NULL)

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_D(MEPA_TRACE_GRP_TS, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

        base_data->ptp_lsc_input_config.pps_conf =  *pin_conf;
        rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_PPS_INPUT_CONG_SET);
        if (rc != MEPA_RC_OK) {
            T_D(MEPA_TRACE_GRP_TS, "Serial ToD conf set fail, port %u", port_no);
        }


    } while (0);

    MEPA_EXIT(dev);
    return rc;
}



mepa_rc lan80xx_phy_ts_sertod_output_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_output_conf_t *const sertod_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t  base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(sertod_conf == NULL)

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_D(MEPA_TRACE_GRP_TS, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

        base_data->ptp_lsc_output_config.sertod_conf = *sertod_conf;
        rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_SERTOD_OUTPUT_SET);
        if (rc != MEPA_RC_OK) {
            T_D(MEPA_TRACE_GRP_TS, "Serial ToD conf set fail, port %u", port_no);
        }


    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_sertod_input_confset(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_sertod_input_conf_t *const sertod_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t  base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(sertod_conf == NULL)

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_D(MEPA_TRACE_GRP_TS, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

        base_data->ptp_lsc_input_config.sertod_conf = *sertod_conf;
        rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_SERTOD_INPUT_SET);
        if (rc != MEPA_RC_OK) {
            T_D(MEPA_TRACE_GRP_TS, "Serial ToD conf set fail, port %u", port_no);
        }


    } while (0);

    MEPA_EXIT(dev);
    return rc;
}





mepa_rc lan80xx_phy_ts_epps_conf_set(mepa_device_t *dev, const mepa_port_no_t    port_no, const  phy25g_ts_epps_conf_t *const epps_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t  base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(epps_conf == NULL)

    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_D(MEPA_TRACE_GRP_TS, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

        base_data->ptp_lsc_input_config.epps_conf = *epps_conf;
        rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_EPPS_SET);
        if (rc != MEPA_RC_OK) {
            T_D(MEPA_TRACE_GRP_TS, "Serial ToD conf set fail, port %u", port_no);
        }


    } while (0);

    MEPA_EXIT(dev);
    return rc;
}



mepa_rc lan80xx_phy_ts_mode_set(mepa_device_t *dev,
                                const mepa_port_no_t  port_no,
                                const mepa_bool_t   enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        data->phy_ts_port_conf.port_ena = enable;
        rc = LAN80XX_RC_COLD(lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_PORT_ENA_SET));
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}
mepa_rc lan80xx_phy_ts_mode_get( mepa_device_t *dev,
                                 const mepa_port_no_t  port_no,
                                 mepa_bool_t      *const enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(enable == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *enable = data->phy_ts_port_conf.port_ena;
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}


mepa_rc lan80xx_phy_ts_ltc_ls_action_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_ptp_action_type_t ls_action)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t  base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;


    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    switch (ls_action) {
    case  LAN80XX_TS_CMD_LOAD:
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->lsc_select), LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(LAN80XX_TS_CMD_LOAD), LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION);
        break;


    case LAN80XX_TS_CMD_STORE:
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->lsc_select), LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(LAN80XX_TS_CMD_STORE), LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION);
        break;

    case LAN80XX_TS_CMD_WAVEFORM:
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->lsc_select), LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(LAN80XX_TS_CMD_WAVEFORM), LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION);

        break;
    case LAN80XX_TS_CMD_DELTA:
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->lsc_select), LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(LAN80XX_TS_CMD_DELTA), LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION);

        break;
    case LAN80XX_TS_CMD_TOD:
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_CFG(base_data->lsc_select), LAN80XX_F_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION(LAN80XX_TS_CMD_TOD), LAN80XX_M_PTP_LTC_PTP_PIN_CFG_PTP_PIN_ACTION);
        break;


    default:
        rc = MEPA_RC_ERROR;
        break;
    }

    return rc;
}

mepa_rc lan80xx_phy_ts_ltc_ls_action_set(mepa_device_t *dev, const mepa_port_no_t port_no, const phy25g_ptp_action_type_t  ls_type)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;
    phy25g_phy_state_t *base_data;
    mepa_port_no_t  base_port = 0;
    //uint8_t lsc_select = 0;

    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
        if (rc != MEPA_RC_OK) {
            break;
        }

        rc = lan80xx_phy_ts_ltc_ls_action_set_priv(dev, port_no, ls_type);

    } while (0);

    return rc;

}




mepa_rc lan80xx_phy_ts_delay_asymmetry_set(mepa_device_t *dev,
                                           const mepa_port_no_t port_no,
                                           const phy25g_timeinterval_t   *const delay_asym)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;;

    MEPA_ASSERT(delay_asym == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_E(MEPA_TRACE_GRP_GEN, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }
        if (*delay_asym <= (32767LL) && *delay_asym >= (-32768LL)) {
            data->phy_ts_port_conf.delay_asym = *delay_asym;
            ////LAN80XX_PHY_TS_SPI_PAUSE(port_no);
            if ((rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_DELAY_ASYM_SET)) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "Asymmetry set fail, port %u", port_no);
                /* don't break, needs to unpause */
            }
            ////LAN80XX_PHY_TS_SPI_UNPAUSE(port_no);
        } else {
            rc = MEPA_RC_ERROR;
        }
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_delay_asymmetry_get(const mepa_device_t *dev,
                                           const mepa_port_no_t port_no,
                                           phy25g_timeinterval_t         *const delay_asym)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;;

    MEPA_ASSERT(delay_asym == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *delay_asym = data->phy_ts_port_conf.delay_asym;
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_path_delay_set(mepa_device_t *dev,
                                      const mepa_port_no_t  port_no,
                                      const phy25g_timeinterval_t    *const path_delay)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;;
    MEPA_ASSERT(path_delay == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_E(MEPA_TRACE_GRP_GEN, "Init not done, port %u", port_no);
            rc = MEPA_RC_ERROR;
            break;
        }
        data->phy_ts_port_conf.path_delay = *path_delay;
        ////LAN80XX_PHY_TS_SPI_PAUSE(port_no);
        if (lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_PATH_DELAY_SET) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Path_delay set fail, port %u", port_no);
            rc = MEPA_RC_ERROR;
            /* don't break, needs to unpause */
        }
        ////LAN80XX_PHY_TS_SPI_UNPAUSE(port_no);
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_path_delay_get(const mepa_device_t *dev,
                                      const mepa_port_no_t  port_no,
                                      phy25g_timeinterval_t          *const path_delay)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;
    MEPA_ASSERT(path_delay == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *path_delay = data->phy_ts_port_conf.path_delay;
    } while (0);
    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_clock_rateadj_set(mepa_device_t  *dev,
                                         const mepa_port_no_t           port_no,
                                         const phy25g_ts_scaled_ppb_t *const adj)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(adj == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        data->phy_ts_port_conf.rate_adj = *adj;
        //LAN80XX_PHY_TS_SPI_PAUSE(port_no);
        if ((rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_RATE_ADJ_SET)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Rate Adj fail, port %u", port_no);
            /* don't break, needs to unpause */
        }
        //LAN80XX_PHY_TS_SPI_UNPAUSE(port_no);
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_clock_rateadj_get(const mepa_device_t  *dev,
                                         const mepa_port_no_t      port_no,
                                         phy25g_ts_scaled_ppb_t  *const adj)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(adj == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *adj = data->phy_ts_port_conf.rate_adj;
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_egress_latency_get(const mepa_device_t  *dev,
                                          const mepa_port_no_t  port_no,
                                          phy25g_timeinterval_t    *const latency)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);

    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *latency = data->phy_ts_port_conf.egress_latency;

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_egress_latency_set(mepa_device_t  *dev,
                                          const mepa_port_no_t  port_no,
                                          const phy25g_timeinterval_t    *const latency)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;
    phy25g_timeinterval_t    cur_latency;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    do {

        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        cur_latency = data->phy_ts_port_conf.egress_latency;
        data->phy_ts_port_conf.egress_latency = *latency;

        if ((rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_EGR_LATENCY_SET)) != MEPA_RC_OK) {
            /* don't break, needs to unpause */
            data->phy_ts_port_conf.egress_latency = cur_latency;
        }

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_ingress_latency_get(const mepa_device_t  *dev,
                                           const mepa_port_no_t  port_no,
                                           phy25g_timeinterval_t    *const latency)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK ;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);

    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        *latency = data->phy_ts_port_conf.ingress_latency;

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_ingress_latency_set(mepa_device_t  *dev,
                                           const mepa_port_no_t  port_no,
                                           const phy25g_timeinterval_t    *const latency)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;
    phy25g_timeinterval_t    cur_latency;

    MEPA_ASSERT(latency == NULL);
    MEPA_ENTER(dev);
    do {

        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        cur_latency = data->phy_ts_port_conf.ingress_latency;
        data->phy_ts_port_conf.ingress_latency = *latency;

        if ((rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_ING_LATENCY_SET)) != MEPA_RC_OK) {
            /* don't break, needs to unpause */
            data->phy_ts_port_conf.ingress_latency = cur_latency;
        }

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_phy_ts_ltc_tod_delta_set(mepa_device_t  *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc rc = MEPA_RC_OK;
    uint32_t value = 0;


    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);

    value = (base_data->ptp_lsc_input_config.tod_delta_adj_conf.nanoseconds & 0xffffffff);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC(base_data->ptp_lsc_input_config.tod_delta_adj_conf.lsc_select), value);

    value = (base_data->ptp_lsc_input_config.tod_delta_adj_conf.subnanoseconds & 0xff);
    LAN80XX_CSR_WR(dev, base_port, LAN80XX_PTP_LTC_PTP_TOD_NSEC_FRAC(base_data->ptp_lsc_input_config.tod_delta_adj_conf.lsc_select), value);

    return rc;
}


mepa_rc lan80xx_phy_ts_ptptime_adj_delta(mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_ts_ltc_delta_adj_cfg *const phy25g_ltc_tod_adj)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(phy25g_ltc_tod_adj == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
        if (rc != MEPA_RC_OK) {
            break;
        }

        base_data->ptp_lsc_input_config.tod_delta_adj_conf = *phy25g_ltc_tod_adj;

        if ((rc = lan80xx_phy_ts_ltc_tod_delta_set(dev, port_no)) !=  MEPA_RC_OK) {
            T_D(MEPA_TRACE_GRP_TS, "Delta adj fail, port %u", port_no);
            /* don't break, needs to unpause */
        }

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}


mepa_rc lan80xx_phy_ts_pps_ouput_conf_set(mepa_device_t *dev, const mepa_port_no_t  port_no, const phy25g_pps_output_conf_t *const pps_out_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(pps_out_conf == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_E(MEPA_TRACE_GRP_GEN, "Init not done, port %u", data->port_no);
            rc = MEPA_RC_ERROR;
            break;
        }

        rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
        if (rc != MEPA_RC_OK) {
            break;
        }

        data->ptp_lsc_output_config.pps_conf = *pps_out_conf;

        rc = LAN80XX_RC_COLD(lan80xx_ts_csr_set_priv(dev, data->port_no, LAN80XX_PHY_TS_PPS_OUTPUT_CONF_SET));
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "PPS Configuration set fail, port %u", data->port_no);
        }
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_pps_conf_get(const mepa_device_t *dev,
                                    phy25g_ts_pps_conf_t *const phy_pps_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(phy_pps_conf == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            T_E(MEPA_TRACE_GRP_GEN, "Init not done, port %u", data->port_no);
            rc = MEPA_RC_ERROR;
            break;
        }
        *phy_pps_conf = data->phy_ts_port_conf.pps_conf;
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

static mepa_rc lan80xx_phy_ts_csr_event_poll_priv(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_ts_event_t *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_phy_state_t *base_data = NULL;
    mepa_port_no_t base_port = 0;
    mepa_rc      rc = MEPA_RC_OK;

    u32 mask = 0, pending = 0, value = 0;

    rc = lan80xx_ts_base_port_get_priv(dev, &base_port, &base_data);
    if (rc != MEPA_RC_OK) {
        return rc;
    }

    *status = 0;

    mask = data->phy_ts_port_conf.ingr_reg_mask;

    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_INT_STATUS, &pending));

    pending &= mask;    /* Only event on enabled sources */

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_INT_STATUS, &pending));

    /* ingress interrupt mask register */
    if (pending & LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_ANALYZER_ERROR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_INGR_ENGINE_ERR;
    }
    if (pending & LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_PREAMBLE_ERR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_INGR_RW_PREAM_ERR;
    }
    if (pending & LAN80XX_F_PTP_PROC_INGR_INT_MASK_INGR_RW_FCS_ERR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_INGR_RW_FCS_ERR;
    }


    mask = data->phy_ts_port_conf.egr_reg_mask;

    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_INT_STATUS, &pending));

    pending &= mask;    /* Only event on enabled sources */

    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_EGR_INT_STATUS, &pending));


    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_ANALYZER_ERROR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_ENGINE_ERR;
    }

    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_PREAMBLE_ERR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_RW_PREAMBLE_ERR;

    }

    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_RW_FCS_ERR_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_RW_FCS_ERR;
    }

    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LEVEL_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_TS_LEVEL;
    }

    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_LOADED_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_TS_LOADED;

    }

    if (pending & LAN80XX_F_PTP_PROC_EGR_INT_MASK_EGR_TS_OVERFLOW_MASK(1)) {
        *status |= LAN80XX_PHY_TS_EGR_TS_OVERFLOW;

    }

    mask = data->phy_ts_port_conf.ltc_reg_mask;

    LAN80XX_CSR_RD(dev, base_port, LAN80XX_PTP_LTC_PTP_INTR_IDENT, &pending);

    pending &= mask;

    //pending interrupt status to be clear for LCS interrupt
    value = pending & LAN80XX_M_PTP_LTC_PTP_PIN_INTR_INTR_PTP;

    if (pending & LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(1)) {
        *status |= LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC0;
    }

    if (pending & LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(2)) {
        *status |= LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC1;
    }

    if (pending & LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(4)) {
        *status |= LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC2;
    }

    if (pending & LAN80XX_F_PTP_LTC_PTP_PIN_INTR_ENA_INTR_PTP_ENA(8)) {
        *status |= LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC3;
    }

    LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_PTP_PIN_INTR, value, LAN80XX_M_PTP_LTC_PTP_PIN_INTR_INTR_PTP);

    if ((pending >> 4)  & LAN80XX_F_PTP_LTC_LTC_MEAS_INTR_ENA_PTP_MEAS_CNT_REACH_INTR_ENA(1)) {
        *status |= LAN80XX_PHY_TS_PTP_LTC_MEAS_INTR;
        //clear the interrupt.
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_LTC_MEAS_INTR, LAN80XX_F_PTP_LTC_LTC_MEAS_INTR_PTP_MEAS_CNT_REACH(1), LAN80XX_M_PTP_LTC_LTC_MEAS_INTR_PTP_MEAS_CNT_REACH);

    }

    if ((pending >> 5)  & LAN80XX_F_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE(1)) {
        *status |= LAN80XX_PHY_TS_PTP_SER_TOD_STORE_INTR_ENA;
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_SER_TOD_STORE_INTR, LAN80XX_F_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE(1), LAN80XX_M_PTP_LTC_SER_TOD_STORE_INTR_TOD_LATCH_DONE);

    }

    if ((pending >> 6) & LAN80XX_F_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE(1)) {
        *status |= LAN80XX_PHY_TS_PTP_SER_TOD_LOAD_INTR_ENA;
        LAN80XX_CSR_WRM(base_port, LAN80XX_PTP_LTC_SER_TOD_LOAD_INTR, LAN80XX_F_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE(1), LAN80XX_M_PTP_LTC_SER_TOD_LOAD_INTR_TOD_LOAD_DONE);

    }

    return rc;
}

static mepa_rc lan80xx_phy_ts_stats_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_phy_ts_stats_t   *const statistics)
{
    u32          value = 0;

    memset(statistics, 0, sizeof(phy25g_phy_ts_stats_t));

    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_INGR_RW_PREAMBLE_ERR_CNT, &value));
    statistics->ingr_pream_shrink_err = value;
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_EGR_RW_PREAMBLE_ERR_CNT, &value));
    statistics->egr_pream_shrink_err = value;
    value = 0;

    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_INGR_RW_FCS_ERR_CNT, &value));
    statistics->ingr_fcs_err = value;
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_EGR_RW_FCS_ERR_CNT, &value));
    statistics->egr_fcs_err = value;
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_INGR_RW_MODFRM_CNT, &value));
    statistics->ingr_frm_mod_cnt = value;
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_EGR_RW_MODFRM_CNT, &value));
    statistics->egr_frm_mod_cnt = value;
    value = 0;

#if 0
    /*yet to chek the LAN80XX_PTP_STI_TS_FIFO_SI_TX_CNT(0) based on channel id */
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_STI_TS_FIFO_SI_TX_CNT(0), &value));
    statistics->ts_fifo_tx_cnt = value;
#endif
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    LAN80XX_PTP_PROC_EGR_TSFIFO_DROP_CNT, &value));
    statistics->ts_fifo_drop_cnt = value;
    return MEPA_RC_OK;
}

#if 0
static mepa_rc lan80xx_phy_ts_csr_adj_1ns_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no, BOOL incr)
{
    u32          value = 0;

    /* read the auto adjust update value register */
    value = 0;
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0),
                                    VTSS_PTP_IP_1588_LTC_LTC_CTRL, &value));
    /* The auto adjust update value is set to 0 after write operation
     * No need to clear the bit before | operation
     */
    value |= VTSS_F_PTP_IP_1588_LTC_LTC_CTRL_LTC_ADD_SUB_1NS_REQ;
    if (incr) {
        value |= VTSS_F_PTP_IP_1588_LTC_LTC_CTRL_LTC_ADD_SUB_1NS;
    } else {
        value = VTSS_PHY_TS_CLR_BITS(value,
                                     VTSS_F_PTP_IP_1588_LTC_LTC_CTRL_LTC_ADD_SUB_1NS);
    }
    VTSS_RC(VTSS_PHY_TS_WRITE_CSR(port_no, VTSS_PHY_TS_PROC_BLK_ID(0),
                                  VTSS_PTP_IP_1588_LTC_LTC_CTRL, &value));

    return VTSS_RC_OK;
}
#endif


mepa_rc lan80xx_phy_ts_event_enable_get(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_ts_event_t *const ev_mask)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc  = MEPA_RC_OK;

    *ev_mask = 0;

    MEPA_ASSERT(ev_mask == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }

        *ev_mask = data->phy_ts_port_conf.event_mask;

    } while (0);
    MEPA_EXIT(dev);

    return rc;
}



mepa_rc lan80xx_phy_ts_event_enable_set(mepa_device_t *dev, const mepa_port_no_t port_no, const BOOL enable, const mepa_ts_event_t ev_mask)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc  = MEPA_RC_OK;
    BOOL mask_changed = FALSE;
    MEPA_ASSERT((ev_mask & ~LAN80XX_PHY_TS_EVENT_MASK));
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        if (enable) {
            mask_changed = (0 != (data->phy_ts_port_conf.event_mask ^ ev_mask));
            data->phy_ts_port_conf.event_mask |= ev_mask;
        } else {
            mask_changed = (0 != (data->phy_ts_port_conf.event_mask & ev_mask));
            data->phy_ts_port_conf.event_mask &= ~ev_mask;
        }
        /* optimization: only update the register if the mask is changed */
        //VTSS_E("port %d, enable %d, mask 0x%x, mask_changed %d", port_no, enable, ev_mask, mask_changed);
        if (mask_changed) {
            rc = lan80xx_ts_csr_set_priv(dev, port_no, LAN80XX_PHY_TS_PORT_EVT_MASK_SET);
        }

    } while (0);

    MEPA_EXIT(dev);
    return rc;

}


mepa_rc lan80xx_phy_ts_event_poll(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_ts_event_t  *const status)
{

    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc  = MEPA_RC_OK;

    MEPA_ASSERT(status == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            *status = 0;
            break;
        }
        rc = lan80xx_phy_ts_csr_event_poll_priv(dev, port_no, status);

    } while (0);

    MEPA_EXIT(dev);
    return rc;
}

mepa_rc lan80xx_phy_ts_stats_get(mepa_device_t *dev, const mepa_port_no_t  port_no, phy25g_phy_ts_stats_t  *const statistics)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc      rc = MEPA_RC_OK;

    MEPA_ASSERT(statistics == NULL);
    MEPA_ENTER(dev);
    do {
        if (data->phy_ts_port_conf.port_ts_init_done == FALSE) {
            rc = MEPA_RC_ERROR;
            break;
        }
        rc = lan80xx_phy_ts_stats_get_priv(dev, port_no, statistics);
    } while (0);

    MEPA_EXIT(dev);
    return rc;
}




/* UNG_MALIBU_25G-2550
On each linkup, the register LINE_PCS25G (Device 0x3 slice registers):VENDOR_PCS_REGISTERS:GB_SHIFT.GB_SHIFT_1 must be read and the ingress_ps_latency must have the following value ADDED to any fixed value for the ingress latency:

Value added: 2 * gb_shift_1 * 0.09697ns
*/

mepa_rc lan80xx_linkup_delay(mepa_device_t *dev)
{
    u32 gb_shift_1, in_delay_ns, in_delay_sns, dly, value = 0;
    float delay;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    MEPA_ENTER(dev);
    LAN80XX_CSR_RD(dev, data->port_no, LAN80XX_LINE_PCS25G_GB_SHIFT, &dly);
    gb_shift_1 = LAN80XX_X_LINE_PCS25G_GB_SHIFT_GB_SHIFT_1(dly);
    delay = (2 * gb_shift_1 * 0.09697);
    in_delay_ns = (u32)delay;
    in_delay_sns = (u32) ((delay - in_delay_ns) * 256);
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY, &dly));
    dly += in_delay_ns;
    value = LAN80XX_X_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_INGR_PS_LOCAL_LATENCY(dly);
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY, &value));
    MEPA_RC(LAN80XX_PHY_TS_READ_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS, &dly));
    dly += in_delay_sns;
    value = LAN80XX_X_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS_INGR_PS_LOCAL_LATENCY_SNS(dly);
    MEPA_RC(LAN80XX_PHY_TS_WRITE_CSR(data->port_no, LAN80XX_PHY_TS_PROC_BLK_ID(0), LAN80XX_PTP_PROC_INGR_PCS_SERDES_LOCAL_LATENCY_SNS, &value));
    MEPA_EXIT(dev);
    return MEPA_RC_OK;

}


mepa_rc lan80xx_mpls_config_set(mepa_device_t *dev, const mepa_port_no_t port_no,
                                BOOL ingress_flow, uint16_t flow_index, BOOL in_cw_en, const phy25g_ts_mpls_flow_conf_t  *const  mpls_conf)
{
    mepa_rc rc;
    phy25g_ts_eng_conf_t *eng_conf;
    phy25g_ts_mpls_flow_conf_t *mpls_flow;
    u16 eng_flow;
    phy25g_ts_engine_t eng_id;
    void *Ptrmem = NULL;

    if (mpls_conf == NULL) {
        return MEPA_RC_ERROR;
    }


    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    if ((rc = lan80xx_get_eng_flow_info(flow_index, &eng_id, &eng_flow) != MEPA_RC_OK)) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid engine ID: %d", eng_id);
        return MEPA_RC_ERROR;
    }

    if (ingress_flow) {

        eng_conf = &data->phy_ts_port_conf.ingress_eng_conf[eng_id];
    } else {
        eng_conf = &data->phy_ts_port_conf.egress_eng_conf[eng_id];
    }

    mpls_flow = &eng_conf->flow_conf.flow_conf.ptp.mpls_opt.flow_opt[eng_flow];


    eng_conf->flow_conf.flow_conf.ptp.mpls_opt.comm_opt.cw_en = in_cw_en;

    mpls_flow->flow_en = mpls_conf->flow_en;
    mpls_flow->stack_depth = mpls_conf->stack_depth;
    mpls_flow->stack_ref_point = mpls_conf->stack_ref_point;

    Ptrmem = memcpy(&mpls_flow->stack_level.top_down, &mpls_conf->stack_level.top_down, sizeof(mpls_flow->stack_level.top_down));

    if (Ptrmem == NULL) {
        return MEPA_RC_ERROR;
    }

    return MEPA_RC_OK;
}




mepa_rc lan80xx_ptp_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr)
{
    u32 mmd = 0;
    mepa_bool_t is_32 = TRUE;
    u32 val1 = 0, val2 = 0;
    pr("\n\n\t\t:-:-:-:  PTP_PROC  :-:-:-:\n\n");
    mmd = MMD_ID_PTP_BLOCK;
    for (u8 i = 0; i < LAN80XX_PTP_PROC_LTC_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_ptp_proc_ltc[i].addr, &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, dump_ptp_proc_ltc[i + 1].addr, &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_ptp_proc_ltc[i].str, val1, dump_ptp_proc_ltc[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  PTP_PROC_INGR  :-:-:-:\n\n");
    mmd = MMD_ID_PTP_BLOCK;
    for (u8 i = 0; i < LAN80XX_PTP_PROC_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_proc[i].addr + LAN80XX_PTP_PROC_INGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_proc[i + 1].addr + LAN80XX_PTP_PROC_INGR_BASE), &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_ptp_proc[i].str, val1, dump_ptp_proc[i + 1].str, val2);
    }

    pr("\n\n\t\t:-:-:-:  PTP_PROC_EGR  :-:-:-:\n\n");
    mmd = MMD_ID_PTP_BLOCK;
    for (u8 i = 0; i < LAN80XX_PTP_PROC_REG_NUM; i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_proc[i].addr + LAN80XX_PTP_PROC_EGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_proc[i + 1].addr + LAN80XX_PTP_PROC_EGR_BASE), &val2));
        pr("%-25s: 0x%08X     %-25s: 0x%08X\n", dump_ptp_proc[i].str, val1, dump_ptp_proc[i + 1].str, val2);
    }

    mmd = MMD_ID_PTP_ANAx;
    pr("\n\n\t\t:-:-:-:  PTP_ANA0_INGR_CFG  :-:-:-:\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);

    pr("\n\n\t\t:-:-:-:  PTP_ANA0_EGR_CFG  :-:-:-:\n\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA0_EGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA0_EGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);


    pr("\n\n\t\t:-:-:-:  PTP_ANA1_INGR_CFG  :-:-:-:\n\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA1_INGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA1_INGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);

    pr("\n\n\t\t:-:-:-:  PTP_ANA1_EGR_CFG  :-:-:-:\n\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA1_EGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA1_EGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);

    pr("\n\n\t\t:-:-:-:  PTP_ANA2_INGR_CFG  :-:-:-:\n\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA2_INGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA2_INGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);

    pr("\n\n\t\t:-:-:-:  PTP_ANA2_EGR_CFG  :-:-:-:\n\n\n");
    for (u32 i = 0; i < (LAN80XX_PTP_ANA_REG_NUM - 1); i = i + 2) {
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i].addr + LAN80XX_PTP_ANA2_EGR_BASE), &val1));
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[i + 1].addr + LAN80XX_PTP_ANA2_EGR_BASE), &val2));
        pr("%-40s: 0x%08X     %-40s: 0x%08X\n", dump_ptp_ana[i].str, val1, dump_ptp_ana[i + 1].str, val2);
    }
    MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, is_32, (dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].addr + LAN80XX_PTP_ANA0_INGR_BASE), &val1));
    pr("%-40s: 0x%08X\n", dump_ptp_ana[LAN80XX_PTP_ANA_REG_NUM - 1].str, val1);

    return MEPA_RC_OK;
}
