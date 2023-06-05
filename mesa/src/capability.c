// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_api.h>
#include "microchip/ethernet/switch/api.h"
#include "mesa_internal.h"        /* For MESA_ASSERT() */

#include "../base/ail/vtss_state.h" /* For VTSS_E() and vtss_inst_check_no_persist() */

void mesa_cap_callback_add(mesa_inst_t inst, mesa_cap_callback_data_t *hook)
{
    vtss_misc_appdata_set((vtss_inst_t)inst, hook);
}

#if defined(VTSS_ARCH_LUTON26)
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MIN           100 /* kbps.         1 *    100.000 =        100.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MAX       3276700 /* kbps.    0x7fff *    100.000 =  3.276.700.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MIN         4096 /* bytes.        1 *      4.096 =          4.096 bytes.     */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MAX       258048 /* bytes.     0x3f *      4.096 =        258.048 bytes.     */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN         100 /* fps.          1 *        100 =            100 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX     3276700 /* fps .    0x7fff *    100.000 =      3.276.700 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN         32 /* frames.       1 *       32,8 =             32,8 frames.  */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX       2067 /* frames.    0x3f *       32,8 =          2.066,4 frames.  */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MIN           100 /* kbps.         1 *    100.000 =        100.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MAX       3276700 /* kbps.    0x7fff *    100.000 =  3.276.700.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MIN         4096 /* bytes.        1 *      4.096 =          4.096 bytes.     */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MAX       245760 /* bytes.     0x3c *      4.096 =        245.760 bytes.     */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN         100 /* fps.          1 *        100 =            100 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX     3276700 /* fps .    0x7fff *    100.000 =      3.276.700 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN         32 /* frames.       1 *       32,8 =             32,8 frames.  */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX       2067 /* frames.    0x3f *       32,8 =          2.066,4 frames.  */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MIN            25 /* kbps.         1 *     25.040 =         25.040 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MAX      13128147 /* kbps.   0x7ffff *     25.040 = 13.128.146.480 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MIN         8192 /* bytes.        1 *      8.192 =          8.192 bytes.     */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MAX       516096 /* bytes.     0x3f *      8.192 =        516.096 bytes.     */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN          10 /* fps.          1 *         10 =             10 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX     5242870 /* fps.    0x7ffff *         10 =      5.242.870 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN          3 /* frames.       1 *  8192/2504 ~              3,3 frames.  */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX        207 /* frames.    0x3f *  8192/2504 ~            206,1 frames.  */
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MIN     /* FA-FIXME */       25 /* kbps.         1 *     25.040 =         25.040 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MAX     /* FA-FIXME */ 13128147 /* kbps.   0x7ffff *     25.040 = 13.128.146.480 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MIN    /* FA-FIXME */     8192 /* bytes.        1 *      8.192 =          8.192 bytes.     */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MAX    /* FA-FIXME */   516096 /* bytes.     0x3f *      8.192 =        516.096 bytes.     */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN   /* FA-FIXME */       10 /* fps.          1 *         10 =             10 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX   /* FA-FIXME */  5242870 /* fps.    0x7ffff *         10 =      5.242.870 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN  /* FA-FIXME */        3 /* frames.       1 *  8192/2504 ~              3,3 frames.  */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX  /* FA-FIXME */      207 /* frames.    0x3f *  8192/2504 ~            206,1 frames.  */
#elif defined(VTSS_ARCH_LAN966X)
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MIN           100 /* kbps.         1 *    100.000 =        100.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_RATE_MAX       3276700 /* kbps.    0x7fff *    100.000 =  3.276.700.000 bps.       */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MIN         4096 /* bytes.        1 *      4.096 =          4.096 bytes.     */
#define VTSS_QOS_PORT_POLICER_BIT_BURST_MAX       245760 /* bytes.     0x3c *      4.096 =        245.760 bytes.     */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN         100 /* fps.          1 *        100 =            100 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX     3276700 /* fps .    0x7fff *    100.000 =      3.276.700 fps.       */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN         32 /* frames.       1 *       32,8 =             32,8 frames.  */
#define VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX       2067 /* frames.    0x3f *       32,8 =          2.066,4 frames.  */
#else
#error "Add architecture here!"
#endif

/* Queue policer bit rate is the same as port policer */
#define VTSS_QOS_QUEUE_POLICER_BIT_RATE_MIN     VTSS_QOS_PORT_POLICER_BIT_RATE_MIN
#define VTSS_QOS_QUEUE_POLICER_BIT_RATE_MAX     VTSS_QOS_PORT_POLICER_BIT_RATE_MAX
#define VTSS_QOS_QUEUE_POLICER_BIT_BURST_MIN    VTSS_QOS_PORT_POLICER_BIT_BURST_MIN
#define VTSS_QOS_QUEUE_POLICER_BIT_BURST_MAX    VTSS_QOS_PORT_POLICER_BIT_BURST_MAX

/* Queue policer frame rate is currently not supported */
#define VTSS_QOS_QUEUE_POLICER_FRAME_RATE_MIN     0
#define VTSS_QOS_QUEUE_POLICER_FRAME_RATE_MAX     0
#define VTSS_QOS_QUEUE_POLICER_FRAME_BURST_MIN    0
#define VTSS_QOS_QUEUE_POLICER_FRAME_BURST_MAX    0

#if defined(VTSS_ARCH_LUTON26)
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN            100 /* kbps.         1 *    100.160 =        100.160 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX        3281943 /* kbps.    0x7fff *    100.160 =  3.281.942.720 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN          4096 /* bytes.        1 *      4.096 =          4.096 bytes. */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX        258048 /* bytes.     0x3f *      4.096 =        258.048 bytes. */
#elif defined(VTSS_ARCH_OCELOT)
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN            100 /* kbps.         1 *    100.000 =        100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX        3281943 /* kbps.    0x7fff *    100.000 =  3.276.700.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN          4096 /* bytes.        1 *      4.096 =          4.096 bytes. */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX        258048 /* bytes.     0x3f *      4.096 =        258.048 bytes. */
#elif defined(VTSS_ARCH_JAGUAR_2)
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN            100 /* kbps.         1 *    100.000 =        100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX       13107100 /* kbps.   0x1ffff *    100.000 = 13.107.100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN          4096 /* bytes.        1 *      4.096 =          4.096 bytes. */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX        258048 /* bytes.     0x3f *      4.096 =        258.048 bytes. */
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN      /* FA-FIXME */      100 /* kbps.         1 *    100.000 =        100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX      /* FA-FIXME */ 13107100 /* kbps.   0x1ffff *    100.000 = 13.107.100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN     /* FA-FIXME */     4096 /* bytes.        1 *      4.096 =          4.096 bytes. */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX     /* FA-FIXME */   258048 /* bytes.     0x3f *      4.096 =        258.048 bytes. */
#elif defined(VTSS_ARCH_LAN966X)
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN            100 /* kbps.         1 *    100.000 =        100.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX        3281943 /* kbps.    0x7fff *    100.000 =  3.276.700.000 bps.   */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN          4096 /* bytes.        1 *      4.096 =          4.096 bytes. */
#define VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX        258048 /* bytes.     0x3f *      4.096 =        258.048 bytes. */
#else
#error "Add architecture here!"
#endif

