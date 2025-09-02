// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_private.h"
#include "lan80xx_types.h"
#include "regs_lan80xx_macsec_egr.h"
#include "regs_lan80xx_macsec_ingr.h"
#include "regs_lan80xx_host_mac.h"
#include "regs_lan80xx_line_mac.h"
#include "regs_lan80xx_line_slice.h"
#include "regs_lan80xx_line_intr_ctrl.h"
#include "lan80xx_macsec_private.h"
#include "lan80xx_macsec.h"
#include "lan80xx_regs_util.h"
#include "regs_lan80xx_mcu_io_mngt_misc.h"

#if defined (MEPA_LAN80XX_MSEC)

#define LAN80XX_EGR_INGR_REG_EXPAN(front, egr, back) ((egr) ? (front##_MACSEC_EGR_##back) : (front##_MACSEC_INGR_##back)) /* Macro to expand EGR or INGR register based on egr */

#define MACSEC_BS(x) ( (((x) >> 8U) & 0x00FFU) | (((x) << 8U) & 0xFF00U) )

/* Use do-while(0) for statement macros */
#define LAN80XX_MACSEC_ASSERT(x, _txt) \
    do { \
        if ((x)) { \
            T_E(MEPA_TRACE_GRP_GEN, "%s", (_txt)); \
            return MEPA_RC_ERROR; \
        } \
    } while (0)

#define MACSEC_RC_COLD(expr) ( ((data)->sync_calling_private) ? (MEPA_RC_OK) : (expr) )
#define LAN80XX_MACSEC_PORT_ARG(X) ((X)->port_no), ((X)->service_id), ((X)->port_id)
#define MACSEC_PORT_FMT "%u/%u/%u"
#define MACADDRESS_FMT "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
#define MACADDRESS_ARG(X) ((X).addr[0]), ((X).addr[1]), ((X).addr[2]), \
                          ((X).addr[3]), ((X).addr[4]), ((X).addr[5])

#define LAN80XX_SCI_FMT MACADDRESS_FMT "#%u"
#define LAN80XX_SCI_ARG(X) MACADDRESS_ARG((X).mac_addr), ((X).port_id)
#define LAN80XX_MPORT_SCI_FMT "Port: " MACSEC_PORT_FMT ", SCI: " LAN80XX_SCI_FMT
#define LAN80XX_MPORT_SCI_ARG(P, S) LAN80XX_MACSEC_PORT_ARG(&(P)), LAN80XX_SCI_ARG(S)
#define LAN80XX_MPORT_SCI_AN_FMT "Port: " MACSEC_PORT_FMT ", SCI: " LAN80XX_SCI_FMT ", an:%u"
#define LAN80XX_MPORT_SCI_AN_ARG(P, S, A) LAN80XX_MACSEC_PORT_ARG(&(P)), LAN80XX_SCI_ARG(S), (A)
#define BOOL_ARG(X) ((X) ? "TRUE" : "FALSE")
#define LAN80XX_MPORT_AN_FMT "Port: " MACSEC_PORT_FMT ", an:%u"
#define LAN80XX_MPORT_AN_ARG(P, A) LAN80XX_MACSEC_PORT_ARG(&(P)), (A)

#define LAN80XX_MACSEC_RX_SC_CONF_FMT \
    "{validate_frames:%u, replay_protect:%s, replay_window:%u, confidentiality_offset:%u}"

#define LAN80XX_MACSEC_RX_SC_CONF_ARG(X) \
    ((X)->validate_frames), BOOL_ARG((X)->replay_protect), \
    ((X)->replay_window), ((X)->confidentiality_offset)

#define LAN80XX_MACSEC_TX_SA_STATUS_FMT \
    "{in_use:%s, next_pn:%u, created_time:%u, started_time:%u, stopped_time:%u}"

#define LAN80XX_MACSEC_TX_SA_STATUS_ARG(X) \
    BOOL_ARG((X).in_use), \
    ((X).next_pn), \
    ((X).created_time), \
    ((X).started_time), \
    ((X).stopped_time)

#define LAN80XX_MACSEC_RX_SA_STATUS_FMT \
    "{in_use:%s, next_pn:%u, lowest_pn:%u, created_time:%u, started_time:%u, stopped_time:%u}"

#define LAN80XX_MACSEC_RX_SA_STATUS_ARG(X) \
    BOOL_ARG((X).in_use), \
    ((X).next_pn), \
    ((X).lowest_pn), \
    ((X).created_time), \
    ((X).started_time), \
    ((X).stopped_time)

#define LAN80XX_MPORT_FMT                             "Port: " MACSEC_PORT_FMT
#define LAN80XX_MPORT_ARG(P)                          LAN80XX_MACSEC_PORT_ARG(&(P))
#define MACSEC_NOT_IN_USE                             (0xFFFFU)
#define MACSEC_ENABLE                                 (1U)
#define MACSEC_DISABLE                                (0U)
#define INGRESS                                       (0U)
#define EGRESS                                        (1U)
#define LAN80XX_MACSEC_TCAM_ETHTYPE_MASK              (0xFFFFU)      /* 16 bit Ethertype compare MASK value */
#define LAN80XX_MACSEC_TCAM_VLANTAG_MASK              (0xFF0FU)      /* 16 bit Vlan tag and 16 bit Ethertype compare MASK Value */
#define LAN80XX_MACSEC_TCAM_DESADDR_1_MASK            (0xFFFFFFFFU) /* 0 - 32 bit Destination Address Match Mask */
#define LAN80XX_MACSEC_TCAM_DESADDR_2_MASK            (0xFFFFU)    /* 33 - 48 bit Destination Address Match Mask */
#define LAN80XX_MACSEC_TCAM_NUM_VLAN_TAGS             (0x0000007FU) /* Mask for number of Vlan tags in frame */
#define LAN80XX_IS_REG_32                             (1U)
#define LAN80XX_BROADCAST_PORT_ID                     (0xFFFFU)

/* Macros related to Cleartags */
#define LAN80XX_MPLS_LABEL_SELECT_2_BIT               (2U)
#define LAN80XX_MPLS_LABEL_SELECT_3_BIT               (3U)
#define LAN80XX_MACSEC_3_MPLS_LABEL                   (3U)
#define LAN80XX_MACSEC_5_MPLS_LABEL                   (5U)
#define LAN80XX_MACSEC_6_MPLS_LABEL                   (6U)
#define LAN80XX_MACSEC_EGR_MAX_MPLS_LABEL             (9U)     /* Max Number of MPLS Label that EIP-161 supports in Egress Direction */

#define LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0           (64U)   /* 64 Xform records are in PAGE0 register and next 64 XFORM records in PAGE1 Register */
#define LAN80XX_MACSEC_SC_REC_PAGE0_NUM              (32U)      /* 32 SC registers are in PAGE0 and the next 32 registers are in PAGE1 */
#define LAN80XX_MACSEC_FLOW_CTRL_PAGE0_NUM           (32U)   /* 32 Flow ctrl registers in PAGE0 and next 32 in PAGE 1 */
#define LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM            (32U)    /* 32 TCAM entry enable register */
#define LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM            (64U)    /* Register to enable 32 - 64 TCAM entry */
#define LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM            (96U)    /* Register to enable 64 - 96 TCAM entry */
#define LAN80XX_MACSEC_SAM_ENTRY_SET4_NUM            (128U)   /* Register to enable 96 - 128 TCAM entry */

/* Egress Direction Control word */
#define LAN80XX_XFORM_EGR_CTRL_WORD_32_BIT_128_AES   (0x120AA006UL)  /* control word for 32-bit frame numbering and 128 AES operation */
#define LAN80XX_XFORM_EGR_CTRL_WORD_64_BIT_128_AES   (0x220AA006UL)  /* control word for 64-bit frame numbering and 128 AES operation */
#define LAN80XX_XFORM_EGR_CTRL_WORD_32_BIT_256_AES   (0x120EA006UL)  /* control word for 32-bit frame numbering and 256 AES operation */
#define LAN80XX_XFORM_EGR_CTRL_WORD_64_BIT_256_AES   (0x220EA006UL)  /* control word for 64-bit frame numbering and 256 AES operation */

/* Ingress Direction Control Word */
#define LAN80XX_XFORM_INGR_CTRL_WORD_32_BIT_128_AES  (0x520AA00FUL) /* control word for 32-bit frame numbering and 128 AES operation */
#define LAN80XX_XFORM_INGR_CTRL_WORD_64_BIT_128_AES  (0x620AA00FUL) /* control word for 64-bit frame numbering and 128 AES operation */
#define LAN80XX_XFORM_INGR_CTRL_WORD_32_BIT_256_AES  (0x520EA00FUL) /* control word for 32-bit frame numbering and 256 AES operation */
#define LAN80XX_XFORM_INGR_CTRL_WORD_64_BIT_256_AES  (0x620EA00FUL) /* control word for 64-bit frame numbering and 256 AES operation */

/* Transform Record format */
#define LAN80XX_MACSEC_XFORM_REC_SIZE                (24U)      /* Transform record size */
#define LAN80XX_MACSEC_XFORM_PAGE0_ADDR              (0x0000U)  /* Transform record Page 0 base address */
#define LAN80XX_MACSEC_XFORM_PAGE1_ADDR              (0x4000U)  /* Transform record Page 1 base address */
#define LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET         (32U)      /* Address difference between base address of each xform record */

#define LAN80XX_MACSEC_TCAM_KEY_PAGE0_ADDR           (0x0800U)
#define LAN80XX_MACSEC_TCAM_KEY_PAGE1_ADDR           (0x4800U)
#define LAN80XX_MACSEC_TCAM_POLICY_PAGE0_ADDR        (0x0C00U)
#define LAN80XX_MACSEC_TCAM_POLICY_PAGE1_ADDR        (0x4C00U)

#define LAN80XX_MACSEC_SC_SA_MAP_PAGE0_ADDR          (0x0E00U)
#define LAN80XX_MACSEC_SC_SA_MAP_PAGE1_ADDR          (0x4E00U)

#define LAN80XX_MACSEC_FLOW_CTRL1_PAGE0_ADDR         (0x1C00U)
#define LAN80XX_MACSEC_FLOW_CTRL1_PAGE1_ADDR         (0x5C00U)

/* Transform Record format */
#define LAN80XX_MACSEC_XFORM_CTRL_WORD               (0U)       /* Rec 1 control word to decide the direction, frame numbering and crypto */
#define LAN80XX_MACSEC_XFORM_REC1_RESERVED           (1U)       /* Rec 2 reserved */
#define LAN80XX_MACSEC_XFORM_KEY_0                   (2U)
#define LAN80XX_MACSEC_XFORM_KEY_1                   (3U)
#define LAN80XX_MACSEC_XFORM_KEY_2                   (4U)
#define LAN80XX_MACSEC_XFORM_KEY_3                   (5U)
#define LAN80XX_MACSEC_XFORM_KEY_4                   (6U)
#define LAN80XX_MACSEC_XFORM_KEY_5                   (7U)
#define LAN80XX_MACSEC_XFORM_KEY_6                   (8U)
#define LAN80XX_MACSEC_XFORM_KEY_7                   (9U)
#define LAN80XX_MACSEC_XFORM_HASH_KEY_0              (10U)
#define LAN80XX_MACSEC_XFORM_HASH_KEY_1              (11U)
#define LAN80XX_MACSEC_XFORM_HASH_KEY_2              (12U)
#define LAN80XX_MACSEC_XFORM_HASH_KEY_3              (13U)
#define LAN80XX_MACSEC_XFORM_SEQ_NUM_0               (14U)      /* Rec 14 Sequence Number LSB */
#define LAN80XX_MACSEC_XFORM_SEQ_NUM_1               (15U)      /* Rec 15 Sequence Number MSB */
#define LAN80XX_MACSEC_EGR_XFORM_SA_UPD_CTRL         (16U)      /* Rec 16 SA update control for Egress */
#define LAN80XX_MACSEC_XFORM_CTX_SALT0               (17U)
#define LAN80XX_MACSEC_XFORM_CTX_SALT1               (18U)
#define LAN80XX_MACSEC_XFORM_CTX_SALT2               (19U)
#define LAN80XX_MACSEC_XFORM_EGR_SCI0_INGR_SA_UPD_CTRL (20U)    /* Rec 20 secure channel identifier LSB for egress and SA upd ctrl for ingress */
#define LAN80XX_MACSEC_XFORM_EGR_SCI1                (21U)      /* Rec 21 Secure channel identifier MSB */
#define LAN80XX_MACSEC_CTRL_WORD_SEQ_BIT             (13U)      /* Bit position of Sequence number update in Rec 0 */
#define LAN80XX_MACSEC_INGR_REC20_AN_BIT_POS         (29U)      /* 29 and 30 bit position in REC20 of INGR holds the Association Number */
#define LAN80XX_MACSEC_CTRL_WRD_AN_BIT               (26U)      /* Association Number Bit position in XFORM REC 0 */

/*Function for counting the number of return code errors.*/
// IN/OUT : dev        - Internal API state containing the error counters
// IN     : port_no    - The port in question for updating the counters
// IN     : rc         - The return code to count
static mepa_rc dbg_counter_incr(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_rc rc)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    switch (rc) {
    case MEPA_RC_ERR_MACSEC_INVALID_SCI_MACADDR:
        data->macsec_conf.rc_dbg_counters.invalid_sci_macaddr++;
        break;

    case MEPA_RC_ERR_MACSEC_NOT_ENABLED:
        data->macsec_conf.rc_dbg_counters.macsec_not_enabled++;
        break;

    case MEPA_RC_ERR_MACSEC_SECY_ALREADY_IN_USE:
        data->macsec_conf.rc_dbg_counters.secy_already_in_use++;
        break;

    case MEPA_RC_ERR_MACSEC_NO_SECY_FOUND:
        data->macsec_conf.rc_dbg_counters.no_secy_found++;
        break;

    case MEPA_RC_ERR_MACSEC_NO_SECY_VACANCY:
        data->macsec_conf.rc_dbg_counters.no_secy_vacency++;
        break;

    case MEPA_RC_ERR_MACSEC_INVALID_VALIDATE_FRM:
        data->macsec_conf.rc_dbg_counters.invalid_validate_frm++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH:
        data->macsec_conf.rc_dbg_counters.could_not_prg_sa_match++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW:
        data->macsec_conf.rc_dbg_counters.could_not_prg_sa_flow++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA:
        data->macsec_conf.rc_dbg_counters.could_not_ena_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA:
        data->macsec_conf.rc_dbg_counters.could_not_set_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_INVALID_BYPASS_HDR_LEN:
        data->macsec_conf.rc_dbg_counters.invalid_hdr_bypass_len++;
        break;

    case MEPA_RC_ERR_MACSEC_SC_NOT_FOUND:
        data->macsec_conf.rc_dbg_counters.sc_not_found++;
        break;

    case MEPA_RC_ERR_MACSEC_NO_CTRL_FRM_MATCH:
        data->macsec_conf.rc_dbg_counters.no_ctrl_frm_match++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN:
        data->macsec_conf.rc_dbg_counters.could_not_set_pattern++;
        break;

    case MEPA_RC_ERR_MACSEC_TIMEOUT_ISSUE:
        data->macsec_conf.rc_dbg_counters.timeout_issue++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS:
        data->macsec_conf.rc_dbg_counters.could_not_empty_egress++;
        break;

    case MEPA_RC_ERR_MACSEC_AN_NOT_CREATED:
        data->macsec_conf.rc_dbg_counters.an_not_created++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS:
        data->macsec_conf.rc_dbg_counters.could_not_empty_ingress++;
        break;

    case MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST:
        data->macsec_conf.rc_dbg_counters.tx_sc_not_exist++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA:
        data->macsec_conf.rc_dbg_counters.could_not_disable_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA:
        data->macsec_conf.rc_dbg_counters.could_not_del_tx_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA:
        data->macsec_conf.rc_dbg_counters.could_not_del_tx_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_PATTERN_NOT_SET:
        data->macsec_conf.rc_dbg_counters.pattern_not_set++;
        break;

    case MEPA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED:
        data->macsec_conf.rc_dbg_counters.hw_resource_exhusted++;
        break;

    case MEPA_RC_ERR_MACSEC_SCI_ALREADY_EXISTS:
        data->macsec_conf.rc_dbg_counters.sci_already_exist++;
        break;

    case MEPA_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND:
        data->macsec_conf.rc_dbg_counters.sc_resource_not_found++;
        break;

    case MEPA_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE:
        data->macsec_conf.rc_dbg_counters.rx_an_already_in_use++;
        break;

    case MEPA_RC_ERR_MACSEC_EMPTY_RECORD:
        data->macsec_conf.rc_dbg_counters.empty_record++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM:
        data->macsec_conf.rc_dbg_counters.could_not_prg_xform++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA:
        data->macsec_conf.rc_dbg_counters.could_not_toggle_sa++;
        break;

    case MEPA_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE:
        data->macsec_conf.rc_dbg_counters.tx_an_already_in_use++;
        break;

    case MEPA_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE:
        data->macsec_conf.rc_dbg_counters.all_available_sa_in_use++;
        break;

    case MEPA_RC_ERR_MACSEC_MATCH_DISABLE:
        data->macsec_conf.rc_dbg_counters.match_disable++;
        break;

    case MEPA_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE:
        data->macsec_conf.rc_dbg_counters.all_cp_rules_in_use++;
        break;

    case MEPA_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID:
        data->macsec_conf.rc_dbg_counters.pattern_prio_not_valid++;
        break;

    case MEPA_RC_ERR_MACSEC_BUFFER_TOO_SMALL:
        data->macsec_conf.rc_dbg_counters.buffer_too_small++;
        break;

    case MEPA_RC_ERR_MACSEC_FRAME_TOO_LONG:
        data->macsec_conf.rc_dbg_counters.frm_too_long++;
        break;

    case MEPA_RC_ERR_MACSEC_FRAME_TRUNCATED:
        data->macsec_conf.rc_dbg_counters.frm_truncated++;
        break;

    case MEPA_RC_ERR_MACSEC_PHY_POWERED_DOWN:
        data->macsec_conf.rc_dbg_counters.phy_powered_down++;
        break;

    case MEPA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE:
        data->macsec_conf.rc_dbg_counters.phy_not_macsec_capable++;
        break;

    case MEPA_RC_ERR_MACSEC_AN_NOT_EXIST:
        data->macsec_conf.rc_dbg_counters.an_not_exist++;
        break;

    case MEPA_RC_ERR_MACSEC_NO_PATTERN_CFG:
        data->macsec_conf.rc_dbg_counters.no_pattern_cfg++;
        break;

    case MEPA_RC_ERR_MACSEC_MAX_MTU:
        data->macsec_conf.rc_dbg_counters.max_mtu++;
        break;

    case MEPA_RC_ERR_MACSEC_UNEXPECT_CP_MODE:
        data->macsec_conf.rc_dbg_counters.unexpected_cp_mode++;
        break;

    case MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN:
        data->macsec_conf.rc_dbg_counters.could_not_disable_an++;
        break;

    case MEPA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE:
        data->macsec_conf.rc_dbg_counters.rule_out_of_range++;
        break;

    case MEPA_RC_ERR_MACSEC_RULE_NOT_EXIST:
        data->macsec_conf.rc_dbg_counters.rule_not_exit++;
        break;

    case MEPA_RC_ERR_MACSEC_CSR_READ:
        data->macsec_conf.rc_dbg_counters.csr_read++;
        break;

    case MEPA_RC_ERR_MACSEC_CSR_WRITE:
        data->macsec_conf.rc_dbg_counters.csr_write++;
        break;

    default:
        data->macsec_conf.rc_dbg_counters.unknown_rc_code++;
        return MEPA_RC_ERROR;

    }
    return rc;
}

mepa_rc lan80xx_macsec_debug_counters_clear_priv(mepa_device_t *dev, const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    memset(&data->macsec_conf.rc_dbg_counters, 0, sizeof(mepa_macsec_rc_dbg_counters_t));
    return MEPA_RC_OK;
}

//Function to check whether MACsec is enabled on the particular port
static mepa_rc lan80xx_port_macsec_enable_check(mepa_device_t *dev, mepa_macsec_port_t port)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (data->macsec_conf.glb.init.enable == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "MacSec not enabled, port_no:%d\n", port.port_no);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NOT_ENABLED);
    }
    return MEPA_RC_OK;
}

static mepa_bool_t lan80xx_macsec_cleartags_supported(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    if (base_data->features.cleartags_disable != 0U) {
        return FALSE;
    }
    return TRUE;
}


//Function to check whether the PHY is macsec capable based on the phy id.
mepa_bool_t lan80xx_phy_is_macsec_capable(mepa_device_t *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_device_t *base_dev;
    phy25g_phy_state_t *base_data;
    LAN80XX_BASE_DEV(data, base_dev, base_data);

    if (base_data->features.macsec_disable != 0U) {
        return FALSE;
    }
    return TRUE;
}

mepa_rc lan80xx_macsec_port_enable_status_get_priv(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_bool_t  *status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    if (!lan80xx_phy_is_macsec_capable(dev)) {
        T_D(MEPA_TRACE_GRP_GEN, "Phy is not MacSec capable");
        *status = FALSE;
    } else {
        if (data->macsec_conf.glb.init.enable == 0) {
            *status = FALSE;
        } else {
            *status = TRUE;
        }
    }
    return rc;
}

static mepa_rc lan80xx_macsec_mtu_set_(mepa_device_t        *dev,
                                       const mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mtu_value = data->macsec_conf.glb.mtu_conf.mtu;
    mepa_bool_t drop     = data->macsec_conf.glb.mtu_conf.drop;
    mepa_bool_t vlan_unaware_en = data->macsec_conf.glb.mtu_conf.vlan_unaware_en;

    if (mtu_value > LAN80XX_MACSEC_MTU_MAX) {
        T_E(MEPA_TRACE_GRP_GEN, "Maximum MTU allowed is %d (+ 4 bytes for VLAN), was:%d", LAN80XX_MACSEC_MTU_MAX, mtu_value);
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_MAX_MTU);
    }

    for (int i = 0 ; i < LAN80XX_MACSEC_SC_REC_PAGE0_NUM; i++) {
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_MCHP_OPPE_MTU(i),
                            LAN80XX_F_MACSEC_EGR_CORE_MCHP_OPPE_MTU_MTU_COMPARE(mtu_value) |
                            (drop ? LAN80XX_M_MACSEC_EGR_CORE_MCHP_OPPE_MTU_MTU_COMP_DROP : 0));
    }
    /* In VLAN aware mode, VLAN_MTU_CHECK == (NON_VLAN_MTU_CHECK + 4) bytes,
       In VLAN unaware mode, NON_VLAN_MTU_CHECK == VLAN_MTU_CHECK bytes */
    if (!vlan_unaware_en) {
        mtu_value += LAN80XX_VLAN_TAG_LEN_BYTE;
    }

    for (int i = 0; i < LAN80XX_MACSEC_SC_REC_PAGE0_NUM; i++) {
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_MCHP_OPPE_MTU(i),
                            LAN80XX_F_MACSEC_EGR_CORE_MCHP_OPPE_MTU_MTU_COMPARE(mtu_value) |
                            (drop ? LAN80XX_M_MACSEC_EGR_CORE_MCHP_OPPE_MTU_MTU_COMP_DROP : 0));
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_lmac_counters_clear_priv(mepa_device_t         *dev,
                                                const mepa_port_no_t  port_no)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_IN_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_IN_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_OK_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_OK_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_BAD_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_BAD_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_UC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_MC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_BC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_CRC_ERR_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_UNDERSIZE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_FRAGMENTS_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_JABBERS_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_OVERSIZE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE64_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE65TO127_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE128TO255_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE256TO511_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE512TO1023_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE1024TO1518_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE1519TOMAX_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_PAUSE_CNT, 0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_OK_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_OK_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_PAUSE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_UC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_MC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_BC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE64_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE65TO127_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE128TO255_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE256TO511_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE512TO1023_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE1024TO1518_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE1519TOMAX_CNT, 0);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_hmac_counters_clear_priv(mepa_device_t         *dev,
                                                const mepa_port_no_t  port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_UC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_MC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_BC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_JABBERS_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE64_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_PAUSE_CNT, 0);

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_MSB_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_PAUSE_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_UC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_MC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_BC_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE64_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT, 0);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_init_set_(mepa_device_t *dev, mepa_port_no_t port_no, const mepa_macsec_init_t *const init)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u8 egr_latency, ingr_latency;
    phy25g_oper_speed_mode_t phy_speed;
    phy_speed = data->port_state.speed;

    /* Configuring Latency values based on the Link Speed */
    switch (phy_speed) {
    case SPEED_1G:
        ingr_latency = LAN80XX_MACSEC_1G_INGR_LATENCY;
        egr_latency = LAN80XX_MACSEC_1G_EGR_LATENCY;
        break;
    case SPEED_10G:
        ingr_latency = LAN80XX_MACSEC_10G_INGR_LATENCY;
        egr_latency = LAN80XX_MACSEC_10G_EGR_LATENCY;
        break;
    case SPEED_25G:
        ingr_latency = LAN80XX_MACSEC_25G_INGR_LATENCY;
        egr_latency = LAN80XX_MACSEC_25G_EGR_LATENCY;
        break;
    default:
        T_E(MEPA_TRACE_GRP_GEN, "\n Port %d Not Configured, Unsupported Speed\n", port_no);
        return MEPA_RC_ERROR;
    }

    if (init->enable) {

        /* Resetiing the MACsec Block When Disabling the MACsec Block of the Port */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_LINE_MACSEC_RESET,
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_INGR_RST |
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_LPART_EGR_RST  |
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_INGR_RST |
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_HPART_EGR_RST  |
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_INGR_RST    |
                       LAN80XX_M_LINE_SLICE_LINE_MACSEC_RESET_MACSEC_IP_EGR_RST);


        LAN80XX_CSR_WR(dev, port_no, LAN80XX_LINE_SLICE_LINE_MACSEC_RESET, 0x0);

        /* Ingress MacSec block Enable Clock */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST);

        /* Egress MacSec Enable Clock */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_CLK_ENA |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST);

        /* Ingress MacSec block Out of SW Reset and Enable Clock */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA);

        /* Egress MacSec block Out of SW Reset and Enable Clock */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_CLK_ENA);

        /* Set the context */
        /* Selcting the Ethertype to be insterted secTag which is 88E5 represented in little endian format and enabling sequence number threshold mode */
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_CONTEXT_CTRL, LAN80XX_MACSEC_CONTEX_CTRL);
        /* Writing the latency value to LATENCY_CONTROL reg */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_CORE_LATENCY_CONTROL,
                            LAN80XX_F_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_LATENCY_FIX_0(ingr_latency));
        /* Dynamic Latency Enable */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_CORE_DYN_LATENCY_CONTROL,
                            LAN80XX_F_MACSEC_INGR_MACSEC_INGR_LATENCY_CONTROL_MC_DYN_LATENCY_WORDS_0(LAN80XX_MACSEC_DYN_LATENCY) |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_DYN_LAT_ENABLE_0);

        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP, 0x0);
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP, 0x0);
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_NCP, 0x0);
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_CP, 0x0);

        /* Egress */
        /* Selcting the Ethertype to be insterted secTag which is 88E5 represented in little endian format and enabling sequence number threshold mode */
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_CONTEXT_CTRL, LAN80XX_MACSEC_CONTEX_CTRL);
        /* Writing the latency value to LATENCY_CONTROL reg */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_CORE_LATENCY_CONTROL,
                            LAN80XX_F_MACSEC_EGR_MACSEC_EGR_LATENCY_CONTROL_MC_LATENCY_FIX_0(egr_latency));
        /* Dynamic Latency Enable */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_CORE_DYN_LATENCY_CONTROL,
                            LAN80XX_F_MACSEC_EGR_MACSEC_EGR_LATENCY_CONTROL_MC_DYN_LATENCY_WORDS_0(LAN80XX_MACSEC_DYN_LATENCY) |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_DYN_LAT_ENABLE_0);

        /* Counters are clear on read */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_TCAM_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_TCAM_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_TCAM_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SECY_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SECY_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SECY_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SA_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SA_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SA_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_IFC_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_IFC_COUNT_CONTROL,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_IFC_COUNT_CONTROL_AUTO_CNTR_RESET_0);

        /* Enable Secondary VLAN tag parsing for Egress */
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_SCP_TAG_ENB,
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SCP_TAG_ENB_PARSE_STAG0_0 |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SCP_TAG_ENB_PARSE_STAG1_0 |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SCP_TAG_ENB_PARSE_STAG2_0 |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SCP_TAG_ENB_PARSE_STAG3_0 |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SCP_TAG_ENB_PARSE_QINQ_0);
        /* Enable Secondary VLAN tag parsing for Ingress */
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_SCP_TAG_ENB,
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG0_0 |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG1_0 |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG2_0 |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_STAG3_0 |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SCP_TAG_ENB_PARSE_QINQ_0);

        /* Enable Primary VLAN Tag Parsing for Egress */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CP_TAG_ENB,
                       LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CP_TAG_ENB_PARSE_STAG0_0 |
                       LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CP_TAG_ENB_PARSE_STAG1_0 |
                       LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CP_TAG_ENB_PARSE_STAG2_0 |
                       LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CP_TAG_ENB_PARSE_STAG3_0 |
                       LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CP_TAG_ENB_PARSE_QINQ_0);

        /* Enable Primary VLAN Tag Parsing for Ingress */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CP_TAG_ENB,
                       LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG0_0 |
                       LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG1_0 |
                       LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG2_0 |
                       LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_STAG3_0 |
                       LAN80XX_M_MACSEC_INGR_MACSEC_INGR_CP_TAG_ENB_PARSE_QINQ_0);

        /* BLOCK_CTX_UPDATE::BLOCK_CTX_UPDATES should be programmed to 0x3 */
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_CONTEXT_UPD_CTRL, LAN80XX_MACSEC_CONTEXT_UPD_CTRL);
        LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_CONTEXT_UPD_CTRL, LAN80XX_MACSEC_CONTEXT_UPD_CTRL);

        /* Making both threshold and rollover event as zero */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_INT_CTRL_STAT, 0, LAN80XX_MACSEC_SEQ_NUM_THR_MASK | LAN80XX_MACSEC_SEQ_NUM_ROLL_MASK);

        /* Clear Mac block counters */
        MEPA_RC(lan80xx_macsec_lmac_counters_clear_priv(dev, port_no));
        MEPA_RC(lan80xx_macsec_hmac_counters_clear_priv(dev, port_no));

        /* We set MTU to maximum, because we don't know which frame size the MAC/Switch supports.*/
        data->macsec_conf.glb.mtu_conf.mtu  = LAN80XX_MACSEC_MTU_MAX;
        data->macsec_conf.glb.mtu_conf.drop = TRUE;
        MEPA_RC(lan80xx_macsec_mtu_set_(dev, port_no));

        for (u8 i = 0; i < LAN80XX_MACSEC_CP_RULES; i++) {
            data->macsec_conf.glb.control_match[i].match = MEPA_MACSEC_MATCH_DISABLE;
            data->macsec_conf.glb.egr_bypass_record[i] = MACSEC_NOT_IN_USE;
        }

        /* Enable Ingress MacSec block and disable Ingress bypass*/
        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA |
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA,
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA |
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST  |
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA |
                             LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA);


        /* Enable Egress MacSec block and disable Egress bypass*/
        LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_CLK_ENA |
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_ENA,
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_CLK_ENA |
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST  |
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA |
                             LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_ENA);
    } else {
        /* Ingress*/
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_CLK_ENA |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_SW_RST  |
                            LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);


        /* Egress*/
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG,
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_CLK_ENA |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_SW_RST  |
                            LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA);

        /* Clear the internals */
        memset(&data->macsec_conf, 0, sizeof(data->macsec_conf));
    }
    return MEPA_RC_OK;
}

/*Function to configure the MACsec block*/
mepa_rc lan80xx_macsec_init_set_priv(mepa_device_t *dev, const mepa_macsec_init_t *const init)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u8 port_no = data->port_no;
    mepa_rc rc = MEPA_RC_OK;
    u32 reg_val = 0;
    /*Enable MAC block to access the MACsec IP Register */
    if (init->enable && (data->port_state.port_mode.oper_mode == PCS_RETIMER)) {
        if ((rc = MACSEC_RC_COLD(lan80xx_operating_mode_set_priv(dev, port_no, MAC_RETIMER))) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not set mac conf on port:%u", port_no);
        }
        data->port_state.port_mode.oper_mode = MAC_RETIMER;
    }
    if (!lan80xx_phy_is_macsec_capable(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, " Phy is not MacSec capable");
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE);
        return MEPA_RC_ERROR;
    } else if (init->bypass == MEPA_MACSEC_INIT_BYPASS_ENABLE || init->bypass == MEPA_MACSEC_INIT_BYPASS_DISABLE) {
        T_I(MEPA_TRACE_GRP_GEN, "Port:%u Macsec bypass %s", port_no, (init->bypass == MEPA_MACSEC_INIT_BYPASS_ENABLE) ? "Enabled" : "Disabled");
        data->macsec_conf.glb.init.bypass = init->bypass;
        /*Ingress*/
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, &reg_val);
        if (init->bypass == MEPA_MACSEC_INIT_BYPASS_ENABLE) {
            reg_val &= ~LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA;
            reg_val |= LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
            LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, reg_val);
        } else {
            reg_val |= LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_ENA;
            reg_val &= ~LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
            LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_INGR_MACSEC_INGR_MACSEC_ENA_CFG, reg_val);
        }
        /*Egress*/
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, &reg_val);
        if (init->bypass == MEPA_MACSEC_INIT_BYPASS_ENABLE) {
            reg_val &= ~LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_ENA;
            reg_val |= LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
            LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, reg_val);
            data->macsec_conf.glb.init.enable = 0;
        } else {
            reg_val |= LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_ENA;
            reg_val &= ~LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG_MACSEC_BYPASS_ENA;
            LAN80XX_CSR_COLD_WR(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_ENA_CFG, reg_val);
            data->macsec_conf.glb.init.enable = 1;
        }
        return MEPA_RC_OK;
    } else {
        if ((data->macsec_conf.glb.init.enable != init->enable)) {
            mepa_macsec_init_t state_init;
            state_init = data->macsec_conf.glb.init;
            data->macsec_conf.glb.init = *init;
            rc = lan80xx_macsec_init_set_(dev, port_no, init);
            if (rc != MEPA_RC_OK) {
                data->macsec_conf.glb.init = state_init;
            }
            data->macsec_conf.glb.mac_block_mtu = LAN80XX_MAC_MAXLEN; /* Default MAC Block MTU */
        }
    }
    return rc;
}

