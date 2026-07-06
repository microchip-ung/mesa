// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"
#include "cli.h"
#include "phy_only.h" /* phy_only_mdint_register() */

#include "lan80xx_mcu.h"
#include "lan80xx_mcu_otp_cfgWrite.h"
#include "lan80xx_mcu_otp_KeyWrite.h"
#include "lan80xx_mcu_otp_RevokeAllKeys.h"
#include "lan80xx_mcu_otp_RevokeROTKey.h"

#define HOST_INTR_B (6)

static meba_inst_t gmeba_inst;
uint8_t            gau8Data[0x4000];
char              *image_type[] = {"None", "Bootloader", "Bootrom", "DFU"};

static mscc_appl_trace_module_t trace_module = {.name = "mcu_fw"};

enum { TRACE_GROUP_DEFAULT, TRACE_GROUP_CNT };

typedef struct otp_cli_req {
    uint16_t otpAddr;
    uint16_t otpLen;
    uint8_t  cfg_idx;
} otp_cli_req_t;

typedef struct mcu_cli_req {
    uint32_t Addr;
    uint32_t Len;
} mcu_cli_req_t;

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {.name = "default", .level = MESA_TRACE_LEVEL_ERROR},
};

////////////////////////////////////////////////////////////
/////////////////   CLI Command functions   ////////////////
////////////////////////////////////////////////////////////

static void cli_cmd_get_fw_info(cli_req_t *req)
{
    mesa_rc        rc = MESA_RC_OK;
    mepa_device_t *dev = NULL;
    DEVICE_INFO    sInfo;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("Getting mcu fw info...\n");
    rc = lan80xx_get_fw_info(dev, &sInfo);
    if (rc != MESA_RC_OK) {
        cli_printf("FW info get failed\n");
    } else {
        cli_printf("FW info get success\n");
        cli_printf("Part ID: 0x%x\n", sInfo.PartId);
        cli_printf("Target ID: 0x%x\n", sInfo.TargetId);
        cli_printf("Image Type: %s\n", image_type[sInfo.ImageType]);
        cli_printf("Firmware Version: %02d.%02d\n", (sInfo.FirmwareVersion >> 8),
                   (sInfo.FirmwareVersion & 0xFF));
    }
}

static void cli_cmd_mcu_reset(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;

    dev = gmeba_inst->phy_devices[req->port_no];

    cli_printf("sending mcu reset request...\n");
    rc = lan80xx_mcu_reset(dev);
    if (rc != MEPA_RC_OK) {
        cli_printf("mcu reset failed: %d\n", rc);
    } else {
        cli_printf("MCU reset done\n");
    }

    return;
}

static void cli_cmd_mcu_fw_update(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("Firmware update\n");
    rc = lan80xx_fw_update(dev);
    if (rc != MESA_RC_OK) {
        cli_printf("Firmware update failed (%d)\n", rc);
    } else {
        cli_printf("Firmware update done\n");
    }
}

void Dumpdata(u8 *pu8Data, u32 u32Len)
{
    int i, j;

    cli_printf("Dumping data...\n");
    for (i = 0, j = 1; i < u32Len; i++, j++) {
        cli_printf("0x%02x ", pu8Data[i]);
        if (j % 16 == 0) {
            cli_printf("\n");
        }
    }
    cli_printf("\n");
}

static void cli_cmd_mcu_otp_read(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;
    otp_cli_req_t *mreq = req->module_req;

    dev = gmeba_inst->phy_devices[req->port_no];
    if (mreq->otpLen == 0) {
        mreq->otpLen = MB_MAX_PAYLOAD_LEN;
    }
    cli_printf("otp read @0x%x of len 0x%x\n", mreq->otpAddr, mreq->otpLen);
    rc = lan80xx_otp_read(dev, gau8Data, mreq->otpAddr, mreq->otpLen);
    if (rc != MESA_RC_OK) {
        cli_printf("Otp read failed (%d)\n", rc);
    } else {
        cli_printf("OTP read done\n");
        Dumpdata(gau8Data, mreq->otpLen);
    }

    return;
}

static void cli_cmd_mcu_otp_cfg_read(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;
    otp_cli_req_t *mreq = req->module_req;
    uint16_t       u16CfgLen = 0;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp cfg read with record index %d\n", mreq->cfg_idx);
    rc = lan80xx_otp_cfg_read(dev, mreq->cfg_idx, gau8Data, &u16CfgLen);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP cfg read failed (%d)\n", rc);
    } else {
        cli_printf("OTP Cfg read success with len: %u\n", u16CfgLen);
        Dumpdata(gau8Data, u16CfgLen);
    }
}