#if defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_PORT_SHAPER_FRAME_RATE_MIN    1
#define VTSS_QOS_PORT_SHAPER_FRAME_RATE_MAX    2600000
#define VTSS_QOS_PORT_SHAPER_FRAME_BURST_MIN   1
#define VTSS_QOS_PORT_SHAPER_FRAME_BURST_MAX   2000 // This is correct for SE_FRM_MODE = 2
//#define VTSS_QOS_PORT_SHAPER_FRAME_BURST_MAX 18   // This is correct for SE_FRM_MODE = 3
#else
#define VTSS_QOS_PORT_SHAPER_FRAME_RATE_MIN    0
#define VTSS_QOS_PORT_SHAPER_FRAME_RATE_MAX    0
#define VTSS_QOS_PORT_SHAPER_FRAME_BURST_MIN   0
#define VTSS_QOS_PORT_SHAPER_FRAME_BURST_MAX   0
#endif

/* Queue shaper bit rate is the same as port shaper */
#define VTSS_QOS_QUEUE_SHAPER_BIT_RATE_MIN    VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN
#define VTSS_QOS_QUEUE_SHAPER_BIT_RATE_MAX    VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX
#define VTSS_QOS_QUEUE_SHAPER_BIT_BURST_MIN   VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN
#define VTSS_QOS_QUEUE_SHAPER_BIT_BURST_MAX   VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX

/* Queue shaper frame rate is currently not supported */
#define VTSS_QOS_QUEUE_SHAPER_FRAME_RATE_MIN    VTSS_QOS_PORT_SHAPER_FRAME_RATE_MIN
#define VTSS_QOS_QUEUE_SHAPER_FRAME_RATE_MAX    VTSS_QOS_PORT_SHAPER_FRAME_RATE_MAX
#define VTSS_QOS_QUEUE_SHAPER_FRAME_BURST_MIN   VTSS_QOS_PORT_SHAPER_FRAME_BURST_MIN
#define VTSS_QOS_QUEUE_SHAPER_FRAME_BURST_MAX   VTSS_QOS_PORT_SHAPER_FRAME_BURST_MAX


#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MIN               0 /* undefined */
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MAX               0 /* undefined */
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MIN              0 /* undefined */
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MAX              0 /* undefined */
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MIN             1 /* fps.    */
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MAX       1024000 /* fps.    */
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MIN            1 /* frames. */
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MAX        32768 /* frames. */
#elif defined(VTSS_ARCH_JAGUAR_2) /* Same as port policer */
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MIN    VTSS_QOS_PORT_POLICER_BIT_RATE_MIN
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MAX    VTSS_QOS_PORT_POLICER_BIT_RATE_MAX
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MIN   VTSS_QOS_PORT_POLICER_BIT_BURST_MIN
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MAX   VTSS_QOS_PORT_POLICER_BIT_BURST_MAX
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MIN  VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MAX  VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MIN VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MAX VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX
#elif defined(VTSS_ARCH_SPARX5) /* Same as port policer */
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MIN    /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_RATE_MIN
#define VTSS_QOS_GLOBAL_STORM_BIT_RATE_MAX    /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_RATE_MAX
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MIN   /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_BURST_MIN
#define VTSS_QOS_GLOBAL_STORM_BIT_BURST_MAX   /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_BURST_MAX
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MIN  /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN
#define VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MAX  /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MIN /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN
#define VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MAX /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX
#else
#error "Add architecture here!"
#endif

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) /* Same as port policer */
#define VTSS_QOS_PORT_STORM_BIT_RATE_MIN        VTSS_QOS_PORT_POLICER_BIT_RATE_MIN
#define VTSS_QOS_PORT_STORM_BIT_RATE_MAX        VTSS_QOS_PORT_POLICER_BIT_RATE_MAX
#define VTSS_QOS_PORT_STORM_BIT_BURST_MIN       VTSS_QOS_PORT_POLICER_BIT_BURST_MIN
#define VTSS_QOS_PORT_STORM_BIT_BURST_MAX       VTSS_QOS_PORT_POLICER_BIT_BURST_MAX
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MIN      VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MAX      VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MIN     VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MAX     VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX
#elif defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_LAN966X)
#define VTSS_QOS_PORT_STORM_BIT_RATE_MIN        0 /* undefined */
#define VTSS_QOS_PORT_STORM_BIT_RATE_MAX        0 /* undefined */
#define VTSS_QOS_PORT_STORM_BIT_BURST_MIN       0 /* undefined */
#define VTSS_QOS_PORT_STORM_BIT_BURST_MAX       0 /* undefined */
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MIN      0 /* undefined */
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MAX      0 /* undefined */
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MIN     0 /* undefined */
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MAX     0 /* undefined */
#elif defined(VTSS_ARCH_SPARX5)
#define VTSS_QOS_PORT_STORM_BIT_RATE_MIN        /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_RATE_MIN
#define VTSS_QOS_PORT_STORM_BIT_RATE_MAX        /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_RATE_MAX
#define VTSS_QOS_PORT_STORM_BIT_BURST_MIN       /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_BURST_MIN
#define VTSS_QOS_PORT_STORM_BIT_BURST_MAX       /* FA-FIXME */ VTSS_QOS_PORT_POLICER_BIT_BURST_MAX
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MIN      /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN
#define VTSS_QOS_PORT_STORM_FRAME_RATE_MAX      /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MIN     /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN
#define VTSS_QOS_PORT_STORM_FRAME_BURST_MAX     /* FA-FIXME */ VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX
#else
#error "Add architecture here!"
#endif

#define MESA_EVENT_EXT_SYNC 5 /* Local definition of external synchronisation event ID */
#define MESA_BIT(x) (1 << (x))