mepa_rc lan80xx_macsec_init_get_priv(mepa_device_t *dev, mepa_macsec_init_t *const init)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u8 port_no = data->port_no;
    mepa_rc rc = MEPA_RC_OK;
    if (!lan80xx_phy_is_macsec_capable(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "Phy is not MacSec capable");
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE);
    } else {
        *init = data->macsec_conf.glb.init;
    }
    return rc;
}

static mepa_rc lan80xx_macsec_default_action_set_(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_bool_t drop = 0;
    drop = (pattern->ingress_non_control_and_non_macsec == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;

    /* Ingress. Not control and not macsec tagged */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP,
                         (drop ? LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0 : 0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT0_0(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT0_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR0_0);

    /* Ingress. Not control but macsec tagged */
    drop = (pattern->ingress_non_control_and_macsec == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP,
                         (drop ? LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0 : 0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT1_0(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION1_0(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT1_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION1_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR1_0);

    /* Bad Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP,
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0  |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT2_0(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT2_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR2_0);

    /* Kay Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_NCP,
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT3_0(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DEST_PORT3_0 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR3_0);

    /* Ingress - Control Frame and Untagged */
    drop = (pattern->ingress_control_and_non_macsec == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP,
                         (drop ? LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1 : 0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT0_1(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION0_1(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT0_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION0_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR0_1);

    /* Ingress. Control and macsec tagged */
    drop = (pattern->ingress_control_and_macsec == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP,
                         (drop ? LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1 : 0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT1_1(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION1_1(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT1_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION1_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR1_1);

    /* Bad Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP,
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1 |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT2_1(0) |
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION2_1(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT2_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_ACTION2_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR2_1);

    /* Kay is handled as macsec taggged */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SAM_NM_FLOW_CP,
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT3_1(0),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_FLOW_TYPE3_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DEST_PORT3_1 |
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_SAM_NM_FLOW_CP_DROP_NON_REDIR3_1);

    /* Egress. Not control and not macsec tagged */
    drop = (pattern->egress_non_control == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_NCP,
                         (drop ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0 : 0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT0_0(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE0_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT0_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION0_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR0_0);

    /* Egress. Not control but macsec tagged */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_NCP,
                         (drop ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0 : 0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT1_0(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE1_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT1_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR1_0);

    /* Bad Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_NCP,
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0  |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT2_0(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE2_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT2_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION2_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR2_0);

    /* Kay Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_NCP,
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0  |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT3_0(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION3_0(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_FLOW_TYPE3_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DEST_PORT3_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_ACTION3_0 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_NCP_DROP_NON_REDIR3_0);

    /* Egress. Control frames */
    drop = (pattern->egress_control == MEPA_MACSEC_DEFAULT_ACTION_DROP) ? 1 : 0;
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_CP,
                         (drop ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1 : 0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT1_1(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION1_1(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE1_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT1_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION1_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_NON_REDIR1_1);

    /* Bad Tag */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_CP,
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1 |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT2_1(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION2_1(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE2_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT2_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION2_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_NON_REDIR2_1);

    /* Kay is handled as macsec taggged */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_CP,
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT3_1(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION3_1(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE3_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT3_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION3_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_NON_REDIR3_1);

    /* Egress. Control and not macsec tagged */
    LAN80XX_CSR_COLD_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_SAM_NM_FLOW_CP,
                         (drop ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1 : 0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT0_1(0) |
                         LAN80XX_F_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION0_1(0),
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_FLOW_TYPE0_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DEST_PORT0_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_ACTION0_1 |
                         LAN80XX_M_MACSEC_EGR_MACSEC_EGR_SAM_NM_FLOW_CP_DROP_NON_REDIR0_1);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_is_sci_valid(mepa_device_t *dev, const mepa_macsec_sci_t *sci)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_mac_t broadcast = {.addr = LAN80XX_MAC_ADDR_BROADCAST};
    mepa_mac_t zeromac = {.addr = LAN80XX_MAC_ADDR_ZERO};
    /*IEEE 802.1AE-2006, section 9.9 - The 64-bit value FF-FF-FF-FF-FF-FF is never used as an SCI and is reserved for use by implementations
    to indicate the absence of an SC or an SCI in contexts where an SC can be present */
    if (memcmp(&sci->mac_addr, &broadcast, sizeof(broadcast)) == 0) {
        T_I(MEPA_TRACE_GRP_GEN, "Broadcast MAC address should not be used");
        return dbg_counter_incr(dev, data->port_no, MEPA_RC_ERR_MACSEC_INVALID_SCI_MACADDR);
    }

    // The MACaddress of the Port can't be zero
    if (memcmp(&sci->mac_addr, &zeromac, sizeof(zeromac)) == 0) {
        T_I(MEPA_TRACE_GRP_GEN, "MACaddress of the Port can't be zero");
        return dbg_counter_incr(dev, data->port_no, MEPA_RC_ERR_MACSEC_INVALID_SCI_MACADDR);
    }
    return MEPA_RC_OK;
}

static mepa_bool_t lan80xx_sci_cmp(const mepa_macsec_sci_t *a, const mepa_macsec_sci_t *b)
{
    if (b == NULL || a == NULL) {
        return FALSE;
    }
    if (memcmp(a, b, sizeof(mepa_macsec_sci_t)) != 0) {
        return FALSE;
    }
    return TRUE;
}

static mepa_rc lan80xx_sc_from_sci_get(mepa_device_t *dev, phy25g_macsec_internal_secy_t *secy, const mepa_macsec_sci_t *sci, u32 *sc)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 i, max_sc_rx = 0;
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);
    for (i = 0; i < max_sc_rx; i++) {
        if (secy->rx_sc[i] != NULL && secy->rx_sc[i]->in_use) {
            if (lan80xx_sci_cmp(sci, &secy->rx_sc[i]->sci)) {
                *sc = i;
                return MEPA_RC_OK;
            }
        }
    }
    return dbg_counter_incr(dev, data->port_no, MEPA_RC_ERR_MACSEC_SC_NOT_FOUND);
}

static u32 lan80xx_get_u32(const u8 *const buf)
{
    return *(buf) | (*(buf + 1) << 8) | (*(buf + 2) << 16) | (*(buf + 3) << 24);
}


static u32 lan80xx_get_xform_value_64(mepa_device_t *dev, u32 tran_rec_index, mepa_bool_t egr, mepa_bool_t aes_128,
                                      phy25g_macsec_internal_secy_t *secy, u16 an, u32 sc, u16 record)
{
    mepa_macsec_sak_t *sak;
    u64 replwin = 0;

    if (egr) {
        sak = &secy->tx_sc.sa[an]->sak;
    } else {
        sak = &secy->rx_sc[sc]->sa[an]->sak;
    }
    switch (tran_rec_index) {
    case LAN80XX_MACSEC_XFORM_CTRL_WORD:
        if (egr) {
            if (aes_128) {
                return (LAN80XX_XFORM_EGR_CTRL_WORD_64_BIT_128_AES | (an << LAN80XX_MACSEC_CTRL_WRD_AN_BIT));
            }
            return (LAN80XX_XFORM_EGR_CTRL_WORD_64_BIT_256_AES | (an << LAN80XX_MACSEC_CTRL_WRD_AN_BIT));
        }
        if (aes_128) {
            return (LAN80XX_XFORM_INGR_CTRL_WORD_64_BIT_128_AES);
        }
        return (LAN80XX_XFORM_INGR_CTRL_WORD_64_BIT_256_AES);
    case LAN80XX_MACSEC_XFORM_SEQ_NUM_0:
        if (egr) {
            return (u32)secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn - 1;
        }
        replwin = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
        return (u32)replwin;
    case LAN80XX_MACSEC_XFORM_SEQ_NUM_1:
        if (egr) {
            return (u32)((secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn - 1) >> 32);
        }
        replwin = secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn + secy->rx_sc[sc]->conf.replay_window;
        return (u32)(replwin >> 32);
    case LAN80XX_MACSEC_XFORM_REC1_RESERVED:
        return 0;
    case LAN80XX_MACSEC_EGR_XFORM_SA_UPD_CTRL:
        if (egr) {
            return 0;
        }
        if (secy->rx_sc[sc]->conf.replay_window <= LAN80XX_MACSEC_REPLAY_WINDOW_SIZE) { /* Replay window size should not exceed 2^30 */
            return secy->rx_sc[sc]->conf.replay_window;
        }
        return 0;
    case LAN80XX_MACSEC_XFORM_EGR_SCI0_INGR_SA_UPD_CTRL:
        if (egr) {
            return lan80xx_get_u32(&secy->sci.mac_addr.addr[0]);
        }
        return (an << LAN80XX_MACSEC_INGR_REC20_AN_BIT_POS);
    case LAN80XX_MACSEC_XFORM_EGR_SCI1:
        if (egr) {
            return (secy->sci.mac_addr.addr[4] | (secy->sci.mac_addr.addr[5] << 8) | (MACSEC_BS(secy->sci.port_id) << 16));
        }
        return 0;
    default :
        if (aes_128) {
            if (tran_rec_index <= LAN80XX_MACSEC_XFORM_KEY_3) {
                return lan80xx_get_u32(&sak->buf[0] + ((tran_rec_index - 2) * 4));
            } else if (tran_rec_index <= LAN80XX_MACSEC_XFORM_HASH_KEY_3 && tran_rec_index >= LAN80XX_MACSEC_XFORM_HASH_KEY_0) {
                return lan80xx_get_u32(&sak->h_buf[0] + ((tran_rec_index - 10) * 4));
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT0) {
                if (egr) {
                    return lan80xx_get_u32(sak->salt.buf) ^ lan80xx_get_u32(secy->tx_sc.sa[an]->ssci.buf);
                }
                return lan80xx_get_u32(sak->salt.buf) ^ lan80xx_get_u32(secy->rx_sc[sc]->sa[an]->ssci.buf);
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT1) {
                return lan80xx_get_u32(&sak->salt.buf[4]);
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT2) {
                return lan80xx_get_u32(&sak->salt.buf[8]);
            }
            return 0;
        } else {
            /* AES 256*/
            if (tran_rec_index <= LAN80XX_MACSEC_XFORM_KEY_7) {
                return lan80xx_get_u32(&sak->buf[0] + ((tran_rec_index - 2) * 4));
            } else if (tran_rec_index <= LAN80XX_MACSEC_XFORM_HASH_KEY_3) {
                return lan80xx_get_u32(&sak->h_buf[0] + ((tran_rec_index - 10) * 4));
            } else if (tran_rec_index == LAN80XX_MACSEC_EGR_XFORM_SA_UPD_CTRL) {
                if (egr) {
                    return 0;
                }
                if (secy->rx_sc[sc]->conf.replay_window <= LAN80XX_MACSEC_REPLAY_WINDOW_SIZE) { /* Replay window size should not exceed 2^30 */
                    return secy->rx_sc[sc]->conf.replay_window;
                }
                return 0;
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT0) {
                if (egr) {
                    return lan80xx_get_u32(sak->salt.buf) ^ lan80xx_get_u32(secy->tx_sc.sa[an]->ssci.buf);
                }
                return lan80xx_get_u32(sak->salt.buf) ^ lan80xx_get_u32(secy->rx_sc[sc]->sa[an]->ssci.buf);
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT1) {
                return lan80xx_get_u32(&sak->salt.buf[4]);
            } else if (tran_rec_index == LAN80XX_MACSEC_XFORM_CTX_SALT2) {
                return lan80xx_get_u32(&sak->salt.buf[8]);
            }
            return 0;
        }
    }
}

static u32 lan80xx_get_xform_value(mepa_device_t *dev, u32 tran_rec_index, mepa_bool_t egr, mepa_bool_t aes_128,
                                   phy25g_macsec_internal_secy_t *secy, u16 an, u32 sc, u16 record)
{
    mepa_macsec_sak_t *sak;

    if (egr) {
        sak = &secy->tx_sc.sa[an]->sak;
    } else {
        sak = &secy->rx_sc[sc]->sa[an]->sak;
    }
    switch (tran_rec_index) {
    case LAN80XX_MACSEC_XFORM_CTRL_WORD:
        if (egr) {
            if (aes_128) {
                return (LAN80XX_XFORM_EGR_CTRL_WORD_32_BIT_128_AES | (an << LAN80XX_MACSEC_CTRL_WRD_AN_BIT));
            }
            return (LAN80XX_XFORM_EGR_CTRL_WORD_32_BIT_256_AES | (an << LAN80XX_MACSEC_CTRL_WRD_AN_BIT));
        }
        if (aes_128) {
            return (LAN80XX_XFORM_INGR_CTRL_WORD_32_BIT_128_AES);
        }
        return (LAN80XX_XFORM_INGR_CTRL_WORD_32_BIT_256_AES);
    case LAN80XX_MACSEC_XFORM_SEQ_NUM_0:
        if (egr) {
            return secy->tx_sc.sa[an]->status.next_pn;
        }
        return secy->rx_sc[sc]->sa[an]->status.lowest_pn;
    case LAN80XX_MACSEC_XFORM_REC1_RESERVED:
        return 0;
    case LAN80XX_MACSEC_XFORM_EGR_SCI0_INGR_SA_UPD_CTRL:
        if (egr) {
            return lan80xx_get_u32(&secy->sci.mac_addr.addr[0]);
        }
        return (an << LAN80XX_MACSEC_INGR_REC20_AN_BIT_POS);
    case LAN80XX_MACSEC_XFORM_EGR_SCI1:
        if (egr) {
            return (secy->sci.mac_addr.addr[4] | (secy->sci.mac_addr.addr[5] << 8) | (MACSEC_BS(secy->sci.port_id) << 16));
        }
        return 0;
    case LAN80XX_MACSEC_EGR_XFORM_SA_UPD_CTRL:
        if (egr) {
            return lan80xx_get_u32(&secy->sci.mac_addr.addr[0]);
        }
        return secy->rx_sc[sc]->conf.replay_window;
    case LAN80XX_MACSEC_XFORM_CTX_SALT0:
        if (!egr) {
            return lan80xx_get_u32(&secy->sci.mac_addr.addr[0]);
        }
        return 0;
    case LAN80XX_MACSEC_XFORM_CTX_SALT1:
        if (!egr) {
            return (secy->sci.mac_addr.addr[4] | (secy->sci.mac_addr.addr[5] << 8) | (MACSEC_BS(secy->sci.port_id) << 16));
        }
        return 0;
    default:
        if (aes_128) {
            if (tran_rec_index <= LAN80XX_MACSEC_XFORM_KEY_3) {
                return lan80xx_get_u32(&sak->buf[0] + ((tran_rec_index - 2) * 4));
            } else if (tran_rec_index <= LAN80XX_MACSEC_XFORM_HASH_KEY_3 && tran_rec_index >= LAN80XX_MACSEC_XFORM_HASH_KEY_0) {
                return lan80xx_get_u32(&sak->h_buf[0] + ((tran_rec_index - 10) * 4));
            }
            return 0;
        } else {
            /* AES 256 */
            if (tran_rec_index <= LAN80XX_MACSEC_XFORM_KEY_7) {
                return lan80xx_get_u32(&sak->buf[0] + ((tran_rec_index - 2) * 4));
            } else if (tran_rec_index <= LAN80XX_MACSEC_XFORM_HASH_KEY_3) {
                return lan80xx_get_u32(&sak->h_buf[0] + ((tran_rec_index - 10) * 4));
            }
            return 0;
        }
    }
}

//Function to check whether HW resouces available or exhastued
static mepa_bool_t check_resources(mepa_device_t *dev, mepa_bool_t is_sc, u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 num_of_sa_rsrv = 0, num_of_rx_sa_inuse = 0, i, sc, sa;
    mepa_bool_t found_sc = 0, found_sa = 0, secy_in_use = 0;
    //Maximum SA that the PHY can support returned by mepa_capability function
    u32 macsec_max_port_sa = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SA);

    u32 macsec_max_sc_rx = macsec_max_port_sa / 2;
    u32 macsec_max_secy = macsec_max_sc_rx;
    num_of_sa_rsrv += MEPA_MACSEC_SA_PER_SC_MIN;

    for (i = 0; i < macsec_max_secy; i++) {
        secy = &data->macsec_conf.secy[i];
        found_sc = 0;
        if (secy->in_use) {
            secy_in_use++;
            for (sc = 0; sc < macsec_max_sc_rx; sc++) {
                if (secy->rx_sc[sc] != NULL) {
                    found_sc = 1;
                    break;
                }
            }
            if (!found_sc) { /* No SC installed yet */
                if (!(is_sc && (secy_id == i))) {
                    num_of_sa_rsrv += MEPA_MACSEC_SA_PER_SC_MIN;
                }
            }
        }
    }
    if (!is_sc && (secy_in_use == macsec_max_secy)) {
        return 0;
    }

    for (sc = 0; sc < macsec_max_sc_rx; sc++) {
        if (data->macsec_conf.rx_sc[sc].in_use) {
            for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
                if (data->macsec_conf.rx_sc[sc].sa[sa] != NULL) {
                    found_sa = 1;
                    break;
                }
            }
            if (!found_sa) { /* No SA installed yet */
                num_of_sa_rsrv += MEPA_MACSEC_SA_PER_SC_MIN;
            }
        }
    }

    for (sa = 0; sa < macsec_max_port_sa; sa++) {
        if (data->macsec_conf.rx_sa[sa].in_use) {
            num_of_rx_sa_inuse++;
        }
    }
    //checks whether any SA is available
    return (num_of_rx_sa_inuse + num_of_sa_rsrv <= macsec_max_port_sa);
}

static mepa_rc lan80xx_macsec_sa_enable(mepa_device_t *dev, mepa_port_no_t port_no, u32 record, mepa_bool_t egr, mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (enable) {
        if (record < LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM) {
            //Enable TCAM match of the particular SA
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_SET_1), 1 << record, 1 << record);
        } else if (record >= LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM  && record < LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_SET_2), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)));

        } else if (record >= LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM && record < LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_SET_3), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)));

        } else if (record >= LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM && record < LAN80XX_MACSEC_SAM_ENTRY_SET4_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_SET_4), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)));
        }
    } else {
        //If enable variable is zero it clears register.
        if (record < LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_CLEAR_1), (1 << record),
                            (1 << record));
        } else if (record >= LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM && record < LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_CLEAR_2), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)));

        } else if (record >= LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM && record < LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_CLEAR_3), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)));
        } else {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_CLEAR_4), (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)),
                            (1 << (record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)));
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_toggle(mepa_device_t *dev, mepa_port_no_t port_no, u32 new_record, u32 old_record, mepa_bool_t egr)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (old_record < LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_1), (1 << old_record), (1 << old_record));

    } else if (old_record >= LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM && old_record < LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_2), (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)),
                        (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)));

    } else if (old_record >= LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM && old_record < LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_3), (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)),
                        (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)));

    } else if (old_record >= LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM && old_record < LAN80XX_MACSEC_SAM_ENTRY_SET4_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_4), (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)),
                        (1 << (old_record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)));
    }

    if (new_record < LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_1), (1 << new_record), (1 << new_record));

    } else if (new_record >= LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM && new_record < LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_2), (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)),
                        (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET1_NUM)));

    } else if (new_record >= LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM && new_record < LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_3), (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)),
                        (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET2_NUM)));

    } else if (new_record >= LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM && new_record < LAN80XX_MACSEC_SAM_ENTRY_SET4_NUM) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_ENTRY_TOGGLE_4), (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)),
                        (1 << (new_record - LAN80XX_MACSEC_SAM_ENTRY_SET3_NUM)));
    }

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_inuse(mepa_device_t *dev, mepa_port_no_t port_no, u32 record, u32 sc, u8 an, mepa_bool_t egr, mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (sc < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        if (egr) {

            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X(sc),
                           LAN80XX_F_MACSEC_EGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0(record) |
                           (enable ? LAN80XX_M_MACSEC_EGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0 : 0));

        } else {
            switch (an) {
            case 0:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX0 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE0);
                break;
            case 1:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX1(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE1 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_INDEX1 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP1_X_SA_IN_USE1);
                break;
            case 2:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX2(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE2 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX2 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE2);
                break;
            case 3:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX3(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE3 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_INDEX3  |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE0_SAM_SC_SA_MAP2_X_SA_IN_USE3);
                break;
            default:
                T_E(MEPA_TRACE_GRP_GEN, "AN number cannot be more than 3 (range : 0 to 3)\n");
                return MEPA_RC_ERROR;
            }
        }
    } else {
        if (egr) {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X(sc - LAN80XX_MACSEC_SC_REC_PAGE0_NUM),
                           LAN80XX_F_MACSEC_EGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0(record) |
                           (enable ? LAN80XX_M_MACSEC_EGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0 : 0));
        } else {
            switch (an) {
            case 0:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X(sc - LAN80XX_MACSEC_SC_REC_PAGE0_NUM),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX0   |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE0);
                break;
            case 1:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X(sc - LAN80XX_MACSEC_SC_REC_PAGE0_NUM),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX1(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE1 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_INDEX1 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP1_X_SA_IN_USE1);
                break;
            case 2:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X(sc - LAN80XX_MACSEC_SC_REC_PAGE0_NUM),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX2(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE2 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX2 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE2);
                break;
            case 3:
                LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X(sc - LAN80XX_MACSEC_SC_REC_PAGE0_NUM),
                                LAN80XX_F_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX3(record) |
                                (enable ? LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE3 : 0),
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_INDEX3 |
                                LAN80XX_M_MACSEC_INGR_CORE_SC_SA_MAP_PAGE1_SAM_SC_SA_MAP2_X_SA_IN_USE3);
                break;
            default:
                T_E(MEPA_TRACE_GRP_GEN, "AN number cannot be more than 3 (range : 0 to 3)\n");
                return MEPA_RC_ERROR;
            }

        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sam_entry_ctrl(mepa_device_t *dev, mepa_port_no_t port_no, u32 record, mepa_bool_t egr, mepa_bool_t enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (enable) {
        if (egr) {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL,
                           LAN80XX_F_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_0(record) |
                           LAN80XX_M_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_0);
        } else {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL,
                           LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_SET_0(record) |
                           LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SET_ENABLE_0);
        }
    } else {
        if (egr) {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL,
                           LAN80XX_F_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_0(record) |
                           LAN80XX_M_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_0);
        } else {
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL,
                           LAN80XX_F_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_SAM_INDEX_CLEAR_0(record) |
                           LAN80XX_M_MACSEC_INGR_CORE_SAM_ENB_CTRL_SAM_ENTRY_ENABLE_CTRL_CLEAR_ENABLE_0);
        }
    }
    return MEPA_RC_OK;
}

static mepa_bool_t lan80xx_macsec_secy_in_use_inter_getnext(mepa_device_t *dev, phy25g_macsec_secy_in_use_iter_t *in_use_inter)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 i, max_secy;
    phy25g_macsec_internal_secy_t *secy;
    max_secy = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_SECY_CNT);
    for (i = in_use_inter->next_index; i < max_secy; i++) {
        in_use_inter->next_index++;
        secy = &data->macsec_conf.secy[i];
        if (secy->in_use) {
            in_use_inter->secy_id = i;
            return TRUE;
        }
    }
    return FALSE;                    // Indicate no more secy's that is in use
}

// Function to update the Validate frames register if no SC is found
static mepa_rc lan80xx_macsec_update_glb_validate(mepa_device_t *dev, mepa_port_no_t port_no)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_secy_in_use_iter_t in_use_inter;
    mepa_validate_frames_t val = MEPA_MACSEC_VALIDATE_FRAMES_STRICT;
    u32 sc, max_sc_rx;
    phy25g_macsec_internal_secy_t *secy;
    memset(&in_use_inter, 0, sizeof(phy25g_macsec_secy_in_use_iter_t));
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

    // Making validate frames as strict in the software side
    while (lan80xx_macsec_secy_in_use_inter_getnext(dev, &in_use_inter)) {
        secy = &data->macsec_conf.secy[in_use_inter.secy_id];
        if (!secy) {
            continue;
        }
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                continue;
            }
            if (secy->rx_sc[sc]->conf.validate_frames < val) {
                val = secy->rx_sc[sc]->conf.validate_frames;
            }
        }
    }
    /* If no Secure Channel is found then global validate frames is made as Strict in Hardware */
    LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_MISC_CONTROL,
                         LAN80XX_F_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_VALIDATE_FRAMES_0(val),
                         LAN80XX_M_MACSEC_INGR_MACSEC_INGR_MISC_CONTROL_MACSEC_VALIDATE_FRAMES_0);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_is_ssci_valid(mepa_device_t *dev,
                                     mepa_bool_t egr,
                                     const mepa_macsec_sci_t  *sci,
                                     const mepa_macsec_ssci_t *ssci,
                                     const mepa_macsec_sak_t  *sak)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 an = 0, sc = 0, max_sc_rx = 0;
    phy25g_macsec_internal_secy_t *secy;
    phy25g_macsec_secy_in_use_iter_t in_use_inter;

    if ((ssci == NULL) || (sci == NULL)) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid SSCI or SCI");
        return MEPA_RC_ERROR;
    }
    if (sak == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "Invalid SAK");
        return MEPA_RC_ERROR;
    }
    max_sc_rx =  lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

    /* Loop through all the SA's to check for same SSCI */
    memset(&in_use_inter, 0, sizeof(phy25g_macsec_secy_in_use_iter_t));
    while (lan80xx_macsec_secy_in_use_inter_getnext(dev, &in_use_inter)) {
        secy = &data->macsec_conf.secy[in_use_inter.secy_id];
        if (egr) {
            for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->tx_sc.sa[an] == NULL || !secy->tx_sc.sa[an]->in_use) {
                    continue;
                }
                if (!memcmp(ssci, &secy->tx_sc.sa[an]->ssci, sizeof(mepa_macsec_ssci_t))) {
                    T_E(MEPA_TRACE_GRP_GEN, "Tx SSCI duplicated for "LAN80XX_SCI_FMT" an:%u", LAN80XX_SCI_ARG(secy->sci), an);
                    return MEPA_RC_ERROR;
                }
            }
        } else {
            for (sc = 0; sc < max_sc_rx; sc++) {
                if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
                    continue;
                }
                for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an++) {
                    if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                        continue;
                    }
                    if (!memcmp(ssci, &secy->rx_sc[sc]->sa[an]->ssci, sizeof(mepa_macsec_ssci_t))) {
                        T_E(MEPA_TRACE_GRP_GEN, "Rx SSCI duplicated for "LAN80XX_SCI_FMT" an:%u", LAN80XX_SCI_ARG(secy->rx_sc[sc]->sci), an);
                        return MEPA_RC_ERROR;
                    }
                }
            }
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_record_empty_get(mepa_device_t *dev, mepa_port_no_t port_no, u32 *id, mepa_bool_t tx)
{
    u32 sa, max_sa;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    max_sa = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SA);
    if (tx) {
        for (sa = 0; sa < max_sa; sa++) {
            if (!data->macsec_conf.tx_sa[sa].in_use) {
                *id = sa;
                return MEPA_RC_OK;
            }
        }
    } else {
        for (sa = 0; sa < max_sa; sa++) {
            if (!data->macsec_conf.rx_sa[sa].in_use) {
                *id = sa;
                return MEPA_RC_OK;
            }
        }
    }

    T_D(MEPA_TRACE_GRP_GEN, "All available SA's are in use");
    return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_ALL_AVAILABLE_SA_IN_USE);
}

