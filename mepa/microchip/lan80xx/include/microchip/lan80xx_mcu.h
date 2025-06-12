// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This file declares the lan8042 MCU chip specic APIs and corresponding
// data structures



#ifndef _LAN80XX_MCU_H_
#define _LAN80XX_MCU_H_

// The following .h file needed
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>

#define BIT0                                0x00000001UL
#define BIT1                                0x00000002UL
#define BIT3                                0x00000008UL
#define BIT21                               0x00200000UL

#define RESERVED_ID                         (0xFFu)
#define MB_PKT_DATA_OFFSET                  4
#define MB_MAX_CRC_LEN                      2
#define CRC_START_CCITT                     0xFFFF
#define CRC_POLY_CCITT                      0x1021
#define SPI_CMD_LEN                         7
#define SPI_VAL_LEN                         4

#define BLOCK_LVL_SOFT_RESET2               (0x203)
#define SW_RESET_MCU                        (0x02)
#define GPIO_INTR_CFG_STAT                  (0xF20E)
#define INTR_SRC_EN_0                       (GPIO_INTR_CFG_STAT + 0x0)
#define INTR_SRC_EN_1                       (GPIO_INTR_CFG_STAT + 0x1)
#define GPIO_MCU_MBOX_INT_EN                (BIT21)
#define MAILBOX_CMD_ADDR                    0xD800
#define MAILBOX_RESP_ADDR                   0xD900
#define MAILBOX_FLAG_REGISTER               0xDA00
#define MAILBOX_MCU_INTR_MASK_REGISTER      0xDA01
#define MAILBOX_HOST_INTR_MASK_REGISTER     0xDA02
#define MAILBOX_FLAG_SET_BIT0               0x00010000
#define MAILBOX_FLAG_SET_BIT7               0x00800000
#define MAILBOX_INTR_ENABLE                 0x00000001
#define MAILBOX_INTR_DISABLE                0x00000000
#define MAILBOX_HOST_INTR_MASK              0x00000002
#define MAILBOX_DFU_FIRST_PKT               0x00000040
#define MAILBOX_DFU_LAST_PKT                0x00000080
#define MAILBOX_FLAG_CLEAR_BIT0_BIT1        0x03000000
#define MAILBOX_FLAG_CLEAR_BIT1             0x02000000
#define MAILBOX_FLAG_CLEAR_BIT0             0x01000000
#define MAILBOX_FLAG_CLEAR_BIT6             0x40000000
#define MALIBOX_FALG_CLEAR_ALL              0xFF000000
#define DFU_INTR_ENABLE                     0x00000080
#define MAILBOX_INTR_TIMEOUT                50000 /*50 msecs timeout to recv intr*/
#define MAILBOX_INTR_SIGN_TIMEOUT           2000 /* 2 secs for sign vaerifiction commands*/
#define MCU_DATA_RAM_OFFSET                 0x00080000
#define DFU_STATUS_REG_OFFSET               0x04
#define DFU_SIGN_VERIFY_FAIL_POS            BIT3

/* Maximum length of the message data */
#define MB_MAX_PKT_HEADER_LEN               4
#define MB_MAX_PAYLOAD_LEN                  1018
#define MB_MAX_PKT_LEN                      (MB_MAX_PAYLOAD_LEN + MB_MAX_PKT_HEADER_LEN + MB_MAX_CRC_LEN)

#define STRAP_INFO                          0x200
#define STRAP_READ_REG                      (STRAP_INFO + 0x00)
#define STRAP_OVERRIDE_REG                  (STRAP_INFO + 0x01)

#define DFU_STRAP                           (BIT0)
#define SERDES_INIT_STRAP                   (BIT1)

#define MAX_OTP_CFG_RECORDS                 64
#define MAX_OTP_SIZE                        (0x4000u)

#define OTP_CONFIG_REGION_LEN               (0x3000u)
#define OTP_PRG_CTR_SIZE                    (0x8U)

#define OTP_CFG_RECORD_LEN                  0x1014
#define OTP_IDX_RECORD_LEN                  0x08U
#define OTP_SIGNATURE_LEN                   0X40

