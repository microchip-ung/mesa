// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MICROCHIP_ETHERNET_BOARD_CPU_PORT_H_
#define _MICROCHIP_ETHERNET_BOARD_CPU_PORT_H_

#include <stdint.h>
#include <microchip/ethernet/switch/api.h>
#include <microchip/ethernet/board/api/types.h>

typedef struct {
    uint32_t idx;
    char    *cpu_port;
} meba_api_cpu_port_t;

#endif // _MICROCHIP_ETHERNET_BOARD_CPU_PORT_H_