static void cli_cmd_mcu_otp_cfg_write(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;
    uint16_t       u16CfgLen = 0;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp cfg write...\n");
    rc = lan80xx_otp_cfg_program(dev, gau8OTPCfgData, &gOTPCfgUpdates[0], gOTPCfgUpdateCnt);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP cfg write failed (%d)\n", rc);
    } else {
        cli_printf("OTP Cfg write success with len: %u\n", u16CfgLen);
    }
}

static void cli_cmd_mcu_otp_key_status(cli_req_t *req)
{
    mesa_rc          rc;
    mepa_device_t   *dev;
    enOTP_ACTIVE_KEY sKey;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp get key status...\n");
    rc = lan80xx_otp_getKey_Status(dev, &sKey);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP get key status failed (%d)\n", rc);
    } else {
        cli_printf("OTP get key status success\n");
        switch (sKey) {
        case eMCHP_PUB_KEY:
            /* MCHP Public key */
            cli_printf("MCHP Public key is active\n");
            break;
        case eREPLACEMENT_KEY1:
            /* Reaplcement key 1 */
            cli_printf("Replacement key 1 is active\n");
            break;
        case eREPLACEMENT_KEY2:
            /* Reaplcement key 2 */
            cli_printf("Replacement key 2 is active\n");
            break;
        case eREPLACEMENT_KEY3:
            /* Reaplcement key 3 */
            cli_printf("Replacement key 3 is active\n");
            break;
        case eALL_KEYS_COMPROMISED:
            /* Key None, all keys revoked */
            cli_printf("All Keys compromised\n");
            break;
        default:
            /* Unknown data, Needs protocol update */
            cli_printf("Needs protocol update!!\n");
            break;
        }
    }
}

static void cli_cmd_mcu_otp_key_write(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp key write...\n");
    rc = lan80xx_otp_prog_RepKey(dev, &gau8OTPKeyData[gKeyOffset], gau8OTPKeyData,
                                 &gOTPKeyUpdates[0], gOTPKeyUpdateCnt);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP key write failed (%d)\n", rc);
    } else {
        cli_printf("OTP key write success\n");
    }
}

static void cli_cmd_mcu_otp_revoke_rot_key(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp revoke rot key...\n");
    rc = lan80xx_otp_revoke_ROTKey(dev, gau8OTPRevokeROTData, &gOTPRevokeROTUpdates[0],
                                   gOTPRevokeROTUpdateCnt);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP ROT key revoke failed (%d)\n", rc);
    } else {
        cli_printf("OTP ROT key revoke success\n");
    }
}

static void cli_cmd_mcu_otp_revoke_all_keys(cli_req_t *req)
{
    mesa_rc        rc;
    mepa_device_t *dev;

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("otp revoke all keys...\n");
    rc = lan80xx_otp_revoke_AllKeys(dev, gau8OTPRevokeAllData, &gOTPRevokeAllUpdates[0],
                                    gOTPRevokeAllUpdateCnt);
    if (rc != MESA_RC_OK) {
        cli_printf("OTP revoke all keys failed (%d)\n", rc);
    } else {
        cli_printf("OTP revoke all keys success\n");
    }
}

static void cli_cmd_mcu_mem_read(cli_req_t *req)
{
    mepa_rc        rc;
    mepa_device_t *dev;
    mcu_cli_req_t *mreq = req->module_req;
    uint8_t        au8Data[MB_MAX_PKT_LEN];

    dev = gmeba_inst->phy_devices[req->port_no];
    cli_printf("mem read @0x%x of len 0x%x\n", mreq->Addr, mreq->Len);
    rc = lan80xx_memory_read(dev, mreq->Addr, au8Data, mreq->Len);
    if (rc != MESA_RC_OK) {
        cli_printf("MEM read failed (%d)\n", rc);
    } else {
        cli_printf("MEM read success\n");
        Dumpdata(au8Data, mreq->Len);
    }
}

////////////////////////////////////////////////////////////
/////////////////   CLI Parameter functions ////////////////
////////////////////////////////////////////////////////////

static int cli_parm_otp_offset(cli_req_t *req)
{
    otp_cli_req_t *mreq = req->module_req;

    return cli_parm_u16(req, &mreq->otpAddr, 0, 0x3FFF);
}

static int cli_parm_otp_length(cli_req_t *req)
{
    otp_cli_req_t *mreq = req->module_req;

    return cli_parm_u16(req, &mreq->otpLen, 1, 0x3FFF);
}

static int cli_parm_mcu_offset(cli_req_t *req)
{
    mcu_cli_req_t *mreq = req->module_req;

    return cli_parm_u32(req, &mreq->Addr, 0, 0xFFFFFFFF);
}

static int cli_parm_mcu_length(cli_req_t *req)
{
    mcu_cli_req_t *mreq = req->module_req;

    return cli_parm_u32(req, &mreq->Len, 1, 0xFFFFFFFF);
}

