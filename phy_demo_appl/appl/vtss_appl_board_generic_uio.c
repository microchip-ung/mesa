// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#if defined(IO_METHOD_UIO)
#include "vtss_api.h"
#include "vtss_appl.h"
#include "board_probe.h"

#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <endian.h>
#include <sys/mman.h>
#include <linux/if_tun.h>
#include <asm/byteorder.h>

static int irq_fd;
static char iodev[64];
static volatile u32 *base_mem;

extern BOOL use_tap;
extern int  tap_fd;
extern const char *tap_ifname;
extern vtss_packet_tx_ifh_t tx_ifh;

static void (*chain_board_init_post)(vtss_appl_board_t *board);

#if defined(VTSS_ARCH_LUTON26)
#define TARGET_NAME "Luton26"
#define MMAP_SIZE   0x10200000
#define CHIPID_OFF (0x00070008 >> 2)
#elif defined(VTSS_ARCH_OCELOT)
#define TARGET_NAME "Ocelot"
#define MMAP_SIZE   0x02000000
#define CHIPID_OFF (0x01070000 >> 2)
#define ENDIAN_OFF (0x01000000 >> 2)
#elif defined(VTSS_ARCH_JAGUAR_2)
#define TARGET_NAME "Jaguar2"
#define MMAP_SIZE   0x02000000
#define CHIPID_OFF (0x01010000 >> 2)
#define ENDIAN_OFF (0x01000000 >> 2)
#endif

#define HWSWAP_BE 0x81818181       /* Big-endian */
#define HWSWAP_LE 0x00000000       /* Little-endian */

#ifdef __BYTE_ORDER
#define IS_BIG_ENDIAN (__BYTE_ORDER == __BIG_ENDIAN)
#else
# error Unable to determine byteorder!
#endif

#if (__BYTE_ORDER == __BIG_ENDIAN)
#define CPU_TO_LE32(x) __cpu_to_le32(x)
#define LE32_TO_CPU(x) __le32_to_cpu(x)
#else
#define CPU_TO_LE32(x) (x)
#define LE32_TO_CPU(x) (x)
#endif

static vtss_rc reg_read(const vtss_chip_no_t chip_no,
                        const u32            addr,
                        u32                  *const value)
{
    *value = LE32_TO_CPU(base_mem[addr]);
    return VTSS_RC_OK;
}

static vtss_rc reg_write(const vtss_chip_no_t chip_no,
                         const u32            addr,
                         const u32            value)
{
    base_mem[addr] = CPU_TO_LE32(value);
    return VTSS_RC_OK;
}

static BOOL find_dev(const char *target)
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
                fgets(devname, sizeof(devname), fp);
                fclose(fp);
                if (strstr(devname, target) || strstr(devname, "vcoreiii_switch")) {
                    snprintf(iodev, sizeof(iodev), "/dev/%s", dent->d_name);
                    found = TRUE;
                    break;
                }
            }
        }
    }

    closedir(dir);

    return found;
}

static void word_memcpy(volatile u32 *dst, volatile u32 *src, int n_words)
{
    if ((((size_t)dst) & 0x3) || (((size_t)src) & 0x3)) {
        printf("Unaligned addresses: dst %p, src %p\n", dst, src);
    }
    int i;
    for(i = 0; i < n_words; i++) {
        dst[i] = src[i];
    }
}

static void rx_frames_fdma(vtss_appl_board_t *board)
{
    u32 frame[1024];
    vtss_packet_rx_meta_t pmeta;
    vtss_packet_rx_info_t info;
    u32 dma_offset;
    memset(frame, 0xce, sizeof(frame));
    if (vtss_packet_dma_offset(NULL, TRUE, &dma_offset) == VTSS_RC_OK) {
        u32 frame_len = 0, chunk = 128 /* words */, status;
        u32 control_bits = 0;
        do {
            u32 chunk_bytes;
            u32 *ptr = &frame[frame_len>>2];
            word_memcpy(ptr, &base_mem[dma_offset - chunk], chunk + 1);
            status = LE32_TO_CPU(ptr[chunk]); /* Get last dword = status */
            control_bits |= status;
            chunk_bytes = status & 0xFFFF; /* Bits[0;15] */
            if(frame_len&0x3) {
                T_E("Unaligned data at %d", frame_len);
            }
            frame_len += chunk_bytes;
            T_D("Chunk %d bytes, total %d, status 0x%08x", chunk_bytes, frame_len, status);
        } while((control_bits & 0x60000) == 0); /* Exit on abort, eof */
        T_D("XTR got %d bytes, control_bits %08x", frame_len, control_bits & 0x70000);
        memset(&pmeta, 0, sizeof(pmeta));
        pmeta.length = frame_len - 16 - 4; /* Ex FCS ex IFH */
        if (vtss_packet_rx_hdr_decode(NULL, &pmeta, (u8*) frame, &info) == VTSS_RC_OK) {
            T_I("PCIe: Received %d bytes on port %d cos %d", info.length, iport2uport(info.port_no), info.cos);
            if (use_tap) {
                /* IFH is 16 bytes with default settings */
                write(tap_fd, &frame[4], info.length); /* info.length = Ex FCS */
            }
        } else {
            T_E("vtss_packet_rx_hdr_decode error");
        }
    }
}

