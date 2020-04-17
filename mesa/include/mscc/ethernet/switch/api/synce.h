// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_ETHERNET_SWITCH_API_SYNCE_
#define _MSCC_ETHERNET_SWITCH_API_SYNCE_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

typedef uint32_t mesa_synce_clk_port_t;
#define MESA_SYNCE_CLK_A 0   /**< Clock A output port */
#define MESA_SYNCE_CLK_B 1   /**< Clock B output port */

/** \brief Identification of a Clock dividing value used when selected input clock goes to output. */
typedef enum
{
    MESA_SYNCE_DIVIDER_1,   /**< Divide input clock with one (no division) */
    MESA_SYNCE_DIVIDER_4,   /**< Divide input clock with 4 */
    MESA_SYNCE_DIVIDER_5,   /**< Divide input clock with 5 */
    MESA_SYNCE_DIVIDER_2,   /**< Divide input clock with 2 */
    MESA_SYNCE_DIVIDER_8,   /**< Divide input clock with 8 */
    MESA_SYNCE_DIVIDER_16,   /**< Divide input clock with 16 */
    MESA_SYNCE_DIVIDER_25   /**< Divide input clock with 25 */
} mesa_synce_divider_t CAP(SYNCE);

/** \brief Struct containing configuration for a recovered clock output port */
typedef struct
{
    mesa_synce_divider_t divider; /**< Selection the clock division. This should be set to MESA_SYNCE_DIVIDER_1 if recovered clock is comming from internal PHY  */
    mesa_bool_t          enable;  /**< Enable/disable of this output clock port */
} mesa_synce_clock_out_t CAP(SYNCE);

/**
 * \brief Set the configuration of a selected output clock port - against external clock controller.
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (MESA_SYNCE_CLK_A or MESA_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a mesa_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_clock_out_set(const mesa_inst_t            inst,
                                 const mesa_synce_clk_port_t  clk_port,
                                 const mesa_synce_clock_out_t *const conf)
    CAP(SYNCE);

/**
 * \brief Get the configuration of a selected output clock port - against external clock controller.
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (MESA_SYNCE_CLK_A or MESA_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a mesa_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_clock_out_get(const mesa_inst_t           inst,
                                 const mesa_synce_clk_port_t clk_port,
                                 mesa_synce_clock_out_t      *const conf)
    CAP(SYNCE);


/** \brief Identification of a clock oniut type. */
typedef enum
{
    MESA_SYNCE_CLOCK_INTERFACE,   /**< Traffic interface port */
    MESA_SYNCE_CLOCK_STATION_CLK, /**< Station clock input */
    MESA_SYNCE_CLOCK_DIFF,        /**< Differential clock input */
    MESA_SYNCE_CLOCK_AUX          /**< AUX Clock */
} mesa_synce_clock_in_type_t CAP(SYNCE_IN_TYPE);

/** \brief Struct containing configuration selecting the recovered input clock port, to be delivered to a selected output clock port */
typedef struct
{
    mesa_port_no_t             port_no; /**< Selection of the input port number - must map to a SERDES port. If clk_in is VTSS_SYNCE_CLOCK_STATION_CLK this is station clock 0->3. If clk_in is VTSS_SYNCE_CLOCK_AUX this is AUX clock 0->3. */
    mesa_bool_t                squelsh; /**< Enable/disable of automatic squelch */
    mesa_bool_t                enable;  /**< Enable/disable of delivery of recovered clock to this selected output clock port */
    mesa_synce_clock_in_type_t clk_in CAP(SYNCE_IN_TYPE); /**< Select clock input type (Traffic interface, station clock or diff clock input */
} mesa_synce_clock_in_t CAP(SYNCE);

/**
 * \brief Set the configuration of input port for a selected output clock port
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (MESA_SYNCE_CLK_A or MESA_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a mesa_synce_clock_in_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_clock_in_set(const mesa_inst_t              inst,
                                const mesa_synce_clk_port_t    clk_port,
                                const mesa_synce_clock_in_t    *const conf)
    CAP(SYNCE);

/**
 * \brief Get the configuration of input port for a selected output clock port
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (MESA_SYNCE_CLK_A or MESA_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a mesa_synce_clock_in_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_clock_in_get(const mesa_inst_t           inst,
                                const mesa_synce_clk_port_t clk_port,
                                mesa_synce_clock_in_t       *const conf)
    CAP(SYNCE);

/** \brief Struct containing configuration for a recovered clock output port */
typedef struct
{
    mesa_synce_divider_t divider;     /**< Selection the clock division. This should be set to MESA_SYNCE_DIVIDER_1 if recovered clock is comming from internal PHY  */
    mesa_bool_t          enable;      /**< Enable/disable of this output clock port */
    uint32_t             dpll_out_no; /**< The DPLL output (Synthesizer) that is connected to the station clock output */
} mesa_synce_station_clock_out_t CAP(SYNCE_OUT_STATION);

/**
 * \brief Set the configuration of a station clock output
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port
 * \param conf [IN]     pointer to a mesa_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_synce_station_clk_out_set(const mesa_inst_t                    inst,
                                             const mesa_synce_clk_port_t          clk_port,
                                             const mesa_synce_station_clock_out_t *const conf)
    CAP(SYNCE_OUT_STATION);

/**
 * \brief Get the configuration of a station clock output
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port
 * \param conf [IN]     pointer to a mesa_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
mesa_rc mesa_synce_synce_station_clk_out_get(const mesa_inst_t              inst,
                                             const mesa_synce_clk_port_t    clk_port,
                                             mesa_synce_station_clock_out_t *const conf)
    CAP(SYNCE_OUT_STATION);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_SYNCE_

