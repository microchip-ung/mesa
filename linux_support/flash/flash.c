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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

#include "main.h"
#include "flash.h"
#include "spi.h"

enum {
    SPIFLASH_WREN   = 0x06,  // Write enable.
    SPIFLASH_WDRI   = 0x04,  // Write disable.
    SPIFLASH_RDID   = 0x9F,  // Read identification.
    SPIFLASH_RDSR   = 0x05,  // Read status register.
    SPIFLASH_WRSR   = 0x01,  // Write status register.
    SPIFLASH_RDFSR  = 0x70,  // Read flag status register
    SPIFLASH_READ   = 0x03,  // Read data.
    SPIFLASH_FREAD  = 0x0B,  // Read data (fast transaction).
    SPIFLASH_PP     = 0x02,  // Page program.
    SPIFLASH_SE     = 0xD8,  // Sector erase.
    SPIFLASH_BE     = 0xC7,  // Bulk erase.
    SPIFLASH_RES    = 0xAB,  // Read electronic signature.
    SPIFLASH_RD_EAR = 0xC8,  // Read EAR register
    SPIFLASH_WR_EAR = 0xC5,  // Write EAR register
};

flash_t devices[] = {
    { 0x00C22013, SIZE_K(512), SIZE_K(64), 256           }, // Macronix MX25L4005A
    { 0x00C22014, SIZE_M(1),   SIZE_K(64), 256,          }, // Macronix MX25L8005
    { 0x00C22015, SIZE_M(2),   SIZE_K(64), 256,          }, // Macronix MX25L1606E
    { 0x00C22016, SIZE_M(4),   SIZE_K(64), 256,          }, // Macronix MX25L3205D
    { 0x00C22017, SIZE_M(8),   SIZE_K(64), 256,          }, // Macronix MX25L6405D
    { 0x00C22018, SIZE_M(16),  SIZE_K(64), 256,          }, // Macronix MX25L128
    { 0x00C22019, SIZE_M(32),  SIZE_K(64), 256, FLAG_EAR }, // Macronix MX25L25635F
    { 0x0020BA19, SIZE_M(32),  SIZE_K(64), 256, FLAG_EAR }, // Micron MT25QL256ABA, N25Q256A
};

const flash_t* flash_find_device(uint32_t jedec)
{
    int i;
    for (i = 0; i < ((sizeof(devices))/(sizeof(devices[0]))); i++) {
        if (devices[i].jedec == jedec) {
            return &devices[i];
        }
    }
    return NULL;
}

uint32_t flash_read_jedec(void)
{
    uint32_t id = 0xFFFFFFFF;
    const uint8_t tx_spidata [4] = { SPIFLASH_RDID, 0, 0, 0 };
    uint8_t rx_spidata[4];
    if (spi_transfer(0, tx_spidata, rx_spidata, sizeof(tx_spidata)) == sizeof(tx_spidata)) {
        id = rx_spidata[3] | (rx_spidata[2] << 8) | (rx_spidata[1] << 16);
    }
    return id;
}

static int flash_wren_set(uint8_t ena)
{
    uint8_t tx_spidata [1];
    tx_spidata[0] = ena ? SPIFLASH_WREN : SPIFLASH_WDRI;
    NOISE("Set WREN = %d (0x%02x)\n", ena, tx_spidata[0]);
    return spi_transfer(0, tx_spidata, NULL, sizeof(tx_spidata));
}


static int flash_set_ear(uint8_t value)
{
    uint8_t tx_spidata [2];
    tx_spidata[0] = SPIFLASH_WR_EAR;
    tx_spidata[1] = value;
    NOISE("Set EAR = %d\n", value);
    return spi_transfer(0, tx_spidata, NULL, sizeof(tx_spidata));
}

static uint8_t flash_read_status(void)
{
    uint8_t tx_spidata [1], status;
    tx_spidata[0] = SPIFLASH_RDSR;
    (void) spi_cmd(0, tx_spidata, sizeof(tx_spidata), &status, sizeof(status), SPI_RX);
    NOISE("Status: %d\n", status);
    return status;
}

static void flash_wait(void)
{
    uint8_t status;
    int ct = 0;
    while((status = flash_read_status()) & 0x01) {
        usleep(25000);
        ct++;
    }
    if (ct) {
        NOISE("Status Wait: %d\n", ct);
    }
}