uint32_t mesa_capability(mesa_inst_t inst, int cap)
{
    uint32_t c = 0;

    switch (cap) {
    // Port
    case MESA_CAP_PORT_CNT:
        c = VTSS_PORTS;
        break;

    case MESA_CAP_PORT_PFC:
#if defined(VTSS_FEATURE_PFC)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_FRAME_LENGTH_MAX:
#if defined(VTSS_ARCH_LUTON26)
        c = 9600;
#else
        c = 10240;
#endif
        break;

    case MESA_CAP_PORT_CNT_ETHER_LIKE:
#if defined(VTSS_FEATURE_PORT_CNT_ETHER_LIKE)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_CNT_EVC:
#if defined(VTSS_ARCH_CARACAL)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_MIIM_CTRL_CNT:
        c = VTSS_MIIM_CONTROLLERS;
        break;

    case MESA_CAP_PORT_BW:
#if defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_IFH:
#if defined(VTSS_FEATURE_PORT_IFH)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_INJ_HDR:
    case MESA_CAP_PORT_XTR_HDR:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_LAN966X)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_10G:
#if defined(VTSS_FEATURE_10G)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_MUX:
#if defined(VTSS_FEATURE_PORT_MUX)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_MUX_AUTO:
#if defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_QS_CONF:
#if defined(VTSS_ARCH_JAGUAR_2_CE)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_KR:
#if defined(VTSS_FEATURE_PORT_KR) || defined(VTSS_FEATURE_PORT_KR_IRQ)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_KR_IRQ:
#if defined(VTSS_FEATURE_PORT_KR_IRQ)
        c = 1;
#endif
        break;

    case MESA_CAP_PORT_CNT_PTP_PHYS_AND_VIRT:
#if defined(VTSS_FEATURE_TIMESTAMP)
        c = VTSS_PORTS + VTSS_TS_IO_ARRAY_SIZE;
#endif
        break;

    case MESA_CAP_PORT_LAST_FRAME_LEN_THRESHOLD:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        c = 1526;
#else
        c = 1518;
#endif
        break;

    case MESA_CAP_PORT_PCS_CONF:
#if defined(VTSS_FEATURE_PORT_PCS_CONF)
        c = 1;
#endif
        break;

    // Miscellaneous
    case MESA_CAP_MISC_GPIO_CNT:
#if defined(VTSS_GPIOS)
        c = VTSS_GPIOS;
#endif
        break;

    case MESA_CAP_MISC_SGPIO_CNT:
#if defined(VTSS_SGPIO_GROUPS)
        c = VTSS_SGPIO_GROUPS;
#endif
        break;

    case MESA_CAP_MISC_PORT_GPIO:
        // Unused
        break;

    case MESA_CAP_MISC_INTERRUPTS:
#if defined(VTSS_FEATURE_INTERRUPTS)
        c = 1;
#endif
        break;

    case MESA_CAP_MISC_IRQ_CONTROL:
#if defined(VTSS_FEATURE_IRQ_CONTROL)
        c = 1;
#endif
        break;

    case MESA_CAP_MISC_FAN:
#if defined(VTSS_FEATURE_FAN)
        c = 1;
#endif
        break;

    case MESA_CAP_MISC_CHIP_FAMILY:
        c = MESA_CHIP_FAMILY_UNKNOWN;
#if defined(VTSS_ARCH_LUTON26)
        c = MESA_CHIP_FAMILY_CARACAL;
#elif defined(VTSS_ARCH_OCELOT)
        c = MESA_CHIP_FAMILY_OCELOT;
#elif defined(VTSS_ARCH_SERVAL_T)
        c = MESA_CHIP_FAMILY_SERVALT;
#elif defined(VTSS_ARCH_JAGUAR_2)
        c = MESA_CHIP_FAMILY_JAGUAR2;
#elif defined(VTSS_ARCH_SPARX5)
        c = MESA_CHIP_FAMILY_SPARX5;
#elif defined(VTSS_ARCH_LAN966X)
        c = MESA_CHIP_FAMILY_LAN966X;
#endif
        break;

    case MESA_CAP_MISC_CPU_TYPE: {
        vtss_state_t *vtss_state;

        if ((vtss_state = vtss_inst_check_no_persist((const vtss_inst_t)inst)) == NULL) {
            VTSS_E("Unable to get state from inst = %p", inst);
            MESA_ASSERT(0);
        }

        c = (vtss_state->init_conf.spi_bus || vtss_state->sys_config.using_pcie) ?
                MESA_CPU_TYPE_EXTERNAL : MESA_CPU_TYPE_VCORE_III;
    }

        break;

    case MESA_CAP_MISC_DAC_CONTROLS_LOCAL_OSC:
#if defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_MISC_SWITCH_BW:
        c = MESA_SWITCH_BW_UNKNOWN;
#if defined(VTSS_CHIP_7546) || defined(VTSS_CHIP_7546TSN)
        c = MESA_SWITCH_BW_64;
#endif
#if defined(VTSS_CHIP_7549) || defined(VTSS_CHIP_7549TSN)
        c = MESA_SWITCH_BW_90;
#endif
#if defined(VTSS_CHIP_7552) || defined(VTSS_CHIP_7552TSN)
        c = MESA_SWITCH_BW_128;
#endif
#if defined(VTSS_CHIP_7556) || defined(VTSS_CHIP_7556TSN)
        c = MESA_SWITCH_BW_160;
#endif
#if defined(VTSS_CHIP_7558) || defined(VTSS_CHIP_7558TSN)
        c = MESA_SWITCH_BW_200;
#endif
        break;

    // Packet
    case MESA_CAP_PACKET_RX_QUEUE_CNT:
        c = VTSS_PACKET_RX_QUEUE_CNT;
        break;

    case MESA_CAP_PACKET_RX_GRP_CNT:
        c = VTSS_PACKET_RX_GRP_CNT;
        break;

    case MESA_CAP_PACKET_TX_GRP_CNT:
        c = VTSS_PACKET_TX_GRP_CNT;
        break;

    case MESA_CAP_PACKET_HDR_SIZE:
#if defined(VTSS_PACKET_HDR_SIZE_BYTES)
        c = VTSS_PACKET_HDR_SIZE_BYTES;
#endif
        break;

    case MESA_CAP_PACKET_RX_IFH_SIZE:
#if defined(VTSS_PACKET_RX_IFH_MAX)
        c = VTSS_PACKET_RX_IFH_MAX;
#endif
        break;

    case MESA_CAP_PACKET_TX_IFH_SIZE:
#if defined(VTSS_PACKET_TX_IFH_MAX)
        c = VTSS_PACKET_TX_IFH_MAX;
#endif
        break;

    case MESA_CAP_PACKET_PORT_L2CP_REG:
#if defined(VTSS_FEATURE_PACKET_PORT_L2CP_REG)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_PORT_IPMC:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_VSTAX:
#if defined(VTSS_FEATURE_VSTAX)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_IFH_EPID:
#if defined(VTSS_ARCH_SPARX5)
        c = 0x0b;
#elif defined(VTSS_ARCH_SERVAL_T)
        c = 0x09;
#elif defined(VTSS_ARCH_JAGUAR_2)
        c = 0x07;
#elif defined(VTSS_ARCH_OCELOT)
        c = 0x0a;
#elif defined(VTSS_ARCH_LAN966X)
        c = 0x0d;
#endif
        break;

    case MESA_CAP_PACKET_FCS_DATA:
#if defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_MASQ_PORT:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_INS_TAG:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_PTP_ACTION:
        c = (MESA_BIT(MESA_PACKET_PTP_ACTION_NONE) |
             MESA_BIT(MESA_PACKET_PTP_ACTION_ONE_STEP) |
             MESA_BIT(MESA_PACKET_PTP_ACTION_TWO_STEP));
#if defined(VTSS_ARCH_LUTON26)
        c |= MESA_BIT(MESA_PACKET_PTP_ACTION_ONE_AND_TWO_STEP);
#elif defined(VTSS_ARCH_OCELOT)
        c |= MESA_BIT(MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP);
#else
        c |= MESA_BIT(MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP);
        c |= MESA_BIT(MESA_PACKET_PTP_ACTION_ORIGIN_TIMESTAMP_SEQ);
        c |= MESA_BIT(MESA_PACKET_PTP_ACTION_AFI_NONE);
#endif
        break;

    case MESA_CAP_PACKET_AUTO_TAGGING:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_PACKET_INJ_ENCAP:
#if defined(VTSS_FEATURE_PACKET_INJ_ENCAP)
        c = 1;
#endif
        break;

    // AFI
    case MESA_CAP_AFI_V1:
#if defined(VTSS_AFI_V1)
        c = 1;
#endif
        break;

    case MESA_CAP_AFI_V2:
#if defined(VTSS_AFI_V2)
        c = 1;
#endif
        break;

    case MESA_CAP_AFI_SLOT_CNT:
#if defined(VTSS_AFI_SLOT_CNT)
        c = VTSS_AFI_SLOT_CNT;
#endif
        break;

    case MESA_CAP_AFI_SLOW_INJ_CNT:
#if defined(VTSS_AFI_SLOW_INJ_CNT)
        c = VTSS_AFI_SLOW_INJ_CNT;
#endif
        break;

    case MESA_CAP_AFI_SLOW_INJ_FPH_MAX:
#if defined(VTSS_AFI_SLOW_INJ_FPH_MAX)
        c = VTSS_AFI_SLOW_INJ_FPH_MAX;
#endif
        break;

    case MESA_CAP_AFI_FAST_INJ_CNT:
#if defined(VTSS_AFI_FAST_INJ_CNT)
        c = VTSS_AFI_FAST_INJ_CNT;
#endif
        break;

    case MESA_CAP_AFI_FAST_INJ_KBPS_MIN:
#if defined(VTSS_AFI_FAST_INJ_BPS_MIN)
    {
        uint64_t max = (VTSS_AFI_FAST_INJ_BPS_MIN / 1000ULL);

        c = max;
    }
#endif
        break;

    case MESA_CAP_AFI_FAST_INJ_KBPS_MAX:
#if defined(VTSS_AFI_FAST_INJ_BPS_MAX)
    {
        uint64_t max = (VTSS_AFI_FAST_INJ_BPS_MAX / 1000ULL);

        c = max;
    }
#endif
        break;

    case MESA_CAP_AFI_FAST_INJ_FRM_CNT:
#if defined(VTSS_AFI_FAST_INJ_FRM_CNT_MAX)
        c = VTSS_AFI_FAST_INJ_FRM_CNT_MAX;
#endif
        break;

    // Layer 2
    case MESA_CAP_L2_MAC_ADDR_CNT:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 32768;
#else
        c = 8192;
#endif
        break;

    case MESA_CAP_L2_AGGR_CNT:
        c = (VTSS_PORTS / 2);
        break;

    case MESA_CAP_L2_PVLAN_CNT:
        c = VTSS_PORTS;
        break;

    case MESA_CAP_L2_SRID_CNT:
        break;

    case MESA_CAP_L2_SVL_FID_CNT:
#if defined(VTSS_FEATURE_VLAN_SVL)
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        c = 63;
#else
        c = 4095;
#endif
#endif
        break;

    case MESA_CAP_L2_VLAN_COUNTERS:
#if defined(VTSS_FEATURE_VLAN_COUNTERS)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_VCAP_PORT_CONF:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_MIRROR_TAG:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_IPV4_MC_SIP:
#if defined(VTSS_FEATURE_IPV4_MC_SIP)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_IPV6_MC_SIP:
#if defined(VTSS_FEATURE_IPV6_MC_SIP)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_SFLOW_TESTED:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
        // SFLOW has been tested on architecture
        c = 1;
#endif
        break;

    case MESA_CAP_L2_MSTP_HW:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_SFLOW_SAMPLE_RATE_MAX:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
        c = 32767;
#elif defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        c = 4096;
#endif
        break;

    case MESA_CAP_L2_XFLOW:
#if defined(VTSS_FEATURE_XFLOW)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_XSTAT:
#if defined(VTSS_FEATURE_XSTAT)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_XDLB:
#if defined(VTSS_FEATURE_XDLB)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_TPID_AWARE:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
        /* Older devices are not fully VLAN aware */
#else
        c = 1;
#endif
        break;

    case MESA_CAP_L2_FRER:
#if defined(VTSS_FEATURE_FRER)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_FRER_MSTREAM_CNT:
#if defined(VTSS_FEATURE_FRER)
        c = VTSS_MSTREAM_CNT;
#endif
        break;
    case MESA_CAP_L2_FRER_CSTREAM_CNT:
#if defined(VTSS_FEATURE_FRER)
        c = VTSS_CSTREAM_CNT;
#endif
        break;

    case MESA_CAP_L2_PSFP:
#if defined(VTSS_FEATURE_PSFP)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_PSFP_GATE_CNT:
#if defined(VTSS_FEATURE_PSFP)
        c = VTSS_PSFP_GATE_CNT;
#endif
        break;
    case MESA_CAP_L2_PSFP_FILTER_CNT:
#if defined(VTSS_FEATURE_PSFP)
        c = VTSS_PSFP_FILTER_CNT;
#endif
        break;

    case MESA_CAP_L2_VCL_KEY_DMAC:
#if defined(VTSS_FEATURE_VCL_KEY_DMAC)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_VCL_KEY_DIP:
#if defined(VTSS_FEATURE_VCL_KEY_DIP)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_FRER_IFLOW_POP:
#if defined(VTSS_FEATURE_FRER_IFLOW_POP)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_RCL:
#if defined(VTSS_FEATURE_RCL)
        c = 1;
#endif
        break;

    case MESA_CAP_L2_MAC_INDEX_TABLE:
#if defined(VTSS_FEATURE_MAC_INDEX_TABLE)
        c = 1;
#endif
        break;

    // Layer 3
    case MESA_CAP_L3:
#if defined(VTSS_FEATURE_LAYER3)
        c = 1;
#endif
        break;

    case MESA_CAP_L3_RLEG_CNT:
#if defined(VTSS_RLEG_CNT)
        c = VTSS_RLEG_CNT;
#endif
        break;

    case MESA_CAP_L3_LPM_CNT:
#if defined(VTSS_LPM_CNT)
        c = VTSS_LPM_CNT;
#endif
        break;

    case MESA_CAP_L3_ARP_CNT:
#if defined(VTSS_ARP_CNT)
        c = VTSS_ARP_CNT;
#endif
        break;

    // QoS
    case MESA_CAP_QOS_PRIO_CNT:
        c = VTSS_PRIOS;
        break;

    case MESA_CAP_QOS_QUEUE_CNT:
        c = VTSS_QUEUES;
        break;

    case MESA_CAP_QOS_DPL_CNT:
        c = VTSS_DPLS;
        break;

    case MESA_CAP_QOS_PORT_POLICER_CNT:
#if defined(VTSS_PORT_POLICERS)
        c = VTSS_PORT_POLICERS;
#endif
        break;

    case MESA_CAP_QOS_WRED_GROUP_CNT:
#if defined(VTSS_FEATURE_QOS_WRED_V2)
        c = 1;
#elif defined(VTSS_WRED_GROUP_CNT)
        c = VTSS_WRED_GROUP_CNT;
#endif
        break;

    case MESA_CAP_QOS_TAS_GCE_CNT:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = VTSS_QOS_TAS_GCL_LEN_MAX;
#endif
        break;

    case MESA_CAP_QOS_TAS_CT_MIN:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = VTSS_QOS_TAS_CT_MIN;
#endif
        break;

    case MESA_CAP_QOS_TAS_CT_MAX:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = VTSS_QOS_TAS_CT_MAX;
#endif
        break;

    case MESA_CAP_QOS_TAS_MAX_SDU_MAX:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = VTSS_QOS_TAS_MAX_SDU_MAX;
#endif
        break;

    case MESA_CAP_QOS_TAS_MAX_SDU_MIN:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = VTSS_QOS_TAS_MAX_SDU_MIN;
#endif
        break;

    case MESA_CAP_QOS_TAS_HOLD_REL_MAC_RESTRICT:
#if defined(VTSS_FEATURE_QOS_TAS) && defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_INGRESS_MAP_CNT:
#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
        c = VTSS_QOS_INGRESS_MAP_IDS;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_MAP_CNT:
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
        c = VTSS_QOS_EGRESS_MAP_IDS;
#endif
        break;

    case MESA_CAP_QOS_COSID_CLASSIFICATION:
#if defined(VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_SCHEDULER_CNT_DWRR:
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_CPU_PORT_SHAPER:
#if defined(VTSS_FEATURE_QOS_CPU_PORT_SHAPER)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_WRED:
#if defined(VTSS_FEATURE_QOS_WRED_V2) || defined(VTSS_FEATURE_QOS_WRED_V3)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_DLB_CM:
#if defined(VTSS_ARCH_JAGUAR_2) || defined (VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_SHAPERS_RT:
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_RT)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_SHAPER_FRAME:
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPER_FRAME)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_SHAPERS_DLB:
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_PORT_POLICER_EXT_DPBL:
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_PORT_POLICER_EXT_TTM:
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_TAS:
#if defined(VTSS_FEATURE_QOS_TAS)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_QUEUE_SHAPERS_EB:
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_QUEUE_SHAPERS_CRB:
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_EGRESS_QUEUE_CUT_THROUGH:
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_DSCP_REMARK_DP_AWARE:
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_QCL_KEY_TYPE:
#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_QCL_DMAC_DIP:
#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_QCL_KEY_DMAC:
#if defined(VTSS_FEATURE_QCL_KEY_DMAC)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_QCL_KEY_DIP:
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_QCL_KEY_INNER_TAG:
#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_SHAPER_CALIBRATE:
        c = 0;
        break;

    case MESA_CAP_QOS_FRAME_PREEMPTION:
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
        c = 1;
