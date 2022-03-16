// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include "microchip/ethernet/switch/api.h"
#include "trace.h"
#include "cli.h"
#include "example.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

int  EXAMPLE_ARGV_FAILED = 0;
char EXAMPLE_SYNTAX[1024] = {};
char EXAMPLE_RUN_SYNTAX[1024];
int  EXAMPLE_SYNTAX_VALID = 0;
int  EXAMPLE_RUN_SYNTAX_VALID = 0;
char EXAMPLE_HELP[1024] = {};
char EXAMPLE_RUN_HELP[1024] = {};
int  EXAMPLE_HELP_VALID = 0;
int  EXAMPLE_RUN_HELP_VALID = 0;
int  EXAMPLE_FATAL_ERROR = 0;
int  EXAMPLE_FATAL_ERROR_LINE = 0;
const char *EXAMPLE_FATAL_ERROR_FILE = 0;

/* Store the meba inst globally */
meba_inst_t meba_example_inst;


#define PR_APPEND(buf, fmt, ...) \
    do { \
        if (buf ## _VALID < sizeof(buf)) { \
            buf ## _VALID += snprintf(buf + buf ## _VALID, sizeof(buf) - buf ## _VALID, fmt, ##__VA_ARGS__); \
            buf[sizeof(buf) - 1] = 0; \
        } \
    } while (0)


static mscc_appl_trace_module_t trace_module = {
    .name = "example"
};

enum {
    TRACE_GROUP_DEFAULT,
    TRACE_GROUP_CNT
};

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    // TRACE_GROUP_DEFAULT
    {
        .name = "default",
        .level = MESA_TRACE_LEVEL_ERROR
    },
};

static mesa_example_register_t *example_first = NULL;

meba_inst_t mesa_example_meba_inst()
{
    return meba_example_inst;
}

void mesa_example_register(mesa_example_register_t  *example)
{
    example->next = example_first;
    example_first = example;
}

int mesa_example_argv_find_key(char *key, int argc, const char *argv[])
{
    for (int i = 0; i < argc; ++i) {
        if (strcmp(key, argv[i]) == 0) {
            return i;
        }
    }

    return -1;
}

int mesa_example_arg_int(int run, int man, int def, char *key, char *help,
                         int argc, const char *argv[]) {
    long int res;
    const char *b;
    char *e;
    int i = mesa_example_argv_find_key(key, argc, argv);

    if (run == 0) {
        if (man) {
            PR_APPEND(EXAMPLE_SYNTAX, "%s <value> ", key);
        } else {
            PR_APPEND(EXAMPLE_SYNTAX, "[%s <value>] ", key);
        }
        PR_APPEND(EXAMPLE_HELP, "%s: %s\n", key, help);
    } else {
        if (man) {
            PR_APPEND(EXAMPLE_RUN_SYNTAX, "%s <value> ", key);
        } else {
            PR_APPEND(EXAMPLE_RUN_SYNTAX, "[%s <value>] ", key);
        }
        PR_APPEND(EXAMPLE_RUN_HELP, "%s: %s\n", key, help);
    }

    if (i == -1) {
        EXAMPLE_ARGV_FAILED += man;
        return def;
    }

    if (i + 1 >= argc) {
        EXAMPLE_ARGV_FAILED += 1;
        return def;
    }

    b = argv[i + 1];

    if (strlen(b) == 0) {
        EXAMPLE_ARGV_FAILED += 1;
        return def;
    }

    res = strtol(b, &e, 10);
    if (e - b != strlen(b)) {
        EXAMPLE_ARGV_FAILED += 1;
        return def;
    }

    return res;
}


static char command_str[] = {"example [help|list|init|run|uninit] [<args>]"};
static char help_str[] = {"Example code execution.\n\
example help:                      Print out this help.\n\
example help <name>:               Print out example name specific help.\n\
example list:                      Print all the known examples.\n\
example init <name> [<args...>]:   Initialize a given example.\n\
example run [<args...>]:           Run additional example setup/status.\n\
example uninit:                    Uninitialize the running example.\n\
"};

static mesa_example_register_t *example_active = NULL;

static void cli_cmd_error(const char *msg)
{
    cli_printf("%s at %s:%d\n", msg, EXAMPLE_FATAL_ERROR_FILE, EXAMPLE_FATAL_ERROR_LINE);
    cli_printf("Please reboot to recover from this.\n");
}