static void flash_sector_erase(const flash_t* flash, uint32_t offset)
{
    if (offset % flash->erase_sz == 0) {
        uint8_t tx_spidata [4];
        tx_spidata[0] = SPIFLASH_SE;
        tx_spidata[1] = (offset >> 16);
        tx_spidata[2] = (offset >> 8);
        tx_spidata[3] = (offset >> 0);
        DEBUG("Erase offset %08x\n", offset);
        flash_wren_set(1);
        (void) spi_transfer(0, tx_spidata, NULL, sizeof(tx_spidata));
        flash_wait();
    } else {
        fprintf(stderr, "Illegal erase offset %08x, sector size 0x%08x\n", offset, flash->erase_sz);
        exit(1);
    }
}

static void flash_update_ear(const flash_t* flash, uint32_t offset)
{
    static uint8_t ear_val_cur = 0xff;
    // Set EAR if so capable
    uint8_t ear_val = (offset >> 24);
    if ((flash->flags & FLAG_EAR) && ear_val != ear_val_cur) {
        ear_val_cur = ear_val;
        flash_wren_set(1);
        flash_set_ear(ear_val);
    }
}

static int flash_write_page(const flash_t* flash, uint32_t offset, const void *buf, size_t length)
{
    uint8_t tx_spidata [4];
    tx_spidata[0] = SPIFLASH_PP;
    tx_spidata[1] = (offset >> 16);
    tx_spidata[2] = (offset >> 8);
    tx_spidata[3] = (offset >> 0);
    flash_update_ear(flash, offset);
    DEBUG("Writing PAGE offset 0x%08x, bytes %zd\n", offset, length);
    flash_wren_set(1);
    (void) spi_cmd(0, tx_spidata, sizeof(tx_spidata), (void*) buf, length, SPI_TX);
    flash_wait();
    return length;
}

static int flash_write_data(const flash_t* flash, uint32_t offset, const void *buf, size_t length)
{
    size_t written, chunk;
    DEBUG("Writing %zd bytes to flash, offset 0x%08x\n", length, offset);
    for (written = 0; length > 0; written += chunk, length -= chunk) {
        chunk = MIN(length, flash->page_sz);
        flash_write_page(flash, offset + written, buf + written, chunk);
    }
    return written;
}

static int flash_read_data(int offset, void *rx, int length)
{
    uint8_t tx_spidata [5];
    tx_spidata[0] = SPIFLASH_FREAD;
    tx_spidata[1] = (offset >> 16);
    tx_spidata[2] = (offset >> 8);
    tx_spidata[3] = (offset >> 0);
    tx_spidata[4] = 0;
    NOISE("Read %d bytes at offset %08x\n", length, offset);
    return spi_cmd(0, tx_spidata, sizeof(tx_spidata), rx, length, SPI_RX);
}

void flash_read(const flash_t* flash, int start_offset, int length, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp) {
        uint8_t buf[flash->page_sz];
        int cur_offset, j, xfer_len, buf_size = sizeof(buf);
        for(cur_offset = start_offset, j = 0;
            cur_offset < flash->flash_size && length > 0;
            cur_offset += xfer_len, length -= xfer_len, j++) {
            xfer_len = MIN(buf_size, length);
            flash_update_ear(flash, cur_offset);
            if (flash_read_data(cur_offset, buf, xfer_len) != xfer_len) {
                fprintf(stderr, "%s: Failure reading %d bytes from flash, offset 0x%08x\n",
                        filename, xfer_len, cur_offset);
                exit(1);
            }
            fputc("|/-\\"[j&0x3], stderr);
            fputc('\b', stderr);
            if (fwrite(buf, 1, xfer_len, fp) != xfer_len) {
                fprintf(stderr, "%s: Failure writing %d bytes\n", filename, xfer_len);
                exit(1);
            }
        }
        fputc('\n', stderr);
        fclose(fp);
    } else {
        perror(filename);
        exit(1);
    }
}