static mepa_rc lan80xx_macsec_sa_xform_set(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t egr, u32 record, phy25g_macsec_internal_secy_t *secy, u16 an, u32 sc)
{
    mepa_bool_t aes_128;
    mepa_bool_t xpn = FALSE;
    u32 i, mmd;
    mmd = egr ? MMD_ID_MACSEC_EGR : MMD_ID_MACSEC_INGR;
    T_I(MEPA_TRACE_GRP_GEN, "Record:%u SC:%u SA:%u  Dir:%s ", record, sc, an, egr ? "Egress" : "Ingress");
    if (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
        secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) {
        xpn = TRUE;
    }
    if (xpn != TRUE) {
        aes_128 = (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128) ? 1 : 0;
        for (i = 0; i < LAN80XX_MACSEC_XFORM_REC_SIZE; i++) {
            if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
                /* Transform Records PAGE0 register starts at address 0x0000 */
                MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE0_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)),
                                       lan80xx_get_xform_value(dev, i, egr, aes_128, secy, an, sc, record)));
            } else {
                /* Transform Records PAGE1 register starts at address 0x4000 */
                MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE1_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)),
                                       lan80xx_get_xform_value(dev, i, egr, aes_128, secy, an, sc, record)));
            }
        }
    } else {
        aes_128 = (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ? TRUE : FALSE;
        for (i = 0; i < LAN80XX_MACSEC_XFORM_REC_SIZE; i++) {
            if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
                /* Transform Records PAGE0 register starts at address 0x0000 */
                MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE0_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)),
                                       lan80xx_get_xform_value_64(dev, i, egr, aes_128, secy, an, sc, record)));
            } else {
                /* Transform Records PAGE1 register starts at address 0x4000 */
                MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE1_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)),
                                       lan80xx_get_xform_value_64(dev, i, egr, aes_128, secy, an, sc, record)));
            }
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_xform_reset(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t egr, u32 record, phy25g_macsec_internal_secy_t *secy,
                                             u16 an, u32 sc)
{
    u32 i = 0, mmd = 0;
    mmd = egr ? MMD_ID_MACSEC_EGR : MMD_ID_MACSEC_INGR;

    for (i = 0; i < LAN80XX_MACSEC_XFORM_REC_SIZE; i++) {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE0_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)), 0));
        } else {
            MEPA_RC(lan80xx_csr_wr(dev, port_no, mmd, LAN80XX_IS_REG_32, ((LAN80XX_MACSEC_XFORM_PAGE1_ADDR + i) | (record * LAN80XX_MACSEC_XFORM_REC_ADDR_OFFSET)), 0));
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_cleartags_conf_set_(mepa_device_t  *dev, mepa_port_no_t  port_no, mepa_bool_t  egr, u32  record,
                                                  const mepa_macsec_match_pattern_t  *pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_cleartags_conf_t *tags_conf;
    tags_conf = &data->macsec_conf.glb.cleartags_conf;
    u32 no_tags = 0, tags_ext = 0, lab_select = 0;
    u32 btag_id = 0, itag_id = 0, cus_id = 0;
    u32 label1, label2 = 0;

    if (tags_conf->packet_type == LAN80XX_PACKET_TYPE_MPLS) {
        if ((tags_conf->num_mpls_label > LAN80XX_MACSEC_EGR_MPLS_SUPPORT && egr) || (tags_conf->num_mpls_label > LAN80XX_MACSEC_INGR_MPLS_SUPPORT && (!egr))) {
            T_E(MEPA_TRACE_GRP_GEN, "EIP-161 Supports Maximum of 9 MPLS Labels in Egress side and 5 MPLS in Ingress Side");
            return MEPA_RC_ERROR;
        }
        /* configuring Number of MPLS Labels in TCAM KEY 0 register */
        no_tags = tags_conf->num_mpls_label <= LAN80XX_MACSEC_NUM_MPLS_LABEL_0 ? LAN80XX_BIT(tags_conf->num_mpls_label) : 0;
        tags_ext = tags_conf->num_mpls_label > LAN80XX_MACSEC_NUM_MPLS_LABEL_0 ? (tags_conf->num_mpls_label - LAN80XX_MACSEC_NUM_MPLS_LABEL_0) : 0;
        if (tags_conf->num_mpls_label > LAN80XX_MACSEC_EGR_MPLS_SUPPORT) {
            tags_ext = LAN80XX_BIT(3); /* Make 3rd bit as 1 for more than 9 MPLS Label */
        }
    } else if (tags_conf->packet_type == LAN80XX_PACKET_TYPE_PBB) {
        no_tags = LAN80XX_BIT(tags_conf->num_tag); /* Number of VLAN tags in PBB type packet */
    }

    /* Packet Type Configuration */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0(record)),
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_PACKET_TYPE(tags_conf->packet_type)) |
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS(no_tags)) |
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_MACSEC_TAGGED)  |
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS_EXT(tags_ext)));

    /* Destination MAC Address Configuration */
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1(record)),
                   lan80xx_get_u32(&pattern->dest_mac.addr[0]));

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2(record)),
                   pattern->dest_mac.addr[4] | (pattern->dest_mac.addr[5] << LAN80XX_8_BIT_SHIFT));

    if (tags_conf->packet_type == LAN80XX_PACKET_TYPE_PBB) {

        btag_id = tags_conf->pbb_conf.btag.vid;
        itag_id = tags_conf->pbb_conf.itag.vid;
        cus_id = tags_conf->pbb_conf.out_cus_vid;
        /* Configurating TCAM registers with PBB Packet Parameters */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4(record)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_11_8((btag_id >> LAN80XX_8_BIT_SHIFT) & LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_DEI(tags_conf->pbb_conf.btag.dei)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_PCP(tags_conf->pbb_conf.btag.pcp)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_BVLAN_ID_7_0(btag_id & LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_23_16((itag_id >> LAN80XX_16_BIT_SHIFT) & LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_SID_15_8((itag_id >> LAN80XX_8_BIT_SHIFT) & LAN80XX_BYTE_MASK)))

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(record)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_SID_7_0(itag_id & LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IDEI(tags_conf->pbb_conf.itag.dei)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_IPCP(tags_conf->pbb_conf.itag.pcp)));

        if (tags_conf->num_tag != LAN80XX_PBB_MPLS_VLAN_TAG_NONE) {
            LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(record)),
                            LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_11_8((cus_id >> LAN80XX_8_BIT_SHIFT) & LAN80XX_WORD_MASK)) |
                            LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_7_0(cus_id & LAN80XX_BYTE_MASK)),
                            LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_11_8) |
                            LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_OUT_VID_7_0));
        }
        /* Enable PBB_ENB_SELECT bit */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_PBB_ENB_SELECT),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_PBB_ENB_SELECT_PARSE_PBB));

    }

    if (tags_conf->packet_type == LAN80XX_PACKET_TYPE_MPLS) {

        label1 = tags_conf->mpls_conf.mpls1_label;
        label2 = tags_conf->mpls_conf.mpls2_label;

        /* MPLS Label 1 Comparision */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4(record)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_19_12((label1 >> LAN80XX_12_BIT_SHIFT)& LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_11_4((label1 >> LAN80XX_4_BIT_SHIFT) & LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_S(tags_conf->mpls_conf.mpls1_s)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_EXP(tags_conf->mpls_conf.mpls1_exp)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4_1_MPLS_LABEL_3_0(label1 & LAN80XX_WORD_MASK)));

        /* MPLS Label 2 Comparision */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(record)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_19_12((label2 >> LAN80XX_12_BIT_SHIFT)& LAN80XX_BYTE_MASK)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5_2_MPLS_LABEL_11_4((label2 >> LAN80XX_4_BIT_SHIFT) & LAN80XX_BYTE_MASK)) |
                       (lab_select << ((tags_conf->num_mpls_label - LAN80XX_MACSEC_3_MPLS_LABEL) * (2 * LAN80XX_MPLS_LABEL_SELECT_2_BIT))));

        /* Note
         * EIP-161 Supports Matching of only two MPLS Labels, so we need to select which two MPLS Labels need to be matched with parameters
         * configured in TCAM_KEY4 and TCAM_KEY5.
         * This MPLS Label can be selected by using MPLS_ENB_SELECT and MPLS_ENB_SELECT2 register
         */
        if (tags_conf->num_mpls_label == LAN80XX_MACSEC_5_MPLS_LABEL) {
            lab_select = ((tags_conf->mpls_conf.mpls2_num - 1) << LAN80XX_MPLS_LABEL_SELECT_3_BIT)  | (tags_conf->mpls_conf.mpls1_num - 1);
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_MPLS_ENB_SELECT, (lab_select << LAN80XX_8_BIT_SHIFT));
        }

        if (tags_conf->num_mpls_label >= LAN80XX_MACSEC_6_MPLS_LABEL && tags_conf->num_mpls_label <= LAN80XX_MACSEC_EGR_MAX_MPLS_LABEL) {
            lab_select = ((tags_conf->mpls_conf.mpls2_num - 1) << LAN80XX_MPLS_LABEL_SELECT_3_BIT)  | (tags_conf->mpls_conf.mpls1_num - 1);
            LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_MPLS_ENB_SELECT2,
                           (lab_select << ((tags_conf->num_mpls_label - LAN80XX_MACSEC_6_MPLS_LABEL) * (2 * LAN80XX_MPLS_LABEL_SELECT_3_BIT))));
        }

        /* Enable the MPLS Parsing */
        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_MPLS_ENB_SELECT,
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS1 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS2 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS3 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS4,
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS1 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS2 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS3 |
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_MPLS4);

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_MPLS_ENB_SELECT, LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_ELI,
                        LAN80XX_M_MACSEC_EGR_CORE_MPLS_ENB_SELECT_PARSE_ELI);

    }

    /* TCAM Matching rule configuration */
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_BVLAN_TAG) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_BVLAN_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_BVLAN_MASK));

    }
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_IVLAN_TAG) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_SID_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_SID_MASK));

        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_SID_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_SID_MASK));
    }
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_CVLAN) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_OUT_VID_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_OUT_VID_MASK));
    }
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_MPLS_1) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_1_MPLS_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_1_MPLS_MASK));
    }
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_MPLS_2) {
        LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_2_MPLS_MASK),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_2_MPLS_MASK));
    }
    if (tags_conf->match & LAN80XX_MACSEC_MATCH_DISABLE) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record)), 0x0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record)), 0x0);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_flow_set(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t egr, u32 record, phy25g_macsec_internal_secy_t *secy,
                                          u16 an, u32 sc, mepa_macsec_match_action_t action)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_cleartags_conf_t *tags_conf;
    tags_conf = &data->macsec_conf.glb.cleartags_conf;

    u32 tag_bypass = 0, offset = 0, validate = 0, dest_port = 0, flow_type = (egr ? 3 : 2);
    mepa_bool_t conf = 0, rp = 0, incl_sci = 0, use_es = 0, use_scb = 0, protect_frm = 0, auth_start = 0;;
    u16 sectag_offset = LAN80XX_MACSEC_STANDARD_SECTAG_OFFSET; /* MACsec standard sectag offset is 12 */
    u16 auth_len = LAN80XX_MAC_ADDRESS_LEN_BYTES;              /* MACsec authentication for MAC address */
    if (action == MEPA_MACSEC_MATCH_ACTION_DROP) {
        flow_type = 1;                                      /* Flow type Drop */
    } else if (action == MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT) {
        dest_port = 0;                                      /* Destination: Controlled port*/
    } else {
        dest_port = 3;                                      /* Destination: Uncontrolled port*/
        flow_type = 0;
    }
    if (secy != NULL) {
        if (egr) {
            conf = secy->tx_sc.sa[an]->confidentiality;
            protect_frm = secy->conf.protect_frames;
            incl_sci = secy->conf.always_include_sci;
            use_es = secy->conf.use_es;
            use_scb = secy->conf.use_scb;
            offset = secy->conf.confidentiality_offset;
        } else {
            rp = secy->rx_sc[sc]->conf.replay_protect;
            offset = secy->rx_sc[sc]->conf.confidentiality_offset;
            if (!((secy->rx_sc[sc]->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_DISABLED) |
                  (secy->rx_sc[sc]->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_CHECK) |
                  (secy->rx_sc[sc]->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_STRICT))) {
                T_E(MEPA_TRACE_GRP_GEN, "validate_frames value invalid, sc:%d, an:%d", sc, an);
                return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_INVALID_VALIDATE_FRM);
            }
            validate = secy->rx_sc[sc]->conf.validate_frames;
            /* Update the global 'validate frames' */
            /* The value is the least of all validate_frames entires of all SecYs, i.e. disabled/check/strict */
            MEPA_RC(lan80xx_macsec_update_glb_validate(dev, port_no));
        }
        tag_bypass = secy->tag_bypass;
    }

    if (data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_HDR && data->macsec_conf.glb.cleartags_init_done == 1) {
        if (tags_conf->packet_type == LAN80XX_PACKET_TYPE_PBB) {
            auth_start = LAN80XX_MACSEC_PBB_AUTH_START;
            switch (tags_conf->sectag_off) {
            case LAN80XX_PBB_SECTAG_AFT_CMAC:
                sectag_offset = LAN80XX_MACSEC_PBB_HEADER_BYTES;  /* Insert Sectag after PBB header */
                break;
            case LAN80XX_PBB_SECTAG_AFT_1TAG:
                sectag_offset = LAN80XX_MACSEC_PBB_HEADER_BYTES + LAN80XX_VLAN_TAG_LEN_BYTE;
                break;
            default:
                sectag_offset = LAN80XX_MACSEC_PBB_HEADER_BYTES + LAN80XX_VLAN_TAG_LEN_BYTE + LAN80XX_VLAN_TAG_LEN_BYTE;
                break;
            }
        } else if ((tags_conf->packet_type == LAN80XX_PACKET_TYPE_MPLS) && (tags_conf->is_eo_mpls == 0)) {
            auth_start = 0;
            auth_len = 0;
            sectag_offset = LAN80XX_MAC_ADDRESS_LEN_BYTES + LAN80XX_ETHER_TYPE_LEN_BYTES  + (tags_conf->num_mpls_label * LAN80XX_MPLS_LABEL_LEN_BYTE);
            if (tags_conf->is_pw_ctrl_word == 1) {
                sectag_offset += LAN80XX_MPLS_PW_CTRL_WORD_LEN;
            }
        } else if ((tags_conf->packet_type == LAN80XX_PACKET_TYPE_MPLS) && (tags_conf->is_eo_mpls == 1)) {
            auth_start = LAN80XX_MAC_ADDRESS_LEN_BYTES + LAN80XX_ETHER_TYPE_LEN_BYTES  + (tags_conf->num_mpls_label * LAN80XX_MPLS_LABEL_LEN_BYTE);
            auth_start = tags_conf->is_pw_ctrl_word == 1 ? auth_start + LAN80XX_MPLS_PW_CTRL_WORD_LEN : auth_start;
            sectag_offset = auth_start + LAN80XX_MAC_ADDRESS_LEN_BYTES;
            switch (tags_conf->sectag_off) {
            case LAN80XX_PBB_SECTAG_AFT_1TAG:
                sectag_offset += LAN80XX_VLAN_TAG_LEN_BYTE;
                break;
            case LAN80XX_PBB_SECTAG_AFT_2TAG:
                sectag_offset += (2 * LAN80XX_VLAN_TAG_LEN_BYTE);
                break;
            default:
                sectag_offset = auth_start + LAN80XX_MAC_ADDRESS_LEN_BYTES;
                break;
            }
        }
    }

    if (data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_TAG) {
        sectag_offset = LAN80XX_MAC_ADDRESS_LEN_BYTES + (LAN80XX_VLAN_TAG_LEN_BYTE * tag_bypass);
    }

    if (sc < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        if (egr) {
            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1(sc),
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_TYPE(flow_type) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DEST_PORT(dest_port) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_ACTION(2)       |
                                (protect_frm ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_PROTECT_FRAME : 0) |
                                (conf ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_CONF_PROTECT : 0 )    |
                                (incl_sci ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_INCLUDE_SCI : 0) |
                                (use_es ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_USE_ES : 0) |
                                (use_scb ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_USE_SCB : 0) |
                                LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_DATA_PACKETS |
                                (tags_conf->is_eo_mpls ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_SUBPORT : 0) |
                                (tags_conf->is_pw_ctrl_word ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_CTRL_WORD : 0) |
                                LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_PREEMPT_EOP_GROWTH);

            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2(sc),
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(0)  |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(auth_len) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_SECTAG_OFFSET(sectag_offset) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(offset));
        } else {
            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_FLOW_TYPE(flow_type) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DEST_PORT(dest_port) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_DROP_ACTION(2)       |
                                (rp ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_REPLAY_PROTECT : 0) |
                                LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_TAGGED_DATA    |
                                LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA  |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(validate) |
                                (tags_conf->is_eo_mpls ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_SUBPORT : 0) |
                                (tags_conf->is_pw_ctrl_word ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1_EOMPLS_CTRL_WORD : 0));

            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(0)  |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(auth_len) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(offset));

        }
    } else {
        if (egr) {
            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1(sc - 32),
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_TYPE(flow_type) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DEST_PORT(dest_port) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_ACTION(2)       |
                                (protect_frm ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_PROTECT_FRAME : 0) |
                                (conf ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_CONF_PROTECT : 0)    |
                                (incl_sci ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_INCLUDE_SCI : 0) |
                                (use_es ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_USE_ES : 0) |
                                (use_scb ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_USE_SCB : 0) |
                                LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_DATA_PACKETS |
                                (tags_conf->is_eo_mpls ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_SUBPORT : 0) |
                                (tags_conf->is_pw_ctrl_word ? LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_CTRL_WORD : 0) |
                                LAN80XX_M_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_PREEMPT_EOP_GROWTH);

            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2(sc - 32),
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(0)  |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(auth_len) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_SECTAG_OFFSET(sectag_offset) |
                                LAN80XX_F_MACSEC_EGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(offset));
        } else {
            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE0_FLOW_CTRL_1(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_FLOW_TYPE(flow_type) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DEST_PORT(dest_port) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_DROP_ACTION(2)       |
                                (rp ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_REPLAY_PROTECT : 0) |
                                LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_TAGGED_DATA    |
                                LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_ALLOW_UNTAGGED_DATA  |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_VALIDATE_FRAMES_TAGGED(validate) |
                                (tags_conf->is_eo_mpls ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_SUBPORT : 0) |
                                (tags_conf->is_pw_ctrl_word ? LAN80XX_M_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_1_EOMPLS_CTRL_WORD : 0));


            LAN80XX_CSR_WARM_WR(port_no, LAN80XX_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2(sc),
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_START(0)  |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_PRE_SECTAG_AUTH_LEN(auth_len) |
                                LAN80XX_F_MACSEC_INGR_CORE_EIP_FLOW_CTRL_PAGE1_FLOW_CTRL_2_CONFIDENTIALITY_OFFSET(offset));

        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_tcam_key_mask_set(mepa_device_t *dev,
                                                   mepa_port_no_t port_no,
                                                   mepa_bool_t egr,
                                                   u32 record,
                                                   phy25g_macsec_internal_secy_t *secy,
                                                   u16 an,
                                                   u32 sc,
                                                   const mepa_macsec_match_pattern_t *pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    /* Bypass Cleartags Header */
    if (data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_HDR &&
        data->macsec_conf.glb.cleartags_init_done) {
        rc = lan80xx_macsec_cleartags_conf_set_(dev, port_no, egr, record, pattern);
        return rc;
    }
    u8 page1 = record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0 ? 0 : 1;
    u32 tag_bypass = secy->tag_bypass;
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0(record)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_NUM_TAGS(1 << tag_bypass)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0_MACSEC_TAGGED));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1(record)),
                       lan80xx_get_u32(&pattern->dest_mac.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2(record)),
                       pattern->dest_mac.addr[4] | (pattern->dest_mac.addr[5] << 8));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4(record)),
                       MACSEC_BS(pattern->etype) | (MACSEC_BS(pattern->vid) << 16));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(record)),
                       MACSEC_BS(pattern->vid_inner) << 8);
    } else {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_NUM_TAGS(1 << tag_bypass)) |
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0_MACSEC_TAGGED));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)),
                       lan80xx_get_u32(&pattern->dest_mac.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)),
                       pattern->dest_mac.addr[4] | (pattern->dest_mac.addr[5] << 8));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)),
                       MACSEC_BS(pattern->etype) | (MACSEC_BS(pattern->vid) << 16));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)),
                       (MACSEC_BS(pattern->vid_inner) << 8));
    }
    /* MASK registers are configured based on "match" value provided by the user */
    if (pattern->match & MEPA_MACSEC_MATCH_SMAC) {
        T_E(MEPA_TRACE_GRP_GEN, "Source MAC Address matching is not supported ");
        return MEPA_RC_ERROR;
    }

    if (pattern->match & MEPA_MACSEC_MATCH_DMAC) {

        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1(record))),
                       LAN80XX_MACSEC_TCAM_DESADDR_1_MASK);


        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2(record))),
                       LAN80XX_MACSEC_TCAM_DESADDR_2_MASK);
    }

    if (pattern->match & MEPA_MACSEC_MATCH_ETYPE) {

        LAN80XX_CSR_WRM(port_no, (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                                  LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record))),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_ETHERTYPE_MASK(LAN80XX_MACSEC_TCAM_ETHTYPE_MASK)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_ETHERTYPE_MASK(LAN80XX_MACSEC_TCAM_ETHTYPE_MASK)));
    }

    if ((pattern->match & MEPA_MACSEC_MATCH_VLAN_ID) && (pattern->match & MEPA_MACSEC_MATCH_HAS_VLAN)) {
        LAN80XX_CSR_WRM(port_no, (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                                  LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record))),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_VLANTAG_MASK(LAN80XX_MACSEC_TCAM_VLANTAG_MASK)),
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4_VLANTAG_MASK(LAN80XX_MACSEC_TCAM_VLANTAG_MASK)));
    }

    if ((pattern->match & MEPA_MACSEC_MATCH_VLAN_ID_INNER) && (pattern->match & MEPA_MACSEC_MATCH_HAS_VLAN_INNER)) {
        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record))),
                       LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5_INNER_VLANTAG_MASK(LAN80XX_MACSEC_TCAM_VLANTAG_MASK)));
    }

    if (pattern->match & MEPA_MACSEC_MATCH_DISABLE) {
        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1(record))), 0);

        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2(record))), 0);

        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record))), 0);

        LAN80XX_CSR_WR(dev, port_no,
                       (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                        LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record))), 0);
    }

    /* TCAM Priority configuration */
    if (pattern->priority > 15) {
        T_E(MEPA_TRACE_GRP_GEN, "Pattern priority should be less than 15");
        return MEPA_RC_ERROR;
    }
    LAN80XX_CSR_WR(dev, port_no,
                   (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                    LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY(record))),
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_VPORT_INDEX(sc)) |
                   LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_F, egr, CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY_PRIO(15 - pattern->priority)));

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_tcam_key_mask_reset(mepa_device_t *dev, mepa_port_no_t port_no, mepa_bool_t egr, u32 record)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;

    MEPA_RC(lan80xx_macsec_sam_entry_ctrl(dev, port_no, record, egr, 0));

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY0(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY1(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY2(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY4(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_KEY5(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK0(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK1(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK2(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK4(record)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE0_TCAM_MASK5(record)), 0);
    } else {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY0(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY1(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY2(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_KEY5(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK0(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK1(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK2(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK4(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_KEY_MASK_PAGE1_TCAM_MASK5(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)), 0);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sa_tcam_policy_unctrl_drop(mepa_device_t *dev, mepa_port_no_t port_no, u32 record, mepa_bool_t egr, mepa_macsec_match_action_t action)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u8 page1 = record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0 ? 0 : 1;

    LAN80XX_CSR_WRM(port_no, (page1 ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0)) :
                              LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_EIP_TCAM_POLICY_PAGE0_TCAM_POLICY(record))),
                    ((action == MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT) ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_CONTROL_PKT) : 0) |
                    ((action == MEPA_MACSEC_MATCH_ACTION_DROP) ? LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_DROP) : 0),
                    LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_CONTROL_PKT) |
                    LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_EIP_TCAM_POLICY_PAGE1_TCAM_POLICY_DROP))

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_sa_sam_in_flight(mepa_device_t *dev, mepa_port_no_t port_no,  mepa_bool_t egr)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val = 0, count = 0;

    LAN80XX_CSR_WRM(port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT),
                    LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE),
                    LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX_M, egr, CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_LOAD_UNSAFE));
    do {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT), &val);
        MEPA_MSLEEP(1);
        count++;
        if (count == 100) {
            T_E(MEPA_TRACE_GRP_GEN, "timeout, bailing out");
            return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_TIMEOUT_ISSUE);
        }
    } while (LAN80XX_F_MACSEC_EGR_CORE_SAM_ENB_CTRL_SAM_IN_FLIGHT_UNSAFE(val)); /* wait until UNSAFE field become zero */
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_port_get_next_priv(mepa_device_t *dev,
                                          const mepa_port_no_t        port_no,
                                          const mepa_macsec_port_t    *const search_macsec_port,
                                          mepa_macsec_port_t          *const found_macsec_port)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 i, max_secy;
    mepa_bool_t found_port = 0;
    max_secy = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_SECY_CNT);

    for (i = 0; i < max_secy; i++) {
        secy = &data->macsec_conf.secy[i];
        if (secy != NULL && secy->in_use) {
            if (search_macsec_port == NULL || found_port) {
                found_macsec_port->port_no = port_no;
                found_macsec_port->service_id = secy->service_id;
                found_macsec_port->port_id = secy->sci.port_id;
                break;
            } else {
                if (search_macsec_port->service_id == secy->service_id && search_macsec_port->port_id == secy->sci.port_id) {
                    found_port = 1; // found the search port, return the next
                }
            }
        }
    }

    if (max_secy == i) {
        return MEPA_RC_ERROR; // No more ports
    }
    return MEPA_RC_OK;
}

