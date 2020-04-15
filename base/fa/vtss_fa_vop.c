/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_OAM
#include "vtss_fa_cil.h"

#if defined(VTSS_ARCH_FA)

#if defined(VTSS_FEATURE_VOP)

#if 0

/* Boolean-to-bits */
#define B2B(boolean, bits)        ((boolean) ? (bits) : 0)
/* system clock is 2,0 ns (500 MHz) and LOC_BASE_TICK_CNT is default 50, i.e. 100 ns */
#define LOC_BASE 100 /* ns */

#if !defined(VTSS_FEATURE_EVC)
/* For convenience, the EVC entry type is defined as void for non-EVC targets */
typedef void vtss_evc_entry_t;
#endif /* VTSS_FEATURE_EVC */


static u32 isdx_count = 0;

/* ================================================================= *
 *  Y.1731/802.1ag OAM
 * ================================================================= */

static vtss_rc mce_clm_add(vtss_state_t      *vtss_state,
                           vtss_mce_entry_t  *mce,
                           vtss_evc_entry_t  *evc,
                           vtss_port_no_t    uni_port);


/*************************************/
/***** Internal helper functions *****/
/*************************************/

static vtss_vcap_user_t order_to_clm_user(vtss_mce_order_t order)
{
    switch (order) {
    case VTSS_MCE_ORDER_0:
        return VTSS_IS1_USER_MCE_0;
    case VTSS_MCE_ORDER_1:
        return VTSS_IS1_USER_MCE_1;
    case VTSS_MCE_ORDER_2:
        return VTSS_IS1_USER_MCE_2;
    case VTSS_MCE_ORDER_3:
        return VTSS_IS1_USER_MCE_3;
    case VTSS_MCE_ORDER_4:
        return VTSS_IS1_USER_MCE_4;
    }
    return VTSS_IS1_USER_MCE_2;
}

static vtss_vcap_user_t order_to_es0_user(vtss_mce_order_t order)
{
    switch (order) {
    case VTSS_MCE_ORDER_0:
        return VTSS_ES0_USER_MCE_0;
    case VTSS_MCE_ORDER_1:
        return VTSS_ES0_USER_MCE_1;
    case VTSS_MCE_ORDER_2:
        return VTSS_ES0_USER_MCE_2;
    case VTSS_MCE_ORDER_3:
        return VTSS_ES0_USER_MCE_3;
    case VTSS_MCE_ORDER_4:
        return VTSS_ES0_USER_MCE_3;
    }
    return VTSS_ES0_USER_MCE_2;
}

static vtss_vcap_id_t mce_vcap_id(vtss_mce_id_t mce_id, vtss_port_no_t port_no)
{
    vtss_vcap_id_t id = port_no;

    return ((id << 32) + mce_id);
}

static void mce2is1_tag(const vtss_mce_tag_t *mce_tag, vtss_is1_tag_t *is1_tag)
{
    is1_tag->tagged = mce_tag->tagged;
    is1_tag->s_tag = mce_tag->s_tagged;
    is1_tag->vid.type = VTSS_VCAP_VR_TYPE_VALUE_MASK;
    is1_tag->vid.vr.v.value = mce_tag->vid.value;
    is1_tag->vid.vr.v.mask = mce_tag->vid.mask;
    is1_tag->pcp = mce_tag->pcp;
    is1_tag->dei = mce_tag->dei;
}

#if defined(VTSS_FEATURE_EVC)
static vtss_sdx_entry_t *evc_isdx_get(vtss_state_t *vtss_state, vtss_evc_entry_t *evc,  vtss_port_no_t port,  BOOL leaf)
{
    vtss_sdx_entry_t         *sdx = NULL;
    vtss_evc_port_evc_conf_t *conf = &vtss_state->evc.port_info_table[evc->port_idx[port]].conf;

    for (sdx = evc->isdx_list; sdx != NULL; sdx = sdx->next) {
        if ((sdx->port_no == port) && ((conf->role != VTSS_EVC_PORT_ROLE_NNI) || (leaf && (sdx->id != 0)) || (!leaf && (sdx->id == 0)))) {
            return (sdx);
        }
    }
    return (NULL);
}
#endif /* VTSS_FEATURE_EVC */

static BOOL more_than_one_port(BOOL *port_list)
{
    u32 i, cnt = 0;

    for (i = 0; i < VTSS_PORT_ARRAY_SIZE; ++i) {
        if (port_list[i]) {
            cnt++;
            if (cnt > 1) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

static BOOL key_mac(u8 *mask)
{
    u32 i;

    for (i = 0; i < 6; ++i) {
        if (mask[i]) {
            return TRUE;
        }
    }
    return FALSE;
}

static BOOL require_normal_key(vtss_mce_t *conf)
{
    return ((conf->key.looped || conf->key.masqueraded || (conf->key.opcode != VTSS_OAM_OPCODE_NONE) || (conf->action.forward_sel == VTSS_MCE_FORWARD_DISABLE) ||   /* Matching on loop interface OR opcode OR masqueraded OR port ingress OR */
             more_than_one_port(conf->key.port_list) || key_mac(conf->key.smac.mask) || key_mac(conf->key.dmac.mask)) ? TRUE : FALSE);  /* multiple ports OR SMAC OR DMAC requires X8 */
}

static vtss_rc fa_oam_voe_counter_clear(vtss_state_t *vtss_state,
                                        const vtss_oam_voe_idx_t voe_idx, const u32 mask);


static BOOL mce_isdx_reuse(vtss_isdx_t isdx)
{
    return (((isdx == 0) || (isdx == VTSS_MCE_ISDX_NONE) || (isdx == VTSS_MCE_ISDX_NEW) || (isdx == VTSS_MCE_ISDX_EVC)) ? FALSE : TRUE);
}

/* CCM-LM: the HW period "runs at double speed", so we need to dedicate two
 * slots in the LOCC period config register for double values and use those
 * slots when CCM-LM is configured.
 *
 * However, from an API standpoint the user doesn't need to know this, so we
 * use the standard enums from #vtss_oam_period_t in the API and convert them
 * to the HW-near values here.
 *
 * This, of course, invalidates the semantics of the enum, so we return u32
 * from this func. Also note that only the 100ms and 1-sec values are supported
 * by the API.
 */
static u32 fa_oam_ccm_lm_period_index(vtss_oam_period_t p)
{
    switch (p) {
    case VTSS_OAM_PERIOD_100_MS:
        return 5; /* LOC index 5 is used for 100 ms CCM-LM insertion */
    case VTSS_OAM_PERIOD_1_SEC:
        return 6; /* LOC index 6 is used for 1 s CCM-LM insertion */
    default:
        return 0;
    }
}

static vtss_rc doing_calculate(vtss_state_t *vtss_state,
                               u32 voe_idx,  BOOL *doing_lb,  BOOL *doing_tst)
{
    u32 v;
    BOOL lb_hw_enabled, tst_hw_enabled;

    REG_RD(VTSS_VOP_OAM_HW_CTRL(voe_idx), &v);
    lb_hw_enabled  = (v & (VTSS_M_VOP_OAM_HW_CTRL_LBM_ENA | VTSS_M_VOP_OAM_HW_CTRL_LBR_ENA)) != 0;
    tst_hw_enabled = (v & VTSS_M_VOP_OAM_HW_CTRL_TST_ENA) != 0;

    *doing_lb  = lb_hw_enabled  && !tst_hw_enabled;
    *doing_tst = tst_hw_enabled && !lb_hw_enabled;

    return (VTSS_RC_OK);
}

static vtss_rc oam_sat_cosid_counters_update(vtss_state_t             *vtss_state,
                                             const vtss_oam_voe_idx_t voe_idx,
                                             const u16                cosid_seq_no_idx,
                                             const u32                prio,
                                             const BOOL               clear)
{
#define CHIPREAD(reg, cnt, clear) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, clear); }
#define UPDATE16(v, cnt, clear)   { vtss_cmn_counter_16_update(v, cnt, clear); }
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);
    vtss_oam_sat_cosid_internal_counters_t *chipcnt = &vtss_state->oam.sat_cosid_counters[cosid_seq_no_idx];
    u32 v;

    VTSS_D("Enter VOE %d", voe_idx);

    if (prio < 7) {
        CHIPREAD(VTSS_VOP_SAM_LBM_TX_TRANSID(cosid_seq_no_idx, prio),         &chipcnt->tx_ccm_lbm_tst[prio],      clear);
        CHIPREAD(VTSS_VOP_SAM_LBR_TX_FRM_CNT(cosid_seq_no_idx, prio),         &chipcnt->tx_lbr[prio],              clear);
        CHIPREAD(VTSS_VOP_SAM_LBR_RX_FRM_CNT(cosid_seq_no_idx, prio),         &chipcnt->rx_ccm_lbr_tst[prio],      clear);
        CHIPREAD(VTSS_VOP_SAM_LBR_RX_TRANSID(cosid_seq_no_idx, prio),         &chipcnt->rx_lbr_trans_id[prio],     clear);
        CHIPREAD(VTSS_VOP_SAM_LBR_RX_TRANSID_ERR_CNT(cosid_seq_no_idx, prio), &chipcnt->rx_lbr_trans_id_err[prio], clear);
    } else {
        if (cfg->sat.cosid_seq_no_mode == VTSS_OAM_SAT_COSID_SEQ_NO_CCM) {
            CHIPREAD(VTSS_VOP_CCM_TX_SEQ_CFG(voe_idx),                              &chipcnt->tx_ccm_lbm_tst[prio],      clear);
            CHIPREAD(VTSS_VOP_LBR_TX_FRM_CNT(voe_idx),                              &chipcnt->tx_lbr[prio],              clear);
            REG_RD(VTSS_VOP_CCM_RX_FRM_CNT(voe_idx), &v);
            UPDATE16(VTSS_X_VOP_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT(v),                &chipcnt->rx_ccm_lbr_tst[prio],      clear);
            CHIPREAD(VTSS_VOP_CCM_RX_SEQ_CFG(voe_idx),                              &chipcnt->rx_lbr_trans_id[prio],     clear);
            REG_RD(VTSS_VOP_CCM_RX_WARNING(voe_idx), &v);
            UPDATE16(VTSS_X_VOP_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT(v),             &chipcnt->rx_lbr_trans_id_err[prio], clear);
        } else if (cfg->sat.cosid_seq_no_mode == VTSS_OAM_SAT_COSID_SEQ_NO_LB_TST) {
            CHIPREAD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx),                          &chipcnt->tx_ccm_lbm_tst[prio],      clear);
            CHIPREAD(VTSS_VOP_LBR_TX_FRM_CNT(voe_idx),                              &chipcnt->tx_lbr[prio],              clear);
            CHIPREAD(VTSS_VOP_LBR_RX_FRM_CNT(voe_idx),                              &chipcnt->rx_ccm_lbr_tst[prio],      clear);
            CHIPREAD(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx),                          &chipcnt->rx_lbr_trans_id[prio],     clear);
            CHIPREAD(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(voe_idx),                      &chipcnt->rx_lbr_trans_id_err[prio], clear);
        }
    }
    return VTSS_RC_OK;
#undef CHIPREAD
#undef UPDATE16
}


#if defined(VTSS_FEATURE_MPLS)
static vtss_rc oam_voe_counter_update_internal_mpls(vtss_state_t              *vtss_state,
                                                    const vtss_oam_voe_idx_t  voe_idx,
                                                    const u32                 clear_mask){
#define CHIPREAD(reg, cnt, clear) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, (clear_mask & (clear)) != 0); }

    vtss_rc rc = VTSS_RC_OK;
    u32 v;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    CHIPREAD(VTSS_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG(voe_idx), &chipcnt->bfd.rx_cc_valid, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG(voe_idx), &chipcnt->bfd.rx_cv_valid, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG(voe_idx), &chipcnt->bfd.rx_cc_invalid, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG(voe_idx), &chipcnt->bfd.rx_cv_invalid, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_BFD_CC_TX_CNT_REG(voe_idx), &chipcnt->bfd.tx_cc, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_BFD_CV_TX_CNT_REG(voe_idx), &chipcnt->bfd.tx_cv, VTSS_OAM_CNT_BFD);

    CHIPREAD(VTSS_VOP_MPLS_RX_CNT_SEL_OAM_MPLS(voe_idx), &chipcnt->bfd.rx_selected, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS(voe_idx), &chipcnt->bfd.rx_nonselected, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_TX_CNT_SEL_OAM_MPLS(voe_idx), &chipcnt->bfd.tx_selected, VTSS_OAM_CNT_BFD);
    CHIPREAD(VTSS_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS(voe_idx), &chipcnt->bfd.tx_nonselected, VTSS_OAM_CNT_BFD);

    return rc;
#undef CHIPREAD
}
#endif

static vtss_rc oam_voe_counter_update_internal(vtss_state_t              *vtss_state,
                                               const vtss_oam_voe_idx_t  voe_idx,
                                               const u32                 clear_mask)
{
/*
 * These macros will aid in reading and optionally clearing counter registers.
 * The clear operation will be triggered by matching the 'clear_mask' with both a
 * counter type (ctype) and a counter direction (cdir - TX or RX).
 */
#define CHIPREAD(reg, cnt, ctype, cdir) { REG_RD(reg, &v); vtss_cmn_counter_32_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE8(v, cnt, ctype, cdir)    { vtss_cmn_counter_8_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }
#define UPDATE16(v, cnt, ctype, cdir)   { vtss_cmn_counter_16_update(v, cnt, ((clear_mask & (ctype)) != 0) && ((clear_mask & (cdir)) != 0)); }

    vtss_rc rc = VTSS_RC_OK;
    u32 v, i, offset;
    BOOL doing_lb = 0, doing_tst = 0;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);

#if defined(VTSS_FEATURE_MPLS)
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_2)
        return oam_voe_counter_update_internal_mpls(vtss_state, voe_idx, clear_mask);
#endif

    if (cfg->sat.enable && cfg->sat.cosid_seq_no_mode != VTSS_OAM_SAT_COSID_SEQ_NO_DISABLED &&
        vtss_state->oam.sat_cosid_counters_allocated[cfg->sat.cosid_seq_no_idx]) {
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            rc = oam_sat_cosid_counters_update(vtss_state, voe_idx, cfg->sat.cosid_seq_no_idx, i, FALSE);
        }
    }

    /* SL:*/
    CHIPREAD(VTSS_VOP_SLM_TX_FRM_CNT(voe_idx), &chipcnt->sl.tx_slm, VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_TX);

    /* LM:*/
    REG_RD(VTSS_VOP_LM_PDU_CNT(voe_idx), &v);
    UPDATE8(VTSS_X_VOP_LM_PDU_CNT_LMM_TX_PDU_CNT(v), &chipcnt->lm.tx_lmm, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_TX);
    UPDATE8(VTSS_X_VOP_LM_PDU_CNT_LMM_RX_PDU_CNT(v), &chipcnt->lm.rx_lmm, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_RX);
    UPDATE8(VTSS_X_VOP_LM_PDU_CNT_LMR_TX_PDU_CNT(v), &chipcnt->lm.tx_lmr, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_TX);
    UPDATE8(VTSS_X_VOP_LM_PDU_CNT_LMR_RX_PDU_CNT(v), &chipcnt->lm.rx_lmr, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_RX);

    if (vtss_state->oam.voe_conf[voe_idx].sl.enable) {
        /* SL:*/
        switch (vtss_state->oam.voe_conf[voe_idx].voe_type) {
        case VTSS_OAM_VOE_SERVICE:
            offset = voe_idx * VTSS_PRIO_ARRAY_SIZE;
            for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
                switch (vtss_state->oam.voe_conf[voe_idx].mep_type) {
                    case VTSS_OAM_DOWNMEP:
                        CHIPREAD(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), &chipcnt->sl.rx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_RX);
                        CHIPREAD(VTSS_REW_SRV_LM_CNT_LSB(offset + i),            &chipcnt->sl.tx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_TX);
                        break;
                    case VTSS_OAM_UPMEP:
                        CHIPREAD(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), &chipcnt->sl.tx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_TX);
                        CHIPREAD(VTSS_REW_SRV_LM_CNT_LSB(offset + i),            &chipcnt->sl.rx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_RX);
                        break;
                }
            }
            break;
        case VTSS_OAM_VOE_PORT:
            offset = (voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE;
            for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
                CHIPREAD(VTSS_ANA_AC_OAM_MOD_PORT_LM_CNT_LSB(offset + i), &chipcnt->sl.rx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_RX);
                CHIPREAD(VTSS_REW_PORT_LM_CNT_LSB(offset + i),            &chipcnt->sl.tx_slr[i], VTSS_OAM_CNT_SL, VTSS_OAM_CNT_DIR_TX);
                /* TBD - the port count-all Rx/Tx counters have been left out */
            }
            break;
        }

    } else {
        /* LM: */
        switch (vtss_state->oam.voe_conf[voe_idx].voe_type) {
        case VTSS_OAM_VOE_SERVICE:
            offset = voe_idx * VTSS_PRIO_ARRAY_SIZE;
            for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
                switch (vtss_state->oam.voe_conf[voe_idx].mep_type) {
                case VTSS_OAM_DOWNMEP:
                    CHIPREAD(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), &chipcnt->lm.lm_count[i].rx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_RX);
                    CHIPREAD(VTSS_REW_SRV_LM_CNT_LSB(offset + i),            &chipcnt->lm.lm_count[i].tx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_TX);
                    break;
                case VTSS_OAM_UPMEP:
                    CHIPREAD(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), &chipcnt->lm.lm_count[i].tx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_TX);
                    CHIPREAD(VTSS_REW_SRV_LM_CNT_LSB(offset + i),            &chipcnt->lm.lm_count[i].rx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_RX);
                    break;
                }
            }
            break;
        case VTSS_OAM_VOE_PORT:
            offset = (voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE;
            for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
                CHIPREAD(VTSS_ANA_AC_OAM_MOD_PORT_LM_CNT_LSB(offset + i), &chipcnt->lm.lm_count[i].rx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_RX);
                CHIPREAD(VTSS_REW_PORT_LM_CNT_LSB(offset + i),            &chipcnt->lm.lm_count[i].tx, VTSS_OAM_CNT_LM, VTSS_OAM_CNT_DIR_TX);
                /* TBD - the port count-all Rx/Tx counters have been left out */
            }
            break;
        }
    }

    /* CCM: */

    REG_RD(VTSS_VOP_CCM_RX_FRM_CNT(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_CCM_RX_FRM_CNT_CCM_RX_VLD_FC_CNT(v),     &chipcnt->ccm.rx_valid_count,    VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    UPDATE16(VTSS_X_VOP_CCM_RX_FRM_CNT_CCM_RX_INVLD_FC_CNT(v),   &chipcnt->ccm.rx_invalid_count,  VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);

    REG_RD(VTSS_VOP_CCM_RX_WARNING(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_CCM_RX_WARNING_CCM_RX_SEQNO_ERR_CNT(v),  &chipcnt->ccm.rx_invalid_seq_no, VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);

    REG_RD(VTSS_VOP_CCM_ERR(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_CCM_ERR_CCM_RX_PERIOD_ERR_CNT(v),        &chipcnt->ccm.rx_invalid_period, VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    UPDATE16(VTSS_X_VOP_CCM_ERR_CCM_RX_MEL_ERR_CNT(v),           &chipcnt->ccm.rx_invalid_mel,    VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);

    REG_RD(VTSS_VOP_CCM_RX_ERR_1(voe_idx), &v);
    UPDATE16(VTSS_X_VOP_CCM_RX_ERR_1_CCM_RX_MEGID_ERR_CNT(v),    &chipcnt->ccm.rx_invalid_megid,  VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);
    UPDATE16(VTSS_X_VOP_CCM_RX_ERR_1_CCM_RX_MEPID_ERR_CNT(v),    &chipcnt->ccm.rx_invalid_mepid,  VTSS_OAM_CNT_CCM, VTSS_OAM_CNT_DIR_RX);

    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));

    /* LB: */

    if (doing_lb || (clear_mask & VTSS_OAM_CNT_LB)) {
        CHIPREAD(VTSS_VOP_LBR_RX_FRM_CNT(voe_idx),         &chipcnt->lb.rx_lbr,              VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx),     &chipcnt->lb.tx_lbm,              VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_TX);
        CHIPREAD(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(voe_idx), &chipcnt->lb.rx_lbr_trans_id_err, VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_LBR_CRC_ERR_CNT(voe_idx),        &chipcnt->lb.rx_lbr_crc_err,      VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_LBR_TX_FRM_CNT(voe_idx),         &chipcnt->lb.tx_lbr,              VTSS_OAM_CNT_LB, VTSS_OAM_CNT_DIR_TX);
    }

    /* TST: */

    if (doing_tst || (clear_mask & VTSS_OAM_CNT_TST)) {
        CHIPREAD(VTSS_VOP_LBR_RX_FRM_CNT(voe_idx),         &chipcnt->tst.rx_tst,              VTSS_OAM_CNT_TST, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx),     &chipcnt->tst.tx_tst,              VTSS_OAM_CNT_TST, VTSS_OAM_CNT_DIR_TX);
        CHIPREAD(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(voe_idx), &chipcnt->tst.rx_tst_trans_id_err, VTSS_OAM_CNT_TST, VTSS_OAM_CNT_DIR_RX);
        CHIPREAD(VTSS_VOP_LBR_CRC_ERR_CNT(voe_idx),        &chipcnt->tst.rx_tst_crc_err,      VTSS_OAM_CNT_TST, VTSS_OAM_CNT_DIR_RX);
    }

    /* DM:*/

    REG_RD(VTSS_VOP_DM_PDU_CNT(voe_idx), &v);
    UPDATE8(VTSS_X_VOP_DM_PDU_CNT_DMM_TX_PDU_CNT(v), &chipcnt->dm.tx_dmm, VTSS_OAM_CNT_DM, VTSS_OAM_CNT_DIR_TX);
    UPDATE8(VTSS_X_VOP_DM_PDU_CNT_DMM_RX_PDU_CNT(v), &chipcnt->dm.rx_dmm, VTSS_OAM_CNT_DM, VTSS_OAM_CNT_DIR_RX);
    UPDATE8(VTSS_X_VOP_DM_PDU_CNT_DMR_TX_PDU_CNT(v), &chipcnt->dm.tx_dmr, VTSS_OAM_CNT_DM, VTSS_OAM_CNT_DIR_TX);
    UPDATE8(VTSS_X_VOP_DM_PDU_CNT_DMR_RX_PDU_CNT(v), &chipcnt->dm.rx_dmr, VTSS_OAM_CNT_DM, VTSS_OAM_CNT_DIR_RX);

    /* Selected: */

    CHIPREAD(VTSS_VOP_RX_SEL_OAM_CNT(voe_idx), &chipcnt->sel.selected_frames.rx,    VTSS_OAM_CNT_SEL, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_VOP_TX_SEL_OAM_CNT(voe_idx), &chipcnt->sel.selected_frames.tx,    VTSS_OAM_CNT_SEL, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_VOP_RX_OAM_FRM_CNT(voe_idx), &chipcnt->sel.nonselected_frames.rx, VTSS_OAM_CNT_SEL, VTSS_OAM_CNT_DIR_RX);
    CHIPREAD(VTSS_VOP_TX_OAM_FRM_CNT(voe_idx), &chipcnt->sel.nonselected_frames.tx, VTSS_OAM_CNT_SEL, VTSS_OAM_CNT_DIR_TX);

    /* Discard: */
    CHIPREAD(VTSS_VOP_TX_OAM_DISCARD(voe_idx), &chipcnt->discard.tx, VTSS_OAM_CNT_DISCARD, VTSS_OAM_CNT_DIR_TX);
    CHIPREAD(VTSS_VOP_RX_OAM_DISCARD(voe_idx), &chipcnt->discard.rx, VTSS_OAM_CNT_DISCARD, VTSS_OAM_CNT_DIR_RX);

    return rc;
#undef CHIPREAD
#undef UPDATE8
#undef UPDATE16
}

static vtss_rc oam_vop_int_enable(vtss_state_t *vtss_state, u32 enable)
{
    REG_WRM(VTSS_VOP_MASTER_INTR_CTRL, B2B(enable, VTSS_M_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA), VTSS_M_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR_ENA);
    return VTSS_RC_OK;
}

/* Determine VOP interrupt flag -- clear if no enabled VOEs have
 * interrupts enabled */
static vtss_rc oam_vop_int_update(vtss_state_t *vtss_state)
{
    u32 i, v;
    u32 must_enable;
    for (i = 0, must_enable = 0; !must_enable && i < VTSS_OAM_VOE_CNT; ++i) {
        if (vtss_state->oam.voe_internal[i].allocated) {
            /* Check which kind of VOE we are running */
            REG_RD(VTSS_VOP_VOE_MISC_CONFIG(i), &v);
            if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 2) {
                REG_RD(VTSS_VOP_MPLS_INTR_ENA_MPLS(i), &must_enable);
            } else {
                REG_RD(VTSS_VOP_INTR_ENA(i), &must_enable);
            }
            must_enable &= 0x7ff;  /* Only bits 0-10 are valid */
        }
    }
    return oam_vop_int_enable(vtss_state, must_enable);
}

static vtss_rc mce_isdx_clear(vtss_state_t  *vtss_state,
                              u32           isdx)
{
    vtss_port_mask_t  pmask;

    /*** IPT Configuration ***/
    /* VOE reference */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA(0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA);

    /* VOE reference */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX(0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_MEP_IDX);

    /* MIP reference */
    REG_WRM(VTSS_ANA_CL_ISDX_CFG(isdx),
            VTSS_F_ANA_CL_ISDX_CFG_MIP_IDX(0),
            VTSS_M_ANA_CL_ISDX_CFG_MIP_IDX);

    /* Set independent_mel */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA);

    /* No L2CP IDX */
    REG_WRM(VTSS_ANA_CL_ISDX_CFG(isdx), VTSS_F_ANA_CL_ISDX_CFG_L2CP_IDX(0), VTSS_M_ANA_CL_ISDX_CFG_L2CP_IDX);

    /*** ISDX Configuration ***/
    /* Calculate ISDX port mask */
    vtss_port_mask_clear(&pmask);
    REG_WRX_PMASK(VTSS_ANA_L2_PORT_MASK_CFG, isdx, pmask);

    /* Use ISDX key in ES0 */
    REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA(1), VTSS_M_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA);

    /* Disable LAG */
    REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_AGGR_REPLACE_ENA(0), VTSS_M_ANA_L2_SERVICE_CTRL_AGGR_REPLACE_ENA);
    REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_AGGR_VAL(0), VTSS_M_ANA_L2_SERVICE_CTRL_AGGR_VAL);

    /* Change pipeline point */
    REG_WRM(VTSS_ANA_L2_MISC_CFG(isdx), VTSS_F_ANA_L2_MISC_CFG_PIPELINE_PT(0), VTSS_M_ANA_L2_MISC_CFG_PIPELINE_PT);

    /* Default is NO counting and NO policing */
    REG_WR(VTSS_ANA_L2_ISDX_BASE_CFG(isdx), VTSS_POL_STAT_NONE);
    REG_WR(VTSS_ANA_L2_DLB_CFG(isdx), VTSS_POL_STAT_NONE);

    return VTSS_RC_OK;
}

static vtss_rc mce_isdx_update(vtss_state_t      *vtss_state,
                               vtss_mce_entry_t  *mce,
                               vtss_evc_entry_t  *evc)
{
    vtss_sdx_entry_t         *sdx = mce->isdx_list;
    vtss_port_mask_t         pmask;
    u32                      isdx = sdx->sdx;
    vtss_mce_action_t        *action = &mce->conf.action;
    vtss_mce_key_t           *key = &mce->conf.key;

    VTSS_D("mce_id: %X  isdx %u", mce->conf.id, isdx);

    /*** IPT Configuration ***/
    /* VOE reference */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA(((action->voe_idx != VTSS_VOE_IDX_NONE) && (action->voe_idx < VTSS_OAM_PORT_VOE_BASE_IDX)) ? 1 : 0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA);

    /* VOE reference */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_MEP_IDX((action->voe_idx != VTSS_VOE_IDX_NONE) ? action->voe_idx : 0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_MEP_IDX);

    /* MIP reference */
    REG_WRM(VTSS_ANA_CL_ISDX_CFG(isdx),
            VTSS_F_ANA_CL_ISDX_CFG_MIP_IDX((action->mip_idx != VTSS_OAM_MIP_IDX_NONE) ? action->mip_idx : 0),
            VTSS_M_ANA_CL_ISDX_CFG_MIP_IDX);

    /* Set independent_mel */
    REG_WRM(VTSS_ANA_CL_OAM_MEP_CFG(isdx),
            VTSS_F_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(action->independent_mel ? 1 : 0),
            VTSS_M_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA);

    /* No L2CP IDX */
    REG_WRM(VTSS_ANA_CL_ISDX_CFG(isdx), VTSS_F_ANA_CL_ISDX_CFG_L2CP_IDX(0), VTSS_M_ANA_CL_ISDX_CFG_L2CP_IDX);

    /*** ISDX Configuration ***/
    /* Calculate ISDX port mask */
    vtss_port_mask_get(vtss_state, action->port_list, &pmask);
    REG_WRX_PMASK(VTSS_ANA_L2_PORT_MASK_CFG, isdx, pmask);

    if (((evc == NULL) && !key->service_detect) || (mce->conf.tt_loop && (mce->conf.rule == VTSS_MCE_RULE_RX) && (action->isdx == VTSS_MCE_ISDX_NEW))) {
        /* Use ISDX key in ES0 if not EVC related and not service related rule or a TT_LOOP RX rule generating ISDX */
        REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA(1), VTSS_M_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA);
    } else {
        /* Do not Use ISDX key in ES0 */
        REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA(0), VTSS_M_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA);
    }

    /* Disable LAG */
    REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_AGGR_REPLACE_ENA(0), VTSS_M_ANA_L2_SERVICE_CTRL_AGGR_REPLACE_ENA);
    REG_WRM(VTSS_ANA_L2_SERVICE_CTRL(isdx), VTSS_F_ANA_L2_SERVICE_CTRL_AGGR_VAL(action->lag_disable ? 1 : 0), VTSS_M_ANA_L2_SERVICE_CTRL_AGGR_VAL);

    /* Change pipeline point */
    u32 pipeline_pt = (key->second && key->masqueraded) ? 10 : 0;     /* This is considered SAT injection */
    REG_WRM(VTSS_ANA_L2_MISC_CFG(isdx), VTSS_F_ANA_L2_MISC_CFG_PIPELINE_PT(pipeline_pt), VTSS_M_ANA_L2_MISC_CFG_PIPELINE_PT);

    /* In case of EVC related rule counting and policing might happen */
#if defined(VTSS_FEATURE_EVC)
    if (evc != NULL) { /* EVC related rule */
        if (action->evc_counting) { /* Do EVC counting */
            VTSS_RC(vtss_fa_evc_counting_update(vtss_state, evc, sdx));
        }

        if (action->evc_policing) { /* Do EVC policing */
            VTSS_RC(vtss_fa_evc_policing_update(vtss_state, evc, sdx));
        }
    }