void flash_write(const flash_t* flash, int start_offset, const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp) {
        uint8_t buf[flash->erase_sz];
        int cur_offset, j, buf_size = flash->erase_sz;
        for(cur_offset = start_offset, j = 0;
            cur_offset < flash->flash_size && !feof(fp);
            cur_offset += buf_size, j++) {
            memset (buf, 0xff, buf_size);
            fputc("|/-\\"[j&0x3], stderr);
            fputc('\b', stderr);
            int bytes_read = fread(buf, 1, buf_size, fp);
            DEBUG("Read %d bytes - wanted %d\n", bytes_read, buf_size);
            if (bytes_read > 0) {
                if(bytes_read != buf_size && !feof(fp)) {
                    fprintf(stderr, "%s: Warning read less than a sector, offset 0x%08x, read %d, wanted %d\n",
                            filename, cur_offset, bytes_read, buf_size);
                    exit(1);
                }
                flash_update_ear(flash, cur_offset);
                DEBUG("Cur offset 0x%08x, end 0x%08x\n", cur_offset, flash->flash_size);
                flash_sector_erase(flash, cur_offset);
                if (flash_write_data(flash, cur_offset, buf, buf_size) != buf_size) {
                    fprintf(stderr, "%s: Failure writing %d bytes to flash, offset 0x%08x\n",
                            filename, buf_size, cur_offset);
                    exit(1);
                }
            }
        }
        fputc('\n', stderr);
        fprintf(stderr, "Wrote %s\n", filename);
        fclose(fp);
    } else {
        perror(filename);
        exit(1);
    }
}

void flash_erase(const flash_t* flash, int start_offset, int length)
{
    int flash_size = MIN(length, flash->flash_size);
    int cur_offset, j;
    fprintf(stderr, "Erase: Start at offset %d, length %d\n", start_offset, length);
    for(cur_offset = start_offset, j = 0; cur_offset < flash_size; cur_offset += flash->erase_sz, j++) {
        fputc("|/-\\"[j&0x3], stderr);
        fputc('\b', stderr);
        flash_update_ear(flash, cur_offset);
        DEBUG("Cur offset 0x%08x, end 0x%08x\n", cur_offset, flash_size);
        flash_sector_erase(flash, cur_offset);
    }
}

void flash_verify(const flash_t* flash, int start_offset, int length, const char *filename)
{

    FILE *fp = fopen(filename, "r");
    if (fp) {
        uint8_t fbuf[flash->page_sz], buf[flash->page_sz];
        int j = 0, bytes_read = 0, buf_size = sizeof(buf);
        int cur_offset, xfer_len;
        for(cur_offset = start_offset;
            cur_offset < flash->flash_size && length > 0;
            cur_offset += xfer_len, length -= xfer_len, j++) {
            xfer_len = MIN(buf_size, length);
            flash_update_ear(flash, cur_offset);
            if ((xfer_len = fread(fbuf, 1, xfer_len, fp)) <= 0) {
                break;
            }
            DEBUG("Verify: Offset 0x%08x, length %8d, read %d bytes\n", cur_offset, bytes_read, xfer_len);
            if (flash_read_data(cur_offset, buf, xfer_len) != xfer_len) {
                fprintf(stderr, "%s: Failure reading %d bytes from flash, offset 0x%08x\n",
                        filename, xfer_len, cur_offset);
                exit(1);
            }
            bytes_read += xfer_len;
            fputc("|/-\\"[j&0x3], stderr);
            fputc('\b', stderr);
            for (int i = 0; i < xfer_len; i++) {
                if (buf[i] != fbuf[i]) {
                    fprintf(stderr, "%s: Verify error offset 0x%08x, flash 0x%02x - file 0x%02x\n",
                            filename, cur_offset + i, buf[i], fbuf[i]);
                    exit(1);
                }
            }
        }
        fputc('\n', stderr);
        fclose(fp);
        fprintf(stderr, "%s: Verified %d data bytes\n", filename, bytes_read);
    } else {
        perror(filename);
        exit(1);
    }
}

#define IMAGE_SIZE(f)    (f->erase_sz * (1))
#define IMAGE_SLOT(f, n) (f->erase_sz + (n*IMAGE_SIZE(f)))

static uint32_t calc_crc(uint8_t *buf, size_t length)
{
    size_t i = 0;
    uint32_t crc = 0;
    for (i = 0; i < length; i++) {
        crc += buf[i];
    }
    return crc;
}

