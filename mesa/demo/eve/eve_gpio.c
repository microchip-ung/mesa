# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

/*
 * eve_gpio.c
 *
 *  Created on: Dec 10, 2013
 *      Author: jsa
 *
 * See: https://www.kernel.org/doc/Documentation/gpio/sysfs.txt
 *      https://www.kernel.org/doc/Documentation/gpio/gpio.txt
 */

#include <fcntl.h>		//open
//#include <poll.h>
#include <stdarg.h>		// vprintf
#include <stdio.h>		//perror
#include <stdlib.h>
#include <string.h>		//strlen
//#include <errno.h>
#include <time.h>     // time
#include <unistd.h>		//close

//#include <sys/types.h>
#include <stdint.h>		//uint32_t
#include <sys/mman.h>	//mmap
#include <sys/stat.h> //stat

#include "eve_gpio.h"

static int gpio_debug = 0;  // GPIO enable debug output

/****************************************************************
 * gpio_export
 ****************************************************************/
int gpio_export(unsigned int gpio)
{
	int fd, len, rc;
	char buf[MAX_BUF];
    struct stat st;

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d", gpio);
    if (stat(buf, &st) == 0) {
        // GPIO already exported. Do not 're-export', this fills /var/log/kern.log
        if (gpio_debug)	log2stderr("GPIO export: %d already exported", gpio);
        return 0;
    }
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	rc = write(fd, buf, len);
	close(fd);
    if (gpio_debug)	log2stderr("GPIO export: %d exported", gpio);
	return (rc <= 0);
}

/****************************************************************
 * gpio_unexport
 ****************************************************************/
int gpio_unexport(unsigned int gpio)
{
	int fd, len, rc;
	char buf[MAX_BUF];
    struct stat st;

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d", gpio);
    if (stat(buf, &st) != 0) {
        // GPIO not exported. Do not 're-unexport', this fills /var/log/kern.log
        return 0;
    }
	fd = open(SYSFS_GPIO_DIR "/unexport", O_WRONLY);
	if (fd < 0) {
		perror("gpio/export");
		return fd;
	}
	len = snprintf(buf, sizeof(buf), "%d", gpio);
	rc = write(fd, buf, len);
	close(fd);
	return (rc <= 0);
}

/****************************************************************
 * gpio_set_dir
 ****************************************************************/
int gpio_set_dir(unsigned int gpio, int set_output)
{
	int fd, rc;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR  "/gpio%d/direction", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
        log2stderr("Failed to open %s", buf);
        perror("gpio/direction");
		return fd;
	}
	if (set_output)
		rc = write(fd, "out", 4);
	else
		rc = write(fd, "in", 3);
	close(fd);
	return (rc <= 0);
}

/****************************************************************
 * gpio_set_value
 ****************************************************************/
int gpio_set_value(unsigned int gpio, int value)
{
	int fd, rc;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-value");
		return fd;
	}
	rc = write(fd, value ? "1":"0", 2);
	close(fd);
	return (rc <= 0);
}

/****************************************************************
 * gpio_get_value
 ****************************************************************/
int gpio_get_value(unsigned int gpio)
{
	int fd, rc, value;
	char buf[MAX_BUF];
	char ch;

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	fd = open(buf, O_RDONLY);
	if (fd < 0) {
		perror("gpio/get-value");
		return fd;
	}
	rc = read(fd, &ch, 1);
	if (rc < 0)
		perror("gpio/get-value");
	value = (ch != '0') ? 1 : 0;
	close(fd);
	return value;
}


/****************************************************************
 * gpio_set_edge
 ****************************************************************/
int gpio_set_edge(unsigned int gpio, char *edge)
{
	int fd, rc;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio);
	fd = open(buf, O_WRONLY);
	if (fd < 0) {
		perror("gpio/set-edge");
		return fd;
	}
	rc = write(fd, edge, strlen(edge) + 1);
	close(fd);
	return (rc <= 0);
}

/****************************************************************
 * gpio_fd_open
 ****************************************************************/
