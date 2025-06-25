// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT
//
// Support for u-dma-buf (https://github.com/ikwzm/udmabuf)
//
// u-dma-buf is an out-of-tree kernel module that provides user space mappable
// dma buffers. It is used by mesa-demo to provide DMA buffer for MESA.
//
// The udmabuf module will search for the first available u-dma-buf instance (in
// alphabetical order), open it with O_SYNC as to disable caches and use it to
// allocate memory chunks requested with the VTSS_MEM_FLAGS_DMA flag.
//

#include <dirent.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <unistd.h>

#include "main.h"
#include "trace.h"

static mscc_appl_trace_module_t trace_module = {.name = "udmabuf"};

enum { TRACE_GROUP_DEFAULT, TRACE_GROUP_CNT };

static mscc_appl_trace_group_t trace_groups[TRACE_GROUP_CNT] = {
    {.name = "default", .level = MESA_TRACE_LEVEL_ERROR},
};

typedef struct udmabuf_region_t {
    uint64_t phys_addr;
    uint64_t size;
    uint64_t current;
    uint8_t *vmem;
} udmabuf_region_t;

static const char      *udmabuf_sysfs_dir = "/sys/class/u-dma-buf";
static udmabuf_region_t udmabuf_region = {0, 0, 0, NULL};

static mesa_rc udmabuf_find_dev(int maj, int min, int *fd)
{
    DIR           *dir;
    struct dirent *dent;
    char           path[PATH_MAX];
    struct stat    sb;

    if (!(dir = opendir("/dev"))) {
        T_E("opendir(/dev) failed");
        return MESA_RC_ERROR;
    }

    while ((dent = readdir(dir)) != NULL) {
        if (dent->d_name[0] == '.') {
            continue;
        }

        snprintf(path, sizeof(path), "/dev/%s", dent->d_name);
        if (lstat(path, &sb) == -1) {
            T_E("Failed to stat: %s", path);
            continue;
        }

        if (((sb.st_mode & S_IFMT) != S_IFCHR) || (major(sb.st_rdev) != maj) ||
            (minor(sb.st_rdev) != min)) {
            continue;
        }

        *fd = open(path, O_RDWR | O_SYNC);
        if (*fd == -1) {
            T_E("Failed to open: %s", path);
            continue;
        }

        closedir(dir);
        return MESA_RC_OK;
    }

    closedir(dir);
    return MESA_RC_ERROR;
}

static mesa_rc udmabuf_read_sysfs(const char *name, const char *node, char *buf, int sz)
{
    char  path[PATH_MAX];
    FILE *fp;

    snprintf(path, sizeof(path), "%s/%s/%s", udmabuf_sysfs_dir, name, node);

    fp = fopen(path, "r");
    if (!fp) {
        T_E("Failed to open: %s", path);
        return MESA_RC_ERROR;
    }

    if (!fgets(buf, sz, fp)) {
        T_E("Failed to read: %s", path);
        fclose(fp);
        return MESA_RC_ERROR;
    }

    fclose(fp);
    return MESA_RC_OK;
}

mesa_rc udmabuf_init(void)
{
    DIR           *dir;
    struct dirent *dent;
    int            fd, maj, min;
    uint64_t       size, phys_addr;
    char           buf[64];
    uint8_t       *vmem;

    if (!(dir = opendir(udmabuf_sysfs_dir))) {
        T_I("%s not found, u-dma-buf not available", udmabuf_sysfs_dir);
        return MESA_RC_ERROR;
    }

    while ((dent = readdir(dir)) != NULL) {
        if (dent->d_name[0] == '.') {
            continue;
        }

        T_D("try %s", dent->d_name);

        if (udmabuf_read_sysfs(dent->d_name, "dev", buf, sizeof(buf)) != MESA_RC_OK) {
            continue;
        }

        if (sscanf(buf, "%d:%d", &maj, &min) != 2) {
            T_E("Failed to read major:minor %s", buf);
            continue;
        }

        if (udmabuf_read_sysfs(dent->d_name, "size", buf, sizeof(buf)) != MESA_RC_OK) {
            continue;
        }

        if (sscanf(buf, "%lld", &size) != 1) {
            T_E("Failed to read size %s", buf);
            continue;
        }

        if (udmabuf_read_sysfs(dent->d_name, "phys_addr", buf, sizeof(buf)) != MESA_RC_OK) {
            continue;
        }

        if (sscanf(buf, "%llx", &phys_addr) != 1) {
            T_E("Failed to read phys_addr %s", buf);
            continue;
        }

        if (udmabuf_find_dev(maj, min, &fd) != MESA_RC_OK) {
            T_E("cannot find %d:%d in /dev", maj, min);
            continue;
        }

        vmem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
        close(fd);

        if (!vmem) {
            T_E("Failed to mmap");
            continue;
        }

        udmabuf_region.phys_addr = phys_addr;
        udmabuf_region.size = size;
        udmabuf_region.current = 0;
        udmabuf_region.vmem = vmem;

        T_I("initialization complete! name=%s major=%d minor=%d phys_addr=0x%lx size=0x%lx",
            dent->d_name, maj, min, phys_addr, size);

        closedir(dir);
        return MESA_RC_OK;
    }

    closedir(dir);
    return MESA_RC_ERROR;
}

void *udmabuf_malloc(size_t size)
{
    uint8_t *vmem;

    if (!udmabuf_region.vmem) {
        T_E("udmabuf not initialized");
        return NULL;
    }

    if (size > udmabuf_region.size - udmabuf_region.current) {
        T_E("udmabuf memory exhausted")
        return NULL;
    }

    vmem = &udmabuf_region.vmem[udmabuf_region.current];
    udmabuf_region.current += size;

    return vmem;
}

void udmabuf_free(void *ptr)
{
    // Not supported
}

uintptr_t udmabuf_cpu_to_dma_addr(void *ptr)
{
    if (!udmabuf_region.vmem) {
        T_E("udmabuf not initialized");
        return 0;
    }

    if (((uint8_t *)ptr < udmabuf_region.vmem) ||
        ((uint8_t *)ptr >= udmabuf_region.vmem + udmabuf_region.size)) {
        T_E("udmabuf pointer out of bound");
        return 0;
    }

    return udmabuf_region.phys_addr + (((uint8_t *)ptr) - udmabuf_region.vmem);
}

void mscc_appl_udmabuf_init(mscc_appl_init_t *init)
{
    if (init->cmd == MSCC_INIT_CMD_REG) {
        mscc_appl_trace_register(&trace_module, trace_groups, TRACE_GROUP_CNT);
    }
}