#endif /* VTSS_FEATURE_EVC */
    VTSS_RC(vtss_fa_isdx_update(vtss_state, sdx));

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_EVC)
static vtss_mce_entry_t *find_rx_subscriber_rule(vtss_state_t      *vtss_state,
                                                 vtss_mce_entry_t  *mce,
                                                 vtss_port_no_t    uni_port)
{
    vtss_mce_info_t         *mce_info = &vtss_state->oam.mce_info;
    vtss_mce_entry_t        *cur = NULL;
    const vtss_mce_key_t    *key = &mce->conf.key;
    const vtss_mce_action_t *action = &mce->conf.action;

    VTSS_D("Enter  mce_id: %X  UNI port: %u  EVC id: %u", mce->conf.id, uni_port, action->evc_id);

    /* Find any TT_LOOP RX subscriber rule */
    for (cur = mce_info->used; cur != NULL; cur = cur->next) {  /* Look through all MCE rules */
        if (cur->conf.tt_loop && (cur->conf.rule == VTSS_MCE_RULE_RX) && (cur->conf.action.evc_id == action->evc_id) &&
            (cur->conf.key.isdx == key->isdx) && ((cur->conf.key.first_tag.vid.value == key->first_tag.vid.value) || (cur->conf.key.first_tag.vid.mask == 0)) && 
            (cur->conf.key.port_list[uni_port])) {   /* Found a RX rule */
            VTSS_D("found mce_id: %X", cur->conf.id);
            return cur;
        }
    }
    VTSS_D("exit");

    return NULL;
}

static void oam_mce_rx_pag_update(vtss_state_t      *vtss_state,
                                  vtss_mce_entry_t  *mce,
                                  vtss_evc_entry_t  *evc)
{
    vtss_mce_info_t         *mce_info = &vtss_state->oam.mce_info;
    vtss_mce_entry_t        *cur = NULL;
    const vtss_mce_key_t    *key = &mce->conf.key;
    const vtss_mce_action_t *action = &mce->conf.action;

    VTSS_D("Enter  mce_id: %X  EVC id: %u", mce->conf.id, action->evc_id);

    for (cur = mce_info->used; cur != NULL; cur = cur->next) {  /* Look through all MCE rules */
        if (!cur->conf.tt_loop && (cur->conf.rule == VTSS_MCE_RULE_RX) && (cur->conf.action.evc_id == action->evc_id) &&
            (cur->conf.key.isdx == key->isdx) && ((cur->conf.key.first_tag.vid.value == key->first_tag.vid.value) || (key->first_tag.vid.mask == 0))) {   /* Found a RX rule */
            for (vtss_port_no_t port_no = 0; vtss_state->port_count; port_no++) {
                if (key->port_list[port_no] && cur->conf.key.port_list[port_no]) {   /* Egress port found */
                    (void)mce_clm_add(vtss_state, cur, evc, port_no);   /* update CLM */
                    break;
                }
            }
        }
    }
    VTSS_D("Exit");

}
#endif

static vtss_rc mce_clm_add(vtss_state_t      *vtss_state,
                           vtss_mce_entry_t  *mce,
                           vtss_evc_entry_t  *evc,
                           vtss_port_no_t    uni_port)
{
    vtss_rc              rc = VTSS_RC_OK;
    vtss_vcap_data_t     data;
    vtss_is1_data_t      *is1 = &data.u.is1;
    vtss_is1_entry_t     entry;
    vtss_is1_action_t    *action = &entry.action;
    vtss_is1_key_t       *key = &entry.key;
    vtss_mce_t           *conf = &mce->conf;
    vtss_mce_entry_t     *cur;
    vtss_oam_detect_t    oam_detect;
#if defined(VTSS_FEATURE_EVC)
    vtss_port_no_t       port_no;
#endif /* VTSS_FEATURE_EVC */
    vtss_vcap_obj_t      *clm_obj = &vtss_state->vcap.clm_c.obj;

    VTSS_D("mce_id: %X", mce->conf.id);

    vtss_vcap_is1_init(&data, &entry);
    key->type = !conf->key.service_detect ? VTSS_IS1_TYPE_ETYPE : VTSS_IS1_TYPE_ANY;

    clm_obj = &vtss_state->vcap.clm_c.obj;  // CLM C as default
    key->key_type = VTSS_VCAP_KEY_TYPE_DOUBLE_TAG;  /* Default is a X2 entry */
    /* Check if key requires X8 entry */
    if (require_normal_key(conf)) { /* Check for NORMAL key required */
        key->key_type = VTSS_VCAP_KEY_TYPE_NORMAL;     /* This will give key size X8 */
        if (((evc == NULL) && !conf->key.looped) || (conf->key.opcode != VTSS_OAM_OPCODE_NONE)) {  /* In EVC domain it is expected that first lookup generates X16 key as next key type. If it is not EVC domain then this entry must go in first lookup in CLM B. A frame coming from loop interface has normal key lookup */
            conf->key.second = FALSE;
            clm_obj = &vtss_state->vcap.clm_b.obj;  // CLM C as default
        }
    }
#if defined(VTSS_FEATURE_EVC)
    if (!conf->key.second && (clm_obj == &vtss_state->vcap.clm_c.obj)) {
        // First lookup in CLM C is EVC lookup - use EVC configured key type
        port_no = vtss_cmn_first_port_no_get(vtss_state, conf->key.port_list);   /* All ports in list must of same key type */
        if (port_no != VTSS_PORT_NO_NONE) {
            vtss_evc_port_conf_t *port_conf = &vtss_state->evc.port_conf[port_no];
            key->key_type = port_conf->key_type;
        }
    }
#endif
    data.key_size = vtss_vcap_key_type2size(key->key_type);

    memcpy(key->port_list, conf->key.port_list, sizeof(key->port_list));

    mce2is1_tag(&conf->key.first_tag, &key->tag);
    mce2is1_tag(&conf->key.second_tag, &key->inner_tag);

    if ((conf->key.looped) && (conf->key.isdx != VTSS_MCE_ISDX_NONE)) {
        // TODO: Why is key ISDX assignment limited to looped scenarios?
        // If the user bothers to specify a key ISDX then one would assume that he means to use it.
        // Answer: Because only frames coming from the loop interface has ISDX in the G_IDX value
        key->g_idx.value = conf->key.isdx;
        key->g_idx.mask = 0xFFF;
    }

    if (!conf->key.service_detect) {    /* Only have OAM detection in key if not service detection required */
        /* ETYPE field encoding */
        key->frame.etype.etype.value[0] = 0x89;
        key->frame.etype.etype.mask[0] = 0xff;
        key->frame.etype.etype.value[1] = 0x02;
        key->frame.etype.etype.mask[1] = 0xff;

        key->frame.etype.mel = conf->key.mel;
        key->masqueraded = conf->key.masqueraded;

        if (conf->key.opcode != VTSS_OAM_OPCODE_NONE) {
            key->frame.etype.data.value[1] = conf->key.opcode;
            key->frame.etype.data.mask[1] = 0xFF;
        }
    }

    key->looped = conf->key.looped;     // match on frames from looped port
    key->port_hit = (conf->action.forward_sel == VTSS_MCE_FORWARD_DISABLE) ? TRUE : FALSE;  /* Forward disable implies that it is only frames on port */

    /* MAC header matching */
    key->mac.dmac = conf->key.dmac;
    key->mac.dmac_mc = conf->key.dmac_mc;
    key->mac.smac = conf->key.smac;

    if (conf->action.pop_cnt < VTSS_MCE_POP_NONE) { /* pop count */
        action->pop_enable = TRUE;
        action->pop = conf->action.pop_cnt;
    }
    if (conf->action.vid != VTSS_MCE_VID_NONE) {
        action->vid_enable = TRUE;
        action->vid = conf->action.vid;
    } else if (evc != NULL && !conf->key.second) {
#if defined(VTSS_FEATURE_EVC)
        /* EVC related rule in first lookup. Must get EVC IVID as classified VID */
        action->vid_enable = TRUE;
        action->vid = evc->ivid;
#endif /* VTSS_FEATURE_EVC */
    }

    if ((conf->action.isdx != VTSS_MCE_ISDX_NONE) && (mce->isdx_list != NULL)) {
        action->isdx_enable = TRUE;
        action->isdx = mce->isdx_list->sdx;
    }

    oam_detect = VTSS_OAM_DETECT_NONE;
    switch (conf->action.oam_detect) {
    case VTSS_MCE_OAM_DETECT_NONE:
        oam_detect = VTSS_OAM_DETECT_NONE;
        break;
    case VTSS_MCE_OAM_DETECT_UNTAGGED:
        oam_detect = VTSS_OAM_DETECT_UNTAGGED;
        break;
    case VTSS_MCE_OAM_DETECT_SINGLE_TAGGED:
        oam_detect = VTSS_OAM_DETECT_SINGLE_TAGGED;
        break;
    case VTSS_MCE_OAM_DETECT_DOUBLE_TAGGED:
        oam_detect = VTSS_OAM_DETECT_DOUBLE_TAGGED;
        break;
    case VTSS_MCE_OAM_DETECT_TRIPLE_TAGGED:
        oam_detect = VTSS_OAM_DETECT_TRIPLE_TAGGED;
        break;
    }
    if (conf->action.policy_no == VTSS_ACL_POLICY_NO_NONE) {
        action->pag_enable = 0;
        action->pag = 0;
    } else {
        action->pag_enable = 1;
        action->pag = conf->action.policy_no;
    }
#if defined(VTSS_FEATURE_EVC)
    if (!conf->tt_loop && (conf->action.evc_id != VTSS_EVC_ID_NONE) && (conf->key.isdx == VTSS_MCE_ISDX_NONE) && (uni_port < vtss_state->port_count)) { /* A OAM EVC RX rule UNI must generate possible TT_LOOP PAG */
        vtss_mce_entry_t *tt_mce;
        if ((tt_mce = find_rx_subscriber_rule(vtss_state, mce, uni_port)) != NULL) {
            action->pag_enable = 1;
            action->pag = tt_mce->conf.action.policy_no;
        }
    }
#endif
    action->oam_detect = oam_detect;
    action->mip_enable = (conf->action.mip_idx != VTSS_OAM_MIP_IDX_NONE) ? TRUE : FALSE;
#if defined(VTSS_FEATURE_MCE_ACT_PRIO)
    action->prio_enable = conf->action.prio_enable;
    action->prio = conf->action.prio;
#endif
    switch (conf->action.pipeline) {
    case VTSS_MCE_PIPELINE_NONE:
    case VTSS_MCE_PIPELINE_EXT_SAT: {    /* None. Extraction in SAT is not CLM action relevant - this is ES0 action */
        break;
    }
    case VTSS_MCE_PIPELINE_INJ_OU_VOE: {    /* Masqueraded injection in outer VOE */
        action->pipe_enable = CLM_PL_ENA_INJ;
        action->pipe_sel = CLM_PL_SEL_INJ_MASQ;
        action->pipe_pt = CLM_PL_PT_ANA_OU_VOE;
        break;
    }
    case VTSS_MCE_PIPELINE_INJ_IN_VOE: {    /* Masqueraded injection in inner VOE */
        action->pipe_enable = CLM_PL_ENA_INJ;
        action->pipe_sel = CLM_PL_SEL_INJ_MASQ;
        action->pipe_pt = CLM_PL_PT_ANA_IN_VOE;
        break;
    }
    case VTSS_MCE_PIPELINE_EXT_OU_SW: {    /* Extraction in outer SW */
        action->pipe_enable = CLM_PL_ENA_XTR;
        action->pipe_pt = CLM_PL_PT_ANA_OU_SW;
        break;
    }
    case VTSS_MCE_PIPELINE_EXT_IN_SW: {    /* Extraction in inner SW */
        action->pipe_enable = CLM_PL_ENA_XTR;
        action->pipe_pt = CLM_PL_PT_ANA_IN_SW;
        break;
    }
    }

    action->match_id = conf->action.match_id;
    action->fwd_disable = (conf->action.forward_sel == VTSS_MCE_FORWARD_DISABLE) ? TRUE : FALSE;

    is1->lookup = conf->key.second;
#if defined(VTSS_FEATURE_EVC)
    if (evc != NULL) { /* EVC related rule */
        vtss_evc_port_role_t role;

        port_no = vtss_cmn_first_port_no_get(vtss_state, key->port_list);   /* All ports in list must of same type - NNI or UNI */
        if (port_no >= vtss_state->port_count) {
            VTSS_E("No port in key->port_list");
            return VTSS_RC_ERROR;
        }
        role = vtss_state->evc.port_info_table[evc->port_idx[port_no]].conf.role;
        if (role == VTSS_EVC_PORT_ROLE_DISABLED) {
            VTSS_E("The port is not active in the EVC  port_no %u", port_no);
            return VTSS_RC_ERROR;
        }
        if ((((conf->action.evc_cos) && (role == VTSS_EVC_PORT_ROLE_NNI)) || ((evc != NULL) && !conf->key.second)) &&
            (evc->rx_map < VTSS_QOS_INGRESS_MAP_IDS)) {   /* EVC COS mapping is wanted but is only supported on NNI. This will not work for subscriber OAM where COS mapping is inherited from previous lookup */
            is1->map_id = evc->rx_map;
            is1->flags = (VTSS_IS1_FLAG_MAP_ID | ((conf->key.second_tag.tagged == VTSS_VCAP_BIT_1) ? VTSS_IS1_FLAG_MAP_INNER : 0));
        }
    }
#endif /* VTSS_FEATURE_EVC */

    /* Find next ID for same VCAP user */
    for (cur = mce->next; cur != NULL; cur = cur->next) {
        if ((cur->conf.rule == VTSS_MCE_RULE_RX) && (cur->conf.order == conf->order)) {     /* Each order is a VCAP user */
            break;
        }
    }
    if ((rc = vtss_vcap_add(vtss_state, clm_obj, order_to_clm_user(conf->order), conf->id, ((cur == NULL) ? VTSS_VCAP_ID_LAST : cur->conf.id), &data, FALSE)) != VTSS_RC_OK) {
        VTSS_E("vtss_vcap_add failed  rc %u", rc);
    }

    VTSS_D("Exit");

    return rc;
}

#if defined(VTSS_FEATURE_EVC)
static vtss_mce_entry_t *find_tx_subscriber_rule(vtss_state_t      *vtss_state,
                                                 vtss_mce_entry_t  *mce,
                                                 vtss_port_no_t    uni_port)
{
    vtss_mce_info_t         *mce_info = &vtss_state->oam.mce_info;
    vtss_mce_entry_t        *cur = NULL;
    const vtss_mce_key_t    *key = &mce->conf.key;
    const vtss_mce_action_t *action = &mce->conf.action;

    VTSS_D("Enter  mce_id: %X  UNI port: %u  EVC id: %u", mce->conf.id, uni_port, action->evc_id);

    /* In case of any other TX rule it must point to the VOE/MIP as OAM frames on NNI is hijacked by TT_LOOP RX rules */
    for (cur = mce_info->used; cur != NULL; cur = cur->next) {  /* Look through all MCE rules */
        if ((mce->conf.tt_loop != cur->conf.tt_loop) && (cur->conf.rule == VTSS_MCE_RULE_TX) && (cur->conf.action.evc_id == action->evc_id) &&
            (cur->conf.key.vid == key->vid) && (cur->conf.action.pipeline == action->pipeline) && (cur->conf.action.port_list[uni_port])) {   /* Found a TX rule */
            return cur;
        }
    }
    VTSS_D("Exit");

    return NULL;
}
#endif

static vtss_rc mce_es0_add(vtss_state_t      *vtss_state,
                           vtss_mce_entry_t  *mce,
                           vtss_evc_entry_t  *evc,
                           vtss_mce_action_t *old_action,
                           vtss_port_no_t    uni_port)
{
    vtss_rc                 rc = VTSS_RC_OK;
    const vtss_mce_key_t    *key = &mce->conf.key;
    const vtss_mce_action_t *action = &mce->conf.action;
    vtss_es0_entry_t        es0_entry;
    vtss_es0_key_t          *es0_key = &es0_entry.key;
    vtss_es0_action_t       *es0_action = &es0_entry.action;
    vtss_vcap_obj_t         *es0_obj = &vtss_state->vcap.es0.obj;
    vtss_port_no_t          port_no;
    vtss_vcap_data_t        data;
    vtss_vcap_id_t          id, id_next;

    /* Find next ID for first ES0 entry */
    id_next = VTSS_VCAP_ID_LAST;

    /* Add/delete ES0 entries, start from last port to avoid VCAP move operations */
    for (port_no = (vtss_state->port_count - 1); ; port_no--) {
        id = mce_vcap_id(mce->conf.id, port_no);

        if (action->port_list[port_no]) {   /* Egress port found */
            vtss_vcap_es0_init(&data, &es0_entry);
            es0_key->port_no = port_no;
            if (mce->isdx_list != NULL) {    /* ISDX must be key */
                es0_key->type = VTSS_ES0_TYPE_ISDX;
                es0_key->data.isdx.isdx_enable = TRUE;
                es0_key->data.isdx.isdx        = mce->isdx_list->sdx;
            } else if (mce->conf.tt_loop && mce->isdx_list == NULL) {
                es0_key->type                  = VTSS_ES0_TYPE_VID;
                es0_key->data.vid.vid          = VTSS_VID_ALL;
            } else if ((key->vid < VTSS_VIDS) || (key->vid == VTSS_VID_ALL)) {    /* This is a VID rule */
                es0_key->type                  = VTSS_ES0_TYPE_VID;
                es0_key->data.vid.vid          = key->vid;
            }

#if defined(VTSS_FEATURE_EVC)
            if ((evc != NULL) && (action->forward_sel != VTSS_MCE_FORWARD_LOOP)) {  /* This is a EVC TX rule that is not on the loop interface, configure the EVC related actions */
                if ((rc = vtss_fa_evc_es0_action(vtss_state, evc, port_no, &data, action->evc_leaf)) != VTSS_RC_OK) {  /* Do the EVC ES0 action configuration first */
                    VTSS_D("vtss_jr2_evc_es0_action failed  rc %u", rc);
                    return rc;
                }
            } else
#endif /* VTSS_FEATURE_EVC */
            {    /* This is NOT EVC - port tagging must be done (unless tt_loop) */
                if (mce->conf.tt_loop) {
                    es0_action->outer_tag.tag = VTSS_ES0_TAG_NONE;
                } else {
                    es0_action->outer_tag.tag = VTSS_ES0_TAG_PORT;
                }
            }
            if (!action->evc_counting) {    /* Should not count as EVC */
                es0_action->esdx = VTSS_POL_STAT_NONE;
            }
            es0_action->mep_idx_enable = FALSE;
            if (action->voe_idx != VTSS_VOE_IDX_NONE) {     /* Enable hitting VOE */
                es0_action->mep_idx_enable = TRUE;
                es0_action->mep_idx = action->voe_idx;
            }
            es0_action->mip_idx = 0;
            if (action->mip_idx != VTSS_OAM_MIP_IDX_NONE) {     /* Enable hitting MIP */
                es0_action->mip_idx = action->mip_idx;
            }
            es0_action->independent_mel = action->independent_mel;
#if defined(VTSS_FEATURE_EVC)
            if (mce->conf.tt_loop && (action->evc_id != VTSS_EVC_ID_NONE) && (action->pipeline == VTSS_MCE_PIPELINE_EXT_SAT) && (uni_port < vtss_state->port_count)) { /* Create of a TT-LOOP Subscriber TX rule on UNI. */
                /* When creating this rule it might be that it must point to a Subscriber Up MEP/MIP instance in the same flow */
                vtss_mce_entry_t *oam_mce = find_tx_subscriber_rule(vtss_state, mce, uni_port);
                if (oam_mce != NULL) {
                    if ((action->voe_idx == VTSS_VOE_IDX_NONE) && (oam_mce->conf.action.voe_idx != VTSS_VOE_IDX_NONE)) {
                        es0_action->mep_idx_enable = TRUE;
                        es0_action->mep_idx = oam_mce->conf.action.voe_idx;
                    }
                    if ((action->mip_idx == VTSS_OAM_MIP_IDX_NONE) && (oam_mce->conf.action.mip_idx != VTSS_OAM_MIP_IDX_NONE)) {
                        es0_action->mip_idx = oam_mce->conf.action.mip_idx;
                    }
                }
            }
#endif
            switch (action->pipeline) {
            case VTSS_MCE_PIPELINE_NONE:
            case VTSS_MCE_PIPELINE_INJ_OU_VOE:  /* Not possible */
            case VTSS_MCE_PIPELINE_INJ_IN_VOE: { /* Not possible */
                es0_action->pipe_pt = 0;
                break;
            }
            case VTSS_MCE_PIPELINE_EXT_SAT: {   /* Extraction in SAT */
                es0_action->pipe_pt = 2;
                break;
            }
            case VTSS_MCE_PIPELINE_EXT_OU_SW: { /* Extract in Outer SW */
                es0_action->pipe_pt = 1;
                break;
            }
            case VTSS_MCE_PIPELINE_EXT_IN_SW: { /* Extract in Inner SW */
                es0_action->pipe_pt = 0;
                break;
            }
            }

            switch (action->forward_sel) {
            case VTSS_MCE_FORWARD_NONE: {   /* No forward selection */
                es0_action->forward_sel = 0;
                break;
            }
            case VTSS_MCE_FORWARD_DISABLE: {  /* Disable forwarding */
                es0_action->forward_sel = 3;
                break;
            }
            case VTSS_MCE_FORWARD_EXTRACT: { /* Extract to CPU */
                es0_action->forward_sel = 2;
                es0_action->pipe_act = 0;
                es0_action->cpu_queue = vtss_state->oam.vop_conf.pdu_type.ccm.rx_queue;
                break;
            }
            case VTSS_MCE_FORWARD_LOOP: { /* MAC swapping loop */
                es0_action->forward_sel = 2;
                es0_action->pipe_act = 1;
                es0_action->mac_swap_enable = TRUE;
                break;
            }
            }

            if ((rc = vtss_vcap_add(vtss_state, es0_obj, order_to_es0_user(mce->conf.order), id, id_next, &data, 0)) != VTSS_RC_OK) {
                VTSS_D("vtss_vcap_add failed  rc %u", rc);
                return rc;
            }
        } else if ((old_action != NULL) && old_action->port_list[port_no]) {
            if ((rc = vtss_vcap_del(vtss_state, es0_obj, order_to_es0_user(mce->conf.order), id)) != VTSS_RC_OK) {
                VTSS_D("vtss_vcap_del failed  rc %u", rc);
                return rc;
            }
        }
        if (port_no == VTSS_PORT_NO_START) {
            break;
        }
    }
    return VTSS_RC_OK;
}

/*************************************/
/****** CIL interface functions ******/
/*************************************/