// ** TX_SA counters **
static mepa_rc lan80xx_macsec_tx_sa_counters_get_(mepa_device_t   *dev,
                                                  const mepa_port_no_t            port_no,
                                                  const u16                       an,
                                                  mepa_macsec_tx_sa_counters_t    *const counters,
                                                  u32                              secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u64 cnt = 0;
    u32 record = 0;
    u64 out_pkts_encrypted = 0;
    memset(counters, 0, sizeof(mepa_macsec_tx_sa_counters_t));

    if (!secy->tx_sc.in_use) {
        T_I(MEPA_TRACE_GRP_GEN, "TX_SC does not exist");
        return MEPA_RC_OK;
    }
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    if (!secy->tx_sc.sa[an]) {
        return MEPA_RC_OK;
    }
    record = secy->tx_sc.sa[an]->record;

    // Encrypted and protected shares the same counters. Which once that is using the counters depends upon confidentiality
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE0_OUTPKTSENCRYPTEDPROTECTED_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE1_OUTPKTSENCRYPTEDPROTECTED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    if (secy->tx_sc.sa[an]->confidentiality) {
        secy->tx_sc.sa[an]->cnt.out_pkts_encrypted += cnt;
        secy->tx_sc.sa[an]->cnt.out_pkts_protected = 0;
        secy->tx_sc.cnt.out_pkts_encrypted += cnt;
        secy->tx_sc.cnt.out_pkts_protected = 0;
        out_pkts_encrypted = cnt;
    } else {
        secy->tx_sc.sa[an]->cnt.out_pkts_encrypted = 0;
        secy->tx_sc.sa[an]->cnt.out_pkts_protected += cnt;
        secy->tx_sc.cnt.out_pkts_encrypted = 0;
        secy->tx_sc.cnt.out_pkts_protected += cnt;
    }
    /* Update SC Octets counters, Not available in SA */
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE0_OUTOCTETSENCRYPTEDPROTECTED_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE1_OUTOCTETSENCRYPTEDPROTECTED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }

    if (secy->conf.protect_frames == FALSE) {
        secy->tx_sc.out_octets_untagged += cnt;
    } else if (secy->tx_sc.sa[an]->confidentiality) {
        if (cnt > (out_pkts_encrypted * secy->conf.confidentiality_offset)) {
            secy->tx_sc.cnt.out_octets_encrypted += cnt - (out_pkts_encrypted * secy->conf.confidentiality_offset);
            secy->secy_cnt.out_octets_encrypted += cnt - (out_pkts_encrypted * secy->conf.confidentiality_offset);
            secy->tx_sc.cnt.out_octets_protected += (out_pkts_encrypted * secy->conf.confidentiality_offset);
            secy->secy_cnt.out_octets_protected += (out_pkts_encrypted * secy->conf.confidentiality_offset);
        } else {
            secy->tx_sc.cnt.out_octets_protected += cnt;
        }
    } else {
        secy->tx_sc.cnt.out_octets_protected += cnt;
        secy->secy_cnt.out_octets_protected += cnt;
    }

    /* Update SecY counters */
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE0_OUTPKTSTOOLONG_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_STAT_SA_COUNTERS_PAGE1_OUTPKTSTOOLONG_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->secy_cnt.out_pkts_too_long += cnt;
    memcpy(counters, &secy->tx_sc.sa[an]->cnt, sizeof(mepa_macsec_tx_sa_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sc_counters_get_(mepa_device_t                   *dev,
                                                  const mepa_port_no_t            port_no,
                                                  mepa_macsec_tx_sc_counters_t    *const counters,
                                                  u32                             secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 an = 0;
    mepa_macsec_tx_sa_counters_t tx_sa_counters;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    memset(counters, 0, sizeof(mepa_macsec_tx_sc_counters_t));

    for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an ++ ) {
        /* SA counters get will update corresponding SC counters as well */
        MEPA_RC(lan80xx_macsec_tx_sa_counters_get_(dev, port_no, an, &tx_sa_counters, secy_id));
        T_I(MEPA_TRACE_GRP_GEN, "encrypted cnt: %d\n", tx_sa_counters.out_pkts_encrypted);
    }
    /* Update deleted SA counters  for this SC*/
    secy->tx_sc.cnt.out_pkts_encrypted   += secy->tx_sc.del_tx_sa_cnt.out_pkts_encrypted;
    secy->tx_sc.cnt.out_pkts_protected   += secy->tx_sc.del_tx_sa_cnt.out_pkts_protected;
    // Pass the counters
    memcpy(counters, &data->macsec_conf.secy[secy_id].tx_sc.cnt, sizeof(mepa_macsec_tx_sc_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_counters_get_(mepa_device_t                *dev,
                                                  const mepa_port_no_t         port_no,
                                                  const mepa_macsec_sci_t      *const sci,
                                                  const u16                    an,
                                                  mepa_macsec_rx_sa_counters_t *const counters,
                                                  u32                          secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0, record = 0;
    u64 cnt = 0, in_ok_pkts = 0;
    memset(counters, 0, sizeof(mepa_macsec_rx_sa_counters_t));
    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    record = secy->rx_sc[sc]->sa[an]->record;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSOK_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSOK_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok += cnt;
    in_ok_pkts = cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSINVALID_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSINVALID_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_invalid += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTVALID_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTVALID_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_valid += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTUSINGSA_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTUSINGSA_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_using_sa += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNUSEDSA_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNUSEDSA_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_unused_sa += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSUNCHECKED_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSUNCHECKED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_unchecked += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSDELAYED_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSDELAYED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_delayed += cnt;

    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSLATE_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSLATE_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    secy->rx_sc[sc]->sa[an]->cnt.in_pkts_late += cnt;

    /* Update SC Specific  counters */
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSDECRYPTED_LO(record), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSDECRYPTED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
    }
    /* UNG_MALIBU_25G-2497 inpkts_ok, inpkts_invalid and inpkts_notvalid MACsec counters gives random values in A0 and A1 - RTL bug*/
    if (data->dev.rev == LAN80XX_REV_A0 || data->dev.rev == LAN80XX_REV_A1) {
        secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok = in_ok_pkts = 0;
        secy->rx_sc[sc]->sa[an]->cnt.in_pkts_invalid  = 0;
        secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_valid = 0;
        if (secy->conf.confidentiality_offset > 0) {
            T_E(MEPA_TRACE_GRP_GEN, "\n octets_decrypted and in_octets_validated counters fails as in_pkts_ok is not valid, RTL issue on port : %d\n", port_no);
        }
    }

    if (secy->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_STRICT) {
        if (cnt > (in_ok_pkts * secy->conf.confidentiality_offset)) {
            secy->rx_sc[sc]->cnt.in_octets_decrypted += cnt - (in_ok_pkts * secy->conf.confidentiality_offset);
            secy->rx_sc[sc]->cnt.in_octets_validated += in_ok_pkts * secy->conf.confidentiality_offset;
        } else {
            secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
        }
    }

    if (secy->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_DISABLED) {
        secy->rx_sc[sc]->in_octets_validation_disabled += cnt;
    }
    // Pass the counters
    memcpy(counters, &secy->rx_sc[sc]->sa[an]->cnt, sizeof(mepa_macsec_rx_sa_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sc_counters_get_(mepa_device_t                   *dev,
                                                  const mepa_port_no_t            port_no,
                                                  const mepa_macsec_sci_t         *const sci,
                                                  mepa_macsec_rx_sc_counters_t    *const counters,
                                                  u32                              secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0, an = 0;
    mepa_macsec_rx_sa_counters_t rx_sa_counters;

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");
    memset(counters, 0, sizeof(mepa_macsec_rx_sc_counters_t));

    /* Clear counters maintained in SA's Donot clear Octets counters*/
    secy->rx_sc[sc]->cnt.in_pkts_ok             = 0;
    secy->rx_sc[sc]->cnt.in_pkts_invalid        = 0;
    secy->rx_sc[sc]->cnt.in_pkts_not_valid      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_not_using_sa   = 0;
    secy->rx_sc[sc]->cnt.in_pkts_unused_sa      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_unchecked      = 0;
    secy->rx_sc[sc]->cnt.in_pkts_delayed        = 0;
    secy->rx_sc[sc]->cnt.in_pkts_late           = 0;

    for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an ++ ) {
        if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
            continue;
        }
        MEPA_RC(lan80xx_macsec_rx_sa_counters_get_(dev, port_no, sci, an, &rx_sa_counters, secy_id));

        secy->rx_sc[sc]->cnt.in_pkts_ok            += rx_sa_counters.in_pkts_ok;
        secy->rx_sc[sc]->cnt.in_pkts_invalid       += rx_sa_counters.in_pkts_invalid;
        secy->rx_sc[sc]->cnt.in_pkts_not_valid     += rx_sa_counters.in_pkts_not_valid;
        secy->rx_sc[sc]->cnt.in_pkts_not_using_sa  += rx_sa_counters.in_pkts_not_using_sa;
        secy->rx_sc[sc]->cnt.in_pkts_unused_sa     += rx_sa_counters.in_pkts_unused_sa;
        secy->rx_sc[sc]->cnt.in_pkts_unchecked     += rx_sa_counters.in_pkts_unchecked;
        secy->rx_sc[sc]->cnt.in_pkts_delayed       += rx_sa_counters.in_pkts_delayed;
        secy->rx_sc[sc]->cnt.in_pkts_late          += rx_sa_counters.in_pkts_late;
    }

    /* Update deleted Rx SA counters for this SC */
    secy->rx_sc[sc]->cnt.in_pkts_ok            += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_ok;
    secy->rx_sc[sc]->cnt.in_pkts_invalid       += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_invalid;
    secy->rx_sc[sc]->cnt.in_pkts_not_valid     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_valid;
    secy->rx_sc[sc]->cnt.in_pkts_not_using_sa  += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_using_sa;
    secy->rx_sc[sc]->cnt.in_pkts_unused_sa     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unused_sa;
    secy->rx_sc[sc]->cnt.in_pkts_unchecked     += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unchecked;
    secy->rx_sc[sc]->cnt.in_pkts_delayed       += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_delayed;
    secy->rx_sc[sc]->cnt.in_pkts_late          += secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_late;

    // Pass the counters
    memcpy(counters, &secy->rx_sc[sc]->cnt, sizeof(mepa_macsec_rx_sc_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_txsa_counters_clear_(mepa_device_t         *dev,
                                                   const u16             an,
                                                   u32                   secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    secy = &data->macsec_conf.secy[secy_id];
    if (secy->tx_sc.in_use != TRUE) {
        T_E(MEPA_TRACE_GRP_GEN, "Tx SC does not exist");
    }
    if ((secy->tx_sc.sa[an] == NULL) || (!secy->tx_sc.sa[an]->in_use)) {
        T_E(MEPA_TRACE_GRP_GEN, "Tx SA does not exist");
    }
    /* Clear Tx SA counters */
    memset(&secy->tx_sc.sa[an]->cnt, 0, sizeof(mepa_macsec_tx_sa_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rxsc_counters_clear_(mepa_device_t *dev,
                                                   const mepa_macsec_sci_t *const sci_id,
                                                   u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u8 max_rxsc;
    u8 rxsc_idx;
    max_rxsc = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);
    /* Clear Rx SC counters */
    for (rxsc_idx = 0; rxsc_idx < max_rxsc; rxsc_idx++) {
        if ((secy->rx_sc[rxsc_idx] != NULL) && (secy->rx_sc[rxsc_idx]->in_use)) {
            if (lan80xx_sci_cmp(sci_id, &secy->rx_sc[rxsc_idx]->sci)) {
                memset(&secy->rx_sc[rxsc_idx]->cnt, 0, sizeof(mepa_macsec_rx_sc_counters_t));
                memset(&secy->rx_sc[rxsc_idx]->del_rx_sa_cnt, 0, sizeof(mepa_macsec_rx_sa_counters_t));
                return MEPA_RC_OK;
            }
        }
    }
    T_E(MEPA_TRACE_GRP_GEN, "Rx SC does not exist");
    return MEPA_RC_ERROR;
}

static mepa_rc lan80xx_macsec_rxsa_counters_clear_(mepa_device_t            *dev,
                                                   const mepa_macsec_sci_t  *const sci_id,
                                                   const u16                an,
                                                   u32                      secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 rxsc_idx = 0;
    secy = &data->macsec_conf.secy[secy_id];
    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci_id, &rxsc_idx));
    if ((secy->rx_sc[rxsc_idx] == NULL) || (secy->rx_sc[rxsc_idx]->in_use != TRUE)) {
        T_E(MEPA_TRACE_GRP_GEN, "Rx SC does not exist");
    }
    if ((secy->rx_sc[rxsc_idx]->sa[an] == NULL) | (!secy->rx_sc[rxsc_idx]->sa[an]->in_use)) {
        T_E(MEPA_TRACE_GRP_GEN, "Rx SA does not exist");
    }
    /* Clear Rx SA counters */
    memset(&secy->rx_sc[rxsc_idx]->sa[an]->cnt, 0, sizeof(mepa_macsec_rx_sa_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_secy_counters_get_(mepa_device_t                 *dev,
                                                 const mepa_port_no_t          port_no,
                                                 mepa_macsec_secy_counters_t   *const counters,
                                                 u32                           secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 record = 0;
    u64 cnt = 0;
    u16 sc = 0, max_sc_rx, an;
    u64 out_pkts_encrypt = 0;
    u64 in_ok_pkts = 0, not_using_sa_cnt = 0;
    mepa_macsec_tx_sc_counters_t tx_sc_counters = {0};
    memset(counters, 0, sizeof(*counters));
    if (secy->tx_sc.in_use) {
        MEPA_RC(lan80xx_macsec_tx_sc_counters_get_(dev, port_no, &tx_sc_counters, secy_id));
        secy->tx_sc.cnt.out_octets_encrypted = tx_sc_counters.out_octets_encrypted;
        secy->tx_sc.cnt.out_octets_protected = tx_sc_counters.out_octets_protected;

        for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an ++ ) {
            if (secy->tx_sc.sa[an]) {
                out_pkts_encrypt += secy->tx_sc.sa[an]->cnt.out_pkts_protected + secy->tx_sc.sa[an]->cnt.out_pkts_encrypted;
            }
        }
    }
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SA) / 2;
    // RX an
    secy->secy_cnt.in_octets_validated = 0;
    secy->secy_cnt.in_octets_decrypted  = 0;
    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use) {
            continue;
        }

        for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an ++ ) {
            if (secy->rx_sc[sc]->sa[an] == NULL || !secy->rx_sc[sc]->sa[an]->in_use) {
                continue;
            }

            record = secy->rx_sc[sc]->sa[an]->record;
            /* Get the OK packets counter for calculating decrypted and validated bytes */
            if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSOK_LO(record), &cnt);
            } else {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSOK_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
            }
            secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok += cnt;
            in_ok_pkts = cnt;
            // Decrypted and validated shares the same counters.
            if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INOCTETSDECRYPTED_LO(record), &cnt);
            } else {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INOCTETSDECRYPTED_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
            }
            if (secy->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_STRICT) {
                if (cnt > (in_ok_pkts * secy->conf.confidentiality_offset)) {
                    secy->rx_sc[sc]->cnt.in_octets_decrypted += cnt - (in_ok_pkts * secy->conf.confidentiality_offset);
                    secy->rx_sc[sc]->cnt.in_octets_validated += in_ok_pkts * secy->conf.confidentiality_offset;
                } else {
                    secy->rx_sc[sc]->cnt.in_octets_validated += cnt;
                }
            }
            if (secy->conf.validate_frames == MEPA_MACSEC_VALIDATE_FRAMES_DISABLED) {
                secy->rx_sc[sc]->in_octets_validation_disabled += cnt;
            }

            if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE0_INPKTSNOTUSINGSA_LO(record), &cnt);
            } else {
                LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_STAT_SA_COUNTERS_PAGE1_INPKTSNOTUSINGSA_LO(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &cnt);
            }
            secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_using_sa += cnt;
            not_using_sa_cnt += secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_using_sa;

            /* UNG_MALIBU_25G-2497 inpkts_ok, inpkts_invalid and inpkts_notvalid MACsec counters gives random values in A0 and A1 - RTL bug*/
            if (data->dev.rev == LAN80XX_REV_A0 || data->dev.rev == LAN80XX_REV_A1) {
                secy->rx_sc[sc]->sa[an]->cnt.in_pkts_ok = in_ok_pkts = 0;
                secy->rx_sc[sc]->sa[an]->cnt.in_pkts_invalid  = 0;
                secy->rx_sc[sc]->sa[an]->cnt.in_pkts_not_valid = 0;
                if (secy->conf.confidentiality_offset > 0) {
                    T_E(MEPA_TRACE_GRP_GEN, "\n octets_decrypted and in_octets_validated counters fails as in_pkts_ok is not valid, RTL issue on port : %d\n",
                        port_no);
                }
            }
        }
        secy->secy_cnt.in_octets_validated += secy->rx_sc[sc]->cnt.in_octets_validated;
        secy->secy_cnt.in_octets_decrypted += secy->rx_sc[sc]->cnt.in_octets_decrypted;
    }

    // in_pkts_no_sci
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOSCI_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOSCI_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    //in_pkts_unknown_sci
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNKNOWNSCI_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNKNOWNSCI_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    secy->secy_cnt.in_pkts_unknown_sci += cnt;

    // in_pkts_bad_tag
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSBADTAG_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSBADTAG_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    secy->secy_cnt.in_pkts_bad_tag += cnt;

    // Untagged
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_STAT_SECY_COUNTERS_PAGE0_OUTPKTSUNTAGGED_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_STAT_SECY_COUNTERS_PAGE1_OUTPKTSUNTAGGED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    secy->secy_cnt.out_pkts_untagged += cnt;

    //  in_pkts_no_tag
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSNOTAG_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSNOTAG_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    secy->secy_cnt.in_pkts_no_tag += cnt;

    //in_pkts_untagged
    if (secy_id < LAN80XX_MACSEC_SC_REC_PAGE0_NUM) {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE0_INPKTSUNTAGGED_LO(secy_id), &cnt);
    } else {
        LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_MACSEC_INGR_CORE_STAT_SECY_COUNTERS_PAGE1_INPKTSUNTAGGED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM), &cnt);
    }
    secy->secy_cnt.in_pkts_untagged += cnt;
    // Overrun - condition does not occur, report as zero.
    secy->secy_cnt.in_pkts_overrun = 0;

    secy->secy_cnt.in_pkts_no_sa_error = secy->secy_cnt.in_pkts_no_sci + not_using_sa_cnt;

    memcpy(counters, &data->macsec_conf.secy[secy_id].secy_cnt, sizeof(*counters));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_controlled_counters_get_(mepa_device_t                       *dev,
                                                       const mepa_macsec_port_t            port,
                                                       mepa_macsec_secy_port_counters_t    *const counters,
                                                       u32                                 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    memset(counters, 0, sizeof(mepa_macsec_secy_port_counters_t));
    u8 page1 = secy_id > LAN80XX_MACSEC_SC_REC_PAGE0_NUM ? 1 : 0;
    u64 cnt = 0;
    u32 port_no = port.port_no;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_in_octets += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_in_ucast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_in_multicast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_in_broadcast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTOCTETSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTOCTETSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_out_octets += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTUCASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTUCASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_out_ucast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTMULTICASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTMULTICASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_out_multicast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTBROADCASTPKTSCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTBROADCASTPKTSCONTROLLED_LO(secy_id), &cnt);

    secy->controlled_cnt.if_out_broadcast_pkts += cnt;

    secy->controlled_cnt.if_in_pkts = secy->controlled_cnt.if_in_ucast_pkts + secy->controlled_cnt.if_in_multicast_pkts + secy->controlled_cnt.if_in_broadcast_pkts;
    secy->controlled_cnt.if_out_pkts = secy->controlled_cnt.if_out_ucast_pkts + secy->controlled_cnt.if_out_multicast_pkts + secy->controlled_cnt.if_out_broadcast_pkts;

    secy->controlled_cnt.if_in_errors = 0;
    secy->controlled_cnt.if_out_errors = 0;
    secy->controlled_cnt.if_in_discards = 0;

    memcpy(counters, &data->macsec_conf.secy[secy_id].controlled_cnt, sizeof(mepa_macsec_secy_port_counters_t));

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_uncontrolled_counters_get_(mepa_device_t                        *dev,
                                                         const mepa_macsec_port_t             port,
                                                         mepa_macsec_uncontrolled_counters_t  *const counters,
                                                         u32                                   secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    memset(counters, 0, sizeof(mepa_macsec_uncontrolled_counters_t));
    u8 page1 = secy_id > LAN80XX_MACSEC_SC_REC_PAGE0_NUM ? 1 : 0;

    u64 cnt = 0;
    u32 port_no = port.port_no;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTOCTETSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTOCTETSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_out_octets += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTUCASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTUCASTPKTSUNCONTROLLED_LO(secy_id), &cnt);
    secy->uncontrolled_cnt.if_out_ucast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTMULTICASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTMULTICASTPKTSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_out_multicast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFOUTBROADCASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_EGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFOUTBROADCASTPKTSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_out_broadcast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINOCTETSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINOCTETSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_in_octets += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINUCASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINUCASTPKTSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_in_ucast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINMULTICASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINMULTICASTPKTSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_in_multicast_pkts += cnt;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no,
                            page1 ? LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE1_IFINBROADCASTPKTSUNCONTROLLED_LO(secy_id - LAN80XX_MACSEC_SC_REC_PAGE0_NUM) :
                            LAN80XX_MACSEC_INGR_CORE_STAT_IFC_COUNTERS_PAGE0_IFINBROADCASTPKTSUNCONTROLLED_LO(secy_id), &cnt);

    secy->uncontrolled_cnt.if_in_broadcast_pkts += cnt;
    secy->uncontrolled_cnt.if_in_discards = 0;
    secy->uncontrolled_cnt.if_in_errors = 0;
    secy->uncontrolled_cnt.if_out_errors = 0;

    memcpy(counters, &data->macsec_conf.secy[secy_id].uncontrolled_cnt, sizeof(mepa_macsec_uncontrolled_counters_t));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_common_counters_get_(mepa_device_t                  *dev,
                                                   const mepa_macsec_port_t       port,
                                                   mepa_macsec_common_counters_t  *const counters,
                                                   u32                            secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    memset(counters, 0, sizeof(mepa_macsec_common_counters_t));
    mepa_macsec_secy_port_counters_t control_cnt;
    mepa_macsec_uncontrolled_counters_t uncontrol_cnt;

    MEPA_RC(lan80xx_macsec_controlled_counters_get_(dev, port, &control_cnt, secy_id));
    MEPA_RC(lan80xx_macsec_uncontrolled_counters_get_(dev, port, &uncontrol_cnt, secy_id));

    secy->common_cnt.if_out_octets = control_cnt.if_out_octets + uncontrol_cnt.if_out_octets;
    secy->common_cnt.if_out_ucast_pkts = control_cnt.if_out_ucast_pkts + uncontrol_cnt.if_out_ucast_pkts;
    secy->common_cnt.if_out_multicast_pkts = control_cnt.if_out_multicast_pkts + uncontrol_cnt.if_out_multicast_pkts;
    secy->common_cnt.if_out_broadcast_pkts = control_cnt.if_out_broadcast_pkts + uncontrol_cnt.if_out_broadcast_pkts;
    secy->common_cnt.if_out_errors = control_cnt.if_out_errors + uncontrol_cnt.if_out_errors;
    secy->common_cnt.if_in_octets = control_cnt.if_in_octets + uncontrol_cnt.if_in_octets;
    secy->common_cnt.if_in_ucast_pkts = control_cnt.if_in_ucast_pkts + uncontrol_cnt.if_in_ucast_pkts;
    secy->common_cnt.if_in_multicast_pkts = control_cnt.if_in_multicast_pkts + uncontrol_cnt.if_in_multicast_pkts;
    secy->common_cnt.if_in_broadcast_pkts = control_cnt.if_in_broadcast_pkts + uncontrol_cnt.if_in_broadcast_pkts;
    secy->common_cnt.if_in_errors = control_cnt.if_in_errors + uncontrol_cnt.if_in_errors;
    secy->common_cnt.if_in_discards = control_cnt.if_in_discards + uncontrol_cnt.if_in_discards;
    memcpy(counters, &data->macsec_conf.secy[secy_id].common_cnt, sizeof(mepa_macsec_common_counters_t));

    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_counters_update_priv(mepa_device_t           *dev,
                                            const mepa_port_no_t    port_no)
{
    phy25g_macsec_secy_in_use_iter_t in_use_inter;
    mepa_macsec_secy_counters_t   dummy_counters;
    memset(&in_use_inter, 0, sizeof(phy25g_macsec_secy_in_use_iter_t));
    while (lan80xx_macsec_secy_in_use_inter_getnext(dev, &in_use_inter)) {
        // Read of hardware counters in order to update the software counters
        MEPA_RC(lan80xx_macsec_secy_counters_get_(dev, port_no, &dummy_counters, in_use_inter.secy_id));
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_lmac_counters_get_priv(mepa_device_t                    *dev,
                                              const mepa_port_no_t              port_no,
                                              mepa_macsec_mac_counters_t        *const counters,
                                              mepa_bool_t                       clear)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 cnt = 0;
    u64 cnt_64 = 0;

    /* Line  Rx Stats Octects = Bad Bytes Counts + OK Bytes Counts */
    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_OK_BYTES_CNT, &cnt_64);
    counters->if_rx_octets = cnt_64;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_BAD_BYTES_CNT, &cnt_64);
    counters->if_rx_octets += cnt_64;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_IN_BYTES_CNT, &cnt_64);
    counters->if_rx_in_bytes = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_PAUSE_CNT, &cnt);
    counters->if_rx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_UC_CNT, &cnt);
    counters->if_rx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_MC_CNT, &cnt);
    counters->if_rx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_BC_CNT, &cnt);
    counters->if_rx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_CRC_ERR_CNT, &cnt);
    counters->if_rx_CRCAlignErrors = cnt;
    counters->if_rx_errors = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_UNDERSIZE_CNT, &cnt);
    counters->if_rx_UndersizePkts = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_FRAGMENTS_CNT, &cnt);
    counters->if_rx_Fragments = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_JABBERS_CNT, &cnt);
    counters->if_rx_Jabbers = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_OVERSIZE_CNT, &cnt);
    counters->if_rx_OversizePkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE64_CNT, &cnt);
    counters->if_rx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE65TO127_CNT, &cnt);
    counters->if_rx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE128TO255_CNT, &cnt);
    counters->if_rx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE256TO511_CNT, &cnt);
    counters->if_rx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE512TO1023_CNT, &cnt);
    counters->if_rx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE1024TO1518_CNT, &cnt);
    counters->if_rx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_RX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_rx_Pkts1519toMaxOctets = cnt;

    /* Discard counters is not valid*/
    counters->if_rx_discards = 0;

    counters->if_rx_StatsPkts = ((u64)counters->if_rx_UndersizePkts        +
                                 (u64)counters->if_rx_OversizePkts         +
                                 (u64)counters->if_rx_Fragments            +
                                 (u64)counters->if_rx_Jabbers              +
                                 (u64)counters->if_rx_Pkts64Octets         +
                                 (u64)counters->if_rx_Pkts65to127Octets    +
                                 (u64)counters->if_rx_Pkts128to255Octets   +
                                 (u64)counters->if_rx_Pkts256to511Octets   +
                                 (u64)counters->if_rx_Pkts512to1023Octets  +
                                 (u64)counters->if_rx_Pkts1024to1518Octets +
                                 (u64)counters->if_rx_Pkts1519toMaxOctets);
    /* Tx Macsec Block RMON Counters */
    counters->if_tx_errors = 0;  /* Reports as 0 */
    counters->if_tx_DropEvents = 0;  /* Reports as 0 */
    counters->if_tx_Collisions = 0;  /* Full duplex MAC reports as 0 */

    /* Line  Tx Stats Octects are OK Bytes Counts only */
    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_OK_BYTES_CNT, &cnt_64);
    counters->if_tx_octets = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_PAUSE_CNT, &cnt);
    counters->if_tx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_UC_CNT, &cnt);
    counters->if_tx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_MC_CNT, &cnt);
    counters->if_tx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_BC_CNT, &cnt);
    counters->if_tx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE64_CNT, &cnt);
    counters->if_tx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE65TO127_CNT, &cnt);
    counters->if_tx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE128TO255_CNT, &cnt);
    counters->if_tx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE256TO511_CNT, &cnt);
    counters->if_tx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE512TO1023_CNT, &cnt);
    counters->if_tx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE1024TO1518_CNT, &cnt);
    counters->if_tx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_TX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_tx_Pkts1519toMaxOctets = cnt;

    counters->if_tx_StatsPkts = ((u64)counters->if_tx_Pkts64Octets         +
                                 (u64)counters->if_tx_Pkts65to127Octets    +
                                 (u64)counters->if_tx_Pkts128to255Octets   +
                                 (u64)counters->if_tx_Pkts256to511Octets   +
                                 (u64)counters->if_tx_Pkts512to1023Octets  +
                                 (u64)counters->if_tx_Pkts1024to1518Octets +
                                 (u64)counters->if_tx_Pkts1519toMaxOctets);
    if (clear) {
        MEPA_RC(lan80xx_macsec_lmac_counters_clear_priv(dev, port_no));
        data->macsec_conf.glb.rmon_counters_clr = TRUE;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_hmac_counters_get_priv(mepa_device_t                     *dev,
                                              const mepa_port_no_t              port_no,
                                              mepa_macsec_mac_counters_t        *const counters,
                                              mepa_bool_t                       clear)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 cnt = 0;
    u64 cnt_64;

    /* Line  Rx Stats Octects = Bad Bytes Counts + OK Bytes Counts */
    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_OK_BYTES_CNT, &cnt_64);
    counters->if_rx_octets = cnt_64;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_BAD_BYTES_CNT, &cnt_64);
    counters->if_rx_octets += cnt_64;

    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_IN_BYTES_CNT, &cnt_64);
    counters->if_rx_in_bytes = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_PAUSE_CNT, &cnt);
    counters->if_rx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_UC_CNT, &cnt);
    counters->if_rx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_MC_CNT, &cnt);
    counters->if_rx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_BC_CNT, &cnt);
    counters->if_rx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_CRC_ERR_CNT, &cnt);
    counters->if_rx_CRCAlignErrors = cnt;
    counters->if_rx_errors = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_UNDERSIZE_CNT, &cnt);
    counters->if_rx_UndersizePkts = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_FRAGMENTS_CNT, &cnt);
    counters->if_rx_Fragments = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_JABBERS_CNT, &cnt);
    counters->if_rx_Jabbers = cnt;
    counters->if_rx_errors += cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_OVERSIZE_CNT, &cnt);
    counters->if_rx_OversizePkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE64_CNT, &cnt);
    counters->if_rx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE65TO127_CNT, &cnt);
    counters->if_rx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE128TO255_CNT, &cnt);
    counters->if_rx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE256TO511_CNT, &cnt);
    counters->if_rx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE512TO1023_CNT, &cnt);
    counters->if_rx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1024TO1518_CNT, &cnt);
    counters->if_rx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_RX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_rx_Pkts1519toMaxOctets = cnt;

    /* Discard counters is not valid for RMON */
    counters->if_rx_discards = 0;

    counters->if_rx_StatsPkts = ((u64)counters->if_rx_UndersizePkts        +
                                 (u64)counters->if_rx_OversizePkts         +
                                 (u64)counters->if_rx_Fragments            +
                                 (u64)counters->if_rx_Jabbers              +
                                 (u64)counters->if_rx_Pkts64Octets         +
                                 (u64)counters->if_rx_Pkts65to127Octets    +
                                 (u64)counters->if_rx_Pkts128to255Octets   +
                                 (u64)counters->if_rx_Pkts256to511Octets   +
                                 (u64)counters->if_rx_Pkts512to1023Octets  +
                                 (u64)counters->if_rx_Pkts1024to1518Octets +
                                 (u64)counters->if_rx_Pkts1519toMaxOctets);
    /* Tx Macsec Block RMON Counters */
    counters->if_tx_errors = 0;  /* Reports as 0 */
    counters->if_tx_DropEvents = 0;  /* Reports as 0 */
    counters->if_tx_Collisions = 0;  /* Full duplex MAC reports as 0 */

    /* Line  Tx Stats Octects are OK Bytes Counts only */
    LAN80XX_MACSEC_CNT64_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_OK_BYTES_CNT, &cnt_64);
    counters->if_tx_octets = cnt_64;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_PAUSE_CNT, &cnt);
    counters->if_tx_pause_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_UC_CNT, &cnt);
    counters->if_tx_ucast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_MC_CNT, &cnt);
    counters->if_tx_multicast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_BC_CNT, &cnt);
    counters->if_tx_broadcast_pkts = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE64_CNT, &cnt);
    counters->if_tx_Pkts64Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE65TO127_CNT, &cnt);
    counters->if_tx_Pkts65to127Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE128TO255_CNT, &cnt);
    counters->if_tx_Pkts128to255Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE256TO511_CNT, &cnt);
    counters->if_tx_Pkts256to511Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE512TO1023_CNT, &cnt);
    counters->if_tx_Pkts512to1023Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1024TO1518_CNT, &cnt);
    counters->if_tx_Pkts1024to1518Octets = cnt;

    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_TX_SIZE1519TOMAX_CNT, &cnt);
    counters->if_tx_Pkts1519toMaxOctets = cnt;

    counters->if_tx_StatsPkts = ((u64)counters->if_tx_Pkts64Octets         +
                                 (u64)counters->if_tx_Pkts65to127Octets    +
                                 (u64)counters->if_tx_Pkts128to255Octets   +
                                 (u64)counters->if_tx_Pkts256to511Octets   +
                                 (u64)counters->if_tx_Pkts512to1023Octets  +
                                 (u64)counters->if_tx_Pkts1024to1518Octets +
                                 (u64)counters->if_tx_Pkts1519toMaxOctets);
    if (clear) {
        MEPA_RC(lan80xx_macsec_hmac_counters_clear_priv(dev, port_no));
        data->macsec_conf.glb.rmon_counters_clr = TRUE;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_mac_block_mtu_set_priv(mepa_device_t       *dev,
                                       const mepa_port_no_t port_no,
                                       u16                  mtu_value,
                                       mepa_bool_t          mtu_tag_check)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mac_maxlen_cfg = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port:%d, MTU:%d, Tag_check:%d", port_no, mtu_value, mtu_tag_check);

    data->macsec_conf.glb.mac_block_mtu = mtu_value;

    if (mtu_tag_check) {
        mac_maxlen_cfg = (LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK | mtu_value);

        /* Host MAC MTU size */
        LAN80XX_CSR_COLD_WR(port_no,  LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG, mac_maxlen_cfg);
        /* Line MAC MTU size */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_MAXLEN_CFG, mac_maxlen_cfg);
    } else {
        /* Host MAC MTU size */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG, mtu_value);
        /* Line MAC MTU size */
        LAN80XX_CSR_COLD_WR(port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_MAXLEN_CFG, mtu_value);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_mac_block_mtu_get_priv(mepa_device_t         *dev,
                                       const mepa_port_no_t  port_no,
                                       u16                   *mtu_value,
                                       mepa_bool_t           *mtu_tag_check)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 host_mtu = 0;
    u32 line_mtu = 0;
    /* Host MAC MTU size */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG, &host_mtu);
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_LINE_MAC_LINE_MAC_MAC_MAXLEN_CFG, &line_mtu);
    if (host_mtu == line_mtu) {
        if (host_mtu & LAN80XX_M_HOST_MAC_HOST_MAC_MAC_MAXLEN_CFG_MAX_LEN_TAG_CHK) {
            *mtu_tag_check = TRUE;
        } else {
            *mtu_tag_check = FALSE;
        }
        /* MTU size */
        *mtu_value = (u16) host_mtu;
    } else {
        *mtu_value = 0;
        *mtu_tag_check = FALSE;
        T_E(MEPA_TRACE_GRP_GEN, "Mismatch Line MAC MTU(%d) and Host MAC MTU(%d) size", line_mtu, host_mtu);
        return MEPA_RC_ERROR;
    }
    T_D(MEPA_TRACE_GRP_GEN, "Port:%d, MTU:%d, Tag:%d\n", port_no, *mtu_value, *mtu_tag_check);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_pattern_set_(mepa_device_t                      *dev,
                                           mepa_port_no_t                     port_no,
                                           u32                                secy_id,
                                           const mepa_macsec_direction_t      direction,
                                           const mepa_macsec_match_action_t   action,
                                           const mepa_macsec_match_pattern_t  *const pattern,
                                           u32                                rule_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 record = 0;
    mepa_bool_t egr = (direction == MEPA_MACSEC_DIRECTION_EGRESS) ? 1 : 0;

    if ((secy != NULL) && (secy->pattern_record[action][direction] != MACSEC_NOT_IN_USE)) {
        T_E(MEPA_TRACE_GRP_GEN, "Pattern already in use for port:%d secy_id:%d egr:%d action:%d\n", port_no, secy_id, egr, action);
        return MEPA_RC_ERROR;
    }

    if (lan80xx_record_empty_get(dev, port_no, &record, egr) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not get an empty record");
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_EMPTY_RECORD);
    }

    if (pattern->priority > MEPA_MACSEC_MATCH_PRIORITY_LOWEST) {
        T_E(MEPA_TRACE_GRP_GEN, "The pattern priority is not valid");
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_PATTERN_PRIO_NOT_VALID);
    }

    T_D(MEPA_TRACE_GRP_GEN, "SA:%u Action:%s Dir:%s", record, (action == 0) ? "Drop" : (action == 1) ? "Ctrl" : "Unctrl",  egr ? "egr" : "ingr");
    if (egr) {
        data->macsec_conf.tx_sa[record].record = record;
        data->macsec_conf.tx_sa[record].in_use = 1;
    } else {
        data->macsec_conf.rx_sa[record].record = record;
        data->macsec_conf.rx_sa[record].in_use = 1;
    }
    if (secy != NULL) {
        secy->pattern_record[action][direction] = record;
    } else {
        data->macsec_conf.glb.egr_bypass_record[rule_id] = record;
    }

    if (lan80xx_macsec_sa_tcam_key_mask_set(dev, port_no, egr, record, secy, 0, secy_id, pattern) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the TCAM match rule");
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }

    if (lan80xx_macsec_sa_tcam_policy_unctrl_drop(dev, port_no, record, egr, action) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the TCAM Policy for Uncontrolled port or drop");
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    /* Enable chip SA Flow */
    if (lan80xx_macsec_sa_enable(dev, port_no, record, egr, MACSEC_ENABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not enable the SA, record:%d, port_no:%d, secy_id:%d", record, port_no, secy_id);
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }


    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_pattern_del_(mepa_device_t                      *dev,
                                           const mepa_macsec_port_t           port,
                                           const u32                          secy_id,
                                           const mepa_macsec_direction_t      direction,
                                           const mepa_macsec_match_action_t   action)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_bool_t egr = (direction == MEPA_MACSEC_DIRECTION_EGRESS) ? 1 : 0;
    u32 record = 0;
    record = secy->pattern_record[action][direction];

    if (record == MACSEC_NOT_IN_USE) {
        T_E(MEPA_TRACE_GRP_GEN, "Pattern not set. port_no:%d, port_id:%d, secy_id:%d, direction:%d", port.port_no, port.port_id, secy_id, direction);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_PATTERN_NOT_SET);
    }
    /* Disable the SA */
    if (lan80xx_macsec_sa_enable(dev, port.port_no, record, egr, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not disable the SA, port_no:%d, port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
    }
    if (lan80xx_macsec_sa_inuse(dev, port.port_no, record, 0, 0, egr, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use, port_no:%d", record, port.port_no);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    if (lan80xx_macsec_sa_tcam_key_mask_reset(dev, port.port_no, egr, record) !=  MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (egr) {
        data->macsec_conf.tx_sa[record].in_use = 0;
    } else {
        data->macsec_conf.rx_sa[record].in_use = 0;
    }
    secy->pattern_record[action][direction] = MACSEC_NOT_IN_USE;
    secy->pattern[action][direction].match = MEPA_MACSEC_MATCH_DISABLE;
    return MEPA_RC_OK;
}

//Function to check whether there is any SecY Vacancy.
static mepa_rc lan80xx_macsec_port_check(mepa_device_t *dev, mepa_macsec_port_t port, mepa_bool_t create, u32 *secy_id)
{
    mepa_bool_t secy_vacancy = 0;
    u16 i, max_secy;
    phy25g_macsec_internal_secy_t *secy;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (lan80xx_port_macsec_enable_check(dev, port) != MEPA_RC_OK) {
        return MEPA_RC_ERROR;
    }

    max_secy = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_SECY_CNT);

    for (i = 0; i < max_secy; i++) {
        secy = &data->macsec_conf.secy[i];
        if ((create && secy->in_use) && (secy->sci.port_id == port.port_id) && (secy->service_id == port.service_id)) {
            T_E(MEPA_TRACE_GRP_GEN, "SecY already in use. (port_no:%u port_id:%u service_id:%u)", port.port_no, port.port_id, port.service_id);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_SECY_ALREADY_IN_USE);
        }
        if ((!create && secy->in_use) && (secy->sci.port_id == port.port_id) && (secy->service_id == port.service_id)) {
            *secy_id = i;
            return MEPA_RC_OK;
        }
        if (create && !secy->in_use) {
            *secy_id = i;
            secy_vacancy = 1;
            break;
        }
    }
    if (!create) {
        T_E(MEPA_TRACE_GRP_GEN, "No SecY found (port_no:%u port_id:%u service_id:%u found)", port.port_no, port.port_id, port.service_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NO_SECY_FOUND);
    }
    if (create && !secy_vacancy) {
        T_E(MEPA_TRACE_GRP_GEN, "No secy vacancy, port_no:%d, port_id:%d, service_id:%d, secy_id:%d ", port.port_no, port.port_id, port.service_id, *secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NO_SECY_VACANCY);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_disable_(mepa_device_t   *dev,
                                             const u32                 secy_id,
                                             const mepa_macsec_port_t  port,
                                             const mepa_macsec_sci_t   *const sci,
                                             const u16                 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0;
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc] == NULL, "SC does not exist");

    if (secy->rx_sc[sc]->sa[an] == NULL) {
        T_I(MEPA_TRACE_GRP_GEN, "AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        MEPA_RC(dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_EXIST));
    }

    if (lan80xx_macsec_sa_inuse(dev, port.port_no, secy->rx_sc[sc]->sa[an]->record, sc, an, INGRESS, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use, port_no:%d, secy_id:%d", secy->rx_sc[sc]->sa[an]->record, port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    secy->rx_sc[sc]->sa[an]->status.in_use = 0;
    secy->rx_sc[sc]->sa[an]->enabled = 0;

    secy->rx_sc[sc]->sa[an]->status.stopped_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_del_(mepa_device_t   *dev,
                                         const u32                 secy_id,
                                         const mepa_macsec_port_t  port,
                                         const mepa_macsec_sci_t   *const sci,
                                         const u16                 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0, record, sa_in_use = 0, i;
    mepa_macsec_rx_sa_counters_t rx_sa_counters;

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");

    if (!secy->rx_sc[sc]->sa[an]) {
        T_E(MEPA_TRACE_GRP_GEN, "AN not created. AN=%u, port_no:%d, port_id:%d, secy_id:%d", an, port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_CREATED);
    }
    record = secy->rx_sc[sc]->sa[an]->record;

    /* Disable chip SA Flow */
    if (lan80xx_macsec_sa_enable(dev, port.port_no, record, INGRESS, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not Enable the SA:%u", an);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }

    // Wait until the unsafe field has reached zero, i.e. while there are packet in the system
    if (lan80xx_sa_sam_in_flight(dev, port.port_no, INGRESS) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not empty the ingress pipeline");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_INGRESS);
    }
    /* Get Rx Sa counters going to be deleted.., and just ignore even if there is a error on reading */
    if ((lan80xx_macsec_rx_sa_counters_get_(dev, port.port_no, sci, an, &rx_sa_counters, secy_id)) == MEPA_RC_OK) {
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_ok            += rx_sa_counters.in_pkts_ok;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_invalid       += rx_sa_counters.in_pkts_invalid;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_valid     += rx_sa_counters.in_pkts_not_valid;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_not_using_sa  += rx_sa_counters.in_pkts_not_using_sa;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unused_sa     += rx_sa_counters.in_pkts_unused_sa;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_unchecked     += rx_sa_counters.in_pkts_unchecked;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_delayed       += rx_sa_counters.in_pkts_delayed;
        secy->rx_sc[sc]->del_rx_sa_cnt.in_pkts_late          += rx_sa_counters.in_pkts_late;
    }
    for (i = 0; i < MEPA_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->rx_sc[sc]->sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->rx_sc[sc]->sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }

    if (!sa_in_use) {
        secy->rx_sc[sc]->status.stopped_time = secy->rx_sc[sc]->sa[an]->status.stopped_time;
    }
    memset(&data->macsec_conf.rx_sa[record], 0, sizeof(data->macsec_conf.rx_sa[record]));
    secy->rx_sc[sc]->sa[an] = NULL;

    /* Clearing the Hardware config registers */
    T_D(MEPA_TRACE_GRP_GEN, "Port:%d, secy_id:%u AN:%u, Record:%u, Hardware Registers clear", port.port_no, secy_id, an, record);

    if (lan80xx_macsec_sa_tcam_key_mask_reset(dev, port.port_no, INGRESS, record) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (lan80xx_macsec_sa_xform_reset(dev, port.port_no, 0, record, secy, an, 0) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not reset the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_activate_(mepa_device_t *dev,
                                              const u32 secy_id,
                                              const mepa_macsec_port_t  port,
                                              const mepa_macsec_sci_t *const sci,
                                              const u16  an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0, i, sa_in_use = 0;

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));


    MEPA_RC(lan80xx_is_sci_valid(dev, sci));
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");

    /* Activate chip SA Flow */
    if (MACSEC_RC_COLD(lan80xx_macsec_sa_inuse(dev, port.port_no, secy->rx_sc[sc]->sa[an]->record, sc, an, INGRESS, MACSEC_ENABLE)) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use'", secy->rx_sc[sc]->sa[an]->record);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }

    secy->rx_sc[sc]->sa[an]->status.started_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds
    secy->rx_sc[sc]->sa[an]->status.in_use = 1;
    secy->rx_sc[sc]->sa[an]->enabled = 1;

    /* Rx Secure channel status */
    for (i = 0; i < MEPA_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->rx_sc[sc]->sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->rx_sc[sc]->sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }
    if (!sa_in_use) {
        secy->rx_sc[sc]->status.started_time = MEPA_UPTIME_SECONDS();
    }
    return MEPA_RC_OK;
}


static mepa_rc lan80xx_macsec_tx_sa_activate_(mepa_device_t *dev, const u32  secy_id, const mepa_macsec_port_t port, const u16 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 old_an, i;
    mepa_bool_t an_in_use = 0;

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(secy->tx_sc.sa[an] == NULL, "AN does not exist");
    LAN80XX_MACSEC_ASSERT(!secy->tx_sc.sa[an]->in_use, "AN is not in use");

    old_an = secy->tx_sc.status.encoding_sa;
    if (secy->tx_sc.sa[old_an] != NULL) {
        an_in_use = secy->tx_sc.sa[old_an]->enabled;
    }
    /* Activate chip SA Flow */
    if (an_in_use && (old_an < MEPA_MACSEC_SA_PER_SC_MAX) && (old_an != an)) {
        if (MACSEC_RC_COLD(lan80xx_macsec_sa_inuse(dev, port.port_no, secy->tx_sc.sa[an]->record, secy_id, an, EGRESS, MACSEC_ENABLE)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use'", secy->tx_sc.sa[an]->record);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
        }
        if (MACSEC_RC_COLD(lan80xx_macsec_sa_toggle(dev, port.port_no, secy->tx_sc.sa[an]->record, secy->tx_sc.sa[old_an]->record, EGRESS)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not toggle SA:%u -> %u", an, old_an);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_TOGGLE_SA);
        }
    } else {
        if (MACSEC_RC_COLD(lan80xx_macsec_sa_inuse(dev, port.port_no, secy->tx_sc.sa[an]->record, secy_id, an, EGRESS, MACSEC_ENABLE)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use'", secy->tx_sc.sa[an]->record);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
        }
        /* Enable chip SA Flow */
        if (lan80xx_macsec_sa_enable(dev, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_ENABLE) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not enable the SA, record:%d, port_no:%d, port_id:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no,
                port.port_id, secy_id);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
        }
    }
    if (lan80xx_macsec_sam_entry_ctrl(dev, port.port_no, secy->tx_sc.sa[an]->record, 1, 1) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not enable the TCAM entry, record:%d, port_no:%d, port_id:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no,
            port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }

    /* Disable Old record */
    if (an_in_use && (old_an < MEPA_MACSEC_SA_PER_SC_MAX)) {
        secy->tx_sc.sa[old_an]->enabled = 0;
        secy->tx_sc.sa[old_an]->status.in_use = 0;
        an_in_use = 0;
    }

    secy->tx_sc.sa[an]->status.started_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds
    secy->tx_sc.sa[an]->enabled = 1;
    secy->tx_sc.sa[an]->status.in_use = 1;

    /* Secure channel status config */
    for (i = 0; i < MEPA_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->tx_sc.sa[i] == NULL || (i == an)) {
            continue;
        }
        if (secy->tx_sc.sa[i]->in_use) {
            an_in_use = 1;
            break;
        }
    }
    /* If this is first SA created for particular SC then assigning the SC start time */
    if (!an_in_use) {
        secy->tx_sc.status.started_time = MEPA_UPTIME_SECONDS();
    }
    secy->tx_sc.status.encoding_sa = an;
    secy->tx_sc.status.enciphering_sa = an;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sa_disable_(mepa_device_t  *dev, const u32 secy_id, const mepa_macsec_port_t  port, const u16 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (secy->tx_sc.sa[an] == NULL) {
        T_I(MEPA_TRACE_GRP_GEN, "AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_EXIST);
    }

    /* Disable chip SA Flow */
    if (lan80xx_macsec_sa_enable(dev, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not disable the AN:%u", an);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_AN);
    }
    if (lan80xx_macsec_sa_inuse(dev, port.port_no, secy->tx_sc.sa[an]->record, secy_id, an, EGRESS, MACSEC_DISABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not set SA:%u to 'in_use, port_no:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_SA);
    }
    if (lan80xx_macsec_sam_entry_ctrl(dev, port.port_no, secy->tx_sc.sa[an]->record, EGRESS, 0) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not clear the TCAM entry, record:%d, port_no:%d, port_id:%d, secy_id:%d", secy->tx_sc.sa[an]->record, port.port_no,
            port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }

    // Update TX SA/SC/SecY counters
    secy->tx_sc.sa[an]->status.in_use = 0;
    secy->tx_sc.sa[an]->enabled = 0;
    if (an == secy->tx_sc.status.encoding_sa) {
        secy->tx_sc.status.encoding_sa = 0;
        secy->tx_sc.status.enciphering_sa = 0;
    }
    secy->tx_sc.sa[an]->status.stopped_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sa_del_(mepa_device_t  *dev, const u32  secy_id, const mepa_macsec_port_t  port, const u16 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 record, i, sa_in_use = 0;
    mepa_macsec_tx_sa_counters_t tx_sa_counters;

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(secy->tx_sc.sa[an] == NULL, "AN is not existing");

    record = secy->tx_sc.sa[an]->record;

    /* Wait until the unsafe field has reached zero, i.e. while there are packet in the system*/
    if (lan80xx_sa_sam_in_flight(dev, port.port_no, EGRESS) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not empty the egress pipeline");
        dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_EMPTY_EGRESS);

    }

    /* Update SC counters before the SA is deleted*/
    tx_sa_counters.out_pkts_encrypted = 0;
    tx_sa_counters.out_pkts_protected = 0;
    if ((lan80xx_macsec_tx_sa_counters_get_(dev, port.port_no, an, &tx_sa_counters, secy_id)) == MEPA_RC_OK) {
        secy->tx_sc.del_tx_sa_cnt.out_pkts_encrypted += tx_sa_counters.out_pkts_encrypted;
        secy->tx_sc.del_tx_sa_cnt.out_pkts_protected += tx_sa_counters.out_pkts_protected;
    }

    for (i = 0; i < MEPA_MACSEC_SA_PER_SC_MAX; i++ ) {
        if (secy->tx_sc.sa[i] == NULL || (i == an)) {
            continue;
        }

        if (secy->tx_sc.sa[i]->in_use) {
            sa_in_use = 1;
            break;
        }
    }
    if (!sa_in_use) {
        /* Last SA in use, must update the SC stopped_time */
        secy->tx_sc.status.stopped_time = secy->tx_sc.sa[an]->status.stopped_time;

    }
    memset(&data->macsec_conf.tx_sa[record], 0, sizeof(data->macsec_conf.tx_sa[record]));
    secy->tx_sc.sa[an] = NULL;
    /* Clear Hardware config registers */
    T_D(MEPA_TRACE_GRP_GEN, "Port:%d, secy_id:%u AN:%u, Record:%u, Hardware Registers clear", port.port_no, secy_id, an, record);
    if (lan80xx_macsec_sa_tcam_key_mask_reset(dev, port.port_no, 1, record) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not reset the SA match, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (lan80xx_macsec_sa_xform_reset(dev, port.port_no, 1, record, secy, an, 0) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not reset the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    secy->tx_sc.sa[an] = NULL;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sa_status_get_(mepa_device_t *dev, u32 secy_id, const mepa_macsec_port_t port, u16 an)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 val, record;
    mepa_bool_t xpn = FALSE; /*By default NON XPN */
    u64 value = 0;

    record = secy->tx_sc.sa[an]->record;
    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }

    if (xpn) {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_EGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &value);
        } else {
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_EGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &value);
        }
        secy->tx_sc.sa[an]->status.pn_status.next_pn.xpn = value;
    } else {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_EGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &val);
        } else {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_EGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &val);
        }
        val += 1;
        secy->tx_sc.sa[an]->status.next_pn = val;
        secy->tx_sc.sa[an]->status.pn_status.next_pn.pn = val;
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_status_get_(mepa_device_t    *dev,
                                                const u32                   secy_id,
                                                const mepa_macsec_port_t    port,
                                                const mepa_macsec_sci_t     *const sci,
                                                const u16                   an,
                                                mepa_macsec_rx_sa_status_t  *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 next_pn = 0, sc = 0, record = 0;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_bool_t xpn = FALSE;
    u64 value = 0;

    if (lan80xx_sc_from_sci_get(dev, secy, sci, &sc) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "No SC found");
        return MEPA_RC_OK;
    }
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    LAN80XX_MACSEC_ASSERT(!secy->rx_sc[sc]->sa[an]->in_use, "AN is not active");

    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }

    record = secy->rx_sc[sc]->sa[an]->record;
    if (xpn) {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            /* PAGE 0 */
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &value);
        } else {
            /* PAGE 1 */
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0),
                                    &value);
        }
        secy->rx_sc[sc]->sa[an]->status.pn_status.next_pn.xpn = value;
        secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn.xpn = (secy->rx_sc[sc]->conf.replay_window >= value) ? 1 : (value - secy->rx_sc[sc]->conf.replay_window);
    } else {
        /* Read the next PN */
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &next_pn);
        } else {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &next_pn);
        }
        secy->rx_sc[sc]->sa[an]->status.next_pn = next_pn;
        secy->rx_sc[sc]->sa[an]->status.lowest_pn = (secy->rx_sc[sc]->conf.replay_window >= next_pn) ? 1 : (next_pn - secy->rx_sc[sc]->conf.replay_window);
    }

    *status = secy->rx_sc[sc]->sa[an]->status;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sc_cam_set(mepa_device_t *dev, mepa_port_no_t port_no, u32 record, phy25g_macsec_internal_secy_t *secy, u16 an, u32 secyid, u32 sc,
                                            mepa_macsec_match_pattern_t *pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_mac_t  mac_addr = {0};
    mepa_mac_t broadcast = {.addr = LAN80XX_MAC_ADDR_BROADCAST};
    u16 port_id = 0;

    /* Accroding to MACsec IP and IEEE MACsec Standard when SCI is Explicitly available in Packet, Ingress engine will use that SCI
     * If SCI is not avaialble Explicitly SCI program should be as follows
     */
    if (secy->conf.always_include_sci) {
        memcpy(mac_addr.addr, secy->rx_sc[sc]->sci.mac_addr.addr, sizeof(mac_addr.addr));
        port_id = secy->rx_sc[sc]->sci.port_id;
    } else if (secy->conf.use_es && secy->conf.use_scb) {
        /* User have to Pass MAC Source-Address as SCI Mac Address in this Case */
        memcpy(mac_addr.addr, secy->rx_sc[sc]->sci.mac_addr.addr, sizeof(mac_addr.addr));
        port_id = 0;
    } else if (secy->conf.use_es && (!secy->conf.use_scb)) {
        /* User have to Pass MAC Source Address as SCI Mac Address in this Case */
        memcpy(mac_addr.addr, secy->rx_sc[sc]->sci.mac_addr.addr, sizeof(mac_addr.addr));
        port_id = 1;
    } else {
        /* Broadcast MAC Address is used as SCI MAC Address */
        memcpy(mac_addr.addr, broadcast.addr, sizeof(mac_addr.addr));
        port_id = LAN80XX_BROADCAST_PORT_ID;
    }

    if (sc < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_SCI_LO(sc), lan80xx_get_u32(&mac_addr.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_SCI_HI(sc),
                       (mac_addr.addr[4] | (mac_addr.addr[5] << 8) | (MACSEC_BS(port_id) << 16)));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL(sc),
                       LAN80XX_F_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL_VPORT_INDEX(secyid));
    } else {
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_SCI_LO(sc - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0),
                       lan80xx_get_u32(&mac_addr.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_SCI_HI(sc - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0),
                       (mac_addr.addr[4] | (mac_addr.addr[5] << 8) | (MACSEC_BS(port_id) << 16)));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE1_RXSC_CAM_CTRL(sc - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0),
                       LAN80XX_F_MACSEC_INGR_CORE_RXSC_CAM_KEY_PAGE0_RXSC_CAM_CTRL_VPORT_INDEX(secyid));
    }

    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL,
                   LAN80XX_F_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SC_INDEX_SET(sc) |
                   LAN80XX_M_MACSEC_INGR_CORE_RXSC_ENTRY_ENABLE_CTRL_SET_ENABLE);

    return MEPA_RC_OK;
}


