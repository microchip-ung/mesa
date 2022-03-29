// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <zlib.h>

static const char minusone = -1;  // sign extending does not work on BBB!!!
static char base64_decoder[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -1, -1, -1, -1, -1,
    -1,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1,
    -1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

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

int base64_decode_inplace(char *buf, int src_len)
{
    int i, j, k;
    uint32_t x[4], xx;

    if (buf == 0 || src_len == 0) {
        return 0;
    }

    // Compact input buffer
    for (i = 0, j = 0; i < src_len; ++i) {
        if (buf[i] == '=' || base64_decoder[(int) buf[i]] != minusone) {
            //dprintf(2, "%d: i=%d j=%d in: %hhd out: %hhd\n", __LINE__, i, j,
            //        buf[i], base64_decoder[(int) buf[i]]);
            buf[j++] = buf[i];
        }
    }
    src_len = j;

    if (src_len % 4) {
        dprintf(2, "%d: Unexpected input size: %d\n  >", __LINE__, src_len);
        for (i = 0; i < src_len; ++i) {
            dprintf(2, "%c", buf[i]);
        }
        dprintf(2, "<\n");

        return -1;
    }

    for (i = 0, j = 0; i < src_len;) {
        int short1 = 0, short2 = 0;
        for (k = 0; k < 4; ++k)
            x[k] = base64_decoder[(int) buf[i++]];

        // Handle padding
        if (i == src_len) {
            if (buf[src_len - 1] == '=') {
                short1 = 1;
                x[3] = 0;
                if (buf[src_len - 2] == '=') {
                    short2 = 1;
                    x[2] = 0;
                }
            }
        }

        xx = (x[0] << 18) + (x[1] << 12) + (x[2] << 6) + x[3];

        buf[j++] = (xx >> 16) & 0xFF;
        if (!short1) {
            buf[j++] = (xx >> 8) & 0xFF;
        }
        if (!short2) {
            buf[j++] = xx & 0xFF;
        }
    }

    return j;
}

int main(int argc, char * const argv[])
{
    int buf_size = 1024;
    int buf_valid = 0;
    char *b = malloc(1024);
    int res = -1, fd = -1;

    if (argc != 2) {
        dprintf(2, "Usage: base64decode <outout-file>\n");
        dprintf(2, "\n");
        goto EXIT;
    }

    while (1) {
        if (buf_size - buf_valid == 0) {
            buf_size += 1024;
            b = realloc(b, buf_size);
        }

        if (!b) {
            dprintf(2, "%d: Alloc error\n", __LINE__);
            goto EXIT;
        }

        res = read(0, b + buf_valid, buf_size - buf_valid);

        if (res > 0) {
            buf_valid += res;

        } else if (res == 0) {
            break;

        } else {
            dprintf(2, "%d: read error\n", __LINE__);
            perror("read");
            goto EXIT;
        }

        if (buf_valid >= 2 &&
            ((b[buf_valid - 1] == '\n' && b[buf_valid - 2] == '\n') ||
             (b[buf_valid - 1] == '\r' && b[buf_valid - 2] == '\r'))) {
            break;
        }
    }

    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd < 0) {
        perror("open");
        goto EXIT;
    }

    buf_valid = base64_decode_inplace(b, buf_valid);
    if (buf_valid > 0) {
        write_block(fd, b, buf_valid);
        goto EXIT;
    }

    res = 0;
EXIT:
    if (b) {
        free(b);
    }

    if (fd != -1) {
        close(fd);
    }

    return res;
}
