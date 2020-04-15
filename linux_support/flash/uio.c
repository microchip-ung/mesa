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
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include "main.h"
#include "uio.h"

#define OCELOT_GCB(x) ((0x01070000 >> 2) + x)
#define OCELOT_CFG(x) ((0x00000000 >> 2) + x)

#define OCELOT_GENERAL_CTRL OCELOT_CFG(0x9)

#define SERVAL1_GCB(x) ((0x01070000 >> 2) + x)
#define SERVAL1_CFG(x) ((0x00000000 >> 2) + x)

#define SERVAL1_GENERAL_CTRL SERVAL1_CFG(0x9)

#define JAGUAR2_GCB(x) ((0x01010000 >> 2) + x)
#define JAGUAR2_CFG(x) ((0x00000000 >> 2) + x)

#define JAGUAR2_GENERAL_CTRL JAGUAR2_CFG(0x9)

#define SERVALT_GCB(x) ((0x01010000 >> 2) + x)
#define SERVALT_CFG(x) ((0x00000000 >> 2) + x)

#define SERVALT_GENERAL_CTRL SERVALT_CFG(0x9)

static void ocelot_initialize(const uiochip_t *chip)
{
    // Set si_owner = 01 : SI Boot Master
    reg_write_masked(OCELOT_GENERAL_CTRL, VTSS_ENCODE_BITFIELD(1, 4, 2), VTSS_ENCODE_BITMASK(4,2));
    NOISE("si_owner = %d\n", (reg_read(OCELOT_GENERAL_CTRL) >> 4) & 0x3);
    NOISE("vcore_cfg = %d\n", (reg_read(OCELOT_GENERAL_CTRL) >> 4) & 0xf);
}

static uiochip_t ocelot_chip = {
    .uio_devname = "Ocelot",
    .name = "Ocelot",
    .initialize               = ocelot_initialize,
    .probe =                  { OCELOT_GCB(0), 0x0ffff000, 0x07514000},
    .regoff_gpiomode          = OCELOT_GCB(0x15),
    .regoff_spimst_swmode     = OCELOT_CFG(0x14),
};

static void serval1_initialize(const uiochip_t *chip)
{
    // SI_MST_ENA
    reg_write_masked(OCELOT_GENERAL_CTRL, VTSS_BIT(3), VTSS_BIT(3));
    // SIO CLK, LD, DI, DO
    gpio_setmode(0, GPIO_ALT1);
    gpio_setmode(1, GPIO_ALT1);
    gpio_setmode(2, GPIO_ALT1);
    gpio_setmode(3, GPIO_ALT1);
    NOISE("ALT0:1 = 0x%08x:0x%08x\n", reg_read(regoff(gpiomode)+0), reg_read(regoff(gpiomode)+1));
}

static uiochip_t serval1_chip = {
    .uio_devname = "Serval1",
    .name = "Serval1",
    .initialize               = serval1_initialize,
    .probe =                  { SERVAL1_GCB(0), 0x0ffff000, 0x07418000},
    .regoff_gpiomode          = SERVAL1_GCB(0x15),
    .regoff_spimst_swmode     = SERVAL1_CFG(0x14),
};

static void jaguar2_initialize(const uiochip_t *chip)
{
    // Set si_owner = 01 : SI Boot Master
    reg_write_masked(JAGUAR2_GENERAL_CTRL, VTSS_ENCODE_BITFIELD(1, 6, 2), VTSS_ENCODE_BITMASK(6,2));
    NOISE("si_owner = %d\n", (reg_read(JAGUAR2_GENERAL_CTRL) >> 6) & 0x3);
}

static uiochip_t jaguar2_chip = {
    .uio_devname = "Jaguar2",
    .name = "Jaguar2/Serval2",
    .probe =                  { JAGUAR2_GCB(0), 0x0ffff000, 0x07468000},
    .initialize               = jaguar2_initialize,
    .regoff_gpiomode          = JAGUAR2_GCB(0x15),
    .regoff_spimst_swmode     = JAGUAR2_CFG(0x14),
};

static void servalt_initialize(const uiochip_t *chip)
{
    // Set si_owner = 01 : SI Boot Master
    reg_write_masked(SERVALT_GENERAL_CTRL, VTSS_ENCODE_BITFIELD(1, 4, 2), VTSS_ENCODE_BITMASK(4,2));
    NOISE("si_owner = %d\n", (reg_read(SERVALT_GENERAL_CTRL) >> 4) & 0x3);
}

static uiochip_t servalt_chip = {
    .uio_devname = "Jaguar2",
    .name = "ServalT",
    .probe =                  { SERVALT_GCB(0), 0x0ffff000, 0x07415000},
    .initialize               = servalt_initialize,
    .regoff_gpiomode          = SERVALT_GCB(0x15),
    .regoff_spimst_swmode     = SERVALT_CFG(0x14),
};