static mepa_rc lan80xx_macsec_rx_sa_set_(mepa_device_t   *dev,
                                         const u32                     secy_id,
                                         const mepa_macsec_port_t      port,
                                         const mepa_macsec_sci_t       *const sci,
                                         const u16                     an,
                                         const mepa_macsec_pkt_num_t   lowest_pn,
                                         const mepa_macsec_sak_t       *const sak,
                                         const mepa_macsec_ssci_t      *const ssci)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_macsec_match_pattern_t *match = &secy->pattern[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_INGRESS];
    u32 sc = 0, record = 0;
    mepa_bool_t create_record = 1;

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    T_I(MEPA_TRACE_GRP_GEN, "port_no: %u, secy: %u, sc:%u, an:%u", port.port_no, secy_id, sc, an);
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    MEPA_RC(lan80xx_is_sci_valid(dev, sci));   /* checking whether SCI is valid */

    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        MEPA_RC(lan80xx_is_ssci_valid(dev, FALSE, sci, ssci, sak));
    }
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if (secy->rx_sc[sc]->sa[an] != NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "Rx AN:%u is in use", an);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_RX_AN_ALREADY_IN_USE);
    }
    if (create_record && (lan80xx_record_empty_get(dev, port.port_no, &record, INGRESS) != MEPA_RC_OK)) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not get an empty record, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_EMPTY_RECORD);
    }
    secy->rx_sc[sc]->sa[an] = &data->macsec_conf.rx_sa[record];
    secy->rx_sc[sc]->sa[an]->record = record;
    secy->rx_sc[sc]->sa[an]->sak = *sak;
    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        memcpy(secy->rx_sc[sc]->sa[an]->ssci.buf, ssci->buf, sizeof(mepa_macsec_ssci_t));
    }
    secy->rx_sc[sc]->sa[an]->status.lowest_pn = lowest_pn.pn;
    secy->rx_sc[sc]->sa[an]->status.pn_status.lowest_pn = lowest_pn;
    secy->rx_sc[sc]->sa[an]->in_use = 1;
    secy->rx_sc[sc]->sa[an]->status.created_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds

    if (lan80xx_macsec_sa_xform_set(dev, port.port_no, INGRESS, secy->rx_sc[sc]->sa[an]->record, secy, an, sc) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the xform record, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM);
    }
    if (lan80xx_macsec_sa_tcam_key_mask_set(dev, port.port_no, INGRESS, record, secy, an, secy_id, match) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the TCAM match rule");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (lan80xx_macsec_rx_sc_cam_set(dev, port.port_no, record, secy, an, secy_id, sc, match) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the RXCAM match rule");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }
    if (lan80xx_macsec_sa_flow_set(dev, port.port_no, INGRESS, secy->rx_sc[sc]->sa[an]->record, secy, an, sc, MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the SA flow, port_no:%d  secy_id:%d", port.port_no, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }
    /* Enable chip SA Flow */
    if (lan80xx_macsec_sa_enable(dev, port.port_no, secy->rx_sc[sc]->sa[an]->record, INGRESS, MACSEC_ENABLE) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not Enable the SA:%u", an);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_get_(mepa_device_t                 *dev,
                                         const u32                     secy_id,
                                         const mepa_macsec_port_t      port,
                                         const mepa_macsec_sci_t       *const sci,
                                         const u16                     an,
                                         mepa_macsec_pkt_num_t         *const lowest_pn,
                                         mepa_macsec_sak_t             *const sak,
                                         mepa_bool_t                   *const active,
                                         mepa_macsec_ssci_t            *const ssci)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 sc = 0, record = 0, val = 0;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_bool_t xpn = FALSE;
    u64 value;

    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    if (secy->rx_sc[sc]->sa[an] == NULL) {
        T_I(MEPA_TRACE_GRP_GEN, "AN:%d does not exist, secyid:%d, port_no:%d", an, secy_id, port.port_no);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_EXIST);
    }
    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128)) {
        xpn = TRUE;
    }

    record = secy->rx_sc[sc]->sa[an]->record;

    if (xpn) {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            /* PAGE 0 */
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &value);
        } else {
            /* PAGE 1 */
            LAN80XX_MACSEC_CNT64_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &value);
        }
        if (value > secy->rx_sc[sc]->conf.replay_window) {
            lowest_pn->xpn = value - secy->rx_sc[sc]->conf.replay_window;
        } else {
            lowest_pn->xpn = 0;
        }
    } else {
        if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W14(record), &val);
        } else {
            LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W14(record - LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0), &val);
        }
        if (val > secy->rx_sc[sc]->conf.replay_window) {
            lowest_pn->pn = val - secy->rx_sc[sc]->conf.replay_window;
        } else {
            lowest_pn->pn = 0;
        }
    }
    T_I(MEPA_TRACE_GRP_GEN, "SC:%d, Record:%d, Lowest PN:%d", sc, record, lowest_pn->pn);
    *sak = secy->rx_sc[sc]->sa[an]->sak;
    *active = secy->rx_sc[sc]->sa[an]->status.in_use;
    *ssci = secy->rx_sc[sc]->sa[an]->ssci;

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sa_next_pn_update_(mepa_device_t    *dev,
                                                    const u32                     secy_id,
                                                    const mepa_macsec_port_t      port,
                                                    const mepa_macsec_pkt_num_t   next_pn,
                                                    const u32                     record)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 ctxt_addr = 0, value = 0;
    u32 next_xpn_lsb, next_xpn_msb;
    mepa_bool_t xpn = FALSE;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];

    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }
    /* Update the next pn */
    if (xpn == TRUE) {
        next_xpn_lsb = (next_pn.xpn) & 0xFFFF;
        next_xpn_msb = next_pn.xpn >> 32;
        LAN80XX_CSR_WR(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXTPN_LO, next_xpn_lsb);
        LAN80XX_CSR_WR(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXTPN_HI, next_xpn_msb);
    } else {
        LAN80XX_CSR_WR(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXTPN_LO, next_pn.pn);
    }
    /* Next_pn_ctx_addr = ((Index of SA * Offset between SAs in bytes) + (Position of SeqNum word * 4)) >> 4 */
    /* Offset between SA's = context size * 4 bytes */
    ctxt_addr = ((record * 24) + (14 * 4) ) >> 4;

    value = LAN80XX_F_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_CONTEXT_ADDRESS(ctxt_addr) |
            (xpn ? LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_SEQUENCE_NUMBER_SIZE : 0);
    LAN80XX_CSR_WR(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL, value);

    /* Make the update effective */
    value = LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_ENABLE_UPDATE;
    LAN80XX_CSR_WRM(port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL, value, value);

    return MEPA_RC_OK;
}


static mepa_rc lan80xx_macsec_rx_sa_lowest_pn_update_(mepa_device_t  *dev,
                                                      const u32                     secy_id,
                                                      const mepa_macsec_port_t      port,
                                                      const mepa_macsec_sci_t       *const sci,
                                                      const u16                     an,
                                                      const mepa_macsec_pkt_num_t   lowest_pn)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 next_pn = 0, sc = 0, record = 0;
    mepa_bool_t xpn = FALSE;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_macsec_pkt_num_t pkt_num;

    if (lan80xx_sc_from_sci_get(dev, secy, sci, &sc) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "No SC found");
        return MEPA_RC_OK;
    }

    MEPA_RC(lan80xx_is_sci_valid(dev, sci));

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(secy->rx_sc[sc]->sa[an] == NULL, "AN does not exist");
    LAN80XX_MACSEC_ASSERT(!secy->rx_sc[sc]->sa[an]->in_use, "AN is not active");
    record = secy->rx_sc[sc]->sa[an]->record;
    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        xpn = TRUE;
    }
    if (xpn == TRUE) {
        pkt_num.xpn = lowest_pn.xpn + secy->conf.replay_window;
    } else {
        pkt_num.pn = lowest_pn.pn + secy->conf.replay_window;
    }

    if (lan80xx_macsec_rx_sa_next_pn_update_(dev, secy_id, port, pkt_num, record) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not update Next PN");
        return MEPA_RC_ERROR;
    }

    LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL, &next_pn);
    while ( (next_pn & LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_ENABLE_UPDATE) &&
            (!(next_pn & LAN80XX_M_MACSEC_INGR_CORE_EIP62_REGISTERS_NEXT_PN_CTRL_NEXT_PN_CTRL_NEXTPN_WRITTEN)) ) {
        T_D(MEPA_TRACE_GRP_GEN, "Next PN not yet updated");
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sa_set_(mepa_device_t *dev, const u32 secy_id, const mepa_macsec_port_t port, const u16 an, const mepa_macsec_pkt_num_t next_pn,
                                         const mepa_bool_t confidentiality, const mepa_macsec_sak_t *const sak, const mepa_macsec_ssci_t *const ssci)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    mepa_macsec_match_pattern_t *match = &secy->pattern[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_EGRESS];
    u32 record = 0;
    mepa_bool_t create_record = 1;

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    LAN80XX_MACSEC_ASSERT(!secy->tx_sc.in_use, "No TxSC installed");
    LAN80XX_MACSEC_ASSERT(next_pn.pn < 1, "NextPN should not be zero (0)");

    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {

        MEPA_RC(lan80xx_is_ssci_valid(dev, TRUE, &secy->sci, ssci, sak));
    }
    if (secy->tx_sc.sa[an] != NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "Tx AN:%u is in use", an);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_TX_AN_ALREADY_IN_USE);
    }
    if (create_record && (lan80xx_record_empty_get(dev, port.port_no, &record, EGRESS) != MEPA_RC_OK)) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not get an empty record");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_EMPTY_RECORD);
    }
    secy->tx_sc.sa[an] = &data->macsec_conf.tx_sa[record];
    secy->tx_sc.sa[an]->record = record;
    secy->tx_sc.sa[an]->sak = *sak;
    secy->tx_sc.sa[an]->confidentiality = confidentiality;
    if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128) ||
        (secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256)) {
        memcpy(secy->tx_sc.sa[an]->ssci.buf, ssci->buf, sizeof(mepa_macsec_ssci_t));
    }
    secy->tx_sc.sa[an]->status.next_pn = next_pn.pn - 1;
    secy->tx_sc.sa[an]->status.pn_status.next_pn = next_pn;
    secy->tx_sc.sa[an]->in_use = 1;
    secy->tx_sc.sa[an]->status.created_time = MEPA_UPTIME_SECONDS(); /* TimeOfDay in seconds*/

    if (lan80xx_macsec_sa_xform_set(dev, port.port_no, EGRESS, record, secy, an, 0) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the xform record");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_XFORM);
    }
    if (lan80xx_macsec_sa_flow_set(dev, port.port_no, EGRESS, record, secy, an, secy_id, MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the SA flow");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_FLOW);
    }

    if (lan80xx_macsec_sa_tcam_key_mask_set(dev, port.port_no, EGRESS, record, secy, an, secy_id, match) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not program the TCAM match rule");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_PRG_SA_MATCH);
    }

    if (lan80xx_macsec_sa_enable(dev, port.port_no, record, EGRESS, 1) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not enable the SA, record:%d, port_no:%d, port_id:%d, secy_id:%d", record, port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_ENA_SA);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sc_del_(mepa_device_t             *dev,
                                         const mepa_macsec_port_t  port,
                                         const mepa_macsec_sci_t   *sci,
                                         const u32                 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0, sa;
    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc))

    for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
        if (secy->rx_sc[sc]->sa[sa] != NULL) {
            if (secy->rx_sc[sc]->sa[sa]->status.in_use) {
                if (lan80xx_macsec_rx_sa_disable_(dev, secy_id, port, sci, sa) != MEPA_RC_OK) {
                    T_E(MEPA_TRACE_GRP_GEN, "Could not disable sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                    return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
            }
            if (lan80xx_macsec_rx_sa_del_(dev, secy_id, port, sci, sa)) {
                T_E(MEPA_TRACE_GRP_GEN, "Could not delete rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA);
            }
        }
    }
    memset(secy->rx_sc[sc], 0, sizeof(*secy->rx_sc[sc]));
    secy->rx_sc[sc] = NULL;
    //If no Secure channel is found then the frame validation will be done based on the update_glb_validate
    MEPA_RC(lan80xx_macsec_update_glb_validate(dev, port.port_no));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rx_sc_add_(mepa_device_t  *dev, const mepa_macsec_port_t  port, const mepa_macsec_sci_t *sci, const u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u16 sc_secy = 0, sc_conf = 0, sc, max_sc_rx;
    mepa_bool_t found_sc_in_secy = 0, found_sc_in_conf = 0;

    if (!check_resources(dev, 1, secy_id)) {
        T_E(MEPA_TRACE_GRP_GEN, "HW resources exhausted, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED);
    }
    //check whether SCI is valid
    MEPA_RC(lan80xx_is_sci_valid(dev, sci));
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (lan80xx_sci_cmp(sci, &data->macsec_conf.rx_sc[sc].sci)) {
            T_E(MEPA_TRACE_GRP_GEN, "SCI already exists, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_SCI_ALREADY_EXISTS);
        }
    }
    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL && !found_sc_in_secy) {
            sc_secy = sc;
            found_sc_in_secy = 1;
        }
        if (!data->macsec_conf.rx_sc[sc].in_use && !found_sc_in_conf) {
            sc_conf = sc;
            found_sc_in_conf = 1;
        }
    }
    if (!(found_sc_in_secy && found_sc_in_conf)) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not find SC resources, port_no:%d  port_id:%d, secy_id:%d", port.port_no, port.port_id, secy_id);
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_SC_RESOURCE_NOT_FOUND);
    }

    T_I(MEPA_TRACE_GRP_GEN, "Adding new RX-SC: Port: "MACSEC_PORT_FMT" SCI: "LAN80XX_SCI_FMT", sc-in-secy:%u", LAN80XX_MACSEC_PORT_ARG(&port), LAN80XX_SCI_ARG(*sci),
        sc_secy);
    secy->rx_sc[sc_secy] = &data->macsec_conf.rx_sc[sc_conf];
    memcpy(&secy->rx_sc[sc_secy]->sci, sci, sizeof(mepa_macsec_sci_t));
    secy->rx_sc[sc_secy]->conf.validate_frames = secy->conf.validate_frames;
    secy->rx_sc[sc_secy]->conf.replay_protect = secy->conf.replay_protect;
    secy->rx_sc[sc_secy]->conf.replay_window = secy->conf.replay_window;
    secy->rx_sc[sc_secy]->conf.confidentiality_offset = secy->conf.confidentiality_offset;
    secy->rx_sc[sc_secy]->status.created_time = MEPA_UPTIME_SECONDS(); // TimeOfDay in seconds
    secy->rx_sc[sc_secy]->in_use = 1;

    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sc_del_(mepa_device_t *dev, const mepa_macsec_port_t port, u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sa;

    if (!secy->tx_sc.in_use) {
        T_E(MEPA_TRACE_GRP_GEN, "TX_SC does not exist");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
    }
    /* Delete the Tx Secure Assosiation if its still in use */
    for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
        if (secy->tx_sc.sa[sa] != NULL) {
            if (lan80xx_macsec_tx_sa_disable_(dev, secy_id, port, sa)) {
                T_E(MEPA_TRACE_GRP_GEN, "Could not disable sa:%u", sa);
                return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
            }
            if (lan80xx_macsec_tx_sa_del_(dev, secy_id, port, sa)) {
                T_E(MEPA_TRACE_GRP_GEN, "Could not delete tx sa:%u, port_no:%d port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA);
            }
        }
    }
    memset(&secy->tx_sc, 0, sizeof(secy->tx_sc));
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tx_sc_set_(mepa_device_t *dev, const u32 secy_id)

{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    MEPA_RC(lan80xx_is_sci_valid(dev, &secy->sci));
    secy->tx_sc.status.created_time = MEPA_UPTIME_SECONDS(); /* 802.1AE 10.7.12 SC Created time */
    secy->tx_sc.status.started_time = MEPA_UPTIME_SECONDS(); /*802.1AE 10.7.12 SC Started time */
    secy->tx_sc.status.stopped_time = 0;       /* 802.1AE 10.7.12 SC Stopped TIme */
    secy->tx_sc.in_use = 1;                    /* Enabling the Tx SC */
    memcpy(&secy->tx_sc.status.sci,  &secy->sci, sizeof(mepa_macsec_sci_t));
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_frame_capture_set_priv(mepa_device_t                       *dev,
                                              const mepa_port_no_t                port_no,
                                              const mepa_macsec_frame_capture_t   capture)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_oper_speed_mode_t phy_speed;
    phy_speed = data->port_state.speed;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA1, 0x0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA2, 0x0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA3, 0x0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA4, 0x0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER, 0x0);

    if (capture != MEPA_MACSEC_FRAME_CAPTURE_DISABLE) {
        T_I(MEPA_TRACE_GRP_GEN, "Capture %s, Max packet size = %u Bytes", capture == MEPA_MACSEC_FRAME_CAPTURE_INGRESS ? "ingress" : "egress",
            MEPA_MACSEC_FRAME_CAPTURE_SIZE_MAX);

        // Select ingress/egress side + Max pkt size
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL,
                       (capture == MEPA_MACSEC_FRAME_CAPTURE_INGRESS ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL_SIDE : 0) |
                       LAN80XX_F_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL_MAX_PKT_SIZE(MEPA_MACSEC_FRAME_CAPTURE_SIZE_MAX / 8));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL, (phy_speed == SPEED_1G) ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL_SPEED : 0,
                        LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_CTRL_SPEED);

        T_I(MEPA_TRACE_GRP_GEN, "Enabling capturing of all SA indexes, %s capturing", capture == MEPA_MACSEC_FRAME_CAPTURE_DISABLE ? "Disabling" : "Enabling");
        // We enables all triggers
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA1, LAN80XX_MACSEC_SA_TRIGGER_MASK);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA2, LAN80XX_MACSEC_SA_TRIGGER_MASK);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA3, LAN80XX_MACSEC_SA_TRIGGER_MASK);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA4, LAN80XX_MACSEC_SA_TRIGGER_MASK);
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_ENABLE);
    }
    return MEPA_RC_OK;
}

