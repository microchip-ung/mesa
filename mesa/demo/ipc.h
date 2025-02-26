// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MSCC_APPL_IPC_H_
#define _MSCC_APPL_IPC_H_

#include <stdint.h>

#define IPC_CMD_LEN (10 * 1024)
#define IPC_FILE    "/var/run/cli_ipc.socket"
// #define IPC_EOT 4 // End Of Transmission
// #define MSG_BUF_MAX 1024

enum { IPC_STDOUT = 0, IPC_STDERR = 1, IPC_RETURN = 2, IPC_ARG_CNT = 3, IPC_ARG = 4 };

struct ipc_msg {
    uint32_t type;
    uint32_t len;
};

#endif /* _MSCC_APPL_IPC_H_ */