static vtss_rc fa_oam_vop_cfg_set(vtss_state_t *vtss_state)
{
    u32 i;
    u32 v;

    VTSS_D("Enter");

    const vtss_oam_vop_conf_t *cfg = &vtss_state->oam.vop_conf;
    v = (VTSS_F_VOP_CPU_EXTR_CFG_DEF_COPY_QU(cfg->pdu_type.other.rx_queue)  |
         VTSS_F_VOP_CPU_EXTR_CFG_CPU_ERR_QU(cfg->pdu_type.err.rx_queue)     |
         VTSS_F_VOP_CPU_EXTR_CFG_LMM_CPU_QU(cfg->pdu_type.lmm_slm.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_LMR_CPU_QU(cfg->pdu_type.lmr_slr.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_DMM_CPU_QU(cfg->pdu_type.dmm.rx_queue)     |
         VTSS_F_VOP_CPU_EXTR_CFG_DMR_CPU_QU(cfg->pdu_type.dmr.rx_queue));
    REG_WR(VTSS_VOP_CPU_EXTR_CFG, v);

    v = (VTSS_F_VOP_CPU_EXTR_CFG_1_CCM_CPU_QU(cfg->pdu_type.ccm.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_1_CCM_LM_CPU_QU(cfg->pdu_type.ccm_lm.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_1_LBM_CPU_QU(cfg->pdu_type.lbm.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_1_LBR_CPU_QU(cfg->pdu_type.lbr.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_1_TST_CPU_QU(cfg->pdu_type.tst.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_1_LT_CPU_QU(cfg->pdu_type.lt.rx_queue));
    REG_WR(VTSS_VOP_CPU_EXTR_CFG_1, v);

    v = (VTSS_F_VOP_CPU_EXTR_CFG_2_AIS_CPU_QU(cfg->pdu_type.ais.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_2_LCK_CPU_QU(cfg->pdu_type.lck.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_CFG_2_CSF_CPU_QU(cfg->pdu_type.csf.rx_queue));
    REG_WR(VTSS_VOP_CPU_EXTR_CFG_2, v);

    v = (VTSS_F_VOP_CPU_EXTR_MPLS_BFD_CC_CPU_QU(cfg->pdu_type.bfd_cc.rx_queue) |
         VTSS_F_VOP_CPU_EXTR_MPLS_BFD_CV_CPU_QU(cfg->pdu_type.bfd_cv.rx_queue));
    REG_WR(VTSS_VOP_CPU_EXTR_MPLS, v);

    for (i = 0; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i) {
        const vtss_oam_vop_generic_opcode_conf_t *g = &(cfg->pdu_type.generic[i]);
        v = VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_CPU_QU(g->extract.rx_queue) |
            VTSS_F_VOP_OAM_GENERIC_CFG_GENERIC_OPCODE_VAL(g->opcode) |
            B2B(!g->check_dmac, VTSS_M_VOP_OAM_GENERIC_CFG_GENERIC_DMAC_CHK_DIS);
        REG_WR(VTSS_VOP_OAM_GENERIC_CFG(i), v);
    }
    for (i = 0; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i) {
        const vtss_oam_vop_generic_opcode_conf_t *g = &(cfg->pdu_type.mpls_generic[i]);
        v = VTSS_F_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_CPU_QU(g->extract.rx_queue) |
            VTSS_F_VOP_MPLS_GENERIC_CODEPOINT_GENERIC_CODEPOINT_VAL(g->opcode);
        REG_WR(VTSS_VOP_MPLS_GENERIC_CODEPOINT(i), v);
    }

    v = (cfg->common_multicast_dmac.addr[0] << 8) | cfg->common_multicast_dmac.addr[1];
    REG_WR(VTSS_VOP_COMMON_MEP_MC_MAC_MSB, VTSS_F_VOP_COMMON_MEP_MC_MAC_MSB_MEP_MC_MAC_MSB(v));

    v = (cfg->common_multicast_dmac.addr[2] << 24) |
        (cfg->common_multicast_dmac.addr[3] << 16) |
        (cfg->common_multicast_dmac.addr[4] <<  8) |
        (cfg->common_multicast_dmac.addr[5]);
    v >>= 4;   /* Value in reg. field doesn't include the lower 4 bits */
    REG_WR(VTSS_VOP_COMMON_MEP_MC_MAC_LSB, VTSS_F_VOP_COMMON_MEP_MC_MAC_LSB_MEP_MC_MAC_LSB(v));

    REG_RD(VTSS_VOP_VOP_CTRL, &v);
    v = (v & ~(VTSS_M_VOP_VOP_CTRL_CCM_LM_UPD_RSV_ENA        |
               VTSS_M_VOP_VOP_CTRL_LMR_UPD_RXFCL_ENA         |
               VTSS_M_VOP_VOP_CTRL_VOP_ENA                   |
#if defined(VTSS_ARCH_FA_CE)
               VTSS_M_VOP_VOP_CTRL_G_8113_1_MEL_CHK_DIS      |
               VTSS_M_VOP_VOP_CTRL_G_8113_1_LBK_INDC_CHK_ENA |
#endif
               VTSS_M_VOP_VOP_CTRL_LOC_SCAN_ENA)) |
        (B2B(cfg->ccm_lm_enable_rx_fcf_in_reserved_field, VTSS_F_VOP_VOP_CTRL_CCM_LM_UPD_RSV_ENA(1))     |
         B2B(cfg->lmr_proprietary_fcf_use,                VTSS_F_VOP_VOP_CTRL_LMR_UPD_RXFCL_ENA(1))      |
         B2B(cfg->enable_all_voe,                         VTSS_F_VOP_VOP_CTRL_VOP_ENA(1))                |
#if defined(VTSS_ARCH_FA_CE)
         B2B(cfg->disable_g8113_1_mel_check,              VTSS_M_VOP_VOP_CTRL_G_8113_1_MEL_CHK_DIS)      |
         B2B(cfg->enable_g8113_1_lbk_indc_check,          VTSS_M_VOP_VOP_CTRL_G_8113_1_LBK_INDC_CHK_ENA) |
#endif
         VTSS_F_VOP_VOP_CTRL_LOC_SCAN_ENA(1));
    REG_WR(VTSS_VOP_VOP_CTRL, v);

    /* We don't touch the interrupt enable bit here; it defaults to disabled,
     * so we leave it to VOE interrupt configuration to modify it.
     */

    /* Below: Always using all 8 HMO slots and HMO scan is initiated at half the configured time... So divide by 8 and multiply by 2. */
    REG_WR(VTSS_VOP_HMO_PERIOD_CFG(0), (((u64)cfg->auto_copy_period[0]) * 1000) / LOC_BASE / (8 / 2));
    REG_WR(VTSS_VOP_HMO_PERIOD_CFG(1), (((u64)cfg->auto_copy_period[1]) * 1000) / LOC_BASE / (8 / 2));

    REG_WR(VTSS_VOP_HMO_TIMER_CFG, (VTSS_F_VOP_HMO_TIMER_CFG_HMO_RX_CCM_NXT_TIMER(cfg->auto_copy_next_valid_ccm & 1)              |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_CCM_RX_TLV_NON_ZERO_TIMER(cfg->auto_copy_on_ccm_tlv_nonzero & 1) |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_CCM_RX_BAD_NXT_TIMER(cfg->auto_copy_on_ccm_err & 1)              |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_RX_TEST_FRM_NXT_TIMER(cfg->auto_copy_next_tst_or_lbr & 1)        |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_EXTRACT_PEER_RX_TIMER(cfg->auto_copy_next_sl_peer & 1)           |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_AIS_RX_FRM_NXT_TIMER(cfg->auto_copy_next_valid_ais & 1)          |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_AIS_RX_BAD_NXT_TIMER(cfg->auto_copy_on_ais_err & 1)              |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_LCK_RX_FRM_NXT_TIMER(cfg->auto_copy_next_valid_lck & 1)          |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_LCK_RX_BAD_NXT_TIMER(cfg->auto_copy_on_lck_err & 1)              |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_CSF_RX_FRM_NXT_TIMER(cfg->auto_copy_next_valid_csf & 1)          |
                                    VTSS_F_VOP_HMO_TIMER_CFG_HMO_CSF_RX_BAD_NXT_TIMER(cfg->auto_copy_on_csf_err & 1)));
    REG_WR(VTSS_ANA_CL_MIP_CTRL, (VTSS_F_ANA_CL_MIP_CTRL_MIP_CCM_INTERVAL_MASK(cfg->mip_ccm_copy_next_mask & 0xf) |
                                  B2B(cfg->mip_ccm_copy_next_to_cpu, VTSS_M_ANA_CL_MIP_CTRL_MIP_CCM_HMO_SET_SHOT)));
    REG_WR(VTSS_REW_MIP_CTRL, (VTSS_F_REW_MIP_CTRL_MIP_CCM_INTERVAL_MASK(cfg->mip_ccm_copy_next_mask & 0xf) |
                               B2B(cfg->mip_ccm_copy_next_to_cpu, VTSS_M_REW_MIP_CTRL_MIP_CCM_HMO_SET_SHOT)));

    return VTSS_RC_OK;
}


static u32 voe_alloc_ix;
static vtss_rc fa_oam_voe_alloc(vtss_state_t *vtss_state,
                                const vtss_oam_voe_type_t      type,
                                const vtss_oam_voe_alloc_cfg_t *data,
                                vtss_oam_voe_idx_t             *voe_idx)
{
    u32 i, offset, v;

    VTSS_D("Enter");

    if (type == VTSS_OAM_VOE_SERVICE) {
        for (i = 0; i < VTSS_OAM_PATH_SERVICE_VOE_CNT && vtss_state->oam.voe_internal[voe_alloc_ix].allocated; ++i) {
            voe_alloc_ix = (voe_alloc_ix + 1) % VTSS_OAM_PATH_SERVICE_VOE_CNT;
        }
        if (i == VTSS_OAM_PATH_SERVICE_VOE_CNT) {
            return VTSS_RC_ERROR;
        }
        i = voe_alloc_ix;
        vtss_state->oam.voe_conf[i].voe_type = VTSS_OAM_VOE_SERVICE;
    } else {
        i = VTSS_CHIP_PORT(data->phys_port) + VTSS_OAM_PORT_VOE_BASE_IDX;
        if (i >= VTSS_OAM_VOE_CNT  ||  vtss_state->oam.voe_internal[i].allocated) {
            return VTSS_RC_ERROR;
        }
        vtss_state->oam.voe_conf[i].voe_type = VTSS_OAM_VOE_PORT;
    }

    *voe_idx = i;
    vtss_state->oam.voe_internal[i].allocated = TRUE;

    /* Clear assorted counters: */
    REG_WR(VTSS_VOP_RX_SEL_OAM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_RX_OAM_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_TX_SEL_OAM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_TX_OAM_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_TX_SEQ_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_SEQ_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_WARNING(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_ERR(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_ERR_1(*voe_idx), 0);
    REG_WR(VTSS_VOP_LBM_TX_TRANSID_CFG(*voe_idx), 1);
    REG_WR(VTSS_VOP_LBR_TX_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_LBR_RX_TRANSID_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_LBR_RX_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_DM_PDU_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_LM_PDU_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_TX_OAM_DISCARD(*voe_idx), 0);
    REG_WR(VTSS_VOP_RX_OAM_DISCARD(*voe_idx), 0);
    REG_WR(VTSS_VOP_PDU_EXTRACT(*voe_idx), VTSS_M_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE);   /* Hit Me Once is default */
    REG_WR(VTSS_VOP_SYNLM_EXTRACT(*voe_idx), 0);
    REG_WR(VTSS_VOP_OAM_TX_STICKY(*voe_idx), VTSS_M_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY | VTSS_M_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY);
    REG_WR(VTSS_VOP_OAM_RX_STICKY(*voe_idx), 0xffffffff); /* sticky bits cleared by writing 1 to them */
    REG_WR(VTSS_VOP_OAM_RX_STICKY2(*voe_idx), 0xff);      /* sticky bits cleared by writing 1 to them */
    REG_WR(VTSS_VOP_CCM_STAT(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_LAST(*voe_idx), 0);
    REG_WR(VTSS_VOP_INTR_STICKY(*voe_idx), 0x7ff);        /* sticky bits cleared by writing 1 to them */
    REG_WR(VTSS_VOP_INTR_ENA(*voe_idx), 0);
    REG_WR(VTSS_VOP_SLM_TX_FRM_CNT(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_TX_FCB_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_CCM_RX_FCB_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_LBR_CRC_ERR_CNT(*voe_idx), 0);

    /* Clear LM counters and COSID_MAPs: */
    switch (vtss_state->oam.voe_conf[*voe_idx].voe_type) {
    case VTSS_OAM_VOE_SERVICE:
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            offset = *voe_idx * VTSS_PRIO_ARRAY_SIZE;
            switch (vtss_state->oam.voe_conf[*voe_idx].mep_type) {
            case VTSS_OAM_DOWNMEP:
                REG_WR(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), 0);
                REG_WR(VTSS_REW_SRV_LM_CNT_LSB(offset + i), 0);
                break;
            case VTSS_OAM_UPMEP:
                REG_WR(VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB(offset + i), 0);
                REG_WR(VTSS_REW_SRV_LM_CNT_LSB(offset + i), 0);
                break;
            }
        }
        /* Default COSID_MAP_TABLE_ANA + COSID_MAP_TABLE_REW: */
        REG_WR(VTSS_VOP_COSID_MAP_TABLE_ANA(*voe_idx), 0xfac688);
        REG_WR(VTSS_VOP_COSID_MAP_TABLE_REW(*voe_idx), 0xfac688);
        /* Default COSID_MAP_CFG_ANA: */
        v = (VTSS_F_VOP_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA(0) |
             VTSS_F_VOP_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA(0) |
             VTSS_F_VOP_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA(1));
        REG_WR(VTSS_VOP_COSID_MAP_CFG_ANA(*voe_idx), v);
        /* Default COSID_MAP_CFG_REW: */
        v = (VTSS_F_VOP_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW(0) |
             VTSS_F_VOP_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW(0) |
             VTSS_F_VOP_COSID_MAP_CFG_REW_CNT_YELLOW_REW(1));
        REG_WR(VTSS_VOP_COSID_MAP_CFG_REW(*voe_idx), v);
        break;
    case VTSS_OAM_VOE_PORT:
        offset = (*voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE;
        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
            REG_WR(VTSS_ANA_AC_OAM_MOD_PORT_LM_CNT_LSB(offset + i), 0);
            REG_WR(VTSS_REW_PORT_LM_CNT_LSB(offset + i), 0);
            /* TBD - the port count-all Rx/Tx counters have been left out */
        }
        /* Default PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=0: */
        REG_WR(VTSS_VOP_PORT_RX_COSID_MAP(*voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), 0);
        REG_WR(VTSS_VOP_PORT_TX_COSID_MAP(*voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), 0);
        /* Default PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=1: */
        REG_WR(VTSS_VOP_PORT_RX_COSID_MAP1(*voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), 0);
        REG_WR(VTSS_VOP_PORT_TX_COSID_MAP1(*voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), 0);
        break;
    }

    /* Clear Per COS counter configuration */
    REG_WR(VTSS_VOP_SAM_NON_OAM_SEQ_CFG(*voe_idx), 0);
    REG_WR(VTSS_VOP_SAM_COSID_SEQ_CFG(*voe_idx), 0);

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_voe_free(vtss_state_t *vtss_state, const vtss_oam_voe_idx_t voe_idx)
{
    u32 v, i;

    if (vtss_state->oam.voe_internal[voe_idx].allocated) {
        /* Disable VOE, and we're done */
        vtss_state->oam.voe_internal[voe_idx].allocated = FALSE;
        if (voe_idx < VTSS_OAM_PATH_SERVICE_VOE_CNT) {
            voe_alloc_ix = voe_idx;
        }
        REG_WRM(VTSS_VOP_VOE_CTRL(voe_idx), 0, VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA);

        /* maybe disable path VOE: */
        REG_RD(VTSS_VOP_VOE_COMMON_CFG(voe_idx), &v);
        if (v & VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA) {
            /* disable path VOE: */
            i = VTSS_X_VOP_VOE_COMMON_CFG_PATH_VOEID(v);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_VOE_COMMON_CFG_VOE_IS_PATH);
        }
        memset(&vtss_state->oam.voe_conf[voe_idx], 0, sizeof(vtss_state->oam.voe_conf[voe_idx]));
        return oam_vop_int_update(vtss_state);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_oam_event_poll(vtss_state_t *vtss_state, vtss_oam_event_mask_t *const mask)
{
    u32 i, v;

    memset(mask, 0, sizeof(*mask));
    REG_RD(VTSS_VOP_MASTER_INTR_CTRL, &v);
    if (!VTSS_X_VOP_MASTER_INTR_CTRL_OAM_MEP_INTR(v)) {
        return VTSS_RC_OK;
    }

    /* use VOE32_INTR to find the VOE's of interest: */
    {
        u32 j;

        for (j = 0; j < 2; j++) {
            REG_RD(VTSS_VOP_VOE32_INTR(j), &v);
            mask->voe_32_mask[j] = v; /* This is passed to application for fast(er) VOE interrupt scan */

            /* Scan VOEs: */
            for (i = j * 32; (v >> (i - j * 32)) != 0 && i < VTSS_OAM_EVENT_MASK_ARRAY_SIZE; ++i) {
                if ((v & (1 << (i % 32))) == 0) {
                    continue;
                }
                REG_RD(VTSS_VOP_INTR(i), &(mask->voe_mask[i]));
            }
        }
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_voe_event_enable(vtss_state_t *vtss_state,
                                       const vtss_oam_voe_idx_t        voe_idx,
                                       const vtss_oam_voe_event_mask_t mask,
                                       const BOOL                      enable)
{
    u32 m, v;

    /* Check which kind of VOE we are running */
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 2) {
        REG_RD(VTSS_VOP_MPLS_INTR_ENA_MPLS(voe_idx), &m);
        m = enable ? (m | mask) : (m & ~mask);
        REG_WR(VTSS_VOP_MPLS_INTR_ENA_MPLS(voe_idx), m);
        return m ? oam_vop_int_enable(vtss_state, TRUE) : oam_vop_int_update(vtss_state);
    } else {
        REG_RD(VTSS_VOP_INTR_ENA(voe_idx), &m);
        m = enable ? (m | mask) : (m & ~mask);
        REG_WR(VTSS_VOP_INTR_ENA(voe_idx), m);
        return m ? oam_vop_int_enable(vtss_state, TRUE) : oam_vop_int_update(vtss_state);
    }
}

#if defined(VTSS_FEATURE_MPLS)
static vtss_rc fa_oam_voe_event_poll_mpls(vtss_state_t *vtss_state,
                                          const vtss_oam_voe_idx_t  voe_idx,
                                          vtss_oam_voe_event_mask_t *const mask)
{
    u32 intmask;
    REG_RD(VTSS_VOP_MPLS_INTR_ENA_MPLS(voe_idx), &intmask);
    /* translate intmask to sticky bit positions (yes, not the same in the chip as the intmask, arg!): */
    intmask = (
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_LOC_CHANGE_STICKY((intmask           & VTSS_OAM_VOE_EVENT_BFD_LOC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SRC_STICKY((intmask     & VTSS_OAM_VOE_EVENT_BFD_RX_DM_CHANGE_SRC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SRC_STICKY((intmask  & VTSS_OAM_VOE_EVENT_BFD_RX_STATE_CHANGE_SRC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SRC_STICKY((intmask   & VTSS_OAM_VOE_EVENT_BFD_RX_DIAG_CHANGE_SRC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SRC_STICKY((intmask         & VTSS_OAM_VOE_EVENT_BFD_RX_P_SET_SRC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SRC_STICKY((intmask         & VTSS_OAM_VOE_EVENT_BFD_RX_F_SET_SRC) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SINK_STICKY((intmask    & VTSS_OAM_VOE_EVENT_BFD_RX_DM_CHANGE_SINK) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SINK_STICKY((intmask & VTSS_OAM_VOE_EVENT_BFD_RX_STATE_CHANGE_SINK) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SINK_STICKY((intmask  & VTSS_OAM_VOE_EVENT_BFD_RX_DIAG_CHANGE_SINK) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SINK_STICKY((intmask        & VTSS_OAM_VOE_EVENT_BFD_RX_P_SET_SINK) ? 1 : 0) |
        VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SINK_STICKY((intmask        & VTSS_OAM_VOE_EVENT_BFD_RX_F_SET_SINK) ? 1 : 0)
        );
    REG_RD(VTSS_VOP_MPLS_INTR_STICKY_MPLS(voe_idx), mask);
    *mask &= intmask;
    REG_WR(VTSS_VOP_MPLS_INTR_STICKY_MPLS(voe_idx), *mask); /* sticky bits cleared by writing 1 to them */
                                                            /* translate sticky mask to event mask: */
    *mask = (
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_LOC_CHANGE_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_LOC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SRC_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_DM_CHANGE_SRC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SRC_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_STATE_CHANGE_SRC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SRC_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_DIAG_CHANGE_SRC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SRC_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_P_SET_SRC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SRC_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_F_SET_SRC : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DM_CHANGE_SINK_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_DM_CHANGE_SINK : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_STATE_CHANGE_SINK_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_STATE_CHANGE_SINK : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_DIAG_CHANGE_SINK_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_DIAG_CHANGE_SINK : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_P_SET_SINK_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_P_SET_SINK : 0) |
        (VTSS_F_VOP_MPLS_INTR_STICKY_MPLS_BFD_RX_F_SET_SINK_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_BFD_RX_F_SET_SINK : 0)
        );

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_oam_voe_event_poll(vtss_state_t *vtss_state,
                                     const vtss_oam_voe_idx_t  voe_idx,
                                     vtss_oam_voe_event_mask_t *const mask)
{
    u32 intmask;
#if defined(VTSS_FEATURE_MPLS)
    u32 v;
    /* Check which kind of VOE we are running */
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 2)
        return fa_oam_voe_event_poll_mpls(vtss_state, voe_idx, mask);
#endif
    REG_RD(VTSS_VOP_INTR_ENA(voe_idx), &intmask);
    /* translate intmask to sticky bit positions (yes, not the same in the chip as the intmask, arg!): */
    intmask = (VTSS_F_VOP_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY((intmask & VTSS_OAM_VOE_EVENT_CCM_SRC_PORT_MOVE_DETECT) ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_TLV_PORT_STATUS_STICKY((intmask        & VTSS_OAM_VOE_EVENT_CCM_TLV_PORT_STATUS)      ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY((intmask   & VTSS_OAM_VOE_EVENT_CCM_TLV_INTERFACE_STATUS) ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_PERIOD_STICKY((intmask       & VTSS_OAM_VOE_EVENT_CCM_PERIOD)               ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_PRIO_STICKY((intmask         & VTSS_OAM_VOE_EVENT_CCM_PRIORITY)             ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY((intmask & VTSS_OAM_VOE_EVENT_CCM_ZERO_PERIOD)          ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_RX_RDI_STICKY((intmask             & VTSS_OAM_VOE_EVENT_CCM_RX_RDI)               ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_LOC_STICKY((intmask                & VTSS_OAM_VOE_EVENT_CCM_LOC)                  ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_MEPID_STICKY((intmask        & VTSS_OAM_VOE_EVENT_CCM_MEP_ID)               ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_UNEXP_MEGID_STICKY((intmask        & VTSS_OAM_VOE_EVENT_CCM_MEG_ID)               ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CCM_RX_MEL_LOW_STICKY((intmask         & VTSS_OAM_VOE_EVENT_MEG_LEVEL)                ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_AIS_ZERO_PERIOD_STICKY((intmask        & VTSS_OAM_VOE_EVENT_AIS_ZERO_PERIOD)          ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_AIS_STICKY((intmask                    & VTSS_OAM_VOE_EVENT_AIS)                      ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_LCK_ZERO_PERIOD_STICKY((intmask        & VTSS_OAM_VOE_EVENT_LCK_ZERO_PERIOD)          ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_LCK_STICKY((intmask                    & VTSS_OAM_VOE_EVENT_LCK)                      ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CSF_ZERO_PERIOD_STICKY((intmask        & VTSS_OAM_VOE_EVENT_CSF_ZERO_PERIOD)          ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CSF_STICKY((intmask                    & VTSS_OAM_VOE_EVENT_CSF)                      ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CSF_RX_CSF_TYPE_STICKY((intmask        & VTSS_OAM_VOE_EVENT_CSF_TYPE)                 ? 1 : 0) |
               VTSS_F_VOP_INTR_STICKY_CSF_INVLD_CSF_TYPE_STICKY((intmask     & VTSS_OAM_VOE_EVENT_CSF_INV_TYPE)             ? 1 : 0));
    REG_RD(VTSS_VOP_INTR_STICKY(voe_idx), mask);
    *mask &= intmask;
    REG_WR(VTSS_VOP_INTR_STICKY(voe_idx), *mask); /* sticky bits cleared by writing 1 to them */
    /* translate sticky mask to event mask: */
    *mask = ((VTSS_X_VOP_INTR_STICKY_CCM_RX_SRC_PORT_DETECT_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_CCM_SRC_PORT_MOVE_DETECT : 0) |
             (VTSS_X_VOP_INTR_STICKY_TLV_PORT_STATUS_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_CCM_TLV_PORT_STATUS      : 0) |
             (VTSS_X_VOP_INTR_STICKY_TLV_INTERFACE_STATUS_STICKY(*mask)   ? VTSS_OAM_VOE_EVENT_CCM_TLV_INTERFACE_STATUS : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_PERIOD_STICKY(*mask)       ? VTSS_OAM_VOE_EVENT_CCM_PERIOD               : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_PRIO_STICKY(*mask)         ? VTSS_OAM_VOE_EVENT_CCM_PRIORITY             : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_ZERO_PERIOD_RX_ERR_STICKY(*mask) ? VTSS_OAM_VOE_EVENT_CCM_ZERO_PERIOD          : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_RX_RDI_STICKY(*mask)             ? VTSS_OAM_VOE_EVENT_CCM_RX_RDI               : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_LOC_STICKY(*mask)                ? VTSS_OAM_VOE_EVENT_CCM_LOC                  : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_MEPID_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_CCM_MEP_ID               : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_UNEXP_MEGID_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_CCM_MEG_ID               : 0) |
             (VTSS_X_VOP_INTR_STICKY_CCM_RX_MEL_LOW_STICKY(*mask)         ? VTSS_OAM_VOE_EVENT_MEG_LEVEL                : 0) |
             (VTSS_X_VOP_INTR_STICKY_AIS_ZERO_PERIOD_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_AIS_ZERO_PERIOD          : 0) |
             (VTSS_X_VOP_INTR_STICKY_AIS_STICKY(*mask)                    ? VTSS_OAM_VOE_EVENT_AIS                      : 0) |
             (VTSS_X_VOP_INTR_STICKY_LCK_ZERO_PERIOD_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_LCK_ZERO_PERIOD          : 0) |
             (VTSS_X_VOP_INTR_STICKY_LCK_STICKY(*mask)                    ? VTSS_OAM_VOE_EVENT_LCK                      : 0) |
             (VTSS_X_VOP_INTR_STICKY_CSF_ZERO_PERIOD_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_CSF_ZERO_PERIOD          : 0) |
             (VTSS_X_VOP_INTR_STICKY_CSF_STICKY(*mask)                    ? VTSS_OAM_VOE_EVENT_CSF                      : 0) |
             (VTSS_X_VOP_INTR_STICKY_CSF_RX_CSF_TYPE_STICKY(*mask)        ? VTSS_OAM_VOE_EVENT_CSF_TYPE                 : 0) |
             (VTSS_X_VOP_INTR_STICKY_CSF_INVLD_CSF_TYPE_STICKY(*mask)     ? VTSS_OAM_VOE_EVENT_CSF_INV_TYPE             : 0));
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MPLS)
static vtss_rc fa_oam_voe_cfg_set_mpls(vtss_state_t *vtss_state, const vtss_oam_voe_idx_t voe_idx)
{
    u32  i, v, mask;
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);

    VTSS_D("Enter VOE %d", voe_idx);

    if (((voe_idx < VTSS_OAM_PORT_VOE_BASE_IDX) && (cfg->voe_type == VTSS_OAM_VOE_PORT)) ||
        ((voe_idx >= VTSS_OAM_PORT_VOE_BASE_IDX) && (cfg->voe_type == VTSS_OAM_VOE_SERVICE))) {
        VTSS_D("VOE %d: VOE type mismatch", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->proc.pdu_type != VTSS_OAM_PDU_G8113_2) {
        VTSS_D("VOE %d: Only try to configure MPLS BFD VOE (G.8113_2) when pdu_type = VTSS_OAM_PDU_G8113_2", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->bfd.enable &&
        (cfg->ccm.enable | cfg->ccm_lm.enable | cfg->single_ended_lm.enable | cfg->lb.enable | cfg->tst.enable |
         cfg->dm.enable_dmm | cfg->dm.enable_1dm | cfg->lt.enable | cfg->sl.enable | cfg->sat.enable )) {
        VTSS_D("VOE %d: Cannot enable G.8113_2 and Y.1731 style PDUs on a MEP", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->voe_type == VTSS_OAM_VOE_PORT ) {
        VTSS_D("VOE %d: Cannot configure port MEP for MPLS service", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->bfd.enable) {
        if (cfg->bfd.my_discr[0] == 0) {
            VTSS_D("VOE %d: My Discriminator (source) cannot be 0", voe_idx);
            return VTSS_RC_ERROR;
        }
        if (cfg->bfd.is_independent && cfg->bfd.my_discr[1] == 0) {
            VTSS_D("VOE %d: My Discriminator (sink) cannot be 0", voe_idx);
            return VTSS_RC_ERROR;
        }
    }

    if (cfg->svc_to_path && cfg->svc_to_path_idx == voe_idx) {  // FIXME: is this correct?
        VTSS_D("VOE %d: Cannot configure MEP as path VOE for itself", voe_idx);
        return VTSS_RC_ERROR;
    }

    /* VOE_MISC_CONFIG: */
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if (cfg->bfd.enable && VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 0) {    /* enabling BFD */
        /* Clear BFD counters: */
        REG_WR(VTSS_VOP_MPLS_BFD_CC_RX_VLD_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_CV_RX_VLD_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_CC_RX_INVLD_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_CV_RX_INVLD_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_CC_TX_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_CV_TX_CNT_REG(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_RX_CNT_SEL_OAM_MPLS(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_RX_CNT_NON_SEL_OAM_MPLS(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_TX_CNT_SEL_OAM_MPLS(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_TX_CNT_NON_SEL_OAM_MPLS(voe_idx), 0);
        REG_WR(VTSS_VOP_MPLS_BFD_STAT(voe_idx), 8); // bfd_miss_count
        REG_WR(VTSS_VOP_MPLS_BFD_RX_LAST(voe_idx), 0);

        /* BFD source/sink detect mult (DM): */
        REG_WR(VTSS_VOP_MPLS_BFD_SRC_INFO(voe_idx),
               VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DM_SRC(3)          |
               VTSS_F_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DM_SRC(3));
        REG_WR(VTSS_VOP_MPLS_BFD_SINK_INFO(voe_idx),
               VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DM_SINK(3)        |
               VTSS_F_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DM_SINK(3));

        VTSS_RC(fa_oam_voe_counter_clear(vtss_state, voe_idx, VTSS_OAM_CNT_ALL | VTSS_OAM_CNT_DIR_BOTH));

        /* Clear BFD sticky bits: */
        REG_WR(VTSS_VOP_MPLS_BFD_RX_STICKY(voe_idx),
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY  |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY        |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY    |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY       |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY         |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY        |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY          |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY          |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY          |
               VTSS_M_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY           );

        REG_WR(VTSS_VOP_MPLS_PDU_EXTRACT_MPLS(voe_idx),
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE      |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR        |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR        |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR          |
               VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR           );

        REG_WR(VTSS_VOP_MPLS_BFD_TX_STICKY(voe_idx),
               VTSS_M_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH);

        REG_WR(VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(voe_idx),
               VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK |
               VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY |
               VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY |
               VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY);

        REG_WR(VTSS_VOP_MPLS_INTR_ENA_MPLS(voe_idx), 0);
    }

    /* VOE_MEPID_CFG: */
    v = VTSS_F_VOP_VOE_MEPID_CFG_VOE_MEPID(cfg->mepid);
    REG_WR(VTSS_VOP_VOE_MEPID_CFG(voe_idx), v);
    v = 0;
    REG_WR(VTSS_VOP_PEER_MEPID_CFG(voe_idx), v);

    /* PATH_VOE_CFG: */
    if (cfg->voe_type == VTSS_OAM_VOE_SERVICE) {
        REG_RD(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), &v);
        if (cfg->svc_to_path) {
            if (VTSS_F_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA(v)) {
                i = VTSS_X_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID(v);
                if (i != cfg->svc_to_path_idx) {
                    /* move, disable old path VOE: */
                    REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH);
                }
            }
            /* enable new path VOE: */
            i = cfg->svc_to_path_idx;
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(i), VTSS_F_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH(1), VTSS_M_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), VTSS_F_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID(cfg->svc_to_path_idx), VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID);
        } else if (VTSS_F_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA(v)) {
            /* disable path VOE: */
            i = VTSS_X_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID(v);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_VOE_IS_PATH);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), 0, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), 0, VTSS_M_VOP_MPLS_VOE_COMMON_CFG_PATH_VOEID);
        }
    }

    v = B2B(cfg->proc.copy_next_only, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE) |
        B2B(cfg->proc.copy_next_cc_rx, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR) |
        B2B(cfg->proc.copy_next_cv_rx, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR) |
        B2B(cfg->proc.copy_next_rx_param_change, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR) |
        B2B(cfg->proc.copy_next_rx_poll_flag, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR) |
        B2B(cfg->proc.copy_next_rx_final_flag, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR) |
        B2B(cfg->proc.copy_next_rx_error, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR) |
        B2B(cfg->proc.copy_next_tx_error, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR);
    REG_WR(VTSS_VOP_MPLS_PDU_EXTRACT_MPLS(voe_idx), v);

    /* OAM_CPU_COPY_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].copy_to_cpu, VTSS_F_VOP_MPLS_CPU_COPY_CTRL_MPLS_GENERIC_COPY_MASK(mask));
    }
    v |= B2B(cfg->bfd.enable && cfg->bfd.copy_cc_to_cpu, VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CC_CPU_COPY_ENA);
    v |= B2B(cfg->bfd.enable && cfg->bfd.copy_cv_to_cpu, VTSS_M_VOP_MPLS_CPU_COPY_CTRL_MPLS_BFD_CV_CPU_COPY_ENA);
    REG_WR(VTSS_VOP_MPLS_CPU_COPY_CTRL_MPLS(voe_idx), v);

    /* OAM_CNT_OAM_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].count_as_selected, VTSS_F_VOP_MPLS_OAM_CNT_SEL_MPLS_GENERIC_CPT_CNT_SEL_MASK(mask));
    }
    v |= B2B(cfg->unknown.enable && cfg->unknown.count_as_selected, VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_UNK_CPT_CNT_SEL_ENA);
    v |= B2B(cfg->bfd.enable     && cfg->bfd.count_as_selected,     VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CC_CNT_SEL_ENA);
    v |= B2B(cfg->bfd.enable     && cfg->bfd.count_as_selected,     VTSS_M_VOP_MPLS_OAM_CNT_SEL_MPLS_BFD_CV_CNT_SEL_ENA);
    REG_WR(VTSS_VOP_MPLS_OAM_CNT_SEL_MPLS(voe_idx), v);

    /* OAM_CNT_DATA_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].count_as_data, VTSS_F_VOP_MPLS_OAM_CNT_DATA_MPLS_GENERIC_CPT_CNT_DATA_MASK(mask));
    }
    v |= B2B(cfg->unknown.enable && cfg->unknown.count_as_data, VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_UNK_CPT_CNT_DATA_ENA);
    v |= B2B(cfg->bfd.enable     && cfg->bfd.count_as_data,     VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CC_CNT_DATA_ENA);
    v |= B2B(cfg->bfd.enable     && cfg->bfd.count_as_data,     VTSS_M_VOP_MPLS_OAM_CNT_DATA_MPLS_BFD_CV_CNT_DATA_ENA);
    REG_WR(VTSS_VOP_MPLS_OAM_CNT_DATA_MPLS(voe_idx), v);


    /* OAM_HW_CTRL: */
    v = 0;
    v |= B2B(cfg->bfd.enable,                      VTSS_M_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CC_ENA);
    v |= B2B(cfg->bfd.enable && !cfg->bfd.cc_only, VTSS_M_VOP_MPLS_OAM_HW_CTRL_MPLS_BFD_CV_ENA);
    REG_WR(VTSS_VOP_MPLS_OAM_HW_CTRL_MPLS(voe_idx), v);

    if (cfg->bfd.enable) {
        v = cfg->bfd.my_discr[0];
        REG_WR(VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SRC(voe_idx), v);
        v = cfg->bfd.your_discr[0];
        REG_WR(VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SRC(voe_idx), v);
    }

    if (cfg->bfd.enable && cfg->bfd.is_independent) { /* only independent mode */
        v = cfg->bfd.my_discr[1];
        REG_WR(VTSS_VOP_MPLS_BFD_LOCAL_DISCR_SINK(voe_idx), v);
        v = cfg->bfd.your_discr[1];
        REG_WR(VTSS_VOP_MPLS_BFD_REMOTE_DISCR_SINK(voe_idx), v);
    }

    if (cfg->bfd.enable) {
        v = VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CC_RFC6428(cfg->bfd.cc_rfc6428 ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_SCAN_PERIOD(cfg->bfd.rx_period) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_SAMPLE_ENA(cfg->bfd.rx_sample ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_TX_UPDATE_ENA(cfg->bfd.tx_update ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_COORDINATED_MODE_ENA(cfg->bfd.is_independent ? 0 : 1) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CC_ENA(cfg->bfd.rx_verify_cc ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_CV_ENA(cfg->bfd.rx_verify_cv ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_VERSION_ENA(cfg->bfd.rx_verify_version ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_MIN_LEN_ENA(cfg->bfd.rx_verify_min_len ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_DISCR_ENA(cfg->bfd.rx_verify_discr ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_RX_VERIFY_FLAGS_ENA(cfg->bfd.rx_verify_flags ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CC_AUTH_ENA(cfg->bfd.cc_auth ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_CV_AUTH_ENA(cfg->bfd.cv_auth ? 1 : 0) |
            VTSS_F_VOP_MPLS_BFD_CONFIG_BFD_MAX_LEN(cfg->bfd.max_len);
       REG_WR(VTSS_VOP_MPLS_BFD_CONFIG(voe_idx), v);
    }

    REG_WRM(VTSS_VOP_MPLS_VOE_COMMON_CFG(voe_idx), VTSS_F_VOP_MPLS_VOE_COMMON_CFG_UPMEP_ENA(cfg->mep_type == VTSS_OAM_UPMEP ? 1 : 0), VTSS_M_VOP_MPLS_VOE_COMMON_CFG_UPMEP_ENA);

    /* VOE_MISC_CONFIG. Comes last, as this is where we enable the VOE */
    REG_WRM(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), 0, VTSS_M_VOP_VOE_MISC_CONFIG_BLK_ENA);
    REG_WRM(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), VTSS_F_VOP_VOE_MISC_CONFIG_VOE_ENA(2), VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA);

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_oam_voe_cfg_set(vtss_state_t *vtss_state, const vtss_oam_voe_idx_t voe_idx)
{
    u32  i, v, v_slm, mask;
    BOOL doing_lb = FALSE;
    BOOL doing_tst = FALSE;
    BOOL doing_anything;
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);
    const u8 *p;
    vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter VOE %d", voe_idx);

    if (((voe_idx < VTSS_OAM_PORT_VOE_BASE_IDX) && (cfg->voe_type == VTSS_OAM_VOE_PORT)) ||
        ((voe_idx >= VTSS_OAM_PORT_VOE_BASE_IDX) && (cfg->voe_type == VTSS_OAM_VOE_SERVICE))) {
        VTSS_D("VOE %d: VOE type mismatch", voe_idx);
        return VTSS_RC_ERROR;
    }

#if defined(VTSS_FEATURE_MPLS)
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_2)
        return fa_oam_voe_cfg_set_mpls(vtss_state, voe_idx);
#endif

    if (cfg->lb.enable && cfg->tst.enable) {
        VTSS_D("VOE %d: Cannot enable simultaneous LB and TST", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->single_ended_lm.enable && cfg->ccm_lm.enable) {
        VTSS_D("VOE %d: Cannot enable simultaneous single- and dual-ended LM", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->sl.enable && (cfg->single_ended_lm.enable || cfg->ccm_lm.enable)) {
        VTSS_D("VOE %d: Cannot enable simultaneous synthetic loss and frame loss LM", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->voe_type == VTSS_OAM_VOE_PORT && cfg->mep_type == VTSS_OAM_UPMEP) {
        VTSS_D("VOE %d: Cannot configure port MEP as UP MEP", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->svc_to_path && cfg->svc_to_path_idx == voe_idx) {
        VTSS_D("VOE %d: Cannot configure MEP as path VOE for itself", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->sl.enable && cfg->sl.count_per_prio && !cfg->sl.peer_mepid_valid[0]) {
        VTSS_D("VOE %d: When SL Count Per Prio is enabled the first peer MEP must be valid", voe_idx);
        return VTSS_RC_ERROR;
    }

    if (cfg->sat.enable) {
        if (cfg->sat.non_oam_seq_no_mode != VTSS_OAM_SAT_NON_OAM_SEQ_NO_DISABLED &&
            cfg->sat.cosid_seq_no_mode == VTSS_OAM_SAT_COSID_SEQ_NO_CCM) {
            VTSS_D("VOE %d: Cannot configure MEP for SAT non OAM and CCM at the same time", voe_idx);
            return VTSS_RC_ERROR;
        }
        if (cfg->sat.cosid_seq_no_mode != VTSS_OAM_SAT_COSID_SEQ_NO_DISABLED &&
            !vtss_state->oam.sat_cosid_counters_allocated[cfg->sat.cosid_seq_no_idx]) {
            VTSS_D("VOE %d: SAT per COS ID counter set %u are not allocated", voe_idx, cfg->sat.cosid_seq_no_idx);
            return VTSS_RC_ERROR;
        }
    }

    /* If the VOE isn't enabled yet, i.e. it's only been allocated and this
     * is the first call to this  function, then we clear the logical
     * counters.
     */
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if ((v & VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA) == 0) {
        VTSS_RC(fa_oam_voe_counter_clear(vtss_state, voe_idx, VTSS_OAM_CNT_ALL | VTSS_OAM_CNT_DIR_BOTH));
    }

    /* Then, if we're enabling LB (and it wasn't enabled previously), we discard
     * any changes to the LB HW counters. Same thing for TST.
     *
     * This is necessary since the two functions share registers.
     */
    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));

    doing_anything = doing_lb || doing_tst;

    if ((!cfg->tst.enable && doing_tst) || (!cfg->lb.enable && doing_lb)) { /* TST or LB is being disabled - update the counters */
        (void)oam_voe_counter_update_internal(vtss_state, voe_idx, 0);
    }
    if (cfg->tst.enable && (doing_lb || !doing_anything)) {        /* Idle-to-TST or change from LB to TST - rebase TST counters */
        REG_RD(VTSS_VOP_LBR_RX_FRM_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->tst.rx_tst);
        REG_RD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->tst.tx_tst);
        REG_RD(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->tst.rx_tst_trans_id_err);
        REG_RD(VTSS_VOP_LBR_CRC_ERR_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->tst.rx_tst_crc_err);
    }
    if (cfg->lb.enable && (doing_tst || !doing_anything)) {        /* Idle-to-LB or change from TST to LB - rebase LB counters */
        REG_RD(VTSS_VOP_LBR_RX_FRM_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->lb.rx_lbr);
        REG_RD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->lb.tx_lbm);
        REG_RD(VTSS_VOP_LBR_RX_TRANSID_ERR_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->lb.rx_lbr_trans_id_err);
        REG_RD(VTSS_VOP_LBR_CRC_ERR_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->lb.rx_lbr_crc_err);
        REG_RD(VTSS_VOP_LBR_TX_FRM_CNT(voe_idx), &v);
        vtss_cmn_counter_32_rebase(v, &chipcnt->lb.tx_lbr);
    }

    /* TBD below - when enabling a function (e.g. CCM), clear any stats first ? E.g. like is done for SL below? */

    /* VOE_MISC_CONFIG: */
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if (cfg->sl.enable && VTSS_X_VOP_VOE_MISC_CONFIG_SL_ENA(v) == 0) {
        /* enabling SL - clear SLM Tx counter: */
        REG_WR(VTSS_VOP_SLM_TX_FRM_CNT(voe_idx), 0);
    }

    /* VOE_MEPID_CFG: */
    v = VTSS_F_VOP_VOE_MEPID_CFG_VOE_MEPID(cfg->mepid);
    REG_WR(VTSS_VOP_VOE_MEPID_CFG(voe_idx), v);

    /* PEER_MEPID_CFG: */
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_Y1731 ||
        cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_1) {
        v = VTSS_F_VOP_PEER_MEPID_CFG_PEER_MEPID(cfg->ccm.peer_mepid);
    } else {
        v = 0;
    }
    REG_WR(VTSS_VOP_PEER_MEPID_CFG(voe_idx), v);

    /* PATH_VOE_CFG: */
    if (cfg->voe_type == VTSS_OAM_VOE_SERVICE) {
        REG_RD(VTSS_VOP_VOE_COMMON_CFG(voe_idx), &v);
        if (cfg->svc_to_path) {
            if (VTSS_F_VOP_VOE_COMMON_CFG_PATH_VOE_ENA(v)) {
                i = VTSS_X_VOP_VOE_COMMON_CFG_PATH_VOEID(v);
                if (i != cfg->svc_to_path_idx) {
                    /* move, disable old path VOE: */
                    REG_WRM(VTSS_VOP_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_VOE_COMMON_CFG_VOE_IS_PATH);
                }
            }
            /* enable new path VOE: */
            i = cfg->svc_to_path_idx;
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(i), VTSS_F_VOP_VOE_COMMON_CFG_VOE_IS_PATH(1), VTSS_M_VOP_VOE_COMMON_CFG_VOE_IS_PATH);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(voe_idx), VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA, VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(voe_idx), VTSS_F_VOP_VOE_COMMON_CFG_PATH_VOEID(cfg->svc_to_path_idx), VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOEID);
        } else if (VTSS_F_VOP_VOE_COMMON_CFG_PATH_VOE_ENA(v)) {
            /* disable path VOE: */
            i = VTSS_X_VOP_VOE_COMMON_CFG_PATH_VOEID(v);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(i), 0, VTSS_M_VOP_VOE_COMMON_CFG_VOE_IS_PATH);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(voe_idx), 0, VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOE_ENA);
            REG_WRM(VTSS_VOP_VOE_COMMON_CFG(voe_idx), 0, VTSS_M_VOP_VOE_COMMON_CFG_PATH_VOEID);
        }
    }
    v = B2B(cfg->proc.copy_next_only,           VTSS_M_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE)         |
        B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR) |
        B2B(cfg->proc.copy_on_mel_too_low_err,  VTSS_M_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR)         |
        B2B(cfg->proc.copy_on_mel_too_high_err, VTSS_M_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR)      |
        B2B(cfg->proc.copy_on_dmac_err,         VTSS_M_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR)            |
        B2B(cfg->proc.copy_on_version_err,      VTSS_M_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR)     |
        B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR)       |
        B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR)       |
        B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR)      |
        B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR)        |
        B2B(cfg->proc.copy_on_ccm_tlv_nonzero,  VTSS_M_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR)    |
        B2B(cfg->proc.copy_next_valid_ccm,      VTSS_M_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR)         |
        B2B(cfg->proc.copy_next_tst_or_lbr,     VTSS_M_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR)        |
        B2B(cfg->proc.copy_on_tx_block_err,     VTSS_M_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR)           |
        B2B(cfg->proc.copy_on_sat_seq_err,      VTSS_M_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR)         |
        B2B(cfg->proc.copy_on_g8113_1_lbm_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR)    |
        B2B(cfg->proc.copy_on_g8113_1_lbr_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR)    |
        B2B(cfg->proc.copy_on_sl_err,           VTSS_M_VOP_PDU_EXTRACT_SL_ERR_EXTR)                 |
        B2B(cfg->proc.copy_on_ais_err,          VTSS_M_VOP_PDU_EXTRACT_AIS_ERR_EXTR)                |
        B2B(cfg->proc.copy_next_valid_ais,      VTSS_M_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR)         |
        B2B(cfg->proc.copy_on_lck_err,          VTSS_M_VOP_PDU_EXTRACT_LCK_ERR_EXTR)                |
        B2B(cfg->proc.copy_next_valid_lck,      VTSS_M_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR)         |
        B2B(cfg->proc.copy_on_csf_err,          VTSS_M_VOP_PDU_EXTRACT_CSF_ERR_EXTR)                |
        B2B(cfg->proc.copy_next_valid_csf,      VTSS_M_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR);

    REG_WR(VTSS_VOP_PDU_EXTRACT(voe_idx), v);

    /* OAM_CPU_COPY_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].copy_to_cpu,          VTSS_F_VOP_OAM_CPU_COPY_CTRL_2_GENERIC_COPY_MASK(mask));
    }
    v |= B2B(cfg->unknown.enable         && cfg->unknown.copy_to_cpu,             VTSS_M_VOP_OAM_CPU_COPY_CTRL_UNK_OPCODE_CPU_COPY_ENA);
    v |= B2B(cfg->single_ended_lm.enable && cfg->single_ended_lm.copy_lmm_to_cpu, VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA);
    v |= B2B(cfg->single_ended_lm.enable && cfg->single_ended_lm.copy_lmr_to_cpu, VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA);
    v |= B2B(cfg->sl.enable              && cfg->sl.copy_slm_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMM_CPU_COPY_ENA);
    v |= B2B(cfg->sl.enable              && cfg->sl.copy_slr_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LMR_CPU_COPY_ENA);
    v |= B2B(cfg->tst.enable             && cfg->tst.copy_to_cpu,                 VTSS_M_VOP_OAM_CPU_COPY_CTRL_TST_CPU_COPY_ENA);
    v |= B2B(cfg->lb.enable              && cfg->lb.copy_lbm_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LBM_CPU_COPY_ENA);
    v |= B2B(cfg->lb.enable              && cfg->lb.copy_lbr_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LBR_CPU_COPY_ENA);
    v |= B2B(cfg->lt.enable              && cfg->lt.copy_ltm_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LTM_CPU_COPY_ENA);
    v |= B2B(cfg->lt.enable              && cfg->lt.copy_ltr_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_LTR_CPU_COPY_ENA);
    v |= B2B(cfg->dm.enable_dmm          && cfg->dm.copy_dmm_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_DMM_CPU_COPY_ENA);
    v |= B2B(cfg->dm.enable_dmm          && cfg->dm.copy_dmr_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_DMR_CPU_COPY_ENA);
    v |= B2B(cfg->dm.enable_1dm          && cfg->dm.copy_1dm_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_SDM_CPU_COPY_ENA);
    v |= B2B(cfg->ccm_lm.enable          && cfg->ccm_lm.copy_to_cpu,              VTSS_M_VOP_OAM_CPU_COPY_CTRL_CCM_LM_CPU_COPY_ENA);
    v |= B2B(TRUE                        && cfg->ais.copy_to_cpu,                 VTSS_M_VOP_OAM_CPU_COPY_CTRL_AIS_CPU_COPY_ENA);
    v |= B2B(TRUE                        && cfg->lck.copy_to_cpu,                 VTSS_M_VOP_OAM_CPU_COPY_CTRL_LCK_CPU_COPY_ENA);
    v |= B2B(TRUE                        && cfg->csf.copy_to_cpu,                 VTSS_M_VOP_OAM_CPU_COPY_CTRL_CSF_CPU_COPY_ENA);
    if (!cfg->proc.copy_next_only) {
        v |= B2B(                           cfg->ccm.copy_to_cpu,                 VTSS_M_VOP_OAM_CPU_COPY_CTRL_CCM_CPU_COPY_ENA);
    }
    v |= B2B(cfg->proc.ccm_check_only, VTSS_M_VOP_OAM_CPU_COPY_CTRL_PDU_ERR_EXTRACT_CCM_ONLY);
    REG_WR(VTSS_VOP_OAM_CPU_COPY_CTRL(voe_idx), v);

    if (!cfg->proc.copy_next_only) {
        v = B2B(cfg->proc.copy_next_only,           VTSS_M_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE)         |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR) |
            B2B(cfg->proc.copy_on_mel_too_low_err,  VTSS_M_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR)         |
            B2B(cfg->proc.copy_on_mel_too_high_err, VTSS_M_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR)      |
            B2B(cfg->proc.copy_on_dmac_err,         VTSS_M_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR)            |
            B2B(cfg->proc.copy_on_version_err,      VTSS_M_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR)     |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR)       |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR)       |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR)      |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR)        |
            B2B(cfg->proc.copy_on_ccm_tlv_nonzero,  VTSS_M_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR)    |
            B2B(cfg->proc.copy_next_valid_ccm,      VTSS_M_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR)         |
            B2B(cfg->proc.copy_next_tst_or_lbr,     VTSS_M_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR)        |
            B2B(cfg->proc.copy_on_tx_block_err,     VTSS_M_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR)           |
            B2B(cfg->proc.copy_on_sat_seq_err,      VTSS_M_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR)         |
            B2B(cfg->proc.copy_on_g8113_1_lbm_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR)    |
            B2B(cfg->proc.copy_on_g8113_1_lbr_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR)    |
            B2B(cfg->proc.copy_on_sl_err,           VTSS_M_VOP_PDU_EXTRACT_SL_ERR_EXTR)                 |
            B2B(cfg->proc.copy_on_ais_err,          VTSS_M_VOP_PDU_EXTRACT_AIS_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_ais,      VTSS_M_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR)         |
            B2B(cfg->proc.copy_on_lck_err,          VTSS_M_VOP_PDU_EXTRACT_LCK_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_lck,      VTSS_M_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR)         |
            B2B(cfg->proc.copy_on_csf_err,          VTSS_M_VOP_PDU_EXTRACT_CSF_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_csf,      VTSS_M_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR);

        REG_WR(VTSS_VOP_PDU_EXTRACT(voe_idx), v);
    }

    // Control extraction of SL peer PDUs (note: NOT controlled by proc.copy_next_only!)
    v = VTSS_M_VOP_SYNLM_EXTRACT_EXTRACT_HMO |
        (cfg->proc.copy_next_sl_peer[0] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  1) : 0) |
        (cfg->proc.copy_next_sl_peer[1] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  2) : 0) |
        (cfg->proc.copy_next_sl_peer[2] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  4) : 0) |
        (cfg->proc.copy_next_sl_peer[3] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  8) : 0) |
        (cfg->proc.copy_next_sl_peer[4] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 16) : 0) |
        (cfg->proc.copy_next_sl_peer[5] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 32) : 0) |
        (cfg->proc.copy_next_sl_peer[6] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 64) : 0) |
        (cfg->proc.copy_next_sl_peer[7] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(128) : 0) |
        (cfg->proc.copy_next_slm_peer[0] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  1) : 0) |
        (cfg->proc.copy_next_slm_peer[1] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  2) : 0) |
        (cfg->proc.copy_next_slm_peer[2] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  4) : 0) |
        (cfg->proc.copy_next_slm_peer[3] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  8) : 0) |
        (cfg->proc.copy_next_slm_peer[4] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 16) : 0) |
        (cfg->proc.copy_next_slm_peer[5] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 32) : 0) |
        (cfg->proc.copy_next_slm_peer[6] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 64) : 0) |
        (cfg->proc.copy_next_slm_peer[7] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(128) : 0);

    REG_WR(VTSS_VOP_SYNLM_EXTRACT(voe_idx), v);

    /* PDU_VOE_PASS: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].forward,          VTSS_F_VOP_PDU_VOE_PASS_GENERIC_VOE_PASS_ENA(mask));
    }
    REG_WR(VTSS_VOP_PDU_VOE_PASS(voe_idx), v);

    /* OAM_CNT_OAM_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].count_as_selected,            VTSS_F_VOP_OAM_CNT_OAM_CTRL_GENERIC_OAM_CNT_MASK(mask));
    }
    v |= B2B(cfg->unknown.enable         && cfg->unknown.count_as_selected,               VTSS_M_VOP_OAM_CNT_OAM_CTRL_UNK_OPCODE_OAM_CNT_ENA);
    v |= B2B(                               cfg->ccm.count_as_selected,                   VTSS_M_VOP_OAM_CNT_OAM_CTRL_CCM_OAM_CNT_ENA);
    v |= B2B(cfg->ccm_lm.enable          && cfg->ccm_lm.count_as_selected,                VTSS_M_VOP_OAM_CNT_OAM_CTRL_CCM_LM_OAM_CNT_ENA);
    v |= B2B(cfg->single_ended_lm.enable && cfg->single_ended_lm.count_as_selected,       VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA | VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA);
    v |= B2B(cfg->sl.enable              && cfg->sl.count_as_selected,                    VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMM_OAM_CNT_ENA | VTSS_M_VOP_OAM_CNT_OAM_CTRL_LMR_OAM_CNT_ENA);
    v |= B2B(cfg->lb.enable              && cfg->lb.count_as_selected,                    VTSS_M_VOP_OAM_CNT_OAM_CTRL_LBM_OAM_CNT_ENA | VTSS_M_VOP_OAM_CNT_OAM_CTRL_LBR_OAM_CNT_ENA);
    v |= B2B(cfg->tst.enable             && cfg->tst.count_as_selected,                   VTSS_M_VOP_OAM_CNT_OAM_CTRL_TST_OAM_CNT_ENA);
    v |= B2B(cfg->lt.enable              && cfg->lt.count_as_selected,                    VTSS_M_VOP_OAM_CNT_OAM_CTRL_LTM_OAM_CNT_ENA | VTSS_M_VOP_OAM_CNT_OAM_CTRL_LTR_OAM_CNT_ENA);
    v |= B2B(cfg->dm.enable_dmm          && cfg->dm.count_as_selected,                    VTSS_M_VOP_OAM_CNT_OAM_CTRL_DMM_OAM_CNT_ENA | VTSS_M_VOP_OAM_CNT_OAM_CTRL_DMR_OAM_CNT_ENA);
    v |= B2B(cfg->dm.enable_1dm          && cfg->dm.count_as_selected,                    VTSS_M_VOP_OAM_CNT_OAM_CTRL_SDM_OAM_CNT_ENA);
    v |= B2B(TRUE                        && cfg->ais.count_as_selected,                   VTSS_M_VOP_OAM_CNT_OAM_CTRL_AIS_OAM_CNT_ENA);
    v |= B2B(TRUE                        && cfg->lck.count_as_selected,                   VTSS_M_VOP_OAM_CNT_OAM_CTRL_LCK_OAM_CNT_ENA);
    v |= B2B(TRUE                        && cfg->csf.count_as_selected,                   VTSS_M_VOP_OAM_CNT_OAM_CTRL_CSF_OAM_CNT_ENA);
    REG_WR(VTSS_VOP_OAM_CNT_OAM_CTRL(voe_idx), v);

    /* OAM_CNT_DATA_CTRL: */
    v = 0;
    for (i = 0, mask = 0x01; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i, mask <<= 1) {
        v |= B2B(cfg->generic[i].enable  && cfg->generic[i].count_as_data,            VTSS_F_VOP_OAM_CNT_DATA_CTRL_GENERIC_DATA_CNT_MASK(mask));
    }
    v |= B2B(cfg->unknown.enable         && cfg->unknown.count_as_data,               VTSS_M_VOP_OAM_CNT_DATA_CTRL_UNK_OPCODE_DATA_CNT_ENA);
    v |= B2B(                               cfg->ccm.count_as_data,                   VTSS_M_VOP_OAM_CNT_DATA_CTRL_CCM_DATA_CNT_ENA);
    v |= B2B(cfg->single_ended_lm.enable && cfg->single_ended_lm.count_as_data,       VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA | VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA);
    v |= B2B(cfg->sl.enable              && cfg->sl.count_as_data,                    VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMM_DATA_CNT_ENA | VTSS_M_VOP_OAM_CNT_DATA_CTRL_LMR_DATA_CNT_ENA);
    v |= B2B(cfg->lb.enable              && cfg->lb.count_as_data,                    VTSS_M_VOP_OAM_CNT_DATA_CTRL_LBM_DATA_CNT_ENA | VTSS_M_VOP_OAM_CNT_DATA_CTRL_LBR_DATA_CNT_ENA);
    v |= B2B(cfg->tst.enable             && cfg->tst.count_as_data,                   VTSS_M_VOP_OAM_CNT_DATA_CTRL_TST_DATA_CNT_ENA);
    v |= B2B(cfg->lt.enable              && cfg->lt.count_as_data,                    VTSS_M_VOP_OAM_CNT_DATA_CTRL_LTM_DATA_CNT_ENA | VTSS_M_VOP_OAM_CNT_DATA_CTRL_LTR_DATA_CNT_ENA);
    v |= B2B(cfg->dm.enable_dmm          && cfg->dm.count_as_data,                    VTSS_M_VOP_OAM_CNT_DATA_CTRL_DMM_DATA_CNT_ENA | VTSS_M_VOP_OAM_CNT_DATA_CTRL_DMR_DATA_CNT_ENA);
    v |= B2B(cfg->dm.enable_1dm          && cfg->dm.count_as_data,                    VTSS_M_VOP_OAM_CNT_DATA_CTRL_SDM_DATA_CNT_ENA);
    v |= B2B(TRUE                        && cfg->ais.count_as_data,                   VTSS_M_VOP_OAM_CNT_DATA_CTRL_AIS_DATA_CNT_ENA);
    v |= B2B(TRUE                        && cfg->lck.count_as_data,                   VTSS_M_VOP_OAM_CNT_DATA_CTRL_LCK_DATA_CNT_ENA);
    v |= B2B(TRUE                        && cfg->csf.count_as_data,                   VTSS_M_VOP_OAM_CNT_DATA_CTRL_CSF_DATA_CNT_ENA);
    REG_WR(VTSS_VOP_OAM_CNT_DATA_CTRL(voe_idx), v);

    /* MEP_UC_MAC_LSB / MEP_UC_MAC_MSB */
    v = VTSS_F_VOP_MEP_UC_MAC_MSB_MEP_UC_MAC_MSB((cfg->unicast_mac.addr[0] << 8) | cfg->unicast_mac.addr[1]);
    REG_WR(VTSS_VOP_MEP_UC_MAC_MSB(voe_idx), v);

    v = (cfg->unicast_mac.addr[2] << 24) |
        (cfg->unicast_mac.addr[3] << 16) |
        (cfg->unicast_mac.addr[4] <<  8) |
        (cfg->unicast_mac.addr[5]);
    REG_WR(VTSS_VOP_MEP_UC_MAC_LSB(voe_idx), v);

    /* OAM_HW_CTRL: */
    v = 0;
    v |= B2B(cfg->ccm.enable,                VTSS_M_VOP_OAM_HW_CTRL_CCM_ENA);
    v |= B2B(cfg->ccm_lm.enable,             VTSS_M_VOP_OAM_HW_CTRL_CCM_LM_ENA);
    v |= B2B(cfg->single_ended_lm.enable,    VTSS_M_VOP_OAM_HW_CTRL_LMM_ENA | VTSS_M_VOP_OAM_HW_CTRL_LMR_ENA);
    v |= B2B(cfg->sl.enable,                 VTSS_M_VOP_OAM_HW_CTRL_LMM_ENA | VTSS_M_VOP_OAM_HW_CTRL_LMR_ENA);
    v |= B2B(cfg->lb.enable,                 VTSS_M_VOP_OAM_HW_CTRL_LBM_ENA | VTSS_M_VOP_OAM_HW_CTRL_LBR_ENA | VTSS_M_VOP_OAM_HW_CTRL_LBR_TLV_CRC_VERIFY_ENA);
    v |= B2B(cfg->tst.enable,                VTSS_M_VOP_OAM_HW_CTRL_TST_ENA | VTSS_M_VOP_OAM_HW_CTRL_TST_TLV_CRC_VERIFY_ENA);
    v |= B2B(cfg->dm.enable_dmm,             VTSS_M_VOP_OAM_HW_CTRL_DMM_ENA | VTSS_M_VOP_OAM_HW_CTRL_DMR_ENA);
    v |= B2B(cfg->dm.enable_1dm,             VTSS_M_VOP_OAM_HW_CTRL_SDM_ENA);
    REG_WR(VTSS_VOP_OAM_HW_CTRL(voe_idx), v);

    /* LOOPBACK_ENA: */
    v = VTSS_M_VOP_LOOPBACK_ENA_LB_LBM_ENA |
        VTSS_M_VOP_LOOPBACK_ENA_LB_LMM_ENA |
        VTSS_M_VOP_LOOPBACK_ENA_LB_DMM_ENA;
    REG_WR(VTSS_VOP_LOOPBACK_ENA(voe_idx), v);

    /* LOOPBACK_CFG: */
    if (cfg->voe_type == VTSS_OAM_VOE_PORT) {
        v = (VTSS_M_VOP_LOOPBACK_CFG_LB_ES0_ISDX_ENA); /* This is to avoid hitting service blocking ES0 that is of type VID */
        REG_WR(VTSS_VOP_LOOPBACK_CFG(voe_idx), v);
    } else {
        v = (B2B(cfg->loop_clear_dp, VTSS_M_VOP_LOOPBACK_CFG_CLEAR_DP_ON_LOOP) |
             VTSS_M_VOP_LOOPBACK_CFG_LB_ES0_ISDX_ENA |
             VTSS_F_VOP_LOOPBACK_CFG_LB_ISDX(cfg->loop_isdx));
        REG_WR(VTSS_VOP_LOOPBACK_CFG(voe_idx), v);
    }

    /* TST/LB setup: */
    REG_WR(VTSS_VOP_TX_TRANSID_UPDATE(voe_idx), VTSS_M_VOP_TX_TRANSID_UPDATE_TST_UPDATE_ENA | VTSS_M_VOP_TX_TRANSID_UPDATE_LBM_UPDATE_ENA);
    if (cfg->tst.enable) {
        if (doing_tst) {
            /* Don't change anything if we're already running TST frames; it would mess up sequence numbering. */
        } else {
            if (doing_lb) {
                REG_RD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), &vtss_state->oam.voe_internal[voe_idx].tx_next_lbm_transaction_id);
                REG_RD(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), &vtss_state->oam.voe_internal[voe_idx].rx_lbr_transaction_id);
            }
//            REG_WR(VTSS_VOP_TX_TRANSID_UPDATE(voe_idx), B2B(cfg->tst.tx_seq_no_auto_update, VTSS_M_VOP_TX_TRANSID_UPDATE_TST_UPDATE_ENA));
            REG_WR(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), cfg->tst.tx_seq_no);
            REG_WR(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), cfg->tst.rx_seq_no);
            vtss_cmn_counter_32_rebase(cfg->tst.tx_seq_no, &chipcnt->tst.tx_tst);    /* Always rebase when transaction id is changed */
        }
    } else if (cfg->lb.enable) {
        if (doing_lb) {
            /* Don't change anything if we're already running LB frames; it would mess up sequence numbering. */
        } else {
            if (doing_tst) {
                REG_RD(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), &vtss_state->oam.voe_internal[voe_idx].rx_tst_seq_no);
            }
//            REG_WR(VTSS_VOP_TX_TRANSID_UPDATE(voe_idx), B2B(cfg->lb.tx_update_transaction_id, VTSS_M_VOP_TX_TRANSID_UPDATE_LBM_UPDATE_ENA));
            u32 tx_transaction_id = (cfg->lb.tx_transaction_id == 0) ? 1 : cfg->lb.tx_transaction_id;
            REG_WR(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), tx_transaction_id);
            REG_WR(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), tx_transaction_id - 1);
            vtss_cmn_counter_32_rebase(cfg->lb.tx_transaction_id, &chipcnt->lb.tx_lbm);    /* Always rebase when transaction id is changed */
        }
    } else {
//        REG_WR(VTSS_VOP_TX_TRANSID_UPDATE(voe_idx), 0);
    }

    if (cfg->ccm.enable) {
        /* CCM_TX_SEQ_CFG: */
        REG_WR(VTSS_VOP_CCM_TX_SEQ_CFG(voe_idx), cfg->ccm.tx_seq_no);

        /* CCM_RX_SEQ_CFG: */
        REG_WR(VTSS_VOP_CCM_RX_SEQ_CFG(voe_idx), cfg->ccm.rx_seq_no);

        /* CCM_CFG: */
        v = (VTSS_F_VOP_CCM_CFG_CCM_LM_PERIOD(cfg->ccm_lm.enable ? (fa_oam_ccm_lm_period_index(cfg->ccm_lm.period) + 1) : 0) |
             B2B(cfg->ccm.tx_seq_no_auto_update, VTSS_M_VOP_CCM_CFG_CCM_SEQ_UPD_ENA)           |
             B2B(cfg->ccm.rx_seq_no_check, VTSS_M_VOP_CCM_CFG_CCM_RX_SEQ_CHK_ENA)              |
             VTSS_F_VOP_CCM_CFG_CCM_PRIO(cfg->ccm.rx_priority)                                 |
             VTSS_F_VOP_CCM_CFG_CCM_PERIOD(cfg->ccm.rx_period)                                 |
             VTSS_M_VOP_CCM_CFG_CCM_MEGID_CHK_ENA                                              |
             VTSS_M_VOP_CCM_CFG_CCM_MEPID_CHK_ENA);
        REG_WR(VTSS_VOP_CCM_CFG(voe_idx), v);

        /* CCM_MEGID_CFG: */
        p = &cfg->ccm.megid.data[47];    // MSB
        for (i = 0; i < 12; ++i, p -= 4) {
            v = (*(p - 3) << 24) |
                (*(p - 2) << 16) |
                (*(p - 1) <<  8) |
                (*(p - 0));
            REG_WR(VTSS_VOP_CCM_MEGID_CFG(voe_idx, i), v);
        }
    }

    if (cfg->voe_type == VTSS_OAM_VOE_PORT) {
        /* PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=0: */
        for (i = 0, v = 0x88888888; i < 8; ++i) { /* set all "CountEnable=1" */
            v |= (cfg->count.port_cosid_tbl[0][i] & 7) << (4 * i);
        }
        REG_WR(VTSS_VOP_PORT_RX_COSID_MAP(voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), v);
        REG_WR(VTSS_VOP_PORT_TX_COSID_MAP(voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), v);
        /* PORT_RX_COSID_MAP + PORT_TX_COSID_MAP, DEI=1: */
        for (i = 0, v = 0x88888888; i < 8; ++i) { /* set all "CountEnable=1" */
            v |= (cfg->count.port_cosid_tbl[1][i] & 7) << (4 * i);
        }
        REG_WR(VTSS_VOP_PORT_RX_COSID_MAP1(voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), v);
        REG_WR(VTSS_VOP_PORT_TX_COSID_MAP1(voe_idx - VTSS_OAM_PORT_VOE_BASE_IDX), v);
    } else {
        /* COSID_MAP_TABLE_ANA + COSID_MAP_TABLE_REW: */
        for (i = 0, v = 0; i < 8; ++i) {
            v |= (cfg->count.cosid_tbl[i] & 7) << (3 * i);
        }
        REG_WR(VTSS_VOP_COSID_MAP_TABLE_ANA(voe_idx), v);
        REG_WR(VTSS_VOP_COSID_MAP_TABLE_REW(voe_idx), v);

        /* COSID_MAP_CFG_ANA: */
        v = (VTSS_F_VOP_COSID_MAP_CFG_ANA_COSID_SRC_SEL_ANA(cfg->count.cosid_src) |
             VTSS_F_VOP_COSID_MAP_CFG_ANA_COLOR_SRC_SEL_ANA(cfg->count.color_src) |
             B2B(cfg->count.yellow, VTSS_M_VOP_COSID_MAP_CFG_ANA_CNT_YELLOW_ANA));
        REG_WR(VTSS_VOP_COSID_MAP_CFG_ANA(voe_idx), v);

        /* COSID_MAP_CFG_REW: */
        v = (VTSS_F_VOP_COSID_MAP_CFG_REW_COSID_SRC_SEL_REW(cfg->count.cosid_src) |
             VTSS_F_VOP_COSID_MAP_CFG_REW_COLOR_SRC_SEL_REW(cfg->count.color_src) |
             B2B(cfg->count.yellow, VTSS_M_VOP_COSID_MAP_CFG_REW_CNT_YELLOW_REW));
        REG_WR(VTSS_VOP_COSID_MAP_CFG_REW(voe_idx), v);
    }

    if (cfg->sl.enable) {
        /* SLM_CONFIG: */
        v = VTSS_F_VOP_SLM_CONFIG_SLM_PRIO(cfg->sl.priority);
        REG_WR(VTSS_VOP_SLM_CONFIG(voe_idx), v);

        /* SLM_TEST_ID: */
        REG_WR(VTSS_VOP_SLM_TEST_ID(voe_idx), cfg->sl.test_id);

        /* SLM_PEER_LIST: */
        for (i = 0; i < (cfg->sl.count_per_prio ? 1 : 8); ++i) {
            v = VTSS_F_VOP_SLM_PEER_LIST_SLM_PEER_MEPID(cfg->sl.peer_mepid[i]) |
                B2B(cfg->sl.peer_mepid_valid[i], VTSS_M_VOP_SLM_PEER_LIST_SLM_PEER_ENA);
            REG_WR(VTSS_VOP_SLM_PEER_LIST(voe_idx, i), v);
        }
    } else {
        /*
         * we need to specifically disable the SLM configuration - otherwise the switch may
         * still respond to incoming SLM PDUs even though SLM is overall disabled.
         */
        REG_WR(VTSS_VOP_SLM_CONFIG(voe_idx), 0);
        REG_WR(VTSS_VOP_SLM_TEST_ID(voe_idx), 0);
        for (i = 0; i < 8; ++i) {
            REG_WR(VTSS_VOP_SLM_PEER_LIST(voe_idx, i), 0);
        }
    }

    if (cfg->sat.enable) {
        /* SAM_COSID_SEQ_CFG: */
        v = (B2B((cfg->sat.cosid_seq_no_mode == VTSS_OAM_SAT_COSID_SEQ_NO_LB_TST), VTSS_M_VOP_SAM_COSID_SEQ_CFG_PER_COSID_LBM) |
             B2B((cfg->sat.cosid_seq_no_mode == VTSS_OAM_SAT_COSID_SEQ_NO_CCM),    VTSS_M_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CCM) |
             VTSS_F_VOP_SAM_COSID_SEQ_CFG_PER_COSID_CNT_SET(cfg->sat.cosid_seq_no_idx));
        REG_WR(VTSS_VOP_SAM_COSID_SEQ_CFG(voe_idx), v);

        /* SAM_NON_OAM_SEQ_CFG: */
        v = (B2B((cfg->sat.non_oam_seq_no_mode == VTSS_OAM_SAT_NON_OAM_SEQ_NO_INITIATOR), VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_INIT) |
             B2B((cfg->sat.non_oam_seq_no_mode == VTSS_OAM_SAT_NON_OAM_SEQ_NO_RESPONDER), VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RESP) |
             VTSS_F_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_OFFSET_SEQ_NO(cfg->sat.non_oam_seq_no_offs)                                        |
             B2B(cfg->sat.non_oam_upd_udp_chksum, VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_UPD_CHKSUM)                                   |
             B2B(cfg->sat.non_oam_seq_no_rx_err_cnt, VTSS_M_VOP_SAM_NON_OAM_SEQ_CFG_SAM_SEQ_RX_ERR_CNT_ENA));
        REG_WR(VTSS_VOP_SAM_NON_OAM_SEQ_CFG(voe_idx), v);
    }
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_1) {
        /* G_8113_1_CFG: */
        v = (VTSS_F_VOP_G_8113_1_CFG_G_8113_1_INITIATOR_FUNCTION(cfg->g8113_1.lb_initiator_mode) |
             B2B(cfg->g8113_1.lb_check_mepid_megid, VTSS_M_VOP_G_8113_1_CFG_G_8113_1_LBX_MEXID_CHK_ENA));
        REG_WR(VTSS_VOP_G_8113_1_CFG(voe_idx), v);

        /* G_8113_1_REMOTE_MIPIDx: */
        v = ((cfg->g8113_1.mipid.icc_carrier_code[0] << 24) | (cfg->g8113_1.mipid.icc_carrier_code[1] << 16) |
             (cfg->g8113_1.mipid.icc_carrier_code[2] <<  8) | cfg->g8113_1.mipid.icc_carrier_code[3]);
        REG_WR(VTSS_VOP_G_8113_1_REMOTE_MIPID(voe_idx), v);
        v = ((cfg->g8113_1.mipid.icc_carrier_code[4] << 24) | (cfg->g8113_1.mipid.icc_carrier_code[5] << 16) |
             (cfg->g8113_1.mipid.node_id >> 16));
        REG_WR(VTSS_VOP_G_8113_1_REMOTE_MIPID1(voe_idx), v);
        v = (cfg->g8113_1.mipid.node_id << 16) | (cfg->g8113_1.mipid.if_num >> 16);
        REG_WR(VTSS_VOP_G_8113_1_REMOTE_MIPID2(voe_idx), v);
        v = VTSS_F_VOP_G_8113_1_REMOTE_MIPID3_G_8113_1_REMOTE_MIPID3(cfg->g8113_1.mipid.if_num & 0xffff);
        REG_WR(VTSS_VOP_G_8113_1_REMOTE_MIPID3(voe_idx), v);
    }

    REG_RD(VTSS_VOP_VOE_CTRL(voe_idx), &v);
    v = VTSS_F_VOP_VOE_CTRL_MEL_VAL(cfg->proc.meg_level) |
        VTSS_F_VOP_VOE_CTRL_G_8113_1_ENA(cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_1 ? 1 : 0) |
        VTSS_F_VOP_VOE_CTRL_VERIFY_VERSION_ENA(1) |
        VTSS_F_VOP_VOE_CTRL_EXTERN_DM_TSTAMP(cfg->dm.extern_ts ? 1 : 0) |
        VTSS_F_VOP_VOE_CTRL_BLOCK_MEL_HIGH_RX((cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_1 || cfg->block_mel_high) ? 1 : 0) |
        VTSS_F_VOP_VOE_CTRL_SAT_TEST_VOE(cfg->sat_test ? 1 : 0);
    switch (cfg->proc.dmac_check_type) {
    case VTSS_OAM_DMAC_CHECK_NONE:
        v |= VTSS_F_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(0);
        break;
    case VTSS_OAM_DMAC_CHECK_UNICAST:
        v |= VTSS_F_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(1);
        break;
    case VTSS_OAM_DMAC_CHECK_MULTICAST:
        v |= VTSS_F_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(2);
        break;
    case VTSS_OAM_DMAC_CHECK_BOTH:
        v |= VTSS_F_VOP_VOE_CTRL_RX_DMAC_CHK_SEL(3);
        break;
    }
    REG_WR(VTSS_VOP_VOE_CTRL(voe_idx), v);

    REG_WRM(VTSS_VOP_VOE_COMMON_CFG(voe_idx), VTSS_F_VOP_VOE_COMMON_CFG_UPMEP_ENA(cfg->mep_type == VTSS_OAM_UPMEP ? 1 : 0), VTSS_M_VOP_VOE_COMMON_CFG_UPMEP_ENA);

    /* VOE_MISC_CONFIGL. Comes last, as this is where we enable the VOE */
    v = VTSS_F_VOP_VOE_MISC_CONFIG_VOE_ENA(cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_2 ? 2 : 1) |
        VTSS_F_VOP_VOE_MISC_CONFIG_LM_CNT_BYTE(0) | /* feature not 100% supported and tested... */
        VTSS_F_VOP_VOE_MISC_CONFIG_SL_ENA(cfg->sl.enable) |
        VTSS_F_VOP_VOE_MISC_CONFIG_BLK_ENA((cfg->aBlk ? 2 : 0) | (cfg->admin_locked ? 1 : 0));
    REG_WR(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), v);

    for (i = 0, v = 0, v_slm = 0; i < 8; ++i) {
        v |= cfg->proc.auto_copy_next_sl_peer[i] ? (1 << i) : 0;
        v_slm |= cfg->proc.auto_copy_next_slm_peer[i] ? (1 << i) : 0;
    }
    v = (VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_SLOT(voe_idx & 7)                                           | /* always using all 8 HMO slots */
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_CCM_NXT(cfg->proc.auto_copy_next_valid_ccm)          |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_TLV_NON_ZERO(cfg->proc.auto_copy_on_ccm_tlv_nonzero) |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CCM_RX_BAD_NXT(cfg->proc.auto_copy_on_ccm_err)              |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_RX_TEST_FRM_NXT(cfg->proc.auto_copy_next_tst_or_lbr)        |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLM(v_slm)                                  |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_EXTRACT_PEER_RX_SLR(v)                                      |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_BAD_NXT(cfg->proc.auto_copy_on_ais_err)              |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_AIS_RX_FRM_NXT(cfg->proc.auto_copy_next_valid_ais)          |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_BAD_NXT(cfg->proc.auto_copy_on_lck_err)              |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_LCK_RX_FRM_NXT(cfg->proc.auto_copy_next_valid_lck)          |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_BAD_NXT(cfg->proc.auto_copy_on_csf_err)              |
         VTSS_F_VOP_AUTO_HIT_ME_ONCE_HMO_CSF_RX_FRM_NXT(cfg->proc.auto_copy_next_valid_csf));
    REG_WR(VTSS_VOP_AUTO_HIT_ME_ONCE(voe_idx), v);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MPLS)
static vtss_rc fa_oam_voe_arm_hitme_mpls(vtss_state_t *vtss_state,
                                         const vtss_oam_voe_idx_t voe_idx,
                                         const BOOL               enable)
{
    u32 v = 0;
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);

    if (cfg->proc.copy_next_only) {
        v = B2B(cfg->proc.copy_next_only, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_EXTRACT_HIT_ME_ONCE) |
            B2B(cfg->proc.copy_next_cc_rx, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CC_RX_NEXT_GOOD_EXTR) |
            B2B(cfg->proc.copy_next_cv_rx, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_CV_RX_NEXT_GOOD_EXTR) |
            B2B(cfg->proc.copy_next_rx_param_change, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_PARAM_CHANGE_EXTR) |
            B2B(cfg->proc.copy_next_rx_poll_flag, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_P_SET_EXTR) |
            B2B(cfg->proc.copy_next_rx_final_flag, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_F_SET_EXTR) |
            B2B(cfg->proc.copy_next_rx_error, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_RX_ERR_EXTR) |
            B2B(cfg->proc.copy_next_tx_error, VTSS_M_VOP_MPLS_PDU_EXTRACT_MPLS_BFD_TX_ERR_EXTR);

        REG_WRM(VTSS_VOP_MPLS_PDU_EXTRACT_MPLS(voe_idx), v, v);
    }

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_oam_voe_arm_hitme(vtss_state_t *vtss_state,
                                    const vtss_oam_voe_idx_t voe_idx,
                                    const BOOL               enable)
{
    u32 v = 0;
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);

#if defined(VTSS_FEATURE_MPLS)
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_2)
        return fa_oam_voe_arm_hitme_mpls(vtss_state, voe_idx, enable);
#endif

    if (cfg->proc.copy_next_only) {
        v = B2B(cfg->proc.copy_next_only,           VTSS_M_VOP_PDU_EXTRACT_EXTRACT_HIT_ME_ONCE)         |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_ZERO_PERIOD_RX_ERR_EXTR) |
            B2B(cfg->proc.copy_on_mel_too_low_err,  VTSS_M_VOP_PDU_EXTRACT_RX_MEL_LOW_ERR_EXTR)         |
            B2B(cfg->proc.copy_on_mel_too_high_err, VTSS_M_VOP_PDU_EXTRACT_RX_MEL_HIGH_BLOCK_EXTR)      |
            B2B(cfg->proc.copy_on_dmac_err,         VTSS_M_VOP_PDU_EXTRACT_DMAC_RX_ERR_EXTR)            |
            B2B(cfg->proc.copy_on_version_err,      VTSS_M_VOP_PDU_EXTRACT_PDU_VERSION_RX_ERR_EXTR)     |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEGID_RX_ERR_EXTR)       |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_MEPID_RX_ERR_EXTR)       |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PERIOD_RX_ERR_EXTR)      |
            B2B(cfg->proc.copy_on_ccm_err,          VTSS_M_VOP_PDU_EXTRACT_CCM_PRIO_RX_ERR_EXTR)        |
            B2B(cfg->proc.copy_on_ccm_tlv_nonzero,  VTSS_M_VOP_PDU_EXTRACT_CCM_RX_TLV_NON_ZERO_EXTR)    |
            B2B(cfg->proc.copy_next_valid_ccm,      VTSS_M_VOP_PDU_EXTRACT_CCM_RX_CCM_NXT_EXTR)         |
            B2B(cfg->proc.copy_next_tst_or_lbr,     VTSS_M_VOP_PDU_EXTRACT_RX_TEST_FRM_NXT_EXTR)        |
            B2B(cfg->proc.copy_on_tx_block_err,     VTSS_M_VOP_PDU_EXTRACT_TX_BLOCK_ERR_EXTR)           |
            B2B(cfg->proc.copy_on_sat_seq_err,      VTSS_M_VOP_PDU_EXTRACT_SAM_RX_SEQ_ERR_EXTR)         |
            B2B(cfg->proc.copy_on_g8113_1_lbm_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBM_RX_ERR_EXTR)    |
            B2B(cfg->proc.copy_on_g8113_1_lbr_err,  VTSS_M_VOP_PDU_EXTRACT_G_8113_1_LBR_RX_ERR_EXTR)    |
            B2B(cfg->proc.copy_on_sl_err,           VTSS_M_VOP_PDU_EXTRACT_SL_ERR_EXTR)                 |
            B2B(cfg->proc.copy_on_ais_err,          VTSS_M_VOP_PDU_EXTRACT_AIS_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_ais,      VTSS_M_VOP_PDU_EXTRACT_AIS_RX_FRM_NXT_EXTR)         |
            B2B(cfg->proc.copy_on_lck_err,          VTSS_M_VOP_PDU_EXTRACT_LCK_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_lck,      VTSS_M_VOP_PDU_EXTRACT_LCK_RX_FRM_NXT_EXTR)         |
            B2B(cfg->proc.copy_on_csf_err,          VTSS_M_VOP_PDU_EXTRACT_CSF_ERR_EXTR)                |
            B2B(cfg->proc.copy_next_valid_csf,      VTSS_M_VOP_PDU_EXTRACT_CSF_RX_FRM_NXT_EXTR);

        REG_WRM(VTSS_VOP_PDU_EXTRACT(voe_idx), v, v);
    }

    // Control extraction of SL peer PDUs (note: NOT controlled by proc.copy_next_only!)
    v = VTSS_M_VOP_SYNLM_EXTRACT_EXTRACT_HMO |
        (cfg->proc.copy_next_sl_peer[0] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  1) : 0) |
        (cfg->proc.copy_next_sl_peer[1] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  2) : 0) |
        (cfg->proc.copy_next_sl_peer[2] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  4) : 0) |
        (cfg->proc.copy_next_sl_peer[3] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(  8) : 0) |
        (cfg->proc.copy_next_sl_peer[4] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 16) : 0) |
        (cfg->proc.copy_next_sl_peer[5] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 32) : 0) |
        (cfg->proc.copy_next_sl_peer[6] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR( 64) : 0) |
        (cfg->proc.copy_next_sl_peer[7] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLR(128) : 0) |
        (cfg->proc.copy_next_slm_peer[0] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  1) : 0) |
        (cfg->proc.copy_next_slm_peer[1] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  2) : 0) |
        (cfg->proc.copy_next_slm_peer[2] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  4) : 0) |
        (cfg->proc.copy_next_slm_peer[3] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(  8) : 0) |
        (cfg->proc.copy_next_slm_peer[4] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 16) : 0) |
        (cfg->proc.copy_next_slm_peer[5] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 32) : 0) |
        (cfg->proc.copy_next_slm_peer[6] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM( 64) : 0) |
        (cfg->proc.copy_next_slm_peer[7] ? VTSS_F_VOP_SYNLM_EXTRACT_EXTRACT_PEER_RX_SLM(128) : 0);

    REG_WRM(VTSS_VOP_SYNLM_EXTRACT(voe_idx), v, v);

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_voe_ccm_set_rdi_flag(vtss_state_t *vtss_state,
                                           const vtss_oam_voe_idx_t voe_idx,
                                           const BOOL               flag)
{
    REG_WRM(VTSS_VOP_CCM_STAT(voe_idx), (flag) ? VTSS_M_VOP_CCM_STAT_CCM_TX_RDI : 0, VTSS_M_VOP_CCM_STAT_CCM_TX_RDI);
    return VTSS_RC_OK;
}

static vtss_rc fa_oam_ccm_status_get(vtss_state_t *vtss_state,
                                     const vtss_oam_voe_idx_t voe_idx,
                                     vtss_oam_ccm_status_t    *value)
{
    u32                 v;
    vtss_phys_port_no_t chip_port;
    vtss_port_no_t port_no;

    REG_RD(VTSS_VOP_CCM_RX_LAST(voe_idx), &v);
    chip_port = VTSS_X_VOP_CCM_RX_LAST_CCM_RX_SRC_PORT(v);
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (VTSS_CHIP_PORT_FROM_STATE(vtss_state, port_no) == chip_port) {
            break;
        }
    }
    value->rx_port               = (port_no < vtss_state->port_count) ? port_no : VTSS_PORT_NO_NONE;
    value->port_status_tlv_value = VTSS_X_VOP_CCM_RX_LAST_TLV_PORT_STATUS(v);
    value->if_status_tlv_value   = VTSS_X_VOP_CCM_RX_LAST_TLV_INTERFACE_STATUS(v);
    value->period_err            = VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_PERIOD_DEFECT(v)  != 0;
    value->priority_err          = VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_PRIO_DEFECT(v)    != 0;
    value->zero_period_err       = VTSS_X_VOP_CCM_RX_LAST_CCM_ZERO_PERIOD_ERR(v)      != 0;
    value->rx_rdi                = VTSS_X_VOP_CCM_RX_LAST_CCM_RX_RDI(v)               != 0;
    value->loc                   = VTSS_X_VOP_CCM_RX_LAST_CCM_LOC_DEFECT(v)           != 0;
    value->mep_id_err            = VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_MEPID_DEFECT(v)   != 0;
    value->meg_id_err            = VTSS_X_VOP_CCM_RX_LAST_CCM_UNEXP_MEGID_DEFECT(v)   != 0;
    value->mel_low_err           = VTSS_X_VOP_CCM_RX_LAST_CCM_RX_MEL_LOW_DEFECT(v)    != 0;

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_pdu_status_get(vtss_state_t *vtss_state,
                                     const vtss_oam_voe_idx_t voe_idx,
                                     vtss_oam_pdu_status_t    *value)
{
    u32                 v;

    REG_RD(VTSS_VOP_AIS_RX_LAST(voe_idx), &v);
    value->ais.zero_period_err = VTSS_X_VOP_AIS_RX_LAST_AIS_ZERO_PERIOD_ERR(v) != 0;
    value->ais.defect          = VTSS_X_VOP_AIS_RX_LAST_AIS_DEFECT(v) != 0;

    REG_RD(VTSS_VOP_LCK_RX_LAST(voe_idx), &v);
    value->lck.zero_period_err = VTSS_X_VOP_LCK_RX_LAST_LCK_ZERO_PERIOD_ERR(v) != 0;
    value->lck.defect          = VTSS_X_VOP_LCK_RX_LAST_LCK_DEFECT(v) != 0;

    memset(&value->csf, 0, sizeof(value->csf));
    REG_RD(VTSS_VOP_CSF_RX_LAST(voe_idx), &v);
    if (VTSS_X_VOP_CSF_RX_LAST_CSF_DEFECT(v)) { /* CSF defect is active */
        value->csf.zero_period_err = VTSS_X_VOP_CSF_RX_LAST_CSF_ZERO_PERIOD_ERR(v) != 0;
        value->csf.type_err        = VTSS_X_VOP_CSF_RX_LAST_CSF_INVLD_CSF_TYPE_ERR(v) != 0;
        value->csf.los_defect      = VTSS_X_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE(v) == 0;    /* Note that receiving DCI (3) will result in cleared defects */
        value->csf.fdi_defect      = VTSS_X_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE(v) == 1;
        value->csf.rdi_defect      = VTSS_X_VOP_CSF_RX_LAST_CSF_RX_CSF_TYPE(v) == 2;
    }

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MPLS)
static vtss_rc fa_oam_pdu_seen_status_get_mpls(vtss_state_t *vtss_state,
                                               const vtss_oam_voe_idx_t   voe_idx,
                                               vtss_oam_pdu_seen_status_t *value)
{
    u32 i, v, mask;

    REG_RD(VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(voe_idx), &v);
    for (i = 0; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i) {
        value->generic_seen[i] = (VTSS_X_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK(v) & (1 << i)) != 0;
    }

    value->unknown_seen = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY) != 0;
    value->bfd_cc_seen  = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY)  != 0;
    value->bfd_cv_seen  = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY)  != 0;

    mask = (VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK |
            VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY          |
            VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY           |
            VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY);

    REG_WR(VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(voe_idx), mask);

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_oam_pdu_seen_status_get(vtss_state_t *vtss_state,
                                          const vtss_oam_voe_idx_t   voe_idx,
                                          vtss_oam_pdu_seen_status_t *value)
{
    u32 i, v, mask;

#if defined(VTSS_FEATURE_MPLS)
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);
    if (cfg->proc.pdu_type == VTSS_OAM_PDU_G8113_2)
        return fa_oam_pdu_seen_status_get_mpls(vtss_state, voe_idx, value);
#endif

    REG_RD(VTSS_VOP_OAM_RX_STICKY2(voe_idx), &v);
    for (i = 0; i < VTSS_OAM_GENERIC_OPCODE_CFG_CNT; ++i) {
        value->generic_seen[i] = (VTSS_X_VOP_OAM_RX_STICKY2_GENERIC_RX_STICKY_MASK(v) & (1 << i)) != 0;
    }
    mask = (VTSS_M_VOP_OAM_RX_STICKY2_GENERIC_RX_STICKY_MASK);

    REG_WR(VTSS_VOP_OAM_RX_STICKY2(voe_idx), mask);

    REG_RD(VTSS_VOP_OAM_RX_STICKY(voe_idx), &v);
    value->unknown_seen = (v & VTSS_M_VOP_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY) != 0;
    value->ltm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LTM_RX_STICKY)        != 0;
    value->ltr_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LTR_RX_STICKY)        != 0;
    value->lmm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LMM_RX_STICKY)        != 0;
    value->lmr_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LMR_RX_STICKY)        != 0;
    value->tst_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_TST_RX_STICKY)        != 0;
    value->lbm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LBM_RX_STICKY)        != 0;
    value->lbr_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LBR_RX_STICKY)        != 0;
    value->dmm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_DMM_RX_STICKY)        != 0;
    value->dmr_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_DMR_RX_STICKY)        != 0;
    value->one_dm_seen  = (v & VTSS_M_VOP_OAM_RX_STICKY_SDM_RX_STICKY)        != 0;
    value->ccm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_STICKY)        != 0;
    value->ccm_lm_seen  = (v & VTSS_M_VOP_OAM_RX_STICKY_CCM_LM_RX_STICKY)     != 0;
    value->slm_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_SLM_RX_STICKY)        != 0;
    value->slr_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_SLR_RX_STICKY)        != 0;
    value->one_sl_seen  = (v & VTSS_M_VOP_OAM_RX_STICKY_SL1_RX_STICKY)        != 0;
    value->ais_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_AIS_RX_STICKY)        != 0;
    value->lck_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_LCK_RX_STICKY)        != 0;
    value->csf_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_CSF_RX_STICKY)        != 0;

    mask = (VTSS_M_VOP_OAM_RX_STICKY_UNK_OPCODE_RX_STICKY   |
            VTSS_M_VOP_OAM_RX_STICKY_LTM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_LTR_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_LMM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_LMR_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_TST_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_LBM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_LBR_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_DMM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_DMR_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_SDM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_CCM_LM_RX_STICKY       |
            VTSS_M_VOP_OAM_RX_STICKY_SLM_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_SLR_RX_STICKY          |
            VTSS_M_VOP_OAM_RX_STICKY_SL1_RX_STICKY);

    REG_WR(VTSS_VOP_OAM_RX_STICKY(voe_idx), mask);

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_MPLS)
static vtss_rc fa_oam_proc_status_get_mpls(vtss_state_t             *vtss_state,
                                           const vtss_oam_voe_idx_t voe_idx,
                                           vtss_oam_proc_status_t   *value)
{
    VTSS_D("Enter VOE %d", voe_idx);
    u32 v;

    REG_RD(VTSS_VOP_MPLS_BFD_SRC_INFO(voe_idx), &v);
    value->bfd_src_info_local_state     = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_STATE_SRC(v);
    value->bfd_src_info_remote_state    = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_STATE_SRC(v);
    value->bfd_src_info_local_diag      = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DIAG_SRC(v);
    value->bfd_src_info_remote_diag     = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DIAG_SRC(v);
    value->bfd_src_info_local_dm        = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_LOCAL_DM_SRC(v);
    value->bfd_src_info_remote_dm       = VTSS_X_VOP_MPLS_BFD_SRC_INFO_BFD_REMOTE_DM_SRC(v);

    REG_RD(VTSS_VOP_MPLS_BFD_SINK_INFO(voe_idx), &v);
    value->bfd_sink_info_local_state    = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_STATE_SINK(v);
    value->bfd_sink_info_remote_state   = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_STATE_SINK(v);
    value->bfd_sink_info_local_diag     = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DIAG_SINK(v);
    value->bfd_sink_info_remote_diag    = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DIAG_SINK(v);
    value->bfd_sink_info_local_dm       = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_LOCAL_DM_SINK(v);
    value->bfd_sink_info_remote_dm      = VTSS_X_VOP_MPLS_BFD_SINK_INFO_BFD_REMOTE_DM_SINK(v);

    REG_RD(VTSS_VOP_MPLS_BFD_STAT(voe_idx), &v);
    value->bfd_miss_count               = VTSS_X_VOP_MPLS_BFD_STAT_BFD_MISS_CNT(v);
    REG_RD(VTSS_VOP_MPLS_BFD_RX_LAST(voe_idx), &v);
    value->bfd_rx_last_loc_defect       = VTSS_X_VOP_MPLS_BFD_RX_LAST_BFD_LOC_DEFECT(v);

    REG_RD(VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(voe_idx), &v);
    value->rx_g8113_2_generic_seen      = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK) != 0;
    value->rx_g8113_2_unknown_seen      = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY) != 0;
    value->bfd_rx_cv_seen               = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY) != 0;
    value->bfd_rx_cc_seen               = (v & VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY) != 0;
    v = (VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_GENERIC_CPT_RX_STICKY_MASK |
         VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_UNK_CPT_RX_STICKY          |
         VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CC_RX_STICKY           |
         VTSS_M_VOP_MPLS_CPT_RX_STICKY_MPLS_BFD_CV_RX_STICKY);
    REG_WR(VTSS_VOP_MPLS_CPT_RX_STICKY_MPLS(voe_idx), v);


    REG_RD(VTSS_VOP_MPLS_BFD_RX_STICKY(voe_idx), &v);
    value->bfd_rx_version_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY) != 0;
    value->bfd_rx_min_len_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY) != 0;
    value->bfd_rx_max_len_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY) != 0;
    value->bfd_rx_dm_zero_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY) != 0;
    value->bfd_rx_m_bit_set_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY) != 0;
    value->bfd_rx_my_discr_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY) != 0;
    value->bfd_rx_your_discr_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY) != 0;
    value->bfd_rx_auth_mismatch_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY) != 0;
    value->bfd_rx_d_bit_set_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY) != 0;
    value->bfd_rx_p_and_f_bit_set_err_seen = (v & VTSS_M_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY) != 0;
    v = (VTSS_M_VOP_MPLS_BFD_RX_STICKY_VERSION_ERR_STICKY       |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_MIN_LEN_ERR_STICKY       |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_MAX_LEN_ERR_STICKY       |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_DM_ZERO_ERR_STICKY       |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_M_BIT_SET_ERR_STICKY     |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_MY_DISCR_ERR_STICKY      |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_YOUR_DISCR_ERR_STICKY    |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_AUTH_MISMATCH_ERR_STICKY |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_D_BIT_SET_ERR_STICKY     |
         VTSS_M_VOP_MPLS_BFD_RX_STICKY_P_AND_F_BIT_SET_ERR_STICKY);
    REG_WR(VTSS_VOP_MPLS_BFD_RX_STICKY(voe_idx), v);

    REG_RD(VTSS_VOP_MPLS_BFD_TX_STICKY(voe_idx), &v);
    value->bfd_tx_my_discr_mismatch_seen = (v & VTSS_M_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH) != 0;
    v = VTSS_M_VOP_MPLS_BFD_TX_STICKY_TX_MY_DISCR_MISMATCH;
    REG_WR(VTSS_VOP_MPLS_BFD_TX_STICKY(voe_idx), v);

    return VTSS_RC_OK;
}
#endif