// Function for getting one frame from the capture FIFO
mepa_rc lan80xx_macsec_frame_get_priv(mepa_device_t                 *dev,
                                      const mepa_port_no_t          port_no,
                                      const u32                     buf_length,
                                      u32                           *const frm_length,
                                      u8                            *const frame)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    const u8 header_size = 2;                  // 64 bit administrator header (two 32 bit registers)
    u32 value = 1;
    u8 i, wr_ptr, frm_cnt;
    mepa_bool_t truncated;
    u32 adm_hdr0, adm_hdr1, frm_data_i;
    *frm_length = 0;

    // Get the amount of data in the FIFO
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_STATUS, &value);
    wr_ptr = LAN80XX_X_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_STATUS_WR_PTR(value);         /* indexes the next 64 bits adm header to be written in the memory */
    frm_cnt = LAN80XX_X_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_STATUS_PKT_COUNT(value);
    if (frm_cnt == 0) {              /* No frames captured */
        T_I(MEPA_TRACE_GRP_GEN, "No Frames are captured");
        return MEPA_RC_OK;
    }
    // Disable the triggers in order to be able to read the FIFO.
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA2, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA1, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA3, 0);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA4, 0);

    /* Read 64 bit Administrator Head */
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_DATA(0), &adm_hdr0);
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_DATA(1), &adm_hdr1);

    truncated = (adm_hdr0 & LAN80XX_MACSEC_FIFO_TRUNCATED_MASK) ? TRUE : FALSE;      /* Determine whether frame is truncated or not */
    *frm_length = (adm_hdr0 & LAN80XX_MACSEC_FIFO_PKT_SIZE_MASK);                   /* 9 bits packet size. */
    T_I(MEPA_TRACE_GRP_GEN, "Frame size:%u, truncated:%u, adm_hdr1:0x%X, adm_hdr0:0x%X, wr_ptr:%u, value:0x%X", *frm_length, truncated, adm_hdr1, adm_hdr0,
        wr_ptr, value);

    // Make sure that frame length is not greater than the amount of data in fifo, which should never happen (wr_ptr uses step of 8 bytes)
    if ((u32)(*frm_length + header_size) >= (u32)(wr_ptr * 8))  {
        T_E(MEPA_TRACE_GRP_GEN, "Frame length (%u bytes) is supposed to be less than the amount of data in the fifo (%u bytes), header_size:%d",
            *frm_length, wr_ptr * 8, header_size);
        *frm_length = wr_ptr;
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_FRAME_TOO_LONG);
    }
    // Get the frame data from the FIFO
    //Each Debug_data register will have 4 bytes of data first 2 registers have header
    frm_data_i = 0;
    for (i = header_size; i <= *frm_length / 4 + header_size; i++) {
        LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_DATA(i), &value);
        frame[frm_data_i++] = value & 0x00000FF;
        frame[frm_data_i++] = (value & 0x0000FF00) >> 8;
        frame[frm_data_i++] = (value & 0x00FF0000) >> 16;
        frame[frm_data_i++] = (value & 0xFF000000) >> 24;
        T_I(MEPA_TRACE_GRP_GEN, "Getting FIFO data:0x%X, i:%d", value, i);
    }

    // Re-enable capture in order to capture next frame.
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA1, LAN80XX_MACSEC_SA_TRIGGER_MASK);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA2, LAN80XX_MACSEC_SA_TRIGGER_MASK);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA3, LAN80XX_MACSEC_SA_TRIGGER_MASK);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_SA4, LAN80XX_MACSEC_SA_TRIGGER_MASK);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_CAPT_DEBUG_TRIGGER_ENABLE);

    // We use error state to signal that frame is not valid
    if (truncated) {
        T_E(MEPA_TRACE_GRP_GEN, "Frame is Truncated, port_no:%d, frm_length:%d, header_size:%d", port_no, *frm_length, header_size);
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_FRAME_TRUNCATED);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_dbg_update_seq_set_(mepa_device_t           *dev,
                                                  const u32                secy_id,
                                                  const mepa_macsec_port_t port,
                                                  const mepa_macsec_sci_t  *const sci,
                                                  u16                      an,
                                                  mepa_bool_t              egr,
                                                  mepa_bool_t              disable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 seq_update = 0;
    u32 record = 0;
    u32 sc = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Update Sequence Port:%u, Egr:%d, AN:%d, Disable:%d", port.port_no, egr, an, disable);
    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));

    if (egr) {
        record = secy->tx_sc.sa[an]->record;
    } else {
        record = secy->rx_sc[sc]->sa[an]->record;
    }
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W0(record)), &seq_update);
    } else {
        LAN80XX_CSR_RD(dev, port.port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W0(record)), &seq_update);
    }
    if (disable) {
        seq_update = seq_update & ~(1 << LAN80XX_MACSEC_CTRL_WORD_SEQ_BIT);
    } else {
        seq_update |= (1 << LAN80XX_MACSEC_CTRL_WORD_SEQ_BIT);
    }
    if (record < LAN80XX_MACSEC_XFORM_REC_NUM_PAGE0) {
        LAN80XX_CSR_WARM_WR(port.port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_TRANSFORM_RECORDS_PAGE0_XFORM_REC_X_W0(record)), seq_update);
    } else {
        LAN80XX_CSR_WARM_WR(port.port_no, LAN80XX_EGR_INGR_REG_EXPAN(LAN80XX, egr, CORE_TRANSFORM_RECORDS_PAGE1_XFORM_REC_X_W0(record)), seq_update);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_enable_set_priv(mepa_device_t              *dev,
                                             const mepa_port_no_t      port_no,
                                             const mepa_macsec_event_t ev_mask,
                                             const mepa_bool_t         enable)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 mask  = 0;
    u32 value = 0;

    if (ev_mask & MEPA_MACSEC_SEQ_THRESHOLD_EVENT) {
        mask |= 1 << LAN80XX_MACSEC_THRESHOLD_EVENT_ENABLE_BIT;
        if (enable) {
            value |= 1 << LAN80XX_MACSEC_THRESHOLD_EVENT_ENABLE_BIT;
        } else {
            value &= ~(1 << LAN80XX_MACSEC_THRESHOLD_EVENT_STATUS_BIT);
        }
    }

    if (ev_mask & MEPA_MACSEC_SEQ_ROLLOVER_EVENT) {
        mask |= 1 << LAN80XX_MACSEC_ROLLOVER_EVENT_ENABLE_BIT;
        if (enable) {
            value |= 1 << LAN80XX_MACSEC_ROLLOVER_EVENT_ENABLE_BIT;
        } else {
            value &= ~(1 << LAN80XX_MACSEC_ROLLOVER_EVENT_STATUS_BIT);
        }
    }
    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_EIP62_INTR_CTRL_STAT, value, mask);
    T_I(MEPA_TRACE_GRP_GEN, "value:0x%X, mask:0x%X", value, mask);

    /* Routing the MACsec Interrupt to Channel Line Interrupt which will route to GPIO */
    LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY_MASK, enable ? LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK : 0,
                    LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY_MASK_ENG_IRQ_STICKY_MASK);

    /* MACsec Interrupt Routing through INTR0 of LINE Slice */
    LAN80XX_CSR_WRM(port_no, LAN80XX_LINE_INTR_CTRL_LINE_INTR_EN(0), enable ? LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_EGR_INTR_EN : 0,
                    LAN80XX_M_LINE_INTR_CTRL_LINE_INTR_EN_MSEC_EGR_INTR_EN);

    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_enable_get_priv(mepa_device_t             *dev,
                                             const mepa_port_no_t      port_no,
                                             mepa_macsec_event_t       *ev_mask)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP62_INTR_CTRL_STAT, &value);
    *ev_mask = 0;
    if (value & (1 << LAN80XX_MACSEC_THRESHOLD_EVENT_ENABLE_BIT)) {
        *ev_mask |= MEPA_MACSEC_SEQ_THRESHOLD_EVENT;
    }

    if (value & (1 << LAN80XX_MACSEC_ROLLOVER_EVENT_ENABLE_BIT)) {
        *ev_mask |= MEPA_MACSEC_SEQ_ROLLOVER_EVENT;
    }
    T_I(MEPA_TRACE_GRP_GEN, "value:0x%X, ev_mask:0x%X", value, *ev_mask);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_poll_priv(mepa_device_t             *dev,
                                       const mepa_port_no_t      port_no,
                                       mepa_macsec_event_t       *ev_mask)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value = 0;
    u32 val = 0;
    *ev_mask = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP62_INTR_CTRL_STAT, &value);
    if (value & (1 << LAN80XX_MACSEC_THRESHOLD_EVENT_STATUS_BIT)) {
        val = (value & (~(1 << LAN80XX_MACSEC_THRESHOLD_EVENT_STATUS_BIT)));
        *ev_mask |= MEPA_MACSEC_SEQ_THRESHOLD_EVENT;
    }

    if (value & (1 << LAN80XX_MACSEC_ROLLOVER_EVENT_STATUS_BIT)) {
        *ev_mask |= MEPA_MACSEC_SEQ_ROLLOVER_EVENT;
        val = (val & (~(1 << LAN80XX_MACSEC_ROLLOVER_EVENT_STATUS_BIT)));
    }

    if (*ev_mask != 0) {
        T_I(MEPA_TRACE_GRP_GEN, "MACsec Interrupt Triggered on port : %d value:0x%X, ev_mask:0x%X", port_no, value, *ev_mask);

        /* Clear the status */
        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_EIP62_INTR_CTRL_STAT, val,
                        LAN80XX_MACSEC_ROLLOVER_EVENT_STATUS_BIT | LAN80XX_MACSEC_THRESHOLD_EVENT_STATUS_BIT);

        /* Clear the Interrupt routing to Aggregate Interrupt GPIO Pin */
        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY, LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY_ENG_IRQ_STICKY,
                        LAN80XX_M_MACSEC_EGR_MACSEC_EGR_MACSEC_STICKY_ENG_IRQ_STICKY);
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_default_action_set_priv(mepa_device_t *dev, const mepa_port_no_t port_no, const mepa_macsec_default_action_policy_t *const policy)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    if (data->macsec_conf.glb.init.enable == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "MacSec on port:%u not enabled", port_no);
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_NOT_ENABLED);
    } else {
        rc = MACSEC_RC_COLD(lan80xx_macsec_default_action_set_(dev, port_no, policy));
        data->macsec_conf.glb.default_action = *policy;
    }
    return rc;
}

mepa_rc lan80xx_macsec_default_action_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_default_action_policy_t *const policy)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    if (!lan80xx_phy_is_macsec_capable(dev)) {
        T_E(MEPA_TRACE_GRP_GEN, "Port/Phy :%u is not MacSec capable", port_no);
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_PHY_NOT_MACSEC_CAPABLE);
    } else {
        *policy = data->macsec_conf.glb.default_action;
    }
    return rc;
}

//Function to add new Secy.
mepa_rc lan80xx_macsec_secy_conf_add_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0, i = 0;
    phy25g_macsec_internal_secy_t *secy;

    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u. TxMAC:", MACADDRESS_FMT, LAN80XX_MACSEC_PORT_ARG(&port), MACADDRESS_ARG(conf->mac_addr));
    T_I(MEPA_TRACE_GRP_GEN, "SecY prm: RP:%d RW:%d Prt frms:%d incl_sci:%d use_es:%d use_scb:%d cipher:%s%s confidentiality offset:%d",
        conf->replay_protect, conf->replay_window, conf->protect_frames, conf->always_include_sci, conf->use_es,
        conf->use_scb, conf->current_cipher_suite > MEPA_MACSEC_CIPHER_SUITE_GCM_AES_256 ? "XPN-" : "",
        (conf->current_cipher_suite % 2) == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128 ? "128" : "256", conf->confidentiality_offset);

    LAN80XX_MACSEC_ASSERT(conf->confidentiality_offset > 127, "Confidentiality offset value not supported");

    if ((rc = lan80xx_macsec_port_check(dev, port, 1, &secy_id)) == MEPA_RC_OK) {
        if (!check_resources(dev, 0, 0)) {
            T_E(MEPA_TRACE_GRP_GEN, "HW resources exhausted");
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_HW_RESOURCE_EXHUSTED);
        } else {
            secy = &data->macsec_conf.secy[secy_id];
            if ((conf->current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                 conf->current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
                conf->replay_window > LAN80XX_MACSEC_REPLAY_WINDOW_SIZE) {

                T_E(MEPA_TRACE_GRP_GEN, "Replay window size cannot be greater than 2^30 for extended packet numbering");
                return MEPA_RC_ERROR;
            }
            secy->conf = *conf;
            secy->sci.port_id = port.port_id;
            secy->service_id = port.service_id;
            secy->tag_bypass = MEPA_MACSEC_BYPASS_TAG_ZERO;
            memcpy(secy->sci.mac_addr.addr, secy->conf.mac_addr.addr, sizeof(secy->sci.mac_addr.addr));
            for (i = 0; i < LAN80XX_MACSEC_ACTION_MAX; ++i) {
                secy->pattern_record[i][0] = MACSEC_NOT_IN_USE;
                secy->pattern_record[i][1] = MACSEC_NOT_IN_USE;
                secy->pattern[i][0].match = MEPA_MACSEC_MATCH_DISABLE;
                secy->pattern[i][1].match = MEPA_MACSEC_MATCH_DISABLE;
            }
            secy->pattern[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_EGRESS].priority = MEPA_MACSEC_MATCH_PRIORITY_LOWEST;
            secy->pattern[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_INGRESS].priority = MEPA_MACSEC_MATCH_PRIORITY_LOWEST;
            if ((rc = lan80xx_is_sci_valid(dev, &secy->sci)) == MEPA_RC_OK) {
                secy->in_use = 1;
            } else {
                secy->in_use = 0;
                T_E(MEPA_TRACE_GRP_GEN, "Secure channel identifier is invalid");
            }
        }
    }
    return rc;
}

static mepa_rc lan80xx_macsec_secy_conf_del_(mepa_device_t *dev, const mepa_macsec_port_t port, const u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u16 sc, max_sc_rx;
    if (secy->tx_sc.in_use) {
        MEPA_RC(lan80xx_macsec_tx_sc_del_(dev, port, secy_id)); // Delete the Tx SC when SecY is deleted
    }
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL) {
            continue;
        }
        MEPA_RC(lan80xx_macsec_rx_sc_del_(dev, port, &secy->rx_sc[sc]->sci, secy_id)); // Delete the SecY's corresponding Rx SC
    }

    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_INGRESS, MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT));
    }
    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT][MEPA_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_INGRESS, MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT));
    }
    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_DROP][MEPA_MACSEC_DIRECTION_INGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_INGRESS, MEPA_MACSEC_MATCH_ACTION_DROP));
    }

    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT][MEPA_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_EGRESS, MEPA_MACSEC_MATCH_ACTION_CONTROLLED_PORT));
    }
    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT][MEPA_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_EGRESS, MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT));
    }
    if (secy->pattern_record[MEPA_MACSEC_MATCH_ACTION_DROP][MEPA_MACSEC_DIRECTION_EGRESS] != MACSEC_NOT_IN_USE) {
        MEPA_RC(lan80xx_macsec_pattern_del_(dev, port, secy_id, MEPA_MACSEC_DIRECTION_EGRESS, MEPA_MACSEC_MATCH_ACTION_DROP));
    }
    memset(secy, 0, sizeof(*secy));
    for (sc = 0; sc < max_sc_rx; sc++) {
        secy->rx_sc[sc] = NULL;
    }
    return MEPA_RC_OK;
}

//Function to delete the Secy.
mepa_rc lan80xx_macsec_secy_conf_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, "port_no: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_secy_conf_del_(dev, port, secy_id);
    }
    return rc;
}

//Function to get the Secy configurations.
mepa_rc lan80xx_macsec_secy_conf_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_secy_conf_t *const conf)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        *conf = data->macsec_conf.secy[secy_id].conf;
    }
    return rc;
}

//Function to update the SecY configurations.
mepa_rc lan80xx_macsec_secy_conf_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_secy_conf_t *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0, sc = 0, sa = 0;
    u32 max_sc_rx;
    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u. TxMAC:"MACADDRESS_FMT, LAN80XX_MACSEC_PORT_ARG(&port), MACADDRESS_ARG(conf->mac_addr));
    T_I(MEPA_TRACE_GRP_GEN, "SecY prm: RP:%d RW:%d Prt frms:%d incl_sci:%d use_es:%d use_scb:%d cipher:%s%s confidentiality offset:%d",
        conf->replay_protect, conf->replay_window, conf->protect_frames, conf->always_include_sci, conf->use_es,
        conf->use_scb, conf->current_cipher_suite > MEPA_MACSEC_CIPHER_SUITE_GCM_AES_256 ? "XPN-" : "",
        (conf->current_cipher_suite % 2) == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_128 ? "128" : "256", conf->confidentiality_offset);

    LAN80XX_MACSEC_ASSERT(conf->confidentiality_offset > 127, "Confidentiality offset value not supported");
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if ((conf->current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
             conf->current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
            conf->replay_window > LAN80XX_MACSEC_REPLAY_WINDOW_SIZE) {

            T_E(MEPA_TRACE_GRP_GEN, "Replay window size cannot be greater than 2^30 for extended packet numbering");
            return MEPA_RC_ERROR;
        }
        secy->conf = *conf;
        memcpy(secy->sci.mac_addr.addr, secy->conf.mac_addr.addr, sizeof(secy->sci.mac_addr.addr));

        max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

        /* Delete the SA configuration because Secy configuration has changed */
        for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
            if (secy->tx_sc.sa[sa] != NULL) {
                if (lan80xx_macsec_tx_sa_disable_(dev, secy_id, port, sa)) {
                    T_E(MEPA_TRACE_GRP_GEN, "Could not disable sa:%u", sa);
                    return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
                if (lan80xx_macsec_tx_sa_del_(dev, secy_id, port, sa)) {
                    T_E(MEPA_TRACE_GRP_GEN, "Could not delete tx sa:%u, port_no:%d port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                    return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_TX_SA);
                }
            }
        }
        for (sc = 0; sc < max_sc_rx; sc++) {
            if (secy->rx_sc[sc] == NULL || !secy->rx_sc[sc]->in_use || (rc = lan80xx_is_sci_valid(dev, &secy->sci)) != MEPA_RC_OK) {
                continue;
            }
            secy->rx_sc[sc]->conf.validate_frames = conf->validate_frames;
            secy->rx_sc[sc]->conf.replay_protect = conf->replay_protect;
            secy->rx_sc[sc]->conf.replay_window = conf->replay_window;
            secy->rx_sc[sc]->conf.confidentiality_offset = conf->confidentiality_offset;

            for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
                if (secy->rx_sc[sc]->sa[sa] != NULL) {
                    if (secy->rx_sc[sc]->sa[sa]->status.in_use) {
                        if (lan80xx_macsec_rx_sa_disable_(dev, secy_id, port, &secy->rx_sc[sc]->sci, sa) != MEPA_RC_OK) {
                            T_E(MEPA_TRACE_GRP_GEN, "Could not disable sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                        }
                    }
                    if (lan80xx_macsec_rx_sa_del_(dev, secy_id, port, &secy->rx_sc[sc]->sci, sa)) {
                        T_E(MEPA_TRACE_GRP_GEN, "Could not delete rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DEL_RX_SA);
                    }
                }
            }
        }
    }
    return rc;
}


static mepa_rc lan80xx_macsec_secy_controlled_set_(mepa_device_t *dev, mepa_macsec_port_t port, const mepa_bool_t enable, const u32 secy_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 sa, sc, max_sc_rx;
    phy25g_macsec_internal_secy_t *secy;
    secy = &data->macsec_conf.secy[secy_id];
    if (secy->controlled_port_enabled == enable) {
        return MEPA_RC_OK;
    }
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);
    for (sc = 0; sc < max_sc_rx; sc++) {
        if (secy->rx_sc[sc] == NULL) {
            continue;
        }
        for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
            if (secy->rx_sc[sc]->sa[sa] != NULL && secy->rx_sc[sc]->sa[sa]->enabled) {
                if (lan80xx_macsec_sa_enable(dev, port.port_no, secy->rx_sc[sc]->sa[sa]->record, INGRESS, enable) != MEPA_RC_OK) {
                    T_E(MEPA_TRACE_GRP_GEN, "Could not disable/enable Rx sa:%u, port_no:%d, port_id:%d, secy_id:%d", sa, port.port_no, port.port_id, secy_id);
                    return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
                }
            }
        }
    }
    for (sa = 0; sa < MEPA_MACSEC_SA_PER_SC; sa++) {
        if (secy->tx_sc.sa[sa] != NULL && secy->tx_sc.sa[sa]->enabled) {
            if (lan80xx_macsec_sa_enable(dev, port.port_no, secy->tx_sc.sa[sa]->record, EGRESS, enable) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "Could not disable/enable Tx sa:%u", sa);
                return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_DISABLE_SA);
            }
        }
    }
    secy->controlled_port_enabled = enable;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_secy_controlled_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_bool_t enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_secy_controlled_set_(dev, port, enable, secy_id);
    }
    return rc;
}

static mepa_rc lan80xx_cp_rule_id_get(mepa_device_t *dev, mepa_port_no_t  port_no, const mepa_macsec_control_frame_match_conf_t *const conf, u32 *indx, u32 *const rule,
                                      mepa_bool_t store)
{

    u32 i;
    *indx = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (!store) { /* find the index to be deleted */
        if (*rule < LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END) {
            *indx = *rule;
        } else if (*rule < LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END) {
            *indx = *rule - LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END;
        } else {
            *indx =  *rule - LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END;
        }
        return MEPA_RC_OK;
    }

    /* Rule ID Match
     * Rule Id  0 and 1 ---> ETHTYPE + DMAC Match
     * Rule Id  2 to 10 ---> ETHTYPE Match
     * Rule Id 10 to 18 ---> DMAC Match
     */
    if ((conf->match & MEPA_MACSEC_MATCH_ETYPE) && (conf->match & MEPA_MACSEC_MATCH_DMAC)) {
        for (i = 0; i < LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END; i++) {
            if (data->macsec_conf.glb.control_match[i].match == MEPA_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                *indx = i; // DMAC/ETYPE index 0 - 1
                return MEPA_RC_OK;
            }
        }
    } else if (conf->match & MEPA_MACSEC_MATCH_ETYPE)  {
        for (i = LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END ; i < LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END; i++) {
            if (data->macsec_conf.glb.control_match[i].match == MEPA_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                *indx = i - LAN80XX_MACSEC_DMAC_AND_ETHTYPE_RULE_ID_END;   /* 0-7*/
                return MEPA_RC_OK;
            }
        }
    } else if (conf->match & MEPA_MACSEC_MATCH_DMAC) {
        for (i = LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END ; i < LAN80XX_MACSEC_MAX_DMAC_RULE_ID_END; i++) {
            if (data->macsec_conf.glb.control_match[i].match == MEPA_MACSEC_MATCH_DISABLE) {
                if (rule != NULL) {
                    *rule = i;
                }
                *indx =  i - LAN80XX_MACSEC_MAX_ETHTYPE_RULE_ID_END;
                return MEPA_RC_OK;
            }
        }
    } else if (conf->match & MEPA_MACSEC_MATCH_DISABLE) {
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_MATCH_DISABLE);
    } else {
        T_E(MEPA_TRACE_GRP_GEN, "Unexpected CP mode %u", conf->match);
        return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_UNEXPECT_CP_MODE);
    }

    T_E(MEPA_TRACE_GRP_GEN, "All CP rules of type '%s' are in use, rule:%d",
        (conf->match == MEPA_MACSEC_MATCH_ETYPE) ? "Etype" : (conf->match == MEPA_MACSEC_MATCH_DMAC) ? "DMAC" : "DMAC/Etype", *rule);
    return dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_ALL_CP_RULES_IN_USE);
}

static mepa_rc lan80xx_macsec_control_frame_match_conf_set_(mepa_device_t                                *dev,
                                                            const mepa_port_no_t                         port_no,
                                                            const mepa_macsec_control_frame_match_conf_t *const conf,
                                                            u32                                          *const rule_id,
                                                            mepa_bool_t                                  store)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 parsed_etype = 1, indx = 0;

    /* Get the next available index for CP rule */
    MEPA_RC(lan80xx_cp_rule_id_get(dev, port_no, conf, &indx, rule_id, store));

    if ((data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_HDR)) {
        parsed_etype = 0;
    }

    if (conf->match == MEPA_MACSEC_MATCH_ETYPE) {
        /* Ethertype Match */
        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_MODE, ((parsed_etype << LAN80XX_8_BIT_SHIFT) << indx),
                             ((parsed_etype << LAN80XX_8_BIT_SHIFT) << indx));

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_MODE, ((parsed_etype << LAN80XX_8_BIT_SHIFT) << indx),
                             ((parsed_etype << LAN80XX_8_BIT_SHIFT) << indx));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH(indx),
                        LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)),
                        LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH(indx),
                        LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)),
                        LAN80XX_M_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_ETHER_TYPE_MATCH);

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx) << LAN80XX_8_BIT_SHIFT) : 0),
                        (LAN80XX_BIT(indx) << LAN80XX_8_BIT_SHIFT));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx) << LAN80XX_8_BIT_SHIFT) : 0),
                        (LAN80XX_BIT(indx) << LAN80XX_8_BIT_SHIFT));
    }
    if (conf->match == MEPA_MACSEC_MATCH_DMAC) {
        /* DMAC Match */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH(indx), lan80xx_get_u32(&conf->dmac.addr[0]));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH(indx),
                        LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                        LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0(conf->dmac.addr[5]),
                        LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8 |
                        LAN80XX_M_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0);

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_MATCH(indx), lan80xx_get_u32(&conf->dmac.addr[0]));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH(indx),
                        LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                        LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0(conf->dmac.addr[5]),
                        LAN80XX_M_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_15_8 |
                        LAN80XX_M_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_ET_MATCH_MAC_DA_MATCH_7_0);

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx)) : 0), LAN80XX_BIT(indx));
        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx)) : 0),  LAN80XX_BIT(indx));
    }

    if (conf->match & MEPA_MACSEC_MATCH_DMAC && conf->match & MEPA_MACSEC_MATCH_ETYPE) {
        /* Ethetype and DMAC Match */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO(indx), lan80xx_get_u32(&conf->dmac.addr[0]));
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO(indx), lan80xx_get_u32(&conf->dmac.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI(indx),
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_7_0(conf->dmac.addr[5]) |
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI(indx),
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_7_0(conf->dmac.addr[5]) |
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                       LAN80XX_F_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_LO(indx), lan80xx_get_u32(&conf->dmac.addr[0]));
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_LO(indx), lan80xx_get_u32(&conf->dmac.addr[0]));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI(indx),
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_7_0(conf->dmac.addr[5]) |
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_START_0_1_HI_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)));

        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI(indx),
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_7_0(conf->dmac.addr[5]) |
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_MAC_DA_MATCH_15_8(conf->dmac.addr[4]) |
                       LAN80XX_F_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MAC_DA_END_0_1_HI_ETHER_TYPE_MATCH(MACSEC_BS(conf->etype)));

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_MODE, ((parsed_etype << LAN80XX_16_BIT_SHIFT) << indx),
                             ((parsed_etype << LAN80XX_16_BIT_SHIFT) << indx));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_INGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx) << LAN80XX_16_BIT_SHIFT) : 0),
                        (LAN80XX_BIT(indx) << LAN80XX_16_BIT_SHIFT));

        LAN80XX_CSR_WARM_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_MODE, ((parsed_etype << LAN80XX_16_BIT_SHIFT) << indx),
                             ((parsed_etype << LAN80XX_16_BIT_SHIFT) << indx));

        LAN80XX_CSR_WRM(port_no, LAN80XX_MACSEC_EGR_CORE_CLASSIFIER_CONTROL_PACKET_CP_MATCH_ENABLE, (store ? (LAN80XX_BIT(indx) << LAN80XX_16_BIT_SHIFT) : 0),
                        (LAN80XX_BIT(indx) << LAN80XX_16_BIT_SHIFT));
    }
    return MEPA_RC_OK;
}



static mepa_rc lan80xx_macsec_rxsa_inst_count_get_(mepa_device_t            *dev,
                                                   const u8                 secy_id,
                                                   const u8                 sc_id,
                                                   mepa_sc_inst_count_t     *sc_count)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u8 rxsa_idx;
    T_D(MEPA_TRACE_GRP_GEN, "RxSA - Port:%d, SecY:%d, SC:%d", data->port_no, secy_id, sc_id);
    /* Rx SA Count */
    for (rxsa_idx = 0; rxsa_idx < MEPA_MACSEC_SA_PER_SC_MAX; rxsa_idx++) {
        if ((secy->rx_sc[sc_id]->sa[rxsa_idx] != NULL) && (secy->rx_sc[sc_id]->sa[rxsa_idx]->in_use == TRUE)) {
            T_D(MEPA_TRACE_GRP_GEN, "RxSA id:%d", rxsa_idx);
            sc_count->sa_id[sc_count->no_sa] = rxsa_idx;
            sc_count->no_sa++;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "RxSA count:%d", sc_count->no_sa);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_txsa_inst_count_get_(mepa_device_t            *dev,
                                                   const u8                 secy_id,
                                                   const u8                 sc_id,
                                                   mepa_sc_inst_count_t     *sc_count)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u8 txsa_idx;
    mepa_sc_inst_count_t *sc_inst_count = sc_count;

    T_D(MEPA_TRACE_GRP_GEN, "TxSA - Port:%d, SecY:%d, SC:%d", data->port_no, secy_id, sc_id);
    secy = &data->macsec_conf.secy[secy_id];
    /* Tx SA Count */
    for (txsa_idx = 0; txsa_idx < MEPA_MACSEC_SA_PER_SC_MAX; txsa_idx++) {
        if ((secy->tx_sc.sa[txsa_idx] != NULL) && (secy->tx_sc.sa[txsa_idx]->in_use == TRUE)) {
            T_D(MEPA_TRACE_GRP_GEN, "TxSA id:%d", txsa_idx);
            sc_inst_count->sa_id[sc_inst_count->no_sa] = txsa_idx;
            sc_inst_count->no_sa++;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "TxSA count:%d", sc_inst_count->no_sa);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_rxsc_inst_count_get_(mepa_device_t            *dev,
                                                   const u8                 secy_id,
                                                   mepa_secy_inst_count_t   *secy_count)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u8 rxsc_idx;
    u32 max_sc_rx;
    mepa_rc rc = MEPA_RC_OK;
    mepa_sc_inst_count_t *sc_inst_count;
    mepa_secy_inst_count_t *secy_inst_count = secy_count;
    max_sc_rx = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);

    T_D(MEPA_TRACE_GRP_GEN, "RxSC - Port:%d, SecY:%d", data->port_no, secy_id);
    secy = &data->macsec_conf.secy[secy_id];
    secy_inst_count->no_rxsc = 0;

    /* Rx SC Count */
    for (rxsc_idx = 0; rxsc_idx < max_sc_rx; rxsc_idx++) {
        if ((secy->rx_sc[rxsc_idx] != NULL) && (secy->rx_sc[rxsc_idx]->in_use == TRUE)) {
            T_D(MEPA_TRACE_GRP_GEN, "RxSC id:%d", rxsc_idx);
            memcpy(&secy_inst_count->rx_sci[secy_inst_count->no_rxsc],
                   &secy->rx_sc[rxsc_idx]->sci, sizeof(mepa_macsec_sci_t));
            secy_inst_count->rxsc_id[secy_inst_count->no_rxsc] = rxsc_idx;
            secy_inst_count->no_rxsc++;
            sc_inst_count = &secy_inst_count->rxsc_inst_count[rxsc_idx];
            rc = lan80xx_macsec_rxsa_inst_count_get_(dev, secy_id, rxsc_idx, sc_inst_count);
            if (rc != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "RxSA Instance count access Error");
            }
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "RxSC count:%d", secy_inst_count->no_rxsc);
    return rc;
}

static mepa_rc lan80xx_macsec_inst_count_get_(mepa_device_t             *dev,
                                              mepa_macsec_inst_count_t  *count)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;
    u8 secy_idx;
    mepa_macsec_inst_count_t inst_counts = {0};
    phy25g_macsec_internal_secy_t *secy;
    u8 max_secy = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_SECY_CNT);
    u8 max_sc   = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);
    memcpy(&inst_counts, &data->inst_counts, sizeof(data->inst_counts));

    if (inst_counts.secy_vport == NULL || inst_counts.secy_inst_count == NULL) {
        T_E(MEPA_TRACE_GRP_GEN, "\n MACsec Instance Count Memory not allocated on port : %d\n", data->port_no);
        return MEPA_RC_ERROR;
    }

    /* Clearing the contents of the structure */
    /* Directly cannot memset the structure to 0 because it has pointer members which will then will
     * not point to any memory so memset contents of pointer seperately */
    for (u8 i = 0; i < max_secy; i++) {
        memset(&inst_counts.secy_vport[i], 0, sizeof(inst_counts.secy_vport[i]));
        memset(&(*inst_counts.secy_inst_count[i].rxsc_id), 0, sizeof(uint8_t) * max_sc);
        memset(&(*inst_counts.secy_inst_count[i].rx_sci), 0, sizeof(mepa_macsec_sci_t) * max_sc);
        memset(&(*inst_counts.secy_inst_count[i].rxsc_inst_count), 0, sizeof(mepa_sc_inst_count_t) * max_sc);

        uint8_t *rxsc_id = inst_counts.secy_inst_count[i].rxsc_id;
        mepa_macsec_sci_t *rx_sci = inst_counts.secy_inst_count[i].rx_sci;
        mepa_sc_inst_count_t *rxsc_inst_count = inst_counts.secy_inst_count[i].rxsc_inst_count;
        memset(&inst_counts.secy_inst_count[i], 0, sizeof(inst_counts.secy_inst_count[i]));

        inst_counts.secy_inst_count[i].rxsc_id = rxsc_id;
        inst_counts.secy_inst_count[i].rx_sci = rx_sci;
        inst_counts.secy_inst_count[i].rxsc_inst_count = rxsc_inst_count;
    }

    T_D(MEPA_TRACE_GRP_GEN, "Macsec Instance - Port:%d", data->port_no);
    for (secy_idx = 0; secy_idx < max_secy; secy_idx++) {

        secy = &data->macsec_conf.secy[secy_idx];
        if ((secy != NULL) && (secy->in_use)) {
            T_D(MEPA_TRACE_GRP_GEN, "SecY idx:%d, SecY VPort:%d", secy_idx, secy->sci.port_id);
            inst_counts.secy_vport[inst_counts.no_secy] = secy->sci.port_id;

            /* Tx SC Count */
            if (secy->tx_sc.in_use == TRUE) {
                T_D(MEPA_TRACE_GRP_GEN, "TxSC id:0");
                inst_counts.secy_inst_count[inst_counts.no_secy].no_txsc = 1;
                inst_counts.secy_inst_count[inst_counts.no_secy].txsc_id = secy->sci.port_id;
                rc = lan80xx_macsec_txsa_inst_count_get_(dev, secy_idx, 0, &inst_counts.secy_inst_count[inst_counts.no_secy].txsc_inst_count);
                if (rc != MEPA_RC_OK) {
                    T_E(MEPA_TRACE_GRP_GEN, "TxSA Instance count access Error");
                }
            }
            T_D(MEPA_TRACE_GRP_GEN, "TxSC count:%d", inst_counts.secy_inst_count[inst_counts.no_secy].no_txsc);

            /* Rx SC Count */
            rc = lan80xx_macsec_rxsc_inst_count_get_(dev, secy_idx, &inst_counts.secy_inst_count[inst_counts.no_secy]);
            if (rc != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "RxSC Instance count access Error");
            }
            T_D(MEPA_TRACE_GRP_GEN, "RxSC count:%d", inst_counts.secy_inst_count[inst_counts.no_secy].no_rxsc);
            inst_counts.no_secy++;
        }
    }
    T_D(MEPA_TRACE_GRP_GEN, "SecY count:%d", inst_counts.no_secy);

    memcpy(count, &inst_counts, sizeof(mepa_macsec_inst_count_t));
    if (inst_counts.no_secy == 0) {
        T_D(MEPA_TRACE_GRP_GEN, "SecYs not created");
        rc = MEPA_RC_OK;
    }
    return rc;
}

mepa_rc lan80xx_macsec_secy_controlled_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_bool_t *const enable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        *enable = secy->controlled_port_enabled;
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sc_set_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_FMT, LAN80XX_MPORT_ARG(port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sc_set_(dev, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sc_update_priv(mepa_device_t *dev, const mepa_macsec_port_t port, const mepa_macsec_tx_sc_conf_t *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;
    LAN80XX_MACSEC_ASSERT(conf->confidentiality_offset > 128, "Confidentiality offset value not supported");
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if (!secy->tx_sc.in_use) {
            T_E(MEPA_TRACE_GRP_GEN, "TX_SC does not exist");
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }
        secy->conf.protect_frames         = conf->protect_frames;
        secy->conf.always_include_sci     = conf->always_include_sci;
        secy->conf.use_es                 = conf->use_es;
        secy->conf.use_scb                = conf->use_scb;
        secy->conf.confidentiality_offset = conf->confidentiality_offset;
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sc_del_priv(mepa_device_t *dev, const mepa_macsec_port_t port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_FMT, LAN80XX_MPORT_ARG(port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sc_del_(dev, port, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sc_status_get_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_status_t *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0, an = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_FMT, LAN80XX_MPORT_ARG(port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];

        if (!secy->tx_sc.in_use) {
            T_E(MEPA_TRACE_GRP_GEN, "TX_SC does not exist");
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }

        secy->tx_sc.status.transmitting = 0;
        for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an++) {
            if (secy->tx_sc.sa[an] != NULL && secy->tx_sc.sa[an]->in_use) {
                secy->tx_sc.status.transmitting = 1;
            }
        }
        *status = secy->tx_sc.status;
        T_D(MEPA_TRACE_GRP_GEN, "Tx SC Status enciphering:%d encoding:%d transmitting:%d created:%d started:%d stopped:%d", status->enciphering_sa,
            status->encoding_sa, status->transmitting, status->created_time, status->started_time, status->stopped_time);
    }
    return rc;
}

//To get the configuration of Tx Secure Channel
mepa_rc lan80xx_macsec_tx_sc_get_conf_priv(mepa_device_t *dev, const mepa_macsec_port_t port, mepa_macsec_tx_sc_conf_t *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if (!secy->tx_sc.in_use) {
            T_I(MEPA_TRACE_GRP_GEN, "TX_SC does not exist");
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_TX_SC_NOT_EXIST);
        }
        conf->protect_frames         = secy->conf.protect_frames;
        conf->always_include_sci     = secy->conf.always_include_sci;
        conf->use_es                 = secy->conf.use_es;
        conf->use_scb                = secy->conf.use_scb;
        conf->confidentiality_offset = secy->conf.confidentiality_offset;
    }
    return rc;
}

// Function to create the new Rx Secure Channel
mepa_rc lan80xx_macsec_rx_sc_add_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const mepa_macsec_sci_t  *const sci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_FMT, LAN80XX_MPORT_SCI_ARG(port, *sci));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sc_add_(dev, port, sci, secy_id);
    }
    return rc;
}

