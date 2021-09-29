// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_PHY_H_
#define _VTSS_PHY_H_

#include "vtss_phy_veriphy.h"


/* PHY family */
typedef enum {
    VTSS_PHY_FAMILY_NONE,     /* Unknown */
    VTSS_PHY_FAMILY_MUSTANG,  /* VSC8201 */
    VTSS_PHY_FAMILY_BLAZER,   /* VSC8204 */
    VTSS_PHY_FAMILY_COBRA,    /* VSC8211/21 */
    VTSS_PHY_FAMILY_QUATTRO,  /* VSC8224/34/44 */
    VTSS_PHY_FAMILY_SPYDER,   /* VSC8538/58/8658 */
    VTSS_PHY_FAMILY_COOPER,   /* VSC8601/41 */
    VTSS_PHY_FAMILY_LUTON,    /* VSC7385/88 */
    VTSS_PHY_FAMILY_LUTON24,  /* VSC7389/90/91 */
    VTSS_PHY_FAMILY_LUTON_E,  /* VSC7395/96/98 */
    VTSS_PHY_FAMILY_INTRIGUE, /* VSC7500-7507 */
    VTSS_PHY_FAMILY_ENZO,     /* VSC8634/64 */
    VTSS_PHY_FAMILY_ATOM,     /* VSC8512/8522 */
    VTSS_PHY_FAMILY_LUTON26,  /* VSC7420*/
    VTSS_PHY_FAMILY_TESLA,    /* VSC8574*/
    VTSS_PHY_FAMILY_VIPER,    /* VSC8582, VSC8584, VSC8575, VSC8564, VSC8586*/
    VTSS_PHY_FAMILY_ELISE,    /* VSC8514*/
    VTSS_PHY_FAMILY_NANO,     /* VSC8502, VSC8501 */
} vtss_phy_family_t;

// Macro to determine if all base ports are found
#define VTSS_PHY_BASE_PORTS_FOUND vtss_state->phy_inst_state.base_ports_found ? VTSS_RC_OK : VTSS_RC_ERR_PHY_BASE_NO_NOT_FOUND

/* Define revision for the different chips. */
#define VTSS_PHY_ATOM_REV_A 0
#define VTSS_PHY_ATOM_REV_B 1
#define VTSS_PHY_ATOM_REV_C 2
#define VTSS_PHY_ATOM_REV_D 3

// Tesla family
#define VTSS_PHY_TESLA_REV_A 0
#define VTSS_PHY_TESLA_REV_B 1
#define VTSS_PHY_TESLA_REV_D 2
#define VTSS_PHY_TESLA_REV_E 3


// Viper family
#define VTSS_PHY_VIPER_REV_A 0
#define VTSS_PHY_VIPER_REV_B 1
// Elise family
#define VTSS_PHY_ELISE_REV_A 0

// Nano family
#define VTSS_PHY_NANO_REV_A  1

#define VTSS_PHY_EPG_SRC_ADDR    (0x2)
#define VTSS_PHY_EPG_DST_ADDR    (0x1)
#define VTSS_PHY_TR_ADDR_WR      (0x8000)
#define VTSS_PHY_TR_ADDR_RD      (0xA000)
#define VTSS_PHY_TR_EPG_ADDR     (0x0CC0)
#define VTSS_PHY_TR_EPG_ADDR_WR  (VTSS_PHY_TR_ADDR_WR | VTSS_PHY_TR_EPG_ADDR)
#define VTSS_PHY_TR_EPG_ADDR_RD  (VTSS_PHY_TR_ADDR_RD | VTSS_PHY_TR_EPG_ADDR)


typedef enum {
    VTSS_CAP_INT       = (1 << 0),    /* Interrupts Suported*/
    VTSS_CAP_EEE       = (1 << 1),    /* EEE Supported */
    VTSS_CAP_MACSEC    = (1 << 2),    /* MACSEC Supported */
    VTSS_CAP_WOL       = (1 << 3),    /* Wake On LAN supported */
    VTSS_CAP_INT_FIFO  = (1 << 4),    /* FIFO TX and RX Interrupts supported on Std Pg Reg 25/26 */
    VTSS_CAP_INT_EXT   = (1 << 5),    /* Extended Interrupt Registers supported */
    VTSS_CAP_SOF_TS    = (1 << 6),    /* NI Added: SOF timestamping */
} vtss_phy_feature_t;

/* Global PHY state per instance */
#define VTSS_PHY_INST_STATE_MAX_COEFF   (12)
typedef struct {
    short maxAbsCoeff;
    short coeff[VTSS_PHY_INST_STATE_MAX_COEFF];  /*- temporary storage for 12 EC/NC coefficients */

    BOOL  base_ports_found;        /* Used for internal in the PHY api to signal that base port is found for all ports. */
    BOOL  at_least_one_fiber_port; /* Signaling that at least at_one port in the system is a fiber port */
} vtss_phy_inst_state_t;

/* Power configuration */
typedef struct {
    BOOL vtss_phy_power_dynamic;
    BOOL vtss_phy_actiphy_on;
    u32  pwrusage;
} vtss_phy_power_t;

typedef struct {
    vtss_phy_clock_conf_t  conf;
    vtss_port_no_t         source;
} phy_clock_conf_t;

typedef enum {
    VTSS_SERDES_LB_NONE = 0,
    VTSS_SERDES_LB_PAD = 1,
    VTSS_SERDES_LB_INPUT = 2,
    VTSS_SERDES_LB_FACILITY = 4,
    VTSS_SERDES_LB_EQUIPMENT = 8,
} serdes_lpback_types_t;

#define VTSS_FORCED_LONG_LINKUP_COUNTER_WINDOW   (3)  /* Max Offset Part of Work-Around for Long Linkup Time in Forced Mode */

typedef struct _vtss_phy_port_state_info_t {
    vtss_phy_reset_conf_t  reset;      /* Reset setup */
    vtss_phy_family_t      family;     /* Family */
    vtss_phy_type_t        type;       /* Type */
    u16                    features;   /* Features supported */
    vtss_phy_conf_t        setup;      /* Setup */
    vtss_port_status_t     status;     /* Status */
    vtss_phy_power_t       power;      /* Power Reduction Setup */
    vtss_phy_eee_conf_t    eee_conf;   /* EEE configuration.  */
    vtss_phy_wol_conf_t    wol_conf;   /* WoL configuration.  */
    vtss_phy_power_conf_t  conf_power;
    vtss_phy_conf_1g_t     conf_1g;    /* 1g setup */
    vtss_phy_status_1g_t   status_1g;  /* 1G Status */
    vtss_phy_ring_resiliency_conf_t rslnt_conf;  /* ring resiliency conf */
#if VTSS_PHY_OPT_VERIPHY
    vtss_veriphy_task_t    veriphy;  /* VeriPHY task */
#endif /* VTSS_PHY_OPT_VERIPHY */
    BOOL                   ena_forced_1000_mode_prev;  /* Signaling that someone set 17E2.5, Setting for Forced-1000BaseT Enable */
    BOOL                   ena_forced_1000_mode_curr;  /* Signaling that someone set 17E2.5, Setting for Forced-1000BaseT Enable */
    vtss_phy_loopback_t    loopback; // Loop back
    serdes_lpback_types_t  prev_mac_serdes_lpback;
    serdes_lpback_types_t  prev_media_serdes_lpback;
    BOOL                   cu_sfp_config_complete;
    BOOL                   conf_none; // Signaling the no PHY is found for this port
    vtss_phy_event_t       ev_mask;    // 32-bit Mask for interrupt events (Reg25) and Ext Int Reg28E2)
    u16                    int_mask_reg;  // Mirror of the interrupt mask register
    u16                    ext_int_mask_reg;  // Mirror of the Extended Interrupt mask register
    phy_clock_conf_t       clock_conf[VTSS_PHY_RECOV_CLK_NUM];
    BOOL                   link_down_due_to_port_reset;
    vtss_port_interface_t  mac_if_old;
    BOOL                   veriphy_running;
    u8                     last_temp_reading;
    BOOL                   dce_port_init_done;
    u16                    SaveMediaSelect; // Used by veriPHY
    u16                    micro_patch_crc; // The chip with this port has a micropatch (Internal 8051 CPU program) with this CRC. It is only set for the base port.

    // Some registers requires that the phy port is reset before a new configure if applied, but during warm start we don't want to reset the phy port (giving traffic loss) if the registers in fact haven't changed. In order to determine if registers have changed during warm start we use this global variable to signal that registers have in fact changed.
    BOOL                   warm_start_reg_changed;
    u16                    mac_block_mtu; /* MAC Block MTU  */
    u16                    forced_long_linkup_counter;    /* Delay for Forced Mode Work-Around for Forced Mode Long Linkup Time issue  */
} vtss_phy_port_state_t;

#define MAX_REGISTERS_PER_PAGE  32
/** \brief Phy type information */
typedef struct {
    u16             phy_port;                              /**< Phy Port number */
    u16             page;                                  /**< Page          */
    char            page_code[4];                          /**< Page Code     */
    u16             reg[MAX_REGISTERS_PER_PAGE];           /**< Chip Regsister number */
    u16             reg_value[MAX_REGISTERS_PER_PAGE];     /**< The Register Value read from the chip */
} vtss_phy_page_reg_dump_t;

//=============================================================================
// 6G Macro debug
//=============================================================================
typedef enum {
    /* MEMITGR - Controlled on Per Port Basis: */
    VTSS_PHY_SERDES_1G_CSR_REG_MEMITGR_START = 0x00,
    VTSS_PHY_SERDES_1G_CSR_REG_MEMITGR_STOP = 0x05,
    /* PLL5G  - Controlled on Per Port Basis: */
    VTSS_PHY_SERDES_1G_CSR_REG_PLL5G_START = 0x06,
    VTSS_PHY_SERDES_1G_CSR_REG_PLL5G_STOP = 0x0d,
    /* MAC SIDE - 1G SERDES  - Controlled on Per Port Basis: */
    VTSS_PHY_SERDES_1G_CSR_REG_SERDES_START = 0x0e,
    VTSS_PHY_SERDES_1G_CSR_REG_SERDES_STOP = 0x1f,
    /* 6G SERDES - Controlled on Per PHY Basis */
    VTSS_PHY_SERDES_6G_CSR_REG_SERDES_START = 0x21,
    VTSS_PHY_SERDES_6G_CSR_REG_SERDES_STOP = 0x3f,
    VTSS_PHY_SERDES_6G_CSR_REG_MAX = 0x3f
} vtss_phy_csr_reg_t;

