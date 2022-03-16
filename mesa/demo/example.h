// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_APPL_EXAMPLE_H_
#define _MSCC_APPL_EXAMPLE_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int EXAMPLE_ARGV_FAILED;
extern char EXAMPLE_SYNTAX[1024];
extern char EXAMPLE_RUN_SYNTAX[1024];
extern int EXAMPLE_FATAL_ERROR;
extern int EXAMPLE_FATAL_ERROR_LINE;
extern const char *EXAMPLE_FATAL_ERROR_FILE;


typedef struct mesa_example_reg {
    const char    *name;
    int          (* init)(int argc, const char *argv[]);
    int          (* run)(int argc, const char *argv[]);
    int          (* uninit)();
    int          (* poll)(int fast);
    const char*  (* help)();
    struct mesa_example_reg *next;
} mesa_example_register_t;

void mesa_example_register(mesa_example_register_t  *example);
int mesa_example_argv_find_key(char *key, int argc, const char *argv[]);
int mesa_example_arg_int(int run, int man, int def, char *key, char *help, int argc,
                         const char *argv[]);
meba_inst_t mesa_example_meba_inst();

#define RC(expr)                                     \
    {                                                \
        mesa_rc _rc = (expr);                        \
        if (_rc != MESA_RC_OK) {                     \
            EXAMPLE_FATAL_ERROR = 1;                 \
            EXAMPLE_FATAL_ERROR_LINE = __LINE__;     \
            EXAMPLE_FATAL_ERROR_FILE = __FUNCTION__; \
            return _rc;                              \
        }                                            \
    }

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

// Example with poll function
#define EXAMPLE_EXT(in_name, in_init, in_run, in_uninit, in_poll, in_help) \
static mesa_example_register_t mesa_example_ ## in_name = {                \
    .name = #in_name,                                                      \
    .init = in_init,                                                       \
    .run = in_run,                                                         \
    .uninit = in_uninit,                                                   \
    .poll = in_poll,                                                       \
    .help = in_help,                                                       \
    .next = NULL                                                           \
};                                                                         \
                                                                           \
__attribute__((constructor))                                               \
static void mesa_example_ ## in_name ## _register() {                      \
    mesa_example_register(&mesa_example_ ## in_name);                      \
}

// Example without poll function
#define EXAMPLE(in_name, in_init, in_run, in_uninit, in_help)           \
    EXAMPLE_EXT(in_name, in_init, in_run, in_uninit, NULL, in_help)

#define ARGV_OPT_INT(key, help, def)                            \
    mesa_example_arg_int(0, 0, def, key, help, argc, argv)

#define ARGV_INT(key, help) mesa_example_arg_int(0, 1, -1, key, help, argc, argv)

#define ARGV_RUN_OPT_INT(key, help, def) \
    mesa_example_arg_int(1, 0, def, key, help, argc, argv)

#define ARGV_RUN_INT(key, help) mesa_example_arg_int(1, 1, -1, key, help, argc, argv)

#define    EXAMPLE_BARRIER(argc)                                         \
    if (argc == 0) {                                                     \
        return 0;                                                        \
    }                                                                    \
    if (EXAMPLE_ARGV_FAILED != 0) {                                      \
        cli_printf("Missing or invalid arguments\n");                    \
        cli_printf("\n");                                                \
        cli_printf("USAGE: %s\n", EXAMPLE_SYNTAX);                       \
        return -1;                                                       \
    }

#ifdef __cplusplus
}
#endif
#endif
