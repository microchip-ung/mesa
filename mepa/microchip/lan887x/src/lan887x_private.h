// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef LAN887X_PRIVATE_H
#define LAN887X_PRIVATE_H

#include "lan887x_registers.h"

#define LAN887X_NSLEEP(ns)           MEPA_NSLEEP((ns))
#define LAN887X_MTIMER_START(t, ms) MEPA_MTIMER_START((t), (ms))

#define MEPA_RC_GOTO(rc, expr) { { (rc) = (expr); }  if ((rc) != 0) { goto error; } }

// START:: LMSTAX OS PRINTS
//Uncomment following to enable OS prints on LMSTAX
//NOTE: It might flood the console!
//#ifdef MEPA_OPSYS_LMSTAX
//#define T_D(grp, format, ...) LM_OS_PR(format, ##__VA_ARGS__);
//#else
#define T_D(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_DEBUG, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
//#endif
// END:: LMSTAX OS PRINTS

#define T_I(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_INFO, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_W(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_WARNING, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);
#define T_E(grp, format, ...) MEPA_trace(grp, MEPA_TRACE_LVL_ERROR, __FUNCTION__, __LINE__, format, ##__VA_ARGS__);

// Locking Macros
// The variable 'dev' is passed as macro argument to obtain callback pointers and call actual lock functions. It does not indicate locks per port.
#define MEPA_ENTER(dev) {                               \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_enter != NULL) {        \
        (dev)->callout->lock_enter(&lock);         \
    }                                                \
}

#define MEPA_EXIT(dev) {          \
    mepa_lock_t lock;                                \
    lock.function = __FUNCTION__;                    \
    lock.file = __FILE__;                            \
    lock.line = __LINE__;                            \
    if ((dev)->callout->lock_exit != NULL) {         \
        (dev)->callout->lock_exit(&lock);          \
    }                                                \
}

#ifdef MEPA_lan887x_static_mem
#define LAN887X_PHY_MAX                        (MEPA_lan887x_phy_max)
#else
#define LAN887X_PHY_MAX                        (1U)
#endif
#define LAN887X_PHY_ID_MAX      (LAN887X_PHY_MAX)

#define LAN8870_PHY_ID          (0x7C1F2U)
#define LAN887X_PHY_ID_MASK     (0xFFFF2U)

#define LAN887X_PHY_ID_PRTO         (0x7C002U)
#define LAN887X_PHY_ID_PRTO_MSK     (0xFFF002U)
#define LAN887X_PHY_ID_EXACT        (0xFFFFF2U)

#define IS_LAN887X_B0_PROTOS(id) (((id) & LAN887X_PHY_ID_EXACT) == LAN887X_PHY_ID_PRTO)

#define PHY_LINKUP          (PHY_TRUE)
#define PHY_LINKDOWN        (PHY_FALSE)

#define INTR_BIT_LEN    (16U)

#define ARRAY_SIZE(x)                       (sizeof(x) / sizeof((x)[0]))

#define BIT(x)                              ((ONE) << (x))
#define CLEAR_BIT(x, n)                     ((x) & ~(BIT(n)))
#define BIT_MASK(x)                         (((ONE) << (x)) - (ONE))

#define EXTRACT_BITS(val, offset, width)    (((val) >> (offset)) & BIT_MASK(width))
#define GENMASK(offset, width)           (BIT_MASK(width) << (offset))

//Retrieve PHY_ID
#define GET_PHY_ID1(x)      (((x) << 2U) & 0x03FFFCU)
#define GET_PHY_ID2(x)      ((EXTRACT_BITS(x, 10U, 6U) << 18U) & 0xFFFFFFFFU)
#define GET_PHY_REV(x)      EXTRACT_BITS(x, 0U, 4U)
#define GET_PHY_MODEL(x)    EXTRACT_BITS(x, 4U, 6U)

/*
 * Data structures
 */