#endif
        break;

    case MESA_CAP_QOS_PORT_POLICER_BIT_RATE_MIN:
        c = VTSS_QOS_PORT_POLICER_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_POLICER_BIT_RATE_MAX:
        c = VTSS_QOS_PORT_POLICER_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_POLICER_BIT_BURST_MIN:
        c = VTSS_QOS_PORT_POLICER_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_POLICER_BIT_BURST_MAX:
        c = VTSS_QOS_PORT_POLICER_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_PORT_POLICER_FRAME_RATE_MIN:
        c = VTSS_QOS_PORT_POLICER_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_POLICER_FRAME_RATE_MAX:
        c = VTSS_QOS_PORT_POLICER_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_POLICER_FRAME_BURST_MIN:
        c = VTSS_QOS_PORT_POLICER_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_POLICER_FRAME_BURST_MAX:
        c = VTSS_QOS_PORT_POLICER_FRAME_BURST_MAX;
        break;

    case MESA_CAP_QOS_QUEUE_POLICER_BIT_RATE_MIN:
        c = VTSS_QOS_QUEUE_POLICER_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_BIT_RATE_MAX:
        c = VTSS_QOS_QUEUE_POLICER_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_BIT_BURST_MIN:
        c = VTSS_QOS_QUEUE_POLICER_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_BIT_BURST_MAX:
        c = VTSS_QOS_QUEUE_POLICER_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_FRAME_RATE_MIN:
        c = VTSS_QOS_QUEUE_POLICER_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_FRAME_RATE_MAX:
        c = VTSS_QOS_QUEUE_POLICER_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_FRAME_BURST_MIN:
        c = VTSS_QOS_QUEUE_POLICER_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_POLICER_FRAME_BURST_MAX:
        c = VTSS_QOS_QUEUE_POLICER_FRAME_BURST_MAX;
        break;

    case MESA_CAP_QOS_PORT_SHAPER_BIT_RATE_MIN:
        c = VTSS_QOS_PORT_SHAPER_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_BIT_RATE_MAX:
        c = VTSS_QOS_PORT_SHAPER_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_BIT_BURST_MIN:
        c = VTSS_QOS_PORT_SHAPER_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_BIT_BURST_MAX:
        c = VTSS_QOS_PORT_SHAPER_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_FRAME_RATE_MIN:
        c = VTSS_QOS_PORT_SHAPER_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_FRAME_RATE_MAX:
        c = VTSS_QOS_PORT_SHAPER_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_FRAME_BURST_MIN:
        c = VTSS_QOS_PORT_SHAPER_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_SHAPER_FRAME_BURST_MAX:
        c = VTSS_QOS_PORT_SHAPER_FRAME_BURST_MAX;
        break;

    case MESA_CAP_QOS_QUEUE_SHAPER_BIT_RATE_MIN:
        c = VTSS_QOS_QUEUE_SHAPER_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_BIT_RATE_MAX:
        c = VTSS_QOS_QUEUE_SHAPER_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_BIT_BURST_MIN:
        c = VTSS_QOS_QUEUE_SHAPER_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_BIT_BURST_MAX:
        c = VTSS_QOS_QUEUE_SHAPER_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_FRAME_RATE_MIN:
        c = VTSS_QOS_QUEUE_SHAPER_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_FRAME_RATE_MAX:
        c = VTSS_QOS_QUEUE_SHAPER_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_FRAME_BURST_MIN:
        c = VTSS_QOS_QUEUE_SHAPER_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_QUEUE_SHAPER_FRAME_BURST_MAX:
        c = VTSS_QOS_QUEUE_SHAPER_FRAME_BURST_MAX;
        break;

    case MESA_CAP_QOS_GLOBAL_STORM_BIT_RATE_MIN:
        c = VTSS_QOS_GLOBAL_STORM_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_BIT_RATE_MAX:
        c = VTSS_QOS_GLOBAL_STORM_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_BIT_BURST_MIN:
        c = VTSS_QOS_GLOBAL_STORM_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_BIT_BURST_MAX:
        c = VTSS_QOS_GLOBAL_STORM_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_FRAME_RATE_MIN:
        c = VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_FRAME_RATE_MAX:
        c = VTSS_QOS_GLOBAL_STORM_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_FRAME_BURST_MIN:
        c = VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_GLOBAL_STORM_FRAME_BURST_MAX:
        c = VTSS_QOS_GLOBAL_STORM_FRAME_BURST_MAX;
        break;

    case MESA_CAP_QOS_PORT_STORM_BIT_RATE_MIN:
        c = VTSS_QOS_PORT_STORM_BIT_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_STORM_BIT_RATE_MAX:
        c = VTSS_QOS_PORT_STORM_BIT_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_STORM_BIT_BURST_MIN:
        c = VTSS_QOS_PORT_STORM_BIT_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_STORM_BIT_BURST_MAX:
        c = VTSS_QOS_PORT_STORM_BIT_BURST_MAX;
        break;
    case MESA_CAP_QOS_PORT_STORM_FRAME_RATE_MIN:
        c = VTSS_QOS_PORT_STORM_FRAME_RATE_MIN;
        break;
    case MESA_CAP_QOS_PORT_STORM_FRAME_RATE_MAX:
        c = VTSS_QOS_PORT_STORM_FRAME_RATE_MAX;
        break;
    case MESA_CAP_QOS_PORT_STORM_FRAME_BURST_MIN:
        c = VTSS_QOS_PORT_STORM_FRAME_BURST_MIN;
        break;
    case MESA_CAP_QOS_PORT_STORM_FRAME_BURST_MAX:
        c = VTSS_QOS_PORT_STORM_FRAME_BURST_MAX;
        break;

    case MESA_CAP_DSCP_CNT:
        c = MESA_DSCP_CNT;
        break;

    case MESA_CAP_QOS_CPU_QUEUE_SHAPER:
