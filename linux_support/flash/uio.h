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

#include "vtss_api.h"

#include "registers.h"

#define regoff(n) (devhandle.chip->regoff_##n)

typedef struct uiochip {
    const char *uio_devname;
    const char *name;
    void (*initialize)(const struct uiochip *chip);
    struct {
        uint32_t offset, mask, value;
    } probe;
    uint32_t regoff_spimst_swmode;
    //uint32_t regoff_spictl;
    uint32_t regoff_gpiomode;
} uiochip_t;

typedef struct {
    char iodev[64];
    size_t mapsize;
    volatile uint32_t *base_mem;
    int fd;
    const uiochip_t *chip;
} devhandle_t;

extern devhandle_t devhandle;

uint32_t reg_read(uint32_t addr);
void reg_write(uint32_t addr, uint32_t value);
void reg_write_masked(uint32_t addr, uint32_t value, uint32_t mask);
void reg_write_masked_cond(uint32_t addr, uint32_t mask, BOOL cond);

static inline void reg_write_masked_set(uint32_t addr, uint32_t mask)
{
    reg_write_masked(addr, mask, mask);
}

static inline void reg_write_masked_clear(uint32_t addr, uint32_t mask)
{
    reg_write_masked(addr, 0, mask);
}

typedef enum { GPIO_NORMAL = 0, GPIO_ALT1 = 1, GPIO_ALT2 = 2, GPIO_ALT3 = 3} gpio_mode;

void gpio_setmode(uint32_t gpio, gpio_mode mode);

void board_io_init(void);

