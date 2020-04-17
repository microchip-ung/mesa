// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


// If using uclibc, compile with
//   gcc -Wall -shared -fPIC -fasynchronous-unwind-tables btsig.c -lubacktrace -o btsig.so
// If using glibc, compile with
//   gcc -Wall -shared -fPIC -fasynchronous-unwind-tables btsig.c -lbacktrace -o btsig.so
//
// Test with
//   LD_PRELOAD=./btsig.so /path/to/program/that/crashes

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <execinfo.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <linux/limits.h>
#include <time.h>

#define FALSE 0
#define TRUE 1

#define CAPTURE(_sig_, _abort_) {.sig = _sig_, .name = #_sig_, .abort = _abort_}
#define ARRSZ(_x_)  (sizeof(_x_) / sizeof((_x_)[0]))

typedef struct {
    int  sig;
    char *name;
    int abort; // True if we should exit the program once handled
} btsig_entry_t;

static const btsig_entry_t btsig_captured_signals[] = {
    CAPTURE(SIGINT,  TRUE),
    CAPTURE(SIGQUIT, TRUE),
    CAPTURE(SIGILL,  TRUE),
    CAPTURE(SIGFPE,  TRUE),
    CAPTURE(SIGSEGV, TRUE),
    CAPTURE(SIGBUS,  TRUE),
    CAPTURE(SIGUSR1, FALSE),
    CAPTURE(SIGUSR2, FALSE),
    CAPTURE(SIGPWR,  FALSE),
};

/******************************************************************************/
// btsig_program_info_print()
/******************************************************************************/
static void btsig_program_info_print(FILE *fd, const btsig_entry_t *btsig_entry)
{
    pid_t     pid, tid;
    FILE      *fp;
    char      filename[100], cmdline[PATH_MAX], time_buf[30];
    time_t    cur_time;
    struct tm *tm_info;

    pid = syscall(SYS_getpid);
    tid = syscall(SYS_gettid);
    strcpy(cmdline, "<Unknown>");

    sprintf(filename, "/proc/%d/cmdline", pid);

    if ((fp = fopen(filename, "r")) != NULL) {
        if (fgets(cmdline, sizeof(cmdline), fp) == NULL) {
            fprintf(stderr, "Unable to read %s\n", filename);
            strncpy(cmdline, "<unknown>", sizeof(cmdline));
        }
        fclose(fp);
    }

    time(&cur_time);
    tm_info = localtime(&cur_time);
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", tm_info);

    fprintf(fd, "\n%s: %s Thread ID %d of process ID %d with cmdline \"%s\" received signal %s (%d)\n", btsig_entry->abort ? "Error" : "Info", time_buf, tid, pid, cmdline, btsig_entry->name, btsig_entry->sig);
}

/******************************************************************************/
// btsig_backtrace_print()
/******************************************************************************/
static void btsig_backtrace_print(FILE *fd)
{
    const int NSYMS_MAX = 100;
    void      *array[NSYMS_MAX];
    char      **symbols;
    int       i, nsyms;

    nsyms = backtrace(array, NSYMS_MAX);
    symbols = backtrace_symbols(array, nsyms);

    if (symbols == NULL) {
        fprintf(fd, "Error: Couldn't get symbols\n");
        return;
    }

    for (i = 1 /* skip first, since that'll be here */; i < nsyms && symbols[i]; i++) {
        fprintf(fd, "[bt]: (%d) %s\n", i, symbols[i]);
    }

    fprintf(fd, "\n");
    free(symbols);
}

/******************************************************************************/
// btsig_signal_handler()
/******************************************************************************/
static void btsig_signal_handler(int sig)
{
    const btsig_entry_t *btsig_entry = NULL;
    int                 i;
    FILE                *fd;
    char                *filename;
    int                 close_file;

    // Find signal in the btsig_captured_signals array.
    for (i = 0; i < ARRSZ(btsig_captured_signals); i++) {
        if (sig == btsig_captured_signals[i].sig) {
            btsig_entry = &btsig_captured_signals[i];
            break;
        }
    }

    if (!btsig_entry) {
        // Not found. How did we end up here, then?
        return;
    }

    // Find a file handle to write to. We listen to two environment variables:
    // 1) BTSIG_ERR_FILE, used when we're aborting afterwards
    // 2) BTSIG_OUT_FILE, used when we're not aborting.
    if ((filename = getenv(btsig_entry->abort ? "BTSIG_ERR_FILE" : "BTSIG_OUT_FILE")) != NULL && (fd = fopen(filename, "a")) != NULL) {
        // We're asked to write to a particular file.
        close_file = TRUE;
    } else {
        // Print on stderr if we're aborting, stdout otherwise.
        fd = btsig_entry->abort ? stderr : stdout;
        close_file = FALSE;
    }

    btsig_program_info_print(fd, btsig_entry);
    btsig_backtrace_print(fd);

    // If printing to stdout, we must call fflush(), because stdout by default is buffered.
    fflush(fd);

    if (close_file) {
        (void)fclose(fd);
    }

    if (btsig_entry->abort) {
        exit(EXIT_FAILURE);
    }
}

/******************************************************************************/
// btsig_init()
// Gets invoked when .so loads
/******************************************************************************/
static void btsig_init(void) __attribute__((constructor));
static void btsig_init(void)
{
    int i;

    // Set-up signal handlers for all the captured signals, so that we get
    // invoked when the signal is raised.
    for (i = 0; i < ARRSZ(btsig_captured_signals); i++) {
        signal(btsig_captured_signals[i].sig, btsig_signal_handler);
    }
}

