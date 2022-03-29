// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <inttypes.h>

#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/stat.h>
#include <sys/mount.h>
#include <sys/types.h>
#include <sys/reboot.h>

#include <linux/loop.h>
#include <linux/reboot.h>
#include <sys/syscall.h>
#include <dirent.h>

#define LOG_ERROR 2
#define LOG_WARN  4
#define LOG_INFO  6
#define LOG_DEBUG 7
#define LOG_NOISE 8


int warn(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
int info(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
int debug(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));
int noise(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

unsigned int g_log_level = LOG_INFO;

int pivot_root(const char *n, const char *o) {
    return syscall(__NR_pivot_root, n, o);
}

void print_time() {
    time_t rawtime;
    struct tm timeinfo_r;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime_r(&rawtime, &timeinfo_r);
    strftime(buffer, 80, "%X", timeinfo);
    printf("%s ", buffer);
}

int info(const char *format, ...) {
    int res = 0;
    va_list args;

    if (LOG_INFO <= g_log_level) {
        print_time();
        va_start(args, format);
        res = vprintf(format, args);
        va_end(args);
    }
    return res;
}

int debug(const char *format, ...) {
    int res = 0;
    va_list args;

    if (LOG_DEBUG <= g_log_level) {
        print_time();
        va_start(args, format);
        res = vprintf(format, args);
        va_end(args);
    }
    return res;
}

int noise(const char *format, ...) {
    int res = 0;
    va_list args;

    if (LOG_NOISE <= g_log_level) {
        print_time();
        va_start(args, format);
        res = vprintf(format, args);
        va_end(args);
    }
    return res;
}

int warn(const char *format, ...) {
    int res = 0;
    va_list args;

    if (LOG_WARN <= g_log_level) {
        print_time();
        va_start(args, format);
        res = vprintf(format, args);
        va_end(args);
    }
    return res;
}

int warn_(int line, const char *format, ...) {
    int res;
    print_time();
    va_list args;
    va_start(args, format);
    res = vprintf(format, args);
    va_end(args);
    printf("\nLine: %d, errno: %d error: %s\n", line, errno, strerror(errno));
    return res;
}

void fatal(unsigned line, const char *format, ...) {
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!! FATAL-ERROR at line: %d\n!!!! MSG: ", line);
    va_list args;
    va_start(args, format);
    (void)vprintf(format, args);
    va_end(args);
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    sleep(1);
    reboot(LINUX_REBOOT_CMD_RESTART);
}

void fatal_(unsigned line, const char *format, ...) {
    printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    printf("!!!! FATAL-ERROR at line: %d, errno: %d error: %s\n!!!! MSG: ",
           line, errno, strerror(errno));
    va_list args;
    va_start(args, format);
    (void)vprintf(format, args);
    va_end(args);
    printf("\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
           "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
    sleep(1);
    reboot(LINUX_REBOOT_CMD_RESTART);
}

#define FATAL(CMD, MSG)                      \
    {                                        \
        int res = CMD;                       \
        if (res != 0) fatal_(__LINE__, MSG); \
    }

#define WARN(CMD, MSG)                      \
    {                                       \
        int res = CMD;                      \
        if (res != 0) warn_(__LINE__, MSG); \
    }

// find the last occurence of needle in haystack
char *strrstr0(const char *haystack, const char *needle) {
    char *tmp = NULL;
    char *p = NULL;

    if (!needle[0]) return (char *)haystack + strlen(haystack);

    for (;;) {
        p = strstr((char *)haystack, needle);
        if (!p) return tmp;
        tmp = p;
        haystack = p + 1;
    }
}

char *cmd_arg(const char *key, int size, char *val) {
    int fd, res;
    const char *p;
    char buf[8 * 1024] = {};

    fd = open("/proc/cmdline", O_RDONLY);
    if (fd == -1) {
        printf("Failed to open /proc/cmdline: %s\n", strerror(errno));
        return 0;
    }

    res = read(fd, buf, sizeof(buf) - 1);
    close(fd);

    if (res <= 0) {
        return 0;
    }

    buf[res] = '\0';

    p = strrstr0(buf, key);
    if (!p) {
        return 0;
    }

    p += strlen(key);

    while (*p && *p != ' ' && *p != '\n') {
        if (size > 1) {
            *val++ = *p++;
            *val = 0;
            size --;
        } else {
            /* Overrun */
            return 0;
        }
    }

    return val;
}

static void basic_linux_system_init() {
    int fd = -1;
    int res, line;

    // Very basic stuff
    FATAL(chdir("/"), "Failed to change dir");
    setsid();
    putenv((char *)"HOME=/");
    putenv((char *)"TERM=linux");
    putenv((char *)"SHELL=/bin/sh");
    putenv((char *)"USER=root");

#define DO(X)            \
    res = X;             \
    if (res == -1) {     \
        line = __LINE__; \
        goto ERROR;      \
    }

    // Mount proc and sysfs as we need this to find the NAND flash.
    DO(mount("proc", "/proc", "proc", 0, 0));
    DO(mount("sysfs", "/sys", "sysfs", 0, 0));

    // Enable sys-requests - ignore errors as this is a nice-to-have
    fd = open("/proc/sys/kernel/sysrq", O_WRONLY);
    static const char *one = "1\n";
    if (fd != -1) {
        res = write(fd, one, strlen(one));
        if (res <= 0)
            return;
        close(fd);
        fd = -1;
    }

#undef DO
    return;

ERROR:
    if (fd != -1) close(fd);
    printf("BASIC SYSTEM INIT FAILED!!!\n");
    printf("File: %s, Line: %d, code: %d\n", __FILE__, line, res);
    printf("errno: %d error: %s\n\n", errno, strerror(errno));
    fflush(stdout);
    fflush(stderr);

    reboot(LINUX_REBOOT_CMD_RESTART);
    abort();
}

void change_root(const char *dev) {
    struct dirent *de;
    int res, cnt = 0;
    struct stat st;
    DIR *d;

    while (1) {
        res = stat(dev, &st);
        if (res == 0)
            break;

        if (cnt > 100000) {
            warn("Timeout. Device %s not found\n", dev);
            warn("\n");
            warn("Devices found:\n");
            d = opendir("/dev");
            if (d) {
                while ((de = readdir(d)) != NULL) {
                    printf("    %s\n", de->d_name);
                }

                closedir(d);
            }
            reboot(LINUX_REBOOT_CMD_RESTART);
        }

        usleep(100);
        cnt += 1;
    }

    FATAL(mount(dev, "/mnt", "ext4", 0, 0), "Failed to mount next rootfs");
    FATAL(chdir("/mnt"), "Failed to change dir");
    FATAL(pivot_root("/mnt", "/mnt/mnt"), "pivot_root failed");

    FATAL(chdir("/"), "chdir failed");

    FATAL(mount("/mnt/dev", "/dev", NULL, MS_MOVE, NULL), "Mount move failed");
    FATAL(mount("proc", "/proc", "proc", 0, 0), "Mount failed");
    FATAL(mount("sysfs", "/sys", "sysfs", 0, 0), "Mount failed");

    FATAL(mount("ramfs", "/tmp", "ramfs", 0,
                "size=8388608,mode=1777"),
          "Mount failed");

    (void)mkdir("/dev/pts", 0755);
    FATAL(mount("devpts", "/dev/pts", "devpts", 0, 0), "Mount failed");

    (void)mkdir("/dev/shm", 0755);
    FATAL(mount("shm", "/dev/shm", "ramfs", 0, 0), "Mount failed");

    WARN(umount2("/mnt", MNT_DETACH), "Unmount of /mnt failed");
}

int main(int argc, char *argv[]) {
    char buf_block[64];
    char buf_init[64];

    if ((int)getpid() == 1) {
        basic_linux_system_init();
    }

    if (!cmd_arg("root_next=", sizeof(buf_block), buf_block)) {
        fatal(__LINE__, "No root_next found!");
    }

    change_root(buf_block);

    if (cmd_arg("init_next=", sizeof(buf_init), buf_init)) {
        execl(buf_init, buf_init, 0);
    } else {
        execl("/sbin/init", "init", 0);
    }

    reboot(LINUX_REBOOT_CMD_RESTART);
    return 0;
}
