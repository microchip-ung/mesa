// Copyright (c) 2004-2025 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_PORT
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_LAIKA)

vtss_rc vtss_cil_miim_read(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     addr,
                           u16                   *value,
                           BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_miim_write(vtss_state_t          *vtss_state,
                            vtss_miim_controller_t miim_controller,
                            u8                     miim_addr,
                            u8                     addr,
                            u16                    value,
                            BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_read(vtss_state_t          *vtss_state,
                          vtss_miim_controller_t miim_controller,
                          u8                     miim_addr,
                          u8                     mmd,
                          u16                    addr,
                          u16                   *value,
                          BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_read_inc(vtss_state_t          *vtss_state,
                              vtss_miim_controller_t miim_controller,
                              u8                     miim_addr,
                              u8                     mmd,
                              u16                    addr,
                              u16                   *buf,
                              u8                     count,
                              BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

vtss_rc vtss_cil_mmd_write(vtss_state_t          *vtss_state,
                           vtss_miim_controller_t miim_controller,
                           u8                     miim_addr,
                           u8                     mmd,
                           u16                    addr,
                           u16                    data,
                           BOOL                   report_errors)
{
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_PORT_CPU_MASQUERADING)

u32 vtss_cpu_masquerade_to_chip_port(vtss_cpu_masquerade_t val)
{
    switch (val) {
    case VTSS_CPU_MASQUERADE_NONE: return 0;
    case VTSS_CPU_MASQUERADE_CPU0: return RT_CHIP_PORT_CPU_0;
    case VTSS_CPU_MASQUERADE_CPU1: return RT_CHIP_PORT_CPU_1;
    }
    return 0;
}

/* On Laika, it is possible to have multiple CPUs using a single CPU port. The typical
 * use case is the system controller (SYSC) doing switch control with MESA while
 * the application CPU (APPC) runs a Linux driver that uses Transmit/Receive Offload
 * Frame Header (TOFH/ROFH). Both CPU use the Packet Insert Extract (PIE) engine, which
 * is a multi-queue DMA engine based on buffer descriptor rings.
 *
 * +--------------------+  TOFH/ROFH  +-----------+
 * | SWITCH   +------+  |  Frames     |  APPC     |
 * |          | PIE0 |<-------------->|           |
 * |          |      |  |             +-----------+
 * |          |      |  | IFH Frames  +-----------+
 * |          |      |<-------------->|  SYSC     |
 * |          +------+  |             |           |
 * |          +------+  |             +-----------+
 * |          | PIE1 |  |
 * |          |      |  |
 * |          +------+  |
 * +--------------------+
 *
 * Referring to the above image, the SYSC receives frames using the "copy to CPU"
 * scheme where one of the bit in the cpu_mask IFH field is set. On the other hand,
 * the APPC receives frames based on regular forwarding decisions.
 *
 * Because of the limited amount of ressources within the switch, the APPC switch
 * port is created using the ressources of a front port. Frames comming from the APPC
 * are masqueraded as comming from a front port when enterring the ASM and frames going
 * to the APPC are redirected to the CPU port in the hierarchical scheduler. This
 * means that using one CPU masqueraded port reduces the amount of available front port
 * from 32 to 31 and using two CPU masqueraded port reduces it to 30.
 *
 * The MESA API allows the user to select which CPU port have masquerading enabled
 * (via the `cpu_masquerade` field of `mesa_port_map_t`) and which front port is used
 * for masquerading (via the `chip_port` field of `mesa_port_map_t`). The front port
 * will show up as an active port using the `MESA_PORT_INTERFACE_MASQUERADING`
 * interface type.
 */
vtss_rc lk_port_masquerading_set(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;
    u32            src_port, cpu_port;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {

        // Not a CPU masquerading port.
        if (vtss_state->port.map[port_no].cpu_masquerade == VTSS_CPU_MASQUERADE_NONE)
            continue;

        src_port = VTSS_CHIP_PORT(port_no);
        cpu_port = vtss_cpu_masquerade_to_chip_port(vtss_state->port.map[port_no].cpu_masquerade);
        VTSS_I("Masquerading cpu_port %i to src_port %i\n", cpu_port, src_port);

        // The OFH_MODE bit allows the ASM to receive a smaller version of the IFH
        // called the TOFH. The port will still be able to receive IFH because the
        // TOFH uses a reserved bit of the IFH to identify itself. The OFH_SRC field
        // is the physical port the cpu port is masqueraded to.
        REG_WRM(VTSS_ASM_PORT_CFG(cpu_port),
                VTSS_F_ASM_PORT_CFG_OFH_MODE(1) | VTSS_F_ASM_PORT_CFG_OFH_SRC(src_port) |
                    VTSS_F_ASM_PORT_CFG_NO_PREAMBLE_ENA(1) | VTSS_F_ASM_PORT_CFG_INJ_FORMAT_CFG(1),
                VTSS_M_ASM_PORT_CFG_OFH_MODE | VTSS_M_ASM_PORT_CFG_OFH_SRC |
                    VTSS_M_ASM_PORT_CFG_NO_PREAMBLE_ENA | VTSS_M_ASM_PORT_CFG_INJ_FORMAT_CFG);

        // Redirect the service queue of src_port to cpu_port.
        REG_WRM(VTSS_HSCH_HSCH_L0_CFG(RT_HSCH_SE_HIGH - RT_CHIP_PORTS_ALL + src_port),
                VTSS_F_HSCH_HSCH_L0_CFG_NEXT_INP(2) | VTSS_F_HSCH_HSCH_L0_CFG_NEXT_IDX(cpu_port),
                VTSS_M_HSCH_HSCH_L0_CFG_NEXT_INP | VTSS_M_HSCH_HSCH_L0_CFG_NEXT_IDX);

        // Frames going to src_port are redirected to cpu_port by redirecting the
        // src_port L1 output to the cpu_port L2 input. Input #3 is used as #1 and
        // #2 are taken.
        REG_WRM(VTSS_HSCH_HSCH_L1_CFG(src_port),
                VTSS_F_HSCH_HSCH_L1_CFG_NEXT_INP(3) | VTSS_F_HSCH_HSCH_L1_CFG_NEXT_IDX(cpu_port),
                VTSS_M_HSCH_HSCH_L1_CFG_NEXT_INP | VTSS_M_HSCH_HSCH_L1_CFG_NEXT_IDX);

        // Add an ROFH in front of DMAC if the frame is not a CPU copy.
        // 0: Dont push ROFH
        // 1: insert ROFH/IFH based on cpu copy
        // 2: Always push ROFH
        // 3: push ROFH on frames when lbl1_sel action from es0 is 1
        REG_WRM(VTSS_REW_PORT_CTRL(cpu_port), VTSS_F_REW_PORT_CTRL_OFH_MODE(1),
                VTSS_M_REW_PORT_CTRL_OFH_MODE);

        // Enable src_port in QFWD.
        REG_WRM_SET(VTSS_QFWD_SWITCH_PORT_MODE(src_port), VTSS_M_QFWD_SWITCH_PORT_MODE_PORT_ENA);

        // PFC stuff
        REG_WRM(VTSS_HSCH_PFC_CFG(cpu_port),
                VTSS_F_HSCH_PFC_CFG_PFC_LAYER(3) | VTSS_F_HSCH_PFC_CFG_PFC_SE(cpu_port),
                VTSS_M_HSCH_PFC_CFG_PFC_LAYER | VTSS_M_HSCH_PFC_CFG_PFC_SE);
        REG_WRM(VTSS_HSCH_PFC_CFG(src_port),
                VTSS_F_HSCH_PFC_CFG_PFC_LAYER(3) | VTSS_F_HSCH_PFC_CFG_PFC_SE(src_port),
                VTSS_M_HSCH_PFC_CFG_PFC_LAYER | VTSS_M_HSCH_PFC_CFG_PFC_SE);
        REG_WRM(VTSS_QSYS_PFC_CFG(src_port), VTSS_F_QSYS_PFC_CFG_TX_PFC_ENA(0xff),
                VTSS_M_QSYS_PFC_CFG_TX_PFC_ENA);
    }

    return VTSS_RC_OK;
}

#endif // VTSS_FEATURE_PORT_CPU_MASQUERADING

#endif /* VTSS_ARCH_LAIKA */