#if defined(VTSS_FEATURE_QOS_CPU_QUEUE_SHAPER)
        c = 1;
#endif
        break;

    // Security/ACL
    case MESA_CAP_ACL_POLICER_CNT:
        c = VTSS_ACL_POLICERS;
        break;

    case MESA_CAP_ACL_POLICY_CNT:
        c = VTSS_ACL_POLICIES;
        break;

    case MESA_CAP_ACL_SIP_CNT:
#if defined(VTSS_ACL_SIP_CNT)
        c = VTSS_ACL_SIP_CNT;
#endif
        break;

    case MESA_CAP_ACL_PTP_DELAY:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_PTP_ONE_AND_TWO_STEP:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_EVC_POLICER:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_CNT_LM:
    case MESA_CAP_ACL_KEY_LOOKUP:
    case MESA_CAP_ACL_KEY_ISDX:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_MAC_SWAP:
    case MESA_CAP_ACL_IFH_FLAG:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_ACE_STATUS:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_POLICER_PACKET_RATE_MAX:
#if defined(VTSS_ARCH_LUTON26)
        c = 3276700;
#elif defined(VTSS_ARCH_OCELOT)
        c = 1092000;
#else
        c = 5000000;
#endif
        break;

    case MESA_CAP_ACL_POLICER_PACKET_RATE_GRAN:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#elif defined(VTSS_ARCH_OCELOT)
        c = 100;
