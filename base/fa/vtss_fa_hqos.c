// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_HQOS
#include "vtss_fa_cil.h"

#if defined(VTSS_FEATURE_HQOS)

/*
    A port can be configured to be in Normal mode or HQoS mode.
    Default the port is in Normal mode.

    In Normal mode (VTSS_HQOS_SCH_MODE_NORMAL) the scheduler hierarchy is like this:

                                 Layer 0

                               ┌────────┐ Port0 P0
                               │        │◄──────
                    ┌──────────┼ SE P0  │ PortN P0
                    │          │        │◄──────
          Layer 2   │          └────────┘
                    │
           ┌────────▼          ┌────────┐ Port0 P1
           │        │          │        │◄──────
    ◄──────┼ SE     ◄──────────┼ SE P1  │ PortN P1
           │        │          │        │◄──────
           └────────▲          └────────┘
                    │
                    │          ┌────────┐ Port0 P7
                    │          │        │◄──────
                    └──────────┼ SE P7  │ PortN P7
                               │        │◄──────
                               └────────┘
    At layer 0 there are one Scheduler Element (SE0-7) for each priority. Input to this SEs is
    from each ingress port.
    This is fully created when calling mesa_hqos_port_conf_set(MESA_HQOS_SCH_MODE_NORMAL)
    Configuration of scheduling and shaping is done by the vtss_qos_port_conf_set() API

    In HQoS mode (VTSS_HQOS_SCH_MODE_HIERARCHICAL) the scheduler hierarchy is like this:

                                                    Layer 0

                                                  ┌───────────┐ Priority0
                                                  │           │◄──────
                                       ┌──────────┼ HQOS-ID0  │ Priority7
                                       │          │           │◄──────
                             Layer 1   │          └───────────┘
                                       │
                              ┌────────+          ┌───────────┐ Priority0
                              │        │          │           │◄──────
                      ┌───────┼ SE     +──────────┼ HQOS-ID1  │ Priority7
                      │       │        │          │           │◄──────
                      │       └────────+          └───────────┘
                      │                │
                      │                │          ┌───────────┐ Priority0
                      │                │          │           │◄──────
                      │                └──────────┼ HQOS-ID64 │ Priority7
            Layer 2   │                           │           │◄──────
                      │                           └───────────┘
             ┌────────+
             │        │
      ◄──────┼ SE     │
             │        │                             Layer 0
             └────────+
                      │                           ┌───────────┐ Priority0
                      │                           │           │◄──────
                      │                ┌──────────┼ HQOS-ID65 │ Priority7
                      │                │          │           │◄──────
                      │      Layer 1   │          └───────────┘
                      │                │
                      │       ┌────────+          ┌───────────┐ Priority0
                      │       │        │          │           │<──────
                      └───────┼ SE     +──────────┼ HQOS-ID66 │ Priority7
                              │        │          │           │<──────
                              └────────+          └───────────┘
                                       │
                                       │          ┌───────────┐ Priority0
                                       │          │           │<──────
                                       └──────────┼ HQOS-ID128│ Priority7
                                                  │           │<──────
                                                  └───────────┘

    This SE hierarchy is created without Layer 0 SE added, when calling
    mesa_hqos_port_conf_set(MESA_HQOS_SCH_MODE_HIERARCHICAL).
    A L1 SE is created for adding priority HQOS elements.
    This priority L1 SE is connected to the L2 SE on input 15
    that is NOT part of the L2 DWRR, meaning it is strict scheduling on highest priority.

    On Layer 0 there can be added Scheduler Elements related to a HQOS-ID (hqos_id)
    Adding of one Layer 0 SE is done by calling mesa_hqos_add(hqos_id)
    Configuration of scheduling and shaping on Layer 0 is done by calling mesa_hqos_add(hqos_id)
    Layer 1 performs DWRR scheduling with weights according to the minimum bandwidth configured
    in the connected Layer 0 SE.
    Layer 2 performs DWRR scheduling with weights according to the minimum bandwidth configured
    for the sum of the connected Layer 0 SE.
    Layer 2 shaping (port shaping) can be done by the mesa_qos_port_conf_set() API.
    The DWRR on Layer 1 and 2 is configured automatically based on the Layer 0 configuration.

    Ingress classification to a HQOS-ID can be done as a per VLAN or per IFLOW attribute
    configured by mesa_vlan_vid_conf_set(hqos_id) and mesa_iflow_conf_set(hqos_id) respectively.

    A level 0 SE can be added with the same HQOS-ID at multiple ports, enabling a multicast frame
    classified to a HQOS-ID to hit a specific hierarchical SE on each port.

    L0 considerations:
    A Large SE has 72 inputs. This requires 9 small SE with each 8 input - 8 * 9 = 72 inputs.
    A chip ports in normal hierarchy needs 8 large SE (one per prio) - 8 * 9 = 72 small SE
    All 70 chip ports in normal hierarchy needs in total 70 * 72 = 5040 small SE
    Chip port 0:
    Large SE the first 64 SE has index    0 to 63.   The 9th SE per prio has index 4480 to 4487
    Chip port 1:
    Large SE the first 64 SE has index   64 to 127.  The 9th SE per prio has index 4488 to 4495
    Chip port 69:
    Large SE the first 64 SE has index 4416 to 4479. The 9th SE per prio has index 5032 to 5039

    L1 SE has 64 inputs
    L2 SE has 16 inputs

    Maximum L0 SEs per port:
    Port 0 - 64 are physical ports.
    Port 65 - 66 are CPU ports and 67 - 69 are Device (internal) ports.
    These SEs cannot be used for HQOS.
    If all front ports are active in a configuration, then only the 72 SEs from the
    default hierarchy can be used for HQOS.
    A pool of extra SEs to be used for HQOS, are created by the not active
    front ports - 72 SEs per port.

    L1 SE:
    There is a maximum of 64 in the chip.

    VPORT:
    There is one VPORT number for each L0 SE - 5040.
    In Normal hierarchy mode a port is using 8 VPORTS
    Chip port 0 VPORT 0-7
    Chip port 1 VPORT 8-15

    QGRP:
    There are 1023 QGRP numbers - 0 is not used as it is NON service.

    Unknown QGRP:
    In Hierarchical Mode, Per port a L0 SE and VPORT is allocated to handle unknown QGRP.
    The Unknown L0 SE is connected to L2 SE input 0.
    In the L2 SE this input can have a "low" DWRR bandwidth.

    QUEUE SHAPER:
    There are 6800 Queue Shapers.
    It requires up to 8 Queue Shapers to implement HQOS element with shaping on all queues.
    That gives a maximum of 850 HQOS elements
*/

#define VTSS_PORT_CNT            70
#define VTSS_FRONT_PORT_CNT      65
#define VTSS_HQOS_QGRP_CNT       1024
#define VTSS_HQOS_L0_CE_CNT      5040
#define VTSS_HQOS_PORT_L0_SE_CNT 72
#define VTSS_HQOS_CHIP_L0_SE_CNT (VTSS_PORT_CNT * VTSS_HQOS_PORT_L0_SE_CNT)
#define VTSS_HQOS_CHIP_L1_SE_CNT 64
// There are 16 inputs on L2.
// Input 0 is used for Unknown.
// Input 1-4 is normal services
// Input 15 (highest) in used for priority services (strict)
#define VTSS_HQOS_L2_INPUT_CNT   16
#define VTSS_HQOS_PORT_L1_SE_CNT (VTSS_HQOS_L2_INPUT_CNT - 2)
#define VTSS_HQOS_PORT_VPORT_CNT 8
#define VTSS_HQOS_CHIP_VPORT_CNT 8191
#define VTSS_HQOS_CHIP_QSHP_CNT  6800

#define L1_ENTRY_COUNT (hier->entry_count / 64 + ((hier->entry_count % 64) != 0) ? 1 : 0)

static vtss_hqos_sch_mode_t sch_port_mode_get(vtss_state_t        *vtss_state,
                                              const vtss_port_no_t port_no)
{
    u32 chip_port = VTSS_CHIP_PORT(port_no);
    u32 value;

    REG_RD(VTSS_XQS_QMAP_PORT_MODE(chip_port), &value);
    switch (VTSS_X_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(value)) {
    case 3: // this value is default according to Fireant VML.
    case 0: return VTSS_HQOS_SCH_MODE_NORMAL;
    case 1: return VTSS_HQOS_SCH_MODE_HIERARCHICAL;
    default:
        VTSS_E("Port %u: Unexpected Port Mode: %u", port_no,
               VTSS_X_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(value));
        return VTSS_HQOS_SCH_MODE_NORMAL;
    }
}

#define L0_USED_BF_GET(a, n) ((a[(n) / 32] & (1 << ((n) % 32))) ? 1 : 0)
#define L0_USED_BF_SET(a, n, v)                                                                    \
    do {                                                                                           \
        if (v) {                                                                                   \
            a[(n) / 32] |= (1U << ((n) % 32));                                                     \
        } else {                                                                                   \
            a[(n) / 32] &= ~(1U << ((n) % 32));                                                    \
        }                                                                                          \
    } while (0)

// For now queue shaper is not implemented due to chip restrictions
#if 0
// A BF list of all the used Queue Shapers.
static u32 qshp_used[(VTSS_HQOS_CHIP_VPORT_CNT / 32) + 1] = {};
static vtss_rc qshp_unused_find(u32 *qshp)
{
    // Find unused QSHP
    for (*qshp = 0; *qshp < VTSS_HQOS_CHIP_QSHP_CNT; (*qshp)++) {
        if (L0_USED_BF_GET(qshp_used, *qshp) == 0) {
            return VTSS_RC_OK;
        }
    }
    VTSS_E("Unused QSHP not found");
    *qshp = 0;
    return VTSS_RC_ERROR;
}
#endif