typedef enum {
    VTSS_PHY_CHAN_A = 0,
    VTSS_PHY_CHAN_B = 1,
    VTSS_PHY_CHAN_C = 2,
    VTSS_PHY_CHAN_D = 3,
} vtss_phy_channel_t;


//=============================================================================
// Start of Function Prototypes
//=============================================================================

vtss_rc vtss_phy_1g_init_conf_set(struct vtss_state_s *vtss_state);
vtss_rc vtss_phy_restart_conf_set(struct vtss_state_s *vtss_state);

vtss_rc vtss_phy_status_get_private(struct vtss_state_s *vtss_state,
                                    const vtss_port_no_t port_no,
                                    vtss_port_status_t   *const status);


vtss_rc vtss_phy_chip_temp_get_private (struct vtss_state_s *vtss_state,
                                        const vtss_port_no_t  port_no,
                                        i16                    *const temp);

vtss_rc vtss_phy_chip_temp_init_private(struct vtss_state_s *vtss_state,
                                        const vtss_port_no_t  port_no);


vtss_rc vtss_phy_rd(struct vtss_state_s *vtss_state,
                    const vtss_port_no_t port_no,
                    const u32            addr,
                    u16                  *const value);

vtss_rc vtss_phy_wr(struct vtss_state_s *vtss_state,
                    const vtss_port_no_t port_no,
                    const u32            addr,
                    const u16            value);

vtss_rc vtss_phy_wr_masked(struct vtss_state_s *vtss_state,
                           const vtss_port_no_t port_no,
                           const u32            addr,
                           const u16            value,
                           const u16            mask);

/* Write PHY register, masked (including the page) */
vtss_rc vtss_phy_wr_masked_page(struct vtss_state_s *vtss_state,
                                const vtss_port_no_t port_no,
                                const u16            page,
                                const u32            addr,
                                const u16            value,
                                const u16            mask,
                                const u16            line);

/* Read PHY register (including the page) */
vtss_rc vtss_phy_rd_page(struct vtss_state_s *vtss_state,
                         const vtss_port_no_t port_no,
                         const u16            page,
                         const u32            addr,
                         u16                  *const value,
                         const u16            line);

/* Write PHY register (including the page) */
vtss_rc vtss_phy_wr_page(struct vtss_state_s *vtss_state,
                         const vtss_port_no_t port_no,
                         const u16            page,
                         const u32            addr,
                         const u16            value,
                         const u16            line);


#define PHY_WR_PAGE(vtss_state, port_no, page_addr, value) vtss_phy_wr_page(vtss_state, port_no, page_addr, value, __LINE__)
#define PHY_WR_MASKED_PAGE(vtss_state, port_no, page_addr, value, mask) vtss_phy_wr_masked_page(vtss_state, port_no, page_addr, value, mask, __LINE__)
#define PHY_RD_PAGE(vtss_state, port_no, page_addr, value) vtss_phy_rd_page(vtss_state, port_no, page_addr, value, __LINE__)