static int cli_cmd_example(int argc, const char **argv)
{
    mesa_example_register_t *example_ptr = NULL;
    const char              *param_str = NULL, *name_str = NULL;
    int                      res = 0, argv_consume = 0;

    T_D("Enter  argc %i", argc);

    if (EXAMPLE_FATAL_ERROR) {
        cli_cmd_error("An earlier example failed in a unrecoverable way");
        return -1;
    }

    switch (argc) {
        case 0:
        case 1:
            cli_printf("Usage: %s\n", command_str);
            return -1;

        case 2:
            param_str = argv[1];
            argv_consume = 1;

            break;

        default:
            // example <cmd> args...
            argv_consume = 1;
            param_str = argv[1];

            if (strcmp(param_str, "help") == 0 ||
                strcmp(param_str, "init") == 0) {
                name_str = argv[2];
                argv_consume = 2;
            }
    }

    // argv/argc will include the name of the command or the name of the
    // example.
    // If you write: 'meas-cmd example init tas asdf asdf' then argv will be
    // {'tas', 'asdf', 'asdf'}
    // If you write: 'meas-cmd example run asdf asdf' then argv will be
    // {'run', 'asdf', 'asdf'}
    argc -= argv_consume;
    argv += argv_consume;

    T_D("argc %i, name: %p", argc, name_str);
    for (int i = 0; i < argc; ++i) {
        T_D("i %d", i);
        T_D("argv %s", argv[i]);
    }

    if (name_str) {
        // Example name is given - find the example in the registered ones
        example_ptr = example_first;
        while (example_ptr != NULL) {
            T_D("example_ptr->name %s", example_ptr->name);
            if (strcmp(example_ptr->name, name_str) == 0) {
                // Example is found
                break;
            } else {
                // Look for next one
                example_ptr = example_ptr->next;
            }
        }

        if (!example_ptr) {
            cli_printf("Example %s not found\n", name_str);
            return -1;
        }
    }

    // Always clear syntax text and syntax help text buffers
    EXAMPLE_SYNTAX_VALID = 0;
    EXAMPLE_RUN_SYNTAX_VALID = 0;
    EXAMPLE_ARGV_FAILED = 0;
    EXAMPLE_HELP_VALID = 0;
    EXAMPLE_RUN_HELP_VALID = 0;
    memset(EXAMPLE_SYNTAX, 0, sizeof(EXAMPLE_SYNTAX));
    memset(EXAMPLE_HELP, 0, sizeof(EXAMPLE_HELP));
    memset(EXAMPLE_RUN_SYNTAX, 0, sizeof(EXAMPLE_RUN_SYNTAX));
    memset(EXAMPLE_RUN_HELP, 0, sizeof(EXAMPLE_RUN_HELP));
    if (example_ptr) {
        PR_APPEND(EXAMPLE_SYNTAX, "example init %s ", example_ptr->name);
        PR_APPEND(EXAMPLE_RUN_SYNTAX, "example run %s ", example_ptr->name);
    }

    T_D("Evaluating cmds");
    if (strcmp(param_str, "help") == 0) {
        T_D("help");
        if (example_ptr != NULL) {
            // Example name is found - print the example name relevant help
            // Calling the init function with no arguments will make the framework generate the syntax and syntax help test
            (void)example_ptr->init(0, NULL);
            cli_printf("%s\n", example_ptr->help());
            cli_printf("Init USAGE:\n%s\n", EXAMPLE_SYNTAX);
            cli_printf("Help:\n%s\n", EXAMPLE_HELP);
            if (example_ptr->run != NULL) {
                // Calling the run function with no arguments will make the framework generate the syntax and syntax help test
                (void)example_ptr->run(0, NULL);
                cli_printf("Run USAGE:\n%s\n", EXAMPLE_RUN_SYNTAX);
                cli_printf("Help:\n%s\n", EXAMPLE_RUN_HELP);
            }
        } else {
            // Print the Example command relevant help
            cli_printf("%s\n", help_str);
        }


    } else if (strcmp(param_str, "list") == 0) {
        T_D("list");
        if (argc != 1) {
            cli_printf("example list: does not accept any arguments\n");
            return -1;
        }

        cli_printf("Known example list:\n");
        example_ptr = example_first;
        while (example_ptr != NULL) {
            cli_printf("%s\n", example_ptr->name);
            example_ptr = example_ptr->next;
        }


    } else if (strcmp(param_str, "init") == 0) {
        T_D("init");
        if (example_ptr == NULL) {
            cli_printf("Example %s not found\n", name_str);
            return -1;
        }

        if (example_active != NULL) {
            cli_printf("Cannot load new example while an existing example is running\n");
            return -1;
        }

        T_D("Calling init for %s", name_str);
        res = example_ptr->init((argc == 0) ? 1 : argc, argv);
        T_D("result: %d", res);
        if (res == 0) {
            example_active = example_ptr;
        }

        if (EXAMPLE_FATAL_ERROR) {
            cli_cmd_error("The example failed unexpectly (coding error)");
        }

        return res;


    } else if (strcmp(param_str, "run") == 0) {
        T_D("run");
        if (!example_active) {
            cli_printf("Example s not active\n");
            return -1;
        }

        if (example_active->run == NULL) {
            cli_printf("Example run function %s not supported\n", name_str);
            return -1;
        }

        res = example_active->run((argc == 0) ? 1 : argc, argv);

        if (EXAMPLE_FATAL_ERROR) {
            cli_cmd_error("The example failed unexpectly (coding error)");
        }

        return res;


    } else if (strcmp(param_str, "uninit") == 0) {
        T_D("uninit");
        if (argc != 1) {
            cli_printf("example uninit: does not accept any arguments\n");
            return -1;
        }

        if (example_active == NULL) {
            cli_printf("No active example running\n");
            return -1;
        }

        res = example_active->uninit();
        example_active = NULL;
        return res;

    } else {
        T_D("...");
        cli_printf("Usage: %s\n", command_str);

    }

    return 0;
}

static cli_cmd_t cli_cmd_table[] = {
    {
        "Example",
        help_str,
        0,
        0,
        cli_cmd_example
    }
};

void mscc_appl_example_init(mscc_appl_init_t *init)
{
    switch (init->cmd) {
    case MSCC_INIT_CMD_REG:
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
        break;

    case MSCC_INIT_CMD_INIT:
        /* Register commands */
        for (int i = 0; i < sizeof(cli_cmd_table)/sizeof(cli_cmd_t); i++) {
            mscc_appl_cli_cmd_reg(&cli_cmd_table[i]);
        }
        meba_example_inst = init->board_inst;
        break;

   case MSCC_INIT_CMD_INIT_WARM:
        break;

    case MSCC_INIT_CMD_POLL:
        if (example_active && example_active->poll) {
            (void)example_active->poll(0);
        }
        break;

    case MSCC_INIT_CMD_POLL_FAST:
        if (example_active && example_active->poll) {
            (void)example_active->poll(1);
        }
        break;

    default:
        break;
    }
}
