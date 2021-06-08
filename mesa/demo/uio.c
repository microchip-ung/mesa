// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/i2c.h>      /* I2C support */
#include <linux/i2c-dev.h>  /* I2C support */
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/syscall.h>
#include <sys/un.h>

#include "microchip/ethernet/switch/api.h"
#include "microchip/ethernet/board/api.h"
#include "main.h"
#include "trace.h"

static mscc_appl_trace_module_t trace_module = {
    .name = "regio"
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

#if (__BYTE_ORDER == __BIG_ENDIAN)
#define PCIE_HOST_CVT(x) __builtin_bswap32((x))  /* PCIe is LE - we're BE, so swap */
#else
#define PCIE_HOST_CVT(x) (x)                     /* We're LE already */
#endif

static volatile uint32_t *base_mem;

/* MEBA callouts */
mesa_rc uio_reg_read(const mesa_chip_no_t chip_no,
                 const uint32_t       addr,
                 uint32_t             *const value)
{
    *value = PCIE_HOST_CVT(base_mem[addr]);
    return MESA_RC_OK;
}

mesa_rc uio_reg_write(const mesa_chip_no_t chip_no,
                  const uint32_t       addr,
                  const uint32_t       value)
{
    base_mem[addr] = PCIE_HOST_CVT(value);
    return MESA_RC_OK;
}

int uio_fd = -1;
char uio_path[PATH_MAX];

mesa_rc uio_reg_io_init(void)
{
    const char *driver = "mscc_switch";
    const char *top = "/sys/class/uio";
    DIR *dir;
    struct dirent *dent;
    char fn[PATH_MAX], devname[128];
    FILE *fp;
    char iodev[512];
    size_t mapsize;
    mesa_rc rc = MESA_RC_ERROR;
    int dev_fd;

    if (!(dir = opendir(top))) {
        T_E("operdir(%s) failed", top);
        return rc;
    }

    while((dent = readdir(dir)) != NULL) {
        if (dent->d_name[0] == '.') {
            continue;
        }

        snprintf(fn, sizeof(fn), "%s/%s/name", top, dent->d_name);
        fp = fopen(fn, "r");
        if (!fp) {
            T_E("UIO: Failed to open: %s", fn);
            continue;
        }

        const char *rrd = fgets(devname, sizeof(devname), fp);
        fclose(fp);

        if (!rrd) {
            T_E("UIO: Failed to read: %s", fn);
            continue;
        }

        T_D("UIO: %s -> %s", fn, devname);
        if (!strstr(devname, "mscc_switch") &&
            !strstr(devname, "vcoreiii_switch") &&
            !strstr(devname, "lan966x_uio")) {
            continue;
        }

        snprintf(iodev, sizeof(iodev), "/dev/%s", dent->d_name);
        snprintf(uio_path, sizeof(uio_path), "%s/%s/device/irqctl", top, dent->d_name);
        snprintf(fn, sizeof(fn), "%s/%s/maps/map0/size", top, dent->d_name);
        fp = fopen(fn, "r");
        if (!fp) {
            continue;
        }

        if (fscanf(fp, "%zi", &mapsize)) {
            fclose(fp);
            rc = MESA_RC_OK;
            T_I("Using UIO device: %s", devname)
            break;
        }
        fclose(fp);
    }
    closedir(dir);

    if (rc != MESA_RC_OK) {
        T_E("No suitable UIO device found!");
        return rc;
    }

    /* Open the UIO device file */
    T_D("Using UIO, found '%s' driver at %s", driver, iodev);
    dev_fd = open(iodev, O_RDWR);
    if (dev_fd < 1) {
        T_E("open(%s) failed", iodev);
        rc = MESA_RC_ERROR;
    } else {
        /* mmap the UIO device */
        base_mem = mmap(NULL, mapsize, PROT_READ|PROT_WRITE, MAP_SHARED, dev_fd, 0);
        if(base_mem != MAP_FAILED) {
            T_D("Mapped register memory @ %p", base_mem);
            // printf("Buildid (maybe): 0x%08x\n", *(base_mem + (0x70008 / 4)));
            uio_fd = dev_fd;
        } else {
            T_E("mmap failed");
            rc = MESA_RC_ERROR;
        }
    }
    return rc;
}

void mscc_appl_uio_init(mscc_appl_init_t *init)
{
    if (init->cmd == MSCC_INIT_CMD_REG) {
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
    }
}
