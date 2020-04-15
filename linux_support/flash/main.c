/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#include "main.h"
#include "uio.h"
#include "flash.h"

int do_debug, do_info = TRUE;

void dump_data(const char *what, uint8_t *buf, size_t len)
{
    char err_buf[256];
    int i = 0;
    while (i < len) {
        int j = 0;
        char *byte_p = err_buf;
        byte_p += sprintf(byte_p, "%04x:", i);
        while (j+i < len && j < 16) {
            byte_p += sprintf(byte_p, " %02x", buf[i+j]);
            j++;
        }
        printf("%s\n", err_buf);
        i += 16;
    }
}

int main(int argc, char **argv)
{
    int opt;
    int flash_offset = 0, flash_length = 0;
    const char *filename = "data.bin";

    while ((opt = getopt(argc, argv, "dqo:l:")) != -1) {
        switch (opt) {
            case 'd':
                do_debug++;
                break;
            case 'q':
                do_debug = do_info = FALSE;
                break;
            case 'l':
                if (sscanf(optarg, "%i", &flash_length) != 1) {
                    fprintf(stderr, "%s: Malformed length\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            case 'o':
                if (sscanf(optarg, "%i", &flash_offset) != 1) {
                    fprintf(stderr, "%s: Malformed offset\n", optarg);
                    exit(EXIT_FAILURE);
                }
                break;
            default: /* '?' */
                fprintf(stderr, "Usage: %s [-d|-q] [-l length] [-o offset] (erase|read <file>|write <file>|verify <file>|update <file>|flashinfo)\n",
                        argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    board_io_init();

    const flash_t *flash;
    uint32_t jedec = flash_read_jedec();

    if ((flash = flash_find_device(jedec)) == NULL) {
        printf("JEDEC: 0x%08x is not recognized\n", jedec);
        exit (EXIT_FAILURE);
    }

    if (flash->flash_size < SIZE_M(1)) {
        INFO("JEDEC: 0x%08x, size %dK\n", jedec, flash->flash_size/(1024));
    } else {
        INFO("JEDEC: 0x%08x, size %dM\n", jedec, flash->flash_size/(1024*1024));
    }

    if (flash_length == 0) {
        flash_length = flash->flash_size;
    }
    flash_length = MIN(flash_length, flash->flash_size);    // Clamp size

    if (optind < argc) {
        for (; optind < argc; optind++) {
            const char *op = argv[optind];
            if (strcmp(op, "erase") == 0) {
                flash_erase(flash, flash_offset, flash_length);
            } else if (strcmp(op, "read") == 0) {
                if (optind+1 < argc &&
                    (filename = argv[++optind])) {
                    flash_read(flash, flash_offset, flash_length, filename);
                } else {
                    fprintf(stderr, "Must provide filename argument\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(op, "write") == 0) {
                if (optind+1 < argc &&
                    (filename = argv[++optind]) &&
                    access(filename, R_OK) == 0) {
                    flash_write(flash, flash_offset, filename);
                } else {
                    fprintf(stderr, "Must provide -f <file> arguments\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(op, "verify") == 0) {
                if (optind+1 < argc &&
                    (filename = argv[++optind]) &&
                    access(filename, R_OK) == 0) {
                    flash_verify(flash, flash_offset, flash_length, filename);
                } else {
                    fprintf(stderr, "Must provide filename argument\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(op, "update") == 0) {
                if (optind+1 < argc &&
                    (filename = argv[++optind]) &&
                    access(filename, R_OK) == 0) {
                    if (flash_update(flash, filename) != 0) {
                        exit(EXIT_FAILURE);
                    }
                } else {
                    fprintf(stderr, "Must provide filename argument\n");
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(op, "flashinfo") == 0) {
                flash_info(flash);
            } else {
                printf("Unknow operation: %s\n", op);
                exit (EXIT_FAILURE);
            }
        }
    } else {
        printf("Operation missing: write/read/erase/update\n");
    }

    flash_reset(flash);

    exit (0);
}

    