// A BF list of all the used VPORTs. This is initialized so all VPORTs used for
// Normal Mode hierarchy on active Chip Port are marked as used.
// Also the CPU and device ports are marked as used.
static u32     vport_used[(VTSS_HQOS_CHIP_VPORT_CNT / 32) + 1] = {};
static vtss_rc vport_unused_find(u32 *vport)
{
    // Find unused VPORT among unused chip ports
    for (*vport = 0; *vport < VTSS_HQOS_CHIP_VPORT_CNT; (*vport)++) {
        if (L0_USED_BF_GET(vport_used, *vport) == 0) {
            return VTSS_RC_OK;
        }
    }
    VTSS_E("Unused VPORT not found");
    *vport = 0;
    return VTSS_RC_ERROR;
}
static vtss_rc vport_used_set(vtss_state_t *vtss_state, u32 chip_port)
{
    u32 i, qgrp, vport, value;

    if (chip_port < VTSS_FRONT_PORT_CNT) {
        // A Front Chip port in Normal Mode used 8 VPORTs.
        for (i = 0; i < 8; i++) {
            vport = (chip_port * 8) + i;
            L0_USED_BF_SET(vport_used, vport, 1);
        }
    } else {
        // The CPU and Device port uses unknown VPORTs - have to read the from registers
        vport = 0;
        for (qgrp = 0; qgrp < VTSS_HQOS_QGRP_CNT; ++qgrp) {
            REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(qgrp));
            REG_RD(VTSS_XQS_QMAP_VPORT_TBL(0, chip_port), &value);
            vport = VTSS_X_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(value);
            L0_USED_BF_SET(vport_used, vport, 1);
        }
    }
    return VTSS_RC_OK;
}

// A BF list of all the used L0 SEs. This is initialized so all SEs used for
// Normal Mode hierarchy on active Chip Port are marked as used.
// Also the CPU and device ports are marked as used.
static u32     l0_used[(VTSS_HQOS_CHIP_L0_SE_CNT / 32) + 1] = {};
static vtss_rc l0_unused_find(u32 *se)
{

    // Find unused L0 SE among unused chip ports
    for (*se = 0; *se < VTSS_HQOS_CHIP_L0_SE_CNT; (*se)++) {
        if (L0_USED_BF_GET(l0_used, *se) == 0) {
            return VTSS_RC_OK;
        }
    }
    VTSS_D("Unused L0 SE not found");
    *se = 0;
    return VTSS_RC_ERROR;
}
static vtss_rc l0_used_set(vtss_state_t *vtss_state, u32 chip_port)
{
    u32 i, se;

    // A Chip port has 72 CEs. The first 64 is in the range 0 - 4479.
    // The last 8 in the range 4480 - 5039
    for (i = 0; i < 64; i++) {
        se = 0 + (chip_port * 64) + i;
        L0_USED_BF_SET(l0_used, se, 1);
    }
    for (i = 0; i < 8; i++) {
        se = 4480 + (chip_port * 8) + i;
        L0_USED_BF_SET(l0_used, se, 1);
    }
    return VTSS_RC_OK;
}

static u32 find_l1_index(vtss_hqos_hier_port_t *hier, u32 se)
{
    u32 index;

    // Find the L1 index
    for (index = 0; index < VTSS_HQOS_PORT_L1_MAX; ++index) {
        if (hier->l1_ses[index].se == se) {
            return index;
        }
    }
    return index;
}

static BOOL l0_ce_used(vtss_hqos_hier_port_t *hier, u32 se)
{
    u32 l0_index;

    if (hier->unknown_l0_se == se) {
        return TRUE;
    }
    for (l0_index = 0; l0_index < VTSS_HQOS_PORT_L0_MAX; ++l0_index) {
        if (hier->l0_ses[l0_index].se == se) {
            return TRUE;
        }
    }
    return FALSE;
}

static vtss_rc find_free_l0_se(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *se)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier = &hqos->hier_conf[port_no];
    u32                    chip_port = VTSS_CHIP_PORT(port_no);
    u32                    i;

    // Try find free SE on this Chip Port
    // A Chip port has 72 CEs. The first 64 is in the range 0 - 4479.
    // The last 8 in the range 4480 - 5039
    for (i = 0; i < 64; i++) {
        *se = 0 + (chip_port * 64) + i;
        // Check if this SE is in use
        if (!l0_ce_used(hier, *se)) {
            return VTSS_RC_OK;
        }
    }
    for (i = 0; i < 8; i++) {
        *se = 4480 + (chip_port * 8) + i;
        // Check if this SE is in use
        if (!l0_ce_used(hier, *se)) {
            return VTSS_RC_OK;
        }
    }
    // Find unused SE among unused Chip Port's
    return l0_unused_find(se);
}

static vtss_rc free_l0_se(vtss_state_t *vtss_state, u32 chip_port, u32 se)
{
    u32 se_start;

    // First check if the SE is a Normal Mode SE for this port
    // The Normal mode SEs must NOT be marked as unused in l0_used
    // In the range 0 - 4479.
    se_start = (chip_port * 64);
    if ((se >= se_start) && (se <= (se_start + 63))) {
        return VTSS_RC_OK;
    }
    // In the range 4480 - 5039.
    se_start = 4480 + (chip_port * 8);
    if ((se >= se_start) && (se <= (se_start + 8))) {
        return VTSS_RC_OK;
    }
    // This is a L0 SE from a unused Chip Port - mark as not used
    L0_USED_BF_SET(l0_used, se, 0);

    // Configure L0 SE to point to invalid chip port
    REG_WR(VTSS_HSCH_HSCH_L0_CFG(se), VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(1) |
                                          VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(70) |
                                          VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(0));

    return VTSS_RC_OK;
}

static vtss_hqos_l0_se_t *find_hier_se(vtss_hqos_hier_port_t *hier, vtss_hqos_id_t hqos_id)
{
    u32 l0;

    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
        if ((hier->l0_ses[l0].se != VTSS_HQOS_SE_NONE) && (hier->l0_ses[l0].hqos_id == hqos_id)) {
            return &hier->l0_ses[l0];
        }
    }
    return NULL;
}

static vtss_hqos_l0_se_t *find_free_hier_se(vtss_hqos_hier_port_t *hier)
{
    u32 l0;

    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
        if (hier->l0_ses[l0].se == VTSS_HQOS_SE_NONE) {
            return &hier->l0_ses[l0];
        }
    }
    return NULL;
}

static vtss_rc find_free_l1_se(vtss_state_t *vtss_state, u32 *l1_se)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier;
    BOOL                   l1_used[VTSS_HQOS_CHIP_L1_SE_CNT] = {};
    u32                    port, l1;

    for (port = VTSS_PORT_NO_START; port < vtss_state->port_count; port++) {
        if (hqos->port_conf[port].sch_mode != VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
            /* This port is not hierarchical mode */
            continue;
        }
        hier = &hqos->hier_conf[port];
        for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
            if (hier->l1_ses[l1].se != VTSS_HQOS_SE_NONE) {
                l1_used[hier->l1_ses[l1].se] = TRUE;
            }
        }
        if (hier->priority_l1_se != VTSS_HQOS_SE_NONE) {
            l1_used[hier->priority_l1_se] = TRUE;
        }
    }
    for (*l1_se = 0; *l1_se < VTSS_HQOS_CHIP_L1_SE_CNT; (*l1_se)++) {
        if (l1_used[*l1_se] == FALSE) {
            /* This L1 is not used */
            return VTSS_RC_OK;
        }
    }

    VTSS_D("No free L1 SE was found");
    *l1_se = 0;
    return VTSS_RC_ERROR;
}

static void free_l1_se(vtss_hqos_hier_port_t *hier, u32 se)
{
    u32 l0, l1_index;

    // Check if L1 SE is no more used
    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; l0++) {
        if (hier->l0_ses[l0].l1_se == se) {
            break;
        }
    }
    if (l0 == VTSS_HQOS_PORT_L0_MAX) {
        // The L1 SE is not used any more
        l1_index = find_l1_index(hier, se);
        hier->l1_ses[l1_index].se = VTSS_HQOS_SE_NONE;
    }
}

static vtss_rc find_free_vport(vtss_state_t *vtss_state, vtss_port_no_t port_no, u32 *vport)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier = &hqos->hier_conf[port_no];
    u32                    chip_port = VTSS_CHIP_PORT(port_no);
    u32                    i, l0;

    // Try find free VPORT on this Chip Port
    // A Chip port has 8 VPORTs.
    for (i = 0; i < 8; i++) {
        *vport = (chip_port * 8) + i;
        // Check if this VPORT is in use
        if (hier->unknown_vport == *vport) {
            continue;
        }
        for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; l0++) {
            if ((hier->l0_ses[l0].se != VTSS_HQOS_SE_NONE) && (hier->l0_ses[l0].vport == *vport)) {
                break;
            }
        }
        if (l0 < VTSS_HQOS_PORT_L0_MAX) {
            continue;
        }
        // Unused
        return VTSS_RC_OK;
    }
    // Find unused VPORT among unused Chip Port's
    return vport_unused_find(vport);
}

static void free_vport(u32 chip_port, u32 vport)
{
    u32 vport_start;

    // Check if the VPORT is a Normal Mode VPORT for this port
    // The Normal mode VPORTs must not be marked as unused in vport_used
    vport_start = chip_port * 8;
    if ((vport >= vport_start) && (vport <= (vport_start + 7))) {
        return;
    }
    // This is a VPORT from a unused Chip Port
    L0_USED_BF_SET(vport_used, vport, 0);
}

