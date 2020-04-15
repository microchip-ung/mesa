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

#include <stdint.h>

enum { FLAG_EAR = 0x1 };

#define SPI_MAX_SIZE SIZE_M(16)

typedef struct {
    uint32_t jedec;
    int	     flash_size;
    int      erase_sz;
    int      page_sz;
    uint32_t flags;
} flash_t;

/* 
 * The header below is prefixed each possible image location = each
 * erase block start (64kb for applicable devices).
 *
 * The active image will be the the image with the highest image
 * sequence id. Lower bytes = lower significance.
 *
 * The image update must take care to update the image "cookie" last
 * and in two tempi - first the "in-progress", and then the "valid"
 * value. Since they differ only by a single bit, the update can be
 * atomic.
 *
 * When updating the flash, the image being most recent (highest ID)
 * is left untouched (if any). An alternate image location is found
 * (either an older valid image, or an empty image location. The
 * sequence ID used for the new image is incremented by one for the
 * new image (if a valid image was found) - or all zeroes.
 *
 * All 32-bit integers are big-endian (network order).
 *
 */
#define IMAGE_MAGIC_INVALID  0xFFFFFFFF    // Empty (erased) slot
#define IMAGE_MAGIC_UPDATING 0XFE3A04A1    // Update in progress
#define IMAGE_MAGIC_VALID    0XFE3A04A0    // Image valid
typedef struct __attribute__ ((__packed__)) {
    uint32_t cookie;    // See above for values
    uint32_t length;    // Image length
    uint8_t  seq[8];    // 8-byte image sequence no
    uint32_t crc;       // CRC value (simple 32-bit checksum)
} image_header_t;

const flash_t* flash_find_device(uint32_t jedec);
uint32_t flash_read_jedec(void);

void flash_read(const flash_t* flash, int flash_offset, int length, const char *filename);
void flash_write(const flash_t* flash, int flash_offset, const char *filename);
void flash_erase(const flash_t* flash, int start_offset, int length);
void flash_verify(const flash_t* flash, int flash_offset, int length, const char *filename);
int flash_update(const flash_t* flash, const char *filename);
void flash_info(const flash_t* flash);

void flash_reset(const flash_t* flash);
