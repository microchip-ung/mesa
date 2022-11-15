// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Initialization API
 * \details This header file describes functions used to create and initialize targets
 */

#ifndef _VTSS_INIT_API_H_
#define _VTSS_INIT_API_H_

#include <vtss/api/types.h>
#include <vtss_misc_api.h>
#include <vtss_port_api.h>
#ifdef __cplusplus
extern "C" {
#endif

/** \brief Target chip type */
typedef enum {
    VTSS_TARGET_CU_PHY,                       /**< Cu PHY family */
    VTSS_TARGET_10G_PHY,                      /**< 10G PHY family */
    VTSS_TARGET_SPARX_III_10_UM    = 0x7420,  /**< SparxIII-10 unmanaged switch */
    VTSS_TARGET_SPARX_III_17_UM    = 0x7421,  /**< SparxIII-17 unmanaged switch */
    VTSS_TARGET_SPARX_III_25_UM    = 0x7422,  /**< SparxIII-25 unmanaged switch */
    VTSS_TARGET_CARACAL_LITE       = 0x7423,  /**< Caracal-Lite CE switch */
    VTSS_TARGET_SPARX_III_10       = 0x7424,  /**< SparxIII-10 switch */
    VTSS_TARGET_SPARX_III_18       = 0x7425,  /**< SparxIII-18 switch */
    VTSS_TARGET_SPARX_III_24       = 0x7426,  /**< SparxIII-24 switch */
    VTSS_TARGET_SPARX_III_26       = 0x7427,  /**< SparxIII-26 switch */
    VTSS_TARGET_SPARX_III_10_01    = 0x17424, /**< SparxIII-10-01 switch */
    VTSS_TARGET_CARACAL_1          = 0x7428,  /**< Caracal-1 CE switch */
    VTSS_TARGET_CARACAL_2          = 0x7429,  /**< Caracal-2 CE switch */
    VTSS_TARGET_SPARX_IV_52        = 0x7442,  /**< Sparx-IV-52 switch */
    VTSS_TARGET_SPARX_IV_44        = 0x7444,  /**< Sparx-IV-44 switch */
    VTSS_TARGET_SPARX_IV_80        = 0x7448,  /**< Sparx-IV-80 switch */
    VTSS_TARGET_SPARX_IV_90        = 0x7449,  /**< Sparx-IV-90 switch */
    VTSS_TARGET_SERVAL_2           = 0x7438,  /**< Serval-2 CE switch */
    VTSS_TARGET_LYNX_2             = 0x7464,  /**< LynX-2 CE switch */
    VTSS_TARGET_JAGUAR_2           = 0x7468,  /**< Jaguar-2 CE switch */
    VTSS_TARGET_SERVAL_T           = 0x7410,  /**< Serval-T switch */
    VTSS_TARGET_SERVAL_TP          = 0x7415,  /**< Serval-TP switch */
    VTSS_TARGET_SERVAL_TE          = 0x7430,  /**< Serval-TE switch */
    VTSS_TARGET_SERVAL_TEP         = 0x7435,  /**< Serval-TEP switch */
    VTSS_TARGET_SERVAL_2_LITE      = 0x7436,  /**< Serval-2 Lite switch */
    VTSS_TARGET_SERVAL_TE10        = 0x7437,  /**< Serval-TE10 switch */
    VTSS_TARGET_SPARX_IV_34        = 0x7440,  /**< Sparx-IV-34 switch */
    VTSS_TARGET_7511               = 0x7511,  /**< VSC7511 unmanaged switch */
    VTSS_TARGET_7512               = 0x7512,  /**< VSC7512 unmanaged switch */
    VTSS_TARGET_7513               = 0x7513,  /**< VSC7513 switch */
    VTSS_TARGET_7514               = 0x7514,  /**< VSC7514 switch */
    VTSS_TARGET_7546               = 0x7546,  /**< SparX-5-64  Enterprise Switch */
    VTSS_TARGET_7549               = 0x7549,  /**< SparX-5-90  Enterprise Switch */
    VTSS_TARGET_7552               = 0x7552,  /**< SparX-5-128 Enterprise Switch */
    VTSS_TARGET_7556               = 0x7556,  /**< SparX-5-160 Enterprise Switch */
    VTSS_TARGET_7558               = 0x7558,  /**< SparX-5-200 Enterprise Switch */
    VTSS_TARGET_7546TSN            = 0x47546, /**< SparX-5-64i Industrial Switch */
    VTSS_TARGET_7549TSN            = 0x47549, /**< SparX-5-90i Industrial Switch */
    VTSS_TARGET_7552TSN            = 0x47552, /**< SparX-5-128i Industrial Switch */
    VTSS_TARGET_7556TSN            = 0x47556, /**< SparX-5-160i Industrial Switch */
    VTSS_TARGET_7558TSN            = 0x47558, /**< SparX-5-200i Industrial Switch */
    VTSS_TARGET_LAN9662            = 0x9662,  /**< LAN9662 switch */
    VTSS_TARGET_LAN9668            = 0x9668,  /**< LAN9668 switch */
} vtss_target_type_t;

/** \brief Create structure */
typedef struct {
    vtss_target_type_t target; /**< Target type */
} vtss_inst_create_t;

/**
 * \brief Initialize create structure for target.
 *
 * \param target [IN] Target name
 * \param create [IN] Create structure
 *
 * \return Return code.
 **/
vtss_rc vtss_inst_get(const vtss_target_type_t target,
                      vtss_inst_create_t       *const create);

/**
 * \brief Create target instance.
 *
 * \param create [IN] Create structure
 * \param inst [OUT]  Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_inst_create(const vtss_inst_create_t *const create,
                         vtss_inst_t              *const inst);

/**
 * \brief Destroy target instance.
 *
 * \param inst [IN] Target instance reference.
 *
 * \return Return code.
 **/
vtss_rc vtss_inst_destroy(const vtss_inst_t inst);

/**
 * \brief Register read function
 *
 * \param chip_no [IN] Chip number, for targets with multiple chips
 * \param addr [IN]    Register address
 * \param value [OUT]  Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_reg_read_t)(const vtss_chip_no_t chip_no,
                                   const u32            addr,
                                   u32                  *const value);

/**
 * \brief Register write function
 *
 * \param chip_no [IN] Chip number, for targets with multiple chips
 * \param addr [IN]    Register address
 * \param value [IN]   Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_reg_write_t)(const vtss_chip_no_t chip_no,
                                  const u32            addr,
                                  const u32            value);


/**
 * \brief I2C read function
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param addr [IN]   Register address
 * \param data [OUT]  Pointer the register(s) data value.
 * \param cnt [IN]    Number of registers to read
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_i2c_read_t)(const vtss_port_no_t port_no,
                                   const u8 i2c_addr,
                                   const u8 addr,
                                   u8 *const data,
                                   const u8 cnt);

/**
 * \brief I2C write function
 *
 * \param port_no [IN] Port number
 * \param i2c_addr [IN] I2C device address
 * \param data [OUT]  Pointer the data to be written.
 * \param cnt [IN]    Number of data bytes to write
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_i2c_write_t)(const vtss_port_no_t port_no,
                                    const u8 i2c_addr,
                                    u8 *const data,
                                    const u8 cnt);

#if defined(VTSS_FEATURE_CLOCK)
/**
 * \brief Register read function for clock chip
 *
 * \param addr  [IN]  Register address
 * \param value [OUT] Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_clock_read_t)(const u32 addr, u32 *const value);
#endif /* VTSS_FEATURE_CLOCK */

#if defined(VTSS_FEATURE_CLOCK)
/**
 * \brief Register write function for clock chip
 *
 * \param addr  [IN] Register address
 * \param value [IN] Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_clock_write_t)(const u32 addr, const u32 value);
#endif /* VTSS_FEATURE_CLOCK */

/**
 * \brief SPI read/write function
 *
 * \param inst [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param bitsize [IN] Size (in bytes) of bitstream following this parameter.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_read_write_t)(const vtss_inst_t inst,
                                       const vtss_port_no_t port_no,
                                       const u8 bitsize,
                                       u8 *const bitstream);

/**
 * \brief SPI 32 bit read/write function
 *
 * \param inst    [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param read    [IN] Read/Write.
 * \param dev     [IN] MMD device number.
 * \param reg_num [IN] Register offset.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_32bit_read_write_t)(const vtss_inst_t inst,
                                               vtss_port_no_t port_no,
                                               BOOL           read,
                                               u8             dev,
                                               u16            reg_num,
                                               u32            *const data);

/**
 * \brief SPI 64 bit read/write function
 *
 * \param inst    [IN] Vitesse API instance.
 * \param port_no [IN] Port number.
 * \param read    [IN] Read/Write.
 * \param dev     [IN] MMD device number.
 * \param reg_num [IN] Register offset.
 * \param data [IN|OUT] Pointer to the data to be written to SPI Slave, if doing write operation.
 *                      Pointer to the data read from SPI Slave, if doing read operation.
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_spi_64bit_read_write_t)(const vtss_inst_t inst,
                                               vtss_port_no_t port_no,
                                               BOOL           read,
                                               u8             dev,
                                               u16            reg_num,
                                               u64            *const data);

/**
 * \brief MII management read function (IEEE 802.3 clause 22)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param addr [IN]    Register address (0-31)
 * \param value [OUT]  Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_miim_read_t)(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    const u8             addr,
                                    u16                  *const value);

/**
 * \brief MII management write function (IEEE 802.3 clause 22)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param addr [IN]    Register address (0-31)
 * \param value [IN]   Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_miim_write_t)(const vtss_inst_t    inst,
                                     const vtss_port_no_t port_no,
                                     const u8             addr,
                                     const u16            value);

/**
 * \brief MMD management read function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Register address (0-65535)
 * \param value [OUT]  Register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_read_t)(const vtss_inst_t    inst,
                                   const vtss_port_no_t port_no,
                                   const u8             mmd,
                                   const u16            addr,
                                   u16                  *const value);

/**
 * \brief MMD management read increment function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Start register address (0-65535)
 * \param buf [OUT]    The register values (pointer provided by user)
 * \param count [IN]   Number of register reads (increment register reads)
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_read_inc_t)(const vtss_inst_t    inst,
                                       const vtss_port_no_t port_no,
                                       const u8             mmd,
                                       const u16            addr,
                                       u16                  *const buf,
                                       u8                   count);

/**
 * \brief MMD management write function (IEEE 802.3 clause 45)
 *
 * \param inst [IN]    Target instance reference.
 * \param port_no [IN] Port number
 * \param mmd [IN]     MMD address (0-31)
 * \param addr [IN]    Start register address (0-65535)
 * \param buf [IN]     The register value
 *
 * \return Return code.
 **/
typedef vtss_rc (*vtss_mmd_write_t)(const vtss_inst_t    inst,
                                    const vtss_port_no_t port_no,
                                    const u8             mmd,
                                    const u16            addr,
                                    const u16            value);

/** \brief PI data width */
typedef enum {
    VTSS_PI_WIDTH_16 = 0, /* 16 bit (default) */
    VTSS_PI_WIDTH_8       /* 8 bit */
} vtss_pi_width_t;

/** \brief PI configuration */
typedef struct {
#if defined(VTSS_ARCH_LUTON26)
    vtss_pi_width_t width;                  /**< Width */
    BOOL            use_extended_bus_cycle; /**< Use extended bus cycle for slow registers */
#endif /* VTSS_ARCH_LUTON26 */
    u32             cs_wait_ns;             /**< Minimum CS wait time in nanoseconds */
} vtss_pi_conf_t;

#if defined(VTSS_FEATURE_PORT_MUX)
/** \brief Port mux configuration */
typedef enum {
#if defined(VTSS_ARCH_LUTON26)
    VTSS_PORT_MUX_MODE_0,       /**< Ports muxed to Serdes blocks: 3xQSGMII, 1x2G5, 1xSGMII */
    VTSS_PORT_MUX_MODE_1,       /**< Ports muxed to Serdes blocks: 2x2G5, 10xSGMII          */
    VTSS_PORT_MUX_MODE_2,       /**< Ports muxed to Serdes blocks: 2xQSGMII, 8xSGMII         */
#endif /* VTSS_ARCH_LUTON26 */
#if defined(VTSS_ARCH_JAGUAR_2)
    VTSS_PORT_MUX_MODE_AUTO,    /**< Port mux mode autodetected (not possible for speeds close to 80Gb (aggregated)) */
    VTSS_PORT_MUX_MODE_0,       /**< Ports muxed to Serdes blocks: 24x2G5, 4x10Gb, NPI, chip ports 8-23,48-53 */
    VTSS_PORT_MUX_MODE_1,       /**< Ports muxed to Serdes blocks: 32x2G5, 2x10Gb, NPI, chip ports 8-31,48-50 */
    VTSS_PORT_MUX_MODE_2,       /**< Supports 48x1G + 4x10G + NPI (JR2-RevC) */
#endif /* VTSS_ARCH_JAGUAR_2 */
#if defined(VTSS_ARCH_OCELOT)
    VTSS_PORT_MUX_MODE_0, /**< Conf:2 4x1G Dual + 2x1G SGMII + 2.5G NPI (+ 2x2.5G SGMII for VSC7514) */
    VTSS_PORT_MUX_MODE_1, /**< Conf:b 4x1G Dual + 2x1G SGMII + PCIe (+ 2x2.5G SGMII for VSC7514) */
    VTSS_PORT_MUX_MODE_2, /**< Conf:0 4x1G Dual + 1xQSGMII + 2.5G NPI (+ 1x1G SGMII + 1x2.5G SGMII for VSC7514) */
    VTSS_PORT_MUX_MODE_3, /**< Conf:c 4x1G Dual + 1xQSGMII + PCIe (+ 1x1G SGMII + 1x2.5G SGMII for VSC7514) */
    VTSS_PORT_MUX_MODE_4, /**< Conf:e 2x1G Dual + 2x1G CuPHY + 4x1G SGMII + 2x2.5G SGMII + 2.5G NPI */
    VTSS_PORT_MUX_MODE_5, /**< Conf:f 2x1G Dual + 2x1G CuPHY + 4x1G SGMII + 2x2.5G SGMII + PCIe */
#endif  /* VTSS_ARCH_OCELOT */
#if defined(VTSS_ARCH_LAN966X)
    VTSS_PORT_MUX_MODE_0, /**< 2xQSGMII (LAN9668) */
    VTSS_PORT_MUX_MODE_1, /**< 2xCu + 2x2.5G (+ 1xQSGMII for LAN9668) */
    VTSS_PORT_MUX_MODE_2, /**< 2xCu + 1x2.5G + 2xRGMII */
    VTSS_PORT_MUX_MODE_3, /**< Not currently used */
    VTSS_PORT_MUX_MODE_4, /**< Not currently used */
    VTSS_PORT_MUX_MODE_5, /**< 2xCu + 3x1G (LAN9668) */
#endif
} vtss_port_mux_mode_t;
#endif /* VTSS_FEATURE_PORT_MUX */

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
/** \brief Serdes fields */
typedef struct {
    u32        ob_post0;                  /**< Trace length */
    u32        ob_sr;                     /**< Slew Rate */
} vtss_serdes_fields_t;

/** \brief Backward compatibility */
typedef vtss_serdes_fields_t serdes_fields_t;

/** \brief Serdes macro configuration */
typedef struct {
    vtss_vdd_t           serdes1g_vdd; /**< Serdes1g supply */
    vtss_vdd_t           serdes6g_vdd; /**< Serdes6g supply */
    BOOL                 ib_cterm_ena; /**< AC(0)/DC(1) coupled */
    vtss_serdes_fields_t qsgmii;       /**< Appl/Board specific fields for QSGMII */
} vtss_serdes_macro_conf_t;
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

#if defined(VTSS_FEATURE_WARM_START)
/** \brief Restart information source */
typedef enum {
    VTSS_RESTART_INFO_SRC_NONE,   /* Restart information not stored in PHYs */
    VTSS_RESTART_INFO_SRC_CU_PHY, /* Restart information stored in 1G PHY */
    VTSS_RESTART_INFO_SRC_10G_PHY /* Restart information stored in 10G PHY */
} vtss_restart_info_src_t;
#endif /* VTSS_FEATURE_WARM_START */

#if defined(VTSS_ARCH_JAGUAR_2_CE)
/** \brief Queue System modes */
typedef enum {
    VTSS_QS_MODE_DEFAULT,   /**< Defaults settings are used */
    VTSS_QS_MODE_QUEUE_LIM  /**< Queue Limitiation settings are enabled. */
} vtss_qs_mode_t;

/** \brief Queue System settings */
typedef struct {
    vtss_qs_mode_t mode;   /**< The mode of the queue system   */
    u32            wm1;    /**< Generic Watermark parameter 1  */
    u32            wm2;    /**< Generic Watermark parameter 2  */
} vtss_qs_conf_t;
#endif /* VTSS_ARCH_JAGUAR_2_CE */

#if defined(VTSS_FEATURE_CORE_CLOCK)
/** \brief Core clock frequency */
typedef enum {
    VTSS_CORE_CLOCK_DEFAULT,  /**< Defaults to the highest supported frequency */
    VTSS_CORE_CLOCK_250MHZ,   /**< 250MHZ core clock frequency */
    VTSS_CORE_CLOCK_500MHZ,   /**< 500MHZ core clock frequency */
    VTSS_CORE_CLOCK_625MHZ,   /**< 625MHZ core clock frequency */
} vtss_core_clock_freq_t;

/** \brief Core clock configuration */
typedef struct {
    vtss_core_clock_freq_t freq;   /**< The frequency of the core clock (LC-PLL) */
} vtss_core_clock_conf_t;
#endif /* VTSS_FEATURE_CORE_CLOCK */

/** \brief Initialization configuration. */
typedef struct {
    /* Register access function are not used for VTSS_TARGET_CU_PHY */
    vtss_reg_read_t   reg_read;     /**< Register read function */
    vtss_reg_write_t  reg_write;    /**< Register write function */

#if defined(VTSS_FEATURE_CLOCK)
    vtss_clock_read_t  clock_read;  /**< Clock-chip read function  */
    vtss_clock_write_t clock_write; /**< Clock-chip write function */
#endif /* VTSS_FEATURE_CLOCK */

    /* MII management access must be setup for VTSS_TARGET_CU_PHY */
    vtss_miim_read_t  miim_read;    /**< MII management read function */
    vtss_miim_write_t miim_write;   /**< MII management write function */

    /* MMD management access must be setup for 10G phys */
    vtss_mmd_read_t     mmd_read;     /**< MMD management read function */
    vtss_mmd_read_inc_t mmd_read_inc; /**< MMD management read increment function */
    vtss_mmd_write_t    mmd_write;    /**< MMD management write function */

    vtss_spi_read_write_t   spi_read_write;/**< Board specific SPI read/write callout function */

    vtss_spi_32bit_read_write_t   spi_32bit_read_write;/**< Board specific SPI read/write callout function for 32 bit data */
    vtss_spi_64bit_read_write_t   spi_64bit_read_write;/**< Board specific SPI read/write callout function for 64 bit data*/

#if defined(VTSS_GPIOS)
    vtss_gpio_func_info_get_t gpio_func_info_get;       /**< GPIO functionallity information get callout function */
#endif

    vtss_port_serdes_tap_get_t serdes_tap_get;  /**< Serdes tap get callout function */

    /** Do not reset the switch core when calling vtss_init_conf_set. This
     * assumes someone else is doing the reset.
     *
     * NOTE: Only the JR2 family supports resetting. This setting has no effect
     * on non-JR2 designs. */
    BOOL                    skip_switch_reset;

    BOOL                    spi_bus;           /**< Using SPI bus interface for reg_read/reg_write */
#if defined(VTSS_FEATURE_WARM_START)
    BOOL                    warm_start_enable; /**< Allow warm start */
    vtss_restart_info_src_t restart_info_src;  /**< Source of restart information */
    vtss_port_no_t          restart_info_port; /**< Port used to store PHY restart information */
#endif /* VTSS_FEATURE_WARM_START */

#if defined(VTSS_FEATURE_PORT_MUX)
    vtss_port_mux_mode_t mux_mode;         /**< Mux mode (port connection to Serdes Macroes) */
#endif /* VTSS_FEATURE_PORT_MUX */

    vtss_pi_conf_t    pi;           /**< Parallel Interface configuration */

#if defined(VTSS_FEATURE_SERDES_MACRO_SETTINGS)
    vtss_serdes_macro_conf_t serdes; /**< Serdes macro configuration */
#endif /* VTSS_FEATURE_SERDES_MACRO_SETTINGS */

    BOOL using_ufdma; /**< Set to TRUE if using the uFDMA driver to Rx and Tx frames (typically used under Linux) */

    /**
     * Reserve bandwidth for Up-MEPs and service activation tests.
     * Example: To get support for 10Gbps Y.1564, set loopback_bw_mbps
     * to 10000.
     */
    u32 loopback_bw_mbps;

#if defined(VTSS_ARCH_JAGUAR_2_CE)
    vtss_qs_conf_t      qs_conf; /**< Queue system configuration*/
#endif /* VTSS_ARCH_JAGUAR_2_CE */

#if defined(VTSS_FEATURE_VLAN_COUNTERS)
    BOOL vlan_counters_disable; /**< Disable VLAN counters (OAM uses the counter resources) */
#endif
#if defined(VTSS_FEATURE_PSFP)
    BOOL psfp_counters_enable;  /**< Enable PSFP counter mode for ingress counters */
#endif
#if defined(VTSS_FEATURE_CORE_CLOCK)
    vtss_core_clock_conf_t core_clock; /**< Core clock (LCPLL) configuration */
#endif
#if defined(VTSS_ARCH_LUTON26)
    BOOL packet_init_disable; /**< Skip initilization of packet interface (no CPU packet support, L26/MESA-354/BZ24450) */
#endif
} vtss_init_conf_t;

/**
 * \brief Get default initialization configuration
 *
 * \param inst [IN]  Target instance reference
 * \param conf [OUT] Initialization configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_init_conf_get(const vtss_inst_t inst,
                           vtss_init_conf_t  *const conf);

/**
 * \brief Set initialization configuration.
 *
 * \param inst [IN] Target instance reference
 * \param conf [IN] Initialization configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_init_conf_set(const vtss_inst_t      inst,
                           const vtss_init_conf_t *const conf);

/**
 * \brief Change access interface to either use SPI or another interface.
 *
 * Registers in the VCore register space are not directly accessible when using
 * the SPI interface, so multiple chip-accesses are required in order to read
 * and write registers in that space when using SPI, whereas such registers are
 * directly accessible when using PCI-E or the internal CPU.
 *
 * When this function is invoked with \p spi_bus set to TRUE, the API will
 * detect register accesses to the VCore register space and make the required
 * indirect access through multiple calls to the application-installed register
 * read/write functions.
 *
 * When \p spi_bus is set to FALSE, the API will perform any type of access in
 * one single call to the application-installed register read/write functions.
 *
 * Normally, you will control the access mode once at API instantiation time
 * through the vtss_init_conf_t::spi_bus member, but in certain applications
 * it might be desirable to be able to change it dynamically - hence this
 * function.
 *
 * \param inst    [IN] Target instance reference
 * \param spi_bus [IN] Control the access mode.
 *
 * \return Return code.
 */
vtss_rc vtss_register_access_mode_set(const vtss_inst_t inst, BOOL spi_bus);

/**
 * \brief Get current way of accessing registers.
 *
 * See vtss_register_access_mode_set() for details.
 *
 * \param inst    [IN]  Target instance reference
 * \param spi_bus [OUT] Pointer to a BOOL receiving current access mode.
 *
 * \return Return code.
 */
vtss_rc vtss_register_access_mode_get(const vtss_inst_t inst, BOOL *spi_bus);

/** \brief SPI slave endian configuration */
typedef enum {
    VTSS_SPI_ENDIAN_LITTLE, /**< Use little endian */
    VTSS_SPI_ENDIAN_BIG,    /**< Use big endian */
} vtss_spi_endian_t;

/** \brief SPI slave bit order configuration */
typedef enum {
    VTSS_SPI_BIT_ORDER_MSB_FIRST, /**< Transfer MSB first */
    VTSS_SPI_BIT_ORDER_LSB_FIRST, /**< Transfer LSB first */
} vtss_spi_bit_order_t;

/** \brief SPI slave initialization configuration. */
typedef struct {
    vtss_reg_write_t     reg_write; /**< Register write function */
    vtss_reg_read_t      reg_read;  /**< Register read function */
    vtss_spi_endian_t    endian;    /**< Endian configuration */
    vtss_spi_bit_order_t bit_order; /**< Bit order configuration */
    u8                   padding;   /**< Number of padding bytes to insert before read-data is shifted out */
} vtss_spi_slave_init_t;

/**
 * \brief Initialize SPI slave interface when using an external CPU.
 * This must always be the first call into the API.
 *
 * \param conf [IN] Initialization configuration
 *
 * \return Return code.
 **/
vtss_rc vtss_spi_slave_init(const vtss_spi_slave_init_t *const conf);

#if defined(VTSS_FEATURE_WARM_START)
/**
 * \brief Indicate configuration end.
 * If a warm start has been done, the stored configuration will be applied.
 *
 * \param inst [IN] Target instance reference
 *
 * \return Return code.
 **/
vtss_rc vtss_restart_conf_end(const vtss_inst_t inst);

/** \brief API version */
typedef u16 vtss_version_t;

/** \brief Restart type */
typedef enum {
    VTSS_RESTART_COLD, /**< Cold: Chip and CPU restart, e.g. power cycling */
    VTSS_RESTART_COOL, /**< Cool: Chip and CPU restart done by CPU */
    VTSS_RESTART_WARM  /**< Warm: CPU restart only */
} vtss_restart_t;

/** \brief Restart status */
typedef struct {
    vtss_restart_t restart;      /**< Previous restart mode */
    vtss_version_t prev_version; /**< Previous API version */
    vtss_version_t cur_version;  /**< Current API version */
} vtss_restart_status_t;

/**
 * \brief Get restart status
 *
 * \param inst [IN]    Target instance reference
 * \param status [OUT] Restart status
 *
 * \return Return code.
 **/
vtss_rc vtss_restart_status_get(const vtss_inst_t inst,
                                vtss_restart_status_t *const status);

/**
 * \brief Get restart configuration (next restart mode)
 *
 * \param inst [IN]     Target instance reference
 * \param restart [OUT] Restart mode
 *
 * \return Return code.
 **/
vtss_rc vtss_restart_conf_get(const vtss_inst_t inst,
                              vtss_restart_t *const restart);

/**
 * \brief Set restart configuration (next restart mode)
 *
 * \param inst [IN]    Target instance reference
 * \param restart [IN] Restart mode
 *
 * \return Return code.
 **/
vtss_rc vtss_restart_conf_set(const vtss_inst_t inst,
                              const vtss_restart_t restart);

#endif /* VTSS_FEATURE_WARM_START */

#ifdef __cplusplus
}
#endif
#endif /* _VTSS_INIT_API_H_ */