static vtss_rc fa_oam_proc_status_get(vtss_state_t             *vtss_state,
                                      const vtss_oam_voe_idx_t voe_idx,
                                      vtss_oam_proc_status_t   *value)
{
    u32 v;
    BOOL doing_lb = 0, doing_tst = 0;

    VTSS_D("Enter VOE %d", voe_idx);

#if defined(VTSS_FEATURE_MPLS)
    REG_RD(VTSS_VOP_VOE_MISC_CONFIG(voe_idx), &v);
    if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 2)
        return fa_oam_proc_status_get_mpls(vtss_state, voe_idx, value);
#endif

    REG_RD(VTSS_VOP_CCM_RX_SEQ_CFG(voe_idx), &value->rx_ccm_seq_no);
    REG_RD(VTSS_VOP_CCM_TX_SEQ_CFG(voe_idx), &value->tx_next_ccm_seq_no);

    VTSS_RC(doing_calculate(vtss_state, voe_idx, &doing_lb, &doing_tst));

    if (doing_tst) {
        value->tx_next_lbm_transaction_id = vtss_state->oam.voe_internal[voe_idx].tx_next_lbm_transaction_id;
        value->rx_lbr_transaction_id = vtss_state->oam.voe_internal[voe_idx].rx_lbr_transaction_id;
        REG_RD(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), &value->rx_tst_seq_no);
    }
    if (doing_lb) {
        value->rx_tst_seq_no = vtss_state->oam.voe_internal[voe_idx].rx_tst_seq_no;
        REG_RD(VTSS_VOP_LBM_TX_TRANSID_CFG(voe_idx), &value->tx_next_lbm_transaction_id);
        REG_RD(VTSS_VOP_LBR_RX_TRANSID_CFG(voe_idx), &value->rx_lbr_transaction_id);
    }

    REG_RD(VTSS_VOP_OAM_TX_STICKY(voe_idx), &v);
    value->tx_meg_level_err_seen    = (v & VTSS_M_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY)    != 0;
    value->tx_sl_prio_err_seen      = (v & VTSS_M_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY) != 0;
    REG_WR(VTSS_VOP_OAM_TX_STICKY(voe_idx), VTSS_M_VOP_OAM_TX_STICKY_TX_BLOCK_ERR_STICKY | VTSS_M_VOP_OAM_TX_STICKY_TX_SLM_PRIO_ERR_STICKY);

    REG_RD(VTSS_VOP_OAM_RX_STICKY(voe_idx), &v);
    value->rx_dmac_err_seen         = (v & VTSS_M_VOP_OAM_RX_STICKY_DMAC_RX_ERR_STICKY)         != 0;
    value->rx_sat_seq_seen          = (v & VTSS_M_VOP_OAM_RX_STICKY_NON_OAM_SEQ_RX_STICKY)      != 0;
    value->rx_lbr_trans_id_err_seen = (v & VTSS_M_VOP_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY)     != 0;
    value->rx_version_err_seen      = (v & VTSS_M_VOP_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY)  != 0;
    value->rx_ccm_tlv_nonzero_seen  = (v & VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY) != 0;
    value->rx_ccm_seq_err_seen      = (v & VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY)      != 0;
    value->rx_mel_low_err_seen      = (v & VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY)    != 0;
    value->rx_mel_high_err_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY)   != 0;
    v = (VTSS_M_VOP_OAM_RX_STICKY_DMAC_RX_ERR_STICKY         |
         VTSS_M_VOP_OAM_RX_STICKY_NON_OAM_SEQ_RX_STICKY      |
         VTSS_M_VOP_OAM_RX_STICKY_LBR_TRANSID_ERR_STICKY     |
         VTSS_M_VOP_OAM_RX_STICKY_PDU_VERSION_RX_ERR_STICKY  |
         VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_TLV_NON_ZERO_STICKY |
         VTSS_M_VOP_OAM_RX_STICKY_CCM_RX_SEQ_ERR_STICKY      |
         VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_LOW_BLOCK_STICKY    |
         VTSS_M_VOP_OAM_RX_STICKY_RX_MEL_HIGH_BLOCK_STICKY);
    REG_WR(VTSS_VOP_OAM_RX_STICKY(voe_idx), v);

    REG_RD(VTSS_VOP_OAM_RX_STICKY2(voe_idx), &v);
    value->rx_sl_test_id_err_seen         = (v & VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_TESTID_ERR_STICKY)               != 0;
    value->rx_sl_prio_err_seen            = (v & VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_PRIO_ERR_STICKY)                 != 0;
    value->rx_sl_mepid_err_seen           = (v & VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_MEPID_ERR_STICKY)                != 0;
    value->rx_slr_ini_mepid_err_seen      = (v & VTSS_M_VOP_OAM_RX_STICKY2_RX_INI_ILLEGAL_MEPID_STICKY)            != 0;
    value->rx_g8113_1_lb_tlv_err_seen     = (v & VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_MISSING_TLV_STICKY)     != 0;
    value->rx_g8113_1_lb_subtype_err_seen = (v & VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY) != 0;
    value->rx_g8113_1_lb_id_err_seen      = (v & VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY)   != 0;
    value->rx_g8113_1_lbr_lbk_err_seen    = (v & VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBR_RX_ILL_LBK_IND_STICKY)     != 0;
    v = (VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_TESTID_ERR_STICKY               |
         VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_PRIO_ERR_STICKY                 |
         VTSS_M_VOP_OAM_RX_STICKY2_RX_SLM_MEPID_ERR_STICKY                |
         VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_MISSING_TLV_STICKY     |
         VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_SUBTYPE_STICKY |
         VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBX_RX_ILLEGAL_MEXID_STICKY   |
         VTSS_M_VOP_OAM_RX_STICKY2_G_8113_1_LBR_RX_ILL_LBK_IND_STICKY     |
         VTSS_M_VOP_OAM_RX_STICKY2_RX_INI_ILLEGAL_MEPID_STICKY);
    REG_WR(VTSS_VOP_OAM_RX_STICKY2(voe_idx), v);
    return VTSS_RC_OK;
}