static u32 find_free_l1_index(vtss_hqos_hier_port_t *hier)
{
    u32 l1;

    for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
        if (hier->l1_ses[l1].se == VTSS_HQOS_SE_NONE) {
            return l1;
        }
    }
    return VTSS_HQOS_PORT_L1_MAX;
}

static BOOL find_free_priority_l1_input(vtss_hqos_hier_port_t *hier, u32 *l1_input)
{
    u32  i, l0;
    BOOL used_input[64]; // L1 has 64 inputs

    memset(used_input, 0, sizeof(used_input));
    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
        if (hier->l0_ses[l0].l1_se == hier->priority_l1_se) {
            // This L0 SE is connected to the Priority L1 SE
            used_input[hier->l0_ses[l0].l1_input] = TRUE;
        }
    }
    for (i = 0; i < 64; ++i) {
        if (used_input[i] == FALSE) {
            *l1_input = i;
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL find_free_l1_input(vtss_hqos_hier_port_t *hier, u32 *l1_se, u32 *l1_input)
{
    u32  i, l1, l0;
    BOOL used_input[64]; // L1 has 64 inputs

    for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
        if (hier->l1_ses[l1].se == VTSS_HQOS_SE_NONE) {
            continue;
        }
        memset(used_input, 0, sizeof(used_input));
        for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
            if (hier->l0_ses[l0].l1_se == hier->l1_ses[l1].se) {
                // This L0 SE is connected to this L1 SE
                used_input[hier->l0_ses[l0].l1_input] = TRUE;
            }
        }
        for (i = 0; i < 64; ++i) {
            if (used_input[i] == FALSE) {
                *l1_se = hier->l1_ses[l1].se;
                *l1_input = i;
                return TRUE;
            }
        }
    }
    return FALSE;
}

static u32 find_free_l2_input(vtss_hqos_hier_port_t *hier)
{
    u32  l1, i;
    BOOL used_input[16] = {};

    used_input[0] = TRUE;  // Used for Unknown QGRP
    used_input[15] = TRUE; // Used for Priority services - strict
    for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
        if (hier->l1_ses[l1].se != VTSS_HQOS_SE_NONE) {
            used_input[hier->l1_ses[l1].l2_input] = TRUE;
        }
    }
    for (i = 0; i < 16; ++i) {
        if (used_input[i] == FALSE) {
            return i;
        }
    }
    return VTSS_HQOS_SE_NONE;
}

static vtss_rc fa_l1_l2_dwrr_configure(vtss_state_t          *vtss_state,
                                       u32                    chip_port,
                                       vtss_hqos_hier_port_t *hier,
                                       u32                    l1_se)
{
    u32 i, l0, l1, total, permille, highest_input, input_cnt;

    // There are 15 DWRR inputs on the L2 SE. Input 15 is used for priority services (strict)
    // There are 64 DWRR inputs on the L1 SE.
    u32        min_rate[64] = {};
    vtss_pct_t ip[64] = {};

    // Configure the L1 DWRR
    // -----------------------

    // Set the minimum rate for all L1 input to one kbps
    for (i = 0; i < 64; ++i) {
        min_rate[i] = 1;
    }

    // L1 SE DWRR is based on the minimum rates of the connected L0 SE
    // Calculate the L0 SE total minimum rate
    highest_input = 0;
    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
        if (hier->l0_ses[l0].l1_se == l1_se) {
            // This L0 SE is connected to this L1 SE
            min_rate[hier->l0_ses[l0].l1_input] = hier->l0_ses[l0].conf.min_rate;
            highest_input = (hier->l0_ses[l0].l1_input > highest_input) ? hier->l0_ses[l0].l1_input
                                                                        : highest_input;
        }
    }
    input_cnt = highest_input + 1;
    for (i = 0, total = 0; i < input_cnt; ++i) {
        total += min_rate[i];
    }

    // Calculate the bandwidth percent for each L1 input
    for (i = 0; i < input_cnt; ++i) {
        permille = (min_rate[i] * 1000) / total;
        ip[i] = MAX(1, ((permille / 10) + (((permille % 10) >= 5) ? 1 : 0)));
    }
    // VTSS_E("min_rate %u-%u-%u-%u-%u-%u-%u-%u-%u-%u", min_rate[0], min_rate[1], min_rate[2],
    // min_rate[3], min_rate[4], min_rate[59], min_rate[60], min_rate[61], min_rate[62],
    // min_rate[63]); VTSS_E("Layer 1 l1_se %u  total_rate %u  dwrr_cnt %u", l1_se, total,
    // input_cnt); VTSS_E("input_pct "
    //         "%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[0], ip[1], ip[2], ip[3], ip[4], ip[5], ip[6], ip[7], ip[8], ip[9]);
    // VTSS_E("%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[10], ip[11], ip[12], ip[13], ip[14], ip[15], ip[16], ip[17], ip[18], ip[19]);
    // VTSS_E("%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[20], ip[21], ip[22], ip[23], ip[24], ip[25], ip[26], ip[27], ip[28], ip[29]);
    // VTSS_E("%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[30], ip[31], ip[32], ip[33], ip[34], ip[35], ip[36], ip[37], ip[38], ip[39]);
    // VTSS_E("%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[40], ip[41], ip[42], ip[43], ip[44], ip[45], ip[46], ip[47], ip[48], ip[49]);
    // VTSS_E("%u-%u-%u-%u-%u-%u-%u-%u-%u-%u",
    //        ip[50], ip[51], ip[52], ip[53], ip[54], ip[55], ip[56], ip[57], ip[58], ip[59]);
    // VTSS_E("%u-%u-%u-%u",
    //        ip[60], ip[61], ip[62], ip[63]);

    if (VTSS_RC_OK != fa_qos_dwrr_conf_set(vtss_state, l1_se, 1, TRUE, input_cnt, ip)) {
        VTSS_E("L1 DWRR configuration failed");
        return VTSS_RC_ERROR;
    }

    if (l1_se == hier->priority_l1_se) {
        // This is the Priority L1 SE that is not part of the L2 DWRR
        return VTSS_RC_OK;
    }

    // Configure the L2 DWRR
    // -----------------------

    // Set the minimum rate for all L2 input to one kbps
    for (i = 0; i < 15; ++i) {
        min_rate[i] = 1;
        ip[i] = 0;
    }

    // Calculate the minimum rate for each L1 SE
    // For each L1 SE calculate the total of the connected L0 minimum rate
    highest_input = 0;
    for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
        if (hier->l1_ses[l1].se == VTSS_HQOS_SE_NONE) {
            continue;
        }
        total = 0;
        for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
            if (hier->l0_ses[l0].l1_se == hier->l1_ses[l1].se) {
                // This L0 SE is connected to this L1 SE
                total += hier->l0_ses[l0].conf.min_rate;
            }
        }
        if (total != 0) {
            // Some L0 SE is connected to this L1
            min_rate[hier->l1_ses[l1].l2_input] = total;
            highest_input = (hier->l1_ses[l1].l2_input > highest_input) ? hier->l1_ses[l1].l2_input
                                                                        : highest_input;
        }
    }
    input_cnt = highest_input + 1;

    // Calculate the L2 SE total minimum rate.
    total = 0;
    for (i = 0; i < input_cnt; ++i) {
        total += min_rate[i];
    }

    // Calculate the bandwidth percent for each L2 input
    for (i = 0; i < input_cnt; ++i) {
        permille = (min_rate[i] * 1000) / total;
        ip[i] = MAX(1, ((permille / 10) + (((permille % 10) >= 5) ? 1 : 0)));
    }
    // VTSS_E("min_rate %u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", min_rate[0], min_rate[1],
    // min_rate[2], min_rate[3], min_rate[4], min_rate[5], min_rate[6], min_rate[7], min_rate[8],
    // min_rate[9], min_rate[10], min_rate[11], min_rate[12], min_rate[13], min_rate[14]);
    // VTSS_E("min_rate %u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", min_rate[0], min_rate[1],
    // min_rate[2], min_rate[3], min_rate[4], min_rate[5], min_rate[6], min_rate[7], min_rate[8],
    // min_rate[9], min_rate[10], min_rate[11], min_rate[12], min_rate[13], min_rate[14]);
    // VTSS_E("Layer 2 se %u total_rate %u dwrr_cnt %u", chip_port, total, input_cnt);
    // VTSS_E("input_pct %u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u-%u", ip[0], ip[1], ip[2], ip[3],
    // ip[4], ip[5], ip[6], ip[7], ip[8], ip[9], ip[10], ip[11], ip[12], ip[13], ip[14]);
    if (VTSS_RC_OK != fa_qos_dwrr_conf_set(vtss_state, chip_port, 2, TRUE, input_cnt, ip)) {
        VTSS_E("L2 DWRR configuration failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

static vtss_rc sch_port_mode_normal(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier = &hqos->hier_conf[port_no];
    u32                    chip_port = VTSS_CHIP_PORT(port_no);
    u32                    l0_se, i, qgrp, large_mask, l0_se_start, vport_start;

    /* Set the SERVICE frame port mode to normal */
    REG_WRM(VTSS_XQS_QMAP_PORT_MODE(chip_port), VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(0),
            VTSS_M_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE);

    // Configure Normal hierarchy
    // --------------------------

    // Make all Normal hierarchy L0 SEs big
    // A Normal hierarchy port uses 8 large L0 SEs
    // In every register replication there are large SE configuration bits for 4 ports (8 * 4 = 32)
    // The 8 large SEs give a mask = 0xFF
    large_mask = 0x0FF << ((chip_port % 4) * 8);
    REG_WRM(VTSS_HSCH_HSCH_LARGE_ENA(chip_port / 4), large_mask, large_mask);

    // Configure L0 SE
    // Each port in Normal Mode is using 64 L0 SE with this start number
    l0_se_start = chip_port * 64;
    for (i = 0; i < 64; ++i) {
        l0_se = l0_se_start + i;
        // Link L0 SE to L2 SE
        REG_WR(VTSS_HSCH_HSCH_L0_CFG(l0_se), VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(1) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(chip_port) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(i / 8));

        // L0 SE Default configuration
        REG_WR(VTSS_HSCH_SE_CFG(l0_se), 0);
        REG_WR(VTSS_HSCH_CIR_CFG(l0_se), 0);
        REG_WR(VTSS_HSCH_EIR_CFG(l0_se), 0);
    }
    // This has no practical relevance as in normal mode (Large SE) the
    // configuration SE in range 4480 - 5039 is not used
    for (i = 0; i < 8; ++i) {
        l0_se = 4480 + (chip_port * 8) + i;
        // Configure L0 SE to point to invalid chip port
        REG_WR(VTSS_HSCH_HSCH_L0_CFG(l0_se), VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(1) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(70) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(0));
    }

    // Each port in Normal Mode is using 8 VPORT numbers with this start number
    vport_start = chip_port * 8;

    // Configure all QGRP on this port to Normal Mode. They all generate same VPORT
    for (qgrp = 0; qgrp < VTSS_HQOS_QGRP_CNT; ++qgrp) {
        REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(qgrp));
        REG_WR(VTSS_XQS_QMAP_VPORT_TBL(0, chip_port),
               VTSS_F_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(vport_start));
    }

    // Configure the SE Table to Normal Mode
    for (i = 0; i < 8; ++i) {
        REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(vport_start + i));
        l0_se = l0_se_start + (i * 8);
        REG_WR(VTSS_XQS_QMAP_SE_TBL(0), VTSS_F_XQS_QMAP_SE_TBL_QMAP_SE_VAL(l0_se));
    }

    // Configure the shapers and DWRR of the Normal Mode hierarchy
    // based on vtss_qos_port_conf_t in vtss_state
    (void)vtss_cil_qos_port_conf_update(vtss_state, port_no);

    // Free the Unknown SE and VPORT
    (void)free_l0_se(vtss_state, chip_port, hier->unknown_l0_se);
    free_vport(chip_port, hier->unknown_vport);

    // Clear the state
    for (i = 0; i < VTSS_HQOS_PORT_L0_MAX; ++i) {
        hier->l0_ses[i].se = VTSS_HQOS_SE_NONE;
    }
    for (i = 0; i < VTSS_HQOS_PORT_L1_MAX; ++i) {
        hier->l1_ses[i].se = VTSS_HQOS_SE_NONE;
    }
    hier->unknown_l0_se = VTSS_HQOS_SE_NONE;
    hier->priority_l1_se = VTSS_HQOS_SE_NONE;
    hier->unknown_vport = 0;
    hier->entry_count = 0;

    return VTSS_RC_OK;
}

