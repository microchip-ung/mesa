// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef MEPA_LAN80XX_TS_PRIVATE_H_
#define MEPA_LAN80XX_TS_PRIVATE_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/phy/api.h>
#include <mepa_driver.h>
#include "lan80xx_regs_util.h"
#include "lan80xx_ts.h"

#define LAN80XX_TS_FLOWS_PER_ENG        (8U)
#define LAN80XX_MAX_CLK_PER_ENGINE      (3U)
#define LAN80XX_PTP_FLOW_INDEX_0        (0U)
#define LAN80XX_PTP_FLOW_INDEX_1        (1U)
#define LAN80XX_PTP_FLOW_INDEX_2        (2U)
#define LAN80XX_PTP_FLOW_INDEX_3        (3U)
#define LAN80XX_PTP_MAX_FLOW            (6U)
#define LAN80XX_PTP_LS_CTRL_0           (0U)
#define LAN80XX_PTP_LS_CTRL_1           (1U)
#define LAN80XX_PTP_LS_CTRL_2           (2U)
#define LAN80XX_PTP_LS_CTRL_3           (3U)
#define LAN80XX_MPLS_MAX_LABEL_VALUE    (0xFFFFF)

#define LAN80XX_PPS_LOW_PERIOD(ti) ((1000000000) - (ti)) /* For computing the low period for the pps user will provide only the width */

/* Extracts a byte from value at position pos */
#define LAN80XX_PHY_TS_EXTRACT_BYTE(value, pos) \
    ( ((uint32_t)(value) & ((uint32_t)0xFFU << (pos))) >> (pos) )

#define LAN80XX_PHY_TS_WRITE_CSR(p, b, a, v) \
    lan80xx_phy_ts_write_csr(dev, (p), (b), (a), (v))

#define LAN80XX_PHY_TS_READ_CSR(p, b, a, v) \
    lan80xx_phy_ts_read_csr(dev, (p), (b), (a), (v))

#define LAN80XX_PHY_TS_ANA_BLK_ID_ING(x) LAN80XX_PHY_TS_ANA_BLK_ID_ING_##x
#define LAN80XX_PHY_TS_ANA_BLK_ID_EGR(x) LAN80XX_PHY_TS_ANA_BLK_ID_EGR_##x
#define LAN80XX_PHY_TS_PROC_BLK_ID(x)    LAN80XX_PHY_TS_PROC_BLK_ID_##x

#if !defined(LAN80XX_PHY_TS_CLR_BITS)
#define LAN80XX_PHY_TS_CLR_BITS(value, mask)   ((value) & (~(mask)))
#endif

#define LAN80XX_PHY_TS_TIME_INTERVAL_ADJUST_32(ti) \
    ((ti) & 0xFFFFFFFFULL)

#define LAN80XX_PHY_TS_EVENT_MASK                (0xFFFFU)


/**
 * \brief Timestamp interrupt events
 **/
/* Timestamp interrupt events */
#define LAN80XX_PHY_TS_INGR_ENGINE_ERR           (0x01U)   /* More than one engine find match */
#define LAN80XX_PHY_TS_INGR_RW_PREAM_ERR         (0x02U)   /* Preamble too short to append timestamp */
#define LAN80XX_PHY_TS_INGR_RW_FCS_ERR           (0x04U)   /* FCS error in ingress */
#define LAN80XX_PHY_TS_EGR_ENGINE_ERR            (0x08U)   /* More than one engine find match */
#define LAN80XX_PHY_TS_EGR_RW_PREAMBLE_ERR       (0x10U)
#define LAN80XX_PHY_TS_EGR_RW_FCS_ERR            (0x20U)   /* FCS error in egress */
#define LAN80XX_PHY_TS_EGR_TS_LEVEL              (0x40U)   /* FIFO reached threshold level */
#define LAN80XX_PHY_TS_EGR_TS_LOADED             (0x80U)   /* Timestamp captured in Tx TSFIFO */
#define LAN80XX_PHY_TS_EGR_TS_OVERFLOW           (0x100U)  /* Tx TSFIFO overflow */
/* #define LAN80XX_PHY_TS_DATA_IN_RSRVD_FIELD    (0x80U)   Data in reserved Field */

#define LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC0     (0x200U)   /* New PPS pushed onto external PPS pin */
#define LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC1     (0x400U)
#define LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC2     (0x800U)
#define LAN80XX_PHY_TS_PTP_LTC_INTR_PTP_LSC3     (0x1000U)
#define LAN80XX_PHY_TS_PTP_LTC_MEAS_INTR         (0x2000U)
#define LAN80XX_PHY_TS_PTP_SER_TOD_LOAD_INTR_ENA (0x4000U)
#define LAN80XX_PHY_TS_PTP_SER_TOD_STORE_INTR_ENA (0x8000U)
#define LAN80XX_PHY_TS_PTP_STI_INTR_EN           (0x10000U)



typedef uint32_t phy25g_ts_event_t; /**< Int events: Single event or 'OR' multiple events above */


/**
 * \brief Timestamping Statistics.
 * \note Use phy25g_phy_ts_stats_get() to retrieve current statistics.
 **/
typedef struct {
    u32    ingr_pream_shrink_err; /**< Frames with preambles too short to shrink */
    u32    egr_pream_shrink_err;  /**< Frames with preambles too short to shrink */
    u32    ingr_fcs_err;          /**< Timestamp block received frame with FCS error in ingress */
    u32    egr_fcs_err;           /**< Timestamp block received frame with FCS error in egress */
    u32    ingr_frm_mod_cnt;      /**< No of frames modified by timestamp block (rewritter) in ingress */
    u32    egr_frm_mod_cnt;       /**< No of frames modified by timestamp block (rewritter) in egress */
    u32    ts_fifo_tx_cnt;        /**< the number of timestamps transmitted to the interface */
    u32    ts_fifo_drop_cnt;      /**< Count of dropped Timestamps not enqueued to the Tx TSFIFO */
} phy25g_phy_ts_stats_t;



/**
 * \brief Frame signature mask
**/
typedef u32 phy25g_ts_fifo_sig_mask_t;

/**
 * \brief Defines Tx TSFIFO signature mask.
 **/