int gpio_fd_open(unsigned int gpio)
{
	int fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
	fd = open(buf, O_RDONLY | O_NONBLOCK );
	if (fd < 0) {
		perror("gpio/fd_open");
	}
	return fd;
}

/****************************************************************
 * gpio_fd_close
 ****************************************************************/
int gpio_fd_close(int fd)
{
	return close(fd);
}

static volatile uint32_t *gpiommap;

static volatile struct s_GPIO_STATE {
    volatile uint32_t *dataout[4];
    volatile uint32_t *setdataout[4];
    volatile uint32_t *clrdataout[4];
    volatile uint32_t *oe[4];
    volatile uint32_t *datain[4];
    int mapped;
} gpioa = {{NULL, NULL, NULL, NULL},
           {NULL, NULL, NULL, NULL},
           {NULL, NULL, NULL, NULL},
           {NULL, NULL, NULL, NULL},
           {NULL, NULL, NULL, NULL},
           0};

static const unsigned int gpio_bankaddr[] = {GPIO0, GPIO1, GPIO2, GPIO3};

/****************************************************************
 * gpio_mm_init
 ****************************************************************/
int gpio_mm_init(void)
{
	static int mapped = 0;
	int i, fd;

	if (!mapped) {
		fd = open("/dev/mem", O_RDWR);
		if (fd == -1) {
			perror("GPIO unable to open /dev/mem");
			exit(EXIT_FAILURE);
		}
		gpiommap = (volatile uint32_t*) mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, MMAP_OFFSET);
		if (gpiommap == MAP_FAILED) {
			close(fd);
			perror("GPIO unable to map /dev/mem");
			exit(EXIT_FAILURE);
		}
        for (i=0; i<4; i++) {
            gpioa.dataout[i]    = gpiommap + ((gpio_bankaddr[i] - MMAP_OFFSET + GPIO_DATAOUT) / 4);
            gpioa.setdataout[i] = gpiommap + ((gpio_bankaddr[i] - MMAP_OFFSET + GPIO_SETDATAOUT) / 4);
            gpioa.clrdataout[i] = gpiommap + ((gpio_bankaddr[i] - MMAP_OFFSET + GPIO_CLEARDATAOUT) / 4);
            gpioa.oe[i]         = gpiommap + ((gpio_bankaddr[i] - MMAP_OFFSET + GPIO_OE) / 4);
            gpioa.datain[i]     = gpiommap + ((gpio_bankaddr[i] - MMAP_OFFSET + GPIO_DATAIN) / 4);
        }
		gpioa.mapped = 1;
		mapped = 1;
        //close(fd);    // If this were called more than once, we would need this.
	}
	return mapped;
}

/****************************************************************
 * gpio_mm_set
 * ~1.2MHz toggle rate at 1GHz CPU frequency
 * ~0.5MHz toggle rate at 300MHz CPU frequency
 * 15.6kHz toggle rate at 1GHz CPU frequency
 * 700Hz-2kHz toggle rate at 300Mhz CPU frequency
 *
 * Change to use GPIO_SETDATAOUT/GPIO_CLEARDATAOUT instead?
 ****************************************************************/
// gpio: AM3358 GPIO #
int gpio_mm_set(unsigned int gpio, int value)
{
	unsigned int bank, bank_id, bank_addr;
	volatile uint32_t *gpioreg;

	gpio_mm_init();
	/* GPIOs are sequentially numbered, and divided into 4 banks of 32 */
	//if (gpio < 0 || 127 < gpio) return -1;
	if (127 < gpio) return -1; // gpio is unsigned
	bank = gpio / 32;
	bank_id = gpio % 32;
	bank_addr = gpio_bankaddr[bank];
	// Set value. Divide addr by 4 since gpioreg is a uint32 pointer.
	gpioreg = gpiommap + ((bank_addr - MMAP_OFFSET + GPIO_DATAOUT) / 4);
	if (value) *gpioreg |=   1 << bank_id;
	else       *gpioreg &= ~(1 << bank_id);

	return 0;
}