#else
        c = 10;
#endif
        break;

    case MESA_CAP_ACL_POLICER_PACKET_RATE_SMALL:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_POLICER_BIT_RATE_MAX:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
        c = 1000000;
#else
        c = 10000000;
#endif
        break;

    case MESA_CAP_ACL_POLICER_BIT_RATE_GRAN:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
        c = 100;
#else
        c = 25;
#endif
        break;

    case MESA_CAP_ACL_HACL:
#if defined(VTSS_FEATURE_HACL)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_EXT_DIP:
#if defined(VTSS_FEATURE_ACL_EXT_DIP)
        c = 1;
#endif
        break;

    case MESA_CAP_ACL_EXT_MAC:
#if defined(VTSS_FEATURE_ACL_EXT_MAC)
        c = 1;
#endif
        break;

    // EVC
    case MESA_CAP_EVC_EVC_CNT:
        break;

    case MESA_CAP_EVC_ECE_CNT:
        break;

    case MESA_CAP_EVC_MPLS_PW_CNT:
        break;

    case MESA_CAP_EVC_POLICER_CNT:
#if defined(VTSS_EVC_POLICERS)
        c = VTSS_EVC_POLICERS;
#endif
        break;

    case MESA_CAP_EVC_ENCAP_CNT:
        break;

    case MESA_CAP_EVC_L2CP_PROFILE_CNT:
        break;

    case MESA_CAP_EVC_NNI_LIST:
        break;

    case MESA_CAP_EVC_LEAF_LIST:
        break;

    case MESA_CAP_EVC_COSID_POLICERS:
        break;

    case MESA_CAP_EVC_POLICER_BLIND:
#if !(defined(VTSS_ARCH_CARACAL) || defined(VTSS_ARCH_OCELOT))
        c = 1;
#endif
        break;

    case MESA_CAP_EVC_SERVAL:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;
    case MESA_CAP_EVC_CARACAL:
#if defined(VTSS_ARCH_CARACAL)
        c = 1;
#endif
        break;

    case MESA_CAP_EVC_PORT:
        break;

    case MESA_CAP_EVC_PORT_EVC:
        break;

    case MESA_CAP_EVC_ETREE:
        break;

    case MESA_CAP_EVC_POLICY:
        break;

    case MESA_CAP_EVC_ECE_ETYPE:
        break;

    case MESA_CAP_EVC_ECE_LLC:
        break;

    case MESA_CAP_EVC_ECE_SNAP:
        break;

    case MESA_CAP_EVC_ECE_DMAC:
        break;

    case MESA_CAP_EVC_ECE_DIP:
        break;

    case MESA_CAP_EVC_ECE_INNER_TAG:
        break;

    case MESA_CAP_EVC_ECE_MASQ:
        break;

    case MESA_CAP_EVC_ECE_ACT_OT:
        break;

    case MESA_CAP_EVC_ECE_ACT_OT_VID:
        break;

    case MESA_CAP_EVC_ECE_ACT_PCP_MODE:
        break;

    case MESA_CAP_EVC_ECE_ACT_DEI_MODE:
        break;

    case MESA_CAP_EVC_ECE_ACT_PCP_DEI_PRES:
        break;

    case MESA_CAP_EVC_ECE_ACT_IT:
        break;

    case MESA_CAP_EVC_ECE_ACT_POLICER:
        break;

    case MESA_CAP_EVC_ECE_ACT_PRIO:
        break;

    case MESA_CAP_EVC_ECE_ACT_DPL:
        break;

    case MESA_CAP_EVC_ECE_ACT_DISCARD:
        break;

    case MESA_CAP_EVC_COUNTERS:
#if defined(VTSS_FEATURE_EVC_COUNTERS)
        c = 1;
#endif
        break;

    case MESA_CAP_EVC_COSID_COUNTERS:
        break;

    case MESA_CAP_EVC_PORT_KEY_TYPE:
        break;

    case MESA_CAP_EVC_PORT_DMAC_DIP:
        break;

        // MPLS
    case MESA_CAP_MPLS:
        break;

    case MESA_CAP_MPLS_LOCAL_TC_MAP:
        break;

    // HQoS
    case MESA_CAP_HQOS_CNT:
        break;

    case MESA_CAP_HQOS_STAT_CNT_SERVICE:
        break;

    case MESA_CAP_HQOS_SHAPER_RT:
        break;

    // VOP
    case MESA_CAP_VOP:
#if defined(VTSS_FEATURE_VOP)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_CFM:
#if defined(VTSS_FEATURE_VOP_CFM)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_V0:
#if defined(VTSS_FEATURE_VOP) && defined(VTSS_FEATURE_VOP_V0)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_V1:
#if defined(VTSS_FEATURE_VOP) && defined(VTSS_FEATURE_VOP_V1)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_V2:
#if defined(VTSS_FEATURE_VOP) && defined(VTSS_FEATURE_VOP_V2)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_TAGGING:
#if defined(VTSS_FEATURE_VOP_TAGGING)
        c = 1;