// Function to update the configurations of existing Rx Secure Channel
mepa_rc lan80xx_macsec_rx_sc_update_priv(mepa_device_t                  *dev,
                                         const mepa_macsec_port_t       port,
                                         const mepa_macsec_sci_t        *const sci,
                                         const mepa_macsec_rx_sc_conf_t *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0, sc = 0;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_FMT", conf:"LAN80XX_MACSEC_RX_SC_CONF_FMT, LAN80XX_MPORT_SCI_ARG(port, *sci), LAN80XX_MACSEC_RX_SC_CONF_ARG(conf));
    LAN80XX_MACSEC_ASSERT(conf->confidentiality_offset > 128, "Confidentiality offset value not supported");
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if ((rc = lan80xx_sc_from_sci_get(dev, secy, sci, &sc)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not find SC (from sci)");
        } else {
            if ((secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_128 ||
                 secy->conf.current_cipher_suite == MEPA_MACSEC_CIPHER_SUITE_GCM_AES_XPN_256) &&
                conf->replay_window > LAN80XX_MACSEC_REPLAY_WINDOW_SIZE) {

                T_E(MEPA_TRACE_GRP_GEN, "Replay window size cannot be greater than 2^30 while using extended packet numbering");
                return MEPA_RC_ERROR;
            }
            secy->rx_sc[sc]->conf = *conf;
        }
    }
    return rc;
}

// Function to get the configuration of the Rx Secure Channel
mepa_rc lan80xx_macsec_rx_sc_get_conf_priv(mepa_device_t                  *dev,
                                           const mepa_macsec_port_t       port,
                                           const mepa_macsec_sci_t        *const sci,
                                           mepa_macsec_rx_sc_conf_t       *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0, sc = 0;

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if ((rc = lan80xx_sc_from_sci_get(dev, secy, sci, &sc)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not find SC (from sci)");
        } else {
            *conf = secy->rx_sc[sc]->conf;
        }
    }
    return rc;
}

// Function to get the current status of the Rx Secure channel
mepa_rc lan80xx_macsec_rx_sc_status_get_priv(mepa_device_t *dev,
                                             const mepa_macsec_port_t        port,
                                             const mepa_macsec_sci_t         *const sci,
                                             mepa_macsec_rx_sc_status_t      *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0, an = 0, sc = 0;

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if ((rc = lan80xx_sc_from_sci_get(dev, secy, sci, &sc)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not find SC (from sci)");
        } else {
            secy->rx_sc[sc]->status.receiving = 0;
            for (an = 0; an < MEPA_MACSEC_SA_PER_SC_MAX; an++) {
                if (secy->rx_sc[sc]->sa[an] != NULL && secy->rx_sc[sc]->sa[an]->in_use) {
                    secy->rx_sc[sc]->status.receiving = 1;
                }
            }
            *status = secy->rx_sc[sc]->status;
            T_D(MEPA_TRACE_GRP_GEN, "Rx SC Status.receiving:%d created:%d started:%d stopped:%d",
                status->receiving, status->created_time, status->started_time, status->stopped_time);
        }
    }
    return rc;
}

mepa_rc lan80xx_macsec_pattern_set_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action,
                                        const mepa_macsec_match_pattern_t  *const pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    if (pattern->match & MEPA_MACSEC_MATCH_SMAC) {
        T_E(MEPA_TRACE_GRP_GEN, "Source MAC Address matching is not supported ");
        return MEPA_RC_ERROR;
    }
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not find any secy");
        return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NO_SECY_FOUND);
    }
    secy = &data->macsec_conf.secy[secy_id];
    if (action == MEPA_MACSEC_MATCH_ACTION_DROP || action == MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT) {
        if ((rc = MACSEC_RC_COLD(lan80xx_macsec_pattern_set_(dev, port.port_no, secy_id, direction, action, pattern, 0))) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not set Pattern for action drop and uncontrolled port");
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_COULD_NOT_SET_PATTERN);
        }
    }
    secy->pattern[action][direction] = *pattern;
    return rc;
}

mepa_rc lan80xx_macsec_pattern_get_priv(mepa_device_t                      *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t  action,
                                        mepa_macsec_match_pattern_t        *const pattern)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if (secy->pattern[action][direction].match == MEPA_MACSEC_MATCH_DISABLE) {
            T_I(MEPA_TRACE_GRP_GEN, "No pattern is configured, port:%d, port_id:%d, direction:%d", port.port_no, port.port_id, direction);
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NO_PATTERN_CFG);
        }
        *pattern = secy->pattern[action][direction];
    }
    return rc;
}

mepa_rc lan80xx_macsec_pattern_del_priv(mepa_device_t                    *dev,
                                        const mepa_macsec_port_t           port,
                                        const mepa_macsec_direction_t      direction,
                                        const mepa_macsec_match_action_t   action)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    T_I(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    do {
        if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Could not find any secy");
            return dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_NO_SECY_FOUND);
        }
        secy = &data->macsec_conf.secy[secy_id];
        if (action == MEPA_MACSEC_MATCH_ACTION_DROP || action == MEPA_MACSEC_MATCH_ACTION_UNCONTROLLED_PORT) {
            if ((rc = lan80xx_macsec_pattern_del_(dev, port, secy_id, direction, action)) != MEPA_RC_OK) {
                T_E(MEPA_TRACE_GRP_GEN, "Could not delete the pattern configured ");
                return MEPA_RC_ERROR;
            }
        }
        memset(&secy->pattern[action][direction], 0, sizeof(secy->pattern[action][direction]));
        secy->pattern[action][direction].match = MEPA_MACSEC_MATCH_DISABLE;
    } while (0);
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_set_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t port,
                                      const u16          an,
                                      const u32          next_pn,
                                      const mepa_bool_t  confidentiality,
                                      const mepa_macsec_sak_t *const sak)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    mepa_macsec_pkt_num_t pkt_num;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_AN_FMT" pn:%u, confidentiality:%d cipher:%u", LAN80XX_MPORT_AN_ARG(port, an), next_pn, confidentiality,
        sak->len == 16 ? 128 : 256);
    pkt_num.pn = next_pn;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_set_(dev, secy_id, port, an, pkt_num, confidentiality, sak, NULL);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_get_priv(mepa_device_t            *dev,
                                      const mepa_macsec_port_t port,
                                      const u16                an,
                                      u32 *const               next_pn,
                                      mepa_bool_t              *const confidentiality,
                                      mepa_macsec_sak_t        *const sak,
                                      mepa_bool_t              *const active)
{
    phy25g_macsec_internal_secy_t *secy;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_AN_FMT, LAN80XX_MPORT_AN_ARG(port, an));
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if (secy->tx_sc.sa[an] == NULL) {
            T_I(MEPA_TRACE_GRP_GEN, "AN does not exist, port_no:%d, port_id:%d, an:%d", port.port_no, port.port_id, an);
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_EXIST);
            memset(sak, 0, sizeof(*sak));
            *active          = FALSE;
            *confidentiality = FALSE;
            *next_pn         = 0;
        } else {
            *sak             = secy->tx_sc.sa[an]->sak;
            *active          = secy->tx_sc.sa[an]->enabled;
            *confidentiality = secy->tx_sc.sa[an]->confidentiality;
            *next_pn         = secy->tx_sc.sa[an]->status.next_pn;
        }
        T_D(MEPA_TRACE_GRP_GEN, " -> pn:%u, confidentiality:%s, active:%s", *next_pn, BOOL_ARG(*confidentiality), BOOL_ARG(*active));
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_seca_set_priv(mepa_device_t                *dev,
                                        const mepa_macsec_port_t     port,
                                        const u16                    an,
                                        const mepa_macsec_pkt_num_t  next_pn,
                                        const mepa_bool_t            confidentiality,
                                        const mepa_macsec_sak_t      *const sak,
                                        const mepa_macsec_ssci_t     *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_set_(dev, secy_id, port, an, next_pn, confidentiality, sak, ssci);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t  port,
                                        const u16                 an,
                                        mepa_macsec_pkt_num_t     *const next_pn,
                                        mepa_bool_t               *const confidentiality,
                                        mepa_macsec_sak_t         *const sak,
                                        mepa_bool_t               *const active,
                                        mepa_macsec_ssci_t        *const ssci)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;
    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_AN_FMT, LAN80XX_MPORT_AN_ARG(port, an));
    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        if (secy->tx_sc.sa[an] == NULL) {
            T_I(MEPA_TRACE_GRP_GEN, "AN does not exist, port_no:%d, port_id:%d, an:%d", port.port_no, port.port_id, an);
            rc = dbg_counter_incr(dev, port.port_no, MEPA_RC_ERR_MACSEC_AN_NOT_EXIST);
            memset(sak, 0, sizeof(*sak));
            *active          = FALSE;
            *confidentiality = FALSE;
            next_pn->xpn     = 0;
        } else {
            *sak             = secy->tx_sc.sa[an]->sak;
            *active          = secy->tx_sc.sa[an]->enabled;
            *confidentiality = secy->tx_sc.sa[an]->confidentiality;
            *next_pn         = secy->tx_sc.sa[an]->status.pn_status.next_pn;
            *ssci            = secy->tx_sc.sa[an]->ssci;
        }
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_set_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      const u32                     lowest_pn,
                                      const mepa_macsec_sak_t       *const sak)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    mepa_macsec_pkt_num_t pkt_num;

    pkt_num.pn = lowest_pn;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT", pn:%u cipher:%u", LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an), lowest_pn, sak->len == 16 ? 128 : 256);
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_set_(dev, secy_id, port, sci, an, pkt_num, sak, NULL);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_get_priv(mepa_device_t                 *dev,
                                      const mepa_macsec_port_t      port,
                                      const mepa_macsec_sci_t       *const sci,
                                      const u16                     an,
                                      u32                           *const lowest_pn,
                                      mepa_macsec_sak_t             *const sak,
                                      mepa_bool_t                   *const active)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    mepa_macsec_pkt_num_t pkt_num;
    mepa_macsec_ssci_t temp;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_get_(dev, secy_id, port, sci, an, &pkt_num, sak, active, &temp);
    }

    if (rc == MEPA_RC_OK) {
        *lowest_pn = pkt_num.pn;
        T_D(MEPA_TRACE_GRP_GEN, "-> pn:%u, active:%s", *lowest_pn, BOOL_ARG(*active));
    } else {
        *lowest_pn = 0;
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_seca_set_priv(mepa_device_t *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        const mepa_macsec_pkt_num_t   lowest_pn,
                                        const mepa_macsec_sak_t       *const sak,
                                        const mepa_macsec_ssci_t      *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_set_(dev, secy_id, port, sci, an, lowest_pn, sak, ssci);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_seca_get_priv(mepa_device_t  *dev,
                                        const mepa_macsec_port_t      port,
                                        const mepa_macsec_sci_t       *const sci,
                                        const u16                     an,
                                        mepa_macsec_pkt_num_t         *const lowest_pn,
                                        mepa_macsec_sak_t             *const sak,
                                        mepa_bool_t                   *const active,
                                        mepa_macsec_ssci_t            *const ssci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_get_(dev, secy_id, port, sci, an, lowest_pn, sak, active, ssci);
    }
    return rc;
}

// Function to delete the already existing Rx Secure channel
mepa_rc lan80xx_macsec_rx_sc_del_priv(mepa_device_t *dev,
                                      const mepa_macsec_port_t    port,
                                      const mepa_macsec_sci_t     *const sci)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_FMT, LAN80XX_MPORT_SCI_ARG(port, *sci));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sc_del_(dev, port, sci, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_AN_FMT, LAN80XX_MPORT_AN_ARG(port, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_del_(dev, secy_id, port, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_activate_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_activate_(dev, secy_id, port, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_disable_priv(mepa_device_t *dev, const mepa_macsec_port_t  port, const u16  an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_disable_(dev, secy_id, port, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_status_get_priv(mepa_device_t  *dev, const mepa_macsec_port_t  port, const u16 an, mepa_macsec_tx_sa_status_t  *const status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;

    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        if ((rc = lan80xx_macsec_tx_sa_status_get_(dev, secy_id, port, an)) == MEPA_RC_OK) {
            secy = &data->macsec_conf.secy[secy_id];
            *status = secy->tx_sc.sa[an]->status;
            T_D(MEPA_TRACE_GRP_GEN, "status:"LAN80XX_MACSEC_TX_SA_STATUS_FMT, LAN80XX_MACSEC_TX_SA_STATUS_ARG(*status));
        }
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_activate_priv(mepa_device_t  *dev, const mepa_macsec_port_t port, const mepa_macsec_sci_t  *const sci, const u16 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_activate_(dev, secy_id, port, sci, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_disable_priv(mepa_device_t *dev,
                                          const mepa_macsec_port_t  port,
                                          const mepa_macsec_sci_t   *const sci,
                                          const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_disable_(dev, secy_id, port, sci, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_del_priv(mepa_device_t  *dev,
                                      const mepa_macsec_port_t  port,
                                      const mepa_macsec_sci_t   *const sci,
                                      const u16                 an)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_del_(dev, secy_id, port, sci, an);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_status_get_priv(mepa_device_t    *dev,
                                             const mepa_macsec_port_t    port,
                                             const mepa_macsec_sci_t     *const sci,
                                             const u16                   an,
                                             mepa_macsec_rx_sa_status_t  *const status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_status_get_(dev, secy_id, port, sci, an, status);
    }
    T_D(MEPA_TRACE_GRP_GEN, " -> status:"LAN80XX_MACSEC_RX_SA_STATUS_FMT, LAN80XX_MACSEC_RX_SA_STATUS_ARG(*status));
    return rc;
}

mepa_rc lan80xx_macsec_rx_sa_lowest_pn_update_priv(mepa_device_t  *dev,
                                                   const mepa_macsec_port_t     port,
                                                   const mepa_macsec_sci_t      *const sci,
                                                   const u16                    an,
                                                   const u32                    lowest_pn)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    mepa_macsec_pkt_num_t pkt_num;

    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT", an: %u", LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an), lowest_pn);
    pkt_num.pn = lowest_pn;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_lowest_pn_update_(dev, secy_id, port, sci, an, pkt_num);
    }
    return rc;
}

static mepa_rc lan80xx_macsec_rxsa_an_status_get_(mepa_device_t             *dev,
                                                  const u32                 secy_id,
                                                  const mepa_macsec_port_t  port,
                                                  const mepa_macsec_sci_t   *const sci,
                                                  const u16                 an,
                                                  mepa_bool_t               *status)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy = &data->macsec_conf.secy[secy_id];
    u32 sc = 0;
    MEPA_RC(lan80xx_sc_from_sci_get(dev, secy, sci, &sc));

    if ((secy->rx_sc[sc]->sa[an] == NULL) || (!secy->rx_sc[sc]->sa[an]->in_use)) {
        T_D(MEPA_TRACE_GRP_GEN, "AN not created. AN=%u, port_no:%d, port_id:%d, secy_id:%d", an, port.port_no, port.port_id, secy_id);
        *status = FALSE;
    } else {
        *status = TRUE;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_rxsa_an_status_get_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               const u16                 an,
                                               mepa_bool_t               *status)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;

    LAN80XX_MACSEC_ASSERT(an >= MEPA_MACSEC_SA_PER_SC_MAX, "AN is invalid");
    T_I(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rxsa_an_status_get_(dev, secy_id, port, sci, an, status);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sa_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const u16                       an,
                                               mepa_macsec_tx_sa_counters_t    *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u an:%u", LAN80XX_MACSEC_PORT_ARG(&port), an);
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sa_counters_get_(dev, port.port_no, an, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_tx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               mepa_macsec_tx_sc_counters_t    *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_tx_sc_counters_get_(dev, port.port_no, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rx_sc_counters_get_priv(mepa_device_t                   *dev,
                                               const mepa_macsec_port_t        port,
                                               const mepa_macsec_sci_t         *const sci,
                                               mepa_macsec_rx_sc_counters_t    *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sc_counters_get_(dev, port.port_no, sci, counters, secy_id);
    }
    return rc;
}


mepa_rc lan80xx_macsec_rx_sa_counters_get_priv(mepa_device_t                *dev,
                                               const mepa_macsec_port_t     port,
                                               const mepa_macsec_sci_t      *const sci,
                                               const u16                    an,
                                               mepa_macsec_rx_sa_counters_t *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rx_sa_counters_get_(dev, port.port_no, sci, an, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_txsc_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port)
{
    mepa_rc rc;
    u32 secy_idx = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_idx)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_idx];
        memset(&secy->tx_sc.cnt, 0, sizeof(mepa_macsec_tx_sc_counters_t));
        memset(&secy->tx_sc.del_tx_sa_cnt, 0, sizeof(mepa_macsec_tx_sa_counters_t));
    }
    return rc;
}

mepa_rc lan80xx_macsec_txsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const u16  an)
{
    mepa_rc rc;
    u32 secy_idx = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_idx)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_txsa_counters_clear_(dev, an, secy_idx);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rxsc_counters_clear_priv(mepa_device_t *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci)
{
    mepa_rc rc;
    u32 secy_idx = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_idx)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rxsc_counters_clear_(dev, sci, secy_idx);
    }
    return rc;
}

mepa_rc lan80xx_macsec_rxsa_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port,
                                                const mepa_macsec_sci_t  *const sci,
                                                const u16  an)
{
    mepa_rc rc;
    u32 secy_idx = 0;

    T_D(MEPA_TRACE_GRP_GEN, LAN80XX_MPORT_SCI_AN_FMT, LAN80XX_MPORT_SCI_AN_ARG(port, *sci, an));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_idx)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_rxsa_counters_clear_(dev, sci, an, secy_idx);
    }
    return rc;
}

mepa_rc lan80xx_macsec_secy_counters_get_priv(mepa_device_t                 *dev,
                                              const mepa_macsec_port_t      port,
                                              mepa_macsec_secy_counters_t   *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_secy_counters_get_(dev, port.port_no, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_controlled_counters_get_priv(mepa_device_t                       *dev,
                                                    const mepa_port_no_t                port_no,
                                                    const mepa_macsec_port_t            port,
                                                    mepa_macsec_secy_port_counters_t    *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;
    T_D(MEPA_TRACE_GRP_GEN, "Port: %u", port.port_no);
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_controlled_counters_get_(dev, port, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_get_priv(mepa_device_t                       *dev,
                                                      const mepa_port_no_t                port_no,
                                                      const mepa_macsec_port_t            port,
                                                      mepa_macsec_uncontrolled_counters_t *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;
    T_D(MEPA_TRACE_GRP_GEN, "Port: %u", port.port_no);
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_uncontrolled_counters_get_(dev, port, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_common_counters_get_priv(mepa_device_t                       *dev,
                                                const mepa_port_no_t                port_no,
                                                const mepa_macsec_port_t            port,
                                                mepa_macsec_common_counters_t       *const counters)
{
    mepa_rc rc;
    u32 secy_id = 0;
    T_D(MEPA_TRACE_GRP_GEN, "Common Counters Port: %u", port.port_no);
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_common_counters_get_(dev, port, counters, secy_id);
    }
    return rc;
}

mepa_rc lan80xx_macsec_secy_counters_clear_priv(mepa_device_t  *dev,
                                                const mepa_macsec_port_t  port)
{
    mepa_rc rc;
    u32 secy_idx = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_idx)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_idx];
        memset(&secy->secy_cnt, 0, sizeof(mepa_macsec_secy_counters_t));
    }
    return rc;
}

mepa_rc lan80xx_macsec_uncontrolled_counters_clear_priv(mepa_device_t  *dev,
                                                        const mepa_port_no_t      port_no,
                                                        const mepa_macsec_port_t  port)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        memset(&secy->uncontrolled_cnt, 0, sizeof(mepa_macsec_uncontrolled_counters_t));
    }
    return rc;
}

mepa_rc lan80xx_macsec_controlled_counters_clear_priv(mepa_device_t  *dev,
                                                      const mepa_port_no_t      port_no,
                                                      const mepa_macsec_port_t  port)
{
    mepa_rc rc;
    u32 secy_id = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        memset(&secy->controlled_cnt, 0, sizeof(mepa_macsec_secy_port_counters_t));
    }
    return rc;
}

mepa_rc lan80xx_macsec_common_counters_clear_priv(mepa_device_t  *dev,
                                                  const mepa_port_no_t      port_no,
                                                  const mepa_macsec_port_t  port)
{
    mepa_rc rc;
    u32 secy_id = 0;
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;

    T_D(MEPA_TRACE_GRP_GEN, "Port: %u/%u/%u", LAN80XX_MACSEC_PORT_ARG(&port));
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        memset(&secy->controlled_cnt, 0, sizeof(mepa_macsec_secy_port_counters_t));
        memset(&secy->uncontrolled_cnt, 0, sizeof(mepa_macsec_uncontrolled_counters_t));
        memset(&secy->common_cnt, 0, sizeof(mepa_macsec_common_counters_t));
    }
    return rc;
}


mepa_rc lan80xx_macsec_csr_read_priv(mepa_device_t               *dev,
                                     const mepa_port_no_t        port_no,
                                     const u16                   mmd,
                                     const u32                   addr,
                                     u32                         *const value)
{
    mepa_rc rc = MEPA_RC_OK;
    u32 read;
    if (lan80xx_phy_csr_read(dev, port_no, mmd, addr, &read) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not do CSR read, port_no:%d, mmd:%d,  addr:%d", port_no, mmd, addr);
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_CSR_READ);
    }
    *value = read;
    return rc;
}


mepa_rc lan80xx_macsec_csr_write_priv(mepa_device_t               *dev,
                                      const mepa_port_no_t        port_no,
                                      const u32                   mmd,
                                      const u32                   addr,
                                      const u32                   value)
{
    mepa_rc rc = MEPA_RC_OK;
    if (lan80xx_phy_csr_write(dev, port_no, mmd, addr, value) != MEPA_RC_OK) {
        T_E(MEPA_TRACE_GRP_GEN, "Could not do CSR write, port_no:%d, mmd:%d, addr:%d, value:%d", port_no, mmd, addr, value);
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_CSR_WRITE);
    }
    return rc;
}

mepa_rc lan80xx_macsec_mtu_set_priv(mepa_device_t            *dev,
                                    const mepa_port_no_t     port_no,
                                    const mepa_macsec_mtu_t  *const mtu_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    T_I(MEPA_TRACE_GRP_GEN, "port_no: %u", port_no);
    data->macsec_conf.glb.mtu_conf.mtu  = mtu_conf->mtu;
    data->macsec_conf.glb.mtu_conf.drop = mtu_conf->drop;
    data->macsec_conf.glb.mtu_conf.vlan_unaware_en = mtu_conf->vlan_unaware_en;
    rc = MACSEC_RC_COLD(lan80xx_macsec_mtu_set_(dev, port_no));
    return rc;
}

mepa_rc lan80xx_macsec_mtu_get_priv(mepa_device_t           *dev,
                                    const mepa_port_no_t    port_no,
                                    mepa_macsec_mtu_t       *mtu_conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *mtu_conf = data->macsec_conf.glb.mtu_conf;
    return MEPA_RC_OK;
}


mepa_rc lan80xx_macsec_dbg_update_seq_set_priv(mepa_device_t             *dev,
                                               const mepa_macsec_port_t  port,
                                               const mepa_macsec_sci_t   *const sci,
                                               u16                       an,
                                               mepa_bool_t               egr,
                                               const mepa_bool_t         disable)
{
    mepa_rc rc = MEPA_RC_ERROR;
    u32 secy_id = 0;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        rc = lan80xx_macsec_dbg_update_seq_set_(dev, secy_id, port, sci, an, egr, disable);
    }
    return rc;
}

mepa_rc lan80xx_macsec_event_seq_threshold_set_priv(mepa_device_t        *dev,
                                                    const mepa_port_no_t port_no,
                                                    const u32            threshold)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD, threshold);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_seq_threshold_get_priv(mepa_device_t        *dev,
                                                    const mepa_port_no_t port_no,
                                                    u32                  *threshold)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD, threshold);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_set_priv(mepa_device_t        *dev,
                                                        const mepa_port_no_t port_no,
                                                        const u64            threshold)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 value = 0;
    value = (threshold & 0xFFFFFFFF);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD64_LO, value);
    value = ((threshold >> 32) & 0xFFFFFFFF);
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD64_HI, value);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_event_xpn_seq_threshold_get_priv(mepa_device_t        *dev,
                                                        const mepa_port_no_t port_no,
                                                        u64                  *threshold)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    u32 val_high = 0, val_lo = 0;
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD64_LO, &val_lo);
    LAN80XX_CSR_RD(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EIP162_REG_SEQ_NUM_THRESHOLD64_HI, &val_high);
    *threshold = ((u64)val_high << 32) | val_lo;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_secy_cap_get_priv(mepa_device_t                 *dev,
                                         const mepa_port_no_t          port_no,
                                         mepa_macsec_secy_cap_t        *const cap)
{
    cap->max_peer_scs = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SC);
    cap->max_receive_keys = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SA);
    cap->max_transmit_keys = lan80xx_phy_capability_priv(dev, MEPA_CAP_MACSEC_MAX_SA);
    cap->ciphersuite_cap = MEPA_MACSEC_CAP_GCM_AES_128 | MEPA_MACSEC_CAP_GCM_AES_256 | MEPA_MACSEC_CAP_GCM_AES_XPN_128 | MEPA_MACSEC_CAP_GCM_AES_XPN_256;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_egr_policy_mode_set_priv(mepa_device_t                   *dev,
                                                const mepa_port_no_t            port_no,
                                                const phy25g_macsec_egr_mode_t  egr_policy_mode,
                                                const mepa_etype_t              hdr_eth_type)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (!lan80xx_macsec_cleartags_supported(dev, port_no)) {
        T_E(MEPA_TRACE_GRP_GEN, "Macsec Clearatgs Feature not supported on port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    data->macsec_conf.glb.egr_policy_mode = egr_policy_mode;
    T_I(MEPA_TRACE_GRP_GEN, "Port_no : %d MACsec Egress Policy Mode : %d", port_no, egr_policy_mode);
    if (egr_policy_mode == LAN80XX_MACSEC_EGR_POLICY_HDR) {
        /* Enable the Egress Header detection */
        LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EGRESS_HDR_ETYPE,
                       LAN80XX_F_MACSEC_EGR_CORE_EGRESS_HDR_ETYPE_EGRESS_HDR_ETYPE(hdr_eth_type) |
                       LAN80XX_M_MACSEC_EGR_CORE_EGRESS_HDR_ETYPE_ENABLE);
        return MEPA_RC_OK;
    }
    LAN80XX_CSR_WR(dev, port_no, LAN80XX_MACSEC_EGR_CORE_EGRESS_HDR_ETYPE, 0x0);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_egr_policy_mode_get_priv(mepa_device_t             *dev,
                                                const mepa_port_no_t      port_no,
                                                phy25g_macsec_egr_mode_t  egr_policy_mode)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    egr_policy_mode = data->macsec_conf.glb.egr_policy_mode;
    T_I(MEPA_TRACE_GRP_GEN, "Port_no : %d MACsec Egress Policy Mode : %d", port_no, egr_policy_mode);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_bypass_mode_set_priv(mepa_device_t                    *dev,
                                            const mepa_port_no_t             port_no,
                                            const mepa_macsec_bypass_mode_t  *const bypass)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    data->macsec_conf.glb.bypass_mode = *bypass;
    T_I(MEPA_TRACE_GRP_GEN, "Port_no : %d MACsec Bypass Mode : %d", port_no, *bypass);
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_bypass_mode_get_priv(mepa_device_t              *dev,
                                            const mepa_port_no_t       port_no,
                                            mepa_macsec_bypass_mode_t  *const bypass)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    *bypass = data->macsec_conf.glb.bypass_mode;
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_bypass_tag_set_priv(mepa_device_t                     *dev,
                                           const mepa_macsec_port_t          port,
                                           const mepa_macsec_tag_bypass_t    tag)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    if (data->macsec_conf.glb.bypass_mode.mode != MEPA_MACSEC_BYPASS_TAG) {
        T_E(MEPA_TRACE_GRP_GEN, "Port : %u/%u/%u Bypass mode is not configured to TAG", LAN80XX_MACSEC_PORT_ARG(&port));
        return MEPA_RC_ERROR;
    }
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        T_I(MEPA_TRACE_GRP_GEN, "Port : %u/%u/%u Bypass %d VLAN Tag", LAN80XX_MACSEC_PORT_ARG(&port), tag);
        secy = &data->macsec_conf.secy[secy_id];
        secy->tag_bypass = tag;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_bypass_tag_get_priv(mepa_device_t                 *dev,
                                           const mepa_macsec_port_t      port,
                                           mepa_macsec_tag_bypass_t      *const tag)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    phy25g_macsec_internal_secy_t *secy;
    u32 secy_id = 0;
    mepa_rc rc = MEPA_RC_ERROR;
    if ((rc = lan80xx_macsec_port_check(dev, port, 0, &secy_id)) == MEPA_RC_OK) {
        secy = &data->macsec_conf.secy[secy_id];
        *tag = secy->tag_bypass;
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_cleartags_config_set_priv(mepa_device_t                         *dev,
                                                 const mepa_port_no_t                  port_no,
                                                 const mepa_bool_t                     enable,
                                                 const phy25g_macsec_cleartags_conf_t  *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (enable == 0) {
        data->macsec_conf.glb.cleartags_init_done = 0;
        memset(&data->macsec_conf.glb.cleartags_conf, 0, sizeof(phy25g_macsec_cleartags_conf_t));
        return MEPA_RC_OK;
    }
    /* Enable the Cleartags Configuration */
    if (data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_HDR) {
        T_I(MEPA_TRACE_GRP_GEN, "Port no : %d Cleartags Configuration", port_no);
        data->macsec_conf.glb.cleartags_conf = *conf;
        data->macsec_conf.glb.cleartags_init_done = 1;
        return MEPA_RC_OK;
    }
    T_E(MEPA_TRACE_GRP_GEN, "Port no : %d Set Bypass mode as Header", port_no);
    return MEPA_RC_ERROR;
}


mepa_rc lan80xx_macsec_control_frame_match_conf_set_priv(mepa_device_t                                 *dev,
                                                         const mepa_port_no_t                          port_no,
                                                         const mepa_macsec_control_frame_match_conf_t *const conf,
                                                         u32                                          *const rule_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    mepa_macsec_control_frame_match_conf_t match = *conf;
    u32 local_rule, *rule_id_p = NULL;

    if (data->macsec_conf.glb.init.enable == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "MacSec not enabled, port_no:%d\n", port_no);
        return MEPA_RC_ERROR;
    }
    rule_id_p = (rule_id == NULL) ? &local_rule : rule_id;
    if ((rc = lan80xx_macsec_control_frame_match_conf_set_(dev, port_no, &match, rule_id_p, 1)) == MEPA_RC_OK) {
        data->macsec_conf.glb.control_match[*rule_id_p] = *conf;
        T_I(MEPA_TRACE_GRP_GEN, "Rule_id used:%u match:%x", *rule_id_p, data->macsec_conf.glb.control_match[*rule_id_p].match);
    }
    return rc;
}

mepa_rc lan80xx_macsec_control_frame_match_conf_del_priv(mepa_device_t             *dev,
                                                         const mepa_port_no_t      port_no,
                                                         const u32                 rule_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    mepa_macsec_control_frame_match_conf_t match;
    u32 rule = rule_id;

    T_I(MEPA_TRACE_GRP_GEN, "port_no: %u rule_id:%u", port_no, rule_id);
    if (rule_id >= LAN80XX_MACSEC_CP_RULES) {
        T_E(MEPA_TRACE_GRP_GEN, "Rule id is out of range");
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE);
    } else if (data->macsec_conf.glb.control_match[rule_id].match == MEPA_MACSEC_MATCH_DISABLE) {
        T_E(MEPA_TRACE_GRP_GEN, "Rule does not exist (id:%u)", rule_id);
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_RULE_NOT_EXIST);
    } else {
        match = data->macsec_conf.glb.control_match[rule_id];
        rc = lan80xx_macsec_control_frame_match_conf_set_(dev, port_no, &match, &rule, 0);
        memset(&data->macsec_conf.glb.control_match[rule_id], 0, sizeof(mepa_macsec_control_frame_match_conf_t));
        data->macsec_conf.glb.control_match[rule_id].match = MEPA_MACSEC_MATCH_DISABLE;
    }
    return rc;
}

mepa_rc lan80xx_macsec_control_frame_match_conf_get_priv(mepa_device_t                              *dev,
                                                         const mepa_port_no_t                       port_no,
                                                         mepa_macsec_control_frame_match_conf_t     *const conf,
                                                         u32                                        rule_id)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_OK;

    T_I(MEPA_TRACE_GRP_GEN, "port_no: %u rule_id:%u", port_no, rule_id);
    if (rule_id >= LAN80XX_MACSEC_CP_RULES) {
        T_E(MEPA_TRACE_GRP_GEN, "Rule id is out of range");
        rc = dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_RULE_OUT_OF_RANGE);
    } else {
        *conf = data->macsec_conf.glb.control_match[rule_id];
    }
    return rc;
}