static int cli_parm_otp_cfg_idx(cli_req_t *req)
{
    otp_cli_req_t *mreq = req->module_req;

    return cli_parm_u8(req, &mreq->cfg_idx, 0, 63);
}

/* Bind the LAN80xx mailbox host-interrupt to a host GPIO line (edge events)
 * instead of polling the flag over SPI. The INTR line is board-specific: taken
 * from $LAN80XX_MDINT, else the built-in default -- either a DT line name
 * (gpio-line-names, probed across all gpiochips) or an explicit "<chip>:<line>".
 * After this, the mailbox/DFU wait on the real interrupt. */
static void cli_cmd_mcu_intr_gpio(cli_req_t *req)
{
    mepa_device_t *dev = gmeba_inst->phy_devices[req->port_no];

    if (dev == NULL) {
        cli_printf("Dev not created for port %u\n", req->port_no);
        return;
    }
    if (phy_only_mdint_register(dev, NULL) == MESA_RC_OK) {
        cli_printf("mcu intr: port %u mailbox INTR bound to host GPIO "
                   "($LAN80XX_MDINT, else the built-in default)\n",
                   iport2uport(req->port_no));
    } else {
        cli_printf("mcu intr: port %u GPIO INTR bind failed (see trace)\n",
                   iport2uport(req->port_no));
    }
}

static cli_cmd_t cli_cmd_table[] = {
    {"PHY MCU fw info <port_no>",                     "get mcu firmware information",               cli_cmd_get_fw_info            },
    {"PHY MCU intr <port_no>",
     "bind mailbox host-interrupt to a host GPIO (edge events); DT line name or <chip>:<line> from $LAN80XX_MDINT, else the built-in default",
     cli_cmd_mcu_intr_gpio                                                                                                         },
    {"PHY MCU reset <port_no>",                       "reset mcu via soft reset",                   cli_cmd_mcu_reset              },
    {"PHY MCU fw update <port_no>",                   "mcu firmware update",                        cli_cmd_mcu_fw_update          },
    {"PHY MCU otp read <port_no> [<offset>] [<len>]", "read OTP memory through mcu",
     cli_cmd_mcu_otp_read                                                                                                          },
    {"PHY MCU otp cfg read <port_no> <cfg_idx>",
     "read OTP configuration/record for the requested number through mcu",                          cli_cmd_mcu_otp_cfg_read       },
    {"PHY mcu otp cfg write <port_no>",               "write OTP configuration/record through mcu",
     cli_cmd_mcu_otp_cfg_write                                                                                                     },
    {"PHY MCU otp key status <port_no>",              "get current active signing key status",
     cli_cmd_mcu_otp_key_status                                                                                                    },
    {"PHY MCU otp key write <port_no>",               "program the new signing key",                cli_cmd_mcu_otp_key_write      },
    {"PHY MCU otp revoke rot <port_no>",              "revoke rot key",                             cli_cmd_mcu_otp_revoke_rot_key },
    {"PHY MCU otp revoke all <port_no>",              "revoke all keys",                            cli_cmd_mcu_otp_revoke_all_keys},
    {"PHY MCU mem read <port_no> <m_offset> <m_len>", "read OTP memory through mcu",
     cli_cmd_mcu_mem_read                                                                                                          },
};

static cli_parm_t cli_parm_table[] = {
    {"<offset>",   "offset address, default: (0x0 - 0x3FFF)", CLI_PARM_FLAG_NONE,
     cli_parm_otp_offset                                                                              },
    {"<len>",      "length, default: (0x0 - 0x3FFF)",         CLI_PARM_FLAG_NONE, cli_parm_otp_length },
    {"<cfg_idx>",  "cfg record number (0 - 63)",              CLI_PARM_FLAG_NONE, cli_parm_otp_cfg_idx},
    {"<m_offset>", "offset address",                          CLI_PARM_FLAG_NONE, cli_parm_mcu_offset },
    {"<m_len>",    "length",                                  CLI_PARM_FLAG_NONE, cli_parm_mcu_length },
};

////////////////////////////////////////////////////////////
/////////////// Core init functions ////////////////////////
////////////////////////////////////////////////////////////

static void mcu_fw_cli_init(void)
{
    int i;

    /* Register commands */
    for (i = 0; i < sizeof(cli_cmd_table) / sizeof(cli_cmd_t); i++) {
        mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
    }
    /* Register parameters */
    for (i = 0; i < sizeof(cli_parm_table) / sizeof(cli_parm_t); i++) {
        mscc_appl_cli_parm_reg(&cli_parm_table[i]);
    }
}

void mscc_appl_mcu_fw_init(mscc_appl_init_t *init)
{
    gmeba_inst = init->board_inst;
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT: mcu_fw_cli_init(); break;

    default: break;
    }
}