#endif
        break;

    case MESA_CAP_VOP_PATH_SERVICE_VOE_CNT:
#if defined(VTSS_PATH_SERVICE_VOE_CNT)
        c = VTSS_PATH_SERVICE_VOE_CNT;
#endif
        break;

    case MESA_CAP_VOP_PORT_VOE_CNT:
#if defined(VTSS_PORT_VOE_CNT)
        c = VTSS_PORT_VOE_CNT;
#endif
        break;

    case MESA_CAP_VOP_VOE_CNT:
#if defined(VTSS_VOE_CNT)
        c = VTSS_VOE_CNT;
#endif
        break;

    case MESA_CAP_VOP_DOWN_VOI_CNT:
#if defined(VTSS_DOWN_VOI_CNT)
        c = VTSS_DOWN_VOI_CNT;
#endif
        break;

    case MESA_CAP_VOP_UP_VOI_CNT:
#if defined(VTSS_UP_VOI_CNT)
        c = VTSS_UP_VOI_CNT;
#endif
        break;

    case MESA_CAP_VOP_VOI_CNT:
#if defined(VTSS_VOI_CNT)
        c = VTSS_VOI_CNT;
#endif
        break;

    case MESA_CAP_VOP_EVENT_ARRAY_SIZE:
#if defined(VTSS_EVENT_MASK_ARRAY_SIZE)
        c = VTSS_EVENT_MASK_ARRAY_SIZE;
#endif
        break;

    case MESA_CAP_VOP_EVENT_SUPPORTED:
#if defined(VTSS_FEATURE_VOP)
        c = MESA_VOE_EVENT_MASK_CCM_PERIOD | MESA_VOE_EVENT_MASK_CCM_ZERO_PERIOD | MESA_VOE_EVENT_MASK_CCM_PRIORITY | MESA_VOE_EVENT_MASK_CCM_LOC |
            MESA_VOE_EVENT_MASK_CCM_MEP_ID | MESA_VOE_EVENT_MASK_CCM_MEG_ID | MESA_VOE_EVENT_MASK_CCM_RX_RDI;
#if defined(VTSS_FEATURE_VOP_V2)
        c = c | MESA_VOE_EVENT_MASK_CCM_SRC_PORT_MOVE | MESA_VOE_EVENT_MASK_CCM_TLV_PORT_STATUS | MESA_VOE_EVENT_MASK_CCM_TLV_IF_STATUS | MESA_VOE_EVENT_MASK_CCM_MEG_LEVEL;
#endif
#endif
        break;
    case MESA_CAP_VOP_USED_AS_PTP_PROTOCOL:
#if defined(VTSS_ARCH_OCELOT)
        {
            mesa_chip_id_t chip_id;
            mesa_rc rc;

            rc = mesa_chip_id_get(inst, &chip_id);  /* check if chip revision is >= rev B */
            if (rc == MESA_RC_OK && chip_id.revision >= 1) {
                c = 1;
            }
        }
#endif
        break;

    case MESA_CAP_VOP_CCM_DEFECT:
#if defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

        // Clock
    case MESA_CAP_CLOCK:
#if defined(VTSS_FEATURE_CLOCK)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE:
#if defined(VTSS_FEATURE_SYNCE)
        c = 1;
#endif
        break;
    case MESA_CAP_SYNCE_CLK_CNT:
#if defined(VTSS_SYNCE_CLK_MAX)
        c = VTSS_SYNCE_CLK_MAX;
#endif
        break;

    case MESA_CAP_SYNCE_IN_TYPE:
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_OUT_STATION:
#if defined(VTSS_ARCH_SERVAL_T)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_ANN_AUTO_TRANSMIT:
#if defined(VTSS_FEATURE_SYNC_ANN_AUTO_TRANSMIT)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_USE_SWITCH_SELECTOR_WITH_PHY:
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_ALWAYS_USE_COPPER_MEDIA_CLK:
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_10G_DNU:
#if !defined(VTSS_FEATURE_CLOCK) && defined(VTSS_ARCH_SERVAL_T)
        c = 1;
#endif
        break;

    case MESA_CAP_SYNCE_SEPARATE_TIMING_DOMAINS:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X)
        c = 1;
#endif
        break;

    // Timestamping
    case MESA_CAP_TS:
#if defined(VTSS_FEATURE_TIMESTAMP)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_LATENCY_COMP:
#if defined(VTSS_FEATURE_TIMESTAMP_LATENCY_COMP)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_ORG_TIME:
#if defined(VTSS_FEATURE_TIMESTAMP_ORG_TIME)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_P2P_DELAY_COMP:
#if defined(VTSS_FEATURE_TIMESTAMP_P2P_DELAY_COMP)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_ASYMMETRY_COMP:
#if defined(VTSS_FEATURE_TIMESTAMP_ASYMMETRY_COMP)
        c = 1;
#endif
        break;
    case MESA_CAP_TS_HW_TIME_CNT_PR_SEC:
#if defined(VTSS_HW_TIME_CNT_PR_SEC)
        c = VTSS_HW_TIME_CNT_PR_SEC;
#endif
        break;

    case MESA_CAP_TS_HW_TIME_NSEC_PR_CNT:
#if defined(VTSS_HW_TIME_NSEC_PR_CNT)
        c = VTSS_HW_TIME_NSEC_PR_CNT;
#endif
        break;

    case MESA_CAP_TS_HW_TIME_WRAP_LIMIT:
#if defined(VTSS_HW_TIME_WRAP_LIMIT)
        c = VTSS_HW_TIME_WRAP_LIMIT;
#endif
        break;

    case MESA_CAP_TS_HW_TIME_MIN_ADJ_RATE:
#if defined(VTSS_HW_TIME_MIN_ADJ_RATE)
        c = VTSS_HW_TIME_MIN_ADJ_RATE;
#endif
        break;

    case MESA_CAP_TS_IO_CNT:
#if defined(VTSS_TS_IO_ARRAY_SIZE)
        c = VTSS_TS_IO_ARRAY_SIZE;
#endif
        break;
    case MESA_CAP_TS_DOMAIN_CNT:
#if defined(VTSS_TS_DOMAIN_ARRAY_SIZE)
        c = VTSS_TS_DOMAIN_ARRAY_SIZE;
#endif
        break;

    case MESA_CAP_TS_RESP_CTRL_CNT:
#if defined(VTSS_TS_RESP_CTRL_ARRAY_SIZE)
        c = VTSS_TS_RESP_CTRL_ARRAY_SIZE;
#endif
        break;

    case MESA_CAP_TS_MISSING_INTERRUPT:
#if defined(VTSS_MISSING_TIMESTAMP_INTERRUPT)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_MISSING_TX_INTERRUPT:
#if defined(VTSS_MISSING_TX_TIMESTAMP_INTERRUPT)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_ALT_CLOCK:
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)  /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_OAM:
        break;

    case MESA_CAP_TS_DELAY_REQ_AUTO_RESP:
#if defined(VTSS_FEATURE_DELAY_REQ_AUTO_RESP)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_PTP_RS422:
#if defined(VTSS_FEATURE_PTP_RS422)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_MISSING_PTP_ON_INTERNAL_PORTS:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    // TOD
    case MESA_CAP_TOD_SAMPLES_PR_SEC:
#if defined(VTSS_ARCH_JAGUAR_2) /* TBD_henrikb */
        c = 2;
#else
        c = 1;
#endif
        break;

    // Deprecated PHY capabilities
    case MESA_CAP_PHY_10G:
    case MESA_CAP_PHY_TS:
    case MESA_CAP_PHY_MALIBU_10G_PLUGIN_MOUNTED:
    case MESA_CAP_PHY_TS_NUMBER_OF_ENGINES:
    case MESA_CAP_PHY_10GBASE_KR:
        c = 0;
        break;

    case MESA_CAP_TS_PPS_VIA_CONFIGURABLE_IO_PINS:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_PPS_MODE_OVERRULES_CLK_OUT:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_PPS_OUT_OVERRULES_CLK_OUT:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_HAS_PTP_IO_PIN:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_HAS_ALT_PIN:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_PPS_IN_VIA_IO_PIN:
#if defined(VTSS_ARCH_LUTON26)
        c = MESA_EVENT_EXT_SYNC;
#else
        c = 0;
#endif
        break;
    case MESA_CAP_TS_USE_EXTERNAL_INPUT_SERVO:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;
    case MESA_CAP_TS_TOD_INTERNAL_TC_MODE:
#if defined(VTSS_ARCH_OCELOT)
        c = (MESA_TS_TOD_INTERNAL_TC_MODE_30BIT) |
            (MESA_TS_TOD_INTERNAL_TC_MODE_32BIT) |
            (MESA_TS_TOD_INTERNAL_TC_MODE_44BIT);
#elif defined(VTSS_ARCH_CARACAL)
        c = 0;
#else
        c = (MESA_TS_TOD_INTERNAL_TC_MODE_30BIT) |
            (MESA_TS_TOD_INTERNAL_TC_MODE_32BIT) |
            (MESA_TS_TOD_INTERNAL_TC_MODE_44BIT) |
            (MESA_TS_TOD_INTERNAL_TC_MODE_48BIT);

#endif
        break;

    case MESA_CAP_TS_HW_FWD_P2P_1STEP:
#if defined (VTSS_ARCH_OCELOT) || defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_HW_FWD_E2E_1STEP_INTERNAL:
#if defined (VTSS_ARCH_OCELOT) || defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_C_DTC_SUPPORTED:
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)  /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_INTERNAL_MODE_SUPPORTED:
#if defined(VTSS_ARCH_OCELOT) || defined (VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN966X) /* TBD_henrikb */
        c = 1;
#endif
        break;

    case MESA_CAP_TS_TWOSTEP_ALWAYS_REQUIRED:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_INTERNAL_PORTS_REQ_TWOSTEP:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_BC_TS_COMBO_IS_SPECIAL:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_TS_TWOSTEP_USE_PTP_ID:
#if defined(VTSS_ARCH_LUTON26) || defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    // Switching Chip
    case MESA_CAP_SOC_FAMILY:
#if defined(VTSS_ARCH_LUTON26)
        c = 2;

        /* Serval architectures */
#elif defined(VTSS_ARCH_OCELOT)
        c = 8;

        /* Jaguar 2 architectures */
#elif defined(VTSS_ARCH_JAGUAR_2_B)
        c = 5;
#elif defined(VTSS_ARCH_SERVAL_T)
        c = 6;
#elif defined(VTSS_ARCH_JAGUAR_2_C)
        c = 7;

        /* Jaguar 3 architectures */
#elif defined(VTSS_ARCH_SPARX5)
        c = 8;
#elif defined(VTSS_ARCH_LAN966X)
        c = 9;
#else
#error Unsupported platform
#endif
        break;

    // Deprecated PHY-MACSEC capabilities
    case MESA_CAP_PHY_MACSEC:
    case MESA_CAP_PHY_MACSEC_SA_CNT:
    case MESA_CAP_PHY_MACSEC_SC_CNT:
    case MESA_CAP_PHY_MACSEC_SECY_CNT:
        c = 0;
        break;

    case MESA_CAP_MEP_LUTON26:
#if defined(VTSS_ARCH_LUTON26)
        c = 1;
#endif
        break;

    case MESA_CAP_MEP_SERVAL:
#if defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    case MESA_CAP_MEP_JAGUAR2:
#if defined(VTSS_ARCH_JAGUAR_2)
        c = 1;
#endif
        break;

    case MESA_CAP_MEP_LBR_MCE_HW_SUPPORT:
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2)
        {
            mesa_chip_id_t chip_id = {};
            mesa_rc        rc;

            if ((rc = mesa_chip_id_get(NULL, &chip_id)) != VTSS_RC_OK) {
                break;
            }

#if defined(VTSS_ARCH_SERVAL_T)
            if (chip_id.revision >= 2) {
                // Rev C (if coming) is assumed to have TST and LBR counting updated
                c = 1; // H/W Support
            }
#else
            if (chip_id.revision >= 3) {
                // Rev D of JR2 has TST and LBR counting updated
                c = 1; // H/W Support
            }
#endif
        }
#endif
        break;

    case MESA_CAP_MEP_TST_BITRATE_MBPS:
#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_JAGUAR_2)
            c = 10000;
#elif defined(VTSS_ARCH_OCELOT)
            c = 2500;
#else
            c = 400;
#endif
        break;

    case MESA_CAP_MEP_PROP_DELAY_MEASUREMENT:
#if !defined(VTSS_ARCH_JAGUAR_2_CE) && !defined(VTSS_ARCH_OCELOT)
        c = 1;
#endif
        break;

    // Hardware Protection
    case MESA_CAP_HW_PROT:
#if defined(VTSS_FEATURE_HW_PROT)
        c = 1;
#endif
        break;

    // Hardware Protection for MPLS flows
    case MESA_CAP_HW_PROT_MPLS:
#if defined(VTSS_FEATURE_HW_PROT) && defined(VTSS_FEATURE_MPLS)
        c = 1;
#endif
        break;

        // Core Clock setup
    case MESA_CAP_INIT_CORE_CLOCK:
#if defined(VTSS_FEATURE_CORE_CLOCK)
        c = 1;
#endif
        break;

    // MRP
    case MESA_CAP_MRP:
#if defined(VTSS_FEATURE_MRP)
        c = 1;
#endif
        break;

    case MESA_CAP_MRP_CNT:
#if defined(VTSS_FEATURE_MRP)
        c = VTSS_MRP_CNT;
#endif
        break;

    // SGPIO to signal detect mapping
    case MESA_CAP_MISC_SGPIO_MAP:
#if defined(VTSS_ARCH_SPARX5)
        c = 1;
#endif

    default:
        {
            mesa_cap_callback_data_t *hook = NULL;
            if (vtss_misc_appdata_get((vtss_inst_t)inst, (void**)&hook) == VTSS_RC_OK && hook != NULL) {
                c = hook->cb(hook->inst, cap);
            } else {
                VTSS_E("Unknown capability: %d\n", cap);
                MESA_ASSERT(0);
            }
        }
        break;
    }

    return c;
}

uint32_t mesa_port_cnt(mesa_inst_t inst)
{
    return mesa_capability(inst, MESA_CAP_PORT_CNT);
}