#define LAN80XX_PHY_TS_FIFO_SIG_SRC_IP            (0x01U)  /**< Src IP address: inner IP for IP-over-IP */
#define LAN80XX_PHY_TS_FIFO_SIG_DEST_IP           (0x02U)  /**< Dest IP address */
#define LAN80XX_PHY_TS_FIFO_SIG_MSG_TYPE          (0x04U)  /**< Message type */
#define LAN80XX_PHY_TS_FIFO_SIG_DOMAIN_NUM        (0x08U)  /**< Domain number */
#define LAN80XX_PHY_TS_FIFO_SIG_SOURCE_PORT_ID    (0x10U)  /**< Source port identity */
#define LAN80XX_PHY_TS_FIFO_SIG_SEQ_ID            (0x20U)  /**< PTP frame Sequence ID */
#define LAN80XX_PHY_TS_FIFO_SIG_DEST_MAC          (0x40U)  /**< Dest MAC address */


/**
 * \brief Time interval in ns * 1<<16
 * range +-2**47 ns = 140737 sec = 39 hours
 * For example, 2.5 ns is expressed as 0x0000.0000.0002.8000
 */
typedef int64_t phy25g_timeinterval_t;


/* F(ltc) is give as 318.309886158MHz in all the cases, nominal tod is derived by 1/f(ltc) ~ 3.141592654
* ns part is 3 << 59
* 1 ns is 0x0800000000000000.
* for fractional ns =>  0x0800000000000000 * 0.141592654 gives 0x121FB5452454FCE */
#define NOM_TOD_VAL ( ((u64)(3) << 59) + (u64)0x121FB5452454FCE )

/**
 * \brief Timestamp block clock frequencies
 **/
typedef enum {
    LAN80XX_PHY_TS_CLOCK_FREQ_25M, /** 25 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_125M,   /**< 125 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_15625M, /**< 156.25 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_200M,   /**< 200 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_250M,   /**< 250 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_500M,   /**< 500 MHz */
    LAN80XX_PHY_TS_CLOCK_FREQ_MAX,    /**< MAX Freq */
} phy25g_phy_ts_clockfreq_t;

/**
 * \brief Clock input source
 * \note Valid Clock Sorces:
 *  Malibu: Only External clock source(i.e., 0) is valid, as none of the other clock sources will provide 161.13MHz due to hardware limitation.
 *  Venice: Clock sources External, Host(Client) recovered Tx and Rx clock sources(i.e., 0, 1 and 2) are valid.
 **/
typedef enum {
    LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_25MHZ,   /**< External source */
    LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_50MHZ,   /**< External source */
    LAN80XX_PHY_TS_CLOCK_SRC_EXTERNAL_125MHZ,   /**< External source */
    LAN80XX_PHY_TS_CLOCK_SRC_LINE0,    /**< line 0 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_LINE1,    /**< line 1 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_LINE2,    /**< line 2 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_LINE3,    /**< line 3 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_HOST0,    /**< host 0 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_HOST1,    /**< host 1 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_HOST2,    /**< host 2 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_HOST3,    /**< host 3 recovery clock */
    LAN80XX_PHY_TS_CLOCK_SRC_SYSREFCLK,   /**< 156.25 MHz Clock */
} phy25g_phy_ts_clock_src_t;


/**
 * \brief Analyzer supported frame encapsulation type
 **/
typedef enum {
    /* PTP encap */
    LAN80XX_PHY_TS_ENCAP_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_IP_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_PTP,
    LAN80XX_PHY_TS_ENCAP_ETH_MPLS_ETH_IP_PTP,
    LAN80XX_PHY_TS_ENCAP_NONE,
} phy25g_ts_encap_t;

/**
 * \brief defines Rx Timestamp position inside PTP frame.
 * \note There are two options to put Rx timestamp in PTP frame:
 *  (a) Rx timestamp in Reserved 4 bytes of PTP header.
 *  (b) Shrink Preamble by 4 bytes and append 4 bytes at the end of frame.
 *      In this case Ethernet CRC will be overwritten by Rx timestamp
 *      and a new CRC will be appended after timestamp
 *  Also note that Rx Timestamp position must be same for all the ports in
 *  the system; otherwsie in ingress timestamp will be put in one position
 *  based on that port config whereas egress extract the time from different
 *  position as par that port config.
 **/
typedef enum {
    LAN80XX_PHY_TS_RX_TIMESTAMP_POS_IN_PTP, /**< 4 reserved bytes in PTP header */
    LAN80XX_PHY_TS_RX_TIMESTAMP_POS_AT_END, /**< 4 bytes appended at the end */
} phy25g_phy_ts_rxtimestamp_pos_t;

/**
 * \brief Defines RX Timestamp format i.e. 30bit or 32bit Rx timestamp.
 * \note 30bit mode: The value in the reserved field is simply the nanosecCounter
 *              i.e. [0..999999999]
 *  32bit mode: The value in the reserved field is a 32 bit value and equals:
 *              (nanosecCounter + secCounter*10^9) mod 2^32
 **/
typedef enum {
    LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_30BIT, /**< 30 bit Rx timestamp */
    LAN80XX_PHY_TS_RX_TIMESTAMP_LEN_32BIT, /**< 32 bit Rx timestamp */
} phy25g_phy_ts_rxtimestamp_len_t;

/**
 * \brief Defines Tx TSFIFO access mode.
 **/
typedef enum {
    LAN80XX_PHY_TS_FIFO_MODE_NORMAL, /**< in this mode, timestamp can be read from normal CPU interface */
    LAN80XX_PHY_TS_FIFO_MODE_SPI,    /**< Timestamps are pushed out on the SPI interface */
} phy25g_phy_ts_fifo_mode_t;

/**
 * \brief Defines 4 bytes vs. the default 10 bytes Timestamp stored in Tx TSFIFO.
 **/
typedef enum {
    LAN80XX_PHY_TS_FIFO_TIMESTAMP_LEN_4BYTE,  /**< 4 byte Tx timestamp */
    LAN80XX_PHY_TS_FIFO_TIMESTAMP_LEN_10BYTE, /**< 10 byte Tx timestamp */
} phy25g_phy_ts_fifo_timestamp_len_t;


/**
 * \brief defines the Transparent Clock Operating Mode.
 * \note There are two Modes TC can work:
 *  (a) Mode A: called SUB and ADD Mode where the local time is subtracted
 *      from the correction field at ingress and added at egress port.
 *  (b) Mode B: also called SUB_ADD Mode which uses reserve bytes (or append
 *      at the end of frame by replacing CRC) in PTP header to write
 *      RX_timestamp.
 *  (c) Mode C: also called 48-bit Mode. This mode uses 48-bits of the CF.
 *      This mode is similar to Mode A. At ingress local time is subtracted
 *      from CF and local time is added at egress.
 *  Also note that TC operating Mode must be same for all the ports in
 *  the system.
 **/