static vtss_rc sch_port_mode_hier(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier = &hqos->hier_conf[port_no];
    vtss_shaper_t          shaper = {};
    u32                    chip_port = VTSS_CHIP_PORT(port_no);
    u32                    qgrp, large_mask, priority_l1_se, unknown_l0_se, unknown_vport;

    // Set both NON-SERVICE and SERVICE frame port mode to hierarchical
    REG_WRM(VTSS_XQS_QMAP_PORT_MODE(chip_port), VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE(1),
            VTSS_M_XQS_QMAP_PORT_MODE_QMAP_MODE_NONSERVICE);
    REG_WRM(VTSS_XQS_QMAP_PORT_MODE(chip_port), VTSS_F_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(1),
            VTSS_M_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE);

    // Find a free L0 SE and VPORT to be used for handling Unknown QGRPs
    if (VTSS_RC_OK != find_free_l0_se(vtss_state, port_no, &unknown_l0_se)) {
        VTSS_D("No free Unknown L0 SE was found");
        return VTSS_RC_ERROR;
    }
    if (VTSS_RC_OK != find_free_vport(vtss_state, port_no, &unknown_vport)) {
        VTSS_D("No free Unknown VPORT was found");
        return VTSS_RC_ERROR;
    }
    /* Find a free L1 SE to be used for Priority services */
    if (VTSS_RC_OK != find_free_l1_se(vtss_state, &priority_l1_se)) {
        VTSS_E("No free Priority L1 SE was found");
        return VTSS_RC_ERROR;
    }

    // All required resources are found
    L0_USED_BF_SET(l0_used, unknown_l0_se, 1);    // Mark L0 SE as used
    L0_USED_BF_SET(vport_used, unknown_vport, 1); // VPORT as used
    hier->unknown_l0_se = unknown_l0_se;
    hier->priority_l1_se = priority_l1_se;
    hier->unknown_vport = unknown_vport;
    hier->entry_count = 0;

    // link the Unknown L0 to input in L2 SE - the first one
    // Input 0 is chosen as Unknown input. This will be configured with "low" bandwidth in L2 DWRR
    // Next layer is L2
    REG_WRM(VTSS_HSCH_HSCH_L0_CFG(unknown_l0_se),
            VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(chip_port) | VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(1),
            VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(0));

    // Link the Priority L1 SE to input in L2 SE - the last one
    // Input 15 is chosen as Priority input. This will not be part of the L2 DWRR - running strict
    // Next layer is L2
    REG_WR(VTSS_HSCH_HSCH_L1_CFG(priority_l1_se),
           VTSS_F_HSCH_HSCH_L1_CFG_NEXT_IDX(chip_port) | VTSS_F_HSCH_HSCH_L1_CFG_NEXT_INP(15));

    // Make all Normal hierarchy L0 SEs small
    // A Normal hierarchy port uses 8 large L0 SEs
    // In every replication there are large SE configuration bits for 4 ports (8 * 4 = 32)
    // The 8 large SEs give a mask = 0xFF
    large_mask = 0x0FF << ((chip_port % 4) * 8);
    REG_WRM(VTSS_HSCH_HSCH_LARGE_ENA(chip_port / 4), 0, large_mask);

    // Configure all QGRP on this port to point at the Unknown SE
    // All QGRP on this port generate Unknown VPORT
    for (qgrp = 0; qgrp < VTSS_HQOS_QGRP_CNT; ++qgrp) {
        REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(qgrp));
        REG_WR(VTSS_XQS_QMAP_VPORT_TBL(0, chip_port),
               VTSS_F_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(unknown_vport));
    }

    // The Unknown VPORT points to Unknown SE
    REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(unknown_vport));
    REG_WR(VTSS_XQS_QMAP_SE_TBL(0), VTSS_F_XQS_QMAP_SE_TBL_QMAP_SE_VAL(unknown_l0_se));

    // Configure the Unknown SE output shapers to a "low" rate
    // to minimize unknown frame transmission
    shaper.level = 1;
    shaper.rate = 10;
    // DLB is currently not supported on FA
    //    shaper.eir = VTSS_BITRATE_DISABLED;
    if (VTSS_RC_OK != vtss_fa_qos_shaper_conf_set(vtss_state, &shaper, 0, unknown_l0_se, 0, 0)) {
        VTSS_E("Output shaper configuration failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_hqos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_port_conf_t *port_conf;
    vtss_hqos_hier_port_t *hier;

    VTSS_D("port_no: %u", port_no);

    if (port_no >= vtss_state->port_count) {
        VTSS_E("Invalid port number %u", port_no);
        return VTSS_RC_ERROR;
    }

    port_conf = &hqos->port_conf[port_no];
    hier = &hqos->hier_conf[port_no];

    if (port_conf->sch_mode == sch_port_mode_get(vtss_state, port_no)) {
        VTSS_E("SCH mode must change");
        return VTSS_RC_ERROR;
    }

    if (port_conf->sch_mode == VTSS_HQOS_SCH_MODE_NORMAL) {
        if (hier->entry_count != 0) {
            VTSS_E("To go to SCH Mode Normal, the HQOS entries must be deleted first");
            return VTSS_RC_ERROR;
        }
        sch_port_mode_normal(vtss_state, port_no);
    } else if (port_conf->sch_mode == VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
        sch_port_mode_hier(vtss_state, port_no);
    } else {
        VTSS_E("Unknown SCH mode %u", port_conf->sch_mode);
    }

    return VTSS_RC_OK;
}

static vtss_rc qshp_alloc(vtss_state_t *vtss_state, vtss_hqos_l0_se_t *hier_se)
{
#if 0
    u32 i;

    if (hier_se->qshp != VTSS_HQOS_QSHP_NONE) {
        // Queue Shaper is already allocated
        return VTSS_RC_OK;
    }

    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        if (hier_se->conf.shaper_queue[i].rate != VTSS_BITRATE_DISABLED) {
            break;
        }
    }

    if (i == VTSS_QUEUE_ARRAY_SIZE) {
        // Queue Shaper is NOT required
        REG_WR(VTSS_HSCH_QSHP_ALLOC_CFG(hier_se->se),
               VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(7) | VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(0) |
               VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_BASE(0));
        return VTSS_RC_OK;
    }

    hier_se->qshp = 0;
    if (VTSS_RC_OK != qshp_unused_find(&hier_se->qshp)) {
        // Unused Queue Shaper cannot be found
        VTSS_E("Unused Queue Shaper cannot be found");
        return VTSS_RC_ERROR;
    }

    // Allocate the Queue Shaper to this L0 SE. Allocate eight, one for each possible priority
    REG_WR(VTSS_HSCH_QSHP_ALLOC_CFG(hier_se->se),
           VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(0) | VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(7) |
           VTSS_F_HSCH_QSHP_ALLOC_CFG_QSHP_BASE(hier_se->qshp * 8));
#endif

    return VTSS_RC_OK;
}