vtss_rc vtss_phy_page_std(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_ext(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_ext2(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_ext3(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_ext4(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_gpio(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_1588(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_macsec(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_test(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_tr(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);
vtss_rc vtss_phy_page_0x2daf(struct vtss_state_s *vtss_state, vtss_port_no_t port_no);

vtss_rc vtss_phy_reset_private(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);
vtss_rc vtss_phy_sync(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

vtss_rc vtss_phy_1g_debug_info_print(struct vtss_state_s *vtss_state,
                                     const vtss_debug_printf_t pr,
                                     const vtss_debug_info_t   *const info,
                                     const BOOL                ail,
                                     const BOOL                ignore_group_enabled,
                                     const BOOL                print_hdr);
BOOL  vtss_phy_veriphy_running(struct vtss_state_s *vtss_state,
                               vtss_port_no_t port_no, BOOL set, u8 running);
vtss_rc vtss_atom_patch_suspend(struct vtss_state_s *vtss_state, vtss_port_no_t iport, BOOL suspend);
vtss_rc vtss_phy_micro_assert_reset(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no);

// Same as vtss_phy_1588_csr_wr defined in vtss_phy_api.h, but this function can be called within the API it-selves
vtss_rc vtss_phy_1588_csr_wr_private(struct vtss_state_s *vtss_state,
                                     const vtss_port_no_t port_no,
                                     const u16            target,
                                     const u32            csr_reg_addr,
                                     const u32            value);

// Same as vtss_phy_1588_csr_rd defined in vtss_phy_api.h, but this function can be called within the API it-selves
vtss_rc vtss_phy_1588_csr_rd_private(struct vtss_state_s  *vtss_state,
                                     const vtss_port_no_t port_no,
                                     const u16            target,
                                     const u32            csr_reg_addr,
                                     u32                  *value);

// Same as vtss_phy_macsec_csr_wr defined in vtss_phy_api.h, but this function can be called within the API it-selves
vtss_rc vtss_phy_macsec_csr_wr_private(struct vtss_state_s *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            target,
                                       const u32            csr_reg_addr,
                                       const u32            value);

// Same as vtss_phy_1588_csr_rd defined in vtss_phy_api.h, but this function can be called within the API it-selves
vtss_rc vtss_phy_macsec_csr_rd_private(struct vtss_state_s  *vtss_state,
                                       const vtss_port_no_t port_no,
                                       const u16            target,
                                       const u32            csr_reg_addr,
                                       u32                  *value);

vtss_rc vtss_phy_macsec_csr_rd_64_private(struct vtss_state_s  *vtss_state,
                                          const vtss_port_no_t port_no,
                                          const u16            target,
                                          const u32            csr_reg_addr,
                                          u64                  *value);

BOOL vtss_phy_can(struct vtss_state_s *vtss_state, const vtss_port_no_t port_no, vtss_phy_feature_t feature);

typedef struct {
    i8 reg;
    i8 bit;
} gpio_table_t;

//
// *********** Registers *************
//

// Function for setting a bit in a vector.
#define VTSS_PHY_BIT(bit)       (1U << (bit))

// Set x bits to 1. E.g x=3 -> b111 (0x7)
#define VTSS_PHY_BITMASK(x)               ((1U << (x)) - 1)

#define VTSS_PHY_EXTRACT_BITFIELD(value, offset, width)  (((value) >> (offset)) & VTSS_PHY_BITMASK(width))
#define VTSS_PHY_ENCODE_BITFIELD(value, offset, width)   (((value) & VTSS_PHY_BITMASK(width)) << (offset))
#define VTSS_PHY_ENCODE_BITMASK(offset, width)      (VTSS_PHY_BITMASK(width) << (offset))

// ** Register definitions - Standard page **

// Register 0 + Bit fields
#define  VTSS_PHY_MODE_CONTROL VTSS_PHY_PAGE_STANDARD, 0
#define  VTSS_F_PHY_MODE_CONTROL_SW_RESET         VTSS_PHY_BIT(15)
#define  VTSS_F_PHY_MODE_CONTROL_LOOP             VTSS_PHY_BIT(14)
#define  VTSS_F_PHY_MODE_CONTROL_AUTO_NEG_ENA     VTSS_PHY_BIT(12)
#define  VTSS_F_PHY_MODE_CONTROL_POWER_DOWN       VTSS_PHY_BIT(11)
#define  VTSS_F_PHY_MODE_CONTROL_ISOLATE          VTSS_PHY_BIT(10)
#define  VTSS_F_PHY_MODE_CONTROL_RESTART_AUTO_NEG VTSS_PHY_BIT(9)
#define  VTSS_F_PHY_MODE_CONTROL_UNIDIRECTIONAL   VTSS_PHY_BIT(5)


// Register 1 + Bit fields
#define  VTSS_PHY_MODE_STATUS VTSS_PHY_PAGE_STANDARD, 1
#define  VTSS_F_PHY_UNIDIRECTIONAL_ABILITY        VTSS_PHY_BIT(7)
#define  VTSS_F_PHY_STATUS_LINK_STATUS            VTSS_PHY_BIT(2)

// Register 2 + Bit fields
#define  VTSS_PHY_IDENTIFIER_1 VTSS_PHY_PAGE_STANDARD, 2

// Register 3 + Bit fields
#define  VTSS_PHY_IDENTIFIER_2 VTSS_PHY_PAGE_STANDARD, 3


// Register 4 + Bit fields
#define  VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT VTSS_PHY_PAGE_STANDARD, 4
#define VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_100BASETX_FDX VTSS_PHY_BIT(8)
#define VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_100BASETX_HDX VTSS_PHY_BIT(7)
#define VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_10BASET_FDX   VTSS_PHY_BIT(6)
#define VTSS_PHY_DEVICE_AUTONEG_ADVERTISEMENT_10BASET_HDX   VTSS_PHY_BIT(5)

// Register 5 + Bit fields
#define  VTSS_PHY_AUTONEGOTIATION_LINK_PARTNER_ABILITY VTSS_PHY_PAGE_STANDARD, 5

// Register 9 + Bit fields
#define VTSS_PHY_1000BASE_T_CONTROL  VTSS_PHY_PAGE_STANDARD, 9
#define VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_FDX_CAPABILITY VTSS_PHY_BIT(9)
#define VTSS_PHY_1000BASE_T_CONTROL_1000BASE_T_HDX_CAPABILITY VTSS_PHY_BIT(8)

//Register 10 + Bit fields
#define VTSS_PHY_1000BASE_T_STATUS VTSS_PHY_PAGE_STANDARD, 10

//Register 13 + Bit fields
#define VTSS_PHY_MMD_EEE_ACCESS VTSS_PHY_PAGE_STANDARD, 13

//Register 14 + Bit fields
#define VTSS_PHY_MMD_ADDR_OR_DATA VTSS_PHY_PAGE_STANDARD, 14

// Register 18 + Bit fields
#define VTSS_PHY_BYPASS_CONTROL VTSS_PHY_PAGE_STANDARD, 18
#define VTSS_F_PHY_BYPASS_CONTROL_HP_AUTO_MDIX_AT_FORCE VTSS_PHY_BIT(7)
#define VTSS_F_PHY_BYPASS_CONTROL_DISABLE_PARI_SWAP_CORRECTION VTSS_PHY_BIT(5)

// Register 19 + Bit fields
#define VTSS_PHY_ERROR_COUNTER_1 VTSS_PHY_PAGE_STANDARD, 19
#define VTSS_M_PHY_ERROR_COUNTER_1_100_1000BASETX_RX_ERR_CNT  VTSS_PHY_ENCODE_BITMASK(0, 7)

// Register 20 + Bit fields
#define VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_20 VTSS_PHY_PAGE_STANDARD, 20
#define VTSS_M_PHY_ERROR_COUNTER_2_100_1000FALSE_CARRIER_ERR_CNT  VTSS_PHY_ENCODE_BITMASK(0, 7)

// Register 21 + Bit fields
#define VTSS_PHY_ERROR_COUNTER_3 VTSS_PHY_PAGE_STANDARD, 21
#define VTSS_M_PHY_ERROR_COUNTER_3_CU_MEDIA_LINK_DISCONN_ERR_CNT  VTSS_PHY_ENCODE_BITMASK(0, 7)

// Register 22 + Bit fields
#define VTSS_PHY_EXTENDED_CONTROL_AND_STATUS VTSS_PHY_PAGE_STANDARD, 22
#define VTSS_PHY_EXTENDED_CONTROL_AND_STATUS_FORCE_10BASE_T_HIGH VTSS_PHY_BIT(15)

// Register 23 + Bit fields
#define  VTSS_PHY_EXTENDED_PHY_CONTROL VTSS_PHY_PAGE_STANDARD, 23
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_RXCLK_BUG_15388        VTSS_PHY_BIT(13)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_MAC_INTERFACE_MODE     VTSS_PHY_BIT(12)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE(value) VTSS_PHY_ENCODE_BITFIELD(value, 8, 3)
#define  VTSS_M_PHY_EXTENDED_PHY_CONTROL_MEDIA_OPERATING_MODE   VTSS_PHY_ENCODE_BITMASK(8,3)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_PREFERENCE         VTSS_PHY_BIT(11)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_ENABLED            VTSS_PHY_BIT(10)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE(value)    VTSS_PHY_ENCODE_BITFIELD(value, 6, 2)
#define  VTSS_M_PHY_EXTENDED_PHY_CONTROL_AMS_OVERRIDE           VTSS_PHY_ENCODE_BITMASK(6,2)
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_FAR_END_LOOPBACK_MODE  VTSS_PHY_BIT(3)

// Register 24 + Bit fields
#define  VTSS_PHY_EXTENDED_PHY_CONTROL_2 VTSS_PHY_PAGE_STANDARD, 24
#define  VTSS_F_PHY_EXTENDED_PHY_CONTROL_2_CONNECTOR_LOOPBACK_MODE  VTSS_PHY_BIT(0)


// Register 25 + Bit fields
#define VTSS_PHY_INTERRUPT_MASK    VTSS_PHY_PAGE_STANDARD, 25

#define VTSS_F_PHY_INTERRUPT_MASK_INT_MASK                     VTSS_PHY_BIT(15)
#define VTSS_F_PHY_INTERRUPT_MASK_SPEED_STATE_CHANGE_MASK      VTSS_PHY_BIT(14)
#define VTSS_F_PHY_INTERRUPT_MASK_LINK_MASK                    VTSS_PHY_BIT(13)
#define VTSS_F_PHY_INTERRUPT_MASK_FDX_STATE_CHANGE_MASK        VTSS_PHY_BIT(12)
#define VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_ERROR_MASK          VTSS_PHY_BIT(11)
#define VTSS_F_PHY_INTERRUPT_MASK_AUTO_NEG_COMPLETE_MASK       VTSS_PHY_BIT(10)
#define VTSS_F_PHY_INTERRUPT_MASK_INLINE_POW_DEV_DETECT_MASK   VTSS_PHY_BIT(9)
#define VTSS_F_PHY_INTERRUPT_MASK_SYMBOL_ERR_INT_MASK          VTSS_PHY_BIT(8)
#define VTSS_F_PHY_INTERRUPT_MASK_FAST_LINK_MASK               VTSS_PHY_BIT(7)
#define VTSS_F_PHY_INTERRUPT_MASK_WAKE_ON_LAN_MASK             VTSS_PHY_BIT(6)
#define VTSS_F_PHY_INTERRUPT_MASK_TX_FIFO_OVERFLOW_INT_MASK    VTSS_PHY_BIT(6)
#define VTSS_F_PHY_INTERRUPT_MASK_RX_FIFO_OVERFLOW_INT_MASK    VTSS_PHY_BIT(5)
#define VTSS_F_PHY_INTERRUPT_MASK_EXTENDED_INT_MASK            VTSS_PHY_BIT(5)
#define VTSS_F_PHY_INTERRUPT_MASK_AMS_MEDIA_CHANGE_MASK        VTSS_PHY_BIT(4)
#define VTSS_F_PHY_INTERRUPT_MASK_FALSE_CARRIER_INT_MASK       VTSS_PHY_BIT(3)
#define VTSS_F_PHY_INTERRUPT_MASK_LINK_SPEED_DS_DETECT_MASK    VTSS_PHY_BIT(2)
#define VTSS_F_PHY_INTERRUPT_MASK_MASTER_SLAVE_RES_ERR_MASK    VTSS_PHY_BIT(1)
#define VTSS_F_PHY_INTERRUPT_MASK_RX_ER_INT_MASK               VTSS_PHY_BIT(0)

// Register 26 + Bit fields
#define VTSS_PHY_INTERRUPT_STATUS   VTSS_PHY_PAGE_STANDARD, 26

// Register 27 + Bit fields
#define VTSS_PHY_STD_27 VTSS_PHY_PAGE_STANDARD, 27
#define VTSS_PHY_COBRA_LED_MODE_SELECT VTSS_PHY_PAGE_STANDARD, 27

// Register 28 + Bit fields
#define COOPER_VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS   VTSS_PHY_PAGE_STANDARD, 23
#define VTSS_PHY_AUXILIARY_CONTROL_AND_STATUS   VTSS_PHY_PAGE_STANDARD, 28
#define VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ANEG_COMPLETE                     VTSS_PHY_BIT(15)
#define VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ANEG_DISABLED                     VTSS_PHY_BIT(14)
#define VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_HP_AUTO_MDIX_CROSSOVER_INDICATION VTSS_PHY_BIT(13)
#define VTSS_F_PHY_AUXILIARY_CONTROL_AND_STATUS_ACTIPHY_MODE_ENABLE               VTSS_PHY_BIT(6)

// Register 29 + Bit fields
#define VTSS_PHY_LED_MODE_SELECT VTSS_PHY_PAGE_STANDARD, 29


// Register 30 + Bit fields
#define VTSS_PHY_LED_BEHAVIOR  VTSS_PHY_PAGE_STANDARD, 30
#define VTSS_F_PHY_LED_BEHAVIOR_LED_PULSING_ENABLE     VTSS_PHY_BIT(12)

//Register 31
#define VTSS_PHY_PAGE    VTSS_PHY_PAGE_STANDARD, 31

// ** Register definitions -  EXT1 page**

// Register 17E1 + Bit fields
#define VTSS_PHY_REG_17E VTSS_PHY_PAGE_EXTENDED, 17

// Register 18E1 + Bit fields
#define VTSS_PHY_CU_MEDIA_CRC_GOOD_COUNTER VTSS_PHY_PAGE_EXTENDED, 18
#define VTSS_F_PHY_CU_MEDIA_CRC_GOOD_COUNTER_PACKET_SINCE_LAST_READ  VTSS_PHY_ENCODE_BITMASK(15, 1)
#define VTSS_M_PHY_CU_MEDIA_CRC_GOOD_COUNTER_CONTENTS  VTSS_PHY_ENCODE_BITMASK(0, 14)

// Register 19E1 + Bit fields
#define VTSS_PHY_EXTENDED_MODE_CONTROL VTSS_PHY_PAGE_EXTENDED, 19
#define VTSS_M_PHY_EXTENDED_MODE_CONTROL_FORCE_MDI_CROSSOVER  VTSS_PHY_ENCODE_BITMASK(2, 2)
#define VTSS_F_PHY_EXTENDED_MODE_CONTROL_FAST_LINK_FAILURE    VTSS_PHY_BIT(4)
#define VTSS_S_PHY_EXTENDED_MODE_CONTROL_FAST_LINK_FAILURE    4
#define VTSS_S_PHY_EXTENDED_MODE_CONTROL_SIGDET_POLARITY      0

// Register 20E1 + Bit fields
#define VTSS_PHY_EXTENDED_PHY_CONTROL_3 VTSS_PHY_PAGE_EXTENDED, 20
#define  VTSS_M_PHY_EXTENDED_PHY_CONTROL_3_MEDIA_MODE_STATUS  VTSS_PHY_ENCODE_BITMASK(6,2)

// Register 21E1 + Bit fields
#define VTSS_PHY_RESERVED_1_WS VTSS_PHY_PAGE_EXTENDED, 21

// Register 22E1 + Bit fields
#define VTSS_PHY_RESERVED_2_WS VTSS_PHY_PAGE_EXTENDED, 22



// Register 23E1 + Bit fields
#define VTSS_PHY_EXTENDED_PHY_CONTROL_4 VTSS_PHY_PAGE_EXTENDED, 23
#define VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_PHY_ADDRESS  VTSS_PHY_ENCODE_BITMASK(11, 5)
#define VTSS_M_VTSS_PHY_EXTENDED_PHY_CONTROL_4_CU_MEDIA_CRC_ERROR_COUNTER  VTSS_PHY_ENCODE_BITMASK(0, 7)


// Register 24E1 + Bit fields
#define VTSS_PHY_VERIPHY_CTRL_REG1 VTSS_PHY_PAGE_EXTENDED, 24
#define VTSS_F_PHY_VERIPHY_CTRL_REG1_TRIGGER VTSS_PHY_BIT(15)
#define VTSS_F_PHY_VERIPHY_CTRL_REG1_VALID   VTSS_PHY_BIT(14)
#define VTSS_M_PHY_VERIPHY_CTRL_REG1_PAIR_A_DISTANCE VTSS_PHY_ENCODE_BITMASK(8, 6)
#define VTSS_M_PHY_VERIPHY_CTRL_REG1_PAIR_B_DISTANCE VTSS_PHY_ENCODE_BITMASK(0, 6)

// Register 25E1 + Bit fields
#define VTSS_PHY_VERIPHY_CTRL_REG2 VTSS_PHY_PAGE_EXTENDED, 25
#define VTSS_M_PHY_VERIPHY_CTRL_REG2_PAIR_C_DISTANCE VTSS_PHY_ENCODE_BITMASK(8, 6)
#define VTSS_M_PHY_VERIPHY_CTRL_REG2_PAIR_D_DISTANCE VTSS_PHY_ENCODE_BITMASK(0, 6)

// Register 26E1 + Bit fields
#define VTSS_PHY_VERIPHY_CTRL_REG3 VTSS_PHY_PAGE_EXTENDED, 26
#define VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_A_TERMINATION_STATUS VTSS_PHY_ENCODE_BITMASK(12, 4)
#define VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_B_TERMINATION_STATUS VTSS_PHY_ENCODE_BITMASK(8, 4)
#define VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_C_TERMINATION_STATUS VTSS_PHY_ENCODE_BITMASK(4, 4)
#define VTSS_M_PHY_VERIPHY_CTRL_REG3_PAIR_D_TERMINATION_STATUS VTSS_PHY_ENCODE_BITMASK(0, 4)


// Register 28E1 + Bit fields
#define VTSS_PHY_EXT_28 VTSS_PHY_PAGE_EXTENDED, 28
// Register 28E1 + Bit field overrides for Viper Rev. B enhanced EPG
#define VTSS_F_PHY_EXT_28_PKT_SZ_OV_ENA          VTSS_PHY_BIT(7)
#define VTSS_F_PHY_EXT_28_IPG_OV_ENA             VTSS_PHY_BIT(6)
#define VTSS_F_PHY_EXT_28_SIG_CTR_ENA            VTSS_PHY_BIT(5)
#define VTSS_F_PHY_EXT_28_ETYPE_UDPDEST_OV_ENA   VTSS_PHY_BIT(4)
#define VTSS_F_PHY_EXT_28_EPG_DATA_REG_IDX(val)  VTSS_PHY_ENCODE_BITFIELD(val, 0, 4)
#define VTSS_M_PHY_EXT_28_EPG_DATA_REG_IDX       VTSS_PHY_ENCODE_BITMASK(0, 4)

// Register 29E1 + Bit fields
#define EPG_CTRL_REG_1 VTSS_PHY_PAGE_EXTENDED, 29
#define VTSS_F_EPG_CTRL_REG_1_EPG_ENABLE              VTSS_PHY_BIT(15)
#define VTSS_F_EPG_CTRL_REG_1_EPG_RUN_STOP            VTSS_PHY_BIT(14)
#define VTSS_F_EPG_CTRL_REG_1_EPG_RUN_CONTINUOUS      VTSS_PHY_BIT(13)   /* Viper B Enhanced EPG */
#define VTSS_F_EPG_CTRL_REG_1_PKT_LENGTH(val)         VTSS_PHY_ENCODE_BITFIELD(val, 11, 2)
#define VTSS_F_EPG_CTRL_REG_1_IPG_8192NSEC            VTSS_PHY_BIT(10)
#define VTSS_F_EPG_CTRL_REG_1_MAC_DA_LOW_NIBBLE(val)  VTSS_PHY_ENCODE_BITFIELD(val, 6, 4)
#define VTSS_F_EPG_CTRL_REG_1_MAC_SA_LOW_NIBBLE(val)  VTSS_PHY_ENCODE_BITFIELD(val, 2, 4)
#define VTSS_F_EPG_CTRL_REG_1_RANDOM_PAYLOAD_PATTERN  VTSS_PHY_BIT(1)
#define VTSS_F_EPG_CTRL_REG_1_BAD_FRAME_FCS_GEN       VTSS_PHY_BIT(0)

#define VTSS_EPG_CTRL_REG_1_PKT_LEN_125               (0)
#define VTSS_EPG_CTRL_REG_1_PKT_LEN_64                (1)
#define VTSS_EPG_CTRL_REG_1_PKT_LEN_1518              (2)
#define VTSS_EPG_CTRL_REG_1_PKT_LEN_10000             (3)

// Register 30E1 + Bit fields
#define EPG_CTRL_REG_2 VTSS_PHY_PAGE_EXTENDED, 30



// ** Register definitions -  EXT2 page**
//Register 16E2
#define VTSS_PHY_CU_PMD_TX_CTRL VTSS_PHY_PAGE_EXTENDED_2, 16

//Register 17E2
#define VTSS_PHY_EEE_CONTROL VTSS_PHY_PAGE_EXTENDED_2, 17
#define VTSS_F_PHY_EEE_CONTROL_ENABLE_10BASE_TE VTSS_PHY_BIT(15)
#define VTSS_F_PHY_EEE_CONTROL_ENABLE_1000BASE_T_FORCE_MODE VTSS_PHY_BIT(5)

//Register 18E2
#define VTSS_EXTENDED_CHIP_ID          VTSS_PHY_PAGE_EXTENDED_2, 18
#define VTSS_PHY_TESLA_RGMII_CONTROL                         VTSS_PHY_PAGE_EXTENDED_2, 18
#define VTSS_F_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_TX(value)  VTSS_PHY_ENCODE_BITFIELD(value, 4, 3)
#define VTSS_M_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_TX         VTSS_PHY_ENCODE_BITMASK(4, 3)
#define VTSS_F_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_RX(value)  VTSS_PHY_ENCODE_BITFIELD(value, 1, 3)
#define VTSS_M_PHY_RGMII_CONTROL_TESLA_RGMII_SKEW_RX         VTSS_PHY_ENCODE_BITMASK(1, 3)

//Register 20E2
#define VTSS_PHY_RGMII_CONTROL         VTSS_PHY_PAGE_EXTENDED_2, 20
#define VTSS_F_PHY_RGMII_CONTROL_RX_CLK_OUT_DISABLE  VTSS_PHY_BIT(11)
#define VTSS_F_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_TX(value)  VTSS_PHY_ENCODE_BITFIELD(value, 0, 3)
#define VTSS_M_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_TX         VTSS_PHY_ENCODE_BITMASK(0, 3)
#define VTSS_F_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_RX(value)  VTSS_PHY_ENCODE_BITFIELD(value, 4, 3)
#define VTSS_M_PHY_RGMII_CONTROL_NANO_RGMII_SKEW_RX         VTSS_PHY_ENCODE_BITMASK(4, 3)
#define VTSS_M_PHY_RGMII_CONTROL_NANO_SOF_ENABLE            VTSS_PHY_BIT(12)

//Register 21E2
#define VTSS_PHY_WOL_LOWER_MAC_ADDR VTSS_PHY_PAGE_EXTENDED_2, 21

//Register 22E2
#define VTSS_PHY_WOL_MID_MAC_ADDR VTSS_PHY_PAGE_EXTENDED_2, 22

//Register 23E2
#define VTSS_PHY_WOL_UPPER_MAC_ADDR VTSS_PHY_PAGE_EXTENDED_2, 23

//Register 24E2
#define VTSS_PHY_WOL_LOWER_PASSWD VTSS_PHY_PAGE_EXTENDED_2, 24

//Register 25E2
#define VTSS_PHY_WOL_MID_PASSWD VTSS_PHY_PAGE_EXTENDED_2, 25

//Register 26E2
#define VTSS_PHY_WOL_UPPER_PASSWD VTSS_PHY_PAGE_EXTENDED_2, 26

//Register 27E2
#define VTSS_PHY_WOL_CONTROL VTSS_PHY_PAGE_EXTENDED_2, 27

#define VTSS_PHY_WOL_CONTROL_SECURE_ON_ENABLE         VTSS_PHY_BIT(15)
#define VTSS_PHY_WOL_CONTROL_SECURE_ON_PASSWD_LEN_4   VTSS_PHY_BIT(14)
#define VTSS_PHY_WOL_CONTROL_RESERVED_001             VTSS_PHY_BIT(13)
#define VTSS_PHY_WOL_CONTROL_RESERVED_002             VTSS_PHY_BIT(12)
#define VTSS_M_PHY_WOL_CONTROL_ADDR_REP_COUNT         VTSS_PHY_ENCODE_BITMASK(8, 4)
#define VTSS_M_PHY_WOL_CONTROL_RESERVED_003           VTSS_PHY_ENCODE_BITMASK(2, 6)
#define VTSS_PHY_WOL_CONTROL_MDINT_SIGNAL_SEP         VTSS_PHY_BIT(1)
#define VTSS_PHY_WOL_CONTROL_MDINT_CMOS_DRIVE_EN      VTSS_PHY_BIT(0)

//Register 28E2
#define VTSS_PHY_EXTENDED_INTERRUPT_MASK              VTSS_PHY_PAGE_EXTENDED_2, 28

#define VTSS_F_PHY_EXT_INT_MASK_RX_FIFO_UNDER_OVERFLOW_INT_MASK  VTSS_PHY_BIT(13)
#define VTSS_F_PHY_EXT_INT_MASK_TX_FIFO_UNDER_OVERFLOW_INT_MASK  VTSS_PHY_BIT(12)
#define VTSS_F_PHY_EXT_INT_MASK_RESERVED_001                     VTSS_PHY_BIT(11)
#define VTSS_F_PHY_EXT_INT_MASK_MEM_INTEGRITY_RING_CTL_INT_MASK  VTSS_PHY_BIT(10)
#define VTSS_F_PHY_EXT_INT_MASK_MACSEC_EGRESS_INT_MASK           VTSS_PHY_BIT(9)
#define VTSS_F_PHY_EXT_INT_MASK_MACSEC_INGRESS_INT_MASK          VTSS_PHY_BIT(8)
#define VTSS_F_PHY_EXT_INT_MASK_MACSEC_FLOW_CTL_INT_MASK         VTSS_PHY_BIT(7)
#define VTSS_F_PHY_EXT_INT_MASK_MACSEC_LINE_MAC_INT_MASK         VTSS_PHY_BIT(6)
#define VTSS_F_PHY_EXT_INT_MASK_MACSEC_HOST_MAC_INT_MASK         VTSS_PHY_BIT(5)
#define VTSS_F_PHY_EXT_INT_MASK_RR_SW_OVER_COMPL_INT_MASK        VTSS_PHY_BIT(4)
#define VTSS_F_PHY_EXT_INT_MASK_EEE_LINK_FAIL_INT_MASK           VTSS_PHY_BIT(3)
#define VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TQ_TIMER_INT_MASK         VTSS_PHY_BIT(2)
#define VTSS_F_PHY_EXT_INT_MASK_EEE_RX_TS_TIMER_INT_MASK         VTSS_PHY_BIT(1)
#define VTSS_F_PHY_EXT_INT_MASK_EEE_WAKE_ERR_INT_MASK            VTSS_PHY_BIT(0)

//Register 29E2
#define VTSS_PHY_EXTENDED_INTERRUPT_STATUS            VTSS_PHY_PAGE_EXTENDED_2, 29

//Register 30E2
#define VTSS_PHY_EXTENDED_RING_RESILIENCY_CTRL        VTSS_PHY_PAGE_EXTENDED_2, 30

#define VTSS_F_PHY_EXT_RING_RSLNT_STARTUP_EN                     VTSS_PHY_BIT(15)
#define VTSS_F_PHY_EXT_RING_RSLNT_ADVERTISE_RING_RESILIENCY      VTSS_PHY_BIT(14)
#define VTSS_F_PHY_EXT_RING_RSLNT_LP_RING_RESILIENCY_ADVERTISE   VTSS_PHY_BIT(13)
#define VTSS_F_PHY_EXT_RING_RSLNT_FORCE_RING_RESILIENCY_EN       VTSS_PHY_BIT(12)
#define VTSS_F_PHY_EXT_RING_RSLNT_RING_RESILIENCY_STATUS         VTSS_PHY_ENCODE_BITMASK(4, 2)
#define VTSS_F_PHY_EXT_RING_RSLNT_START_SWITCHOVER               VTSS_PHY_BIT(0)

// ** Register definitions -  EXT3 page**
// Register 16E3
#define VTSS_PHY_MAC_SERDES_PCS_CONTROL VTSS_PHY_PAGE_EXTENDED_3, 16
#define VTSS_F_MAC_SERDES_PCS_CONTROL_MAC_IF_PD_ENA               VTSS_PHY_BIT(13)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_FORCE_ADV_ABILITY           VTSS_PHY_BIT(11)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_SGMII_OUTPUT_PREAMBLE       VTSS_PHY_BIT(8)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_ANEG_ENA                    VTSS_PHY_BIT(7)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_INV_POLARITY_AT_INPUT       VTSS_PHY_BIT(6)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_INV_POLARITY_AT_OUTPUT      VTSS_PHY_BIT(5)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_FAST_LINK_STATUS_ENA        VTSS_PHY_BIT(4)
#define VTSS_F_MAC_SERDES_PCS_CONTROL_INHIBIT_MAC_ODD_START_DELAY VTSS_PHY_BIT(2)

// Register 17E3
#define VTSS_PHY_MAC_SERDES_PCS_STATUS  VTSS_PHY_PAGE_EXTENDED_3, 17
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_SYNC_FAIL                VTSS_PHY_BIT(15)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_CGBAD                    VTSS_PHY_BIT(14)
#define VTSS_F_MAC_SERDES_PCS_STATUS_SGMII_ALIGN_ERROR            VTSS_PHY_BIT(12)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_LP_ANEG_RESTART          VTSS_PHY_BIT(11)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_FDX_ADV                  VTSS_PHY_BIT(5)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_HDX_ADV                  VTSS_PHY_BIT(4)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_LP_ANEG_CAPABLE          VTSS_PHY_BIT(3)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_LINK_STATUS              VTSS_PHY_BIT(2)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_ANEG_COMPLETE            VTSS_PHY_BIT(1)
#define VTSS_F_MAC_SERDES_PCS_STATUS_MAC_PCS_SIG_DETECT           VTSS_PHY_BIT(0)


// Register 18E3
#define VTSS_PHY_REVERED_18 VTSS_PHY_PAGE_EXTENDED_3, 18
#define VTSS_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY VTSS_PHY_PAGE_EXTENDED_3, 18
#define VTSS_M_PHY_MAC_SERDES_CLAUSE_37_ADVERTISED_ABILITY  VTSS_PHY_ENCODE_BITMASK(0, 15)

// Register 20E3
#define VTSS_PHY_MAC_SERDES_STATUS VTSS_PHY_PAGE_EXTENDED_3, 20

// Register 21E3
#define VTSS_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER  VTSS_PHY_PAGE_EXTENDED_3, 21
#define VTSS_F_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER_ACTIVE VTSS_PHY_BIT(15)
#define VTSS_M_PHY_MEDIA_SERDES_TX_GOOD_PACKET_COUNTER_CNT    VTSS_PHY_ENCODE_BITMASK(0, 13)

// Register 22E3
#define VTSS_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER  VTSS_PHY_PAGE_EXTENDED_3, 22
#define VTSS_M_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_SELECT          VTSS_PHY_ENCODE_BITMASK(14, 2)
#define VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_SELECT(value)   VTSS_PHY_ENCODE_BITFIELD(value, 14, 2)
#define VTSS_F_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_TX_PREAMBLE_FIX    VTSS_PHY_BIT(13)
#define VTSS_M_PHY_MEDIA_SERDES_TX_CRC_ERROR_COUNTER_CNT                VTSS_PHY_ENCODE_BITMASK(0, 7)

// Register 23E3
#define VTSS_PHY_MEDIA_SERDES_PCS_CONTROL    VTSS_PHY_PAGE_EXTENDED_3, 23
#define VTSS_M_PHY_MEDIA_SERDES_PCS_CNTL_REMOTE_FAULT_TO_MEDIA             VTSS_PHY_ENCODE_BITMASK(15, 14)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_MEDIA_IF_ANEG_PARALLEL_DETECT     VTSS_PHY_BIT(13)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_FORCE_ADVERTISED_ABILITY          VTSS_PHY_BIT(11)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_POLARITY_REVERSAL_INPUT           VTSS_PHY_BIT(6)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_POLARITY_REVERSAL_OUTPUT          VTSS_PHY_BIT(5)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_INHIBIT_ODD_START_DELAY           VTSS_PHY_BIT(4)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_HLS               VTSS_PHY_BIT(2)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FORCE_FEFI              VTSS_PHY_BIT(1)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_CNTL_100BASEFX_FEFI_FORCE_VALUE        VTSS_PHY_BIT(0)

// Register 24E3
#define VTSS_PHY_MEDIA_SERDES_PCS_STATUS     VTSS_PHY_PAGE_EXTENDED_3, 24
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_100BASEFX_PROTO_XFER_LINK_STATUS VTSS_PHY_BIT(13)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_10MB_LINK_STATUS                 VTSS_PHY_BIT(12)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_LP_FULL_DUPLEX                   VTSS_PHY_BIT(5)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_LP_HALF_DUPLEX                   VTSS_PHY_BIT(4)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_LP_ANEG_CAP                      VTSS_PHY_BIT(3)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_MEDIA_LINK_STATUS                VTSS_PHY_BIT(2)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_MEDIA_ANEG_COMPLETE              VTSS_PHY_BIT(1)
#define VTSS_F_PHY_MEDIA_SERDES_PCS_STATUS_MEDIA_SIG_DET                    VTSS_PHY_BIT(0)

// Register 26E3
#define VTSS_PHY_MEDIA_SERDES_CLAUSE_37_LP_ABILITY VTSS_PHY_PAGE_EXTENDED_3, 26

// Register 27E3
#define VTSS_PHY_MEDIA_SERDES_STATUS                    VTSS_PHY_PAGE_EXTENDED_3, 27
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_COMMA_REALIGN                 VTSS_PHY_BIT(15)
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_SIG_DETECT                    VTSS_PHY_BIT(14)
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_100FX_FEFI_DETECT             VTSS_PHY_BIT(13)
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_COMMA_DETECT                  VTSS_PHY_BIT(12)
#define VTSS_M_PHY_MEDIA_SERDES_STATUS_COMMA_POSITION   VTSS_PHY_ENCODE_BITMASK(8, 11)
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_100FX_HLS_DETECT              VTSS_PHY_BIT(7)
#define VTSS_F_PHY_MEDIA_SERDES_STATUS_FIBER_SERDES_FREQ             VTSS_PHY_BIT(6)

// Register 28E3
#define VTSS_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER  VTSS_PHY_PAGE_EXTENDED_3, 28
#define VTSS_M_PHY_MEDIA_MAC_SERDES_RX_GOOD_COUNTER_CNT    VTSS_PHY_ENCODE_BITMASK(0, 13)

// Register 29E3
#define VTSS_PHY_MEDIA_MAC_SERDES_RX_CRC_CRC_ERR_COUNTER  VTSS_PHY_PAGE_EXTENDED_3, 29
#define VTSS_F_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_PKT_SINCE_LAST_RD  VTSS_PHY_BIT(15)
#define VTSS_M_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_RX_SELECT          VTSS_PHY_ENCODE_BITMASK(14, 2)
#define VTSS_F_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_RX_SELECT(value)   VTSS_PHY_ENCODE_BITFIELD(value, 14, 2)
#define VTSS_M_PHY_MEDIA_MAC_SERDES_RX_CRC_ERR_COUNTER_CNT                VTSS_PHY_ENCODE_BITMASK(0, 7)

// Register 26E4
#define VTSS_PHY_SPI_DAISY_CHAIN_CTRL                       VTSS_PHY_PAGE_EXTENDED_4, 26
#define VTSS_F_PHY_SPI_DAISY_CHAIN_CTRL_ENABLE_INPUT_PORT   VTSS_PHY_BIT(15)
#define VTSS_F_PHY_SPI_DAISY_CHAIN_CTRL_ENABLE_OUTPUT_PORT  VTSS_PHY_BIT(14)

// Register 28E4
#define VTSS_PHY_SPI_DAISY_CHAIN_CNTR                         VTSS_PHY_PAGE_EXTENDED_4, 28
#define VTSS_M_PHY_SPI_DAISY_CHAIN_CNTR_SELECT_DAISY_CHAIN_CNTR VTSS_PHY_ENCODE_BITMASK(15, 14)
#define VTSS_PHY_1588_PPS_0_MUX_CTRL                        VTSS_PHY_PAGE_EXTENDED_4, 21
#define VTSS_F_PHY_1588_PPS_0_MUX_CTRL_1588_SOFT_RESET      VTSS_PHY_BIT(15)

// ** Register definitions -  GPIO page**
#define VTSS_PHY_GPIO_0 VTSS_PHY_PAGE_GPIO, 0
#define VTSS_PHY_GPIO_3 VTSS_PHY_PAGE_GPIO, 3
#define VTSS_PHY_GPIO_4 VTSS_PHY_PAGE_GPIO, 4
#define VTSS_PHY_GPIO_5 VTSS_PHY_PAGE_GPIO, 5
#define VTSS_PHY_GPIO_6 VTSS_PHY_PAGE_GPIO, 6
#define VTSS_PHY_GPIO_7 VTSS_PHY_PAGE_GPIO, 7
#define VTSS_PHY_GPIO_8 VTSS_PHY_PAGE_GPIO, 8
#define VTSS_PHY_GPIO_9 VTSS_PHY_PAGE_GPIO, 9
#define VTSS_PHY_GPIO_10 VTSS_PHY_PAGE_GPIO, 10
#define VTSS_PHY_GPIO_11 VTSS_PHY_PAGE_GPIO, 11
#define VTSS_PHY_GPIO_12 VTSS_PHY_PAGE_GPIO, 12
#define VTSS_PHY_GPIO_15 VTSS_PHY_PAGE_GPIO, 15

// Register 13G + Bit fields
#define VTSS_PHY_SIGDET_GPIO_CONTROL VTSS_PHY_PAGE_GPIO, 13
#define VTSS_M_PHY_SIGDET_GPIO_CONTROL_GPIO0        VTSS_PHY_ENCODE_BITMASK(0, 2)
#define VTSS_F_PHY_SIGDET_GPIO_CONTROL_GPIO0(value) VTSS_PHY_ENCODE_BITFIELD(value, 0, 2)
#define VTSS_M_PHY_SIGDET_GPIO_CONTROL_GPIO1 VTSS_PHY_ENCODE_BITMASK(2, 2)
#define VTSS_F_PHY_SIGDET_GPIO_CONTROL_GPIO1(value) VTSS_PHY_ENCODE_BITFIELD(value, 2, 2)
#define VTSS_M_PHY_SIGDET_GPIO_CONTROL_GPIO2 VTSS_PHY_ENCODE_BITMASK(8, 2)
#define VTSS_F_PHY_SIGDET_GPIO_CONTROL_GPIO2(value) VTSS_PHY_ENCODE_BITFIELD(value, 2, 2)
#define VTSS_M_PHY_SIGDET_GPIO_CONTROL_GPIO3 VTSS_PHY_ENCODE_BITMASK(10, 2)
#define VTSS_F_PHY_SIGDET_GPIO_CONTROL_GPIO3(value) VTSS_PHY_ENCODE_BITFIELD(value, 10, 2)

// Register 14G + Bit fields
#define VTSS_PHY_GPIO_CONTROL_2 VTSS_PHY_PAGE_GPIO, 14
#define VTSS_M_PHY_GPIO_CONTROL_2_GPIO12_GPIO13            VTSS_PHY_ENCODE_BITMASK(14, 2)
#define VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_ENABLE  VTSS_PHY_BIT(13)
#define VTSS_F_PHY_GPIO_CONTROL_2_COMA_MODE_OUTPUT_DATA    VTSS_PHY_BIT(12)
#define VTSS_M_PHY_GPIO_CONTROL_2_GPIO4                    VTSS_PHY_ENCODE_BITMASK(0, 2)
#define VTSS_F_PHY_GPIO_CONTROL_2_GPIO4(value)             VTSS_PHY_ENCODE_BITFIELD(value, 0, 2)
#define VTSS_M_PHY_GPIO_CONTROL_2_GPIO5                    VTSS_PHY_ENCODE_BITMASK(2, 2)
#define VTSS_F_PHY_GPIO_CONTROL_2_GPIO5(value)             VTSS_PHY_ENCODE_BITFIELD(value, 2, 2)

// Register 15G
#define VTSS_PHY_GPIO_INPUT VTSS_PHY_PAGE_GPIO, 15

// Register 16G
#define VTSS_PHY_GPIO_OUTPUT VTSS_PHY_PAGE_GPIO, 16

// Register 17G
#define VTSS_PHY_GPIO_IN_OUT_CONF VTSS_PHY_PAGE_GPIO, 17
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO0    VTSS_PHY_BIT(0)
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO1    VTSS_PHY_BIT(1)
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO2    VTSS_PHY_BIT(4)
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO3    VTSS_PHY_BIT(5)
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO4    VTSS_PHY_BIT(8)
#define VTSS_F_PHY_GPIO_IN_OUT_CONF_GPIO5    VTSS_PHY_BIT(9)

// Register 18G
#define VTSS_PHY_MICRO_PAGE VTSS_PHY_PAGE_GPIO, 18

// Register 19G + Bit fields
#define      VTSS_PHY_GPIO_CONTROL_3 VTSS_PHY_PAGE_GPIO, 19
#define      VTSS_PHY_MAC_MODE_AND_FAST_LINK VTSS_PHY_PAGE_GPIO, 19
#define VTSS_F_PHY_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT(value)  VTSS_PHY_ENCODE_BITFIELD(value, 14, 2)
#define VTSS_M_MAC_MODE_AND_FAST_LINK_MAC_IF_MODE_SELECT VTSS_PHY_ENCODE_BITMASK(14, 2)
#define VTSS_M_PHY_GPIO_CONTROL_3_MAC_IF_MODE_SELECT VTSS_PHY_ENCODE_BITMASK(14, 2)

// Register 20G + Bit fields
#define VTSS_PHY_I2C_MUX_CONTROL_1 VTSS_PHY_PAGE_GPIO, 20
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_DEV_ADDR(value)  VTSS_PHY_ENCODE_BITFIELD(value, 9, 7)
#define VTSS_M_PHY_I2C_MUX_CONTROL_1_DEV_ADDR         VTSS_PHY_ENCODE_BITMASK(9, 7)
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ(value)  VTSS_PHY_ENCODE_BITFIELD(value, 4, 2)
#define VTSS_M_PHY_I2C_MUX_CONTROL_1_SCL_CLK_FREQ         VTSS_PHY_ENCODE_BITMASK(4, 2)
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_3_ENABLE        VTSS_PHY_BIT(3)
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_2_ENABLE        VTSS_PHY_BIT(2)
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_1_ENABLE        VTSS_PHY_BIT(1)
#define VTSS_F_PHY_I2C_MUX_CONTROL_1_PORT_0_ENABLE        VTSS_PHY_BIT(0)

// Register 21G + Bit fields
#define VTSS_PHY_I2C_MUX_CONTROL_2 VTSS_PHY_PAGE_GPIO, 21
#define VTSS_F_PHY_I2C_MUX_CONTROL_2_MUX_READY            VTSS_PHY_BIT(15)
#define VTSS_F_PHY_I2C_MUX_CONTROL_2_PHY_PORT_ADDR(value) VTSS_PHY_ENCODE_BITFIELD(value, 10, 2)
#define VTSS_M_PHY_I2C_MUX_CONTROL_2_PHY_PORT_ADDR        VTSS_PHY_ENCODE_BITMASK(10, 1)
#define VTSS_F_PHY_I2C_MUX_CONTROL_2_ENA_I2C_MUX_ACCESS   VTSS_PHY_BIT(9)
#define VTSS_F_PHY_I2C_MUX_CONTROL_2_RD                   VTSS_PHY_BIT(8)
#define VTSS_F_PHY_I2C_MUX_CONTROL_2_ADDR(value)          VTSS_PHY_ENCODE_BITFIELD(value, 0, 8)
#define VTSS_M_PHY_I2C_MUX_CONTROL_2_ADDR                 VTSS_PHY_ENCODE_BITMASK(7, 0)

// Register 22G + Bit fields
#define VTSS_PHY_I2C_MUX_DATA_READ_WRITE VTSS_PHY_PAGE_GPIO, 22
#define VTSS_M_PHY_I2C_MUX_DATA_READ_WRITE_READ_DATA          VTSS_PHY_ENCODE_BITMASK(8, 8)
#define VTSS_F_PHY_I2C_MUX_DATA_READ_WRITE_WRITE_DATA(value)  VTSS_PHY_ENCODE_BITFIELD(value, 0, 8)
#define VTSS_M_PHY_I2C_MUX_DATA_READ_WRITE_WRITE_DATA         VTSS_PHY_ENCODE_BITMASK(0, 8)

// Register 23G + Bit fields
#define VTSS_PHY_RECOVERED_CLOCK_0_CONTROL VTSS_PHY_PAGE_GPIO, 23

// Register 24G + Bit fields
#define VTSS_PHY_RECOVERED_CLOCK_1_CONTROL VTSS_PHY_PAGE_GPIO, 24


// Register 25G + Bit fields
#define VTSS_PHY_ENHANCED_LED_CONTROL VTSS_PHY_PAGE_GPIO, 25

// Register 26G + Bit fields
#define VTSS_PHY_TEMP_CONF VTSS_PHY_PAGE_GPIO, 26

// Register 28G + Bit fields
#define VTSS_PHY_TEMP_VAL VTSS_PHY_PAGE_GPIO, 28

// Register 30G + Bit fields
#define VTSS_PHY_EXTENDED_REVISION             VTSS_PHY_PAGE_GPIO, 30
#define VTSS_F_PHY_EXTENDED_REVISION_TESLA_E   VTSS_PHY_BIT(0)


// ** Register definitions -  TEST page**
#define VTSS_PHY_TEST_PAGE_0 VTSS_PHY_PAGE_TEST, 0
#define VTSS_PHY_TEST_PAGE_1 VTSS_PHY_PAGE_TEST, 1
#define VTSS_PHY_TEST_PAGE_2 VTSS_PHY_PAGE_TEST, 2
#define VTSS_PHY_TEST_PAGE_3 VTSS_PHY_PAGE_TEST, 3
#define VTSS_PHY_TEST_PAGE_5 VTSS_PHY_PAGE_TEST, 5
#define VTSS_PHY_TEST_PAGE_8 VTSS_PHY_PAGE_TEST, 8
#define VTSS_PHY_TEST_PAGE_9 VTSS_PHY_PAGE_TEST, 9
#define VTSS_PHY_TEST_PAGE_12 VTSS_PHY_PAGE_TEST, 12
#define VTSS_PHY_TEST_PAGE_19 VTSS_PHY_PAGE_TEST, 19
#define VTSS_PHY_TEST_PAGE_20 VTSS_PHY_PAGE_TEST, 20
#define VTSS_PHY_TEST_PAGE_22 VTSS_PHY_PAGE_TEST, 22
#define VTSS_PHY_TEST_PAGE_23 VTSS_PHY_PAGE_TEST, 23
#define VTSS_PHY_TEST_PAGE_24 VTSS_PHY_PAGE_TEST, 24
#define VTSS_PHY_TEST_PAGE_25 VTSS_PHY_PAGE_TEST, 25
#define VTSS_PHY_TEST_PAGE_27 VTSS_PHY_PAGE_TEST, 27
#define VTSS_PHY_TEST_PAGE_28 VTSS_PHY_PAGE_TEST, 28


// ** Register definitions -  TR page**
#define VTSS_PHY_PAGE_TR_0 VTSS_PHY_PAGE_TR, 0
#define VTSS_PHY_PAGE_TR_1 VTSS_PHY_PAGE_TR, 1
#define VTSS_PHY_PAGE_TR_2 VTSS_PHY_PAGE_TR, 2
#define VTSS_PHY_PAGE_TR_16 VTSS_PHY_PAGE_TR, 16
#define VTSS_PHY_PAGE_TR_17 VTSS_PHY_PAGE_TR, 17
#define VTSS_PHY_PAGE_TR_18 VTSS_PHY_PAGE_TR, 18

// ** Register definitions -  1588 page**
#define VTSS_PHY_PAGE_1588_16 VTSS_PHY_PAGE_1588, 16
#define VTSS_PHY_F_PAGE_1588_16_CMD_BIT  VTSS_PHY_BIT(15)
#define VTSS_PHY_F_PAGE_1588_16_READ  VTSS_PHY_BIT(14)
#define VTSS_PHY_F_PAGE_1588_16_TARGET(value) VTSS_PHY_ENCODE_BITFIELD(value, 11, 3)
#define VTSS_PHY_F_PAGE_1588_16_CSR_REG_ADDR(value) VTSS_PHY_ENCODE_BITFIELD(value, 0, 11)

#define VTSS_PHY_PAGE_1588_CSR_DATA_LSB VTSS_PHY_PAGE_1588, 17
#define VTSS_PHY_PAGE_1588_CSR_DATA_MSB VTSS_PHY_PAGE_1588, 18


// ** Register definitions -  MACSEC page**
#define VTSS_PHY_PAGE_MACSEC_19 VTSS_PHY_PAGE_MACSEC, 19
#define VTSS_PHY_PAGE_MACSEC_20 VTSS_PHY_PAGE_MACSEC, 20
#define VTSS_PHY_F_PAGE_MACSEC_19_CMD_BIT  VTSS_PHY_BIT(15)
#define VTSS_PHY_F_PAGE_MACSEC_20_READY(value) VTSS_PHY_ENCODE_BITFIELD(value, 13, 2)

#define VTSS_PHY_F_PAGE_MACSEC_19_READ  VTSS_PHY_BIT(14)
#define VTSS_PHY_F_PAGE_MACSEC_19_TARGET(value) VTSS_PHY_ENCODE_BITFIELD(value, 12, 2)
#define VTSS_PHY_F_PAGE_MACSEC_20_TARGET(value) VTSS_PHY_ENCODE_BITFIELD(value, 0, 4)
#define VTSS_PHY_F_PAGE_MACSEC_19_CSR_REG_ADDR(value) VTSS_PHY_ENCODE_BITFIELD(value, 0, 14)

#define VTSS_PHY_PAGE_MACSEC_CSR_DATA_LSB VTSS_PHY_PAGE_MACSEC, 17
#define VTSS_PHY_PAGE_MACSEC_CSR_DATA_MSB VTSS_PHY_PAGE_MACSEC, 18


/* ********************************************************************* */
/*            The following Definitions Apply for Tesla SERDES ONLY      */
/* ********************************************************************* */
/* PHY SerDes Init Interface */
typedef enum {
    VTSS_PHY_SERDES_INIT_NONE,          /* Unknown */
    VTSS_PHY_SERDES_INIT_MAC,           /* MAC */
    VTSS_PHY_SERDES_INIT_MEDIA,         /* MEDIA */
} vtss_phy_serdes_init_t;

typedef enum {
    VTSS_TESLA_SERDES_PRBS_7
} vtss_phy_serdes_prbs_t;

typedef enum {
    VTSS_TESLA_SERDES_TEST_MODE_OFF,
    VTSS_TESLA_SERDES_TEST_MODE_BIST
} vtss_phy_serdes_test_mode_t;

#define VTSS_TESLA_MCB_CFG_BUF_START_ADDR   (0xd7c7)
// the following match the current config and status sizes (in bits) in Tesla
#define VTSS_TESLA_SD1G_ANA_CFG_SIZE    100
#define VTSS_TESLA_SD1G_DIG_CFG_SIZE    96
#define VTSS_TESLA_CFG_SIZE_SD1G    (VTSS_TESLA_SD1G_ANA_CFG_SIZE+VTSS_TESLA_SD1G_DIG_CFG_SIZE) //196

#define VTSS_TESLA_SD6G_ANA_CFG_SIZE    148
#define VTSS_TESLA_SD6G_DIG_CFG_SIZE    154
#define VTSS_TESLA_CFG_SIZE_SD6G    (VTSS_TESLA_SD6G_ANA_CFG_SIZE+VTSS_TESLA_SD6G_DIG_CFG_SIZE) //302

#define VTSS_TESLA_SYNC_ETH_CFG_SIZE    6
#define VTSS_TESLA_RCOMP_CFG_SIZE   12
// for LCPLL
#define VTSS_TESLA_PLL5G_CFG_SIZE   154
#define VTSS_TESLA_CFG_SIZE_RCPL    (VTSS_TESLA_SYNC_ETH_CFG_SIZE+VTSS_TESLA_RCOMP_CFG_SIZE+VTSS_TESLA_PLL5G_CFG_SIZE)  //172

#define VTSS_TESLA_SD1G_ANA_STAT_SIZE   11
#define VTSS_TESLA_SD1G_DIG_STAT_SIZE   7
#define VTSS_TESLA_STAT_SIZE_SD1G   (VTSS_TESLA_SD1G_ANA_STAT_SIZE+VTSS_TESLA_SD1G_DIG_STAT_SIZE)   //18

#define VTSS_TESLA_SD6G_ANA_STAT_SIZE   11
#define VTSS_TESLA_SD6G_DIG_STAT_SIZE   7
#define VTSS_TESLA_STAT_SIZE_SD6G   VTSS_TESLA_SD6G_ANA_STAT_SIZE+VTSS_TESLA_SD6G_DIG_STAT_SIZE //18

#define VTSS_TESLA_RCOMP_STAT_SIZE  6
#define VTSS_TESLA_PLL5G_STAT_SIZE  40
#define VTSS_TESLA_STAT_SIZE_RCPL   VTSS_TESLA_RCOMP_STAT_SIZE+VTSS_TESLA_PLL5G_STAT_SIZE   //46

// frequently used config bit locations (min. bit if bit field)
// SERDES1G_ANA_CFG
#define VTSS_TESLA_SERDES1G_ANA_CFG_PLL_FSM_ENA_1G           3  // cfg_vec[3]
#define VTSS_TESLA_SERDES1G_ANA_CFG_PLL_FSM_CTRL_DATA_1G     4  // cfg_vec[11:4]
#define VTSS_TESLA_SERDES1G_ANA_CFG_PLL_ENA_RC_DIV2_1G      12  // cfg_vec[12]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IF_MODE_1G              14  // cfg_vec[14]
#define VTSS_TESLA_SERDES1G_ANA_CFG_HRATE_1G                15  // cfg_vec[15]
#define VTSS_TESLA_SERDES1G_ANA_CFG_ENA_PLOOP_1G            16  // cfg_vec[16]
#define VTSS_TESLA_SERDES1G_ANA_CFG_ENA_ILOOP_1G            17  // cfg_vec[17]
#define VTSS_TESLA_SERDES1G_ANA_CFG_ENA_FLOOP_1G            18  // cfg_vec[18]
#define VTSS_TESLA_SERDES1G_ANA_CFG_ENA_ELOOP_1G            19  // cfg_vec[19]
#define VTSS_TESLA_SERDES1G_ANA_CFG_PWD_TX_1G               24  // cfg_vec[24]
#define VTSS_TESLA_SERDES1G_ANA_CFG_PWD_RX_1G               25  // cfg_vec[25]
#define VTSS_TESLA_SERDES1G_ANA_CFG_ENA_LANE_1G             26  // cfg_vec[26]
#define VTSS_TESLA_SERDES1G_ANA_CFG_SYS_RST_1G              31  // cfg_vec[31]
#define VTSS_TESLA_SERDES1G_ANA_CFG_OB_RES_CTRL_1G          42  // cfg_vec[45:42]
#define VTSS_TESLA_SERDES1G_ANA_CFG_OB_VCM_CTRL_1G          46  // cfg_vec[49:46]
#define VTSS_TESLA_SERDES1G_ANA_CFG_OB_AMP_CTRL_1G          55  // cfg_vec[58:55]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_RES_CTRL_1G          61  // cfg_vec[64:61]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_EQ_GAIN_1G           67  // cfg_vec[69:67]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_OFFSET_COMP_1G   70  // cfg_vec[70]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_HYST_1G          71  // cfg_vec[71]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_DETLEV_1G        72  // cfg_vec[72]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_DC_COUPLING_1G   73  // cfg_vec[73]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_ENA_CMV_TERM_1G      74  // cfg_vec[74]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_DET_LEV_1G           76  // cfg_vec[78:76]
#define VTSS_TESLA_SERDES1G_ANA_CFG_IB_FX100_ENA_1G         82  // cfg_vec[82]
#define VTSS_TESLA_SERDES1G_ANA_CFG_DES_BW_ANA_1G           88  // cfg_vec[90:88]
#define VTSS_TESLA_SERDES1G_ANA_CFG_DES_MBTR_CTRL_1G        91  // cfg_vec[93:91]
#define VTSS_TESLA_SERDES1G_ANA_CFG_DES_CPMD_SEL_1G         94  // cfg_vec[95:94]
#define VTSS_TESLA_SERDES1G_ANA_CFG_DES_PHS_CTRL_1G         96  // cfg_vec[99:96]
// SERDES1G_DIG_CFG
#define VTSS_TESLA_SERDES1G_DIG_CFG_LANE_RST_1G            100  // cfg_vec[100]
#define VTSS_TESLA_SERDES1G_DIG_CFG_TX_DATA_INV_ENA_1G     101  // cfg_vec[101]
#define VTSS_TESLA_SERDES1G_DIG_CFG_RX_DATA_INV_ENA_1G     102  // cfg_vec[102]
#define VTSS_TESLA_SERDES1G_DIG_CFG_TX_LPI_MODE_ENA_1G     103  // cfg_vec[103]
#define VTSS_TESLA_SERDES1G_DIG_CFG_RX_LPI_MODE_ENA_1G     104  // cfg_vec[104]
#define VTSS_TESLA_SERDES1G_DIG_CFG_DES_100FX_CPMD_ENA_1G  105  // cfg_vec[105]
#define VTSS_TESLA_SERDES1G_DIG_CFG_DES_100FX_CPMD_MODE_1G 106  // cfg_vec[106]
#define VTSS_TESLA_SERDES1G_DIG_CFG_DES_100FX_CPMD_SWAP_1G 107  // cfg_vec[107]
#define VTSS_TESLA_SERDES1G_DIG_CFG_TEST_MODE_1G           189 // cfg_vec[191:189]
#define VTSS_TESLA_SERDES1G_DIG_CFG_PRBS_SEL_1G            192 // cfg_vec[193:192]
#define VTSS_TESLA_SERDES1G_DIG_CFG_INV_DIS_1G             194 // cfg_vec[194]
#define VTSS_TESLA_SERDES1G_DIG_CFG_LAZYBIT_1G             195 // cfg_vec[195]

// SERDES6G_ANA_CFG
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_ROT_FRQ_6G        0   // cfg_vec[0]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_ROT_DIR_6G        1   // cfg_vec[1]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_FSM_ENA_6G        5   // cfg_vec[5]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_FSM_CTRL_DATA_6G  6   // cfg_vec[13:6]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_ENA_ROT_6G       14  // cfg_vec[14]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PLL_DIV4_6G          15  // cfg_vec[15]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IF_MODE_6G           16  // cfg_vec[17:16]
#define VTSS_TESLA_SERDES6G_ANA_CFG_QRATE_6G             18  // cfg_vec[18]
#define VTSS_TESLA_SERDES6G_ANA_CFG_HRATE_6G             19  // cfg_vec[19]
#define VTSS_TESLA_SERDES6G_ANA_CFG_ENA_PLOOP_6G         20  // cfg_vec[20]
#define VTSS_TESLA_SERDES6G_ANA_CFG_ENA_ILOOP_6G         21  // cfg_vec[21]
#define VTSS_TESLA_SERDES6G_ANA_CFG_ENA_FLOOP_6G         22  // cfg_vec[22]
#define VTSS_TESLA_SERDES6G_ANA_CFG_ENA_ELOOP_6G         23  // cfg_vec[23]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PWD_TX_6G            28  // cfg_vec[28]
#define VTSS_TESLA_SERDES6G_ANA_CFG_PWD_RX_6G            29  // cfg_vec[29]
#define VTSS_TESLA_SERDES6G_ANA_CFG_ENA_LANE_6G          30  // cfg_vec[30]
#define VTSS_TESLA_SERDES6G_ANA_CFG_SYS_RST_6G           35  // cfg_vec[35]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_LEV_6G            45  // cfg_vec[50:45]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_EN_CAS_6G         51  // cfg_vec[53:51]
//#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_RES_CTRL_6G     54  // cfg_vec[57:54]
//#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_SR_6G           58  // cfg_vec[61:58]
// these were swapped in routing in Luton26/Atom12
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_SR_6G             54  // cfg_vec[57:54]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_RES_CTRL_6G       58  // cfg_vec[61:58]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_SR_H_6G           62  // cfg_vec[62]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST0_6G          77  // cfg_vec[82:77]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_POST1_6G          72  // cfg_vec[76:72]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_PREC_6G           67  // cfg_vec[71:67]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_POL_6G            83  // cfg_vec[83]
#define VTSS_TESLA_SERDES6G_ANA_CFG_OB_ENA1V_MODE_6G     84  // cfg_vec[84]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_RST_6G            86  // cfg_vec[86]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_FX100_ENA_6G      87  // cfg_vec[87]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_ENA_OFFSDC_6G     88  // cfg_vec[88]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_ENA_OFFSAC_6G     89  // cfg_vec[89]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_DIS_EQ_6G         90  // cfg_vec[90]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_CTERM_ENA_6G      91  // cfg_vec[91]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_C_6G              94  // cfg_vec[97:94]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_RES_CTRL_6G      100 // cfg_vec[103:100]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_VBCOM_6G         104 // cfg_vec[106:104]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_VBAC_6G          107 // cfg_vec[109:107]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_RT_6G            110 // cfg_vec[113:110]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_RF_6G            114 // cfg_vec[117:114]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_IC_DC_6G         119 // cfg_vec[121:119]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_IC_COM_6G        122 // cfg_vec[124:122]
#define VTSS_TESLA_SERDES6G_ANA_CFG_IB_IC_AC_6G         125 // cfg_vec[127:125]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_BW_ANA_6G       132 // cfg_vec[134:132]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_SWAP_HYST_6G    135 // cfg_vec[135]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_BW_HYST_6G      136 // cfg_vec[138:136]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_CPMD_SEL_6G     139 // cfg_vec[140:139]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_MBTR_CTRL_6G    141 // cfg_vec[143:141]
#define VTSS_TESLA_SERDES6G_ANA_CFG_DES_PHS_CTRL_6G     144 // cfg_vec[147:144]
// SERDES6G_DIG_CFG
#define VTSS_TESLA_SERDES6G_DIG_CFG_AN_OB_LEV_6G        148 // cfg_vec[153:148]
#define VTSS_TESLA_SERDES6G_DIG_CFG_AN_OB_ENA_CAS_6G    154 // cfg_vec[156:154]
#define VTSS_TESLA_SERDES6G_DIG_CFG_AN_OB_PREC_6G       157 // cfg_vec[161:157]
#define VTSS_TESLA_SERDES6G_DIG_CFG_AN_OB_POST1_6G      162 // cfg_vec[166:162]
#define VTSS_TESLA_SERDES6G_DIG_CFG_AN_OB_POST0_6G      167 // cfg_vec[172:167]
#define VTSS_TESLA_SERDES6G_DIG_CFG_LANE_RESET_6G       173 // cfg_vec[173]
#define VTSS_TESLA_SERDES6G_DIG_CFG_TX_DATA_INV_ENA_6G  174 // cfg_vec[174]
#define VTSS_TESLA_SERDES6G_DIG_CFG_RX_DATA_INV_ENA_6G  175 // cfg_vec[175]
#define VTSS_TESLA_SERDES6G_DIG_CFG_TX_LPI_MODE_ENA_6G  176 // cfg_vec[176]
#define VTSS_TESLA_SERDES6G_DIG_CFG_RX_LPI_MODE_ENA_6G  177 // cfg_vec[177]
//=====//
#define VTSS_TESLA_SERDES6G_DIG_CFG_TEST_MODE_6G        284 // cfg_vec[286:284]
#define VTSS_TESLA_SERDES6G_DIG_CFG_PRBS_SEL_6G         287 // cfg_vec[288:287]
#define VTSS_TESLA_SERDES6G_DIG_CFG_INV_DIS_6G          289 // cfg_vec[289]
#define VTSS_TESLA_SERDES6G_DIG_CFG_LAZYBIT_6G          290 // cfg_vec[290]
#define VTSS_TESLA_SERDES6G_DIG_CFG_SIGDET_DST_6G       291 // cfg_vec[293:291]
#define VTSS_TESLA_SERDES6G_DIG_CFG_SIGDET_AST_6G       294 // cfg_vec[296:294]
#define VTSS_TESLA_SERDES6G_DIG_CFG_SIGDET_TESTMODE_6G  297 // cfg_vec[297]

// RCOMP_CFG
#define VTSS_TESLA_RCOMP_CFG_RCOMP_MODE_SEL         (VTSS_TESLA_SYNC_ETH_CFG_SIZE+5)  // cfg_vec[12:11]
#define VTSS_TESLA_RCOMP_CFG_RCOMP_RUN_CAL          (VTSS_TESLA_SYNC_ETH_CFG_SIZE+9)  // cfg_vec[15]
#define VTSS_TESLA_RCOMP_CFG_RCOMP_DISTR_DIS        (VTSS_TESLA_SYNC_ETH_CFG_SIZE+11) // cfg_vec[17]
// RCOMP_STATUS
#define VTSS_TESLA_RCOMP_STATUS_RCOMP_RCOMP     0   // stat_vec[3:0]
#define VTSS_TESLA_RCOMP_STATUS_RCOMP_BUSY      5   // stat_vec[5]
// PLL5G_STATUS (LCPLL)
#define VTSS_TESLA_PLL5G_STATUS_PLL5G_LOCK_STATUS   (VTSS_TESLA_RCOMP_STAT_SIZE+26)   // stat_vec[32]
#define VTSS_TESLA_PLL5G_STATUS_PLL5G_FSM_LOCK      (VTSS_TESLA_RCOMP_STAT_SIZE+39)   // stat_vec[45]



#endif /* _VTSS_PHY_H_ */