typedef enum {
    LAN80XX_PHY_TS_TC_OP_MODE_A = 1, /**< Sub local time at ingress and add at egress from CF */
    LAN80XX_PHY_TS_TC_OP_MODE_B = 0, /**< RX_timestamp using reserved bytes or append at the end as defined in vtss_phy_ts_rxtimestamp_pos_t */
    LAN80XX_PHY_TS_TC_OP_MODE_C = 2, /**< Sub local time at ingress and add at egress from CF and use 48 bits in CF */
} phy25g_phy_ts_tc_op_mode_t;

/* Ts Phy Modes */
typedef enum {
    LAN80XX_PHY_TS_OPER_MODE_LAN = 0, /* LAN Mode     */
    LAN80XX_PHY_TS_OPER_MODE_1G =  1, /* 1G Mode     */
    LAN80XX_PHY_TS_OPER_MODE_10G = 2, /* 1G Mode     */
    LAN80XX_PHY_TS_OPER_MODE_INV = 3  /* Invalid Mode */
} phy25g_ts_oper_mode_t;

/**
 * \brief parameter for setting the alternative clock mode.
 */
/** \brief external clock output configuration. */
typedef struct {
    mepa_bool_t pps_ls_lpbk;       /**< output PPS is loopback to L/S input pin */
    mepa_bool_t ls_lpbk;           /**< L/S act as output pin at 1PPS */
    mepa_bool_t ls_pps_lpbk;       /**< L/S connected to PPS out */
} phy25g_ts_alt_clock_mode_t;


/**
 * \brief PHY timestamp in seconds and nanoseconds (10 bytes Timestamp)
 **/


typedef struct {
    phy25g_pps_input_conf_t        pps_conf;
    phy25g_ts_sertod_input_conf_t     sertod_conf;
    phy25g_ts_epps_conf_t       epps_conf;
    phy25g_ts_ltc_delta_adj_cfg tod_delta_adj_conf;
} phy25g_ptp_lsc_input;



typedef struct {
    phy25g_pps_output_conf_t    pps_conf;
    phy25g_ts_sertod_output_conf_t     sertod_conf;
} phy25g_ptp_lsc_output;


typedef enum {
    LAN80XX_TS_CMD_IDLE,
    LAN80XX_TS_CMD_LOAD,
    LAN80XX_TS_CMD_STORE,
    LAN80XX_TS_CMD_WAVEFORM,
    LAN80XX_TS_CMD_DELTA,
    LAN80XX_TS_CMD_TOD,
} phy25g_ptp_action_type_t;



/**
 * \brief Frequency systhesis pulse configuration
**/

typedef struct {
    mepa_bool_t  enable;               /**< Enable/Disable frequency synthesis pulse */
    uint8_t      high_duty_cycle;      /**< Number of clock cycles pulse is high */
    uint8_t      low_duty_cycle;       /**< Number of clock cycles pulse is low */
} phy25g_ltc_freq_synth_t ;



typedef enum {
    LAN80XX_PHY_TS_ING_LATENCY_SET, /* called from mepa_ts_ingress_latency_set*/
    LAN80XX_PHY_TS_EGR_LATENCY_SET, /* called from mepa_ts_egress_latency_set*/
    LAN80XX_PHY_TS_PATH_DELAY_SET,  /* called from mepa_ts_path_delay_set*/
    LAN80XX_PHY_TS_DELAY_ASYM_SET,  /* called from mepa_ts_delay_asymmetry_set*/
    LAN80XX_PHY_TS_RATE_ADJ_SET,
    LAN80XX_PHY_TS_PORT_ENA_SET,   /* called from lan80xx_ts_mode_set*/
    LAN80XX_PHY_TS_PORT_EVT_MASK_SET,
    LAN80XX_PHY_TS_PORT_OPER_MODE_CHANGE_SET,
    LAN80XX_PHY_TS_PPS_OUTPUT_CONF_SET,
    LAN80XX_PHY_TS_ALT_CLK_SET,
    LAN80XX_PHY_TS_SERTOD_INPUT_SET,
    LAN80XX_PHY_TS_EPPS_SET,
    LAN80XX_PHY_TS_SERTOD_OUTPUT_SET,
    LAN80XX_PHY_TS_PPS_INPUT_CONG_SET,
    LAN80XX_PHY_TS_LOAD_PULSE_DLY_SET,
    LAN80XX_PHY_TS_LTC_FREQ_SYNTH_SET,
} phy25g_ts_proc_conf_t;



/**
 * \brief Defines the initial parameters to be passed to init function
 **/

typedef struct {
    phy25g_phy_ts_clockfreq_t           clk_freq;  /**< reference clock frequency */
    phy25g_phy_ts_clock_src_t           clk_src;   /**< clock source          */
    phy25g_phy_ts_rxtimestamp_pos_t     rx_ts_pos; /**< Rx timestamp position */
    phy25g_phy_ts_rxtimestamp_len_t     rx_ts_len; /**< Rx timestamp length */
    phy25g_phy_ts_fifo_mode_t           tx_fifo_mode; /**< Tx TSFIFO access mode */
    phy25g_phy_ts_fifo_timestamp_len_t  tx_ts_len; /**< timestamp size in Tx TSFIFO */
    mepa_bool_t                       tx_fifo_spi_conf; /**< Modify default 1588_spi configuration, applicable only on PHYs with SPI timestamp fifo support */
    uint8_t                           tx_fifo_hi_clk_cycs; /**< Number of clock periods that the spi_clk is high */
    uint8_t                           tx_fifo_lo_clk_cycs; /**< Number of clock periods that the spi_clk is low */
    phy25g_phy_ts_tc_op_mode_t          tc_op_mode; /**< TC operating mode */
    mepa_bool_t                       auto_clear_ls; /**< Load and Save of LTC are auto cleared */
    mepa_bool_t                       macsec_ena;       /**< MACsec is enabled or disabled */
    mepa_bool_t                       chk_ing_modified;/**< True if the flag bit needs to be modified in ingress and thus in egress */
    mepa_bool_t                       one_step_txfifo; /**< used when transmitting Delay_Req in one step mode. FALSE when correctionfield update is used instead */
    mepa_mch_pch_t                    mch_conf;
} phy25g_phy_ts_init_conf_t;

typedef struct {
    mepa_bool_t          dly_req_recv_10byte_ts;
    uint8_t              rx_flow_clk[24]; // TS_FLOWS_PER_ENG * 3(total engines in 1588 block)
    uint8_t              tx_flow_clk[24]; // TS_FLOWS_PER_ENG * 3(total engines in 1588 block)
} phy25g_ts_data_t;