static vtss_rc fa_oam_voe_counter_update(vtss_state_t *vtss_state,
                                         const vtss_oam_voe_idx_t voe_idx)
{
    return oam_voe_counter_update_internal(vtss_state, voe_idx, 0);
}

#define SET(v) value->v = chipcnt->v.value
static vtss_rc fa_oam_voe_counter_get(vtss_state_t *vtss_state,
                                      const vtss_oam_voe_idx_t voe_idx,
                                      vtss_oam_voe_counter_t   *value)
{
    vtss_rc rc = VTSS_RC_OK;
    u32 i;
    const vtss_oam_voe_internal_counters_t *chipcnt = &vtss_state->oam.voe_internal[voe_idx].counters;

    VTSS_D("Enter VOE %d", voe_idx);

    /* Poll so we get the most recent values */
    rc = oam_voe_counter_update_internal(vtss_state, voe_idx, 0);

    /* SL: */

    SET(sl.tx_slm);
    for (i = 0; i < 8; ++i) {
        SET(sl.rx_slr[i]);
        SET(sl.tx_slr[i]);
    }

    /* LM: */

    for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
        SET(lm.lm_count[i].rx);
        SET(lm.lm_count[i].tx);
    }

    SET(lm.tx_lmm);
    SET(lm.tx_lmr);
    SET(lm.rx_lmm);
    SET(lm.rx_lmr);

    REG_RD(VTSS_VOP_CCM_TX_FCB_CFG(voe_idx), &value->lm.tx_FCf);
    REG_RD(VTSS_VOP_CCM_RX_FCB_CFG(voe_idx), &value->lm.rx_FCl);

    /* CCM: */

    SET(ccm.rx_valid_count);
    SET(ccm.rx_invalid_count);
    SET(ccm.rx_invalid_seq_no);
    SET(ccm.rx_invalid_period);
    SET(ccm.rx_invalid_mel);
    SET(ccm.rx_invalid_megid);
    SET(ccm.rx_invalid_mepid);

    /* LB: */

    SET(lb.rx_lbr);
    SET(lb.tx_lbm);
    SET(lb.rx_lbr_trans_id_err);
    SET(lb.rx_lbr_crc_err);
    SET(lb.tx_lbr);

    /* TST: */

    SET(tst.rx_tst);
    SET(tst.tx_tst);
    SET(tst.rx_tst_trans_id_err);
    SET(tst.rx_tst_crc_err);

    /* DM: */

    SET(dm.tx_dmm);
    SET(dm.tx_dmr);
    SET(dm.rx_dmm);
    SET(dm.rx_dmr);

