// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MICROCHIP_ETHERNET_BOARD_SYNCE_H_
#define _MICROCHIP_ETHERNET_BOARD_SYNCE_H_

#include <stdint.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/types.h>
#include <microchip/ethernet/board/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// The purpose of the MEBA_SYNCE API is to allow board designers to describe how
// the different clock sources are connected to the DPLL. The synce application
// uses this information to setup the board accordingly to the applied
// configuration.
//
// A clock source is either being derived from a port (copper or SFP) or
// provided as a direct clock input.
//
// It is common for a PHY to support many ports, but they may not provide the
// same number of clock outputs as the number of ports they support. It is also
// common for many boards to include CPLDs or other HW to "route" the clock
// signal from the clock source to the DPLL. This is being modeled as a MUX in
// the board API.
//
// Different MUXes have different ownership, but they must all be included in
// the graph to allow the synce application to calculate how it can utilize the
// boards facilities to provide the required functionality. The board API can
// only apply the configuration for MUXes of type MEBA_SYNCE_DEV_TYPE_MUX_BOARD,
// other APIs is provided to update the remaining MUXes.
//
// Normally a MUX is "fully-connected" meaning that all inputs may be connected
// to all outputs, but in rare circumstance then certain configurations is not
// allowed. To express such exceptions the
// MEBA_SYNCE_GRAPH_ELEMENT_TYPE_INVALID_CONF type must be used.
//
// The MEBA_SYNCE API provide the date-structures for board designers to
// describe this in a formal way. The information is then exposed by the
// meba_synce_graph_get function.

#define MESA_SYNCE_DEV_INPUT             0x80000000
#define MESA_SYNCE_TRI_STATE_FROM_SWITCH 0x40000000
#define MESA_SYNCE_TRI_STATE_FROM_PHY    0x20000000

#define MESA_SYNCE_ARG_1_3(a, b, c, ...) a, b, c
#define MESA_SYNCE_ARG_4_6(a, b, c, d, e, f, ...) d, e, f

#define MESA_SYNCE_ATTR_(dev_type, dev_id, dev_idx, type, val) \
        {dev_id, dev_idx, type, val}
#define MESA_SYNCE_ATTR(...) MESA_SYNCE_ATTR_(__VA_ARGS__)

#define MESA_SYNCE_DEV_PORT(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_PORT, dev_id, idx

#define MESA_SYNCE_DEV_CLOCK_IN(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_CLOCK_IN, dev_id, idx

#define MESA_SYNCE_DEV_DIVIDER(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_DIVIDER, dev_id, idx

#define MESA_SYNCE_DEV_MUX_PHY(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_MUX_PHY, dev_id, idx

#define MESA_SYNCE_DEV_MUX_SWITCH(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_MUX_SWITCH, dev_id, idx

#define MESA_SYNCE_DEV_MUX_BOARD(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_MUX_BOARD, dev_id, idx

#define MESA_SYNCE_DEV_DPLL(dev_id, idx) \
        MEBA_SYNCE_DEV_TYPE_DPLL, dev_id, idx

#define MESA_SYNCE_GRAPH_CONNECTION(...) \
    {MEBA_SYNCE_GRAPH_ELEMENT_TYPE_CONNECTION, \
     {MESA_SYNCE_ARG_1_3(__VA_ARGS__)} , \
     {MESA_SYNCE_ARG_4_6(__VA_ARGS__)} }

#define MESA_SYNCE_GRAPH_INVALID_CONNECTION(...) \
    {MEBA_SYNCE_GRAPH_ELEMENT_TYPE_INVALID_CONF, \
     {MESA_SYNCE_ARG_1_3(__VA_ARGS__)} , \
     {MESA_SYNCE_ARG_4_6(__VA_ARGS__)} }

typedef enum {
    MEBA_SYNCE_CLOCK_FREQ_INVALID = -1,
    MEBA_SYNCE_CLOCK_FREQ_UNKNOWN = 0,
    MEBA_SYNCE_CLOCK_FREQ_25MHZ,
    MEBA_SYNCE_CLOCK_FREQ_31_25MHZ,
    MEBA_SYNCE_CLOCK_FREQ_32_226MHZ,   // 32.2265625 Mhz
    MEBA_SYNCE_CLOCK_FREQ_39_062MHZ,
    MEBA_SYNCE_CLOCK_FREQ_40_283MHZ,
    MEBA_SYNCE_CLOCK_FREQ_60_606MHZ,
    MEBA_SYNCE_CLOCK_FREQ_62_5MHZ,
    MEBA_SYNCE_CLOCK_FREQ_78_125MHZ,
    MEBA_SYNCE_CLOCK_FREQ_80_565MHZ,   // 80.5664062 Mhz
    MEBA_SYNCE_CLOCK_FREQ_125MHZ,
    MEBA_SYNCE_CLOCK_FREQ_156_25MHZ,
    MEBA_SYNCE_CLOCK_FREQ_161_13MHZ,
    MEBA_SYNCE_CLOCK_FREQ_312_5MHZ,
    MEBA_SYNCE_CLOCK_FREQ_322_265MHZ,
    MEBA_SYNCE_CLOCK_FREQ_644_53MHZ,
    MEBA_SYNCE_CLOCK_FREQ_10MHZ,
    MEBA_SYNCE_CLOCK_FREQ_1544_KHZ,    // 1544 KHz
    MEBA_SYNCE_CLOCK_FREQ_2048_KHZ     // 2048 KHz
} meba_synce_clock_frequency_t;