static uint8_t *create_buffer(image_header_t *hdr, const char *filename, size_t maxsize, size_t *osz)
{
    FILE *fp = fopen(filename, "r");
    uint8_t *buf = NULL;
    if (fp) {
        fseek(fp, 0, SEEK_END);
        size_t sz = (size_t) ftell(fp);
        if ((sz + sizeof(*hdr)) > maxsize) {
            fprintf(stderr, "File size %zd too large - maximum is %zd\n", sz, maxsize);
            exit(1);
        }
        if (sz) {
            buf = malloc(sz + sizeof(*hdr));
            rewind(fp);
            if (buf) {
                uint8_t *dataptr = buf + sizeof(*hdr);
                size_t nread = fread(dataptr, 1, sz, fp);
                if (nread != sz) {
                    fprintf(stderr, "Failure reading %zd bytes from %s - got %zd\n", sz, filename, nread);
                    exit(1);
                }
                DEBUG("Read %zd bytes from %s\n", nread, filename);
                hdr->cookie = htonl(IMAGE_MAGIC_UPDATING);
                hdr->length = htonl(sz);
                hdr->crc = htonl(calc_crc(dataptr, nread));
                memcpy(buf, hdr, sizeof(*hdr));
            }
        }
        *osz = sz + sizeof(*hdr);
        fclose(fp);
    } else {
        perror(filename);
        exit(1);
    }
    return buf;
}

static void flash_do_update(const flash_t* flash,
                            uint32_t offset,
                            image_header_t *hdr,
                            const char *filename)
{
    INFO("Update image @ 0x%08x, seq %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
         offset,
         hdr->seq[0],hdr->seq[1],hdr->seq[2],hdr->seq[3],
         hdr->seq[4],hdr->seq[5],hdr->seq[6],hdr->seq[7]);
    size_t file_size;
    uint8_t *buf = create_buffer(hdr, filename, IMAGE_SIZE(flash), &file_size);
    if (buf) {
        // Write buffer
        flash_update_ear(flash, offset);
        flash_sector_erase(flash, offset);
        if (do_debug > 1) {
            dump_data("image", buf, file_size);
        }
        flash_write_data(flash, offset, buf, file_size);
        // Now update atomic bit / cookie
        hdr->cookie = htonl(IMAGE_MAGIC_VALID);
        flash_write_page(flash, offset, &hdr->cookie, sizeof(hdr->cookie));
        free(buf);
    }
}

static int verify_checksum(uint32_t offset, const image_header_t *hdr)
{
    uint32_t len = ntohl(hdr->length);
    uint8_t *buf = malloc(len);
    int verified = 0;
    if (buf) {
        if (flash_read_data(offset + sizeof(*hdr), buf, len) == len) {
            uint32_t crc = htonl(calc_crc(buf, len));
            DEBUG("Verify cksum: hdr '%08x' calc '%08x'\n", hdr->crc, crc);
            verified = (crc == hdr->crc);
        }
        free(buf);
    }
    return verified;
}

static int verify_latest_img(image_header_t *hdr, const char *filename, size_t maxsize)
{
    size_t file_size;
    image_header_t in_hdr;
    uint8_t *buf = create_buffer(&in_hdr, filename, maxsize, &file_size);
    int identical = 0;
    if (buf) {
        identical = (in_hdr.length == hdr->length &&
                     ntohl(in_hdr.crc) == ntohl(hdr->crc));
        free(buf);
    }
    return identical;
}