#if defined(VTSS_FEATURE_MPLS)
    /* BFD: */
    SET(bfd.rx_cc_valid);
    SET(bfd.rx_cv_valid);
    SET(bfd.rx_cc_invalid);
    SET(bfd.rx_cv_invalid);
    SET(bfd.tx_cc);
    SET(bfd.tx_cv);
    SET(bfd.rx_selected);
    SET(bfd.rx_nonselected);
    SET(bfd.tx_selected);
    SET(bfd.tx_nonselected);
#endif

    /* Selected: */

    SET(sel.selected_frames.rx);
    SET(sel.selected_frames.tx);
    SET(sel.nonselected_frames.rx);
    SET(sel.nonselected_frames.tx);

    /* Discard: */

    SET(discard.tx);
    SET(discard.rx);

    return rc;
}
#undef SET

static vtss_rc fa_oam_voe_counter_clear(vtss_state_t *vtss_state,
                                        const vtss_oam_voe_idx_t voe_idx, const u32 mask)
{
    /* Poll & clear */
    VTSS_D("Enter VOE %d  mask %X", voe_idx, mask);

    return oam_voe_counter_update_internal(vtss_state, voe_idx, mask);
}

static u32 down_mip_alloc_ix = 0, up_mip_alloc_ix = 0;
static vtss_rc fa_oam_mip_alloc(vtss_state_t *vtss_state,
                                const vtss_oam_mip_type_t type,
                                vtss_oam_mip_idx_t        *mip_idx)
{
    u32 i;
    if (type == VTSS_OAM_DOWNMIP) {
        for (i = 0; i < VTSS_OAM_DOWN_MIP_CNT && vtss_state->oam.down_mip_allocated[down_mip_alloc_ix]; ++i) {
            down_mip_alloc_ix = (down_mip_alloc_ix + 1) % VTSS_OAM_DOWN_MIP_CNT;
        }
        if (i == VTSS_OAM_DOWN_MIP_CNT) {
            return VTSS_RC_ERROR;
        }
        vtss_state->oam.down_mip_allocated[down_mip_alloc_ix] = TRUE;
        i = down_mip_alloc_ix;
    } else {
        for (i = 0; i < VTSS_OAM_UP_MIP_CNT && vtss_state->oam.up_mip_allocated[up_mip_alloc_ix]; ++i) {
            up_mip_alloc_ix = (up_mip_alloc_ix + 1) % VTSS_OAM_UP_MIP_CNT;
        }
        if (i == VTSS_OAM_UP_MIP_CNT) {
            return VTSS_RC_ERROR;
        }
        vtss_state->oam.up_mip_allocated[up_mip_alloc_ix] = TRUE;
        i = up_mip_alloc_ix+1;  /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
    }

    *mip_idx = i;

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_mip_free(vtss_state_t *vtss_state,
                               const vtss_oam_mip_type_t type,
                               const vtss_oam_mip_idx_t  mip_idx)
{
    if (type == VTSS_OAM_DOWNMIP && vtss_state->oam.down_mip_allocated[mip_idx]) {
        vtss_state->oam.down_mip_allocated[mip_idx] = FALSE;
        down_mip_alloc_ix = mip_idx;

        /* disable down MIP: */
        REG_WR(VTSS_ANA_CL_MIP_CFG(mip_idx), 0);
        REG_WR(VTSS_ANA_CL_CCM_HMO_CTRL(mip_idx), 0);
        REG_WR(VTSS_ANA_CL_MIP_CL_VID_CTRL(mip_idx), 0);
        REG_WR(VTSS_ANA_CL_LBM_MAC_HIGH(mip_idx), 0);
        REG_WR(VTSS_ANA_CL_LBM_MAC_LOW(mip_idx), 0);

    } else if (type == VTSS_OAM_UPMIP && vtss_state->oam.up_mip_allocated[mip_idx-1]) {
        up_mip_alloc_ix = mip_idx-1;
        vtss_state->oam.up_mip_allocated[up_mip_alloc_ix] = FALSE;

        /* disable up MIP: */
        /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
        REG_WR(VTSS_REW_MIP_CFG(mip_idx), 0);
        REG_WR(VTSS_REW_CCM_HMO_CTRL(mip_idx), 0);
        REG_WR(VTSS_REW_MIP_VID_CTRL(mip_idx), 0);
        REG_WR(VTSS_REW_LBM_MAC_HIGH(mip_idx), 0);
        REG_WR(VTSS_REW_LBM_MAC_LOW(mip_idx), 0);
    }
    return VTSS_RC_OK;
}

static vtss_rc fa_oam_mip_cfg_set(vtss_state_t *vtss_state,
                                  const vtss_oam_mip_type_t        type,
                                  const vtss_oam_mip_idx_t         mip_idx)
{
    const vtss_oam_mip_conf_t *cfg;
    u32 v;

    if (type == VTSS_OAM_DOWNMIP) {
        cfg = &(vtss_state->oam.down_mip_conf[mip_idx]);
        v = (VTSS_F_ANA_CL_MIP_CFG_MEL_VAL(cfg->meg_level)                   |
             B2B(cfg->ccm_copy_to_cpu, VTSS_M_ANA_CL_MIP_CFG_CCM_COPY_ENA)   |
             B2B(cfg->lbm_redir_to_cpu, VTSS_M_ANA_CL_MIP_CFG_LBM_REDIR_ENA) |
             B2B(cfg->ltm_redir_to_cpu, VTSS_M_ANA_CL_MIP_CFG_LTM_REDIR_ENA) |
             VTSS_F_ANA_CL_MIP_CFG_RAPS_CFG(cfg->raps_action)                |
             VTSS_F_ANA_CL_MIP_CFG_GENERIC_OPCODE_VAL(cfg->generic_opcode)   |
             VTSS_F_ANA_CL_MIP_CFG_GENERIC_OPCODE_CFG(cfg->generic_action)   |
             VTSS_F_ANA_CL_MIP_CFG_CPU_MIP_QU(cfg->cpu_queue)                |
             VTSS_F_ANA_CL_MIP_CFG_PIPELINE_PT(cfg->location));
        REG_WR(VTSS_ANA_CL_MIP_CFG(mip_idx), v);

        v = (VTSS_F_ANA_CL_CCM_HMO_CTRL_CCM_INTERVAL(cfg->ccm_copy_next_id)  |
             B2B(cfg->ccm_copy_next_to_cpu, VTSS_M_ANA_CL_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA));
        REG_WR(VTSS_ANA_CL_CCM_HMO_CTRL(mip_idx), v);

        v = (VTSS_F_ANA_CL_MIP_CL_VID_CTRL_VID_VAL(cfg->vid) |
             VTSS_F_ANA_CL_MIP_CL_VID_CTRL_VID_SEL(cfg->vid_sel));
        REG_WR(VTSS_ANA_CL_MIP_CL_VID_CTRL(mip_idx), v);

        v = VTSS_F_ANA_CL_LBM_MAC_HIGH_LBM_MAC_HIGH((cfg->unicast_mac.addr[0] << 8) | cfg->unicast_mac.addr[1]);
        REG_WR(VTSS_ANA_CL_LBM_MAC_HIGH(mip_idx), v);
        v = (cfg->unicast_mac.addr[2] << 24) | (cfg->unicast_mac.addr[3] << 16) | (cfg->unicast_mac.addr[4] << 8) | cfg->unicast_mac.addr[5];
        REG_WR(VTSS_ANA_CL_LBM_MAC_LOW(mip_idx), v);
    } else {
        cfg = &(vtss_state->oam.up_mip_conf[mip_idx-1]);

        /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
        v = (VTSS_F_REW_MIP_CFG_MEL_VAL(cfg->meg_level)                   |
             B2B(cfg->ccm_copy_to_cpu, VTSS_M_REW_MIP_CFG_CCM_COPY_ENA)   |
             B2B(cfg->lbm_redir_to_cpu, VTSS_M_REW_MIP_CFG_LBM_REDIR_ENA) |
             B2B(cfg->ltm_redir_to_cpu, VTSS_M_REW_MIP_CFG_LTM_REDIR_ENA) |
             VTSS_F_REW_MIP_CFG_RAPS_CFG(cfg->raps_action)                |
             VTSS_F_REW_MIP_CFG_GENERIC_OPCODE_VAL(cfg->generic_opcode)   |
             VTSS_F_REW_MIP_CFG_GENERIC_OPCODE_CFG(cfg->generic_action)   |
             VTSS_F_REW_MIP_CFG_CPU_MIP_QU(cfg->cpu_queue)                |
             VTSS_F_REW_MIP_CFG_PIPELINE_PT(cfg->location));
        REG_WR(VTSS_REW_MIP_CFG(mip_idx), v);

        v = (VTSS_F_REW_CCM_HMO_CTRL_CCM_INTERVAL(cfg->ccm_copy_next_id)  |
             B2B(cfg->ccm_copy_next_to_cpu, VTSS_M_REW_CCM_HMO_CTRL_CCM_COPY_ONCE_ENA));
        REG_WR(VTSS_REW_CCM_HMO_CTRL(mip_idx), v);

        v = (VTSS_F_REW_MIP_VID_CTRL_VID_VAL(cfg->vid) |
             VTSS_F_REW_MIP_VID_CTRL_VID_SEL(cfg->vid_sel));
        REG_WR(VTSS_REW_MIP_VID_CTRL(mip_idx), v);

        v = VTSS_F_REW_LBM_MAC_HIGH_LBM_MAC_HIGH((cfg->unicast_mac.addr[0] << 8) | cfg->unicast_mac.addr[1]);
        REG_WR(VTSS_REW_LBM_MAC_HIGH(mip_idx), v);
        v = (cfg->unicast_mac.addr[2] << 24) | (cfg->unicast_mac.addr[3] << 16) | (cfg->unicast_mac.addr[4] << 8) | cfg->unicast_mac.addr[5];
        REG_WR(VTSS_REW_LBM_MAC_LOW(mip_idx), v);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_sat_cosid_counters_alloc(struct vtss_state_s *vtss_state,
                                               u16                 *cosid_seq_no_idx)
{
    u32 i;

    VTSS_D("Enter");

    for (i = 0; i < VTSS_OAM_SAT_COSID_CNTRS && vtss_state->oam.sat_cosid_counters_allocated[i]; ++i)
        /* search for free instance */ ;
    if (i == VTSS_OAM_SAT_COSID_CNTRS) {
        return VTSS_RC_ERROR;
    }
    vtss_state->oam.sat_cosid_counters_allocated[i] = TRUE;
    *cosid_seq_no_idx = i;

    for (i = 0; i < VTSS_PRIO_ARRAY_SIZE - 1; ++i) { /* Clear counters for each COS */
        REG_WR(VTSS_VOP_SAM_LBM_TX_TRANSID(*cosid_seq_no_idx, i), 0);
        REG_WR(VTSS_VOP_SAM_LBR_TX_FRM_CNT(*cosid_seq_no_idx, i), 0);
        REG_WR(VTSS_VOP_SAM_LBR_RX_FRM_CNT(*cosid_seq_no_idx, i), 0);
        REG_WR(VTSS_VOP_SAM_LBR_RX_TRANSID(*cosid_seq_no_idx, i), 0);
        REG_WR(VTSS_VOP_SAM_LBR_RX_TRANSID_ERR_CNT(*cosid_seq_no_idx, i), 0);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_oam_sat_cosid_counters_free(struct vtss_state_s *vtss_state,
                                              const u16           cosid_seq_no_idx)
{
    vtss_state->oam.sat_cosid_counters_allocated[cosid_seq_no_idx] = FALSE;
    return VTSS_RC_OK;
}

static vtss_rc fa_oam_sat_cosid_counters_get(struct vtss_state_s          *vtss_state,
                                             const vtss_oam_voe_idx_t     voe_idx,
                                             const u16                    cosid_seq_no_idx,
                                             vtss_oam_sat_cosid_counter_t *value)
{
#define SET(v) value->v = chipcnt->v.value
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);
    vtss_oam_sat_cosid_internal_counters_t *chipcnt = &vtss_state->oam.sat_cosid_counters[cfg->sat.cosid_seq_no_idx];
    vtss_rc rc = VTSS_RC_OK;
    u32 i;

    VTSS_D("Enter VOE %d", voe_idx);

    if (!cfg->sat.enable) {
        VTSS_D("VOE %d: SAT not enabled", voe_idx);
        return VTSS_RC_ERROR;
    }
    if (cfg->sat.cosid_seq_no_idx != cosid_seq_no_idx) {
        VTSS_D("VOE %d: SAT per COS ID counter set %u mismatch %u", voe_idx, cfg->sat.cosid_seq_no_idx, cosid_seq_no_idx);
        return VTSS_RC_ERROR;
    }
    if (!vtss_state->oam.sat_cosid_counters_allocated[cfg->sat.cosid_seq_no_idx]) {
        VTSS_D("VOE %d: SAT per COS ID counter set %u are not allocated", voe_idx, cfg->sat.cosid_seq_no_idx);
        return VTSS_RC_ERROR;
    }

    /* Poll so we get the most recent values: */
    for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
        rc = oam_sat_cosid_counters_update(vtss_state, voe_idx, cosid_seq_no_idx, i, FALSE);
    }

    for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; ++i) {
        SET(tx_ccm_lbm_tst[i]);
        SET(tx_lbr[i]);
        SET(rx_ccm_lbr_tst[i]);
        SET(rx_lbr_trans_id_err[i]);
        SET(rx_lbr_trans_id[i]);
    }

    return rc;
#undef SET
}

static vtss_rc fa_oam_sat_cosid_counters_clear(vtss_state_t             *vtss_state,
                                               const vtss_oam_voe_idx_t voe_idx,
                                               const u16                cosid_seq_no_idx,
                                               const u32                prio)
{
    const vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[voe_idx]);

    VTSS_D("Enter VOE %d  prio %u", voe_idx, prio);

    if (!cfg->sat.enable) {
        VTSS_D("VOE %d: SAT not enabled", voe_idx);
        return VTSS_RC_ERROR;
    }
    if (cfg->sat.cosid_seq_no_idx != cosid_seq_no_idx) {
        VTSS_D("VOE %d: SAT per COS ID counter set %u mismatch %u", voe_idx, cfg->sat.cosid_seq_no_idx, cosid_seq_no_idx);
        return VTSS_RC_ERROR;
    }
    if (!vtss_state->oam.sat_cosid_counters_allocated[cfg->sat.cosid_seq_no_idx]) {
        VTSS_D("VOE %d: SAT per COS ID counter set %u are not allocated", voe_idx, cfg->sat.cosid_seq_no_idx);
        return VTSS_RC_ERROR;
    }
    /* Poll & clear */
    return oam_sat_cosid_counters_update(vtss_state, voe_idx, cosid_seq_no_idx, prio, TRUE);
}

#if defined(VTSS_FEATURE_EVC)
static vtss_port_no_t mce_uni_calc(vtss_state_t      *vtss_state,
                                   const vtss_mce_t  *const mce)
{
    if (mce->rule == VTSS_MCE_RULE_UPINJ) {
        return vtss_state->port_count;
    }
    vtss_port_no_t            mce_port = (mce->rule == VTSS_MCE_RULE_TX) ? vtss_cmn_first_port_no_get(vtss_state, mce->action.port_list) : vtss_cmn_first_port_no_get(vtss_state, mce->key.port_list);
    u16                       port_idx = vtss_state->evc.info.table[mce->action.evc_id].port_idx[mce_port];
    vtss_evc_port_evc_conf_t  *evc_port_conf = &vtss_state->evc.port_info_table[port_idx].conf;
    return ((evc_port_conf->role == VTSS_EVC_PORT_ROLE_ROOT) || (evc_port_conf->role == VTSS_EVC_PORT_ROLE_LEAF)) ? mce_port : vtss_state->port_count;
}
#endif

static vtss_rc fa_mce_add(vtss_state_t         *vtss_state,
                          const vtss_mce_id_t  mce_id,
                          const vtss_mce_t     *const mce)
{
    vtss_rc                 rc = VTSS_RC_OK;
    const vtss_mce_key_t    *key = &mce->key;
    const vtss_mce_action_t *action = &mce->action;
    vtss_mce_action_t       old_action;
    vtss_mce_info_t         *mce_info = &vtss_state->oam.mce_info;
    vtss_mce_entry_t        *cur, *prev = NULL;
    vtss_mce_entry_t        *old = NULL, *old_prev = NULL, *ins = NULL, *ins_prev = NULL;
    vtss_res_t              res;
    vtss_sdx_entry_t        *isdx = NULL, *isdx_old = NULL;
    vtss_port_no_t          port_no, port_rx, port_tx;
    vtss_evc_entry_t        *evc = NULL;
    vtss_isdx_t             mce_isdx, old_mce_isdx;
    vtss_vid_t              mce_vid;
    BOOL                    port_list[VTSS_PORT_ARRAY_SIZE], evc_isdx_reuse=FALSE;
    vtss_port_no_t          uni_port = vtss_state->port_count;

    VTSS_D("Enter  mce_id: %X, mce->id: %X, tt_loop: %u, rule: %u, evc_id: %u  key->isdx: %u  action->isdx: %u", mce_id, mce->id, mce->tt_loop, mce->rule, mce->action.evc_id, key->isdx, action->isdx);

    if ((mce->id == VTSS_MCE_ID_LAST) || (mce->id == mce_id)) { /* Check MCE ID */
        VTSS_E("illegal mce id: %u", mce->id);
        return VTSS_RC_ERROR;
    }

#if defined(VTSS_FEATURE_EVC)
    if (action->evc_id == VTSS_EVC_ID_NONE) {   /* Check id EVC id is required to create this MCE */
        if ((action->isdx == VTSS_MCE_ISDX_EVC) || action->evc_counting || action->evc_hqos || action->evc_policing || action->evc_leaf) {
            VTSS_E("Missing EVC id");
            return VTSS_RC_ERROR;
        }
    }
#endif /* VTSS_FEATURE_EVC */

    if ((key->vid != VTSS_MCE_VID_NONE) && (mce->rule != VTSS_MCE_RULE_TX)) { /* Key VID is only allowed for VTSS_MCE_RULE_TX */
        VTSS_E("illegal VID key: vid %u", key->vid);
        return VTSS_RC_ERROR;
    }

    if ((key->isdx != VTSS_MCE_ISDX_NONE) && (action->isdx != VTSS_MCE_ISDX_NONE) && (action->isdx != VTSS_MCE_ISDX_EVC)) {    /* Check if invalid key/action ISDX */
        VTSS_E("illegal ISDX key/action: key %u action %u", key->isdx, action->isdx);
        return VTSS_RC_ERROR;
    }

    if ((key->vid != VTSS_MCE_VID_NONE) && (action->vid != VTSS_MCE_VID_NONE)) {    /* Check if invalid key/action VID */
        VTSS_E("illegal VID key/action: key %u action %u", key->vid, action->vid);
        return VTSS_RC_ERROR;
    }

    if ((action->isdx != VTSS_MCE_ISDX_NONE) && (mce->rule != VTSS_MCE_RULE_RX)) {  /* VTSS_MCE_RULE_RX is only to have action.isdx */
        VTSS_E("illegal action ISDX or VID: isdx %u  vid %u", action->isdx, action->vid);
        return VTSS_RC_ERROR;
    }

    if ((action->vid != VTSS_MCE_VID_NONE) && (mce->rule != VTSS_MCE_RULE_RX) && (mce->rule != VTSS_MCE_RULE_UPINJ)) {  /* VTSS_MCE_RULE_RX and VTSS_MCE_RULE_UPIJ is only to have action.vid */
        VTSS_E("illegal action ISDX or VID: isdx %u  vid %u", action->isdx, action->vid);
        return VTSS_RC_ERROR;
    }

    if ((key->isdx != VTSS_MCE_ISDX_NONE) && (mce->rule == VTSS_MCE_RULE_RX) && !key->looped) {  /* VTSS_MCE_RULE_RX is not allowed to have key.isdx unless looped */
        VTSS_E("illegal key ISDX: isdx %u ", key->isdx);
        return VTSS_RC_ERROR;
    }

    if ((key->isdx == VTSS_MCE_ISDX_NONE) && (key->vid == VTSS_MCE_VID_NONE) && (mce->rule == VTSS_MCE_RULE_TX) && !mce->tt_loop && (mce->action.forward_sel != VTSS_MCE_FORWARD_DISABLE)) {
        /* VTSS_MCE_RULE_TX must have key.isdx or key.vid -- except if tt_loop or TX forward disable (hit by any egress frame on this port */
        VTSS_E("illegal key ISDX or VID: isdx %u  vid %u", key->isdx, key->vid);
        return VTSS_RC_ERROR;
    }

    if ((key->isdx == VTSS_MCE_ISDX_NONE) && (mce->rule == VTSS_MCE_RULE_UPINJ)) { /* VTSS_MCE_RULE_UPINJ must have key.isdx */
        VTSS_E("illegal key ISDX: isdx %u", key->isdx);
        return VTSS_RC_ERROR;
    }

    if ((key->isdx == VTSS_MCE_ISDX_EVC) && (mce->rule != VTSS_MCE_RULE_UPINJ)) { /* VTSS_MCE_RULE_UPINJ is allowed to have key.isdx as EVC ISDX */
        VTSS_E("illegal key ISDX: isdx %u  rule %u", key->isdx, mce->rule);
        return VTSS_RC_ERROR;
    }

    /* Initialize */
    mce_isdx = (key->isdx != VTSS_MCE_ISDX_NONE) ? key->isdx : action->isdx;    /* MCE ISDX is either key.isdx or action.isdx */
    mce_vid = (key->vid != VTSS_MCE_VID_NONE) ? key->vid : action->vid;
    vtss_cmn_res_init(&res);
    memset(&old_action, 0, sizeof(old_action));
    old_mce_isdx = 0;

    /* Search for existing entry and place to add in list of MCE rules */
    for (cur = mce_info->used; cur != NULL; prev = cur, cur = cur->next) {
        if (cur->conf.id == mce->id) {  /* Entry already exists so this is reuse of existing MCE entry */
            old_prev = prev;
            old = cur;
        }

        if (cur->conf.id == mce_id) {   /* Found insertion point - insert MCE in front on this found entry */
            ins_prev = prev;
            ins = cur;
        }

        if ((cur->isdx_list != NULL) && (cur->isdx_list->sdx == mce_isdx)) {  /* Found requested ISDX - so this is ISDX reuse */
            if (cur->conf.action.isdx == VTSS_MCE_ISDX_EVC) {   /* The found and reused ISDX is a EVC ISDX. */
                mce_isdx = VTSS_MCE_ISDX_EVC;
                evc_isdx_reuse = TRUE;
            } else {
                isdx = cur->isdx_list;
            }
            VTSS_D("Found requested ISDX - so this is ISDX reuse.  evc_isdx_reuse: %u  isdx_ptr: %p", evc_isdx_reuse, isdx);
        }
    }

    if (mce->rule == VTSS_MCE_RULE_TX && !mce->tt_loop) {    /* In case of VTSS_MCE_RULE_TX 'port_rx' must be calculated */
        memset(port_list, 0, sizeof(port_list));
        if (isdx != NULL) {    /* This is reuse of ISDX - port list is the port of the ISDX */
            port_list[isdx->port_no] = TRUE;
        } else {    /* In case of not reuse of ISDX, port '0' is used as ISDX port */
            port_list[0] = TRUE;
        }
    } else {    /* RX and INJ rules are using key->port_list */
        memcpy(port_list, key->port_list, sizeof(port_list));
    }
    port_rx = vtss_cmn_first_port_no_get(vtss_state, port_list);
    port_tx = vtss_cmn_first_port_no_get(vtss_state, action->port_list);
    if (port_rx >= vtss_state->port_count) {
        VTSS_E("illegal key->port_list");
        return VTSS_RC_ERROR;
    }
    if ((port_tx >= vtss_state->port_count) && (mce->rule == VTSS_MCE_RULE_TX)) {
        VTSS_E("illegal action->port_list");
        return VTSS_RC_ERROR;
    }

#if defined(VTSS_FEATURE_EVC)
    if (action->evc_id != VTSS_EVC_ID_NONE) {
        evc = vtss_cmn_evc_get(vtss_state, action->evc_id);
        if (evc == NULL) {
            VTSS_E("illegal EVC id: evc_id %u ", action->evc_id);
            return VTSS_RC_ERROR;
        }
        uni_port = mce_uni_calc(vtss_state, mce);
        VTSS_D("uni_port: %u", uni_port);
    }
#endif /* VTSS_FEATURE_EVC */

    if (mce_id == VTSS_MCE_ID_LAST) {   /* This MCE entry should be added in the end of the list. */
        ins_prev = prev;
        ins = NULL;
    } else {   /* This MCE entry should be inserted - check if the place to insert was found */
        if (ins == NULL) {
            VTSS_E("Insertion point not found, could not find mce ID: %X", mce_id);
            return VTSS_RC_ERROR;
        }
    }

    if (mce_isdx_reuse(mce_isdx) && (isdx == NULL)) {   /* Check if reused ISDX was found */
        VTSS_E("could not find reuse ISDX %u", mce_isdx);
        return VTSS_RC_ERROR;
    }

    if (old != NULL) {  /* This is reuse of an existing MCE entry - register free of old resources */
        old_action = old->conf.action;
        old_mce_isdx = (old->conf.key.isdx != VTSS_MCE_ISDX_NONE) ? old->conf.key.isdx : old->conf.action.isdx;
        /* Old resources */
        if ((old->isdx_list != NULL) && (old_mce_isdx == VTSS_MCE_ISDX_NEW)) { /* Free old ISDX */
            res.isdx.del++;
        }
        port_no = vtss_cmn_first_port_no_get(vtss_state, old->conf.key.port_list);
        if ((old->conf.rule == VTSS_MCE_RULE_RX) && (port_no < vtss_state->port_count)) {   /* VTSS_MCE_RULE_RX has CLM entry */
            res.clm_c.del++;  /* Free CLM */
        }
        if (old->conf.rule == VTSS_MCE_RULE_TX) {   /* VTSS_MCE_RULE_TX has ES0 entry */
            for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
                if (old->conf.action.port_list[port_no]) {
                    res.es0.del++;  /* Free ES0 */
                }
            }
        }
    }

    /* Register new/changed resources */
    if (mce->rule == VTSS_MCE_RULE_RX) {  /* Register CLM entry required */
        res.clm_c.add++;
    }
    if (mce_isdx == VTSS_MCE_ISDX_NEW) {    /* Register ISDX entry required */
        res.isdx.add++;
    }
    if (mce->rule == VTSS_MCE_RULE_TX) {   /* Register ES0 entry required */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (action->port_list[port_no]) {
                res.es0.add++;
            }
        }
    }
    if (res.es0.add) {   /* Register ESDX required */
        res.esdx.add++;
    }

    /* Check resource availability */
    if ((rc = vtss_cmn_res_check(vtss_state, &res)) != VTSS_RC_OK) {
        VTSS_D("vtss_cmn_res_check failed  rc %u", rc);
        return rc;
    }

    /* Update free/used MCE list */
    if (old == NULL) {  /* No reuse of existing 'old' MCE entry */
        /* Take entry from free list */
        cur = mce_info->free;   /* cur is pointing to entry to insert */
        if (cur == NULL) {  /* No free entry was found */
            VTSS_E("no more MCEs");
            return VTSS_RC_ERROR;
        }
        mce_info->free = cur->next;
        mce_info->count++;
    } else {    /* Reuse of existing 'old' MCE entry */
        /* Take existing entry out of used list */
        if (old_prev == NULL) {  /* Check if the 'old' entry is first in list */
            mce_info->used = old->next;
        } else {
            old_prev->next = old->next;
        }
        cur = old;  /* cur is pointing to entry to insert */
    }

    /* Insert cur entry in used list */
    if ((old != NULL) && (ins_prev == old)) {   /* Insert of 'old' in front of itself */
        ins_prev = old_prev;
    }
    if (ins_prev == NULL) {     /* Insert in front of used list */
        cur->next = mce_info->used;
        mce_info->used = cur;
    } else {    /* Insert after ins_prev of used list */
        cur->next = ins_prev->next;
        ins_prev->next = cur;
    }
    cur->conf = *mce;   /* cur is now containing the MCE entry */
    if (evc_isdx_reuse) {   /* In case of reuse of EVC ISDX the configuration action is changed to VTSS_MCE_ISDX_EVC */
        cur->conf.action.isdx = VTSS_MCE_ISDX_EVC;
    }