#define OTP_REP_KEY_LEN                     0x40
#define OTP_REP_KEY_SIGN_LEN                0x40
/* Keeping 16 maximum of buffered updates to RAM OTP */
#define MAX_RAM_OTP_UPDATES                 (16)
/* OTP FW Registers */
#define OTP_PRG_CTR                         0x0100U // 8 Bytes
#define OTP_MCHP_PUB_KEY                    0x0108U // 64 Bytes
#define OTP_ROT_KEY                         0x0148U // 64 Bytes
#define OTP_REPLACEMENT_KEY1                0x0188U // 64 Bytes
#define OTP_REPLACEMENT_KEY1_SIGN           0x01C8U // 64 Bytes
#define OTP_REPLACEMENT_KEY2                0x0208U // 64 Bytes
#define OTP_REPLACEMENT_KEY2_SIGN           0x0248U // 64 Bytes
#define OTP_REPLACEMENT_KEY3                0x0288U // 64 Bytes
#define OTP_REPLACEMENT_KEY3_SIGN           0x02C8U // 64 Bytes
#define OTP_KEY_REVOCATION                  0x0308U // 1 Byte
#define OTP_REPLACEMENT_KEY_CTR             0x0309U // 1 Byte

/* OTP configuration start address */
#define OTP_CONFIG_START                    0x100U
#define OTP_HEADER_DATA_OFFSET              0x400U

/* OTP Key status */
#define KEY_CTR_MCHP_PUB_KEY_VAL            0x00
#define KEY_CTR_REPLACEMENT_KEY1_VAL        0x01
#define KEY_CTR_REPLACEMENT_KEY2_VAL        0x03
#define KEY_CTR_REPLACEMENT_KEY3_VAL        0x07
#define KEY_CTR_NONE                        0x0F

#define LAN80XX_MCU_CODE_RAM_START_REGION         (0x00040000U)
#define LAN80XX_MEMORY_SLICE_ONE_OFFSET             0x10000
#define LAN80XX_MEMORY_SLICE_TWO_OFFSET             0x20000
#define LAN80XX_MEMORY_SLICE_THREE_OFFSET           0x30000

#define MAKEWORD(a, b)      ((uint16_t)(((uint8_t)(((unsigned long)(a)) & 0xff)) | ((uint16_t)((uint8_t)(((unsigned long)(b)) & 0xff))) << 8))


typedef enum DEVICE_COMMANDS {
    /* m25g_device commands */
    eGET_DEVICE_INFO = 0x00,
    eDEVICE_RESET,
    /* UART related commands */
    eUART_GET_CONFIG,
    eUART_SET_CONFIG,
    /* WDT related commands */
    eWDT_DISABLE,
    eWDT_LOCK,
    /* Memory related commands */
    eMEM_READ,
    eMEM_WRITE,
    /* OTP related commands */
    eOTP_CFG_READ,
    eOTP_WRITE,
    eOTP_READ,
    /* DFU related commands */
    eDFU_UPDATE,
    /* Replacement key */
    ePROG_OTP_KEY1,
    ePROG_OTP_KEY2,
    ePROG_OTP_KEY3,
    eREVOKE_OTP_KEYS,
    eREVOKE_ROT_KEY,
    eOTP_KEY_STATUS,
    /* KR related commands */
    ePORT_RESTART_ANEG,
    eSET_PORT_ANEGKR_CFG,
    eGET_PORT_ANEGKR_CFG,
    /* WDT enable Command */
    eWDT_ENABLE,
    /* KR Logging Enable command */
    eENABLE_KR_LOG,
    eRESET_KR_LOG_MEMORY,
    eANEGKR_ENABLE,
    eENABLE_UART_LOG,
    eTEMPERATURE_SENSOR_THRESHOLD,
    eSET_SERDES_CONFIG,
    eGET_SERDES_CONFIG,
    /* Protocol test command */
    eTEST_COMM = 0x70,
    /* Unknown command ID, add new cmd ids above this. Keep this as last */
    eUNKNOWN_CMD_ID,

} enDEVICE_COMMANDS_T;

typedef struct PACKET_HEADER {
    /* packet id */
    uint8_t u8PktId;
    /* Reserved */
    uint8_t u8Reserved;
    /* packet length */
    uint16_t u16PktLen;
} PKT_HDR_T;

typedef enum IMAGE_TYPE {
    eIMG_BOOTLOADER = 0x01,
    eIMG_BOOTROM_APP,
    eIMG_DFU_APP,
} enIMAGE_TYPE_T;