/** \brief Ethernet per flow configuration */
typedef struct {
    mepa_bool_t  flow_en;  /**< flow enable/disable */
#define LAN80XX_PHY_TS_ETH_ADDR_MATCH_48BIT            ((u8)0x01) /**< Full 48-bit address match */
#define LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_UNICAST      ((u8)0x02) /**< Match any unicast MAC addres */
#define LAN80XX_PHY_TS_ETH_ADDR_MATCH_ANY_MULTICAST    ((u8)0x04) /**< Match any multicast MAC addres */
    uint8_t    addr_match_mode; /**< Multiple match can be possible using OR */
#define LAN80XX_PHY_TS_ETH_MATCH_DEST_ADDR      ((u8)0x00) /**< Match destination MAC address */
#define LAN80XX_PHY_TS_ETH_MATCH_SRC_ADDR       ((u8)0x01) /**< Match source MAC address */
#define LAN80XX_PHY_TS_ETH_MATCH_SRC_OR_DEST    ((u8)0x02) /**< Match source or destination MAC address */
#define LAN80XX_PHY_TS_ETH_MATCH_NONE           ((u8)0x03)
    uint8_t    addr_match_select; /**< src or dest addr to be matched */
    uint8_t    mac_addr[6]; /**< addr to be matched, src or dest */

    mepa_bool_t  vlan_check; /**< TRUE=>verify configured VLAN tag configuration, FALSE=>parse VLAN tag if any, but don't check, for PBB I-tag is always checked */
    uint8_t    num_tag; /**< No of Tags (max 2 tag), for PBB at least I-tag should be present */
#define LAN80XX_PHY_TS_TAG_TYPE_C    ((u8)0x01) /**< Tag type: C */
#define LAN80XX_PHY_TS_TAG_TYPE_S    ((u8)0x02) /**< Tag type: S */
#define LAN80XX_PHY_TS_TAG_TYPE_I    ((u8)0x03) /**< Tag type: I */
#define LAN80XX_PHY_TS_TAG_TYPE_B    ((u8)0x04) /**< Tag type: B */
    uint8_t    outer_tag_type; /**< for PBB enabled with 2-tag, this must be B-tag */
    uint8_t    inner_tag_type; /**< for PBB this must be I-tag; also for single tag inner_tag is used */
#define LAN80XX_PHY_TS_TAG_RANGE_NONE     ((u8)0x00) /**< Neither inner nor outer tag allows range config */
#define LAN80XX_PHY_TS_TAG_RANGE_OUTER    ((u8)0x01) /**< Outer tag allows range config */
#define LAN80XX_PHY_TS_TAG_RANGE_INNER    ((u8)0x02) /**< Inner tag allows range config */
    uint8_t    tag_range_mode;  /**< for PBB no range check is allowed */
    union {
        struct {
            uint16_t    upper; /**< Upper value for outer tag range */
            uint16_t    lower; /**< Lower value for outer tag range */
        } range;  /**< tag in range */
        struct {
            uint16_t    val;  /**< Value */
            uint16_t    mask; /**< Mask */
        } value;  /**< tag in value/mask */
    } outer_tag; /**< Outer tag */
    union {
        struct {
            uint16_t    upper; /**< Upper value for inner tag range */
            uint16_t    lower; /**< Loower value for inner tag range */
        } range;  /**< tag in range */
        struct {
            uint16_t    val; /**< Value */
            uint16_t    mask; /**< Mask */
        } value;  /**< tag in value/mask */
        struct {
            uint32_t    val;   /**< 24-bit I-tag value */
            uint32_t    mask;  /**< 24-bit I-tag mask */
        } i_tag;  /**< I-tag in value/mask. This is applicable for PBB i.e. Eth1 comparator */
    } inner_tag; /**< Inner Tag*/
} phy25g_ts_eth_flow_conf_t;


/**
 * \brief Analyzer Ethernet comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per-flow configuration.
 **/
typedef struct {
    struct {
        mepa_bool_t  pbb_en; /**< PBB tag present, not applicable for Eth2 comparator */
        uint16_t   etype;  /**< The value of Ether type to be checked if Ethertype/length field is an Ethertype */
        uint16_t   tpid;  /**< VLAN TPID for S or B-tag */
    } comm_opt; /**< Ethernet common config */
    phy25g_ts_eth_flow_conf_t flow_opt[8]; /**< Ethernet per flow config */
} phy25g_ts_eth_conf_t; /**< ETH configuration */


/** \brief IP per flow configuration */
typedef struct {
    mepa_bool_t  flow_en;  /**< flow enable/disable */
#define LAN80XX_PHY_TS_IP_MATCH_SRC          0x00 /**< Match source IP address */
#define LAN80XX_PHY_TS_IP_MATCH_DEST         0x01 /**< Match destination IP address */
#define LAN80XX_PHY_TS_IP_MATCH_SRC_OR_DEST  0x02 /**< Match source or destination IP address */
#define LAN80XX_PHY_TS_IP_MATCH_NONE         0x03
    u8    match_mode; /**< match src, dest or either IP address */
    union {
        struct {
            u32    addr; /**< IPv4 address */
            u32    mask; /**< IPv4 address mask */
        } ipv4; /**< IPv4 Address */
        struct {
            u32    addr[4]; /**< IPv6 Address */
            u32    mask[4]; /**<IPv6 Mask */
        } ipv6; /**< IPv6 Mask */
    } ip_addr;  /**< IPv4/IPv6 address to be matched */
} phy25g_ts_ip_flow_conf_t;


/**
 * \brief Analyzer IP comparator configuration options
 * \note Common options apply all the flows within the comparator. Also there
 *  are per flow configuration.
 **/
typedef struct {
    struct {
#define LAN80XX_PHY_TS_IP_VER_4    0x01 /**< Version: IPv4 */
#define LAN80XX_PHY_TS_IP_VER_6    0x02 /**< Version: IPv6 */
        u8    ip_mode; /**< IPv4, IPv6 */
        /**< if next protocol is not UDP, next UDP fields are not used */
        u16   sport_val; /**< UDP source port value */
        u16   sport_mask; /**< UDP source port mask */
        u16   dport_val; /**< UDP dest port value */
        u16   dport_mask; /**< UDP dest port mask */
    } comm_opt; /**< IP common config */

    phy25g_ts_ip_flow_conf_t flow_opt[8]; /**< IP per flow config */
} phy25g_ts_ip_conf_t; /**< IP configuration */


#define LAN80XX_PHY_TS_MPLS_STACK_DEPTH_1    ((u8)0x01) /**< MPLS stack of depth 1 only allows */
#define LAN80XX_PHY_TS_MPLS_STACK_DEPTH_2    ((u8)0x02) /**< MPLS stack of depth 2 only allows */
#define LAN80XX_PHY_TS_MPLS_STACK_DEPTH_3    ((u8)0x04) /**< MPLS stack of depth 3 only allows */
#define LAN80XX_PHY_TS_MPLS_STACK_DEPTH_4    ((u8)0x08) /**< MPLS stack of depth 4 only allows */