#if defined(VTSS_FEATURE_EVC)
    if ((key->isdx == VTSS_MCE_ISDX_EVC) && (mce->rule == VTSS_MCE_RULE_UPINJ) && (evc != NULL)) { /* UP injection rule using the EVC ISDX */
        cur->isdx_list = evc_isdx_get(vtss_state, evc, port_rx, action->evc_leaf);
        VTSS_D("EVC Up injection port_rx %u  isdx_list %p  sdx %u",port_rx, cur->isdx_list, (cur->isdx_list != NULL) ? cur->isdx_list->sdx : 0);
        return(VTSS_RC_OK);     /* An injection rule using EVC ISDX does not do any resource allocation or configuration */
    }
#endif
    /* Free/allocate SDX resources */
    if (old != NULL) {  /* This is reuse of old entry */
        VTSS_D("This is reuse of old entry  mce_id %X", mce->id);
        if ((old->isdx_list != NULL) &&     /* Check if old entry ISDX must be forgotten */
            ((mce_isdx == VTSS_MCE_ISDX_NEW) || (mce_isdx == VTSS_MCE_ISDX_NONE) || (old->isdx_list->sdx != mce_isdx) || (old->isdx_list->port_no != port_rx))) {
            /* There is a demand for ISDX change - forget old entry ISDX */
            if (!mce_isdx_reuse(old_mce_isdx)) {    /* Old entry ISDX is not reuse (owned by this entry) - free it */
                vtss_cmn_sdx_free(vtss_state, old->isdx_list, TRUE);
                if (isdx_count) {
                    isdx_count--;
                }
                isdx_old = old->isdx_list; /* Remember old allocated ISDX that is freed */
            }
            if (isdx == old->isdx_list) { /* The found reuse ISDX for the new entry is the same as the old - that cannot be used */
                isdx = NULL;
            }
            old->isdx_list = NULL;     /* Forget old ISDX */
        }
        if ((isdx != NULL) && (isdx == old->isdx_list)) { /* The found reuse ISDX for the new entry is the same as the old - takeover as NEW ISDX indicating still "owner" */
            if (cur->conf.key.isdx != VTSS_MCE_ISDX_NONE) {
                cur->conf.key.isdx = VTSS_MCE_ISDX_NEW;
            }
            if (cur->conf.action.isdx != VTSS_MCE_ISDX_NONE) {
                cur->conf.action.isdx = VTSS_MCE_ISDX_NEW;
            }
        }
    }
    if (isdx != NULL) {  /* Check if this is reuse of other MCE entry ISDX */
        cur->isdx_list = isdx;
        VTSS_D("Reuse ISDX  mce_id %X  isdx %u", mce->id, cur->isdx_list->sdx);
    }
    if (mce_isdx == VTSS_MCE_ISDX_NEW) {  /* Alloc ISDX in case of NEW requested. */
        cur->isdx_list = vtss_cmn_sdx_alloc(vtss_state, port_rx, 0, TRUE);
        if (cur->isdx_list == NULL) {   /* Check if requested ISDX was allocated */
            VTSS_E("ISDX allocation failed");
            return VTSS_RC_ERROR;
        }
        VTSS_D("New ISDX  mce_id %X  isdx %u", mce->id, cur->isdx_list->sdx);
        isdx_count++;
    }
#if defined(VTSS_FEATURE_EVC)
    if (cur->conf.action.isdx == VTSS_MCE_ISDX_EVC) {  /* Mapping to the EVC ISDX */
        cur->isdx_list = evc_isdx_get(vtss_state, evc, port_rx, action->evc_leaf);
        VTSS_D("EVC ISDX  mce_id %X  isdx %u", mce->id, cur->isdx_list->sdx);
    }
#endif
    isdx = cur->isdx_list;

    /* Allocate counter if required */
    if (cur->conf.action.isdx_counting) {   /* This MCE must allocate counter */
        if ((rc = vtss_cmn_istat_alloc(vtss_state, 1, &cur->stat_idx)) != VTSS_RC_OK) {
            VTSS_D("vtss_cmn_stat_alloc failed  rc %u", rc);
            return rc;
        }
    } else {
        if ((rc = vtss_cmn_istat_free(vtss_state, &cur->stat_idx)) != VTSS_RC_OK) {
            VTSS_D("vtss_cmn_stat_free failed  rc %u", rc);
            return rc;
        }
    }
    if (isdx != NULL) {
        isdx->stat_idx = cur->stat_idx;
        isdx->stat_cnt = 1;
    }

    /* Add/delete CLM entry */
    if (mce->rule == VTSS_MCE_RULE_RX) {   /* Check if CLM entry required */
        VTSS_RC(mce_clm_add(vtss_state, cur, evc, uni_port));    /* Add CLM */
    } else {
        if (vtss_vcap_del(vtss_state, &vtss_state->vcap.clm_c.obj, order_to_clm_user(mce->order), mce_id) != VTSS_RC_OK) {
            VTSS_D("CLM vtss_vcap_del failed  mce_id: %X", mce_id);
        }
        if (vtss_vcap_del(vtss_state, &vtss_state->vcap.clm_b.obj, order_to_clm_user(mce->order), mce_id) != VTSS_RC_OK) {
            VTSS_D("CLM vtss_vcap_del failed  mce_id: %X", mce_id);
        }
    }

#if defined(VTSS_FEATURE_EVC)
    if (mce->tt_loop && (mce->rule == VTSS_MCE_RULE_RX) && (mce->action.evc_id != VTSS_EVC_ID_NONE) && (mce->key.isdx == VTSS_MCE_ISDX_NONE) && (uni_port < vtss_state->port_count)) {
        /* This is a EVC TT_LOOP RX rule on UNI matching on tag. It might be that OAM RX rules in front must generate PAG also */
        oam_mce_rx_pag_update(vtss_state, cur, evc);
    }
#endif

    /* Update the IPT and ISDX table */
    if ((((mce->rule == VTSS_MCE_RULE_RX) && (mce_isdx != VTSS_MCE_ISDX_EVC) && (key->isdx == VTSS_MCE_ISDX_NONE)) || (mce->rule == VTSS_MCE_RULE_UPINJ)) &&
        (isdx != NULL)) {   /* Check for ISDX/IPT table update required. Do not update the EVC ISDX */
        VTSS_RC(mce_isdx_update(vtss_state, cur, evc));
    }
    if (mce->rule == VTSS_MCE_RULE_TX) {   /* Check for ISDX/IPT table clear required */
        if ((mce_isdx == VTSS_MCE_ISDX_NEW) && (isdx != NULL)) {    /* Check for ISDX owner */
            VTSS_RC(mce_isdx_clear(vtss_state, cur->isdx_list->sdx));
        }
    }

    /* Add/delete ES0 entry */
    VTSS_D("Add/delete ES0 entry");
    if ((mce->rule == VTSS_MCE_RULE_TX) && (port_tx < vtss_state->port_count) &&
        (((isdx != NULL) || mce->tt_loop || (action->forward_sel == VTSS_MCE_FORWARD_DISABLE)) || (mce_vid < VTSS_VIDS))) {   /* Check if ES0 entry required */
        VTSS_RC(mce_es0_add(vtss_state, cur, evc, &old_action, uni_port));
    } /* Check if ES0 entry required */

#if defined(VTSS_FEATURE_EVC)
    if (!mce->tt_loop && (mce->rule == VTSS_MCE_RULE_TX) && (uni_port < vtss_state->port_count) &&
        (action->evc_id != VTSS_EVC_ID_NONE) && (action->pipeline == VTSS_MCE_PIPELINE_EXT_SAT)) { /* This is a create of a, non TT-LOOP, OAM Subscriber TX rule on UNI. */
        /* In case of any TT_LOOP Subscriber TX rule, in the same EVC Subscriber flow, it must point to the VOE/MIP as OAM frames on NNI is hijacked by TT_LOOP RX rules */
        vtss_mce_entry_t *tt_mce = find_tx_subscriber_rule(vtss_state, cur, uni_port);
        if (tt_mce != NULL) {
            tt_mce->conf.action.voe_idx = action->voe_idx;
            tt_mce->conf.action.mip_idx = action->mip_idx;
            VTSS_RC(mce_es0_add(vtss_state, tt_mce, evc, NULL, uni_port));
        }
    }
#endif

    if (isdx == NULL && isdx_old != NULL) {
        /* Remove references to deleted ISDX */
        for (cur = mce_info->used; cur != NULL; cur = cur->next) {
            if (cur->isdx_list == isdx_old) {
                cur->isdx_list = NULL;
            }
        }
    }

    VTSS_D("Exit");

    return VTSS_RC_OK;
}

static vtss_rc fa_mce_get(vtss_state_t         *vtss_state,
                          const vtss_mce_id_t  mce_id,
                          vtss_mce_t           *const mce_ret)
{
    vtss_mce_entry_t  *mce;

    vtss_mce_info_t  *mce_info = &vtss_state->oam.mce_info;

    VTSS_D("mce_id: %X", mce_id);

    memset(mce_ret, 0, sizeof(*mce_ret));

    /* Find MCE */
    for (mce = mce_info->used; mce != NULL; mce = mce->next) {
        if (mce->conf.id == mce_id) {
            break;
        }
    }

    /* Check if MCE was found */
    if (mce == NULL) {
        VTSS_E("could not find mce ID: %X", mce_id);
        return VTSS_RC_ERROR;
    }

    *mce_ret = mce->conf;

    return VTSS_RC_OK;
}