typedef struct DeviceInfo {
    uint16_t PartId;
    uint8_t TargetId;
    uint8_t ImageType;
    uint16_t FirmwareVersion;
} DEVICE_INFO;

typedef enum OTP_Key_Counter {
    eMCHP_PUB_KEY = 0x0,
    eREPLACEMENT_KEY1 = 0x01,
    eREPLACEMENT_KEY2 = 0x03,
    eREPLACEMENT_KEY3 = 0x07,
    eALL_KEYS_COMPROMISED = 0x0F,
} enOTP_ACTIVE_KEY;

typedef struct OTPRAMUpdatedDB {
    uint16_t    u16Offset;
    uint16_t    u16Len;

} OTPRAMUpdatedDB_t;

/*
 * Reserved Byte    - specifies the type of write operation
 *      0xFF        - eOTPWRITE_RAW, Raw Write
 *      0xFE        - eOTPWRITE_BUFF, Buffered write
 *      0xFD        - eOTPWRITE_AUTH, Authenticated write
 */
typedef enum OTPWRITE_MODE {
    eOTPWRITE_RAW = 0xFF,
    eOTPWRITE_BUFF = 0xFE,
    eOTPWRITE_AUTH = 0xFD,

} enOTPWRITE_MODE_T;

typedef struct KR_port_Config {
    u32 b10g_fec_req : 1;           // Request R-FEC
    u32 b10g_fec_Ability : 1;       // 10G FEC ability
    u32 b25gR_fec_req : 1;          // 25G Request R-FEC
    u32 b25gRs_fec_req : 1;         // Request RS-FEC (25G)
    u32 bAdv_1g : 1;                // Advertise 1G
    u32 bAdv_10g : 1;               // Advertise 10G
    u32 bAdv_25g_kr_s : 1;          // Advertise 25G_KR_S
    u32 bAdv_25g_kr : 1;            // Advertise 25G_KR
    u32 bNextPage : 1;              // Next Page
    u32 bNP_25G_KR : 1;             // Next Page ability 25G KR
    u32 bNP_25G_CR : 1;             // Next Page ability 25G CR
    u32 bNP_f1_91_fec : 1;          // Next Page ability 91 fec
    u32 bNP_f2_74_fec : 1;          // Next Page ability 74 fec
    u32 bFWhcd_resolve : 1;         // FW resolve HCD
    u32 bSerdes_64bit_mode : 1;     // Serdes 64 bit mode
    u32 bAnegEnable : 1;            // Autoneg enable
    u32 bBypassTraining : 1;        // Bypass KR training
    u32 bBEREnable : 1;             //BER enable
    u32 bEyeHeightEnable : 1;       //Eye height enable
    u32 wReserved : 13;

} KR_PORT_CONF;

typedef struct KR_Port {
    u8 byLP0: 1;
    u8 byLP1: 1;
    u8 byLP2: 1;
    u8 byLP3: 1;
    u8 byHP0: 1;
    u8 byHP1: 1;
    u8 byHP2: 1;
    u8 byHP3: 1;
} KR_PORT;

typedef enum SD_CFG_SPEED_IDX {
    SD_CFG_1G = 0,
    SD_CFG_10G,
    SD_CFG_25G,
    SD_UNKNOWN_SPEED,

} SD_CFG_SPEED_IDX_t;

typedef enum SERDES_CFG {
    eTX_EQ_CFG = 0x0,
    eCDR_CFG,
    eSPEED_CHANGE_CFG,
    eRX_EQ_CFG,
    eDFE_CFG,
    ePOL_SQ_CFG,
    eTX_SWING_CFG,
    eMISC_CFG,
    eUNKNOWN_CFG,
    eALL_CFG = 0xFF,

} eSERDES_CFG_T;

typedef struct tx_eq_cfg {
    u8 Tap_dly;
    u8 Tap_main;
    u8 Tap_adv;
    u8 En_main;
    u8 En_adv;
    u8 En_dly;

} tx_eq_cfg_t;

typedef struct cdr_cfg {
    u8 Cdr_m;
    u8 Alos_thr;

} cdr_cfg_t;

typedef struct speed_change_cfg {
    u8 L0_cfg_tx_reserve_15_8;
    u8 L0_cfg_tx_reserve_7_0;
    u8 Ln_cfg_tx_reserve_15_8;
    u8 Ln_cfg_tx_reserve_7_0;

} speed_change_cfg_t;

