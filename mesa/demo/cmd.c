// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/un.h>

#include "ipc.h"

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif


static int trace_enabled = 0;

static void trace_printf(int line, const char *format, ...)
{
    va_list va;

    if (trace_enabled) {
        printf("client(%d): ", line);
        va_start(va, format);
        vprintf(format, va);
        va_end(va);
        printf("\n");
    }
}

#define T(...) trace_printf(__LINE__, __VA_ARGS__)

int write_block(int fd, const char *b, size_t s)
{
    int c = 0, res = 0;

    while (s) {
        res = write(fd, b, s);
        if (res < 0) {
            perror("write");
            return -1;
        } else {
            b += res;
            c += res;
            s -= res;
        }
    }

    return c;
}

void write_tlv(int fd, const char *b, size_t s, int type)
{
    struct ipc_msg m = {};
    m.type = type;
    m.len = s;
    if (write_block(fd, (const char *)&m, 8) < 0) {
        dprintf(2, "%d: write_tlv error\n", __LINE__);
        exit(-1);
    }

    if (write_block(fd, b, s) < 0) {
        dprintf(2, "%d: write_tlv error\n", __LINE__);
        exit(-1);
    }
}

int read_block(int fd, char *b, size_t s)
{
    int c = 0, res = 0;

    while (s) {
        res = read(fd, b, s);
        if (res < 0) {
            return c;

        } else if (res == 0) {
            return c;

        } else {
            b += res;
            c += res;
            s -= res;
        }
    }

    return c;
}

void copy_to(int fd_from, int fd_to, int cnt)
{
    int res;
    char buf[1024];

    while (cnt > 0) {
        res = read(fd_from, buf, MIN(1024, cnt));
        if (res > 0) {
            write_block(fd_to, buf, res);
            cnt -= res;

        } else if (res == 0) {
            return;

        } else {
            perror("read");
            exit(-1);
        }
    }
}

int usage(int res) {
    printf("Usage: mesa-cmd [options] <cmd>\n");
    printf("\n");
    printf("Where:\n");
    printf("  -h               This help message\n");
    printf("  -i               Append argument from stdin\n");
    printf("  -t               Enable debug traces\n");

    return res;
}

int main(int argc, char * const argv[])
{
    struct ipc_msg msg;
    struct sockaddr_un remote;
    int err_code = -1, fd, i, res, read_from_stdin = 0, opt;

    while ((opt = getopt(argc, argv, "hit")) != -1) {
        switch (opt) {
            case 'h':
                return usage(0);

            case 'i':
                read_from_stdin = 1;
                break;

            case 't':
                trace_enabled = 1;
                break;

            default:
                return usage(-1);
        }
    }

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }

    T("connecting");
    res = -1;
    for (i = 0; i < 1000; ++i) {
        remote.sun_family = AF_UNIX;
        strcpy(remote.sun_path, IPC_FILE);
        res = connect(fd, (struct sockaddr *)&remote,
                      sizeof(remote.sun_family) + strlen(remote.sun_path));

        if (res == 0) {
            break;
        } else {
            usleep(100000);
        }
    }
    if (res < 0) {
        perror("connect");
        return -1;
    }
    T("connected");


    // Write number of arguments
    i = argc - optind;
    if (read_from_stdin)
        i += 1;
    write_tlv(fd, (char *)&i, sizeof(i), IPC_ARG_CNT);

    // Write arguments
    for (i = optind; i < argc; ++i)
        write_tlv(fd, argv[i], strlen(argv[i]) + 1, IPC_ARG);

    // Copy stdin message
    if (read_from_stdin) {
        int buf_size = 1024;
        int buf_valid = 0;
        char *b = malloc(1024);

        T("Appending argument from stdin");
        while (1) {
            if (buf_size - buf_valid == 0) {
                buf_size += 1024;
                b = realloc(b, buf_size);
            }

            if (!b) {
                dprintf(2, "%d: Alloc error\n", __LINE__);
                return -1;
            }

            res = read(0, b + buf_valid, buf_size - buf_valid);
            T("Read -> %d", res);

            if (res > 0) {
                buf_valid += res;

            } else if (res == 0) {
                T("EOF");
                break;

            } else {
                perror("read");
                return 1;
            }
        }

        if (buf_size - buf_valid == 0) {
            buf_size += 1024;
            b = realloc(b, buf_size);
        }

        if (!b) {
            dprintf(2, "%d: Alloc error\n", __LINE__);
            return -1;
        }

        b[buf_valid] = 0;
        buf_valid += 1;

        T("Writing stdin tlv");
        write_tlv(fd, b, buf_valid, IPC_ARG);
        free(b);
    }

    // Read output
    while (1) {
        res = read_block(fd, (char *)&msg, sizeof(msg));
        if (res == 0) {
            break;
        } else if (res != sizeof(msg)) {
            perror("read");
            return -1;
        }

        switch (msg.type) {
            case IPC_STDOUT:
                copy_to(fd, 1, msg.len);
                break;

            case IPC_STDERR:
                copy_to(fd, 2, msg.len);
                break;

            case IPC_RETURN:
                if (msg.len != sizeof(err_code)) {
                    dprintf(2, "%d: Unexpected msg type/len: %d/%d\n", __LINE__,
                            msg.type, msg.len);
                }

                read_block(fd, (char *)&err_code, sizeof(err_code));
                break;

            default:
                dprintf(2, "%d: Unexpected msg type: %d\n", __LINE__, msg.type);
                return -1;
        }
    }

    return err_code;
}