mepa_rc lan80xx_macsec_cleartags_conf_get_priv(mepa_device_t                      *dev,
                                               const mepa_port_no_t               port_no,
                                               mepa_bool_t                        enable,
                                               phy25g_macsec_cleartags_conf_t     *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (!lan80xx_macsec_cleartags_supported(dev, port_no)) {
        T_E(MEPA_TRACE_GRP_GEN, "Macsec Clearatgs Feature not supported on port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    enable = data->macsec_conf.glb.cleartags_init_done;
    *conf = data->macsec_conf.glb.cleartags_conf;
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_inst_mem_alloc(mepa_device_t      *dev)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_secy_inst_count_t *secy_cnt = NULL;
    u8 *secy_ports = NULL;
    u8 *rxsc_id = NULL;
    mepa_macsec_sci_t *sci = NULL;
    mepa_sc_inst_count_t *sc_inst = NULL;

    if (data->inst_counts.secy_vport != NULL || data->inst_counts.secy_inst_count != NULL) {
        lan80xx_mamcsec_mem_free(dev);
    }
    secy_ports = mepa_mem_alloc_int(dev->callout, dev->callout_ctx, sizeof(uint8_t) * LAN80XX_MACSEC_MAX_SECY);
    if (!secy_ports) {
        goto lan80xx_macsec_mem_dealloc;
    }
    secy_cnt = mepa_mem_alloc_int(dev->callout, dev->callout_ctx, sizeof(mepa_secy_inst_count_t) * LAN80XX_MACSEC_MAX_SECY);
    if (!secy_cnt) {
        goto lan80xx_macsec_mem_dealloc;
    }
    rxsc_id = mepa_mem_alloc_int(dev->callout, dev->callout_ctx, sizeof(uint8_t) * LAN80XX_MACSEC_MAX_RX_SC * LAN80XX_MACSEC_MAX_SECY);
    if (!rxsc_id) {
        goto lan80xx_macsec_mem_dealloc;
    }
    memset(rxsc_id, 0, sizeof(uint8_t) * LAN80XX_MACSEC_MAX_RX_SC * LAN80XX_MACSEC_MAX_SECY);
    sci = mepa_mem_alloc_int(dev->callout, dev->callout_ctx, sizeof(mepa_macsec_sci_t) * LAN80XX_MACSEC_MAX_RX_SC * LAN80XX_MACSEC_MAX_SECY);
    if (!sci) {
        goto lan80xx_macsec_mem_dealloc;
    }
    sc_inst = mepa_mem_alloc_int(dev->callout, dev->callout_ctx, sizeof(mepa_sc_inst_count_t) * LAN80XX_MACSEC_MAX_RX_SC * LAN80XX_MACSEC_MAX_SECY);
    if (!sc_inst) {
        goto lan80xx_macsec_mem_dealloc;
    }
    for (u8 c = 0; c < LAN80XX_MACSEC_MAX_SECY; c++) {
        secy_cnt[c].rxsc_id = rxsc_id + (LAN80XX_MACSEC_MAX_RX_SC * c);
        secy_cnt[c].rx_sci = sci + (LAN80XX_MACSEC_MAX_RX_SC * c);
        secy_cnt[c].rxsc_inst_count = sc_inst + (LAN80XX_MACSEC_MAX_RX_SC * c);
    }
    data->inst_counts.secy_vport = secy_ports;
    data->inst_counts.secy_inst_count = secy_cnt;
    return MEPA_RC_OK;

lan80xx_macsec_mem_dealloc:
    if (sc_inst != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, sc_inst);
    }
    if (sci != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, sci);
    }
    if (rxsc_id != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, rxsc_id);
    }
    if (secy_cnt != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, secy_cnt);
    }
    if (secy_ports != NULL) {
        mepa_mem_free_int(dev->callout, dev->callout_ctx, secy_ports);
    }
    return MEPA_RC_ERROR;
}



mepa_rc lan80xx_macsec_inst_count_get_priv(mepa_device_t             *dev,
                                           const mepa_port_no_t      port_no,
                                           mepa_macsec_inst_count_t  *counts)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    mepa_rc rc = MEPA_RC_ERROR;
    if ((data->inst_counts.secy_vport == NULL) || (data->inst_counts.secy_inst_count == NULL)) {
        if ((rc = lan80xx_macsec_inst_mem_alloc(dev)) != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "\n Error in allocating memory to Macsec instance on port : %d \n", port_no);
            return MEPA_RC_ERROR;
        }
    }
    if (data->macsec_conf.glb.init.enable == 0) {
        T_E(MEPA_TRACE_GRP_GEN, "MacSec API port:%u not enabled", port_no);
        rc =  dbg_counter_incr(dev, port_no, MEPA_RC_ERR_MACSEC_NOT_ENABLED);
    } else {
        rc = lan80xx_macsec_inst_count_get_(dev, counts);
        if (rc != MEPA_RC_OK) {
            T_E(MEPA_TRACE_GRP_GEN, "Macsec Instance Count access Error");
        }
    }
    return rc;
}

mepa_rc lan80xx_macsec_cleartags_conf_set_priv(mepa_device_t                         *dev,
                                               const mepa_port_no_t                  port_no,
                                               const mepa_bool_t                     enable,
                                               const phy25g_macsec_cleartags_conf_t  *const conf)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    if (!lan80xx_macsec_cleartags_supported(dev, port_no)) {
        T_E(MEPA_TRACE_GRP_GEN, "Macsec Clearatgs Feature not supported on port : %d", port_no);
        return MEPA_RC_ERROR;
    }
    if (enable == 0) {
        data->macsec_conf.glb.cleartags_init_done = 0;
        memset(&data->macsec_conf.glb.cleartags_conf, 0, sizeof(phy25g_macsec_cleartags_conf_t));
        return MEPA_RC_OK;
    }
    /* Enable the Cleartags Configuration */
    if (data->macsec_conf.glb.bypass_mode.mode == MEPA_MACSEC_BYPASS_HDR) {
        T_I(MEPA_TRACE_GRP_GEN, "Port no : %d Cleartags Configuration", port_no);
        data->macsec_conf.glb.cleartags_conf = *conf;
        data->macsec_conf.glb.cleartags_init_done = 1;
        return MEPA_RC_OK;
    }
    T_E(MEPA_TRACE_GRP_GEN, "Port no : %d Set Bypass mode as Header", port_no);
    return MEPA_RC_ERROR;
}

#define LAN80XX_PHY_MS_DISP_CSR(p,d,m,a,v) \
                       lan80xx_csr_rd(dev,port_no, m, TRUE, a, v); \
                       pr("%-10u %-40s 0x%-10x 0x%-12x\n",p, d,a,*v) \
 
static mepa_rc lan80xx_macsec_dbg_ms_ctrl_reg_dump_(mepa_device_t     *dev,
                                                    mepa_port_no_t     port_no,
                                                    mepa_debug_print_t pr)
{
    u32             value;
    pr("\n\nMACSEC_CTL_REGS MACsec Ingress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_ENA_CFG",              MMD_ID_MACSEC_INGR, (u16)(0xc40),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_CTL_CFG",              MMD_ID_MACSEC_INGR, (u16)(0xc41),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY",               MMD_ID_MACSEC_INGR, (u16)(0xc42),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY_MASK",          MMD_ID_MACSEC_INGR, (u16)(0xc43),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_IGR_LATENCY_CFG",      MMD_ID_MACSEC_INGR, (u16)(0xc44),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_DEBUG_REG_ADDR",       MMD_ID_MACSEC_INGR, (u16)(0xc45),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_DEBUG_REG_DATA",       MMD_ID_MACSEC_INGR, (u16)(0xc46),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG0",          MMD_ID_MACSEC_INGR, (u16)(0xc48),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG1",          MMD_ID_MACSEC_INGR, (u16)(0xc49),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG2",          MMD_ID_MACSEC_INGR, (u16)(0xc4a),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG3",          MMD_ID_MACSEC_INGR, (u16)(0xc4b),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG4",          MMD_ID_MACSEC_INGR, (u16)(0xc4c),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG5",          MMD_ID_MACSEC_INGR, (u16)(0xc4d),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG6",          MMD_ID_MACSEC_INGR, (u16)(0xc4e),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INGR_MACSEC_DEBUG7",          MMD_ID_MACSEC_INGR, (u16)(0xc4f),  &value);

    pr("\n\nMACSEC_CTL_REGS MACsec Egress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_ENA_CFG",              MMD_ID_MACSEC_EGR, (u16)(0xc40),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_CTL_CFG",              MMD_ID_MACSEC_EGR, (u16)(0xc41),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY",               MMD_ID_MACSEC_EGR, (u16)(0xc42),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_STICKY_MASK",          MMD_ID_MACSEC_EGR, (u16)(0xc43),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_FC_CFG",               MMD_ID_MACSEC_EGR, (u16)(0xc44),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_PTP_STALL_CFG",        MMD_ID_MACSEC_EGR, (u16)(0xc45),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_DEBUG_REG_ADDR",       MMD_ID_MACSEC_EGR, (u16)(0xc46),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MACSEC_DEBUG_REG_DATA",       MMD_ID_MACSEC_EGR, (u16)(0xc47),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_CTRL",         MMD_ID_MACSEC_EGR, (u16)(0xcd0),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_STATUS",       MMD_ID_MACSEC_EGR, (u16)(0xcd1),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_TRIGGER",      MMD_ID_MACSEC_EGR, (u16)(0xcd6),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_TRIGGER_SA1",  MMD_ID_MACSEC_EGR, (u16)(0xcd2),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_TRIGGER_SA2",  MMD_ID_MACSEC_EGR, (u16)(0xcd3),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_TRIGGER_SA3",  MMD_ID_MACSEC_EGR, (u16)(0xcd4),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_CAPT_DEBUG_TRIGGER_SA4",  MMD_ID_MACSEC_EGR, (u16)(0xcd5),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG0",           MMD_ID_MACSEC_EGR, (u16)(0xc48),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG1",           MMD_ID_MACSEC_EGR, (u16)(0xc49),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG2",           MMD_ID_MACSEC_EGR, (u16)(0xc4a),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG3",           MMD_ID_MACSEC_EGR, (u16)(0xc4b),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG4",           MMD_ID_MACSEC_EGR, (u16)(0xc4c),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG5",           MMD_ID_MACSEC_EGR, (u16)(0xc4d),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG6",           MMD_ID_MACSEC_EGR, (u16)(0xc4e),  &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EGR_MACSEC_DEBUG7",           MMD_ID_MACSEC_EGR, (u16)(0xc4f),  &value);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_dbg_cls_ctrl_reg_dump_(mepa_device_t     *dev,
                                                     mepa_port_no_t     port_no,
                                                     mepa_debug_print_t pr)
{
    u32  value;
    pr("\n\nMACSEC_CLASSIFIER_VARIOUS_CTRL_REGS Ingress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG",          MMD_ID_MACSEC_INGR, (u16)(0x1e40), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS",         MMD_ID_MACSEC_INGR, (u16)(0x1e41), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS2",        MMD_ID_MACSEC_INGR, (u16)(0x1e42), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAGS2",        MMD_ID_MACSEC_INGR, (u16)(0x1e43), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_CP",      MMD_ID_MACSEC_INGR, (u16)(0x1e52), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_NCP",     MMD_ID_MACSEC_INGR, (u16)(0x1e51), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MISC_CONTROL",        MMD_ID_MACSEC_INGR, (u16)(0x1e5f), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "LATENCY_CONTROL",     MMD_ID_MACSEC_INGR, (u16)(0x1e5d), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DYN_LATENCY_CONTROL", MMD_ID_MACSEC_INGR, (u16)(0x1e5e), &value);

    pr("\n\n Ingress Debug registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG1",            MMD_ID_MACSEC_INGR, (u16)(0x1100), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG3",            MMD_ID_MACSEC_INGR, (u16)(0x1102), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG4",            MMD_ID_MACSEC_INGR, (u16)(0x1103), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_CTRL",              MMD_ID_MACSEC_INGR, (u16)(0x1104), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CP_MATCH_DEBUG",               MMD_ID_MACSEC_INGR, (u16)(0x1F00), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SCP_MPLS_MATCH_DEBUG",         MMD_ID_MACSEC_INGR, (u16)(0x1F01), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SCP_PBB_MATCH_DEBUG",          MMD_ID_MACSEC_INGR, (u16)(0x1F02), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_DEBUG",                    MMD_ID_MACSEC_INGR, (u16)(0x1F08), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_DEBUG",                   MMD_ID_MACSEC_INGR, (u16)(0x1F09), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECTAG_DEBUG",                 MMD_ID_MACSEC_INGR, (u16)(0x1F0A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SC_SA_DEBUG",                  MMD_ID_MACSEC_INGR, (u16)(0x1F0C), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG1",            MMD_ID_MACSEC_INGR, (u16)(0x1F10), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG2",            MMD_ID_MACSEC_INGR, (u16)(0x1F11), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG3",            MMD_ID_MACSEC_INGR, (u16)(0x1F12), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG4",            MMD_ID_MACSEC_INGR, (u16)(0x1F13), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG1",                MMD_ID_MACSEC_INGR, (u16)(0x1F20), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG2",                MMD_ID_MACSEC_INGR, (u16)(0x1F21), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG3",                MMD_ID_MACSEC_INGR, (u16)(0x1F22), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MPLS_DEBUG1",                  MMD_ID_MACSEC_INGR, (u16)(0x1F25), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MPLS_DEBUG2",                  MMD_ID_MACSEC_INGR, (u16)(0x1F26), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_DA_LO",      MMD_ID_MACSEC_INGR, (u16)(0x1F28), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_DA_HI",      MMD_ID_MACSEC_INGR, (u16)(0x1F29), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_SA_LO",      MMD_ID_MACSEC_INGR, (u16)(0x1F2A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_SA_HI",      MMD_ID_MACSEC_INGR, (u16)(0x1F2B), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_MPLS_SECTAG_LO",    MMD_ID_MACSEC_INGR, (u16)(0x1F2C), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_MPLS_SECTAG_HI",    MMD_ID_MACSEC_INGR, (u16)(0x1F2D), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_MPLS_SCI_LO",       MMD_ID_MACSEC_INGR, (u16)(0x1F2E), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_MPLS_SCI_HI",       MMD_ID_MACSEC_INGR, (u16)(0x1F2F), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "RXCAM_MATCH_DEBUG1",           MMD_ID_MACSEC_INGR, (u16)(0x1F30), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "RXCAM_MATCH_DEBUG2",           MMD_ID_MACSEC_INGR, (u16)(0x1F31), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_DA_LO",             MMD_ID_MACSEC_INGR, (u16)(0x1F40), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_DA_HI",             MMD_ID_MACSEC_INGR, (u16)(0x1F41), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SA_LO",             MMD_ID_MACSEC_INGR, (u16)(0x1F42), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SA_HI",             MMD_ID_MACSEC_INGR, (u16)(0x1F43), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SECTAG_LO",         MMD_ID_MACSEC_INGR, (u16)(0x1F44), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SECTAG_HI",         MMD_ID_MACSEC_INGR, (u16)(0x1F45), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SCI_LO",            MMD_ID_MACSEC_INGR, (u16)(0x1F46), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SCI_HI",            MMD_ID_MACSEC_INGR, (u16)(0x1F47), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_FLOW_LOOKUP",              MMD_ID_MACSEC_INGR, (u16)(0x1F48), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_SA_UPDATE",                MMD_ID_MACSEC_INGR, (u16)(0x1F49), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_ATOK_DEBUG_0",          MMD_ID_MACSEC_INGR, (u16)(0x1F4A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_0",          MMD_ID_MACSEC_INGR, (u16)(0x1F4C), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_1",          MMD_ID_MACSEC_INGR, (u16)(0x1F4D), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_2",          MMD_ID_MACSEC_INGR, (u16)(0x1F4E), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_3",          MMD_ID_MACSEC_INGR, (u16)(0x1F4F), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "PBB_DEBUG1",                   MMD_ID_MACSEC_INGR, (u16)(0x1F50), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "PBB_DEBUG2",                   MMD_ID_MACSEC_INGR, (u16)(0x1F51), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CDA_LO",        MMD_ID_MACSEC_INGR, (u16)(0x1F58), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CDA_HI",        MMD_ID_MACSEC_INGR, (u16)(0x1F59), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CSA_LO",        MMD_ID_MACSEC_INGR, (u16)(0x1F5A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CSA_HI",        MMD_ID_MACSEC_INGR, (u16)(0x1F5B), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SA_COUNT_DEBUG1",              MMD_ID_MACSEC_INGR, (u16)(0x3880), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SA_COUNT_DEBUG4",              MMD_ID_MACSEC_INGR, (u16)(0x3883), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECY_COUNT_DEBUG1",            MMD_ID_MACSEC_INGR, (u16)(0x3900), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECY_COUNT_DEBUG4",            MMD_ID_MACSEC_INGR, (u16)(0x3903), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "IFC_COUNT_DEBUG1",             MMD_ID_MACSEC_INGR, (u16)(0x3980), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "IFC_COUNT_DEBUG4",             MMD_ID_MACSEC_INGR, (u16)(0x3983), &value);

    pr("\n\nMACSEC_CLASSIFIER_VARIOUS_CTRL_REGS Egress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAG",          MMD_ID_MACSEC_EGR, (u16)(0x1e40), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS",         MMD_ID_MACSEC_EGR, (u16)(0x1e41), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_TAGS2",        MMD_ID_MACSEC_EGR, (u16)(0x1e42), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_CP_TAGS2",        MMD_ID_MACSEC_EGR, (u16)(0x1e43), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_CP",      MMD_ID_MACSEC_EGR, (u16)(0x1e52), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_NM_FLOW_NCP",     MMD_ID_MACSEC_EGR, (u16)(0x1e51), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MISC_CONTROL",        MMD_ID_MACSEC_EGR, (u16)(0x1e5f), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "LATENCY_CONTROL",     MMD_ID_MACSEC_EGR, (u16)(0x1e5d), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DYN_LATENCY_CONTROL", MMD_ID_MACSEC_EGR, (u16)(0x1e5e), &value);

    pr("\n\n Egress Debug registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG1",            MMD_ID_MACSEC_EGR, (u16)(0x1100), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG3",            MMD_ID_MACSEC_EGR, (u16)(0x1102), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_DEBUG4",            MMD_ID_MACSEC_EGR, (u16)(0x1103), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_COUNT_CTRL",              MMD_ID_MACSEC_EGR, (u16)(0x1104), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CP_MATCH_DEBUG",               MMD_ID_MACSEC_EGR, (u16)(0x1F00), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SCP_MPLS_MATCH_DEBUG",         MMD_ID_MACSEC_EGR, (u16)(0x1F01), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SCP_PBB_MATCH_DEBUG",          MMD_ID_MACSEC_EGR, (u16)(0x1F02), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_DEBUG",                    MMD_ID_MACSEC_EGR, (u16)(0x1F08), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_DEBUG",                   MMD_ID_MACSEC_EGR, (u16)(0x1F09), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECTAG_DEBUG",                 MMD_ID_MACSEC_EGR, (u16)(0x1F0A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SC_SA_DEBUG",                  MMD_ID_MACSEC_EGR, (u16)(0x1F0C), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG1",            MMD_ID_MACSEC_EGR, (u16)(0x1F10), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG2",            MMD_ID_MACSEC_EGR, (u16)(0x1F11), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG3",            MMD_ID_MACSEC_EGR, (u16)(0x1F12), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "TCAM_MATCH_DEBUG4",            MMD_ID_MACSEC_EGR, (u16)(0x1F13), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG1",                MMD_ID_MACSEC_EGR, (u16)(0x1F20), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG2",                MMD_ID_MACSEC_EGR, (u16)(0x1F21), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SAM_PP_DEBUG3",                MMD_ID_MACSEC_EGR, (u16)(0x1F22), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "EHDR_DEBUG",                   MMD_ID_MACSEC_EGR, (u16)(0x1F24), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MPLS_DEBUG1",                  MMD_ID_MACSEC_EGR, (u16)(0x1F25), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "MPLS_DEBUG2",                  MMD_ID_MACSEC_EGR, (u16)(0x1F26), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_DA_LO",      MMD_ID_MACSEC_EGR, (u16)(0x1F28), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_DA_HI",      MMD_ID_MACSEC_EGR, (u16)(0x1F29), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_SA_LO",      MMD_ID_MACSEC_EGR, (u16)(0x1F2A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_EOMPLS_SA_HI",      MMD_ID_MACSEC_EGR, (u16)(0x1F2B), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_DA_LO",             MMD_ID_MACSEC_EGR, (u16)(0x1F40), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_DA_HI",             MMD_ID_MACSEC_EGR, (u16)(0x1F41), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SA_LO",             MMD_ID_MACSEC_EGR, (u16)(0x1F42), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SA_HI",             MMD_ID_MACSEC_EGR, (u16)(0x1F43), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SECTAG_LO",         MMD_ID_MACSEC_EGR, (u16)(0x1F44), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SECTAG_HI",         MMD_ID_MACSEC_EGR, (u16)(0x1F45), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SCI_LO",            MMD_ID_MACSEC_EGR, (u16)(0x1F46), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_SCI_HI",            MMD_ID_MACSEC_EGR, (u16)(0x1F47), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_FLOW_LOOKUP",              MMD_ID_MACSEC_EGR, (u16)(0x1F48), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_SA_UPDATE",                MMD_ID_MACSEC_EGR, (u16)(0x1F49), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_ATOK_DEBUG_0",          MMD_ID_MACSEC_EGR, (u16)(0x1F4A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_0",          MMD_ID_MACSEC_EGR, (u16)(0x1F4C), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_1",          MMD_ID_MACSEC_EGR, (u16)(0x1F4D), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_2",          MMD_ID_MACSEC_EGR, (u16)(0x1F4E), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CRYPTO_CMMD_DEBUG_3",          MMD_ID_MACSEC_EGR, (u16)(0x1F4F), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "PBB_DEBUG1",                   MMD_ID_MACSEC_EGR, (u16)(0x1F50), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "PBB_DEBUG2",                   MMD_ID_MACSEC_EGR, (u16)(0x1F51), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CDA_LO",        MMD_ID_MACSEC_EGR, (u16)(0x1F58), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CDA_HI",        MMD_ID_MACSEC_EGR, (u16)(0x1F59), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CSA_LO",        MMD_ID_MACSEC_EGR, (u16)(0x1F5A), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "DBG_PARSED_PBB_CSA_HI",        MMD_ID_MACSEC_EGR, (u16)(0x1F5B), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SA_COUNT_DEBUG1",              MMD_ID_MACSEC_EGR, (u16)(0x3880), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SA_COUNT_DEBUG4",              MMD_ID_MACSEC_EGR, (u16)(0x3883), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECY_COUNT_DEBUG1",            MMD_ID_MACSEC_EGR, (u16)(0x3900), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "SECY_COUNT_DEBUG4",            MMD_ID_MACSEC_EGR, (u16)(0x3903), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "IFC_COUNT_DEBUG1",             MMD_ID_MACSEC_EGR, (u16)(0x3980), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "IFC_COUNT_DEBUG4",             MMD_ID_MACSEC_EGR, (u16)(0x3983), &value);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_dbg_eip62_reg_dump_(mepa_device_t     *dev,
                                                  mepa_port_no_t     port_no,
                                                  mepa_debug_print_t pr)
{
    u32 value;
    pr("\n\nMACSEC_EIP62_REGS Ingress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CONTEXT_CTRL",      8, (u16)(0x3d02), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INT_CTRL_STAT",     8, (u16)(0x3d04), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CONTEXT_UPD_CTRL",  8, (u16)(0x3d0c), &value);

    pr("\n\nMACSEC_EIP62_REGS Egress Control registers\n\n");
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CONTEXT_CTRL",      31, (u16)(0x3d02), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "INT_CTRL_STAT",     31, (u16)(0x3d04), &value);
    LAN80XX_PHY_MS_DISP_CSR(port_no, "CONTEXT_UPD_CTRL",  31, (u16)(0x3d0c), &value);
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_flow_ctrl_dump(mepa_device_t     *dev,
                                             mepa_port_no_t     port_no,
                                             mepa_debug_print_t pr)
{
    u32 val1 = 0, val2 = 0;
    u32 mmd = 0, addr = 0;
    mmd = MMD_ID_MACSEC_EGR;
    pr("\n\n MACSEC EGRESS Flow Control Registers \n\n");
    for (u8 i = 0; i < LAN80XX_MACSEC_RECORD_PAGE0_CNT; i = i + 2) {
        addr = LAN80XX_MACSEC_FLOW_CTRL1_PAGE0_ADDR + i;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val1));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL1_", (i / 2), addr, val1);
        addr = addr + 1;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val2));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL2_", (i / 2), addr, val2);
    }

    for (u8 i = 0; i < LAN80XX_MACSEC_RECORD_PAGE0_CNT; i = i + 2) {
        addr = LAN80XX_MACSEC_FLOW_CTRL1_PAGE1_ADDR + i;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val1));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL1_", ((i / 2) + 32), addr, val1);
        addr = addr + 1;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val2));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL2_", ((i / 2) + 32), addr, val2);
    }

    mmd = MMD_ID_MACSEC_INGR;
    pr("\n\n MACSEC INGRESS Flow Control Registers \n\n");
    for (u8 i = 0; i < LAN80XX_MACSEC_RECORD_PAGE0_CNT; i = i + 2) {
        addr = LAN80XX_MACSEC_FLOW_CTRL1_PAGE0_ADDR + i;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val1));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL1_", (i / 2), addr, val1);
        addr = addr + 1;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val2));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL2_", (i / 2), addr, val2);
    }

    for (u8 i = 0; i < LAN80XX_MACSEC_RECORD_PAGE0_CNT; i = i + 2) {
        addr = LAN80XX_MACSEC_FLOW_CTRL1_PAGE1_ADDR + i;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val1));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL1_", ((i / 2) + 32), addr, val1);
        addr = addr + 1;
        MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, addr, &val2));
        pr("%-10u %s%-25d 0x%-10x 0x%-12x\n", port_no, "SAM_FLOW_CTRL2_", ((i / 2) + 32), addr, val2);
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tcam_register_dump(mepa_device_t     *dev,
                                                 mepa_port_no_t     port_no,
                                                 mepa_debug_print_t pr)
{
    u32 key1 = 0, key2 = 0, key4 = 0, key5 = 0, key0 = 0;
    u32 mask1 = 0, mask2 = 0, mask4 = 0, mask5 = 0, mask0 = 0;
    u32 mmd = 0, addr = 0;
    u32 page0_base_addr = LAN80XX_MACSEC_TCAM_KEY_PAGE0_ADDR;
    u32 page1_base_addr = LAN80XX_MACSEC_TCAM_KEY_PAGE1_ADDR;
    pr("\n\n\n\n -:-:-:-:-:  MACSEC TCAM Registers :-:-:-:-:-\n\n");
    pr("\n Register Dump Format :");
    pr("\n ==========================\n");
    pr("\n RECORD  KEY0   KEY1   KEY2   KEY4   KEY5    MASK0   MASK1   MASK2   MASK4   MASK5 \n\n");

    for (u8 ingr = 0 ; ingr < 2 ; ingr++) {
        mmd = ingr ? MMD_ID_MACSEC_INGR : MMD_ID_MACSEC_EGR;
        pr("\n\n\n %s \n", ingr ? "INGRESS TCAM Registers :-:-:-" : "EGRESS TCAM Registers :-:-:-");
        for (u8 i = 0; i < LAN80XX_MACSEC_MAX_SA; i++) {
            addr = (i >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? page1_base_addr : page0_base_addr;
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x0) | (i * 16)), &key0));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x1) | (i * 16)), &key1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x2) | (i * 16)), &key2));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x4) | (i * 16)), &key4));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x5) | (i * 16)), &key5));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x8) | (i * 16)), &mask0));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0x9) | (i * 16)), &mask1));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0xa) | (i * 16)), &mask2));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0xc) | (i * 16)), &mask4));
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + 0xd) | (i * 16)), &mask5));
            pr("\n %-5d   0x%08X 0x%08X 0x%08X 0x%08X 0x%08X  0x%08X 0x%08X 0x%08X 0x%08X 0x%08X", i, key0, key1, key2, key4, key5, mask0, mask1, mask2, mask4, mask5);
        }
    }
    pr("\n\n");
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_xform_record_dump(mepa_device_t     *dev,
                                                mepa_port_no_t     port_no,
                                                mepa_debug_print_t pr)
{
    u32 mmd = 0;
    u32 val = 0, addr = 0, i = 0;
    u32 page0_base_addr = LAN80XX_MACSEC_XFORM_PAGE0_ADDR;
    u32 page1_base_addr = LAN80XX_MACSEC_XFORM_PAGE1_ADDR;

    pr("\n\n -:-:-:-:-:  MACSEC XFORM Record Registers :-:-:-:-:-\n\n");
    pr("\n Register Dump Format :");
    pr("\n ========================");
    pr("\n RECORD :");
    pr("\n        W0   W1   W2   W3   W4   W5   W6   W7");
    pr("\n        W8   W9   W10  W11  W12  W13  W14  W15");
    pr("\n        W16  W17  W18  W19  W20  W21  W22  W23");

    for (u8 ingr = 0 ; ingr < 2 ; ingr++) {
        mmd = ingr ? MMD_ID_MACSEC_INGR : MMD_ID_MACSEC_EGR;
        pr("\n\n\n %s \n", ingr ? "INGRESS XFORM Records :-:-:-" : "EGRESS XFORM Registers :-:-:-");

        for (u8 record = 0; record < LAN80XX_MACSEC_MAX_SA; record++) {
            pr("\nRecord %02d:", record);
            addr = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? page1_base_addr : page0_base_addr;
            i = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? (record - LAN80XX_MACSEC_RECORD_PAGE0_CNT) : record;
            for (u8 word = 0; word < LAN80XX_MACSEC_XFORM_REC_SIZE; word++) {
                MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, ((addr + word) | (i * 0x20)), &val));
                if (word % 8 == 0) {
                    pr("\n%-10s", " ");
                }
                pr("0x%08X  ", val);
            }
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_tcam_policy_dump(mepa_device_t     *dev,
                                               mepa_port_no_t     port_no,
                                               mepa_debug_print_t pr)
{
    u32 mmd = 0;
    u32 val = 0, addr = 0, i = 0;
    u32 page0_base_addr = LAN80XX_MACSEC_TCAM_POLICY_PAGE0_ADDR;
    u32 page1_base_addr = LAN80XX_MACSEC_TCAM_POLICY_PAGE1_ADDR;

    for (u8 ingr = 0 ; ingr < 2 ; ingr++) {
        mmd = ingr ? MMD_ID_MACSEC_INGR : MMD_ID_MACSEC_EGR;
        pr("\n\n %s \n\n", ingr ? "\n\n MACSEC INGRESS TCAM Policy Registers :-:-:-:-:-\n\n" :
           "\n\n MACSEC EGRESS TCAM Policy Registers :-:-:-:-:-\n\n");

        for (u8 record = 0; record < LAN80XX_MACSEC_MAX_SA; record++) {
            addr = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? page1_base_addr : page0_base_addr;
            i = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? (record - LAN80XX_MACSEC_RECORD_PAGE0_CNT) : record;
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, (addr + i), &val));
            if (record % 8 == 0) {
                pr("\nRecord %03d :", record);
            }
            pr("0x%08X  ", val);
        }
    }
    return MEPA_RC_OK;
}

static mepa_rc lan80xx_macsec_sc_sa_map_dump(mepa_device_t     *dev,
                                             mepa_port_no_t     port_no,
                                             mepa_debug_print_t pr)
{
    u32 mmd = 0;
    u32 val = 0, addr = 0, i = 0;
    u32 page0_base_addr = LAN80XX_MACSEC_SC_SA_MAP_PAGE0_ADDR;
    u32 page1_base_addr = LAN80XX_MACSEC_SC_SA_MAP_PAGE1_ADDR;

    for (u8 ingr = 0 ; ingr < 2 ; ingr++) {
        mmd = ingr ? MMD_ID_MACSEC_INGR : MMD_ID_MACSEC_EGR;
        pr("\n\n %s \n\n", ingr ? "\n\n MACSEC INGRESS SC & SA Map Registers :-:-:-:-:-\n\n" :
           "\n\n MACSEC EGRESS SC & SA Map Registers :-:-:-:-:-\n\n");

        for (u8 record = 0; record < LAN80XX_MACSEC_MAX_SA; record++) {
            addr = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? page1_base_addr : page0_base_addr;
            i = (record >= LAN80XX_MACSEC_RECORD_PAGE0_CNT) ? (record - LAN80XX_MACSEC_RECORD_PAGE0_CNT) : record;
            MEPA_RC(lan80xx_csr_rd(dev, port_no, mmd, TRUE, (addr + i), &val));
            if (record % 8 == 0) {
                pr("\nRecord %03d :", record);
            }
            pr("0x%08X  ", val);
        }
    }
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_dbg_reg_dump_priv(mepa_device_t     *dev,
                                         mepa_port_no_t     port_no,
                                         mepa_debug_print_t pr)
{
    pr("\n\n\t\t:-:-:-:  MACSEC  :-:-:-:\n\n");
    lan80xx_macsec_dbg_ms_ctrl_reg_dump_(dev, port_no, pr);
    lan80xx_macsec_dbg_cls_ctrl_reg_dump_(dev, port_no, pr);
    lan80xx_macsec_dbg_eip62_reg_dump_(dev, port_no, pr);
    lan80xx_macsec_flow_ctrl_dump(dev, port_no, pr);
    lan80xx_macsec_tcam_register_dump(dev, port_no, pr);
    lan80xx_macsec_tcam_policy_dump(dev, port_no, pr);
    lan80xx_macsec_sc_sa_map_dump(dev, port_no, pr);
    lan80xx_macsec_xform_record_dump(dev, port_no, pr);
    pr("\n\n");
    return MEPA_RC_OK;
}

mepa_rc lan80xx_macsec_dbg_counter_get_priv(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_macsec_rc_dbg_counters_t *const counters)
{
    phy25g_phy_state_t *data = (phy25g_phy_state_t *)dev->data;
    memcpy(counters, &data->macsec_conf.rc_dbg_counters, sizeof(mepa_macsec_rc_dbg_counters_t));
    return MEPA_RC_OK;
}

#endif /* End of MEPA_LAN80XX_MSEC Flag */