#define LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_TOP    0x00 /**< Search starts from the top of the stack */
#define LAN80XX_PHY_TS_MPLS_STACK_REF_POINT_END    0x01 /**< Search starts from the end of the stack */


/**
 * \brief MPLS level range
 **/
typedef struct {
    u32    lower; /**< lower range value */
    u32    upper; /**< upper range value */
    u8     match_mode;/*Label match mode for the label */
} phy25g_ts_mpls_lvl_rng_t;


/** \brief MPLS per flow configuration */
typedef struct {
    BOOL                         flow_en;  /**< flow enable/disable */

    u8                           stack_depth; /**< depth of MPLS level; multiple depth match can be possible using OR */

    mepa_ts_mpls_parse_t         stack_ref_point; /**< Search direction for label matching: top to bottom or bottom to top */
    union {
        struct {
            phy25g_ts_mpls_lvl_rng_t  top; /**< Top level */
            phy25g_ts_mpls_lvl_rng_t  frst_lvl_after_top; /**< First label after the top label */
            phy25g_ts_mpls_lvl_rng_t  snd_lvl_after_top; /**< Second label after the top label */
            phy25g_ts_mpls_lvl_rng_t  thrd_lvl_after_top; /**< Third label after the top label */
        } top_down; /**< Top down configuration */
        struct {
            phy25g_ts_mpls_lvl_rng_t  end; /**< End level */
            phy25g_ts_mpls_lvl_rng_t  frst_lvl_before_end; /**< First label before the end label */
            phy25g_ts_mpls_lvl_rng_t  snd_lvl_before_end; /**< Second label before the end label */
            phy25g_ts_mpls_lvl_rng_t  thrd_lvl_before_end; /**< Third label before the end label */
        } bottom_up; /**< Bottom up configuration */
    } stack_level; /**< 4 level values; top_down or bottom_up depends on stack_ref_point */
} phy25g_ts_mpls_flow_conf_t;

/**
 * \brief Analyzer MPLS comparator configuration options
 **/
typedef struct {
    struct {
        BOOL           cw_en;  /**< flow uses psudowire control word or not */
    } comm_opt; /**< MPLS common config */

    phy25g_ts_mpls_flow_conf_t flow_opt[8]; /**< MPLS per flow config */
} phy25g_ts_mpls_conf_t; /**< MPLS configuration */


/**
 * \brief PTP engine flow configuration options
 **/
typedef struct {
    phy25g_ts_eth_conf_t       eth1_opt;    /**< Eth-1 comparator */
    phy25g_ts_eth_conf_t       eth2_opt;    /**< Eth-2 comparator; for single ETH encap, Eth-1 is used */
    phy25g_ts_ip_conf_t        ip1_opt;     /**< IP-1 comparator */
    phy25g_ts_ip_conf_t        ip2_opt;     /**< IP-2 comparator; for single IP encap, IP-1 is used */
    phy25g_ts_mpls_conf_t      mpls_opt;    /**< MPLS comparator */
} phy25g_ts_ptp_engine_flow_conf_t;

/**
 *\brief Defines Analyzer engine ID
 **/
typedef enum {
    LAN80XX_PHY_TS_PTP_ENGINE_ID_0, /**< PTP engine 0 */
    LAN80XX_PHY_TS_PTP_ENGINE_ID_1, /**< PTP engine 1 */
    LAN80XX_PHY_TS_OAM_ENGINE_ID_2A, /**< OAM engine 2A, no PTP support */
    LAN80XX_PHY_TS_OAM_ENGINE_ID_2B, /**< OAM engine 2B, no PTP; only OAM-over-ETH support */
    LAN80XX_PHY_TS_ENGINE_ID_INVALID, /**< Invalid Engine ID */
} phy25g_ts_engine_t;

/**
 * \brief to split the ingress and egress analyzer blocks
 **/
typedef enum {
    LAN80XX_PHY_TS_ANA_BLK_ID_ING_0,
    LAN80XX_PHY_TS_ANA_BLK_ID_EGR_0,
    LAN80XX_PHY_TS_ANA_BLK_ID_ING_1,
    LAN80XX_PHY_TS_ANA_BLK_ID_EGR_1,
    LAN80XX_PHY_TS_ANA_BLK_ID_ING_2,
    LAN80XX_PHY_TS_ANA_BLK_ID_EGR_2,
    LAN80XX_PHY_TS_PROC_BLK_ID_0,
    LAN80XX_PHY_TS_PROC_BLK_ID_1,
    LAN80XX_PHY_TS_MAX_BLK_ID
} phy25g_ts_blk_id_t;


typedef struct lan80xx_phy_ts_target_map {
    uint16_t  dev_id;
    uint16_t  mmd_addr;
    uint16_t  mdio_address[LAN80XX_PHY_TS_MAX_BLK_ID];
} lan80xx_phy_ts_biu_addr_map_t;



/**
 * \brief Analyzer flow configuration options
 * \note Engine configuration will be parsed to know PTP or OAM flow based on
 * encapsulation type provided during engine allocation.
 **/
typedef struct {
    mepa_bool_t                              eng_mode;    /**< engine enable/disable */
    union {
        phy25g_ts_ptp_engine_flow_conf_t ptp;       /**< PTP engine configuration */
    } flow_conf; /**< PTP/OAM flow config */
} phy25g_ts_engine_flow_conf_t;


/**
 * \brief Flow matching within an analyzer engine.
 * \note There are two types of flow match possible:
 *  (1) Strict flow matching: A valid frame must use the same flow IDs in all
 *      comparators in the engine except the PTP and MPLS comparators.
 *  (2) A valid frame may match any enabled flow within each comparator.
 *  There is one HW restriction mentioned above for flow match mode i.e.
 *  ingress and egress for same engine ID must have same flow match.
 *  In other words there is no provision to configure strict flow match in
 *  ingress, but non-strict flow match for egress. Same restriction for OAM
 *  engine 2A and 2B and also for ingress and egress i.e. engine 2A and 2B
 *  both ingress and egress must have same flow match mode.
 *
 **/
typedef enum {
    LAN80XX_PHY_TS_ENG_FLOW_MATCH_ANY,    /**< match any flow in comparators */
    LAN80XX_PHY_TS_ENG_FLOW_MATCH_STRICT  /**< strict flow match */
} phy25g_ts_engine_flow_match_t;


/**
 * \brief Analyzer PTP comparator configuration options
 **/