typedef struct rx_eq_cfg {
    u8 Ln_cfg_vga_ctrl_byp;
    u8 Ln_cfg_vga_byp;
    u8 Ln_cfg_eqr_force;
    u8 Ln_cfg_eqc_force;

} rx_eq_cfg_t;

typedef struct dfe_cfg {
    u8 Ln_cfg_dfeck_en;
    u8 Ln_cfg_dfe_pd;
    u8 Ln_cfg_dfemx_pd;
    u8 Ln_cfg_dfe_dmux_pd;
    u8 Ln_cfg_pi_dfe_en;
    u8 Ln_cfg_dfedig_m;
    u8 Ln_cfg_dfetap_en;
    u8 Ln_cfg_en_dfedig;

} dfe_cfg_t;

typedef struct pol_sq_cfg {
    u8 Tx_pol_inv;
    u8 Rx_pol_inv;
    u8 Ln_cfg_dis_sq;
    u8 Ln_cfg_pd_sq;

} pol_sq_cfg_t;

typedef struct tx_swing_cfg {
    u8 Itx_ipdriver_base;

} tx_swing_cfg_t;

typedef struct misc_cfg {
    u8 Cfg_common_reserve;
    u8 Cfg_jc_byp;
    u8 Cfg_pll_lol_set;
    u8 Cfg_en_dummy;
    u8 Cfg_pll_reserve;
    u8 R_dwidthctrl_from_hwt;
    u8 R_reg_manual;
    u8 Vco_div_mode;
    u8 Pre_divsel;
    u8 Cfg_seldiv;
    u8 Data_width_sel;
    u8 Txfifo_ck_div;
    u8 Rxfifo_ck_div;
    u8 Pma_txck_sel;
    u8 Tx_prediv;
    u8 Rxdiv_sel;
    u8 Txrate_sel;
    u8 Rxrate_sel;
    u8 Ln_cfg_cdrck_en;
    u8 Ln_cfg_dmux_pd;
    u8 Ln_cfg_dmux_clk_pd;
    u8 Ln_cfg_erramp_pd;
    u8 Ln_cfg_pi_en;
    u8 Ln_cfg_pd_ctle;
    u8 Ln_cfg_summer_en;
    u8 Ln_cfg_pmad_ck_pd;
    u8 Ln_cfg_pd_clk;
    u8 Ln_cfg_pd_cml;
    u8 Ln_cfg_pd_driver;
    u8 Ln_cfg_rx_reg_pu;
    u8 Ln_cfg_pd_rms_det;
    u8 Ln_cfg_dcdr_pd;
    u8 Ln_cfg_ecdr_pd;
    u8 L0_cfg_bw;
    u8 L0_cfg_txcal_en;
    u8 Ln_cfg_bw;
    u8 Ln_cfg_txcal_man_en;
    u8 Ln_cfg_phase_man;
    u8 Ln_cfg_quad_man;
    u8 Ln_cfg_txcal_shift_code;
    u8 Ln_cfg_txcal_valid_sel;
    u8 Ln_cfg_cdr_kf;
    u8 Ln_cfg_pi_bw;
    u8 Ln_cfg_pi_steps;
    u8 Ln_cfg_dis_2ndorder;
    u8 Ln_cfg_rx_reserve_7_0;
    u8 Ln_cfg_rx_reserve_15_8;
    u8 Ln_cfg_rx_term;
    u8 Ln_cfg_rx_sp_ctle;
    u8 Ln_cfg_isel_ctle;
    u8 Ln_cfg_eqr_byp;
    u8 Ln_cfg_agc_adpt_byp;
    u8 Ln_cfg_sum_setcm_en;
    u8 Ln_cfg_init_pos_iscan;
    u8 Ln_cfg_init_pos_iPI;
    u8 Cfg_i_vco;
    u8 Icp_base_sel;
    u8 Icp_sel;
    u8 Cfg_rsel;
    u8 Ln_cfg_iscan_en;
    u8 Ln_cfg_en_fast_iscan;
    u8 Ln_cfg_filter2nd_yz_6_0;
    u8 Ln_r_alos_en;

} misc_cfg_t;

