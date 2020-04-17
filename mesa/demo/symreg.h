// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_APPL_SYMREG_H_
#define _MSCC_APPL_SYMREG_H_

typedef enum {
    READ,
    WRITE,
    QUERY
} symreg_func_t;

void symreg_cli_regs_print(symreg_func_t func, char *pattern, uint32_t value);

#endif /* _MSCC_APPL_SYMREG_H_ */