typedef struct {
    mepa_bool_t             range_en;  /**< PTP domain number in range enable/disable */
    mepa_range_unit8_t      range; /* Domain Range */
    mepa_value_unit8_t      value; /* Domain value */
} phy25g_ts_ptp_conf_t;



/**
 * \brief Analyzer PTP action configuration options
 * \note Timestamp action will be based on clock type and delay measurement method.
 **/
typedef struct {
    mepa_bool_t                    enable;   /**< PTP action active/enable or not */
    //phy25g_ts_engine_channel_map_t channel_map;  /**< maps action to channel for multi-channel timestamp block */
    phy25g_ts_ptp_conf_t           ptp_conf;    /**< PTP configuration */
    mepa_ts_ptp_clock_mode_t       clk_mode;     /**< clock mode: bc1step, bc2step, tc1step or tc2step */
    mepa_ts_ptp_delaym_type_t      delaym_type;  /**< delay measurement method: P2P, E2E */
    mepa_bool_t                    cf_update;    /**< correction field update for bc1step */
    mepa_bool_t                    delay_req_recieve_timestamp; /**<auto Delay_Req/Response feature */
} phy25g_ts_ptp_engine_action_t;


/**
 * \brief Engine Action configuration options
 * \note Number of PTP actions in a engine depends on clock mode and delay
 * method, like TC1Step and P2P, it requires 3 ingress rules to be added into
 * PTP flows. There are total 6 flows in PTP . For each
 * frame type that needs to be timestamped requires one rule (i.e 1 flow).
 * So application should decide the number of actions accordingly.
 *. The number of PTP actions config here is the maximum number,
 * application should decide how many are
 * valid for a engine based on clock mode and delay method.
 **/
typedef struct {
    mepa_bool_t  action_ptp;  /**< is the action for PTP or OAM */
//    mepa_bool_t  action_gen;  /**< generic action or not */
    union {
        phy25g_ts_ptp_engine_action_t   ptp_conf; /**< Max 2 PTP action per engine */
        //      phy25g_ts_oam_engine_action_t   oam_conf[6]; /**< Max 6 OAM action per engine */
        //      phy25g_ts_generic_action_t      gen_conf[6]; /**< Max 6 Generic action per engine */
    } action; /**< PTP/OAM action config */
} phy25g_ts_engine_action_t;

/**
 * \brief PTP Event Message TYPES.
 * \note  4 Types of Event messages.
 *
 **/
typedef enum {
    PTP_MSG_TYPE_SYNC,
    PTP_MSG_TYPE_DELAY_REQ,
    PTP_MSG_TYPE_PDELAY_REQ,
    PTP_MSG_TYPE_PDELAY_RESP,
} phy25g_ts_ptp_msg_type_t;


/**
 * \brief PTP PLL values for clock sources.
 * \note  Types of Event messages.
 *
 **/
typedef struct {
    uint16_t pll_r;
    uint16_t pll_div_fi;
    uint16_t pll_divff_hi;
    uint16_t pll_divff_lo;
    uint16_t pll_divq;
    uint16_t clk_sel;
} lan80xx_phy_ts_pll_map_t;


// this is diffrenent from phy25g_ts_eng_init_conf_t
typedef struct {
    mepa_bool_t                     eng_used; /* allocated the engine to application */
    phy25g_ts_encap_t               encap_type; /* engine encapsulation */
    phy25g_ts_engine_flow_match_t   flow_match_mode; /* strict/non-strict flow match */
    uint8_t                         flow_st_index; /* start index of flow */
    uint8_t                         flow_end_index; /* end index of flow */
    phy25g_ts_engine_flow_conf_t    flow_conf; /* engine flow config */
    phy25g_ts_engine_action_t       action_conf; /* engine action */
    uint8_t                         action_flow_map[6]; /* action map to flow */
} phy25g_ts_eng_conf_t;


/** \brief Clock frequency ratio in scaled PartsPerBillion, defined as rate in units of ppb and multiplied by 2^16 */
/** \brief Example, 2.5 ppb is expressed as 0000 0000 0002 8000 */
typedef i64 phy25g_ts_scaled_ppb_t;


typedef struct {
    mepa_bool_t                      port_ts_init_done; /* PHY TS init done */
    mepa_port_no_t                   base_port; /* base port for multi-channel PHY */
    mepa_bool_t                       port_ena;
    mepa_port_no_t                   alt_port;
    phy25g_phy_ts_clockfreq_t          clk_freq;  /* reference clock frequency */
    phy25g_phy_ts_clock_src_t          clk_src;   /* reference clock source */
    phy25g_phy_ts_rxtimestamp_pos_t    rx_ts_pos; /* Rx timestamp position */
    phy25g_phy_ts_rxtimestamp_len_t    rx_ts_len; /* Rx timestamp length */
    phy25g_phy_ts_fifo_mode_t          tx_fifo_mode; /* Tx TSFIFO access mode */
    phy25g_phy_ts_fifo_timestamp_len_t tx_ts_len; /* timestamp size in Tx TSFIFO */
    phy25g_phy_ts_tc_op_mode_t         tc_op_mode; /* TC operating Mode: Mode A or B*/
    uint16_t                         load_pulse_delay;
    mepa_bool_t                      chk_ing_modified;
    mepa_bool_t                      auto_clear_ls;
    mepa_bool_t                      macsec_ena;
    mepa_bool_t                      one_step_txfifo;
    uint8_t                          ip1_nxt_cmp[4]; /* IP1 comparator is available only in blocks 0,1,2,3. */
    uint8_t                          ip2_nxt_cmp[4]; /* IP2 comparator is available only in blocks 0,1,2,3. */
    phy25g_ts_event_t                  event_mask; /* interrupt mask config */
    uint32_t                         egr_reg_mask;  /* Egress mask register value */
    uint32_t                         ingr_reg_mask; /* Ingress mask register value */
    uint32_t                         ltc_reg_mask;  /* LTC reg mask value */
    mepa_bool_t                      event_enable; /* interrupt enable/disable */
    mepa_bool_t                      is_gen2;
    phy25g_ts_scaled_ppb_t         rate_adj;  /* clock rate adjustment */
    phy25g_ts_alt_clock_mode_t       alt_clock_mode;
    phy25g_ltc_freq_synth_t            ltc_freq_synth;
    phy25g_timeinterval_t              ingress_latency;
    phy25g_timeinterval_t              egress_latency;
    phy25g_timeinterval_t              path_delay;
    phy25g_timeinterval_t              delay_asym;
    phy25g_ts_fifo_sig_mask_t      sig_mask;
    phy25g_ts_eng_conf_t           egress_eng_conf[4];
    phy25g_ts_eng_conf_t           ingress_eng_conf[4];
    mepa_mch_pch_t                   mch_conf;
} phy25g_phy_ts_port_conf_t;