int flash_update(const flash_t* flash, const char *filename)
{
    uint32_t offset, keep_offset = 0, update_offset;
    image_header_t hdr, keep_hdr;
    // Start AFTER first erase block (keeps boot monitor)
    for (offset = IMAGE_SLOT(flash, 0); offset < flash->flash_size; offset += IMAGE_SIZE(flash)) {
        flash_update_ear(flash, offset);
        if (flash_read_data(offset, &hdr, sizeof(hdr)) == sizeof(hdr)) {
            if (hdr.cookie == ntohl(IMAGE_MAGIC_VALID) &&
                ntohl(hdr.length) < IMAGE_SIZE(flash) &&
                verify_checksum(offset, &hdr)) {
                DEBUG("Found image at offset %08x\n", offset);
                if (keep_offset) {
                    if (memcmp(hdr.seq, keep_hdr.seq, sizeof(hdr.seq)) > 0) {
                        DEBUG("New candidate @ 0x%08x, seq %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                             offset,
                             hdr.seq[0],hdr.seq[1],hdr.seq[2],hdr.seq[3],
                             hdr.seq[4],hdr.seq[5],hdr.seq[6],hdr.seq[7]);
                        keep_offset = offset;
                        keep_hdr = hdr;
                    }
                } else {
                    DEBUG("1st candidate @ 0x%08x, seq %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
                         offset,
                         hdr.seq[0],hdr.seq[1],hdr.seq[2],hdr.seq[3],
                         hdr.seq[4],hdr.seq[5],hdr.seq[6],hdr.seq[7]);
                    keep_offset = offset;
                    keep_hdr = hdr;
                }
            } else {
                NOISE("Offset 0x%08x, cookie 0x%08x, length %u\n", offset, hdr.cookie, ntohl(hdr.length));
            }
        }
    }
    if (keep_offset != 0) {
        DEBUG("Keep candidate @ 0x%08x, seq %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x\n",
              keep_offset,
              keep_hdr.seq[0],keep_hdr.seq[1],keep_hdr.seq[2],keep_hdr.seq[3],
              keep_hdr.seq[4],keep_hdr.seq[5],keep_hdr.seq[6],keep_hdr.seq[7]);
        if (verify_latest_img(&keep_hdr, filename, IMAGE_SIZE(flash))) {
            DEBUG("No update, image is already flashed.\n");
            return -1;
        }
        // Inc ID
        uint8_t carry = 1;
        int i;
        for (i = 0; i < sizeof(keep_hdr.seq); i++) {
            uint32_t v = keep_hdr.seq[i] + carry;
            hdr.seq[i] = (uint8_t) v;
            carry = v > 0xff ? 1 : 0;
        }
        // Select slot
        if (keep_offset == IMAGE_SLOT(flash, 0)) {
            update_offset = IMAGE_SLOT(flash, 1);
        } else {
            update_offset = IMAGE_SLOT(flash, 0);
        }
    } else {
        INFO("No valid images found\n");
        update_offset = IMAGE_SLOT(flash, 0);
        memset(&hdr, 0xFF, sizeof(hdr));
        memset(&hdr.seq, 0x00, sizeof(hdr.seq));
    }
    // Now do the update
    flash_do_update(flash, update_offset, &hdr, filename);
    return 0;
}

void flash_info(const flash_t* flash)
{
    uint32_t       offset, first = 1;
    image_header_t hdr;

    printf("Flash Info:\n");
    printf("===========\n");
    printf("JEDEC: 0x%08x, Total size: %dMB, Image block size: %dKB, Page size: %dB\n",
           flash->jedec, flash->flash_size / (1024 * 1024), flash->erase_sz / 1024, flash->page_sz);
    printf("\nImages in the flash:\n");
    printf("====================\n");
    // Start AFTER first erase block (keeps boot monitor)
    for (offset = IMAGE_SLOT(flash, 0); offset < flash->flash_size; offset += IMAGE_SIZE(flash)) {
        flash_update_ear(flash, offset);
        if (flash_read_data(offset, &hdr, sizeof(hdr)) == sizeof(hdr)) {
            if (hdr.cookie != ntohl(IMAGE_MAGIC_INVALID)) {
                if (first) {
                    first = 0;
                    printf("Position    Cookie      Image Size (B)  Sequence                 CRC\n");
                }
                printf("0x%08x  0x%08x  %14d  %02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x  %10d",
                       offset,
                       ntohl(hdr.cookie),
                       ntohl(hdr.length),
                       hdr.seq[0], hdr.seq[1], hdr.seq[2], hdr.seq[3],
                       hdr.seq[4], hdr.seq[5], hdr.seq[6], hdr.seq[7],
                       ntohl(hdr.crc));
                printf("\n");
            }
        }
    }
    if (first) {
        printf("Flash contains no images\n");
    }
}

void flash_reset(const flash_t* flash)
{
    flash_update_ear(flash, 0);
}