#if 0
static void hqos_to_qos_shaper(const vtss_hqos_queue_shaper_t *hqos_shapers, vtss_shaper_t *shapers)
{
    u32 i;
    memset(shapers, 0, (sizeof(*shapers) * VTSS_QUEUE_ARRAY_SIZE));
    for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; ++i) {
        shapers[i].level = hqos_shapers[i].level;
        shapers[i].rate = hqos_shapers[i].rate;
        shapers[i].mode = hqos_shapers[i].mode;
    }
}
#endif

vtss_rc vtss_cil_hqos_add(vtss_state_t                 *vtss_state,
                          const vtss_port_no_t          port_no,
                          const vtss_hqos_id_t          hqos_id,
                          const vtss_hqos_conf_t *const conf)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_port_conf_t *port_conf;
    vtss_hqos_hier_port_t *hier;
    vtss_hqos_l0_se_t     *hier_se;
    //    vtss_shaper_t shapers[VTSS_QUEUE_ARRAY_SIZE];
    u32  chip_port = VTSS_CHIP_PORT(port_no);
    u32  l1_se, l0_se, vport, l1_index, l1_input, l2_input;
    BOOL save_priority;

    VTSS_D("hqos_id: %u", hqos_id);

    if (port_no >= vtss_state->port_count) {
        VTSS_E("Invalid port number %u", port_no);
        return VTSS_RC_ERROR;
    }
    if (hqos_id >= VTSS_HQOS_ID_MAX) {
        VTSS_E("Invalid hqos_id %u", hqos_id);
        return VTSS_RC_ERROR;
    }

    port_conf = &hqos->port_conf[port_no];
    hier = &hqos->hier_conf[port_no];

    if (port_conf->sch_mode != VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
        VTSS_E("Adding of HQOS elements only allowed in HIERARCHICAL mode");
        return VTSS_RC_ERROR;
    }

    // Find the HQOS element (L0 SE) with this hqos_id
    if (NULL == (hier_se = find_hier_se(hier, hqos_id))) {
        // The HQOS element does not exist already
        if (hier->entry_count == VTSS_HQOS_PORT_L0_MAX) {
            VTSS_E("No more entries can be added on this port. entry_count %u  max %u",
                   hier->entry_count, VTSS_HQOS_PORT_L0_MAX);
            return VTSS_RC_ERROR;
        }
        if ((conf->priority_service == TRUE) &&
            (hier->priority_count == VTSS_HQOS_PORT_PRIORITY_ENTRY_MAX)) {
            VTSS_E("No more Priority entries can be added on this port. priority_count %u  max %u",
                   hier->entry_count, VTSS_HQOS_PORT_PRIORITY_ENTRY_MAX);
            return VTSS_RC_ERROR;
        }

        // Find a free L0 SE and VPORT and index
        if (VTSS_RC_OK != find_free_l0_se(vtss_state, port_no, &l0_se)) {
            VTSS_E("No free L0 SE was found");
            return VTSS_RC_ERROR;
        }
        if (VTSS_RC_OK != find_free_vport(vtss_state, port_no, &vport)) {
            VTSS_E("No free VPORT was found");
            return VTSS_RC_ERROR;
        }
        hier_se = find_free_hier_se(hier);

        // Check if there is a free input in the L1 CE or a new must be added
        if (conf->priority_service == TRUE) {
            // Priority service entry must be connected to the Priority L1 SE
            // The Priority L1 SE is always there and must have a free input
            if (FALSE == find_free_priority_l1_input(hier, &l1_input)) {
                VTSS_E("No free input in Priority L1 SE was found");
                return VTSS_RC_ERROR;
            }
            l1_se = hier->priority_l1_se;
        } else {
            // Not a Priority entry
            if (FALSE == find_free_l1_input(hier, &l1_se, &l1_input)) {
                // NO free input was found on existing L1
                // Check if the number of L1 limit is reached
                if (L1_ENTRY_COUNT >= VTSS_HQOS_PORT_L1_SE_CNT) {
                    VTSS_E("The L1 limit is reached on this port");
                    return VTSS_RC_ERROR;
                }
                /* Find a free L1 SE and L1 index */
                if (VTSS_RC_OK != find_free_l1_se(vtss_state, &l1_se)) {
                    VTSS_E("No free L1 SE was found");
                    return VTSS_RC_ERROR;
                }
                l1_index = find_free_l1_index(hier);
                l1_input = 0;

                // Find a free L2 input
                l2_input = find_free_l2_input(hier);

                // Link the L1 SE to input in L2 SE
                REG_WR(VTSS_HSCH_HSCH_L1_CFG(l1_se),
                       VTSS_F_HSCH_HSCH_L1_CFG_NEXT_IDX(chip_port) |
                           VTSS_F_HSCH_HSCH_L1_CFG_NEXT_INP(l2_input));

                hier->l1_ses[l1_index].se = l1_se;
                hier->l1_ses[l1_index].l2_input = l2_input;
            }
        }

        // All required resources are found

        // Link the L0 SE to input in L1 SE
        REG_WR(VTSS_HSCH_HSCH_L0_CFG(l0_se), VTSS_F_HSCH_HSCH_L0_CFG_NEXT_LAYER(0) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(l1_se) |
                                                 VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(l1_input));

        // Mark L0 SE and VPORT as used
        L0_USED_BF_SET(l0_used, l0_se, 1);
        L0_USED_BF_SET(vport_used, vport, 1);

        // Configure QGRP on this port to generate VPORT
        REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(hqos_id + 1));
        REG_WR(VTSS_XQS_QMAP_VPORT_TBL(0, chip_port),
               VTSS_F_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(vport));

        // Configure the SE Table to point to the added L0 SE
        REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(vport));
        REG_WR(VTSS_XQS_QMAP_QOS_TBL(0), VTSS_F_XQS_QMAP_QOS_TBL_QMAP_QOS_SEL(0));
        REG_WR(VTSS_XQS_QMAP_SE_TBL(0), VTSS_F_XQS_QMAP_SE_TBL_QMAP_SE_VAL(l0_se));

        // Now the new HQOS element is created
        hier->entry_count += 1;
        if (conf->priority_service == TRUE) {
            hier->priority_count += 1;
        }
        hier_se->hqos_id = hqos_id;
        hier_se->se = l0_se;
        hier_se->vport = vport;
        hier_se->l1_se = l1_se;
        hier_se->l1_input = l1_input;
    }
    save_priority = conf->priority_service;
    hier_se->conf = *conf;
    // This cannot be changed after initial add
    hier_se->conf.priority_service = save_priority;

    // Allocate a Queue Shaper if needed
    if (VTSS_RC_OK != qshp_alloc(vtss_state, hier_se)) {
        VTSS_E("Queue shaper allocation failed");
        return VTSS_RC_ERROR;
    }

#if 0
    // Configure the L0 SE queue shapers
    hqos_to_qos_shaper(conf->shaper_queue, shapers);
    if (VTSS_RC_OK !=
        vtss_fa_qos_se_queue_shaper_conf_set(vtss_state, port_no, hier_se->se, shapers)) {
        VTSS_E("Queue shaper configuration failed");
        return VTSS_RC_ERROR;
    }
#endif

    // Configure the L0 SE output shapers
    if (VTSS_RC_OK !=
        vtss_fa_qos_shaper_conf_set(vtss_state, &conf->shaper, 0, hier_se->se, 0, 0)) {
        VTSS_E("Output shaper configuration failed");
        return VTSS_RC_ERROR;
    }
    REG_WRM(VTSS_HSCH_SE_CFG(hier_se->se),
            VTSS_F_HSCH_SE_CFG_SE_AVB_ENA(conf->shaper.credit_enable),
            VTSS_M_HSCH_SE_CFG_SE_AVB_ENA);

    // Configure the L0 SE DWRR
    if (VTSS_RC_OK != fa_qos_dwrr_conf_set(vtss_state, hier_se->se, 0, (conf->dwrr_cnt != 0),
                                           conf->dwrr_cnt, conf->input_pct)) {
        VTSS_E("L0 DWRR configuration failed");
        return VTSS_RC_ERROR;
    }

    // Configure the L1 and L2 SE DWRR
    if (VTSS_RC_OK != fa_l1_l2_dwrr_configure(vtss_state, chip_port, hier, hier_se->l1_se)) {
        VTSS_E("L1 - L2 DWRR configuration failed");
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_cil_hqos_del(vtss_state_t        *vtss_state,
                          const vtss_port_no_t port_no,
                          const vtss_hqos_id_t hqos_id)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_port_conf_t *port_conf;
    vtss_hqos_hier_port_t *hier;
    vtss_hqos_l0_se_t     *hier_se;
    u32                    l1_se, chip_port = VTSS_CHIP_PORT(port_no);

    VTSS_D("hqos_id: %u", hqos_id);

    if (port_no >= vtss_state->port_count) {
        VTSS_E("Invalid port number %u", port_no);
        return VTSS_RC_ERROR;
    }

    port_conf = &hqos->port_conf[port_no];
    hier = &hqos->hier_conf[port_no];

    if (port_conf->sch_mode != VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
        VTSS_D("Deleting of HQOS elements only allowed in HIERARCHICAL mode");
        return VTSS_RC_ERROR;
    }

    // Find the HQOS element (L0 SE) with this hqos_id
    if (NULL == (hier_se = find_hier_se(hier, hqos_id))) {
        // The HQOS element does not exist already
        VTSS_D("Deleting of HQOS element that does not exist");
        return VTSS_RC_ERROR;
    }

    // Configure QGRP to point to Unknown VPORT and SE
    REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(hqos_id + 1));
    REG_WR(VTSS_XQS_QMAP_VPORT_TBL(0, chip_port),
           VTSS_F_XQS_QMAP_VPORT_TBL_QMAP_VPORT_VAL(hier->unknown_vport));
    REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(hier->unknown_vport));
    REG_WR(VTSS_XQS_QMAP_SE_TBL(0), VTSS_F_XQS_QMAP_SE_TBL_QMAP_SE_VAL(hier->unknown_l0_se));

    // Free L0 SE and VPORT
    (void)free_l0_se(vtss_state, chip_port, hier_se->se);
    free_vport(chip_port, hier_se->vport);
    hier_se->se = VTSS_HQOS_SE_NONE;
    hier_se->vport = VTSS_HQOS_VPORT_NONE;

    // Decrement the number of entries on this port
    hier->entry_count -= 1;

    l1_se = hier_se->l1_se;
    hier_se->l1_se = VTSS_HQOS_SE_NONE;
    if (hier_se->conf.priority_service == TRUE) {
        hier->priority_count -= 1;
    } else {
        // Not a priority entry - free the L1 SE
        free_l1_se(hier, l1_se);
    }

    // Configure the L1 and L2 SE DWRR
    return fa_l1_l2_dwrr_configure(vtss_state, chip_port, hier, l1_se);
}

