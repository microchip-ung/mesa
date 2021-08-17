// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file
 * \brief Synchronization API
 * \details This header file describes synchronization functions
 */

#ifndef _VTSS_SYNC_API_H_
#define _VTSS_SYNC_API_H_
#include "vtss/api/types.h"



// ***************************************************************************
//
//  SYNC interface
//
// ***************************************************************************

#if defined(VTSS_FEATURE_SYNCE)
#ifdef __cplusplus
extern "C" {
#endif

/** \brief Identification of a output clock port */
//typedef enum
//{
//    VTSS_SYNCE_CLK_A,   /**< Clock A output port */
//    VTSS_SYNCE_CLK_B,   /**< Clock B output port */
//} vtss_synce_clk_port_t;
typedef u32 vtss_synce_clk_port_t;
#define VTSS_SYNCE_CLK_A 0   /**< Clock A output port */
#define VTSS_SYNCE_CLK_B 1   /**< Clock B output port */
#if defined (VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
//#if defined (VTSS_ARCH_SERVAL_T)
//#define VTSS_SYNCE_CLK_MAX 2   /**< Number of recovered clock outputs is 2 in ServalT*/
//#else
#define VTSS_SYNCE_CLK_MAX 4   /**< Number of recovered clock outputs is 4 in other Jagyar2 variants , serval-t case RCVRD_CLK_3 is used*/
//#endif // (VTSS_ARCH_SERVAL_T)
#else
#define VTSS_SYNCE_CLK_MAX 2   /**< Number of recovered clock outputs */
#endif

/** \brief Identification of a Clock dividing value used when selected input clock goes to output. */
typedef enum
{
    VTSS_SYNCE_DIVIDER_1,   /**< Divide input clock with one (no division) */
    VTSS_SYNCE_DIVIDER_4,   /**< Divide input clock with 4 */
    VTSS_SYNCE_DIVIDER_5,   /**< Divide input clock with 5 */
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LAN969X)
    VTSS_SYNCE_DIVIDER_2,   /**< Divide input clock with 2 */
    VTSS_SYNCE_DIVIDER_8,   /**< Divide input clock with 8 */
    VTSS_SYNCE_DIVIDER_16,   /**< Divide input clock with 16 */
    VTSS_SYNCE_DIVIDER_25   /**< Divide input clock with 25 */
#endif
} vtss_synce_divider_t;

/** \brief Struct containing configuration for a recovered clock output port */
typedef struct
{
    vtss_synce_divider_t    divider;    /**< Selection the clock division. This should be set to VTSS_SYNCE_DIVIDER_1 if recovered clock is comming from internal PHY  */
    BOOL                    enable;     /**< Enable/disable of this output clock port */
} vtss_synce_clock_out_t;

/**
 * \brief Set the configuration of a selected output clock port - against external clock controller.
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (VTSS_SYNCE_CLK_A or VTSS_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a vtss_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_clock_out_set(const vtss_inst_t              inst,
                                 const vtss_synce_clk_port_t    clk_port,
                                 const vtss_synce_clock_out_t   *const conf);

/**
 * \brief Get the configuration of a selected output clock port - against external clock controller.
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (VTSS_SYNCE_CLK_A or VTSS_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a vtss_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_clock_out_get(const vtss_inst_t           inst,
                                 const vtss_synce_clk_port_t clk_port,
                                 vtss_synce_clock_out_t      *const conf);


#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
/** \brief Identification of a clock oniut type. */
typedef enum
{
    VTSS_SYNCE_CLOCK_INTERFACE,   /**< Traffic interface port */
#if defined(VTSS_ARCH_SERVAL_T)
    VTSS_SYNCE_CLOCK_STATION_CLK, /**< Station clock input */
    VTSS_SYNCE_CLOCK_DIFF         /**< Differential clock input */
#endif
#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
    VTSS_SYNCE_CLOCK_AUX          /**< AUX Clock */
#endif
} vtss_synce_clock_in_type_t;
#endif


/** \brief Struct containing configuration selecting the recovered input clock port, to be delivered to a selected output clock port */
typedef struct
{
    vtss_port_no_t              port_no;    /**< Selection of the input port number - must map to a SERDES port. If clk_in is VTSS_SYNCE_CLOCK_STATION_CLK this is station clock 0->3. If clk_in is VTSS_SYNCE_CLOCK_AUX this is AUX clock 0->3. */
    BOOL                        squelsh;    /**< Enable/disable of automatic squelch */
    BOOL                        enable;     /**< Enable/disable of delivery of recovered clock to this selected output clock port */
#if defined (VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
    vtss_synce_clock_in_type_t  clk_in;     /**< Select clock input type (Traffic interface, station clock, differential clock input or AUX clock */
#endif
} vtss_synce_clock_in_t;

/**
 * \brief Set the configuration of input port for a selected output clock port
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (VTSS_SYNCE_CLK_A or VTSS_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a vtss_synce_clock_in_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_clock_in_set(const vtss_inst_t              inst,
                                const vtss_synce_clk_port_t    clk_port,
                                const vtss_synce_clock_in_t    *const conf);

/**
 * \brief Get the configuration of input port for a selected output clock port
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port (VTSS_SYNCE_CLK_A or VTSS_SYNCE_CLK_B)
 * \param conf [IN]     pointer to a vtss_synce_clock_in_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_clock_in_get(const vtss_inst_t            inst,
                                const vtss_synce_clk_port_t  clk_port,
                                vtss_synce_clock_in_t        *const conf);

/** \brief Struct containing configuration for a recovered clock output port */
typedef struct
{
    vtss_synce_divider_t    divider;    /**< Selection the clock division. This should be set to VTSS_SYNCE_DIVIDER_1 if recovered clock is comming from internal PHY  */
    BOOL                    enable;     /**< Enable/disable of this output clock port */
    u32                    dpll_out_no;/**< The DPLL output (Synthesizer) that is connected to the station clock output */
} vtss_synce_station_clock_out_t;

/**
 * \brief Set the configuration of a station clock output 
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port
 * \param conf [IN]     pointer to a vtss_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_synce_station_clk_out_set(const vtss_inst_t              inst,
        const vtss_synce_clk_port_t    clk_port,
        const vtss_synce_station_clock_out_t   *const conf);

#if defined(VTSS_ARCH_SERVAL_T)     /* TBD_henrikb */
/**
 * \brief Get the configuration of a station clock output
 * \param inst [IN]     handle to an API instance.
 * \param clk_port [IN] Selection of the output clock port
 * \param conf [IN]     pointer to a vtss_synce_clock_out_t configuration structure.
 *
 * \return Return code.
 */
vtss_rc vtss_synce_synce_station_clk_out_get(const vtss_inst_t            inst,
        const vtss_synce_clk_port_t  clk_port,
        vtss_synce_station_clock_out_t       *const conf);
#endif //VTSS_ARCH_SERVAL_T

#ifdef __cplusplus
}
#endif
#endif /* VTSS_FEATURE_SYNCE */
#endif // _VTSS_SYNC_API_H_

// ***************************************************************************
//
//  End of file.
//
// ***************************************************************************