// Enumeration of the different devices used to connect the clock sources to
// the DPLL.
typedef enum {
    // A port (SFP or Cu). A valid 'start' point for a synce board graph.
    MEBA_SYNCE_DEV_TYPE_PORT,

    // A direct clock input. A valid 'start' point for a synce board graph.
    MEBA_SYNCE_DEV_TYPE_CLOCK_IN,

    // A divider used for breaking an edge into two segments so that each end
    // can be assigned a different frequency
    MEBA_SYNCE_DEV_TYPE_DIVIDER,

    // A DPLL, all 'clock' connections should end in a DPLL.
    MEBA_SYNCE_DEV_TYPE_DPLL,

    // A mux embedded in a PHY.
    MEBA_SYNCE_DEV_TYPE_MUX_PHY,

    // A mux controlled/owned by the board.
    MEBA_SYNCE_DEV_TYPE_MUX_BOARD,

    // A mux embedded in the switch.
    MEBA_SYNCE_DEV_TYPE_MUX_SWITCH,

    // This value is for code to be able to determine the number of values
    // implemented in the enum type.
    MEBA_SYNCE_DEV_TYPE_SIZE

} meba_sync_dev_type_t;

// An input or output on one of the nodes in the graph.
typedef struct {
    // Node type
    meba_sync_dev_type_t type;

    // Node ID. This ID is used as a unique identifier of the node, through
    // the entire graph.
    uint32_t             dev_id;

    // In/out identifier local to the node. A given MUX/DPLL have a number of
    // in/out terminals, which are identified by this index.
    // Must be zero for PORTS
    // TODO, add check
    uint32_t             idx;
} meba_synce_terminal_t;

typedef enum {
    MEBA_ATTR_INVALID = 0,
    MEBA_ATTR_CLOCK_ID = 1,

    // This is the attribute to use in the general case. Typically when the
    // recovered clock is the same for more line speeds.
    MEBA_ATTR_FREQ = 2,

    // This attribute shall be used when the recovered clock for a line speed of
    // 100M is different from the general case.
    MEBA_ATTR_FREQ_100M = 3,

    // This attribute shall be used when the recovered clock for a line speed of
    // 1G is different from the general case.
    MEBA_ATTR_FREQ_1G = 4,

    // This attribute shall be used when the recovered clock for a line speed of
    // 2.5G is different from the general case.
    MEBA_ATTR_FREQ_2_5G = 5,

    // This attribute shall be used when the recovered clock for a line speed of
    // 5G is different from the general case.
    MEBA_ATTR_FREQ_5G = 6,

    // This attribute shall be used when the recovered clock for a line speed of
    // 10G is different from the general case.
    MEBA_ATTR_FREQ_10G = 7,

    // This attribute shall be used when the recovered clock for a line speed of
    // 25G is different from the general case.
    MEBA_ATTR_FREQ_25G = 8,
} meba_attr_t;

// Structure representing an attribute attached to a terminal in the SyncE graph
typedef struct {
    // Device ID of the terminal to which the attribute applies.
    uint32_t             dev_id;

    // Index of the terminal to which the attribute applies.
    uint32_t             idx;

    // The type of the attribute
    meba_attr_t          type;

    // The value of the attribute
    uint32_t             value;
} meba_synce_terminal_attr_t;

// Graph element type.
typedef enum {
    // An edge (connection) in the graph. When using this type, the src.dev_id
    // and dst.dev_id must be different.
    MEBA_SYNCE_GRAPH_ELEMENT_TYPE_CONNECTION,

    // An invalid configuration. Certain MUXes are not fully connected.
    MEBA_SYNCE_GRAPH_ELEMENT_TYPE_INVALID_CONF

} meba_synce_graph_element_type_t;

// An element in the graph (normally a edge).
typedef struct {
    // Element type.
    meba_synce_graph_element_type_t type;

    // Source of edge/connection.
    meba_synce_terminal_t           src;

    // Destination of edge/connection.
    meba_synce_terminal_t           dst;

} meba_synce_graph_element_t;

// A data structure for representing the "clock" graph on the board.
typedef struct {
    // Number of elements in the graph.
    uint32_t                          graph_length;

    // Array of graph elements.
    const meba_synce_graph_element_t *graph;

    // Number of attributes
    uint32_t                          attr_length;

    // Array of attribues
    const meba_synce_terminal_attr_t *attr;
} meba_synce_graph_t;