static vtss_rc fa_mce_counters_get(vtss_state_t         *vtss_state,
                                   const vtss_mce_id_t  mce_id,
                                   const vtss_port_no_t port_no,
                                   vtss_evc_counters_t  *const counters)
{
    vtss_mce_entry_t  *mce;

    vtss_mce_info_t  *mce_info = &vtss_state->oam.mce_info;

    VTSS_D("mce_id: %X", mce_id);

    memset(counters, 0, sizeof(*counters));

    /* Find MCE */
    for (mce = mce_info->used; mce != NULL; mce = mce->next) {
        if (mce->conf.id == mce_id) {
            break;
        }
    }

    /* Check if MCE was found */
    if (mce == NULL) {
        VTSS_E("could not find mce ID: %X", mce_id);
        return VTSS_RC_ERROR;
    }

    if (mce->conf.action.isdx_counting && mce->stat_idx != VTSS_POL_STAT_NONE) {   /* This MCE has allocated counter */
        vtss_stat_idx_t stat_idx;

        stat_idx.idx = mce->stat_idx;
        stat_idx.edx = 0;
        VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &stat_idx, counters, FALSE));
        VTSS_I("Counter is allocated. rx_green %" PRIu64 "", counters->rx_green.frames);
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_mce_counters_clear(vtss_state_t         *vtss_state,
                                     const vtss_mce_id_t  mce_id,
                                     const vtss_port_no_t port_no)
{
    vtss_mce_entry_t  *mce;

    vtss_mce_info_t  *mce_info = &vtss_state->oam.mce_info;

    VTSS_D("mce_id: %X", mce_id);

    /* Find MCE */
    for (mce = mce_info->used; mce != NULL; mce = mce->next) {
        if (mce->conf.id == mce_id) {
            break;
        }
    }

    /* Check if MCE was found */
    if (mce == NULL) {
        VTSS_E("could not find mce ID: %X", mce_id);
        return VTSS_RC_ERROR;
    }

    if (mce->conf.action.isdx_counting && mce->stat_idx != VTSS_POL_STAT_NONE) {   /* This MCE has allocated policer-counter */
        vtss_stat_idx_t stat_idx;

        stat_idx.idx = mce->stat_idx;
        stat_idx.edx = 0;
        VTSS_RC(vtss_fa_sdx_counters_update(vtss_state, &stat_idx, NULL, TRUE));
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_mce_del(vtss_state_t *vtss_state, const vtss_mce_id_t mce_id)
{
    vtss_mce_info_t  *mce_info = &vtss_state->oam.mce_info;
    vtss_mce_entry_t *mce, *cur, *prev = NULL;
    vtss_mce_t       *conf;
    vtss_vcap_id_t   id;
    vtss_port_no_t   port_no;

    VTSS_D("mce_id: %X", mce_id);

    /* Find MCE */
    for (mce = mce_info->used; mce != NULL; prev = mce, mce = mce->next) {
        if (mce->conf.id == mce_id) {
            break;
        }
    }

    /* Check if MCE was found */
    if (mce == NULL) {
        VTSS_E("could not find MCE.  mce ID: %X", mce_id);
        return VTSS_RC_ERROR;
    }

    /* Move MCE from used to free list */
    mce_info->count--;
    if (prev == NULL) {
        mce_info->used = mce->next;
    } else {
        prev->next = mce->next;
    }
    mce->next = mce_info->free;
    mce_info->free = mce;
    conf = &mce->conf;

#if defined(VTSS_FEATURE_EVC)
    if ((conf->key.isdx == VTSS_MCE_ISDX_EVC) && (conf->rule == VTSS_MCE_RULE_UPINJ) && (conf->action.evc_id != VTSS_EVC_ID_NONE)) { /* UP injection rule using the EVC ISDX */
        mce->isdx_list = NULL;
        VTSS_D("EVC Up injection mce->id %X", conf->id);
        return VTSS_RC_OK;  /* An injection rule using EVC ISDX does not do any resource allocation or configuration */
    }
    if ((conf->action.isdx == VTSS_MCE_ISDX_EVC) && (conf->rule == VTSS_MCE_RULE_RX) && (conf->action.evc_id != VTSS_EVC_ID_NONE)) { /* RX rule mapping to the EVC ISDX */
        mce->isdx_list = NULL;
    }
#endif
    /* Free SDX resources */
    if (mce->isdx_list != NULL) {
        /* MCE got ISDX reference - look for other users (not this) of this ISDX */
        for (cur = mce_info->used; cur != NULL; cur = cur->next) {
            if ((cur->conf.id != mce_id) && (cur->isdx_list == mce->isdx_list)) {
                break;
            }
        }
        if (cur == NULL) {  /* Check if other found */
            vtss_cmn_sdx_free(vtss_state, mce->isdx_list, TRUE);    /* Free ISDX */
            if (isdx_count) {
                isdx_count--;
            }
        }
    }
    mce->isdx_list = NULL;

    /* Free counter if any allocated */
    if (conf->action.isdx_counting && mce->stat_idx != VTSS_POL_STAT_NONE) {   /* This MCE has allocated policer-counter */
        if (vtss_cmn_istat_free(vtss_state, &mce->stat_idx) != VTSS_RC_OK) {
            VTSS_D("vtss_cmn_stat_free failed, stat_idx: %u", mce->stat_idx);
        }
    }

    /* Free CLM and ES0 entries */
    if (conf->rule == VTSS_MCE_RULE_RX) {   /* Free CLM */
        if (vtss_vcap_del(vtss_state, &vtss_state->vcap.clm_c.obj, order_to_clm_user(conf->order), mce_id) != VTSS_RC_OK) {
            VTSS_D("CLM vtss_vcap_del failed  mce_id: %X", mce_id);
        }
        if (vtss_vcap_del(vtss_state, &vtss_state->vcap.clm_b.obj, order_to_clm_user(conf->order), mce_id) != VTSS_RC_OK) {
            VTSS_D("CLM vtss_vcap_del failed  mce_id: %X", mce_id);
        }
    }
    if (conf->rule == VTSS_MCE_RULE_TX) {   /* Free ES0 */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (conf->action.port_list[port_no]) {
                id = mce_vcap_id(mce_id, port_no);
                if (vtss_vcap_del(vtss_state, &vtss_state->vcap.es0.obj, order_to_es0_user(conf->order), id) != VTSS_RC_OK) {
                    VTSS_D("ES0 vtss_vcap_del failed  id: %" PRIu64 "", id);
                }
            }
        }
    }

#if defined(VTSS_FEATURE_EVC)
    vtss_port_no_t  uni_port;
    if ((conf->action.evc_id != VTSS_EVC_ID_NONE) && (conf->rule != VTSS_MCE_RULE_UPINJ) && ((uni_port = mce_uni_calc(vtss_state, conf)) < vtss_state->port_count)) { /* This is an EVC RX/TX rule on UNI */
        vtss_evc_entry_t *evc = vtss_cmn_evc_get(vtss_state, conf->action.evc_id);
        if (evc == NULL) {
            VTSS_D("The EVC id: %u does not exist when this MCE is deleted", conf->action.evc_id);
        } else {
            if (conf->tt_loop && (conf->rule == VTSS_MCE_RULE_RX) && (conf->key.isdx == VTSS_MCE_ISDX_NONE)) {  /* TT_LOOP RX rule matching on tags */
                /* There might be OAM rules that no longer should generate the TT-LOOP PAG */
                oam_mce_rx_pag_update(vtss_state, mce, evc);
            }

            if (!conf->tt_loop && (conf->rule == VTSS_MCE_RULE_TX) && (conf->action.pipeline == VTSS_MCE_PIPELINE_EXT_SAT)) { /* OAM Subscriber TX rule */
                /* There might be TT_LOOP rules that no longer should point to possible VOE or MIP */
                vtss_mce_entry_t *tt_mce;
                if ((tt_mce = find_tx_subscriber_rule(vtss_state, mce, uni_port)) != NULL) {
                    if (tt_mce->conf.action.voe_idx == conf->action.voe_idx) {
                        tt_mce->conf.action.voe_idx = VTSS_VOE_IDX_NONE;
                    }
                    if (tt_mce->conf.action.mip_idx == conf->action.mip_idx) {
                        tt_mce->conf.action.mip_idx = VTSS_OAM_MIP_IDX_NONE;
                    }
                    VTSS_RC(mce_es0_add(vtss_state, tt_mce, evc, NULL, uni_port));
                }
            }
        }
    }
#endif

    return VTSS_RC_OK;
}

static vtss_rc fa_mce_port_get(vtss_state_t          *vtss_state,
                               const vtss_mce_id_t   mce_id,
                               const vtss_port_no_t  port_no,
                               vtss_mce_port_info_t  *const info)
{
    vtss_mce_entry_t  *mce;
    vtss_sdx_entry_t  *isdx;
    vtss_mce_t        *conf;

    VTSS_D("mce_id: %X, port_no: %u", mce_id, port_no);

    info->isdx = VTSS_MCE_ISDX_NONE;
    info->evc_isdx = VTSS_MCE_ISDX_NONE;
    info->evc_normal_key = FALSE;

    /* Find MCE */
    for (mce = vtss_state->oam.mce_info.used; mce != NULL; mce = mce->next) {
        conf = &mce->conf;
        if (conf->id == mce_id) {
            break;
        }
    }

    if (mce == NULL) {
        VTSS_E("could not find MCE.  mce ID: %u", mce_id);
        return VTSS_RC_ERROR;
    }

    isdx = mce->isdx_list;
    if (isdx == NULL) {
        VTSS_D("ISDX list empty.  mce ID: %u", mce_id);
    } else {
        info->isdx = isdx->sdx;
    }

#if defined(VTSS_FEATURE_EVC)
    if (conf->action.evc_id != VTSS_EVC_ID_NONE) {
        vtss_evc_entry_t  *evc = vtss_cmn_evc_get(vtss_state, conf->action.evc_id);
        if (evc == NULL) {
            VTSS_E("Could not get EVC.  mce ID: %u  EVC ID: %u", mce_id, conf->action.evc_id);
            return VTSS_RC_ERROR;
        }

        if ((conf->rule == VTSS_MCE_RULE_RX) || (conf->rule == VTSS_MCE_RULE_UPINJ)) {
            isdx = evc_isdx_get(vtss_state, evc, port_no, conf->action.evc_leaf);
            if (isdx != NULL) {
                info->evc_isdx = isdx->sdx;
            }
        }

        info->evc_normal_key = (conf->key.second && !conf->key.looped && require_normal_key(conf)) ? TRUE : FALSE;
    }
#endif /* VTSS_FEATURE_EVC */

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

/*
 * OAM CIL debug. (AIL debug is in vtss_common.c)
 */

// D_COM: Debug COMmon; DR_COM: Debug Read COMmon. _I for Instance. Etc.
#define D_COM(pr, name)            vtss_fa_debug_reg(vtss_state, pr, VTSS_VOP_##name,                    "COMMON:"#name)
#define D_COM_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VOP_##name(i),      (i),  "COMMON:"#name)
#define D_VOE_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VOP_##name(i),         (i),  "VOE:"#name)
#define D_VOE_MPLS_CONF_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VOP_MPLS_##name(i),         (i),  "VOE:"#name)
#define D_VOE_MPLS_STAT_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VOP_MPLS_##name(i),         (i),  "VOE:"#name)
#define D_VOE_II(pr, name, i1, i2) vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_VOP_##name((i1),(i2)), (i2), "VOE:"#name)
#define DR_COM(name, v)            { REG_RD(VTSS_VOP_##name, &v); }
#define DR_COM_I(name, i, v)       { REG_RD(VTSS_VOP_##name(i), &v); }
#define DR_VOE_I(name, i, v)       { REG_RD(VTSS_VOP_##name(i), &v); }
#define DR_VOE_II(name, i1, i2, v) { REG_RD(VTSS_VOP_##name((i1),(i2)), &v); }
#define D_D_MIP_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_ANA_CL_##name(i),         (i),  "DOWN_MIP:"#name)
#define D_U_MIP_I(pr, name, i)       vtss_fa_debug_reg_inst(vtss_state, pr, VTSS_REW_##name(i),         (i),  "UP_MIP:"#name)
#define D_D_MIP_S(pr, name)       vtss_fa_debug_reg(vtss_state, pr, VTSS_ANA_CL_##name,  "DOWN_MIP:"#name)
#define D_U_MIP_S(pr, name)       vtss_fa_debug_reg(vtss_state, pr, VTSS_REW_##name,  "UP_MIP:"#name)

static vtss_rc fa_debug_oam(vtss_state_t               *vtss_state,
                            const vtss_debug_printf_t  pr,
                            const vtss_debug_info_t    *const info)
{
    u32               i, k, v, w, voe_idx, div, tx_counter, rx_counter, clm_cnt, es0_cnt, isdx_cnt, mce_cnt, voe_cnt, umip_cnt, dmip_cnt;
    vtss_mce_entry_t  *mce;
    vtss_sdx_entry_t  *sdx;
    vtss_port_mask_t  pmask;
    BOOL              header = 1;
    char              buf[32];
    BOOL              show, vop, voe, status, clm, es0, isdx, lm_counters, d_mip, u_mip, mip_status, resources;
    vtss_mce_info_t   *mce_info = &vtss_state->oam.mce_info;

    div = 0;
    voe_idx = 0;
    tx_counter = 0;
    rx_counter = 0;
    clm_cnt = es0_cnt = isdx_cnt = mce_cnt = voe_cnt = umip_cnt = dmip_cnt = 0;
    show = vop = voe = status = clm = es0 = isdx = lm_counters = d_mip = u_mip = mip_status = resources = FALSE;

    VTSS_D("has_action %u  action %u", info->has_action, info->action);

    if (info->has_action) { /* Action parameter is present */
        show = (info->action == 0) ? TRUE : FALSE;
        vop = (info->action == 1) ? TRUE : FALSE;
        clm = (info->action == 2) ? TRUE : FALSE;
        es0 = (info->action == 3) ? TRUE : FALSE;
        isdx = (info->action == 4) ? TRUE : FALSE;
        mip_status = (info->action == 5) ? TRUE : FALSE;
        resources = (info->action == 6) ? TRUE : FALSE;

        if (info->action > 6) { /* This potentially a VOE config or VOE status action */
            for (i = 0, div = 10000; i < 5; ++i, (div = div / 10)) {
                voe = (info->action / div == 7) ? TRUE : FALSE;
                status = (info->action / div == 8) ? TRUE : FALSE;
                lm_counters = (info->action / div == 9) ? TRUE : FALSE;
                d_mip = (info->action / div == 10) ? TRUE : FALSE;
                u_mip = (info->action / div == 11) ? TRUE : FALSE;
                if (voe || status || lm_counters || d_mip || u_mip) {
                    break;
                }
            }
            if (voe || status || lm_counters || d_mip || u_mip) {    /* Calculate the possible VOE/MIP index */
                voe_idx = info->action % div;
            }
        }
    }

    VTSS_D("show %u  vop %u  voe %u  status %u  lm_counters %u  d_mip %u  u_mip %u  clm %u  es0 %u  isdx %u  mip_status  %u", show, vop, voe, status, lm_counters, d_mip, u_mip, clm, es0, isdx, mip_status);

    if (show) {
        pr("OAM Debug Group action:\n");
        pr("    0: Show possible actions\n");
        pr("    1: Print VOP configurations\n");
        pr("    2: Print CLM configurations\n");
        pr("    3: Print ES0 configurations\n");
        pr("    4: Print ISDX configurations\n");
        pr("    5: Print MIP status.\n");
        pr("    6: Print allocated resources\n");
        pr("    7XXXX: Print VOE XXXX configurations. Without XXXX all VOEs are printed\n");
        pr("    8XXXX: Print VOE XXXX status. Without XXXX all VOEs are printed\n");
        pr("    9XXXX: Print VOE XXXX LM counters. Without XXXX all VOEs are printed\n");
        pr("    10XXXX: Print Down-MIP XXXX configurations. Without XXXX all MIPs are printed\n");
        pr("    11XXXX: Print Up-MIP XXXX configurations. Without XXXX all MIPs are printed\n");
        pr("\n");
    }

    if (!info->has_action || vop) { /* VOP configuration must be printed */
        vtss_fa_debug_reg_header(pr, "VOP");
        D_COM(pr, VOP_CTRL);
        D_COM(pr, CPU_EXTR_CFG);
        D_COM(pr, CPU_EXTR_CFG_1);
        D_COM(pr, CPU_EXTR_CFG_2);
        D_COM(pr, CPU_EXTR_MPLS);
        D_COM(pr, CPU_EXTR_L3);
        D_COM(pr, VERSION_CTRL);
        D_COM(pr, VERSION_CTRL_2);
        D_COM(pr, VERSION_CTRL_3);
        D_COM(pr, VERSION_CTRL_MPLS);
        for (i = 0; i < 8; ++i) {
            D_COM_I(pr, OAM_GENERIC_CFG, i);
        }
        for (i = 0; i < 8; ++i) {
            D_COM_I(pr, MPLS_GENERIC_CODEPOINT, i);
        }
        D_COM(pr, LOC_CTRL);
        for (i = 0; i < 7; ++i) {
            D_COM_I(pr, LOC_PERIOD_CFG, i);
        }
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, HMO_PERIOD_CFG, i);
        }
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, HMO_FORCE_SLOT_CFG, i);
        }
        D_COM(pr, HMO_TIMER_CFG);
        D_COM(pr, LOC_SCAN_STICKY);
        D_COM(pr, MASTER_INTR_CTRL);
        for (i = 0; i < 2; ++i) {
            D_COM_I(pr, VOE32_INTR, i);
        }
        for (i = 0; i < 7; ++i) {
            D_COM_I(pr, INTR, i);
        }
        D_COM(pr, COMMON_MEP_MC_MAC_LSB);
        D_COM(pr, COMMON_MEP_MC_MAC_MSB);
        pr("\n");
    } /* Print VOP configurations */

    if (!info->has_action || voe) { /* VOE configuration must be printed */
        for (i = 0; i < VTSS_OAM_VOE_CNT; ++i) {
            if (voe && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(VOE_MISC_CONFIG, i, v);
            DR_VOE_I(VOE_CTRL, i, w);
            if (info->full  ||  (v & VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA) != 0) {
                sprintf(buf, "VOE_CONF %u", i);
                vtss_fa_debug_reg_header(pr, buf);
                D_VOE_I(pr, VOE_MISC_CONFIG, i);
                if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 1) {
                    D_VOE_I(pr, VOE_COMMON_CFG, i);
                    D_VOE_I(pr, VOE_CTRL, i);
                    D_VOE_I(pr, VOE_MEPID_CFG, i);
                    D_VOE_I(pr, PEER_MEPID_CFG, i);
                    D_VOE_I(pr, SAM_COSID_SEQ_CFG, i);
                    D_VOE_I(pr, SAM_NON_OAM_SEQ_CFG, i);
                    D_VOE_I(pr, OAM_CPU_COPY_CTRL, i);
                    D_VOE_I(pr, OAM_CPU_COPY_CTRL_2, i);
                    D_VOE_I(pr, PDU_VOE_PASS, i);
                    D_VOE_I(pr, OAM_CNT_OAM_CTRL, i);
                    D_VOE_I(pr, OAM_CNT_DATA_CTRL, i);
                    D_VOE_I(pr, OAM_CNT_DATA_CTRL_2, i);
                    D_VOE_I(pr, MEP_UC_MAC_LSB, i);
                    D_VOE_I(pr, MEP_UC_MAC_MSB, i);
                    D_VOE_I(pr, OAM_HW_CTRL, i);
                    D_VOE_I(pr, LOOPBACK_ENA, i);
                    D_VOE_I(pr, LOOPBACK_CFG, i);
                    D_VOE_I(pr, TX_TRANSID_UPDATE, i);
                    D_VOE_I(pr, CCM_CFG, i);
                    for (k = 0; k < 12; ++k) {
                        D_VOE_II(pr, CCM_MEGID_CFG, i, k);
                    }
                    D_VOE_I(pr, SLM_CONFIG, i);
                    D_VOE_I(pr, SLM_TEST_ID, i);
                    for (k = 0; k < 12; ++k) {
                        D_VOE_II(pr, SLM_PEER_LIST, i, k);
                    }
                    if (w & VTSS_M_VOP_VOE_CTRL_G_8113_1_ENA) {
                        D_VOE_I(pr, G_8113_1_CFG, i);
                        D_VOE_I(pr, G_8113_1_REMOTE_MIPID, i);
                        D_VOE_I(pr, G_8113_1_REMOTE_MIPID1, i);
                        D_VOE_I(pr, G_8113_1_REMOTE_MIPID2, i);
                        D_VOE_I(pr, G_8113_1_REMOTE_MIPID3, i);
                    }
                } else {
                    D_VOE_MPLS_CONF_I(pr, VOE_COMMON_CFG, i);
                    D_VOE_MPLS_CONF_I(pr, CPU_COPY_CTRL_MPLS, i);
                    D_VOE_MPLS_CONF_I(pr, OAM_HW_CTRL_MPLS, i);
                    D_VOE_MPLS_CONF_I(pr, OAM_CNT_SEL_MPLS, i);
                    D_VOE_MPLS_CONF_I(pr, OAM_CNT_DATA_MPLS, i);
                    D_VOE_MPLS_CONF_I(pr, BFD_CONFIG, i);
                    D_VOE_MPLS_CONF_I(pr, BFD_LOCAL_DISCR_SRC, i);
                    D_VOE_MPLS_CONF_I(pr, BFD_REMOTE_DISCR_SRC, i);
                    D_VOE_MPLS_CONF_I(pr, BFD_LOCAL_DISCR_SINK, i);
                    D_VOE_MPLS_CONF_I(pr, BFD_REMOTE_DISCR_SINK, i);
                }
            }
        }
        pr("\n");
    } /* Print VOE configurations */

    if (!info->has_action || status) { /* VOE status must be printed */
        for (i = 0; i < VTSS_OAM_VOE_CNT; ++i) {
            if (status && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(VOE_MISC_CONFIG, i, v);
            if (info->full  ||  (v & VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA) != 0) {
                sprintf(buf, "VOE_STAT %u", i);
                if (VTSS_X_VOP_VOE_MISC_CONFIG_VOE_ENA(v) == 1) {
                vtss_fa_debug_reg_header(pr, buf);
                D_VOE_I(pr, RX_SEL_OAM_CNT, i);
                D_VOE_I(pr, RX_OAM_FRM_CNT, i);
                D_VOE_I(pr, TX_SEL_OAM_CNT, i);
                D_VOE_I(pr, TX_OAM_FRM_CNT, i);
                D_VOE_I(pr, CCM_RX_FRM_CNT, i);
                D_VOE_I(pr, CCM_TX_SEQ_CFG, i);
                D_VOE_I(pr, CCM_RX_SEQ_CFG, i);
                D_VOE_I(pr, CCM_RX_WARNING, i);
                D_VOE_I(pr, CCM_ERR, i);
                D_VOE_I(pr, CCM_RX_ERR_1, i);
                D_VOE_I(pr, LBM_TX_TRANSID_CFG, i);
                D_VOE_I(pr, LBR_TX_FRM_CNT, i);
                D_VOE_I(pr, LBR_RX_TRANSID_CFG, i);
                D_VOE_I(pr, LBR_RX_FRM_CNT, i);
                D_VOE_I(pr, LBR_RX_TRANSID_ERR_CNT, i);
                D_VOE_I(pr, DM_PDU_CNT, i);
                D_VOE_I(pr, LM_PDU_CNT, i);
                D_VOE_I(pr, TX_OAM_DISCARD, i);
                D_VOE_I(pr, RX_OAM_DISCARD, i);
                D_VOE_I(pr, PDU_EXTRACT, i);
                D_VOE_I(pr, AUTO_HIT_ME_ONCE, i);
                D_VOE_I(pr, SYNLM_EXTRACT, i);
                D_VOE_I(pr, OAM_TX_STICKY, i);
                D_VOE_I(pr, OAM_RX_STICKY, i);
                D_VOE_I(pr, OAM_RX_STICKY2, i);
                D_VOE_I(pr, CCM_STAT, i);
                D_VOE_I(pr, CCM_STAT_2, i);
                D_VOE_I(pr, CCM_RX_LAST, i);
                D_VOE_I(pr, AIS_STAT, i);
                D_VOE_I(pr, AIS_RX_LAST, i);
                D_VOE_I(pr, LCK_STAT, i);
                D_VOE_I(pr, LCK_RX_LAST, i);
                D_VOE_I(pr, CSF_STAT, i);
                D_VOE_I(pr, CSF_RX_LAST, i);
                D_VOE_I(pr, INTR_STICKY, i);
                D_VOE_I(pr, INTR_ENA, i);
                D_VOE_I(pr, SLM_TX_FRM_CNT, i);
                D_VOE_I(pr, BLK_STICKY, i);
                D_VOE_I(pr, CCM_TX_FCB_CFG, i);
                D_VOE_I(pr, CCM_RX_FCB_CFG, i);
                D_VOE_I(pr, LBR_CRC_ERR_CNT, i);
                } else {
                D_VOE_MPLS_STAT_I(pr, RX_CNT_SEL_OAM_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, RX_CNT_NON_SEL_OAM_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, TX_CNT_SEL_OAM_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, TX_CNT_NON_SEL_OAM_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, BFD_SRC_INFO, i);
                D_VOE_MPLS_STAT_I(pr, BFD_SINK_INFO, i);
                D_VOE_MPLS_STAT_I(pr, BFD_STAT, i);
                D_VOE_MPLS_STAT_I(pr, BFD_RX_LAST, i);
                D_VOE_MPLS_STAT_I(pr, INTR_STICKY_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, INTR_ENA_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, CPT_RX_STICKY_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, PDU_EXTRACT_MPLS, i);
                D_VOE_MPLS_STAT_I(pr, BFD_RX_STICKY, i);
                D_VOE_MPLS_STAT_I(pr, BFD_TX_STICKY, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CC_TX_CNT_REG, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CV_TX_CNT_REG, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CC_RX_VLD_CNT_REG, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CV_RX_VLD_CNT_REG, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CC_RX_INVLD_CNT_REG, i);
                D_VOE_MPLS_STAT_I(pr, BFD_CV_RX_INVLD_CNT_REG, i);
                }
            }
        }
        pr("\n");
#if 0
        /* TBD - these are per front port: */
        D_VOE_I(pr, CONTEXT_REW_CT_OAM_INFO_REW, i);
        D_VOE_I(pr, CONTEXT_REW_CT_OAM_STICKY_REW, i);
        D_VOE_I(pr, CONTEXT_REW_CT_CCM_TLV_INFO_REW, i);
        D_VOE_I(pr, CONTEXT_REW_CT_OAM_DATA_REW, i);
        D_VOE_I(pr, CONTEXT_REW_CT_OAM_DATA1_REW, i);
        /* TBD - these are per front port x 2 (??): */
        D_VOE_I(pr, CONTEXT_ANA_CT_OAM_INFO_ANA, i);
        D_VOE_I(pr, CONTEXT_ANA_CT_OAM_STICKY_ANA, i);
        D_VOE_I(pr, CONTEXT_ANA_CT_CCM_TLV_INFO_ANA, i);
        D_VOE_I(pr, CONTEXT_ANA_CT_OAM_DATA_ANA, i);
        D_VOE_I(pr, CONTEXT_ANA_CT_OAM_DATA1_ANA, i);
        /* TBD - these are per VOE: */
        VTSS_VOP_ANA_COSID_MAP_CONF_COSID_MAP_TABLE_ANA, i;
        VTSS_VOP_ANA_COSID_MAP_CONF_COSID_MAP_CFG_ANA, i;
        VTSS_VOP_REW_COSID_MAP_CONF_COSID_MAP_TABLE_REW, i;
        VTSS_VOP_REW_COSID_MAP_CONF_COSID_MAP_CFG_REW, i;
        /* TBD - these are per front port: */
        VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP, i;
        VTSS_VOP_PORT_COSID_MAP_CONF_PORT_RX_COSID_MAP1, i;
        VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP, i;
        VTSS_VOP_PORT_COSID_MAP_CONF_PORT_TX_COSID_MAP1, i;
        /* TBD - SAT specific: */
        VTSS_VOP_SAM_COSID_SEQ_CNT_SAM_LBM_TX_TRANSID(gi, ri);
        VTSS_VOP_SAM_COSID_SEQ_CNT_SAM_LBR_TX_FRM_CNT(gi, ri);
        VTSS_VOP_SAM_COSID_SEQ_CNT_SAM_LBR_RX_FRM_CNT(gi, ri);
        VTSS_VOP_SAM_COSID_SEQ_CNT_SAM_LBR_RX_TRANSID(gi, ri);
        VTSS_VOP_SAM_COSID_SEQ_CNT_SAM_LBR_RX_TRANSID_ERR_CNT(gi, ri);
        pr("\n");
#endif
    } /* Print VOE status */

    if (!info->has_action || lm_counters) { /* VOE LM counters must be printed */
        for (i = 0; i < VTSS_OAM_VOE_CNT; ++i) {
            if (lm_counters && (div > 1) && (voe_idx != i)) {   /* A specific VOE must be printed - this is not the one */
                continue;
            }
            DR_VOE_I(VOE_MISC_CONFIG, i, v);
            DR_VOE_I(VOE_COMMON_CFG, i, w);
            if ((v & VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA) != 0) {  /* Only print for active VOEs */
                sprintf(buf, "VOE_LM_COUNTERS %u", i);
                pr("VOE_LM_COUNTERS %u\n", i);
                pr("COS     TX counter      RX counter\n");
                for (k = 0; k < VTSS_PRIO_ARRAY_SIZE; ++k) { /* Print RX and TX count for each COS */
                    pr("%3u     ", k);
                    if ((w & VTSS_M_VOP_VOE_COMMON_CFG_UPMEP_ENA) != 0) { /* This an Up-MEP (Service instance) */
                        tx_counter = VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                        rx_counter = VTSS_REW_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                    } else {    /* This is Down-MEP */
                        if (i >= VTSS_OAM_PORT_VOE_BASE_IDX) {  /* This is port Down-MEP */
                            tx_counter = VTSS_REW_PORT_LM_CNT_LSB(((i - VTSS_OAM_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE) + k);
                            rx_counter = VTSS_ANA_AC_OAM_MOD_PORT_LM_CNT_LSB(((i - VTSS_OAM_PORT_VOE_BASE_IDX) * VTSS_PRIO_ARRAY_SIZE) + k);
                        } else {    /* This is a Service Down-MEP */
                            tx_counter = VTSS_REW_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                            rx_counter = VTSS_ANA_AC_OAM_MOD_SRV_LM_CNT_LSB((i * VTSS_PRIO_ARRAY_SIZE) + k);
                        }
                    }
                    REG_RD(tx_counter, &v);
                    pr("%10u      ", v);
                    REG_RD(rx_counter, &v);
                    pr("%10u\n", v);
                }

                vtss_oam_voe_conf_t *cfg = &(vtss_state->oam.voe_conf[i]);
                if (cfg->sat.enable && cfg->sat.cosid_seq_no_mode != VTSS_OAM_SAT_COSID_SEQ_NO_DISABLED &&
                    vtss_state->oam.sat_cosid_counters_allocated[cfg->sat.cosid_seq_no_idx]) {
                    pr("SAM_COSID_COUNTERS %u\n", i);
                    pr("COS   tx_ccm_lbm_tst        tx_lbr   rx_ccm_lbr_tst   rx_lbr_trans_id_err   rx_lbr_trans_id\n");
                    for (k = 0; k < VTSS_PRIO_ARRAY_SIZE - 1; ++k) { /* Print counters for each COS */
                        pr("%3u", k);
                        REG_RD(VTSS_VOP_SAM_LBM_TX_TRANSID(cfg->sat.cosid_seq_no_idx, k), &v);
                        pr("%17u", v);
                        REG_RD(VTSS_VOP_SAM_LBR_TX_FRM_CNT(cfg->sat.cosid_seq_no_idx, k), &v);
                        pr("%14u", v);
                        REG_RD(VTSS_VOP_SAM_LBR_RX_FRM_CNT(cfg->sat.cosid_seq_no_idx, k), &v);
                        pr("%17u", v);
                        REG_RD(VTSS_VOP_SAM_LBR_RX_TRANSID(cfg->sat.cosid_seq_no_idx, k), &v);
                        pr("%22u", v);
                        REG_RD(VTSS_VOP_SAM_LBR_RX_TRANSID_ERR_CNT(cfg->sat.cosid_seq_no_idx, k), &v);
                        pr("%18u\n", v);
                    }
                }
            }
        }
        pr("\n");
    } /* Print VOE LM counters */

    if (!info->has_action || resources) { /* Used resources must be printed */
        /* Print resource consumption */
        clm_cnt = vtss_vcap_count_get(&vtss_state->vcap.clm_c.obj, VTSS_IS1_USER_MCE_0);
        clm_cnt += vtss_vcap_count_get(&vtss_state->vcap.clm_c.obj, VTSS_IS1_USER_MCE_1);
        clm_cnt += vtss_vcap_count_get(&vtss_state->vcap.clm_c.obj, VTSS_IS1_USER_MCE_2);
        clm_cnt += vtss_vcap_count_get(&vtss_state->vcap.clm_c.obj, VTSS_IS1_USER_MCE_3);
        es0_cnt = vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_MCE_0);
        es0_cnt += vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_MCE_1);
        es0_cnt += vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_MCE_2);
        es0_cnt += vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_MCE_3);

        isdx_cnt = isdx_count;
        for (mce_cnt = 0, mce = mce_info->used; mce != NULL; mce = mce->next) {
            mce_cnt++;
        }
        for (i = 0; i < VTSS_OAM_VOE_CNT; ++i) {
            DR_VOE_I(VOE_MISC_CONFIG, i, v);
            if ((v & VTSS_M_VOP_VOE_MISC_CONFIG_VOE_ENA) != 0) {
                voe_cnt++;
            }
        }
        for (i = 0; i < VTSS_OAM_DOWN_MIP_CNT; ++i) {
            REG_RD(VTSS_ANA_CL_MIP_CFG(i), &v)
            if ((v & VTSS_M_ANA_CL_MIP_CFG_LBM_REDIR_ENA) != 0) {
                dmip_cnt++;
            }
        }
        for (i = 1; i < (VTSS_OAM_UP_MIP_CNT + 1); ++i) {   /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
            REG_RD(VTSS_REW_MIP_CFG(i), &v)
            if ((v & VTSS_M_REW_MIP_CFG_LBM_REDIR_ENA) != 0) {
                umip_cnt++;
            }
        }

        pr("Resource consumption:\n");
        pr("CLM-MEP: %u\n", clm_cnt);
        pr("CLM-ROWS: %u\n", vtss_state->vcap.clm_c.obj.count);
        pr("ES0-MEP: %u  ES0-VLAN: %u  ES0-EFE: %u\n", es0_cnt, vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_VLAN), vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_EFE));
        pr("ES0-TXTAG: %u  ES0-MPLS: %u\n", vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_TX_TAG), vtss_vcap_count_get(&vtss_state->vcap.es0.obj, VTSS_ES0_USER_MPLS));
        pr("ES0-TOT: %u\n", vtss_state->vcap.es0.obj.count);
        pr("ISDX: %u\n", isdx_cnt);
        pr("VOE: %u\n", voe_cnt);
        pr("UMIP: %u\n", umip_cnt);
        pr("DMIP: %u\n", dmip_cnt);
        pr("MCE: %u\n", mce_cnt);
        pr("\n");
        pr("Maximum values:\n");
        pr("CLM-FULL-KEY-MAX: %u\n", VTSS_VCAP_SUPER_BLK_CNT * VTSS_VCAP_SUPER_ROW_CNT);
        pr("ES0-MAX: %u\n", VTSS_ES0_CNT);
        pr("ISDX-MAX: %u\n", VTSS_SDX_CNT);
        pr("POL-MAX: %u\n", VTSS_EVC_POL_CNT);
        pr("STAT-MAX: %u\n", VTSS_EVC_STAT_CNT);
        pr("SERVICE-VOE-MAX: %u\n", VTSS_OAM_PATH_SERVICE_VOE_CNT);
        pr("PORT-VOE-MAX: %u\n", VTSS_OAM_PORT_VOE_CNT);
        pr("UP-MIP-MAX: %u\n", VTSS_OAM_UP_MIP_CNT);
        pr("MCE-MAX: %u\n", VTSS_MCES);
        pr("\n");
    } /* Print resource consumption */

    if (!info->has_action || clm) { /* CLM configuration must be printed */
        /* Print CLM for any created entries */
        pr("CLM:\n");
        VTSS_RC(vtss_fa_debug_clm_c(vtss_state, pr, info));
    } /* Print CLM status */

    if (!info->has_action || es0) { /* ES0 configuration must be printed */
        /* Print ES0 for any created entries */
        pr("ES0:\n");
        VTSS_RC(vtss_fa_debug_es0(vtss_state, pr, info));
    } /* Print ES0 status */

    if (!info->has_action || isdx) { /* ISDX configuration must be printed */
        for (mce = mce_info->used; mce != NULL; mce = mce->next) {
            if (header) {
                vtss_fa_debug_print_port_header(vtss_state, pr, "MCE       Port  ID    ISDX  ");
                header = 0;
            }
            if ((sdx = mce->isdx_list) == NULL) {
                pr("%-10X  No ISDX\n", mce->conf.id);
                continue;
            }
            pr("%-10X%-6u%-6u%-6u", mce->conf.id, sdx->port_no, sdx->id, sdx->sdx);
            REG_RDX_PMASK(VTSS_ANA_L2_PORT_MASK_CFG, sdx->sdx, &pmask);
            vtss_fa_debug_print_pmask(pr, &pmask);

            REG_RD(VTSS_ANA_L2_DLB_CFG(sdx->sdx), &v);
            pr("%28s: %u", "DLB  ", v);
            for (k = 0; k < 8; k++) {
                REG_RD(VTSS_ANA_L2_DLB_COS_CFG(sdx->sdx, k), &v);
                pr("%s%u", k ? "/" : " + ", v);
            }
            pr("\n");

            REG_RD(VTSS_ANA_L2_ISDX_BASE_CFG(sdx->sdx), &v);
            pr("%28s: %u", "COUNT", v);
            for (k = 0; k < 8; k++) {
                REG_RD(VTSS_ANA_L2_ISDX_COS_CFG(sdx->sdx, k), &v);
                pr("%s%u", k ? "/" : " + ", v);
            }
            pr("\n");

            REG_RD(VTSS_ANA_L2_SERVICE_CTRL(sdx->sdx), &v);
            pr("%28s: enable %u\n", "ES0  ", VTSS_X_ANA_L2_SERVICE_CTRL_ES0_ISDX_KEY_ENA(v));
            pr("%28s: enable %u  value %u\n", "AGGR ", VTSS_X_ANA_L2_SERVICE_CTRL_AGGR_REPLACE_ENA(v), VTSS_X_ANA_L2_SERVICE_CTRL_AGGR_VAL(v));

            REG_RD(VTSS_ANA_L2_MISC_CFG(sdx->sdx), &v);
            pr("%28s: value %u\n", "PIPE ", VTSS_X_ANA_L2_MISC_CFG_PIPELINE_PT(v));

            REG_RD(VTSS_ANA_CL_OAM_MEP_CFG(sdx->sdx), &v);
            pr("%28s: enable %u  value %u\n", "VOE  ", VTSS_X_ANA_CL_OAM_MEP_CFG_MEP_IDX_ENA(v), VTSS_X_ANA_CL_OAM_MEP_CFG_MEP_IDX(v));
            pr("%28s: value %u\n", "NOMEL", VTSS_X_ANA_CL_OAM_MEP_CFG_INDEPENDENT_MEL_ENA(v));

            REG_RD(VTSS_ANA_CL_ISDX_CFG(sdx->sdx), &v);
            pr("%28s: value %u\n", "MIP  ", VTSS_X_ANA_CL_ISDX_CFG_MIP_IDX(v));
        }
    } /* Print ISDX configuration */

    if (!info->has_action || d_mip) { /* Down-MIP must be printed */
        for (i = 0; i < VTSS_OAM_DOWN_MIP_CNT; ++i) {
            if (d_mip && (div > 1) && (voe_idx != i)) {   /* A specific Down-MIP must be printed - this is not the one */
                continue;
            }
            REG_RD(VTSS_ANA_CL_MIP_CFG(i), &v)
            if ((v & VTSS_M_ANA_CL_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                sprintf(buf, "DOWN_MIP_CONF %u", i);
                vtss_fa_debug_reg_header(pr, buf);
                D_D_MIP_I(pr, MIP_CFG, i);
                D_D_MIP_I(pr, CCM_HMO_CTRL, i);
                D_D_MIP_I(pr, MIP_CL_VID_CTRL, i);
                D_D_MIP_I(pr, LBM_MAC_HIGH, i);
                D_D_MIP_I(pr, LBM_MAC_LOW, i);
            }
        }
    }

    if (!info->has_action || u_mip) { /* Up-MIP must be printed */
        for (i = 1; i < (VTSS_OAM_UP_MIP_CNT + 1); ++i) {   /* Up MIP instance 0 is not used as it cannot be addressed by ES0 action - 0 has the meaning of no MIB */
            if (u_mip && (div > 1) && (voe_idx != i)) {   /* A specific Up-MIP must be printed - this is not the one */
                continue;
            }

            REG_RD(VTSS_REW_MIP_CFG(i), &v)
            if ((v & VTSS_M_REW_MIP_CFG_LBM_REDIR_ENA) != 0) {  /* Only print for active MIPs */
                sprintf(buf, "UP_MIP_CONF %u", i);
                vtss_fa_debug_reg_header(pr, buf);
                D_U_MIP_I(pr, MIP_CFG, i);
                D_U_MIP_I(pr, CCM_HMO_CTRL, i);
                D_U_MIP_I(pr, MIP_VID_CTRL, i);
                D_U_MIP_I(pr, LBM_MAC_HIGH, i);
                D_U_MIP_I(pr, LBM_MAC_LOW, i);
            }
        }
    }

    if (!info->has_action || mip_status) { /* MIP status must be printed */
        sprintf(buf, "DOWN_MIP_STAT");
        vtss_fa_debug_reg_header(pr, buf);
        D_D_MIP_S(pr, MIP_STICKY);
        pr("\n");

        sprintf(buf, "UP_MIP_STAT");
        vtss_fa_debug_reg_header(pr, buf);
        D_U_MIP_S(pr, MIP_STICKY_EVENT);
    }

    return VTSS_RC_OK;
}

#undef D_COM
#undef D_COM_I
#undef D_VOE_I
#undef D_VOE_II
#undef DR_COM
#undef DR_COM_I
#undef DR_VOE_I
#undef DR_VOE_II

vtss_rc vtss_fa_oam_debug_print(vtss_state_t *vtss_state,
                                const vtss_debug_printf_t pr,
                                const vtss_debug_info_t   *const info)
{
    return vtss_debug_print_group(VTSS_DEBUG_GROUP_OAM, fa_debug_oam, vtss_state, pr, info);
}

/* - Initialization ------------------------------------------------ */

static vtss_rc fa_oam_voe_poll_1sec(vtss_state_t *vtss_state)
{
    /* LM and DM PDU Tx/Rx counters are 8 bit
     * Some CCM PDU counters are 16 bit
     * Data frame counters are 32 bit
     * No byte counters
     * For a 32-bit frame counter at 10G, wrap happens after approx. 219s
     * For OAM PDU at 3.3 ms (CCM) 16-bit wrap happens after approx. 196s
     * For OAM PDU at 100 ms (LM/DM) 8-bit wrap happens after approx. 25s
     * I.e. worst case is 25s
     * Jaguar2 has 1077 VOEs to cover in 25s -> poll 44 at each tick
     * ServalT has  203 VOEs to cover in 25s -> poll 9 at each tick
     *
     * Bugzilla #23350: The original algorithm depended on a very accurate
     * timer to drive this poll. This turned out to be a false assumption.
     * We thus occasionally encountered DM counter overrun because the polling
     * sometimes took a bit longer. We have thus increased the number of VOEs
     * that is polled every second by setting the target "full circle" period
     * to 20 seconds instead of 25.
     */
    const u32 N = 1 + VTSS_OAM_VOE_CNT / 20;

    vtss_oam_voe_idx_t *idx = &(vtss_state->oam.voe_poll_idx);  /* For readability */
    u32 i;

    for (i = 0; i < N; ++i) {
        VTSS_RC(fa_oam_voe_counter_update(vtss_state, *idx));
        *idx = (*idx == VTSS_OAM_VOE_CNT - 1) ? 0 : *idx + 1;
    }

    return VTSS_RC_OK;
}

static vtss_rc fa_init(vtss_state_t *vtss_state)
{
    u32               v;

    /* All VOEs are disabled in hardware by default - will prevent the CLI
       command "debug api cil oam" from spewing out loads of irrelevant
       information -- it only dumps enabled VOEs by default. */

    /* G.8113.1: */
    REG_RD(VTSS_VOP_VOP_CTRL, &v);
    v = ((v & ~(VTSS_M_VOP_VOP_CTRL_LOC_SCAN_ENA                  |
                VTSS_M_VOP_VOP_CTRL_G_8113_1_MEP_SCENARIO         |
                VTSS_M_VOP_VOP_CTRL_G_8113_1_CNT_LBR_RX_ERROR_ENA |
                VTSS_M_VOP_VOP_CTRL_VOP_ENA)) |
         VTSS_F_VOP_VOP_CTRL_LOC_SCAN_ENA(0)                      |
         VTSS_F_VOP_VOP_CTRL_G_8113_1_MEP_SCENARIO(2)             | /* Scenario C */
         VTSS_F_VOP_VOP_CTRL_G_8113_1_CNT_LBR_RX_ERROR_ENA(1)     | /* count LBR erors */
         VTSS_F_VOP_VOP_CTRL_VOP_ENA(0));
    REG_WR(VTSS_VOP_VOP_CTRL, v);

    /* LOC index 0-4 is used for CCM LOC: */
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(VTSS_OAM_PERIOD_3_3_MS - 1), (     3333ULL * 1000) / LOC_BASE);
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(VTSS_OAM_PERIOD_10_MS - 1),  (    10000ULL * 1000) / LOC_BASE);
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(VTSS_OAM_PERIOD_100_MS - 1), (   100000ULL * 1000) / LOC_BASE);
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(VTSS_OAM_PERIOD_1_SEC - 1),  (  1000000ULL * 1000) / LOC_BASE);
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(VTSS_OAM_PERIOD_10_SEC - 1), ( 10000000ULL * 1000) / LOC_BASE);

    /* LOC index 5 and 6 is used for CCM-LM counter insertion (1 sec and 100 ms): */
    /* (must be configured with 2 x desired CCM-LM counter insertion period) */
    /* Use slightly slower CCM-LM counter insertion to make sure 1 sec and 100 ms CC frames always have LM counters inserted. */
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(fa_oam_ccm_lm_period_index(VTSS_OAM_PERIOD_100_MS)), ( 2 * 99900ULL * 1000) / LOC_BASE); /* 2 x 100 ms */
    REG_WR(VTSS_VOP_LOC_PERIOD_CFG(fa_oam_ccm_lm_period_index(VTSS_OAM_PERIOD_1_SEC)),  (2 * 999900ULL * 1000) / LOC_BASE); /* 2 x 1 sec */

    /* This is to make subscriber VOE looped frames hit CLM C 1. lookup */
    REG_WRM(VTSS_ANA_CL_CLM_MISC_CTRL,
            VTSS_F_ANA_CL_CLM_MISC_CTRL_CLM_GIDX_DEF_SEL(1) |    /* Default G_IDX is the logical port number */
            VTSS_F_ANA_CL_CLM_MISC_CTRL_FORCED_KEY_SEL(1) |      /* Forced CLM lookup is done with NORMAL key */
            VTSS_F_ANA_CL_CLM_MISC_CTRL_LBK_CLM_FORCE_ENA(0x20), /* Force Looped frames to do CLM lookup in C 2. lookup */
            VTSS_M_ANA_CL_CLM_MISC_CTRL_FORCED_KEY_SEL |
            VTSS_M_ANA_CL_CLM_MISC_CTRL_LBK_CLM_FORCE_ENA |
            VTSS_M_ANA_CL_CLM_MISC_CTRL_CLM_GIDX_DEF_SEL);

    /* This is to make down VOE looping (ex. LBM->LBR) possible without port being member of the classified VLAN */
    REG_WR(VTSS_ANA_ACL_VOE_LOOPBACK_CFG, 0);

    return VTSS_RC_OK;
}

vtss_rc vtss_fa_oam_init(vtss_state_t *vtss_state, vtss_init_cmd_t cmd)
{
    vtss_oam_state_t *state = &vtss_state->oam;

    switch (cmd) {
    case VTSS_INIT_CMD_CREATE:
        state->vop_cfg_set               = fa_oam_vop_cfg_set;
        state->voe_alloc                 = fa_oam_voe_alloc;
        state->voe_free                  = fa_oam_voe_free;
        state->voe_cfg_set               = fa_oam_voe_cfg_set;
        state->event_poll                = fa_oam_event_poll;
        state->voe_event_poll            = fa_oam_voe_event_poll;
        state->voe_event_enable          = fa_oam_voe_event_enable;
        state->voe_arm_hitme             = fa_oam_voe_arm_hitme;
        state->voe_ccm_set_rdi_flag      = fa_oam_voe_ccm_set_rdi_flag;
        state->ccm_status_get            = fa_oam_ccm_status_get;
        state->pdu_status_get            = fa_oam_pdu_status_get;
        state->pdu_seen_status_get       = fa_oam_pdu_seen_status_get;
        state->proc_status_get           = fa_oam_proc_status_get;
        state->voe_counter_update        = fa_oam_voe_counter_update;
        state->voe_counter_get           = fa_oam_voe_counter_get;
        state->voe_counter_clear         = fa_oam_voe_counter_clear;
        state->mip_alloc                 = fa_oam_mip_alloc;
        state->mip_free                  = fa_oam_mip_free;
        state->mip_cfg_set               = fa_oam_mip_cfg_set;
        state->sat_cosid_counters_alloc  = fa_oam_sat_cosid_counters_alloc;
        state->sat_cosid_counters_free   = fa_oam_sat_cosid_counters_free;
        state->sat_cosid_counters_get    = fa_oam_sat_cosid_counters_get;
        state->sat_cosid_counters_clear  = fa_oam_sat_cosid_counters_clear;
        state->mce_add                   = fa_mce_add;
        state->mce_del                   = fa_mce_del;
        state->mce_get                   = fa_mce_get;
        state->mce_counters_get          = fa_mce_counters_get;
        state->mce_counters_clear        = fa_mce_counters_clear;
        state->mce_port_get              = fa_mce_port_get;
        state->mce_info.max_count        = VTSS_MCES;
        break;
    case VTSS_INIT_CMD_INIT:
        VTSS_RC(fa_init(vtss_state));
        break;
    case VTSS_INIT_CMD_POLL:
        VTSS_RC(fa_oam_voe_poll_1sec(vtss_state));
        break;
    default:
        break;
    }
    return VTSS_RC_OK;
}

#endif /* if 0 */

#endif /* VTSS_FEATURE_VOP */

#endif /* VTSS_ARCH_FA */