typedef struct SERDES_CONFIG {
    tx_eq_cfg_t         sTx_eq_cfg;
    cdr_cfg_t           sCdr_cfg;
    speed_change_cfg_t  sSpeed_change_cfg;
    rx_eq_cfg_t         sRx_eq_cfg;
    dfe_cfg_t           sDfe_cfg;
    pol_sq_cfg_t        sPol_sq_cfg;
    tx_swing_cfg_t      sTx_swing_cfg;
    misc_cfg_t          sMisc_cfg;

} __SERDES_CONFIG_T;

typedef uint8_t (*gpio_callback_t) (void);

mepa_rc lan80xx_MB_INTR_register_callback(const mepa_device_t *dev, gpio_callback_t gpio_cb);

mepa_rc lan80xx_mcu_mailbox_init(const mepa_device_t *dev, u32 u32McuIntMask, u32 u32HostIntMask);

mepa_rc lan80xx_otp_cfg_program(const mepa_device_t  *dev,
                                u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_cfg_read(const mepa_device_t  *dev,
                             u8 u8RecIdx,
                             u8 *pu8Cfg,
                             u16 *pu16Len);

mepa_rc lan80xx_otp_prog_RepKey(const mepa_device_t  *dev,
                                u8 *pu8SignedKey,
                                u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_revoke_ROTKey(const mepa_device_t  *dev,
                                  u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_revoke_AllKeys(const mepa_device_t  *dev,
                                   u8 *pu8OTPBuffer, OTPRAMUpdatedDB_t *pCfgUpdates, u8 u8UpdateCnt);

mepa_rc lan80xx_otp_getKey_Status(const mepa_device_t  *dev,
                                  enOTP_ACTIVE_KEY *pKey);

mepa_rc lan80xx_otp_read(const mepa_device_t  *dev,
                         u8 *pu8Data,
                         u16 u16Offset,
                         const u16 u16Len);

/* lan80xx_mcu_reset - API to reset MCU*/
mepa_rc lan80xx_mcu_reset(const mepa_device_t *dev);

/* lan80xx_get_fw_info - API to get Firmware info (Part ID, Target ID, Image Type, Firmware Version)*/
mepa_rc lan80xx_get_fw_info(const mepa_device_t *dev, DEVICE_INFO *psDevInfo);

mepa_rc lan80xx_memory_read(const mepa_device_t *dev, uint32_t u32Addres, uint8_t *pu8Data, const uint16_t u16Len);
mepa_rc lan80xx_memory_write(const mepa_device_t *dev, uint32_t u16Addres, uint8_t *pu8Data, const u16 u16Len);
mepa_rc lan80xx_fw_update(mepa_device_t *dev);

#if 0
/* TODO: Below need to add definitions */
mepa_rc lan80xx_ANEG_GetConfig(const mepa_device_t  *dev, KR_PORT_CONF *psConfig);
mepa_rc lan80xx_ANEG_SetConfig(const mepa_device_t  *dev, KR_PORT sPort, KR_PORT_CONF sConfig);
mepa_rc lan80xx_ANEG_Enable(const mepa_device_t  *dev);
mepa_rc lan80xx_ANEG_Disable(const mepa_device_t  *dev);

mepa_rc lan80xx_KRLog_Enable(const mepa_device_t  *dev, KR_PORT sPort);
mepa_rc lan80xx_KRLog_Reset(const mepa_device_t  *dev);
#endif

uint16_t lan80xx_CreatePacket(uint8_t u8PacketId, uint16_t u16CmdParamLen, uint8_t *pu8PktBuf, uint8_t *pu8CmdData, uint8_t u8Reserved);
mepa_rc lan80xx_MB_SendRequest(const mepa_device_t *dev, uint8_t *au8CmdPkt, uint16_t u16DataLen);
mepa_rc lan80xx_MB_ReadResponse(const mepa_device_t *dev, uint8_t *u8ResponsePkt, uint16_t *u16PayloadLen, uint16_t u16MailboxTimeout);
mepa_rc lan80xx_ValidatePacket(uint8_t *u8PktBuf);
mepa_rc lan80xx_check_mcu_rdy(mepa_device_t *dev);

mepa_rc lan80xx_get_serdes_config(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, __SERDES_CONFIG_T *const data);
mepa_rc lan80xx_set_serdes_config(const mepa_device_t *dev, SD_CFG_SPEED_IDX_t speed, eSERDES_CFG_T cfgType, const __SERDES_CONFIG_T *data);

#endif //  end of _LAN80XX_MCU_H_