static void rx_frames_register(vtss_appl_board_t *board)
{
    u8                      frame[2000];
    vtss_packet_rx_header_t header;
    vtss_packet_rx_queue_t  queue;
    u32                     total, frames;
                
    total = 0;
    do {
        frames = 0;
        for (queue = VTSS_PACKET_RX_QUEUE_START; queue < VTSS_PACKET_RX_QUEUE_END; queue++) {
            if (vtss_packet_rx_frame_get(board->inst, queue, &header, frame, sizeof(frame)) == VTSS_RC_OK) {
                T_I("received frame on port_no: %u, queue_mask: 0x%02x, length: %u",
                    header.port_no, header.queue_mask, header.length);
                total++, frames++;
                if (use_tap) {
                    write(tap_fd, frame, header.length < 60 ? 60 : header.length); /* pad info.length */
                }
            }
        }
    } while(frames);
    T_I("Extracted %d frames", total);
}

static void irq_poll(vtss_appl_board_t *board)
{
    vtss_irq_status_t status;
    fd_set rfds;
    struct timeval tv;
    int ret, nfds = 0;

    FD_ZERO(&rfds);
    FD_SET(irq_fd, &rfds);
    nfds = MAX(nfds, irq_fd);
    if (use_tap) {
        FD_SET(tap_fd, &rfds);
        nfds = MAX(nfds, tap_fd);
    }
    tv.tv_sec = 0;
    tv.tv_usec = 100000;    // 0.1 ms
    if((ret = select(nfds + 1, &rfds, NULL, NULL, &tv)) > 0) {

        if (FD_ISSET(irq_fd, &rfds)) {
            const int enable = 1;
            int n_irq;
            read(irq_fd, &n_irq, sizeof(n_irq));

            if (vtss_irq_status_get_and_mask(NULL, &status) == VTSS_RC_OK) {
                T_D("IRQ %d - status: 0x%08x (raw 0x%08x)", n_irq, status.active, status.raw_ident);
                if (status.active & (1 << VTSS_IRQ_FDMA_XTR)) {
                    rx_frames_fdma(board);
                    vtss_irq_enable(NULL, VTSS_IRQ_FDMA_XTR, TRUE);
                }
                if (status.active & (1 << VTSS_IRQ_XTR)) {
                    rx_frames_register(board);
                    vtss_irq_enable(NULL, VTSS_IRQ_XTR, TRUE);
                }
            }
            if(write(irq_fd, &enable, sizeof(enable)) != sizeof(enable)) {
                perror("write() failed, unable to enable IRQs");
            }
        }
        if (use_tap && FD_ISSET(tap_fd, &rfds)) {
            u32 buf[1024];
            int n_read;
#ifdef ENABLE_DMA_PACKET_MODE
            memcpy(buf, tx_ifh.ifh, tx_ifh.length);
            n_read = read(tap_fd, ((u8*) buf) + tx_ifh.length, sizeof(buf) - tx_ifh.length);
            if(n_read > 0) {
                T_I("TAP: DMA inject %d bytes", n_read);
                tx_frame_dma(buf, tx_ifh.length + n_read + 4); /* + 4 = Dummy FCS */
            }
#else
            n_read = read(tap_fd, ((u8*) buf), sizeof(buf));
            if(n_read > 0) {
                T_I("TAP: register inject %d bytes", n_read);
                vtss_packet_tx_frame(NULL, &tx_ifh, (u8 *) buf, n_read);
            }
#endif
        }
    } else {
        if (ret < 0) {
            perror("select()");
        }
    }
}

static void board_init_post(vtss_appl_board_t *board)
{
    vtss_irq_conf_t conf;

    if (chain_board_init_post) {
        chain_board_init_post(board);
    }

    memset(&conf, 0, sizeof(conf));
#if defined(__mips__)
    conf.external = FALSE;
    conf.destination = 1; // CPU0 = INT0_IRQ (BSP), CPU1 = INT1_IRQ (UIO)
#else
    conf.external = TRUE;
    conf.destination = 0;    // EXT0 / EXT1
#endif
    vtss_irq_conf_set(NULL, VTSS_IRQ_XTR, &conf);
    vtss_irq_conf_set(NULL, VTSS_IRQ_FDMA_XTR, &conf);
    vtss_irq_enable(NULL, VTSS_IRQ_XTR, TRUE);
    vtss_irq_enable(NULL, VTSS_IRQ_FDMA_XTR, TRUE);
}

void board_io_uio_init(vtss_board_info_t *board_info,
                       struct vtss_appl_board_t *board)
{
    u32 value;
    const int enable = 1;

    if(!find_dev(TARGET_NAME)) {
        fprintf(stderr, "Unable to locate UIO device for '%s', please make sure appropriate driver and HW is present\n", TARGET_NAME);
        exit(1);
    }

    /* Open the UIO device file */
    fprintf(stderr, "Using UIO: %s\n", iodev);
    irq_fd = open(iodev, O_RDWR);
    if (irq_fd < 1) {
        perror(iodev);
        exit(1);
    }

    /* mmap the UIO device */
    base_mem = mmap(NULL, MMAP_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, irq_fd, 0);
    if(base_mem != MAP_FAILED) {
        fprintf(stderr, "Mapped register memory @ %p\n", base_mem);
#if defined(ENDIAN_OFF)
        value = HWSWAP_LE;
        reg_write(0, ENDIAN_OFF, value);
        reg_read(0, ENDIAN_OFF, &value);
#endif
        reg_read(0, CHIPID_OFF, &value);
        fprintf(stderr, "Chipid: %08x\n", value);
        board_info->target = (value >> 12) & 0xffff;
    } else {
        perror("mmap");
    }

    board_info->reg_read = reg_read;
    board_info->reg_write = reg_write;

    if (use_tap) {
        if(write(irq_fd, &enable, sizeof(enable)) != sizeof(enable)) {
            perror("write() failed, unable to enable IRQs");
        }
        chain_board_init_post = board->board_init_post;    // Allow to hook onto init_post
        board->board_init_post = board_init_post;
        board->board_periodic = irq_poll;
    }
}

#endif /* IO_METHOD_UIO */