typedef struct {
    uint8_t   speed;
    mepa_bool_t rs_fec_25g;
    mepa_bool_t mac_pcs_retiming_mode;
    mepa_bool_t egress_ingress;
    uint32_t local_latency_ns;
    uint8_t  local_latency_sns;

    uint32_t cfg_stall_latency;
    uint8_t  cfg_stall_latency_sns;

    uint32_t  pslocal_latency_ns;
    uint8_t   pslocal_latency_sns;

} phy25g_phy_ts_local_latency;


/**
 * \brief Defines Tx TSFIFO signature length.
 **/
#define LAN80XX_PHY_TS_SIG_TIME_STAMP_LEN         (11U)
#define LAN80XX_PHY_TS_SIG_SOURCE_PORT_ID_LEN     (10U)
#define LAN80XX_PHY_TS_SIG_SEQUENCE_ID_LEN        (2U)
#define LAN80XX_PHY_TS_SIG_DEST_IP_LEN            (4U)
#define LAN80XX_PHY_TS_SIG_SRC_IP_LEN             (4U)
#define LAN80XX_PHY_TS_SIG_DEST_MAC_LEN           (6U)
#define LAN80XX_PTP_SIGNATURE_LEN                 (28U)

/**
 * \brief Tx TSFIFO entry signature
 **/
typedef struct {
    phy25g_ts_fifo_sig_mask_t  sig_mask;  /**< valid signature fields */
    u8        msg_type;              /**< PTP message type */
    u8        domain_num;            /**< domain number in PTP message */
    u8        src_port_identity[10]; /**< source port identity in PTP message */
    u16       sequence_id;           /**< PTP message sequence ID */
    u32       dest_ip;               /**< Destination IP */
    u32       src_ip;                /**< Source IP */
    u8        dest_mac[6];           /**< Destination MAC */
    u32       dest_ipv6_addr[4]; /**< IPv6 Address */
    u32       src_ipv6_addr[4]; /**<IPv6 Mask */
} phy25g_ts_fifo_sig_t;


/**
 * \brief PHY timestamp in seconds and nanoseconds (11 bytes Timestamp)
 **/
typedef struct {
    struct {
        uint16_t    high; /**< bits 32-47 of 48-bit second */
        uint32_t    low;  /**< bits 0-31 of 48-bit second */
    } seconds;             /**< 6 bytes second part of Timestamp */
    uint32_t        nanoseconds; /**< 4 bytes nano-sec part of Timestamp */
    uint8_t         subnanoseconds; /**< 1 bytes sub-nano-sec part of Timestamp */
} phy25g_phy_timestamp_t;


/**
 *brief configure TS FIFO frame signature mask.
 * \param dev[IN]                   mepa driver
 * \param port_no [IN]              port number
 * \phy25g_ts_fifo_sig_mask_t[IN]   mask for the frame signature field.
*/
mepa_rc lan80xx_phy_ts_fifo_sig_set(mepa_device_t                    *dev,
                                    const mepa_port_no_t             port_no,
                                    phy25g_ts_engine_t               eng_id,
                                    const phy25g_ts_fifo_sig_mask_t  sig_mask);


phy25g_phy_ts_tc_op_mode_t mepa_to_lan80xx_tc_opmode(mepa_ts_tc_op_mode_t tc_opmode);
mepa_ts_tc_op_mode_t lan80xx_to_mepa_tc_opmode(phy25g_phy_ts_tc_op_mode_t tc_opmode);
mepa_rc lan80xx_ts_reset_priv(mepa_device_t *dev, const mepa_ts_reset_conf_t *const ts_rst_type);
mepa_rc lan80xx_phy_ts_init_conf_get(mepa_device_t *dev, mepa_port_no_t port_no,
                                     mepa_bool_t  *const   port_ts_init_done,
                                     phy25g_phy_ts_init_conf_t         *const conf);



mepa_rc lan80xx_phy_ts_init(const mepa_device_t *dev,
                            const  mepa_port_no_t port_no,
                            const phy25g_phy_ts_init_conf_t  *const conf);

mepa_rc lan80xx_ts_get_1588_version(const mepa_device_t *dev,
                                    const mepa_port_no_t port_no, uint32_t *version);
mepa_rc lan80xx_ts_csr_ptptime_get_priv(mepa_device_t *dev,
                                        const mepa_port_no_t port_no,
                                        phy25g_phy_timestamp_t  *const ts);

mepa_rc lan80xx_ts_csr_ptptime_set_priv( mepa_device_t *dev,
                                         const mepa_port_no_t port_no,
                                         const phy25g_phy_timestamp_t  *const ts);

mepa_rc lan80xx_get_eng_flow_info(u16 in_flow, phy25g_ts_engine_t *eng_id, u16 *eng_flow);

mepa_rc lan80xx_ts_egress_engine_conf_set(mepa_device_t *dev,
                                          const phy25g_ts_engine_t eng_id,
                                          const u16 flow_index,
                                          phy25g_ts_engine_flow_conf_t *const flow_conf);

mepa_rc lan80xx_ts_ingress_engine_conf_set(mepa_device_t *dev,
                                           const phy25g_ts_engine_t eng_id,
                                           const u16 flow_index,
                                           phy25g_ts_engine_flow_conf_t *const flow_conf);

mepa_rc lan80xx_ts_egress_engine_clear(mepa_device_t *dev,
                                       const mepa_port_no_t port_no,
                                       const phy25g_ts_engine_t eng_id);

mepa_rc lan80xx_ts_egress_engine_action_set(mepa_device_t *dev, mepa_port_no_t port_no,
                                            phy25g_ts_engine_t eng_id, const phy25g_ts_engine_action_t *const action_conf);


mepa_rc lan80xx_ts_ingress_engine_action_set(mepa_device_t *dev, mepa_port_no_t port_no,
                                             phy25g_ts_engine_t eng_id, const phy25g_ts_engine_action_t *const action_conf);

mepa_rc lan80xx_phy_ts_fifo_empty_priv(mepa_device_t          *dev,
                                       const mepa_port_no_t   port_no,
                                       mepa_fifo_ts_entry_t   ts_list[],
                                       u32                    *const num,
                                       BOOL                   callback);

mepa_rc lan80xx_phy_ts_fifo_empty (mepa_device_t           *dev,
                                   const mepa_port_no_t    port_no,
                                   mepa_fifo_ts_entry_t    ts_list[],
                                   u32                     *const num,
                                   BOOL                    callback);