static vtss_rc min_rate_calc(vtss_state_t *vtss_state, u32 layer, u32 se, u32 input, u32 out_rate)
{
    u32 i, value, dwrr_cnt, sum, cost, weight, rate;
    u64 rate0, rate1;

    REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer) | VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER | VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

    REG_RD(VTSS_HSCH_SE_CFG(se), &value);
    dwrr_cnt = VTSS_X_HSCH_SE_CFG_SE_DWRR_CNT(value);
    if (dwrr_cnt == 0) {
        return out_rate;
    }

    sum = 0;
    for (i = 0; i < (dwrr_cnt + 1); i++) {
        REG_RD(VTSS_HSCH_DWRR_ENTRY(i), &value);
        cost = VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(value) + 1;
        weight = 10000 / cost;
        sum += weight;
    }
    if (sum == 0) {
        return 0;
    }

    REG_RD(VTSS_HSCH_DWRR_ENTRY(input), &value);
    cost = VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(value) + 1;
    weight = 10000 / cost;
    rate0 = (u64)weight * (u64)out_rate;
    rate1 = rate0 / (u64)sum;
    if ((rate0 % (u64)sum) > (u64)(sum / 2)) {
        // Round up
        rate1 += 1;
    }
    rate = (u32)rate1;

    return rate;
}

