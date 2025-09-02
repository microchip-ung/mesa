// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

// This is a dummy file, only here to provide symreg typedefs
// in order to test that the generated vtss_XXX_symregs.c file compiles.

typedef struct {
    const char      *name;
    unsigned long   addr;
    unsigned long   repl_cnt;
    unsigned long   repl_width;
} vtss_symreg_reg_t;

typedef struct {
    const char         *name;
    unsigned long      base_addr;
    unsigned long      repl_cnt;
    unsigned long      repl_width;
    vtss_symreg_reg_t const *regs;
} vtss_symreg_reggrp_t;

typedef struct {
    const char            *name;
    int                   repl_number;
    unsigned long         tgt_id;
    unsigned long         base_addr;
    vtss_symreg_reggrp_t const *reggrps;
} vtss_symreg_target_t;