mepa_rc lan80xx_ts_tx_clock_conf_get_priv(mepa_device_t *dev,
                                          u16 clock_id, mepa_ts_ptp_clock_conf_t *ptpclock_conf);

mepa_rc lan80xx_ts_rx_clock_conf_get_priv(mepa_device_t *dev,
                                          u16 clock_id, mepa_ts_ptp_clock_conf_t *ptpclock_conf);

mepa_rc lan80xx_ts_egress_engine_conf_get(mepa_device_t  *dev,
                                          const mepa_port_no_t            port_no,
                                          const phy25g_ts_engine_t      eng_id,
                                          phy25g_ts_engine_flow_conf_t  *const flow_conf);

mepa_rc lan80xx_ts_ingress_engine_conf_get(mepa_device_t  *dev,
                                           const mepa_port_no_t            port_no,
                                           const phy25g_ts_engine_t      eng_id,
                                           phy25g_ts_engine_flow_conf_t  *const flow_conf);

mepa_rc lan80xx_rx_classifier_conf_get_priv(mepa_device_t *dev, u16 in_flow,
                                            mepa_ts_classifier_t *const out_conf);


mepa_rc lan80xx_phy_ts_path_delay_set(mepa_device_t *dev,
                                      const mepa_port_no_t  port_no,
                                      const phy25g_timeinterval_t    *const path_delay);

mepa_rc lan80xx_phy_ts_delay_asymmetry_get(const mepa_device_t *dev,
                                           const mepa_port_no_t port_no,
                                           phy25g_timeinterval_t         *const delay_asym);

mepa_rc lan80xx_phy_ts_delay_asymmetry_set(mepa_device_t *dev,
                                           const mepa_port_no_t port_no,
                                           const phy25g_timeinterval_t   *const delay_asym);

mepa_rc lan80xx_phy_ts_path_delay_get(const mepa_device_t *dev,
                                      const mepa_port_no_t  port_no,
                                      phy25g_timeinterval_t          *const path_delay);


mepa_rc lan80xx_phy_ts_clock_rateadj_get(const mepa_device_t  *dev,
                                         const mepa_port_no_t      port_no,
                                         phy25g_ts_scaled_ppb_t  *const adj);


mepa_rc lan80xx_phy_ts_clock_rateadj_set(mepa_device_t  *dev,
                                         const mepa_port_no_t           port_no,
                                         const phy25g_ts_scaled_ppb_t *const adj);


mepa_rc lan80xx_ts_mode_set_priv(mepa_device_t *dev,
                                 const mepa_bool_t   enable);

mepa_rc lan80xx_ts_mode_get_priv( mepa_device_t *dev,
                                  mepa_bool_t      *const enable);

mepa_rc lan80xx_phy_ts_stats_get(mepa_device_t *dev, const mepa_port_no_t  port_no, phy25g_phy_ts_stats_t  *const statistics);

mepa_rc lan80xx_phy_ts_event_enable_set(mepa_device_t *dev, const mepa_port_no_t port_no, const BOOL enable, const mepa_ts_event_t ev_mask);

mepa_rc lan80xx_phy_ts_event_enable_get(mepa_device_t *dev, const mepa_port_no_t port_no, mepa_ts_event_t *const ev_mask);

mepa_rc lan80xx_phy_ts_event_poll(mepa_device_t *dev, const mepa_port_no_t  port_no, mepa_ts_event_t  *const status);

mepa_rc lan80xx_phy_ts_egress_latency_get(const mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_timeinterval_t *const latency);

mepa_rc lan80xx_phy_ts_egress_latency_set(mepa_device_t  *dev, const mepa_port_no_t  port_no, const phy25g_timeinterval_t  *const latency);

mepa_rc lan80xx_phy_ts_ingress_latency_get(const mepa_device_t  *dev, const mepa_port_no_t  port_no, phy25g_timeinterval_t *const latency);

mepa_rc lan80xx_phy_ts_ingress_latency_set(mepa_device_t  *dev, const mepa_port_no_t  port_no, const phy25g_timeinterval_t *const latency);

mepa_rc lan80xx_phy_ts_ltc_ls_action_set(mepa_device_t *dev, const mepa_port_no_t port_no, phy25g_ptp_action_type_t const ls_type);

mepa_rc lan80xx_ptp_reg_dump(mepa_device_t            *dev,
                             const mepa_port_no_t     port_no,
                             const mepa_debug_print_t pr);

mepa_rc lan80xx_ts_tx_classifier_conf_set_priv(struct mepa_device *dev,
                                               uint16_t flow_index,
                                               const mepa_ts_classifier_t *const pkt_class_conf);

mepa_rc lan80xx_tx_classifier_conf_get_priv(mepa_device_t *dev,
                                            u16 in_flow,
                                            mepa_ts_classifier_t *const out_conf);

mepa_rc mepa_to_lan80xx_encap(mepa_ts_pkt_encap_t encap, phy25g_ts_encap_t *phy25g_encap);

mepa_ts_pkt_encap_t lan80xx_to_mepa_encap(phy25g_ts_encap_t phy25g_encap);

uint8_t lan80xx_get_vs_ntw_type(mepa_ts_ip_match_select_t ntw_type);

uint8_t lan80xx_get_vs_addr_type(mepa_ts_mac_match_mode_t mac_match);

uint8_t lan80xx_get_vs_mac_type(mepa_ts_mac_match_select_t mac_type);

mepa_rc lan80xx_ts_rx_classifier_conf_set_priv(struct mepa_device *dev,
                                               uint16_t flow_index,
                                               const mepa_ts_classifier_t *const pkt_class_conf);

mepa_rc lan80xx_ts_tx_clock_conf_set_priv(struct mepa_device *dev,
                                          uint16_t clock_id,
                                          const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

mepa_rc lan80xx_phy_ts_fifo_get(mepa_device_t           *dev,
                                const mepa_port_no_t    port_no,
                                mepa_fifo_ts_entry_t    ts_list[],
                                const size_t            size,
                                uint32_t                *const num);

mepa_rc lan80xx_ts_rx_clock_conf_set_priv(struct mepa_device *dev,
                                          uint16_t clock_id,
                                          const mepa_ts_ptp_clock_conf_t *const ptpclock_conf);

mepa_rc lan80xx_ts_pps_conf_set_priv(mepa_device_t *dev, const mepa_ts_pps_conf_t *const phy_pps_conf);

mepa_rc lan80xx_ts_pps_conf_get_priv(mepa_device_t *dev, mepa_ts_pps_conf_t *const phy_pps_conf);
#endif //_MEPA_LAN80XX_TS_PRIVATE_H_