vtss_rc vtss_cil_hqos_status_get(struct vtss_state_s      *vtss_state,
                                 const vtss_port_no_t      port_no,
                                 const vtss_hqos_id_t      hqos_id,
                                 vtss_hqos_status_t *const status)
{
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier;
    vtss_hqos_l0_se_t     *hier_se;
    u32                    chip_port = VTSS_CHIP_PORT(port_no);
    u32                    l2_se, l1_se, l1_input, l1_index, l2_input, l0_rate, l1_rate;

    VTSS_D("hqos_id: %u", hqos_id);

    if (port_no >= vtss_state->port_count) {
        VTSS_E("Invalid port number %u", port_no);
        return VTSS_RC_ERROR;
    }

    hier = &hqos->hier_conf[port_no];

    // Find the HQOS element (L0 SE) with this hqos_id
    if (NULL == (hier_se = find_hier_se(hier, hqos_id))) {
        // The HQOS element does not exist already
        VTSS_D("Deleting of HQOS element that does not exist");
        return VTSS_RC_ERROR;
    }

    l2_se = chip_port;
    l1_se = hier_se->l1_se;
    l1_input = hier_se->l1_input;
    if (hier_se->conf.priority_service == TRUE) {
        l0_rate = min_rate_calc(vtss_state, 1, l1_se, l1_input, 1000000);
    } else {
        l1_index = find_l1_index(hier, l1_se);
        l2_input = hier->l1_ses[l1_index].l2_input;
        l1_rate = min_rate_calc(vtss_state, 2, l2_se, l2_input, 1000000);
        l0_rate = min_rate_calc(vtss_state, 1, l1_se, l1_input, l1_rate);
    }

    status->min_rate = l0_rate;

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

static vtss_rc debug_print_dwrr(vtss_state_t *vtss_state, lmu_ss_t *ss, u32 layer, u32 index, u32 se)
{
    u32 i, value, dwrr_cnt, dwrr_cost[64];

    REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
            VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(layer) | VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(se),
            VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER | VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

    REG_RD(VTSS_HSCH_SE_CFG(se), &value);
    dwrr_cnt = VTSS_X_HSCH_SE_CFG_SE_DWRR_CNT(value);
    if (dwrr_cnt == 0) {
        pr("IDX: %u  SE %u - No DWRR in this SE", index, se);
        pr("\n");
        return VTSS_RC_OK;
    }

    for (i = 0; i < (dwrr_cnt + 1); i++) {
        REG_RD(VTSS_HSCH_DWRR_ENTRY(i), &value);
        dwrr_cost[i] = VTSS_X_HSCH_DWRR_ENTRY_DWRR_COST(value);
    }
    pr("IDX: %u  SE: %u  DWRR-CNT: %u  DWRR-COST: ", index, se, (dwrr_cnt + 1));
    for (i = 0; i < (dwrr_cnt + 1); i++) {
        pr("%u-", dwrr_cost[i]);
    }
    pr("\n");
    return VTSS_RC_OK;
}

static vtss_rc debug_print_l0_se(vtss_state_t *vtss_state, lmu_ss_t *ss, u32 cport, u32 se)
{
    u32 value, l0_nxt_layer, l0_nxt_idx, l0_nxt_inp, l1_nxt_idx, l1_nxt_inp;

    REG_RD(VTSS_HSCH_HSCH_L0_CFG(se), &value);
    l0_nxt_layer = VTSS_X_HSCH_HSCH_L0_CFG_NEXT_LAYER(value);
    l0_nxt_idx = VTSS_X_HSCH_HSCH_L0_CFG_NEXT_IDX(value);
    l0_nxt_inp = VTSS_X_HSCH_HSCH_L0_CFG_NEXT_INP(value);
    if (l0_nxt_layer == 0) {
        // Next Layer is L1
        REG_RD(VTSS_HSCH_HSCH_L1_CFG(l0_nxt_idx), &value);
        l1_nxt_idx = VTSS_X_HSCH_HSCH_L1_CFG_NEXT_IDX(value);
        l1_nxt_inp = VTSS_X_HSCH_HSCH_L1_CFG_NEXT_INP(value);
        if (l1_nxt_idx != cport) {
            // The L1 is not connected to this port
            return VTSS_RC_OK;
        }
        pr("L0-SE: %u L1-SE %u L1-INP %u L2-SE %u L2-INP %u\n", se, l0_nxt_idx, l0_nxt_inp,
           l1_nxt_idx, l1_nxt_inp);
    } else {
        // Next Layer is L2 (Chip Port)
        if (l0_nxt_idx != cport) {
            // The L0 is not connected to this port
            return VTSS_RC_OK;
        }
        pr("L0-SE: %u L2-SE %u L2-INP %u\n", se, l0_nxt_idx, l0_nxt_inp);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_debug_hqos(vtss_state_t                  *vtss_state,
                             lmu_ss_t                      *ss,
                             const vtss_debug_info_t *const info)
{
    vtss_port_no_t port_no = VTSS_PORT_NO_NONE;
    u32            i, div, qgrp = VTSS_HQOS_QGRP_NONE, vport, se, cport = VTSS_PORT_NO_NONE;
    BOOL           show_act, internal_act, tables_act, dwrr_act, hier_act, se_act, hq_act, large;
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier;
    vtss_hqos_port_conf_t *conf;
    u32                    port_start = VTSS_PORT_NO_START;
    u32                    port_end = VTSS_PORT_NO_START + (vtss_state->port_count - 1);
    u32 l0, l1, ppqqq, layer = 0xFF, value, l0_se = 0, large_mask, port = 0, cir, cbs, mode,
                       rep_closed, cir_lvl, min, max, base, nxt;
    u32 inp_state[3];

    VTSS_D("has_action %u  action %u", info->has_action, info->action);

    show_act = internal_act = tables_act = dwrr_act = hier_act = se_act = hq_act = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show_act = (info->action == 0) ? TRUE : FALSE;
        internal_act = (info->action == 1) ? TRUE : FALSE;
        tables_act = (info->action == 2) ? TRUE : FALSE;
        dwrr_act = (info->action == 3) ? TRUE : FALSE;
        hier_act = (info->action == 4) ? TRUE : FALSE;
        se_act = (info->action == 5) ? TRUE : FALSE;
        hq_act = (info->action == 6) ? TRUE : FALSE;
    }

    if (info->action > 6) { /* There potentially a encoded port and/or QGRP */
        for (i = 0, div = 100000; i < 6; ++i, (div = div / 10)) {
            internal_act = ((info->action / div) == 1) ? TRUE : FALSE;
            tables_act = ((info->action / div) == 2) ? TRUE : FALSE;
            dwrr_act = ((info->action / div) == 3) ? TRUE : FALSE;
            hier_act = ((info->action / div) == 4) ? TRUE : FALSE;
            se_act = ((info->action / div) == 5) ? TRUE : FALSE;
            hq_act = ((info->action / div) == 6) ? TRUE : FALSE;

            if (tables_act || hier_act || internal_act || dwrr_act || se_act || se_act || hq_act) {
                break;
            }
        }
        if (internal_act || hier_act || hq_act) {
            port_no = info->action % div;
            cport = VTSS_CHIP_PORT(port_no);
        }
        if (se_act) {
            l0_se = info->action % div;
        }
        if (tables_act) {
            ppqqq = info->action % div;
            if (ppqqq > 0) {
                if ((ppqqq / 1000) != 0) {
                    port_no = ppqqq / 1000;
                    qgrp = ppqqq % 1000;
                } else {
                    port_no = ppqqq;
                }
            }
            cport = VTSS_CHIP_PORT(port_no);
        }
        if (dwrr_act) {
            port_no = (info->action % div) / 10;
            cport = VTSS_CHIP_PORT(port_no);
            layer = (info->action % div) % 10;
        }
        VTSS_D("port_no %u  chip port %u  qgrp %u  div %u  layer %u", port_no, cport, qgrp, div,
               layer);
    }

    VTSS_D("show %u  internal_act %u  tables_act %u  dwrr_act %u  hier_act %u  hq_act %u", show_act,
           internal_act, tables_act, dwrr_act, hier_act, hq_act);

    if (show_act) {
        pr("HQOS Debug Group action:\n");
        pr("    0:      Show possible actions\n");
        pr("    1PP:    Print Internal structures\n");
        pr("    2PPQQQ: Print VPORT_TBL and SE_TBL configuration. PP = Port. QQQ = QGRP\n");
        pr("    3PPL:   Print DWRR configuration. PP = Port. L = Layer. L0 = 0 L1 = 1 L2 = 2\n");
        pr("    4PP:    Print Hierarchy configuration. PP = Port\n");
        pr("    5SE:    Print L0 SE information. QGRP/VPORT pointing to this SE. Shapers. State."
           "SE = L0 scheduler element index\n");
        pr("    6PP:    Print HQOS guaranteed rate information. PP = Port\n");
        pr("\n");
    }

    if (!info->has_action || internal_act) { /* Internal structures must be printed */
        pr("HQOS Internal information:\n");
        pr("--------------------------\n");
        if (port_no != VTSS_PORT_NO_NONE) {
            port_start = port_no;
            port_end = port_start;
        }
        for (port = port_start; port <= port_end; port++) {
            hier = &hqos->hier_conf[port];
            conf = &hqos->port_conf[port];
            cport = VTSS_CHIP_PORT(port);

            if (conf->sch_mode == VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
                /* This port is not hierarchical mode */
                pr("PORT %u  CHIP-PORT: %u  HIERARCHICAL MODE:\n", port, cport);
                pr("entry_count %u  unknown_vport %u  unknown_l0_se %u  priority_l1_se %u\n",
                   hier->entry_count, hier->unknown_vport, hier->unknown_l0_se,
                   hier->priority_l1_se);
                pr("\n");
                pr("L0 SE's:\n");
                for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
                    if (hier->l0_ses[l0].se != VTSS_HQOS_SE_NONE) {
                        pr("IDX: %3u  HQOS-ID: %3u  PRIO: %u  MIN: %7u  VPORT: %3u  "
                           "SE: %4u  L1-SE: %2u  L1-INPUT: %2u  QSHP: %u\n",
                           l0, hier->l0_ses[l0].hqos_id, hier->l0_ses[l0].conf.priority_service,
                           hier->l0_ses[l0].conf.min_rate, hier->l0_ses[l0].vport,
                           hier->l0_ses[l0].se, hier->l0_ses[l0].l1_se, hier->l0_ses[l0].l1_input,
                           hier->l0_ses[l0].qshp);
                    }
                }
                pr("\n");
                pr("L1 SE's:\n");
                for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
                    if (hier->l1_ses[l1].se != VTSS_HQOS_SE_NONE) {
                        pr("IDX %u  SE %u  L2-INPUT %u\n", l1, hier->l1_ses[l1].se,
                           hier->l1_ses[l1].l2_input);
                    }
                }
                pr("\n");
            }
        }
    }

    if (!info->has_action || tables_act) { /* VPORT_TBL and SE_TBL configuration must be printed */
        u32 qtable_cnt = 5;
        u32 ctable_cnt = 8;
        u32 qgrps[5] = {0, 2, (VTSS_HQOS_QGRP_CNT / 4), (VTSS_HQOS_QGRP_CNT / 2),
                        (VTSS_HQOS_QGRP_CNT - 1)};
        u32 cports[8] = {0,
                         2,
                         (VTSS_PORT_CNT / 4),
                         (VTSS_PORT_CNT - 5),
                         (VTSS_PORT_CNT - 4),
                         (VTSS_PORT_CNT - 3),
                         (VTSS_PORT_CNT - 2),
                         (VTSS_PORT_CNT - 1)};

        pr("HQOS VPORT Table (Replication 0):\n");
        pr("----------------------------\n");
        if (port_no != VTSS_PORT_NO_NONE) {
            ctable_cnt = 1;
            cports[0] = VTSS_CHIP_PORT(port_no);
            if (qgrp != VTSS_HQOS_QGRP_NONE) {
                qtable_cnt = 1;
                qgrps[0] = qgrp;
            }
        }
        for (port = 0; port < ctable_cnt; ++port) {
            for (qgrp = 0; qgrp < qtable_cnt; ++qgrp) {
                REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(qgrps[qgrp]));
                REG_RD(VTSS_XQS_QMAP_VPORT_TBL(0, cports[port]), &vport);
                REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(vport));
                REG_RD(VTSS_XQS_QMAP_SE_TBL(0), &se);
                pr("CHIP-PORT %u  QGRP %u  VPORT %u  SE %u:\n", cports[port], qgrps[qgrp], vport,
                   se);
            }
        }
    }

    if (!info->has_action || dwrr_act) { /* SE Hierarchy DWRR configuration must be printed */
        pr("HQOS DWRR configuration:\n");
        pr("--------------------------\n");
        if (port_no != VTSS_PORT_NO_NONE) {
            port_start = port_no;
            port_end = port_start;
        }
        for (port = port_start; port <= port_end; port++) {
            hier = &hqos->hier_conf[port];
            conf = &hqos->port_conf[port];
            cport = VTSS_CHIP_PORT(port);

            if (conf->sch_mode == VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
                /* This port is hierarchical mode */
                if ((layer == 0) || (layer == 0xFF)) {
                    pr("L0 SE DWRR:\n");
                    for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
                        if (hier->l0_ses[l0].se == VTSS_HQOS_SE_NONE) {
                            continue;
                        }
                        (void)debug_print_dwrr(vtss_state, ss, layer, l0, hier->l0_ses[l0].se);
                    }
                    pr("\n");
                }
                if ((layer == 1) || (layer == 0xFF)) {
                    pr("L1 SE DWRR:\n");
                    for (l1 = 0; l1 < VTSS_HQOS_PORT_L1_MAX; ++l1) {
                        if (hier->l1_ses[l1].se == VTSS_HQOS_SE_NONE) {
                            continue;
                        }
                        (void)debug_print_dwrr(vtss_state, ss, layer, l1, hier->l1_ses[l1].se);
                    }
                    pr("PRIORITY L1 SE DWRR:\n");
                    (void)debug_print_dwrr(vtss_state, ss, layer, 0, hier->priority_l1_se);
                    pr("\n");
                }
                if ((layer == 2) || (layer == 0xFF)) {
                    pr("L2 SE DWRR:\n");
                    (void)debug_print_dwrr(vtss_state, ss, layer, cport, cport);
                }
                pr("\n");
            }
        }
    }

    if (!info->has_action || hier_act) { /* SE Hierarchy configuration must be printed */
        u32 mode;

        pr("HQOS SE Hierarchy configuration:\n");
        pr("--------------------------------\n");
        if (port_no != VTSS_PORT_NO_NONE) {
            port_start = port_no;
            port_end = port_start;
        }
        for (port = port_start; port <= port_end; port++) {
            cport = VTSS_CHIP_PORT(port);

            REG_RD(VTSS_XQS_QMAP_PORT_MODE(cport), &value);
            mode = VTSS_X_XQS_QMAP_PORT_MODE_QMAP_MODE_SERVICE(value);

            REG_RD(VTSS_HSCH_HSCH_LARGE_ENA(cport / 4), &value);
            large_mask = 0x0FF << ((cport % 4) * 8);
            large = ((value & large_mask) == large_mask) ? TRUE : FALSE;

            pr("PORT %u  CHIP-PORT: %u  MODE: %s  LARGE: %s\n", port, cport,
               (mode == 1) ? "HIERARCHICAL" : "NORMAL", (large == TRUE) ? "TRUE" : "FALSE");

            pr("L0 SE connected:\n");

            for (l0 = 0; l0 < VTSS_HQOS_L0_CE_CNT; ++l0) {
                (void)debug_print_l0_se(vtss_state, ss, cport, l0);
            }
        }
    }

    if (!info->has_action || se_act) { /* QGRP/VPORT pointing to this SE must be printed*/
        pr("HQOS SE pointers:\n");
        pr("----------------------------\n");
        for (i = 0; i < (VTSS_HQOS_CHIP_VPORT_CNT * 8); ++i) {
            REG_WR(VTSS_XQS_MAP_CFG_CFG, VTSS_F_XQS_MAP_CFG_CFG_MAP_CFG_CFG(i));
            REG_RD(VTSS_XQS_QMAP_SE_TBL(0), &se);
            if (se == l0_se) {
                pr("VPORT %u  SE %u:\n", i, se);
            }
        }

        pr("HQOS SE Hierarchy configuration:\n");
        pr("--------------------------------\n");
        (void)debug_print_l0_se(vtss_state, ss, cport, l0);

        pr("HQOS SE Shapers\n");
        pr("----------------------------\n");
        /* Select layer */
        REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(0) | VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(l0_se),
                VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER | VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

        // Read the output shaper configuration
        REG_RD(VTSS_HSCH_CIR_CFG(l0_se), &value);
        cir = VTSS_X_HSCH_CIR_CFG_CIR_RATE(value);
        cbs = VTSS_X_HSCH_CIR_CFG_CIR_BURST(value);
        REG_RD(VTSS_HSCH_SE_CFG(l0_se), &value);
        mode = VTSS_X_HSCH_SE_CFG_SE_FRM_MODE(value);
        pr("OUTPUT SHAPER SE: %u  CIR: %u  CBS: %u  MODE: %u\n", l0_se, cir, cbs, mode);

        /* Select QSHP layer */
        REG_WRM(VTSS_HSCH_HSCH_CFG_CFG,
                VTSS_F_HSCH_HSCH_CFG_CFG_HSCH_LAYER(3) | VTSS_F_HSCH_HSCH_CFG_CFG_CFG_SE_IDX(l0_se),
                VTSS_M_HSCH_HSCH_CFG_CFG_HSCH_LAYER | VTSS_M_HSCH_HSCH_CFG_CFG_CFG_SE_IDX);

        // Check if Queue Shaper is allocated
        REG_RD(VTSS_HSCH_QSHP_ALLOC_CFG(l0_se), &value);
        if (VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(value) !=
            VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(value)) {
            // Print Queue Shaper configuration
            min = VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MIN(value);
            max = VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_MAX(value);
            base = VTSS_X_HSCH_QSHP_ALLOC_CFG_QSHP_BASE(value);
            REG_RD(VTSS_HSCH_QSHP_CONNECT(l0_se), &value);
            nxt = VTSS_X_HSCH_QSHP_CONNECT_SE_LEAK_LINK(value);
            pr("QUEUE SHAPER SE: %u  MIN: %u  MAX: %u  BASE: %u  SE-NXT %u\n", l0_se, min, max,
               base, nxt);
            for (i = 0; i < 8; ++i) {
                REG_RD(VTSS_HSCH_QSHP_CFG(i), &value);
                mode = VTSS_X_HSCH_QSHP_CFG_SE_FRM_MODE(value);
                REG_RD(VTSS_HSCH_QSHP_CIR_CFG(i), &value);
                cir = VTSS_X_HSCH_QSHP_CIR_CFG_CIR_RATE(value);
                cbs = VTSS_X_HSCH_QSHP_CIR_CFG_CIR_BURST(value);
                REG_RD(VTSS_HSCH_QSHP_CIR_STATE(i), &value);
                cir_lvl = VTSS_X_HSCH_QSHP_CIR_STATE_CIR_LVL(value);
                pr("Priority: %u  CIR: %u  CBS: %u  MODE: %u  CIR-LVL %u\n", i, cir, cbs, mode,
                   cir_lvl);
            }
        }

        pr("HQOS SE State\n");
        pr("----------------------------\n");
        REG_RD(VTSS_HSCH_SE_STATE(l0_se), &value);
        rep_closed = VTSS_X_HSCH_SE_STATE_REP_CLOSED(value);

        REG_RD(VTSS_HSCH_INP_STATE(0), &inp_state[0]);
        REG_RD(VTSS_HSCH_INP_STATE(1), &inp_state[1]);
        REG_RD(VTSS_HSCH_INP_STATE(2), &inp_state[2]);
        pr("SE: %u  REP_CLOSED: %u  INP-STATE: %X-%X-%X\n", l0_se, rep_closed, inp_state[0],
           inp_state[1], inp_state[2]);
    }

    if (!info->has_action || hq_act) { /* HQOS information must be printed */
        pr("HQOS information:\n");
        pr("--------------------------\n");
        if (port_no != VTSS_PORT_NO_NONE) {
            port_start = port_no;
            port_end = port_start;
        }

        for (port = port_start; port <= port_end; port++) {
            hier = &hqos->hier_conf[port];
            conf = &hqos->port_conf[port];

            if (conf->sch_mode != VTSS_HQOS_SCH_MODE_HIERARCHICAL) {
                continue;
            }

            u32 l2_se = cport;
            u32 l1_rate[5];
            for (i = 0; i < 5; ++i) {
                l1_rate[i] = min_rate_calc(vtss_state, 2, l2_se, i, 1000000);
            }
            for (l0 = 0; l0 < VTSS_HQOS_PORT_L0_MAX; ++l0) {
                if ((hier->l0_ses[l0].se == VTSS_HQOS_SE_NONE) ||
                    (hier->l0_ses[l0].l1_se == VTSS_HQOS_SE_NONE)) {
                    continue;
                }
                u32 l1_se = hier->l0_ses[l0].l1_se;
                u32 l0_se = hier->l0_ses[l0].se;
                u32 l1_index = find_l1_index(hier, l1_se);
                u32 l2_input = hier->l1_ses[l1_index].l2_input;
                u32 l1_input = hier->l0_ses[l0].l1_input;
                u32 l0_rate;

                if (hier->l0_ses[l0].conf.priority_service) {
                    l0_rate = min_rate_calc(vtss_state, 1, l1_se, l1_input, 1000000);
                } else {
                    l0_rate = min_rate_calc(vtss_state, 1, l1_se, l1_input, l1_rate[l2_input]);
                }
                u32 off = (l0_rate > hier->l0_ses[l0].conf.min_rate)
                              ? l0_rate - hier->l0_ses[l0].conf.min_rate
                              : hier->l0_ses[l0].conf.min_rate - l0_rate;
                pr("HQOS-ID: %3u  L1-SE: %4u  L0-SE: %4u  MIN-RATE: %7u  ACT-RATE: %7u  "
                   "OFF: %7u  PCT: %u\n",
                   hier->l0_ses[l0].hqos_id, l1_se, l0_se, hier->l0_ses[l0].conf.min_rate,
                   l0_rate, off, (l0_rate * 100) / hier->l0_ses[l0].conf.min_rate);
            }
        }
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_hqos_debug_print(vtss_state_t                  *vtss_state,
                                 lmu_ss_t                      *ss,
                                 const vtss_debug_info_t *const info)
{
    VTSS_RC(vtss_debug_print_group(VTSS_DEBUG_GROUP_HQOS, fa_debug_hqos, vtss_state, ss, info));
    return VTSS_RC_OK;
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_hqos_init(vtss_state_t *vtss_state)
{
    u32                    i, port;
    vtss_hqos_state_t     *hqos = &vtss_state->hqos;
    vtss_hqos_hier_port_t *hier;

    for (port = 0; port < VTSS_PORT_ARRAY_SIZE; ++port) {
        hier = &hqos->hier_conf[port];
        for (i = 0; i < VTSS_HQOS_PORT_L0_MAX; ++i) {
            hier->l0_ses[i].conf.shaper.rate = VTSS_BITRATE_DISABLED;
#if 0
            for (prio = 0; prio < VTSS_QUEUE_ARRAY_SIZE; ++prio) {
                hier->l0_ses[i].conf.shaper_queue[prio].rate = VTSS_BITRATE_DISABLED;
            }
#endif
            hier->l0_ses[i].se = VTSS_HQOS_SE_NONE;
            hier->l0_ses[i].l1_se = VTSS_HQOS_SE_NONE;
            hier->l0_ses[i].vport = VTSS_HQOS_VPORT_NONE;
            hier->l0_ses[i].qshp = VTSS_HQOS_QSHP_NONE;
        }
        for (i = 0; i < VTSS_HQOS_PORT_L1_MAX; ++i) {
            hier->l1_ses[i].se = VTSS_HQOS_SE_NONE;
        }
        hier->unknown_l0_se = VTSS_HQOS_SE_NONE;
        hier->priority_l1_se = VTSS_HQOS_SE_NONE;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_fa_hqos_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    u32  port_no, chip_port;
#if defined(HENRIKTBD)
    u32 large_mask;
#endif
    BOOL chip_port_used[VTSS_PORT_CNT] = {};

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE: break;
    case VTSS_INIT_CMD_INIT:
        VTSS_PROF_ENTER(LM_PROF_ID_MESA_INIT, 90);
        VTSS_RC(fa_hqos_init(vtss_state));
        VTSS_PROF_EXIT(LM_PROF_ID_MESA_INIT, 90);
        break;
    case VTSS_INIT_CMD_POLL: break;
    case VTSS_INIT_CMD_PORT_MAP:
        /* Calculate all Normal Mode used SEs */
        // Chip port 0 - 64 are physical ports and are configured in the port map
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            chip_port = VTSS_CHIP_PORT(port_no);
            chip_port_used[chip_port] = TRUE;
            (void)l0_used_set(vtss_state, chip_port);
            (void)vport_used_set(vtss_state, chip_port);
        }
        // Chip Port 65 - 69 are CPU and Device (internal) ports. These SEs cannot be used for HQOS.
        for (chip_port = 65; chip_port < VTSS_PORT_CNT; chip_port++) {
            (void)l0_used_set(vtss_state, chip_port);
            (void)vport_used_set(vtss_state, chip_port);
        }
        // All unused chip port SE is configured as NOT large
        for (chip_port = 0; chip_port < VTSS_PORT_CNT; chip_port++) {
            if (chip_port_used[chip_port] == TRUE) {
                continue;
            }
            // Make all Normal hierarchy L0 SEs small
            // A Normal hierarchy port uses 8 large L0 SEs
            // In every replication there are large SE configuration bits for 4 ports (8 * 4 = 32)
            // The 8 large SEs give a mask = 0xFF
#if defined(HENRIKTBD)
            large_mask = 0x0FF << ((chip_port % 4) * 8);
            REG_WRM(VTSS_HSCH_HSCH_LARGE_ENA(chip_port / 4), 0, large_mask);
#endif
        }
        break;
    default: break;
    }

    return VTSS_RC_OK;
}

#endif /* defined(VTSS_FEATURE_HQOS) */