// Same as gpio_mm_set, but using GPIO_SETDATAOUT/GPIO_CLEARDATAOUT
// ~2.1MHz toggle rate at 1GHz CPU frequency - old method
// ~2.2MHz toggle rate at 1GHz CPU frequency - new method
// gpio: AM3358 GPIO #
int gpio_mmdo_set(unsigned int gpio, int value)
{
	unsigned int bank, bank_id;
	volatile uint32_t *gpioreg;

	if (!gpioa.mapped) gpio_mm_init();
	/* GPIOs are sequentially numbered, and divided into 4 banks of 32 */
	if (gpio < 0 || 127 < gpio) return -1;
	bank = gpio / 32;
	bank_id = gpio % 32;
    gpioreg = value ? gpioa.setdataout[bank] : gpioa.clrdataout[bank];
	*gpioreg = 1 << bank_id;

	return 0;
}

// gpio: AM3358 GPIO #
int gpio_mm_get(unsigned int gpio)
{
	unsigned int bank, bank_id, bank_addr;
	volatile uint32_t *gpioreg;

	gpio_mm_init();
	/* GPIOs are sequentially numbered, and divided into 4 banks of 32 */
	if (gpio < 0 || 127 < gpio) return -1;
	bank = gpio / 32;
	bank_id = gpio % 32;
	bank_addr = gpio_bankaddr[bank];
	// Get value. Divide addr by 4 since gpioreg is a uint32 pointer.
	gpioreg = gpiommap + ((bank_addr - MMAP_OFFSET + GPIO_DATAIN) / 4);
	return (*gpioreg & (1 << bank_id)) ? 1:0;
}

// gpio: AM3358 GPIO #
// dir:  1 is output, 0 is input
int gpio_mm_dir(unsigned int gpio, int dir) {
	unsigned int bank, bank_id, bank_addr;
	volatile uint32_t *gpioreg;

	gpio_mm_init();
	/* GPIOs are sequentially numbered, and divided into 4 banks of 32 */
	if (gpio < 0 || 127 < gpio) return -1;
	bank = gpio / 32;
	bank_id = gpio % 32;
	bank_addr = gpio_bankaddr[bank];
	// Enable output. Divide addr by 4 since gpioreg is a uint32 pointer.
	gpioreg = gpiommap + ((bank_addr - MMAP_OFFSET + GPIO_OE) / 4);
	if (!dir) *gpioreg |=   1 << bank_id;  // 1 in OE is input
	else      *gpioreg &= ~(1 << bank_id); // 0 in OE is output enable

	return 0;
}

// gpio: AM3358 GPIO #
// dir:  1 is output, 0 is input
int gpio_mmdo_dir(unsigned int gpio, int dir) {
	unsigned int bank, bank_id;  //, bank_addr;
	volatile uint32_t *gpioreg;

	gpio_mm_init();
	/* GPIOs are sequentially numbered, and divided into 4 banks of 32 */
	if (gpio < 0 || 127 < gpio) return -1;
	bank = gpio / 32;
	bank_id = gpio % 32;
	//bank_addr = gpio_bankaddr[bank];
    gpioreg = gpioa.oe[bank];
	if (!dir) *gpioreg |=   1 << bank_id;  // 1 in OE is input
	else      *gpioreg &= ~(1 << bank_id); // 0 in OE is output enable

	return 0;
}

void GPIO_set_debug(int on) {
	gpio_debug = on;
	log2stderr("GPIO debug %s", gpio_debug ? "enabled" : "disabled");
}

void log2stderr(char *msg, ...)	{
	va_list argp;
	time_t now;
	struct tm tim;
	char s[20];

	now = time(NULL);
	tim = *(localtime(&now));
	strftime(s, 20,"%Y-%m-%d %H:%M:%S",&tim);

	fprintf(stderr, "[%s] ", s);
	va_start(argp, msg);
	vfprintf(stderr, msg, argp);
	va_end(argp);
	fprintf(stderr, "\n");
}