typedef struct {
    uint32_t id;
    uint16_t  model;
    uint16_t  rev;
    mepa_bool_t is_master;
    mepa_bool_t is_master_fault;
} phy_dev_info_t;

typedef struct {
    mepa_bool_t                     sleep_enable;
    mepa_tc10_wakeup_mode_t         wakeup_mode;
    mepa_tc10_wakeup_fwd_mode_t     wakeup_fwd_mode;
    mepa_gpio_mode_t                wake_in_pol;
    mepa_gpio_mode_t                wake_out_pol;
    mepa_gpio_mode_t                wake_out_mode;
    mepa_gpio_mode_t                inh_mode;
} lan887x_tc10_data_t;

typedef struct {
    mepa_bool_t             init_done;
    mepa_bool_t             link_status;
    mepa_port_no_t          port_no;
    mepa_port_interface_t   mac_if;
    mepa_media_interface_t  media_intf;
    mepa_conf_t             conf;
    mepa_event_t            events;
    mepa_loopback_t         loopback;
    phy_dev_info_t          dev;
    mepa_bool_t             ctx_status;
    mepa_cable_diag_result_t cd_res;
    lan887x_tc10_data_t         tc10_cfg;
    mepa_gpio_conf_t        led3_conf;
    /* Pointer to the device of base port on the phy chip */
    //mepa_device_t           *base_dev;
} phy_data_t;

struct phy_reg_dbg {
    const char *string;
    uint8_t mmd;
    uint16_t reg;
};

struct phy_reg_map {
    uint8_t  mmd;
    uint16_t offset;
    uint16_t val;
};

typedef enum  {
    LAN887X_RST_SOFT,           // soft-reset and re-configure
    LAN887X_RST_SOFT_MAC,       // mac change, soft-reset and re-configure
    LAN887X_RST_SOFT_EXT,       // external soft-reset and re-configure
    LAN887X_RST_HARD_ONLY,      // hard-reset only
    LAN887X_RST_HARD,           // hard-reset, phy_setup and re-configure
    LAN887X_RST_SKIP_TO_CONF,   // no reset. proceed to re-configure
    //Anything new above this line
    LAN887X_RST_MAX
} lan887x_reset_typ;

typedef enum {
    LAN87XX_CABLE_TEST_OK,
    LAN87XX_CABLE_TEST_OPEN,
    LAN87XX_CABLE_TEST_SHORT,
} lan887x_cd_status_t;

extern mepa_tc10_driver_t lan887x_tc10_drivers;
mepa_rc lan887x_phy_tc10_set_config(struct mepa_device *dev, lan887x_tc10_data_t *cfg);

mepa_rc phy_reg_rd(mepa_device_t *const phydev, uint32_t const offset, uint16_t *const value);

mepa_rc phy_reg_wr(mepa_device_t *const phydev, uint32_t const offset, uint16_t const value);

mepa_rc phy_reg_modify(mepa_device_t *const phydev, uint32_t const offset, uint16_t const mask, uint16_t const value);

mepa_rc phy_reg_set_bits(mepa_device_t *const phydev, uint32_t const offset, uint16_t const value);

mepa_rc phy_reg_clear_bits(mepa_device_t *const phydev, uint32_t const offset, uint16_t const value);

mepa_rc phy_mmd_reg_rd(mepa_device_t *const phydev, uint32_t const dev, uint32_t const offset, uint16_t *const value);

mepa_rc phy_mmd_reg_wr(mepa_device_t *const phydev, uint32_t const dev, uint32_t const offset, uint16_t const value);

mepa_rc phy_mmd_reg_modify(mepa_device_t *const phydev, uint32_t const dev, uint32_t const offset, uint16_t const mask, uint16_t const value);

mepa_rc phy_mmd_reg_clear_bits(mepa_device_t *const phydev, uint32_t const dev, uint32_t const offset, uint16_t const value);

mepa_rc phy_mmd_reg_set_bits(mepa_device_t *const phydev, uint32_t const dev, uint32_t const offset, uint16_t const value);

#endif //LAN887X_PRIVATE_H
