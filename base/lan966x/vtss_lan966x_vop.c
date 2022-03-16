// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_lan966x_cil.h"

#if defined(VTSS_ARCH_LAN966X) && defined(VTSS_FEATURE_VOP)

/* Counter clear feature mask's */
#define VTSS_OAM_CNT_CCM      (1<<0)
#define VTSS_OAM_CNT_VOE      (1<<4)
#define VTSS_OAM_CNT_ALL      (VTSS_BITMASK(6))

/* Counter clear direction mask's */
#define VTSS_OAM_CNT_DIR_TX    (1<<31)
#define VTSS_OAM_CNT_DIR_RX    (1<<30)
#define VTSS_OAM_CNT_DIR_BOTH  (VTSS_OAM_CNT_DIR_TX | VTSS_OAM_CNT_DIR_RX)


static vtss_rc voe_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx);

static u32 loc_period_value(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
        return 1;
    case VTSS_VOE_CCM_PERIOD_10_MS:
        return 2;
    case VTSS_VOE_CCM_PERIOD_100_MS:
        return 3;
    case VTSS_VOE_CCM_PERIOD_1_SEC:
        return 4;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static u32 cc_loc_period_index(vtss_voe_ccm_period_t p)
{
    switch (p) {
    case VTSS_VOE_CCM_PERIOD_3_3_MS:
        return 0;
    case VTSS_VOE_CCM_PERIOD_10_MS:
        return 1;
    case VTSS_VOE_CCM_PERIOD_100_MS:
        return 2;
    case VTSS_VOE_CCM_PERIOD_1_SEC:
        return 3;
    }
    VTSS_D("Invalid period for CC");
    return 0;
}

static vtss_rc level_filtering_conf(vtss_state_t           *vtss_state,
                                    const vtss_voe_idx_t   voe_idx,
                                    const vtss_voe_conf_t  *const conf)
{
    u32 value, mask, i;

    VTSS_D("Enter  enable %u", conf->enable);

    value = (conf->enable) ? 0 : (1 << voe_idx);  /* OAM frames on this level or lower, must not be forwarded to this port */
    mask = (1 << voe_idx);
    for (i = 0; i <= conf->meg_level; ++i) {    /* Configure filtering on this level an lower */
        REG_WRM(MEP_MEL_FILTERING_CFG(i), value, mask);
    }

    return VTSS_RC_OK;
}

static vtss_rc voe_counter_update(vtss_state_t         *vtss_state,
                                  const vtss_voe_idx_t  voe_idx,
                                  const u32             clear_mask)
{
/*
 * These macros will aid in reading and optionally clearing counter registers.
 * The clear operation will be triggered by matching the 'clear_mask' with both a
 * counter type (ctype) and a counter direction (cdir - TX or RX).
 */
#define CHIPREAD(reg, cnt, ctype, cdir) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE8(v, cnt, ctype, cdir)    { vtss_cmn_counter_8_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE16(v, cnt, ctype, cdir)   { vtss_cmn_counter_16_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }

    vtss_rc     rc = VTSS_RC_OK;
    u32         v;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    /* CCM counter update */
    CHIPREAD(MEP_CCM_RX_VL_FC_CNT(voe_idx), &chipcnt->ccm.rx_valid_counter,   VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(MEP_CCM_RX_IV_FC_CNT(voe_idx), &chipcnt->ccm.rx_invalid_counter, VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(REW_PTP_SEQ_NO(voe_idx),       &chipcnt->ccm.tx_counter,         VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_TX);

    /* CCM sequence number error counter is a one bit sticky. We need to read a sticky bit and internally accumulate the value. */
    REG_RD(MEP_RX_STICKY(voe_idx), &v);
    REG_WR(MEP_RX_STICKY(voe_idx), MEP_RX_STICKY_CCM_RX_SEQ_ERR_STICKY_M);
    v = MEP_RX_STICKY_CCM_RX_SEQ_ERR_STICKY_X(v);
    vtss_cmn_counter_32_update(v + chipcnt->ccm.rx_oo_counter.prev, &chipcnt->ccm.rx_oo_counter, (clear_mask & VTSS_OAM_CNT_CCM) != 0);

    /* VOE counter update */
    CHIPREAD(MEP_RX_SEL_CNT(voe_idx), &chipcnt->voe.rx_selected_counter,  VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(MEP_RX_FRM_CNT(voe_idx), &chipcnt->voe.rx_counter,           VTSS_OAM_CNT_VOE, VTSS_OAM_CNT_DIR_RX);

    return rc;
#undef CHIPREAD
#undef UPDATE8
#undef UPDATE16
}

static vtss_rc lan966x_voe_alloc(vtss_state_t                *vtss_state,
                                 const vtss_voe_type_t       type,
                                 const vtss_port_no_t        port,
                                 const vtss_oam_direction_t  direction,
                                 vtss_voe_idx_t              *const voe_idx)
{
    u32 i, offset;

    VTSS_D("Enter  type %u  port %u  direction %u", type, port, direction);

    if (type == VTSS_VOE_TYPE_SERVICE) {
        VTSS_E("Service VOE not supported");
        return VTSS_RC_ERROR;
    }
    if (direction == VTSS_OAM_DIRECTION_UP) {
        VTSS_E("Up-VOE not supported");
        return VTSS_RC_ERROR;
    }
    i = VTSS_CHIP_PORT(port);
    if (vtss_state->oam.voe_alloc_data[i].allocated) {
        VTSS_E("No free Port VOE to allocate");
        return VTSS_RC_ERROR;
    }

    *voe_idx = i;
    vtss_state->oam.voe_alloc_data[*voe_idx].allocated = TRUE;
    vtss_state->oam.voe_alloc_data[*voe_idx].type = type;
    vtss_state->oam.voe_alloc_data[*voe_idx].port = port;
    vtss_state->oam.voe_alloc_data[*voe_idx].direction = direction;

    /* Disable VOE */
    REG_WRM(MEP_BASIC_CTRL(*voe_idx), MEP_BASIC_CTRL_VOE_ENA(0), MEP_BASIC_CTRL_VOE_ENA_M);

    /* Clear assorted counters: */
    REG_WR(MEP_CCM_RX_VL_FC_CNT(*voe_idx), 0);       /* Clear assorted counters */
    REG_WR(MEP_CCM_RX_IV_FC_CNT(*voe_idx), 0);
    REG_WR(REW_PTP_SEQ_NO(i), 0);
    REG_WR(MEP_CCM_RX_SEQ_CFG(*voe_idx), 0);
    REG_WR(MEP_RX_SEL_CNT(*voe_idx), 0);
    REG_WR(MEP_RX_FRM_CNT(*voe_idx), 0);

    REG_WR(MEP_RX_STICKY(*voe_idx), 0xffffff);   /* sticky bits cleared by writing 1 to them */
    REG_WR(MEP_STICKY(*voe_idx), 0xff);          /* sticky bits cleared by writing 1 to them */
    REG_WR(MEP_INTR_ENA(*voe_idx), 0);

    /* Clear LM counters */
    offset = *voe_idx * VTSS_PRIO_ARRAY_SIZE;
    for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
        REG_WR(MEP_PORT_RX_FRM_CNT(offset + i), 0);
    }

    VTSS_D("Exit voe_idx %u", *voe_idx);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_free(vtss_state_t          *vtss_state,
                             const vtss_voe_idx_t  voe_idx)
{
    vtss_rc           rc, ret_rc = VTSS_RC_OK;
    vtss_voe_alloc_t  *alloc_data = &vtss_state->oam.voe_alloc_data[voe_idx];

    VTSS_D("Enter  voe_idx %u", voe_idx);

    if (!alloc_data->allocated) {
        VTSS_D("VOE not allocated  voe_idx %u", voe_idx);
        return (VTSS_RC_OK);
    }
    alloc_data->allocated = FALSE;

    /* Update the level filtering mask */
    vtss_state->oam.voe_conf[voe_idx].enable = FALSE;
    VTSS_RC(level_filtering_conf(vtss_state, voe_idx, &vtss_state->oam.voe_conf[voe_idx]));

    if ((rc = voe_default_set(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }

    return (ret_rc);
}

static vtss_rc lan966x_vop_conf_set(vtss_state_t          *vtss_state,
                                    const vtss_vop_conf_t *const conf)
{
    BOOL  npi = vtss_state->packet.npi_conf.enable ? TRUE : FALSE;
    u32   value, npi_port = npi ? VTSS_CHIP_PORT(vtss_state->packet.npi_conf.port_no) : 0;

    VTSS_D("Enter");

    /* Multicast MAC configuration */
    value = (conf->multicast_dmac.addr[0] << 8) | conf->multicast_dmac.addr[1];
    REG_WR(MEP_MC_MAC_MSB, MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(value));

    value = (conf->multicast_dmac.addr[2] << 24) | (conf->multicast_dmac.addr[3] << 16) |
            (conf->multicast_dmac.addr[4] <<  8) | (conf->multicast_dmac.addr[5]);
    value >>= 4;   /* Value in reg. field doesn't include the lower 4 bits */
    REG_WR(MEP_MC_MAC_LSB, MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(value));

    /* CPU extraction queue configuration */
    value = MEP_CPU_CFG_DEF_EXT_PORT_ENA(npi ? 1 : 0) | MEP_CPU_CFG_DEF_COPY_QU(npi ? npi_port : conf->voe_queue_ccm) |
            MEP_CPU_CFG_CPU_ERR_EXT_PORT_ENA(npi ? 1 : 0) | MEP_CPU_CFG_CPU_ERR_QU(npi ? npi_port : conf->voe_queue_err);
    REG_WR(MEP_CPU_CFG, value);

    value = MEP_CPU_CFG_1_CCM_EXT_PORT_ENA(npi ? 1: 0) | MEP_CPU_CFG_1_CCM_CPU_QU(npi ? npi_port : conf->voe_queue_ccm);
    REG_WR(MEP_CPU_CFG_1, value);

    value = MEP_MRP_CPU_CFG_REM_CPU_QU(conf->mrp_queue) | MEP_MRP_CPU_CFG_OWN_CPU_QU(conf->mrp_queue) | MEP_MRP_CPU_CFG_MRP_OTHER_CPU_QU(conf->mrp_queue) |
            MEP_MRP_CPU_CFG_MRP_TST_CPU_QU(conf->mrp_queue) | MEP_MRP_CPU_CFG_MRP_CTRL_CPU_QU(conf->mrp_queue) | MEP_MRP_CPU_CFG_MRP_ITST_CPU_QU(conf->mrp_queue) |
            MEP_MRP_CPU_CFG_MRP_ICTRL_CPU_QU(conf->mrp_queue);
    REG_WR(MEP_MRP_CPU_CFG, value);

    /* Enable master interrupt */
    REG_WRM(MEP_INTR_CTRL, MEP_INTR_CTRL_OAM_MEP_INTR_ENA(1), MEP_INTR_CTRL_OAM_MEP_INTR_ENA_M);

    /* Enable VOP */
    value = MEP_CPU_MASK_CFG_EXT_CPU_PORTMASK(npi ? (0x01 << npi_port) : 0);
    REG_WR(MEP_CPU_MASK_CFG, value);
    value = MEP_MEP_CTRL_MEP_ENA(1) | MEP_MEP_CTRL_LOC_SCAN_ENA(1);
    REG_WR(MEP_MEP_CTRL, value);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_active_get(vtss_state_t   *vtss_state,
                                            const u32      active_size,
                                            u32            *const active)
{
    VTSS_D("Enter  active_size %u", active_size);

    VTSS_MEMSET(active, 0, sizeof(active_size));

    /* just scan all VOEs: */
    REG_RD(MEP_INTR, active);
    *active = MEP_INTR_CCM_INTR_X(*active);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_mask_set(vtss_state_t          *vtss_state,
                                          const vtss_voe_idx_t  voe_idx,
                                          const u32             mask,
                                          const BOOL            enable)
{
    u32 enable_mask, reg_mask;

    VTSS_D("Enter  voe_idx %u  mask %u  enable %u", voe_idx, mask, enable);

    /* Read the interrupt enable mask */
    REG_RD(MEP_INTR_ENA(voe_idx), &enable_mask);

    /* Translate the input mask to register mask */
    reg_mask = ((mask & VTSS_VOE_EVENT_MASK_CCM_PERIOD)      ? MEP_INTR_ENA_CCM_PER_INTR_ENA_M       : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_PRIORITY)    ? MEP_INTR_ENA_CCM_PRIO_INTR_ENA_M      : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD) ? MEP_INTR_ENA_CCM_ZERO_PER_INTR_ENA_M  : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_RX_RDI)      ? MEP_INTR_ENA_CCM_RX_RDI_INTR_ENA_M    : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_LOC)         ? MEP_INTR_ENA_CCM_LOC_INTR_ENA_M       : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_MEP_ID)      ? MEP_INTR_ENA_CCM_MEPID_INTR_ENA_M     : 0) |
               ((mask & VTSS_VOE_EVENT_MASK_CCM_MEG_ID)      ? MEP_INTR_ENA_CCM_MEGID_INTR_ENA_M     : 0);

    /* Calculate new enable mask */
    enable_mask = enable ? (enable_mask | reg_mask) : (enable_mask & ~reg_mask);

    /* Write back the interrupt enable mask */
    REG_WR(MEP_INTR_ENA(voe_idx), enable_mask);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_event_get(vtss_state_t          *vtss_state,
                                     const vtss_voe_idx_t  voe_idx,
                                     u32                   *const mask)
{
    u32 enable_mask, sticky_mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Read the interrupt enable mask */
    REG_RD(MEP_INTR_ENA(voe_idx), &enable_mask);

    /* Read sticky bits and clear the enabled ones */
    REG_RD(MEP_STICKY(voe_idx), &sticky_mask);
    sticky_mask &= enable_mask;
    REG_WR(MEP_STICKY(voe_idx), sticky_mask); /* Sticky bits cleared by writing 1 to them */

    /* Translate sticky mask to returned event mask */
    *mask = (((sticky_mask & MEP_STICKY_CCM_PERIOD_STICKY_M) != 0)      ? VTSS_VOE_EVENT_MASK_CCM_PERIOD      : 0) |
            (((sticky_mask & MEP_STICKY_CCM_PRIO_STICKY_M) != 0)        ? VTSS_VOE_EVENT_MASK_CCM_PRIORITY    : 0) |
            (((sticky_mask & MEP_STICKY_CCM_ZERO_PERIOD_STICKY_M) != 0) ? VTSS_VOE_EVENT_MASK_CCM_ZERO_PERIOD : 0) |
            (((sticky_mask & MEP_STICKY_CCM_RX_RDI_STICKY_M) != 0)      ? VTSS_VOE_EVENT_MASK_CCM_RX_RDI      : 0) |
            (((sticky_mask & MEP_STICKY_CCM_LOC_STICKY_M) != 0)         ? VTSS_VOE_EVENT_MASK_CCM_LOC         : 0) |
            (((sticky_mask & MEP_STICKY_CCM_MEPID_STICKY_M) != 0)       ? VTSS_VOE_EVENT_MASK_CCM_MEP_ID      : 0) |
            (((sticky_mask & MEP_STICKY_CCM_MEGID_STICKY_M) != 0)       ? VTSS_VOE_EVENT_MASK_CCM_MEG_ID      : 0);

    VTSS_D("Exit  mask %X", *mask);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_conf_set(vtss_state_t           *vtss_state,
                                    const vtss_voe_idx_t   voe_idx,
                                    const vtss_voe_conf_t  *const conf)
{
    u32  value, mask;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure the unicast MAC */
    value = MEP_UC_MAC_MSB_MEP_UC_MAC_MSB((conf->unicast_mac.addr[0] << 8) | conf->unicast_mac.addr[1]);
    REG_WR(MEP_UC_MAC_MSB(voe_idx), value);
    value = (conf->unicast_mac.addr[2] << 24) | (conf->unicast_mac.addr[3] << 16) |
        (conf->unicast_mac.addr[4] <<  8) | (conf->unicast_mac.addr[5]);
    REG_WR(MEP_UC_MAC_LSB(voe_idx), value);

    /* Configure MEG level and Up-MEP port mask and Up-MEP Loop Back mode */
    value = MEP_MEL_CTRL_MEL_VAL(conf->meg_level);
    mask = MEP_MEL_CTRL_MEL_VAL_M;
    REG_WRM(MEP_MEL_CTRL(voe_idx), value, mask);

    /* Configure the DMAC check type */
    switch (conf->dmac_check_type) {
    case VTSS_VOE_DMAC_CHECK_NONE:
        value = MEP_BASIC_CTRL_RX_DMAC_CHK_SEL(0x01);
        break;
    case VTSS_VOE_DMAC_CHECK_UNICAST:
        value = MEP_BASIC_CTRL_RX_DMAC_CHK_SEL(0x01);
        break;
    case VTSS_VOE_DMAC_CHECK_MULTICAST:
        value = MEP_BASIC_CTRL_RX_DMAC_CHK_SEL(0x02);
        break;
    case VTSS_VOE_DMAC_CHECK_BOTH:
        value = MEP_BASIC_CTRL_RX_DMAC_CHK_SEL(0x03);
        break;
    }
    mask = MEP_BASIC_CTRL_RX_DMAC_CHK_SEL_M;
    REG_WRM(MEP_BASIC_CTRL(voe_idx), value, mask);

    switch (conf->tagging) {
    case VTSS_PORT_MAX_TAGS_NONE:
        value = ANA_OAM_CFG_OAM_CFG(0x01);
        break;
    case VTSS_PORT_MAX_TAGS_ONE:
        value = ANA_OAM_CFG_OAM_CFG(0x02);
        break;
    case VTSS_PORT_MAX_TAGS_TWO:
        value = ANA_OAM_CFG_OAM_CFG(0x03);
        break;
    }
    REG_WRM(ANA_OAM_CFG(voe_idx), value, ANA_OAM_CFG_OAM_CFG_M);  /* voe_idx is the chip port number */

    /* Update the level filtering mask */
    VTSS_RC(level_filtering_conf(vtss_state, voe_idx, conf));

    /* Enable/Disable VOE */
    REG_WRM(MEP_BASIC_CTRL(voe_idx), MEP_BASIC_CTRL_VOE_ENA(conf->enable ? 1 : 0), MEP_BASIC_CTRL_VOE_ENA_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_conf_set(vtss_state_t              *vtss_state,
                                       const vtss_voe_idx_t      voe_idx,
                                       const vtss_voe_cc_conf_t  *const conf)
{
    u32                 i, value, mask;
    const u8            *p;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Configure CPU copy */
    value = (conf->enable && (conf->cpu_copy == VTSS_OAM_CPU_COPY_ALL)) ? MEP_CPU_COPY_CTRL_CCM_CPU_CP(1) : 0;
    mask = MEP_CPU_COPY_CTRL_CCM_CPU_CP_M;
    REG_WRM(MEP_CPU_COPY_CTRL(voe_idx), value, mask);

    /* Clear sequence numbers */
    REG_RD(MEP_BASIC_CTRL(voe_idx), &value);
    if (conf->enable && (MEP_BASIC_CTRL_VOE_ENA_X(value) == 0)) {    /* The Tx and Rx sequence numbers are cleared when CC is enabled */
        REG_WR(REW_PTP_SEQ_NO(voe_idx), 0);
        REG_WR(MEP_CCM_RX_SEQ_CFG(voe_idx), 0);
        vtss_cmn_counter_32_rebase(0, &vtss_state->oam.voe_internal[voe_idx].counters.ccm.tx_counter);    /* Always re-base when Tx sequence number is changed */
    }

    /* Configure prio, period ect. */
    value = MEP_CCM_CFG_CCM_RX_SEQ_CHK_ENA(1)                               |
            MEP_CCM_CFG_CCM_PRIO(conf->expected_priority)                   |
            MEP_CCM_CFG_CCM_PERIOD(loc_period_value(conf->expected_period)) |
            MEP_CCM_CFG_CCM_MEGID_CHK_ENA(1)                                |
            MEP_CCM_CFG_CCM_MEPID_CHK_ENA(1);
    mask = MEP_CCM_CFG_CCM_RX_SEQ_CHK_ENA_M |
           MEP_CCM_CFG_CCM_PRIO_M           |
           MEP_CCM_CFG_CCM_PERIOD_M         |
           MEP_CCM_CFG_CCM_MEGID_CHK_ENA_M  |
           MEP_CCM_CFG_CCM_MEPID_CHK_ENA_M;
    REG_WRM(MEP_CCM_CFG(voe_idx), value, mask);

    /* Configure the sequence number update enable in rewriter */
    REG_WRM(REW_CCM_TX_CFG(voe_idx), REW_CCM_TX_CFG_CCM_SEQ_UPD_ENA(conf->seq_no_update ? 1 : 0), REW_CCM_TX_CFG_CCM_SEQ_UPD_ENA_M);

    /* Configure MEG id */
    p = &conf->expected_megid[47];    // MSB
    for (i = 0; i < 12; ++i, p -= 4) {
        value = (*(p - 3) << 24) | (*(p - 2) << 16) | (*(p - 1) <<  8) | (*(p - 0));
        REG_WR(MEP_CCM_MEGID_CFG(voe_idx, i), value);
    }

    /* Configure count_as_selected */
    REG_WRM(MEP_CNT_OAM_CTRL(voe_idx), MEP_CNT_OAM_CTRL_CCM_OAM_CNT((conf->enable && conf->count_as_selected) ? 1 : 0), MEP_CNT_OAM_CTRL_CCM_OAM_CNT_M);

    /* Configure peer MEP id */
    REG_WR(MEP_CCM_MEPID_CFG(voe_idx), MEP_CCM_MEPID_CFG_CCM_MEPID(conf->expected_peer_mepid));

    /* Enable/Disable CCM handling */
    REG_WRM(MEP_HW_CTRL(voe_idx), MEP_HW_CTRL_CCM_ENA(conf->enable ? 1 : 0), MEP_HW_CTRL_CCM_ENA_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_rdi_set(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx,
                                      const BOOL            rdi)
{
    VTSS_D("Enter  voe_idx %u  rdi %u", voe_idx, rdi);

    REG_WRM(REW_CCM_TX_CFG(voe_idx), REW_CCM_TX_CFG_CCM_TX_RDI(rdi ? 1 : 0), REW_CCM_TX_CFG_CCM_TX_RDI_M);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_cpu_copy_next_set(vtss_state_t          *vtss_state,
                                                const vtss_voe_idx_t  voe_idx)
{
    u32 value, mask;

    value = MEP_BASIC_CTRL_CPU_ONCE_CCM_TLV(1) |
            MEP_BASIC_CTRL_CCM_ERR_CPU_ONCE(1) |
            MEP_BASIC_CTRL_CCM_NXT_CPU_ONCE(1);
    mask = MEP_BASIC_CTRL_CPU_ONCE_CCM_TLV_M | MEP_BASIC_CTRL_CCM_ERR_CPU_ONCE_M | MEP_BASIC_CTRL_CCM_NXT_CPU_ONCE_M;
    REG_WRM(MEP_BASIC_CTRL(voe_idx), value, mask);

    value = MEP_MEL_CTRL_CPU_HITME_ONCE_CCM_MTL(1);
    mask = MEP_MEL_CTRL_CPU_HITME_ONCE_CCM_MTL_M;
    REG_WRM(MEP_MEL_CTRL(voe_idx), value, mask);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_status_get(vtss_state_t          *vtss_state,
                                      const vtss_voe_idx_t  voe_idx,
                                      vtss_voe_status_t     *const status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    REG_RD(MEP_RX_STICKY(voe_idx), &value);
    status->opcode_unexp_seen  = MEP_RX_STICKY_UNK_OPCODE_RX_STICKY_X(value);
    status->dmac_unexp_seen    = MEP_RX_STICKY_MAC_ADDR_ERR_STICKY_X(value);

    /* Clear the RX sticky bits that has been detected */
    value = value &
            (MEP_RX_STICKY_UNK_OPCODE_RX_STICKY_M  |
             MEP_RX_STICKY_MAC_ADDR_ERR_STICKY_M   |
             MEP_RX_STICKY_MEP_EGR_BLOCK_STICKY_M);
    REG_WR(MEP_RX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_status_get(vtss_state_t          *vtss_state,
                                         const vtss_voe_idx_t  voe_idx,
                                         vtss_voe_cc_status_t  *status)
{
    u32 value;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Calculate CCM received status */
    REG_RD(MEP_CCM_CFG(voe_idx), &value);
    status->zero_period     = MEP_CCM_CFG_CCM_ZERO_PERIOD_ERR_X(value);
    status->rdi             = MEP_CCM_CFG_CCM_RX_RDI_X(value);
    status->loc             = (MEP_CCM_CFG_CCM_MISS_CNT_X(value) == 0x07) != 0;
    status->period_unexp    = MEP_CCM_CFG_CCM_PERIOD_ERR_X(value);
    status->priority_unexp  = MEP_CCM_CFG_CCM_PRIO_ERR_X(value);
    status->mep_id_unexp    = MEP_CCM_CFG_CCM_MEPID_ERR_X(value);
    status->meg_id_unexp    = MEP_CCM_CFG_CCM_MEGID_ERR_X(value);

    /* Calculate the 'xxx_seen' - read the RX sticky bits */
    REG_RD(MEP_RX_STICKY(voe_idx), &value);
    status->seen           = MEP_RX_STICKY_CCM_RX_STICKY_X(value) || MEP_RX_STICKY_CCM_LM_RX_STICKY_X(value);

    /* Clear the sticky bits that has been detected */
    value = value &
            (MEP_RX_STICKY_CCM_RX_STICKY_M | MEP_RX_STICKY_CCM_LM_RX_STICKY_M);
    REG_WR(MEP_RX_STICKY(voe_idx), value);

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_counters_get(vtss_state_t         *vtss_state,
                                        const vtss_voe_idx_t voe_idx,
                                        vtss_voe_counters_t  *const counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    VTSS_MEMSET(counters, 0, sizeof(*counters));
    counters->rx_counter          = chipcnt->voe.rx_counter.value;

    return rc;
}

static vtss_rc lan966x_voe_cc_counters_get(vtss_state_t           *vtss_state,
                                           const vtss_voe_idx_t   voe_idx,
                                           vtss_voe_cc_counters_t *counters)
{
    vtss_rc                           rc;
    vtss_oam_voe_internal_counters_t  *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter  voe_idx %u", voe_idx);

    /* Poll so we get the most recent counter values */
    rc = voe_counter_update(vtss_state, voe_idx, 0);

    /* Get the counters */
    counters->rx_valid_counter   = chipcnt->ccm.rx_valid_counter.value;
    counters->rx_invalid_counter = chipcnt->ccm.rx_invalid_counter.value;
    counters->rx_oo_counter      = chipcnt->ccm.rx_oo_counter.value;
    counters->tx_counter         = chipcnt->ccm.tx_counter.value;

    return rc;
}

static vtss_rc lan966x_voe_counters_clear(vtss_state_t          *vtss_state,
                                          const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_VOE | VTSS_OAM_CNT_DIR_BOTH));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_voe_cc_counters_clear(vtss_state_t          *vtss_state,
                                             const vtss_voe_idx_t  voe_idx)
{
    VTSS_D("Enter  voe_idx %u", voe_idx);

    VTSS_RC(voe_counter_update(vtss_state, voe_idx, VTSS_OAM_CNT_CCM | VTSS_OAM_CNT_DIR_BOTH));

    return VTSS_RC_OK;
}

static vtss_rc lan966x_oam_voe_poll_1sec(vtss_state_t *vtss_state)
{
    vtss_voe_idx_t *idx = &(vtss_state->oam.voe_poll_idx);  /* For readability */

    VTSS_RC(voe_counter_update(vtss_state, *idx, 0));
    *idx = (*idx == VTSS_VOE_CNT - 1) ? 0 : *idx + 1;

    return VTSS_RC_OK;
}

// D_COM: Debug COMmon; DR_COM: Debug Read COMmon. _I for Instance. Etc.
#define D_REG(pr, name)            vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(name), name)
#define D_REG_I(pr, name, i)       vtss_lan966x_debug_reg_inst(vtss_state, pr, name, (i), name)

static vtss_rc lan966x_debug_oam(vtss_state_t               *vtss_state,
                                 const vtss_debug_printf_t  pr,
                                 const vtss_debug_info_t    *const info)
{
    u32   i, k, v, div, voe_idx;
    char  buf[80];
    BOOL  show, vop, voe, status, lm_counters;

    div = 0;
    voe_idx = 0;
    show = vop = voe = status = lm_counters = FALSE;

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        vop = (info->action == 1) ? TRUE : FALSE;

        if (info->action > 2) { /* This potentially a VOE config or VOE status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                voe = (info->action / div == 4) ? TRUE : FALSE;
                status = (info->action / div == 5) ? TRUE : FALSE;
                lm_counters = (info->action / div == 6) ? TRUE : FALSE;
                if (voe || status || lm_counters) {
                    break;
                }
            }
            if (voe || status || lm_counters) {    /* Calculate the possible VOE/MIP index */
                voe_idx = info->action % div;
            }
        }
    }

    VTSS_D("show %u  vop %u  voe %u  status %u  lm_counters %u", show, vop, voe, status, lm_counters);

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print VOP configurations\n");
        pr("    4XXXX: Print VOE XXXX configurations. Without XXXX all VOEs are printed\n");
        pr("    5XXXX: Print VOE XXXX status. Without XXXX all VOEs are printed\n");
        pr("    6XXXX: Print VOE XXXX LM counters. Without XXXX all VOEs are printed\n");
        pr("\n");
    }

    if (!info->has_action || vop) { /* VOP configuration must be printed */
        vtss_lan966x_debug_reg_header(pr, "VOP");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_MEP_CTRL), "MEP_MEP_CTRL");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_CPU_CFG), "MEP_CPU_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_CPU_CFG_1), "MEP_CPU_CFG_1");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_MRP_CPU_CFG), "MEP_MRP_CPU_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_DLR_CPU_CFG), "MEP_DLR_CPU_CFG");
        for (i=0; i<8; ++i)
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_GENERIC_CFG(i)), i, "MEP_GENERIC_CFG");
        for (i=0; i<7; ++i)
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_LOC_PERIOD_CFG(i)), i, "MEP_LOC_PERIOD_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_LOC_CTRL), "MEP_LOC_CTRL");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_LOC_SCAN_STICKY), "MEP_LOC_SCAN_STICKY");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_INTR_CTRL), "MEP_INTR_CTRL");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_INTR), "MEP_INTR");
        for (i=0; i<7; ++i)
            vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_VOE_CNT_CTRL(i)), i, "MEP_VOE_CNT_CTRL");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_MC_MAC_MSB), "MEP_MC_MAC_MSB");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_MC_MAC_LSB), "MEP_MC_MAC_LSB");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_TICK_CFG), "MEP_TICK_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_MRP_RX_TS_CFG), "MEP_MRP_RX_TS_CFG");
        vtss_lan966x_debug_reg(vtss_state, pr, REG_ADDR(MEP_DBG_STICKY), "MEP_DBG_STICKY");
        pr("\n");
    }

    if (!info->has_action || voe) { /* VOE configuration must be printed */
        pr("VOE Config:\n\n");

        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (voe && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            REG_RD(MEP_BASIC_CTRL(i), &v);
            if (info->full  ||  MEP_BASIC_CTRL_VOE_ENA_X(v)) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_lan966x_debug_reg_header(pr, buf);
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_BASIC_CTRL(i)), i, "MEP_BASIC_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_MEL_CTRL(i)), i, "MEP_MEL_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CPU_COPY_CTRL(i)), i, "MEP_CPU_COPY_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_FWD_CTRL(i)), i, "MEP_FWD_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CNT_OAM_CTRL(i)), i, "MEP_CNT_OAM_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CNT_DATA_CTRL(i)), i, "MEP_CNT_DATA_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_UC_MAC_LSB(i)), i, "MEP_UC_MAC_LSB");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_UC_MAC_MSB(i)), i, "MEP_UC_MAC_MSB");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_HW_CTRL(i)), i, "MEP_HW_CTRL");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_CFG(i)), i, "MEP_CCM_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(REW_PTP_SEQ_NO(i)), i, "REW_PTP_SEQ_NO");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_RX_SEQ_CFG(i)), i, "MEP_CCM_RX_SEQ_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_MEPID_CFG(i)), i, "MEP_CCM_MEPID_CFG");
                for (k=0; k<12; ++k)
                    vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_MEGID_CFG(i, k)), 11-k, "MEP_CCM_MEGID_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_INTR_ENA(i)), i, "MEP_INTR_ENA");
                pr("\n");
            }
        }
    }
    pr("\n");

    if (!info->has_action || status) { /* VOE status must be printed */
        pr("VOE Status:\n\n");

        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (status && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            REG_RD(MEP_BASIC_CTRL(i), &v);
            if (info->full  ||  MEP_BASIC_CTRL_VOE_ENA_X(v)) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_lan966x_debug_reg_header(pr, buf);
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_CFG(i)), i, "MEP_CCM_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_RX_VL_FC_CNT(i)), i, "MEP_CCM_RX_VL_FC_CNT");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_RX_IV_FC_CNT(i)), i, "MEP_CCM_RX_IV_FC_CNT");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(REW_PTP_SEQ_NO(i)), i, "REW_PTP_SEQ_NO");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_CCM_RX_SEQ_CFG(i)), i, "MEP_CCM_RX_SEQ_CFG");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_RX_STICKY(i)), i, "MEP_RX_STICKY");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_STICKY(i)), i, "MEP_STICKY");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_RX_SEL_CNT(i)), i, "MEP_RX_SEL_CNT");
                vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_RX_FRM_CNT(i)), i, "MEP_RX_FRM_CNT");
            }
        }
    }
    pr("\n");

    if (!info->has_action || lm_counters) { /* VOE status must be printed */
        pr("VOE LM counters:\n\n");

        for (i=0; i<VTSS_VOE_CNT; ++i) {
            if (lm_counters && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }

            REG_RD(MEP_BASIC_CTRL(i), &v);
            if (info->full  ||  MEP_BASIC_CTRL_VOE_ENA_X(v)) {
                VTSS_SPRINTF(buf, "VOE %u", i);
                vtss_lan966x_debug_reg_header(pr, buf);

                for (k = 0; k < VTSS_PRIO_ARRAY_SIZE; ++k) {
                    VTSS_SPRINTF(buf, "Priority %u", k);
                    vtss_lan966x_debug_reg_inst(vtss_state, pr, REG_ADDR(MEP_PORT_RX_FRM_CNT(i)), ((i*VTSS_PRIO_ARRAY_SIZE)+k), "MEP_PORT_RX_FRM_CNT");
                }
            }
        }
    }
    pr("\n");

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_oam_debug_print(vtss_state_t               *vtss_state,
                                     const vtss_debug_printf_t  pr,
                                     const vtss_debug_info_t    *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_OAM, lan966x_debug_oam, vtss_state, pr, info);
}