typedef enum {
    MEBA_SYNCE_CLOCK_HW_NONE,      // NO Synce clock present
    MEBA_SYNCE_CLOCK_HW_SI_5326,   // Silabs 5326 (PCB104) clock present
    MEBA_SYNCE_CLOCK_HW_SI_5328,   // Silabs 5328 (PCB104)  clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30343,  // Zarlink ZL 30343 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30363,  // Zarlink ZL 30363 clock present
    MEBA_SYNCE_CLOCK_HW_OMEGA,     // OMEGA (ServalT) clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30771,  // Zarlink ZL 30771 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30772,  // Zarlink ZL 30772 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30773,  // Zarlink ZL 30773 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30731,  // Zarlink ZL 30731 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30732,  // Zarlink ZL 30732 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30733,  // Zarlink ZL 30733 clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30734,  // Zarlink ZL 30734clock present
    MEBA_SYNCE_CLOCK_HW_ZL_30735,  // Zarlink ZL 30735 clock present
} meba_synce_clock_hw_id_t;

typedef uint32_t meba_synce_clock_fw_ver_t;

// Get the synce clock graph for the given board instance.
// conf [OUT] The MEBA synce clock graph.
typedef mesa_rc (*meba_synce_graph_get_t)(struct meba_inst *inst,
                                          const meba_synce_graph_t **const g);

// Update the configuration of a board MUX. The MUX will be instructed to
// connect 'input' to 'output'.
//
// dev_id [IN] The device id of the (board) MUX
// input  [IN] Input id (local to the MUX).
// output [IN] Output id (local to the MUX).
typedef mesa_rc (*meba_synce_mux_set_t)(struct meba_inst *inst,
                                        uint32_t          dev_id,
                                        uint32_t          input,
                                        uint32_t          output);

// Make transfer of data on the SyncE SPI interface
// buflen       [IN] Number of bytes to transfer
// tx_data      [IN] Pointer to TX buffer
// rx_data      [IN] Pointer to RX buffer
typedef mesa_rc (*meba_synce_spi_if_spi_transfer_t)(struct meba_inst *inst,
                                                    uint32_t          buflen,
                                                    const uint8_t    *tx_data,
                                                    uint8_t          *rx_data);

// Write data to DPLL
// addr         [IN] address of first register to write
// buflen       [IN] Number of bytes to transfer
// tx_data      [IN] Pointer to TX buffer
typedef mesa_rc (*meba_synce_write_t)(struct meba_inst *inst,
                                      uint8_t           addr,
                                      uint32_t          buflen,
                                      const uint8_t    *tx_data);

// Read data from DPLL
// addr         [IN] address of first register to read
// buflen       [IN] Number of bytes to transfer
// tx_data      [IN] Pointer to RX buffer
typedef mesa_rc (*meba_synce_read_t)(struct meba_inst *inst,
                                      uint8_t          addr,
                                      uint32_t         buflen,
                                      uint8_t         *rx_data);

// Detect the type of DPLL present in the system (if any)
// dpll_type    [IN] Pointer to variable used for returning DPLL type
typedef mesa_rc (*meba_synce_spi_if_get_dpll_type_t)(
        struct meba_inst *inst,
        meba_synce_clock_hw_id_t *dpll_type);

// Find the SPI device file corresponding to a particular SPI attached device
// id           [IN] Pointer to character string holding the name of the SPI
//                   attached device
// spi_file     [IN] Pointer to variable used for returning SPI device file name
// max_size     [IN] Parameter holding the max allowed size of data returned
//                   through the buffer pointed to by spi_file
typedef mesa_rc (*meba_synce_spi_if_find_spidev_t)(struct meba_inst *inst,
                                                   const char       *id,
                                                   char             *spi_file,
                                                   size_t            max_size);


typedef mesa_rc (*meba_synce_spi_if_dpll_fw_ver_get_t)(meba_inst_t inst,
                                                       meba_synce_clock_fw_ver_t *dpll_ver);


#define MEBA_LIST_OF_API_SYNCE_CALLS   \
    X(meba_synce_graph_get)            \
    X(meba_synce_mux_set)              \
    X(meba_synce_spi_if_spi_transfer)  \
    X(meba_synce_write)                \
    X(meba_synce_read)                 \
    X(meba_synce_spi_if_get_dpll_type) \
    X(meba_synce_spi_if_find_spidev)   \
    X(meba_synce_spi_if_dpll_fw_ver_get)  \

typedef struct {
    meba_synce_graph_get_t             meba_synce_graph_get;
    meba_synce_mux_set_t               meba_synce_mux_set;
    meba_synce_spi_if_spi_transfer_t   meba_synce_spi_if_spi_transfer;
    meba_synce_write_t                 meba_synce_write;
    meba_synce_read_t                  meba_synce_read;
    meba_synce_spi_if_get_dpll_type_t  meba_synce_spi_if_get_dpll_type;
    meba_synce_spi_if_find_spidev_t    meba_synce_spi_if_find_spidev;
    meba_synce_spi_if_dpll_fw_ver_get_t meba_synce_spi_if_dpll_fw_ver_get;
} meba_api_synce_t;

#include <microchip/ethernet/board/api/hdr_end.h>
#endif // _MICROCHIP_ETHERNET_BOARD_SYNCE_H_
