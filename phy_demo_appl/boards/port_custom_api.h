// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PORT_CUSTOM_H_
#define _VTSS_PORT_CUSTOM_H_


#include <vtss_api.h>
#include <vtss/api/port.h>

#ifdef __cplusplus
extern "C" {
#endif
/******************************************************************************/
/* Port capabilities                                                          */
/******************************************************************************/
#define PORT_CAP_NONE              0x00000000 /**< No capabilities */
#define PORT_CAP_AUTONEG           0x00000001 /**< Auto negotiation */
#define PORT_CAP_10M_HDX           0x00000002 /**< 10 Mbps, half duplex */
#define PORT_CAP_10M_FDX           0x00000004 /**< 10 Mbps, full duplex */
#define PORT_CAP_100M_HDX          0x00000008 /**< 100 Mbps, half duplex */
#define PORT_CAP_100M_FDX          0x00000010 /**< 100 Mbps, full duplex */
#define PORT_CAP_1G_FDX            0x00000020 /**< 1 Gbps, full duplex */
#define PORT_CAP_2_5G_FDX          0x00000040 /**< 2.5 Gbps, full duplex */
#define PORT_CAP_5G_FDX            0x00000080 /**< 5Gbps, full duplex */
#define PORT_CAP_10G_FDX           0x00000100 /**< 10Gbps, full duplex */
#define PORT_CAP_FLOW_CTRL         0x00001000 /**< Flow control */
#define PORT_CAP_COPPER            0x00002000 /**< Copper media */
#define PORT_CAP_FIBER             0x00004000 /**< Fiber media */
#define PORT_CAP_DUAL_COPPER       0x00008000 /**< Dual media, copper preferred */
#define PORT_CAP_DUAL_FIBER        0x00010000 /**< Dual media, fiber preferred */
#define PORT_CAP_SD_ENABLE         0x00020000 /**< Signal Detect enabled */
#define PORT_CAP_SD_HIGH           0x00040000 /**< Signal Detect active high */
#define PORT_CAP_SD_INTERNAL       0x00080000 /**< Signal Detect select internal */
#define PORT_CAP_XAUI_LANE_FLIP    0x00200000 /**< Flip the XAUI lanes */
#define PORT_CAP_VTSS_10G_PHY      0x00400000 /**< Connected to VTSS 10G PHY */
#define PORT_CAP_SFP_DETECT        0x00800000 /**< Auto detect the SFP module */
#define PORT_CAP_STACKING          0x01000000 /**< Stack port candidate */
#define PORT_CAP_DUAL_SFP_DETECT   0x02000000 /**< Auto detect the SFP module for dual media*/
#define PORT_CAP_SFP_ONLY          0x04000000 /**< SFP only port (not dual media)*/
#define PORT_CAP_SERDES_RX_INVERT  0x10000000 /**< Serdes RX signal is inverted */
#define PORT_CAP_SERDES_TX_INVERT  0x20000000 /**< Serdes TX signal is inverted */
#define PORT_CAP_INT_PHY           0x40000000 /**< Connected to internal PHY */


#define PORT_CAP_HDX (PORT_CAP_10M_HDX | PORT_CAP_100M_HDX) /**< Half duplex */
#define PORT_CAP_TRI_SPEED_FDX (PORT_CAP_AUTONEG | PORT_CAP_1G_FDX | PORT_CAP_100M_FDX | PORT_CAP_10M_FDX | PORT_CAP_FLOW_CTRL) /**< Tri-speed port full duplex only */
#define PORT_CAP_TRI_SPEED (PORT_CAP_TRI_SPEED_FDX | PORT_CAP_HDX) /**< Tri-speed port, both full and half duplex */
#define PORT_CAP_1G_PHY (PORT_CAP_COPPER | PORT_CAP_FIBER | PORT_CAP_DUAL_COPPER | PORT_CAP_DUAL_FIBER) /**< 1G PHY present */

#define PORT_CAP_TRI_SPEED_COPPER            (PORT_CAP_TRI_SPEED | PORT_CAP_COPPER)                                                                          /**< Tri-speed port copper only*/
#define PORT_CAP_TRI_SPEED_FIBER             (PORT_CAP_TRI_SPEED | PORT_CAP_FIBER)                                                                           /**< Tri-speed port fiber only*/
#define PORT_CAP_TRI_SPEED_DUAL_COPPER       (PORT_CAP_TRI_SPEED | PORT_CAP_DUAL_COPPER)                                                                     /**< Tri-speed port both fiber and copper. Copper prefered*/
#define PORT_CAP_TRI_SPEED_DUAL_FIBER        (PORT_CAP_TRI_SPEED | PORT_CAP_DUAL_FIBER)                                                                      /**< Tri-speed port both fiber and copper. Fiber prefered*/
#define PORT_CAP_ANY_FIBER                   (PORT_CAP_FIBER | PORT_CAP_DUAL_FIBER | PORT_CAP_DUAL_COPPER | PORT_CAP_SFP_DETECT) /**< Any fiber mode */
#define PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED       (PORT_CAP_DUAL_FIBER | PORT_CAP_DUAL_COPPER)                             /**< Any fiber mode, but auto detection not supported */
#define PORT_CAP_SPEED_DUAL_ANY_FIBER        (PORT_CAP_DUAL_COPPER | PORT_CAP_DUAL_FIBER| PORT_CAP_DUAL_SFP_DETECT)              /**< Any fiber mode, auto detection supported */
#define PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER    (PORT_CAP_TRI_SPEED | PORT_CAP_SPEED_DUAL_ANY_FIBER)                                                            /**< Copper 5 Fiber mode, auto detection supported */
#define PORT_CAP_TRI_SPEED_DUAL_ANY_FIBER_FIXED_SFP_SPEED    (PORT_CAP_TRI_SPEED | PORT_CAP_SPEED_DUAL_ANY_FIBER_FIXED_SPEED)                                /**< Copper & Fiber mode, but SFP auto detection not supported */
#define PORT_CAP_DUAL_FIBER_1000X                 (PORT_CAP_DUAL_FIBER | PORT_CAP_DUAL_COPPER)                                                                    /**< 1000Base-X fiber mode */

#define PORT_CAP_SFP_1G   (PORT_CAP_AUTONEG | PORT_CAP_100M_FDX | PORT_CAP_1G_FDX | PORT_CAP_FLOW_CTRL | PORT_CAP_SFP_ONLY)                 /**< SFP fiber port 100FX/1G with auto negotiation and flow control */
#define PORT_CAP_SFP_2_5G (PORT_CAP_SFP_1G | PORT_CAP_2_5G_FDX)                                                                                              /**< SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control */
#define PORT_CAP_SFP_SD_HIGH (PORT_CAP_SD_ENABLE | PORT_CAP_SD_HIGH | PORT_CAP_SD_INTERNAL | PORT_CAP_SFP_DETECT | PORT_CAP_SFP_ONLY)                        /**< SFP fiber port 100FX/1G/2.5G with auto negotiation and flow control, signal detect high */ 

#define PORT_CAP_2_5G_TRI_SPEED_FDX     (PORT_CAP_AUTONEG | PORT_CAP_2_5G_FDX | PORT_CAP_1G_FDX | PORT_CAP_100M_FDX | PORT_CAP_FLOW_CTRL) /**< 100M/1G/2.5G Tri-speed port full duplex only */
#define PORT_CAP_2_5G_TRI_SPEED         (PORT_CAP_2_5G_TRI_SPEED_FDX | PORT_CAP_100M_HDX)                                                 /**< 100M/1G/2.5G Tri-speed port, all full duplex and 100M half duplex */
#define PORT_CAP_2_5G_TRI_SPEED_COPPER  (PORT_CAP_2_5G_TRI_SPEED | PORT_CAP_COPPER)                                                        /**< 100M/1G/2.5G Tri-speed port copper only */

typedef u32 port_cap_t; /**< Bit-mask containing the port capabilities */

/******************************************************************************/
/* Port configuration                                                         */
/******************************************************************************/

/** \brief Port configuration */
typedef struct {
    BOOL                  enable;                  /**< Admin enable/disable */
    BOOL                  autoneg;                 /**< Auto negotiation */
    BOOL                  fdx;                     /**< Forced duplex mode */
    BOOL                  flow_control;            /**< Flow control (Standard 802.3x) */
#if defined(VTSS_FEATURE_QOS)
    BOOL                  pfc[VTSS_PRIOS];         /**< Priority Flow control (802.1Qbb)*/
#endif
    vtss_port_speed_t     speed;                   /**< Forced port speed */
    vtss_fiber_port_speed_t dual_media_fiber_speed;/**< Speed for dual media fiber ports*/
    unsigned int          max_length;              /**< Max frame length */
#ifdef VTSS_SW_OPTION_PHY_POWER_CONTROL
    vtss_phy_power_mode_t power_mode;              /**< PHY power mode */
#endif /* VTSS_SW_OPTION_PHY_POWER_CONTROL */
    BOOL                  exc_col_cont;            /**< Excessive collision continuation */
    u16                   adv_dis;                 /**< Auto neg advertisement disable */
    u8                    max_tags;                /**< Maximum number of tags */
    BOOL                  oper_up;                 /**< Force operational state up */
    BOOL                   frame_length_chk;       /**< True to do 802.3 frame length check for ethertypes below 0x0600*/
} port_custom_conf_t;

typedef struct {
    vtss_port_map_t       map;    /* Port map */
    vtss_port_interface_t mac_if; /* MAC interface */
    port_cap_t            cap;    /* Port capabilities */
#ifdef VTSS_SW_OPTION_POE
    // The chip_port and the poe channel number does not necessary match.
    // So far only for PCB120.
    vtss_chip_no_t         poe_port;      /**< Chip port number */
    BOOL                   poe_support;   /**< PoE support for this port */
#endif
} port_custom_entry_t;

typedef struct {
    BOOL  tx_fault;    /* TxFault */
    BOOL  los;         /* Loss Of Signal  */
    BOOL  present;     /* SFP module present  */
} port_custom_sfp_status_t;

/* Set after board probing */
extern const port_custom_entry_t *port_custom_table;

/* Disable advertisement during auto negotiation */
#define PORT_ADV_DIS_HDX  0x01
#define PORT_ADV_DIS_FDX  0x02
#define PORT_ADV_DIS_2500M_FDX 0x08
#define PORT_ADV_DIS_1G_FDX   0x10
#define PORT_ADV_UP_MEP_LOOP  0x20
#define PORT_ADV_DIS_100M     0x40 /* Disable 100Mbit mode*/
#define PORT_ADV_DIS_10M      0x80 /* Disable 10Mbit mode*/
#define PORT_ADV_DIS_SPEED    (PORT_ADV_DIS_10M | PORT_ADV_DIS_100M | PORT_ADV_DIS_1G_FDX | PORT_ADV_DIS_2500M_FDX) /* All speed bits */
#define PORT_ADV_DIS_DUPLEX   (PORT_ADV_DIS_HDX | PORT_ADV_DIS_FDX) /* All duplex bits*/

/* Maximum number of tags */
#define PORT_MAX_TAGS_ONE  0 /* Backward compatible default is one tag */
#define PORT_MAX_TAGS_NONE 1
#define PORT_MAX_TAGS_TWO  2

/* The default power mode value */
#define CONF_POWER_MODE_DEFAULT VTSS_PHY_POWER_NOMINAL

/* Initialize board */
void port_custom_init(void);

/* Release ports from reset */
vtss_rc port_custom_reset(void);


/* Post ports reset */
vtss_rc post_port_custom_reset(void);

/* Initialize port LEDs */
vtss_rc port_custom_led_init(void);

#if defined(VTSS_FEATURE_FAN)
/***************************************************************************
 * Fan
 ***************************************************************************/
vtss_rc port_custom_fan_init(vtss_fan_conf_t fan_spec);
#endif /* VTSS_FEATURE_FAN */

/***************************************************************************
 * Temperature sensors
 ***************************************************************************/

/* Initialize temperature sensors */
vtss_rc port_custom_temp_sensors_init(void);

/* Get temperature sensors readings*/
vtss_rc port_custom_temp_sensors_get(vtss_port_no_t iport, i16 * temp);

/* Get number of temperature sensors on the board*/
u8 port_custom_temp_sensors_cnt(void);

/* Update port LED */
vtss_rc port_custom_led_update(vtss_port_no_t port_no,
                               vtss_port_status_t *status,
                               vtss_port_counters_t *counters,
                               port_custom_conf_t *port_conf);

/* Set LED intensity */
vtss_rc port_custom_led_intensity_set(vtss_phy_led_intensity intensity);

// Function for doing special port configuration that depends upon the platform
// Forexample do the enzo board requires that if the stack ports uses SFPs, the SFPs must be turn on
// using a special serialised GPIO system.
void port_custom_conf(vtss_port_no_t port,
                      port_custom_conf_t *port_conf);

/* Called when system is reset. */
void port_custom_pre_reset(void);

/* Functions for handling SFP modules */
vtss_rc board_sfp_i2c_read(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, u8 cnt, BOOL word_access);
vtss_rc board_sfp_i2c_write(vtss_port_no_t port_no, u8 i2c_addr, u8 addr, u8 *const data, BOOL word_access);
vtss_rc port_custom_sfp_mod_detect(BOOL *detect_status);
vtss_rc port_custom_sfp_status(port_custom_sfp_status_t *status); // Gets sfp present, los and tx_fault signals

typedef enum {
    VTSS_BOARD_UNKNOWN = 0,
    VTSS_BOARD_LUTON10_REF = 4 /* Don't change. 1-3 are obsolete */,
    VTSS_BOARD_LUTON26_REF,
    VTSS_BOARD_JAG_CU24_REF,
    VTSS_BOARD_JAG_SFP24_REF,
    VTSS_BOARD_JAG_PCB107_REF,
    VTSS_BOARD_JAG_CU48_REF = 10 /* Don't change. 9 is obsolete */,
    VTSS_BOARD_SERVAL_REF,
    VTSS_BOARD_SERVAL_PCB106_REF,
    VTSS_BOARD_SERVAL2_NID_REF = 14 /* Don't change. 13 is obsolete */,
    VTSS_BOARD_JAGUAR2_CU48_REF,
    VTSS_BOARD_JAGUAR2_REF,
    VTSS_BOARD_JAGUAR2_AQR_REF,
    VTSS_BOARD_SERVALT_NID_REF,
    VTSS_BOARD_RIO_GRANDE_4T1T_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_4T1T,
    VTSS_BOARD_RIO_GRANDE_6T2T_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_6T2T,
    VTSS_BOARD_RIO_GRANDE_4P2S_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_4P2S,
    VTSS_BOARD_RIO_GRANDE_8P2S_A,  /* Proto-A, HW_ID=0 */
    VTSS_BOARD_RIO_GRANDE_8P2S,
    VTSS_BOARD_OCELOT_REF = 28 /* Don't change. 27 is obsolete */, // PCB120
    VTSS_BOARD_OCELOT_PCB123_REF,                                  // PCB123
} vtss_board_type_t;

enum vtss_board_feature_e {
    VTSS_BOARD_FEATURE_AMS           = (1 << 0), /**< TBD */
    VTSS_BOARD_FEATURE_LOS           = (1 << 1), /**< Loss of Signal detect */
    VTSS_BOARD_FEATURE_POE           = (1 << 2), /**< Power Over Ethernet */
    VTSS_BOARD_FEATURE_VCXO          = (1 << 3), /**< Voltage-controlled oscillator */
    VTSS_BOARD_FEATURE_STACKING      = (1 << 4), /**< Stacking support */
    VTSS_BOARD_FEATURE_ANEG_COMPLETE = (1 << 5), /**< PHY autoneg complete interrupt */
    VTSS_BOARD_FEATURE_1588_CLK_ADJ_DAC = (1 << 6), /**< AD5667 DAC used to Adjust the 1588 ref clock */
    VTSS_BOARD_FEATURE_1588_REF_CLK_SEL = (1 << 7), /**< Set 1588 ref clock to different frequencies */
};

/* Board information for exchanging data between application and probe function */
typedef struct {
    int                      board_type;   /* Board type */
    vtss_target_type_t       target;       /* Target ID */
    u32                      port_count;   /* Number of ports */
    vtss_reg_read_t          reg_read;     /* Register read function */
    vtss_reg_write_t         reg_write;    /* Register write function */
    vtss_i2c_read_t          i2c_read;     /**< I2C read function */
    vtss_i2c_write_t         i2c_write;    /**< I2C write function */
    vtss_rc                  (*board_conf_get)(const char *tag, char *buf, size_t bufsize, size_t *buflen); /**< Read board config */
} vtss_board_info_t;

int vtss_board_probe(vtss_board_info_t *board_info, const port_custom_entry_t **port_custom_table);

const char *vtss_board_name(void);

vtss_board_type_t vtss_board_type(void);

#if defined(VTSS_ARCH_JAGUAR_2)
vtss_port_mux_mode_t vtss_port_mux_mode(void);
#endif /* VTSS_ARCH_JAGUAR_2 */

u32 vtss_board_features(void);

u32 vtss_board_chipcount(void);

#if defined(VTSS_FEATURE_VSTAX)
u32 vtss_board_default_stackport(BOOL port_0);
#endif  /* VTSS_FEATURE_VSTAX */

port_cap_t vtss_board_port_cap(int board_type, vtss_port_no_t port_no);

void led_tower_update(void);

#ifdef __cplusplus
}
#endif

#endif /* _VTSS_PORT_CUSTOM_H_ */

/****************************************************************************/
/*                                                                          */
/*  End of file.                                                            */
/*                                                                          */
/****************************************************************************/