#undef D_REG
#undef D_REG_I

static vtss_rc voe_default_set(vtss_state_t          *vtss_state,
                               const vtss_voe_idx_t  voe_idx)
{
    vtss_rc  rc, ret_rc = VTSS_RC_OK;

    VTSS_MEMSET(&vtss_state->oam.voe_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_cc_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_cc_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_rdi_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_rdi_conf[voe_idx]));
    VTSS_MEMSET(&vtss_state->oam.voe_event_mask[voe_idx], 0, sizeof(vtss_state->oam.voe_event_mask[voe_idx]));

    if ((rc = lan966x_voe_event_mask_set(vtss_state, voe_idx, VTSS_VOE_EVENT_MASK_ALL, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = lan966x_voe_cc_rdi_set(vtss_state, voe_idx, FALSE)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = lan966x_voe_cc_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_cc_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = lan966x_voe_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = lan966x_voe_cc_counters_clear(vtss_state, voe_idx)) != VTSS_RC_OK) {
        ret_rc = rc;
    }
    if ((rc = lan966x_voe_conf_set(vtss_state, voe_idx, &vtss_state->oam.voe_conf[voe_idx])) != VTSS_RC_OK) {
        ret_rc = rc;
    }

    return(ret_rc);
}

static vtss_rc lan966x_init(vtss_state_t *vtss_state)
{
    u32 i, clk_period_in_ps, base_tick_ps, value;

    /* All VOEs are default enabled by hardware; we disable them here. */
    for (i=0; i < VTSS_VOE_CNT; ++i) {
        REG_WR(MEP_BASIC_CTRL(i), 0);
    }

    /* Disable VOP */
    REG_WR(MEP_MEP_CTRL, 0);

    /* Configure LOC base tick count */
    clk_period_in_ps = vtss_lan966x_clk_period_ps(vtss_state);
    base_tick_ps = 200 * 1000;    /* Base tick target is 200 ns */
    value = base_tick_ps / clk_period_in_ps; /* clk_period * value = base_tick */
    REG_WRM(MEP_LOC_CTRL, MEP_LOC_CTRL_BASE_TICK_CNT(value), MEP_LOC_CTRL_BASE_TICK_CNT_M);
    base_tick_ps = clk_period_in_ps * value;

    /* Configure LOC periods used for CCM LOC. Note that MRP is using the last six LOC timers */
    value = (3300000000 / base_tick_ps) + ((3300000000 % base_tick_ps) ? 1 : 0);
    REG_WR(MEP_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_3_3_MS)), value);
    value = (10000000000 / base_tick_ps) + ((10000000000 % base_tick_ps) ? 1 : 0);
    REG_WR(MEP_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_10_MS)), value);
    value = (100000000000 / base_tick_ps) + ((100000000000 % base_tick_ps) ? 1 : 0);
    REG_WR(MEP_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_100_MS)), value);
    value = (1000000000000 / base_tick_ps) + ((1000000000000 % base_tick_ps) ? 1 : 0);
    REG_WR(MEP_LOC_PERIOD_CFG(cc_loc_period_index(VTSS_VOE_CCM_PERIOD_1_SEC)), value);

    /* Configure analyzer to default mark OAM as untagged */
    for (i=0; i < VTSS_CHIP_PORTS; ++i) {
        REG_WR(ANA_OAM_CFG(i), ANA_OAM_CFG_OAM_CFG(1));
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_lan966x_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_oam_state_t *state = &vtss_state->oam;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->voe_alloc = lan966x_voe_alloc;
        state->voe_free = lan966x_voe_free;
        state->vop_conf_set = lan966x_vop_conf_set;
        state->voe_event_active_get = lan966x_voe_event_active_get;
        state->voe_event_mask_set = lan966x_voe_event_mask_set;
        state->voe_event_get = lan966x_voe_event_get;
        state->voe_conf_set = lan966x_voe_conf_set;
        state->voe_cc_conf_set = lan966x_voe_cc_conf_set;
        state->voe_cc_rdi_set = lan966x_voe_cc_rdi_set;
        state->voe_cc_cpu_copy_next_set = lan966x_voe_cc_cpu_copy_next_set;
        state->voe_status_get = lan966x_voe_status_get;
        state->voe_cc_status_get = lan966x_voe_cc_status_get;
        state->voe_counters_get = lan966x_voe_counters_get;
        state->voe_cc_counters_get = lan966x_voe_cc_counters_get;
        state->voe_counters_clear = lan966x_voe_counters_clear;
        state->voe_cc_counters_clear = lan966x_voe_cc_counters_clear;
        break;

    case VTSS_INIT_CMD_INIT:
        VTSS_RC(lan966x_init(vtss_state));
        break;

    case VTSS_INIT_CMD_POLL:
        VTSS_RC(lan966x_oam_voe_poll_1sec(vtss_state));
        break;

    default:
        break;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_ARCH_LAN966X */