uiochip_t* uio_devices[] = {
    &serval1_chip,
    &ocelot_chip,
    &jaguar2_chip,
    &servalt_chip,
};

devhandle_t devhandle;

uint32_t reg_read(uint32_t addr)
{
    uint32_t val = devhandle.base_mem[addr];
    //printf("Read (0x%08x)=0x%08x\n", addr, val);
    return val;
}

void reg_write(uint32_t addr, uint32_t value)
{
    //printf("Write(0x%08x, 0x%08x)\n", addr, value);
    devhandle.base_mem[addr] = value;
}

void reg_write_masked(uint32_t addr, uint32_t value, uint32_t mask)
{
    uint32_t val = reg_read(addr);
    reg_write(addr, (val & ~mask) | (value & mask));
}

void reg_write_masked_cond(uint32_t addr, uint32_t mask, BOOL cond)
{
    uint32_t val = reg_read(addr);
    if (cond) {
        val |= mask;
    } else {
        val &= ~mask;
    }
    //printf("Write(0x%08x, 0x%08x) - cond %d mask 0x%08x\n", addr, val, cond, mask);
    reg_write(addr, val);
}

void gpio_setmode(uint32_t gpio, gpio_mode mode)
{
    reg_write_masked_cond(regoff(gpiomode)+0, VTSS_BIT(gpio), mode & VTSS_BIT(0));
    reg_write_masked_cond(regoff(gpiomode)+1, VTSS_BIT(gpio), mode & VTSS_BIT(1));
}

static BOOL probe_dev(devhandle_t *dev, const uiochip_t *chip)
{
    /* Open the UIO device file */
    DEBUG("Probing UIO: %s\n", dev->iodev);
    dev->fd = open(dev->iodev, O_RDWR);
    if (dev->fd < 1) {
        perror(dev->iodev);
        return FALSE;
    }

    /* mmap the UIO device */
    dev->base_mem = mmap(NULL, dev->mapsize, PROT_READ|PROT_WRITE, MAP_SHARED, dev->fd, 0);
    if(dev->base_mem != MAP_FAILED) {
        uint32_t value;
        DEBUG("Mapped register memory @ %p\n", dev->base_mem);
        value = reg_read(chip->probe.offset);
        DEBUG("Read chipid: %08x\n", value);
        value = value & chip->probe.mask;
        if (value != chip->probe.value) {
            DEBUG("Unexpected probe value 0x%08x, expected 0x%08x\n", value, chip->probe.value);
            munmap((void *)dev->base_mem, dev->mapsize);
        } else {
            dev->chip = chip;
            return TRUE;
        }
    } else {
        perror("mmap");
    }
    close(dev->fd);
    return FALSE;
}

static BOOL find_dev(devhandle_t *dev, const uiochip_t *chip)
{
    const char *top = "/sys/class/uio";
    DIR *dir;
    struct dirent *dent;
    char fn[PATH_MAX], devname[128];
    FILE *fp;
    BOOL found = FALSE;

    if (!(dir = opendir (top))) {
        perror(top);
        exit (1);
    }

    while((dent = readdir(dir)) != NULL) {
        if (dent->d_name[0] != '.') {
            snprintf(fn, sizeof(fn), "%s/%s/name", top, dent->d_name);
            if ((fp = fopen(fn, "r"))) {
                const char *rrd = fgets(devname, sizeof(devname), fp);
                fclose(fp);
                if (rrd && (strstr(devname, chip->uio_devname) != NULL)) {
                    snprintf(dev->iodev, sizeof(dev->iodev), "/dev/%s", dent->d_name);
                    snprintf(fn, sizeof(fn), "%s/%s/maps/map0/size", top, dent->d_name);
                    if ((fp = fopen(fn, "r"))) {
                        if (fscanf(fp, "%zi", &dev->mapsize) != 1) {
                            dev->mapsize = 0;
                        }
                        fclose(fp);
                        if (probe_dev(dev, chip)) {
                            if (chip->initialize) {
                                chip->initialize(chip);
                            }
                            found = TRUE;
                            break;
                        }
                    }
                }
            }
        }
    }

    closedir(dir);

    return found;
}

void board_io_init(void)
{
    int i;
    for (i = 0; i < (sizeof(uio_devices)/sizeof(uio_devices[0])); i++) {
        if (find_dev(&devhandle, uio_devices[i])) {
            DEBUG("Found device %d - %s - UIO %s\n", i, uio_devices[i]->name, uio_devices[i]->uio_devname);
            return;
        }
    }
    fprintf(stderr, "Unable to locate any UIO device, please check 'lspci -nn' and 'lsmod'\n");
    exit(1);
}

