// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_VCAP
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"

#if defined(VTSS_FEATURE_VCAP)

/* - Resource utilities -------------------------------------------- */

/* Initialize resource change information */
void vtss_cmn_res_init(vtss_res_t *res)
{
    VTSS_MEMSET(res, 0, sizeof(*res));
}

/* Check VCAP resource usage */
vtss_rc vtss_cmn_vcap_res_check(vtss_vcap_obj_t *obj, vtss_res_chg_t *chg)
{
    u32                  add_row, del_row, add, del, old, new, key_count, count, max_row = obj->max_count;
    vtss_vcap_key_size_t key_size;

    add_row = chg->add;
    del_row = chg->del;

    /* Calculate added/deleted rows for each key size */
    for (key_size = VTSS_VCAP_KEY_SIZE_FULL; key_size <= VTSS_VCAP_KEY_SIZE_LAST; key_size++) {
        count = vtss_vcap_key_rule_count(key_size);
        add = chg->add_key[key_size];
        del = chg->del_key[key_size];
        key_count = (obj->key_count[key_size] + count - 1);
        old = (key_count / count);
        new = ((key_count + add - del) / count);

        if (add > del) {
            /* Adding rules may cause addition of rows */
            add_row += (new - old);
        } else {
            /* Deleting rules may cause deletion of rows */
            del_row += (old - new);
        }
    }

#if defined(VTSS_FEATURE_VCAP_SUPER)
    {
        vtss_vcap_super_obj_t *vcap_super = obj->vcap_super;

        if (vcap_super != NULL) {
            /* Rows in super pool may be used */
            max_row += ((vcap_super->block.max_count - vcap_super->block.count) * vcap_super->row_count);
        }
    }
#endif /* VTSS_FEATURE_VCAP_SUPER */

    if ((obj->count + add_row) > (max_row + del_row)) {
        VTSS_I("VCAP %s exceeded, add: %u, del: %u, count: %u, max: %u",
               obj->name, add_row, del_row, obj->count, max_row);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_EVC_STAT_CNT)
static vtss_rc vtss_ps_res_check(const char *name, vtss_xrow_header_t *hdr, vtss_ps_chg_t *chg)
{
    u32 size, count = 0;

    /* Calculate number of items needed */
    for (size = 0; size < 9; size++) {
        count += ((hdr->count_size[size] + 7 + chg->add_size[size] - chg->del_size[size]) / 8);
    }
    count *= 8;
    if (count > hdr->max_count) {
        VTSS_I("%s table exceeded, count: %u, max: %u", name, count, hdr->max_count);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}
#endif

/* Check SDK and VCAP resource usage */
vtss_rc vtss_cmn_res_check(vtss_state_t *vtss_state, vtss_res_t *res)
{
#if defined(VTSS_SDX_CNT)
    vtss_sdx_info_t *sdx_info = &vtss_state->l2.sdx_info;

    if ((sdx_info->isdx.count + res->isdx.add - res->isdx.del) > sdx_info->max_count) {
        VTSS_I("ISDX exceeded  isdx.count %u  isdx.add %u  isdx.del %u  max_count %u", sdx_info->isdx.count, res->isdx.add, res->isdx.del, sdx_info->max_count);
        return VTSS_RC_ERROR;
    }

    if ((sdx_info->esdx.count + res->esdx.add - res->esdx.del) > sdx_info->max_count) {
        VTSS_I("ESDX exceeded  esdx.count %u  esdx.add %u  esdx.del %u  max_count %u", sdx_info->esdx.count, res->esdx.add, res->esdx.del, sdx_info->max_count);
        return VTSS_RC_ERROR;
    }
#endif /* VTSS_SDX_CNT */

#if defined(VTSS_ARCH_JAGUAR_2)
    vtss_vsi_info_t    *vsi_info = &vtss_state->l2.vsi_info;

    if ((vsi_info->count + res->vsi.add - res->vsi.del) > vsi_info->max_count) {
        VTSS_I("VSI exceeded");
        return VTSS_RC_ERROR;
    }
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_EVC_STAT_CNT)
    VTSS_RC(vtss_ps_res_check("policer", &vtss_state->l2.pol_table.hdr, &res->pol));
    VTSS_RC(vtss_ps_res_check("ingress statistics", &vtss_state->l2.istat_table.hdr, &res->istat));
    VTSS_RC(vtss_ps_res_check("egress statistics", &vtss_state->l2.estat_table.hdr, &res->estat));
#endif

#if defined(VTSS_FEATURE_IS0)
    /* VCAP IS0 */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.is0.obj, &res->is0));
#endif /* VTSS_FEATURE_IS0 */

#if defined(VTSS_FEATURE_IS1)
    /* VCAP IS1 */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.is1.obj, &res->is1));
#endif /* VTSS_FEATURE_IS1 */

#if defined(VTSS_FEATURE_CLM)
    /* VCAP CLM */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.clm_a.obj, &res->clm_a));
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.clm_b.obj, &res->clm_b));
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.clm_c.obj, &res->clm_c));
#endif /* VTSS_FEATURE_CLM */

#if defined(VTSS_FEATURE_LPM)
    /* VCAP LPM */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.lpm.obj, &res->lpm));
#endif /* VTSS_FEATURE_LPM */

#if defined(VTSS_FEATURE_IS2)
    /* VCAP IS2 */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.is2.obj, &res->is2));
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_IS2_B)
    /* VCAP IS2_B */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.is2_b.obj, &res->is2_b));
#endif /* VTSS_FEATURE_IS2_B */

#if defined(VTSS_FEATURE_ES0)
    /* VCAP ES0 */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.es0.obj, &res->es0));
#endif /* VTSS_FEATURE_ES0 */

#if defined(VTSS_FEATURE_ES2)
    /* VCAP ES2 */
    VTSS_RC(vtss_cmn_vcap_res_check(&vtss_state->vcap.es2.obj, &res->es2));
#endif /* VTSS_FEATURE_ES2 */

    return VTSS_RC_OK;
}

/* - Range checkers ------------------------------------------------ */

/* Determine if UDP/TCP rule */
BOOL vtss_vcap_udp_tcp_rule(const vtss_vcap_u8_t *proto)
{
    return (proto->mask == 0xff && (proto->value == 6 || proto->value == 17));
}

/* Allocate range checker */
vtss_rc vtss_vcap_range_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                              u32 *range,
                              vtss_vcap_range_chk_type_t type,
                              u32 min,
                              u32 max)
{
    u32                   i, new = VTSS_VCAP_RANGE_CHK_NONE;
    vtss_vcap_range_chk_t *entry;

    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &range_chk_table->entry[i];
        if (entry->type == type && entry->min == min && entry->max == max) {
            /* Matching used entry */
            new = i;
            break;
        }

        if (entry->count == 0 && (new == VTSS_VCAP_RANGE_CHK_NONE || i == *range)) {
            /* Free entry found, possibly reuse old range checker */
            new = i;
        }
    }

    if (new == VTSS_VCAP_RANGE_CHK_NONE) {
        VTSS_I("no more range checkers");
        return VTSS_RC_ERROR;
    }

    VTSS_I("alloc range: %u, min: %u, max: %u", new, min, max);

    entry = &range_chk_table->entry[new];
    entry->count++;
    entry->type = type;
    entry->min = min;
    entry->max = max;
    *range = new;
    return VTSS_RC_OK;
}

/* Free VCAP range checker */
vtss_rc vtss_vcap_range_free(vtss_vcap_range_chk_table_t *range_chk_table,
                             u32 range)
{
    vtss_vcap_range_chk_t *entry;

    /* Ignore this special value */
    if (range == VTSS_VCAP_RANGE_CHK_NONE)
        return VTSS_RC_OK;

    if (range >= VTSS_VCAP_RANGE_CHK_CNT) {
        VTSS_E("illegal range: %u", range);
        return VTSS_RC_ERROR;
    }

    entry = &range_chk_table->entry[range];
    if (entry->count == 0) {
        VTSS_E("illegal range free: %u", range);
        return VTSS_RC_ERROR;
    }

    entry->count--;
    if (entry->count == 0) {
        entry->type = VTSS_VCAP_RANGE_TYPE_IDLE;
    }

    return VTSS_RC_OK;
}

/* Allocate UDP/TCP range checker */
vtss_rc vtss_vcap_udp_tcp_range_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                                      u32 *range,
                                      const vtss_vcap_udp_tcp_t *port,
                                      BOOL sport)
{
    vtss_vcap_range_chk_type_t type;

    if (port->low == port->high || (port->low == 0 && port->high == 0xffff)) {
        /* No range checker required */
        *range = VTSS_VCAP_RANGE_CHK_NONE;
        return VTSS_RC_OK;
    }
    type = (sport ? VTSS_VCAP_RANGE_TYPE_SPORT : VTSS_VCAP_RANGE_TYPE_DPORT);
    return vtss_vcap_range_alloc(range_chk_table, range, type, port->low, port->high);
}

/* Try to convert a range to a value/mask.
 * Conversion is possible if the following conditions are true:
 *  * 'low' and 'high' matches in upper bits.
 *  * lower bits of 'low' are zero.
 *  * lower bits of 'high' are one.
 *
 * Returns TRUE if conversion succeeded.
 */
BOOL vtss_vcap_vr_rng2vm(vtss_vcap_vr_t *vr)
{
    if (vr->type != VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        vtss_vcap_vr_value_t mask;
        vtss_vcap_vr_value_t low  = vr->vr.r.low;
        vtss_vcap_vr_value_t high = vr->vr.r.high;
        int                  bit;

        /* Start with most significant bit and find the first bit where 'low' and 'high' differs. */
        for (bit = (sizeof(vtss_vcap_vr_value_t) * 8) - 1; bit >= 0; bit--) {
            mask = 1 << bit;
            if ((low & mask) != (high & mask)) {
                break;
            }
        }

        /* Create a mask for the lower and different bits */
        mask = (1 << (bit + 1)) - 1;

        if (((low & ~mask) == low) && ((high & mask) == mask)) {
            vr->type = VTSS_VCAP_VR_TYPE_VALUE_MASK;
            vr->vr.v.value = low;
            vr->vr.v.mask = ~mask;
            VTSS_I("range %u-%u converted to value 0x%X, mask 0x%X", low, high, vr->vr.v.value, vr->vr.v.mask);
            return TRUE;
        }
    }

    return FALSE;
}

/* Allocate universal range checker
   NOTE: If it is possible to change an inclusive range to a value/mask,
   the vr is modified here in order to save a range checker.
*/
vtss_rc vtss_vcap_vr_alloc(vtss_vcap_range_chk_table_t *range_chk_table,
                           u32 *range,
                           vtss_vcap_range_chk_type_t type,
                           vtss_vcap_vr_t *vr)
{
    u8 bits = (type == VTSS_VCAP_RANGE_TYPE_DSCP ? 6 :
               type == VTSS_VCAP_RANGE_TYPE_VID ? 12 : 16);
    u32 max_value = (1 << bits) - 1;

    /* Parameter check */
    if (vr->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        if (vr->vr.v.value > max_value) {
            VTSS_E("illegal value: 0x%X (max value is 0x%X)", vr->vr.v.value, max_value);
            return VTSS_RC_ERROR;
        }
    }
    else {
        if ((vr->vr.r.low > max_value) || (vr->vr.r.high > max_value) || (vr->vr.r.low > vr->vr.r.high)){
            VTSS_E("illegal range: 0x%X-0x%X", vr->vr.r.low, vr->vr.r.high);
            return VTSS_RC_ERROR;
        }
    }

    /* Try to convert a range to value/mask */
    (void)vtss_vcap_vr_rng2vm(vr);

    if (vr->type == VTSS_VCAP_VR_TYPE_VALUE_MASK) {
        /* No range checker required */
        *range = VTSS_VCAP_RANGE_CHK_NONE;
        return VTSS_RC_OK;
    }
    return vtss_vcap_range_alloc(range_chk_table, range, type, vr->vr.r.low, vr->vr.r.high);
}

vtss_rc vtss_vcap_range_commit(vtss_state_t *vtss_state, vtss_vcap_range_chk_table_t *range_new)
{
    if (VTSS_MEMCMP(&vtss_state->vcap.range, range_new, sizeof(*range_new))) {
        /* The temporary working copy has changed - Save it and commit */
        vtss_state->vcap.range = *range_new;
        return VTSS_FUNC_COLD_0(vcap.range_commit);
    }
    return VTSS_RC_OK;
}

/* - VCAP table functions ------------------------------------------ */

/* Return number of rules per row for a given key */
u32 vtss_vcap_key_rule_count(vtss_vcap_key_size_t key_size)
{
    if (key_size > VTSS_VCAP_KEY_SIZE_LAST) {
        VTSS_E("illegal key_size");
    }
    return (key_size == VTSS_VCAP_KEY_SIZE_SIXTEENTH ? 16 :
            key_size == VTSS_VCAP_KEY_SIZE_TWELFTH ? 12 :
            key_size == VTSS_VCAP_KEY_SIZE_EIGHTH ? 8 :
            key_size == VTSS_VCAP_KEY_SIZE_SIXTH ? 6 :
            key_size == VTSS_VCAP_KEY_SIZE_QUARTER ? 4 :
            key_size == VTSS_VCAP_KEY_SIZE_HALF ? 2 : 1);
}

const char *vtss_vcap_key_size2txt(vtss_vcap_key_size_t key_size)
{
    return (key_size == VTSS_VCAP_KEY_SIZE_FULL ? "Full" :
            key_size == VTSS_VCAP_KEY_SIZE_HALF ? "Half" :
            key_size == VTSS_VCAP_KEY_SIZE_QUARTER ? "Quarter" :
            key_size == VTSS_VCAP_KEY_SIZE_SIXTH ? "Sixth" :
            key_size == VTSS_VCAP_KEY_SIZE_EIGHTH ? "Eighth" :
            key_size == VTSS_VCAP_KEY_SIZE_TWELFTH ? "Twelfth" :
            key_size == VTSS_VCAP_KEY_SIZE_SIXTEENTH ? "Sixteenth" : "?");
}

const char *vtss_vcap_key_type2txt(vtss_vcap_key_type_t key_type)
{
    return (key_type == VTSS_VCAP_KEY_TYPE_NORMAL ? "NORMAL" :
            key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG ? "DOUBLE_TAG" :
            key_type == VTSS_VCAP_KEY_TYPE_IP_ADDR ? "IP_ADDR" :
            key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR ? "MAC_IP_ADDR" : "?");
}

vtss_vcap_key_size_t vtss_vcap_key_type2size(vtss_vcap_key_type_t key_type)
{
    vtss_vcap_key_size_t key_size;
#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    key_size = VTSS_VCAP_KEY_SIZE_QUARTER;
#elif defined(VTSS_ARCH_SPARX5)
    key_size = VTSS_VCAP_KEY_SIZE_SIXTH;
#else
    key_size = VTSS_VCAP_KEY_SIZE_EIGHTH;
#endif

    return (key_type == VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR ? VTSS_VCAP_KEY_SIZE_FULL :
            key_type == VTSS_VCAP_KEY_TYPE_DOUBLE_TAG ? key_size :
            VTSS_VCAP_KEY_SIZE_HALF);
}

/* Get (row, col) position of rule */
static void vtss_vcap_pos_get(vtss_vcap_obj_t *obj, vtss_vcap_idx_t *idx, u32 ndx)
{
    u32                  cnt;
    vtss_vcap_key_size_t key_size;

    /* Use index to find (row, col) within own block */
    cnt = vtss_vcap_key_rule_count(idx->key_size);
    idx->row = (ndx / cnt);
    idx->col = (ndx % cnt);

    /* Include rows for previous blocks */
    for (key_size = (idx->key_size + 1); key_size < VTSS_VCAP_KEY_SIZE_MAX; key_size++) {
        cnt = vtss_vcap_key_rule_count(key_size);
        idx->row += ((obj->key_count[key_size] + cnt - 1) / cnt);
    }
}

char *vtss_vcap_id_txt(vtss_state_t *vtss_state, vtss_vcap_id_t id)
{
    u32  high = ((id >> 32) & 0xffffffff);
    u32  low = (id & 0xffffffff);
    char *txt;

    vtss_state->txt_buf_index++;
    txt = &vtss_state->txt_buf[(vtss_state->txt_buf_index & 1) ? 0 : 32];
    VTSS_SPRINTF(txt, "0x%08x:0x%08x", high, low);
    return txt;
}

/* Lookup VCAP entry */
vtss_rc vtss_vcap_lookup(vtss_state_t *vtss_state,
                         vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id,
                         vtss_vcap_data_t *data, vtss_vcap_idx_t *idx)
{
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];
    vtss_vcap_entry_t    *cur;
    vtss_vcap_key_size_t key_size;

    VTSS_D("VCAP %s, id: %s", obj->name, vtss_vcap_id_txt(vtss_state, id));

    VTSS_MEMSET(ndx, 0, sizeof(ndx));

    for (cur = obj->used; cur != NULL; cur = cur->next) {
        key_size = cur->data.key_size;
        if (cur->user == user && cur->id == id) {
            if (idx != NULL) {
                idx->key_size = key_size;
                vtss_vcap_pos_get(obj, idx, ndx[key_size]);
            }
            if (data != NULL)
                *data = cur->data;
            return VTSS_RC_OK;
        }
        ndx[key_size]++;
    }
    return VTSS_RC_ERROR;
}

#if defined(VTSS_FEATURE_VCAP_SUPER)
static vtss_rc vtss_vcap_super_add(vtss_state_t *vtss_state, vtss_vcap_obj_t *obj)
{
    vtss_vcap_super_obj_t *vcap_super = obj->vcap_super;
    vtss_vcap_type_t      type;
    u32                   i, count = 0, found = 0;

    if (obj->count < obj->max_count) {
        /* No need to allocate super block */
        return VTSS_RC_OK;
    }

    if (vcap_super == NULL || vcap_super->block.count >= vcap_super->block.max_count) {
        VTSS_I("no more VCAP super blocks for %s", obj->name);
        return VTSS_RC_ERROR;
    }

    /* Look for free blocks */
    for (i = 0; i < vcap_super->block.max_count; i++) {
        type = vcap_super->block_type[i];
        if (type == VTSS_VCAP_TYPE_NONE) {
            /* Free block found */
            break;
        } else if (type == obj->type) {
            /* Same type found, start couting blocks to move */
            found = 1;
        } else if (found) {
            /* Count blocks to move */
            count++;
        }
    }

    if (i == vcap_super->block.max_count) {
        VTSS_E("VCAP super blocks are used");
        return VTSS_RC_ERROR;
    }

    /* Move blocks down to make room for new block */
    for ( ; count > 0; count--, i--) {
        type = vcap_super->block_type[i - 1];
        VTSS_RC(vcap_super->block_map(vtss_state, i, type));
        vcap_super->block_type[i] = type;
        VTSS_RC(vcap_super->block_move(vtss_state, i - 1, 0));
    }

    /* Allocate new block */
    VTSS_I("VCAP super block %u used by %s", i, obj->name);
    VTSS_RC(vcap_super->block_map(vtss_state, i, obj->type));
    vcap_super->block_type[i] = obj->type;
    vcap_super->block.count++;
    obj->max_count += vcap_super->row_count;

    return VTSS_RC_OK;
}

static vtss_rc vtss_vcap_super_del(vtss_state_t *vtss_state, vtss_vcap_obj_t *obj)
{
    vtss_vcap_super_obj_t *vcap_super = obj->vcap_super;
    vtss_vcap_type_t      type;
    u32                   i, found = 0;

    if (vcap_super == NULL || (obj->count % vcap_super->row_count) != 0) {
        VTSS_I("nothing to free for %s", obj->name);
        return VTSS_RC_OK;
    }

    VTSS_I("free %s, count: %u", obj->name, obj->count);

    /* Look for blocks to move */
    for (i = 0; i < vcap_super->block.max_count; i++) {
        type = vcap_super->block_type[i];
        if (type == VTSS_VCAP_TYPE_NONE) {
            /* Free block found */
            break;
        } else if (type == obj->type) {
            /* Same type found */
            found = 1;
        } else if (found && (i > 0)) { /* Please Lint with 'i > 0' check */
            /* Move block up */
            VTSS_I("block %u now %s", i - 1, vtss_vcap_type_txt(type));
            VTSS_RC(vcap_super->block_map(vtss_state, i - 1, type));
            vcap_super->block_type[i - 1] = type;
            VTSS_RC(vcap_super->block_move(vtss_state, i, 1));
        }
    }

    if (found) {
        i--;
        VTSS_I("block %u now free", i);
        type = VTSS_VCAP_TYPE_NONE;
        VTSS_RC(vcap_super->block_map(vtss_state, i, type));
        vcap_super->block_type[i] = type;
        if (obj->max_count < vcap_super->row_count) {
            VTSS_E("max_count: %u, row_count: %u", obj->max_count, vcap_super->row_count);
            return VTSS_RC_ERROR;
        }
        obj->max_count -= vcap_super->row_count;
        vcap_super->block.count--;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_VCAP_SUPER */

/* Delete rule found in list */
static vtss_rc vtss_vcap_del_rule(vtss_state_t *vtss_state,
                                  vtss_vcap_obj_t *obj, vtss_vcap_entry_t *cur,
                                  vtss_vcap_entry_t *prev, u32 ndx)
{
    vtss_vcap_key_size_t key_size;
    vtss_vcap_idx_t      idx;
    u32                  cnt;
    vtss_vcap_entry_t    **free_list = &obj->free;
    u32                  *rule_count = &obj->rule_count;

    VTSS_D("VCAP %s, ndx: %u", obj->name, ndx);

    /* Move rule to free list */
    if (prev == NULL)
        obj->used = cur->next;
    else
        prev->next = cur->next;
#if defined(VTSS_FEATURE_VCAP_SUPER)
    if (obj->vcap_super != NULL) {
        /* Use VCAP_SUPER free list if valid */
        free_list = &obj->vcap_super->free;
        rule_count = &obj->vcap_super->rule_count;
    }
#endif /* VTSS_FEATURE_VCAP_SUPER */
    cur->next = *free_list;
    *free_list = cur;
    *rule_count = (*rule_count - 1);

    /* Delete VCAP entry from block */
    key_size = cur->data.key_size;
    idx.key_size = key_size;
    obj->key_count[key_size]--;
    cnt = obj->key_count[key_size];
    if (!vtss_state->warm_start_cur) {
        /* Avoid VCAP update in warm start mode */
        if (ndx == cnt) {
            /* Last rule in block, just delete */
            vtss_vcap_pos_get(obj, &idx, ndx);
            VTSS_RC(obj->entry_del(vtss_state, &idx));
        } else {
            /* Delete and contract by moving rules up */
            vtss_vcap_pos_get(obj, &idx, ndx + 1);
            VTSS_RC(obj->entry_move(vtss_state, &idx, cnt - ndx, 1));
        }
    }

    /* Get position of the entry after the last entry in block */
    vtss_vcap_pos_get(obj, &idx, cnt);
    if (idx.col) {
        /* Done, there are more rules on the last row */
        return VTSS_RC_OK;
    }

    /* Delete and contract by moving rows up */
    obj->count--;
    if (!vtss_state->warm_start_cur && idx.row != obj->count) {
        cnt = (obj->count - idx.row);
        idx.key_size = VTSS_VCAP_KEY_SIZE_FULL;
        idx.row++;
        VTSS_RC(obj->entry_move(vtss_state, &idx, cnt, 1));
    }
#if defined(VTSS_FEATURE_VCAP_SUPER)
    VTSS_RC(vtss_vcap_super_del(vtss_state, obj));
#endif /* VTSS_FEATURE_VCAP_SUPER */
    return VTSS_RC_OK;
}

u32 vtss_vcap_count_get(vtss_vcap_obj_t *obj, int user)
{
    u32                 count = 0;
    vtss_vcap_entry_t   *cur;

    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->user == user) {
            count++;
        }
    }
    return count;
}

/* Delete VCAP rule */
vtss_rc vtss_vcap_del(vtss_state_t *vtss_state,
                      vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id)
{
    vtss_vcap_entry_t    *cur, *prev = NULL;
    vtss_vcap_key_size_t key_size;
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];

    VTSS_D("VCAP %s, id: %s", obj->name, vtss_vcap_id_txt(vtss_state, id));

    VTSS_MEMSET(ndx, 0, sizeof(ndx));
    for (cur = obj->used; cur != NULL; prev = cur, cur = cur->next) {
        key_size = cur->data.key_size;
        if (cur->user == user && cur->id == id) {
            /* Found rule, delete it */
            return vtss_vcap_del_rule(vtss_state, obj, cur, prev, ndx[key_size]);
        }
        ndx[key_size]++;
    }

    /* Silently ignore if rule not found */
    return VTSS_RC_OK;
}

vtss_rc vtss_vcap_add(vtss_state_t *vtss_state, vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id,
                      vtss_vcap_id_t ins_id, vtss_vcap_data_t *data, BOOL dont_add)
{
    u32                  cnt = 0, ndx_ins = 0, ndx_old = 0, ndx_old_key[VTSS_VCAP_KEY_SIZE_MAX];
    vtss_vcap_entry_t    *cur, *prev = NULL;
    vtss_vcap_entry_t    *old = NULL, *old_prev = NULL, *ins = NULL, *ins_prev = NULL;
    vtss_vcap_idx_t      idx;
    vtss_vcap_key_size_t key_size, key_size_new;
    vtss_res_chg_t       chg;
    vtss_vcap_id_t       cur_id;
    vtss_vcap_entry_t    **free_list = &obj->free;
    u32                  *rule_count = &obj->rule_count;

    key_size_new = (data ? data->key_size : VTSS_VCAP_KEY_SIZE_FULL);
    VTSS_MEMSET(ndx_old_key, 0, sizeof(ndx_old_key));

    VTSS_D("VCAP %s, key_size: %s, id: %s, ins_id: %s",
           obj->name, vtss_vcap_key_size2txt(key_size_new),
           vtss_vcap_id_txt(vtss_state, id), vtss_vcap_id_txt(vtss_state, ins_id));

    if (id == VTSS_VCAP_ID_LAST || id == VTSS_VCAP_ID_GT) {
        VTSS_E("VCAP %s, illegal id: %s", obj->name, vtss_vcap_id_txt(vtss_state, id));
        return VTSS_RC_ERROR;
    }

    for (cur = obj->used; cur != NULL; prev = cur, cur = cur->next) {
        /* No further processing if bigger user found */
        if (cur->user > user)
            break;

        /* Look for existing ID and next ID */
        if (cur->user == user) {
            cur_id = cur->id;
            if (cur_id == id) {
                /* Found ID */
                VTSS_D("found old id");
                old = cur;
                old_prev = prev;
            }

            if (ins == NULL &&
                (cur_id == ins_id ||
                 (ins_id == VTSS_VCAP_ID_GT && cur_id > id))) {
                /* Found place to insert */
                VTSS_D("found ins_id");
                ins = cur;
                ins_prev = prev;
            }
        }

        /* Count entries depending on key size */
        key_size = cur->data.key_size;
        if (key_size > VTSS_VCAP_KEY_SIZE_LAST) {
            VTSS_E("VCAP %s key size exceeded", obj->name);
            return VTSS_RC_ERROR;
        }

        /* Count number of rules smaller than insert entry */
        if (ins == NULL && key_size == key_size_new)
            ndx_ins++;

        /* Count number of rules smaller than old entry */
        if (old == NULL)
            ndx_old_key[key_size]++;
    }

    /* Check if insert ID is valid */
    if (ins == NULL) {
        if (ins_id != VTSS_VCAP_ID_LAST && ins_id != VTSS_VCAP_ID_GT) {
            VTSS_E("VCAP %s: Could not find Insert ID: %s, ID: %s",
                   obj->name, vtss_vcap_id_txt(vtss_state, ins_id), vtss_vcap_id_txt(vtss_state, id));
            return VTSS_RC_ERROR;
        }
        ins_prev = prev;
    }

    /* Check if resources are available */
    if (old == NULL || old->data.key_size != key_size_new) {
        VTSS_MEMSET(&chg, 0, sizeof(chg));

        /* Calculate added resources */
        if ((obj->key_count[key_size_new] % vtss_vcap_key_rule_count(key_size_new)) == 0)
            chg.add++;

        /* Calculate deleted resources */
        if (old != NULL) {
            key_size = old->data.key_size;
            if ((obj->key_count[key_size] % vtss_vcap_key_rule_count(key_size)) == 1)
                chg.del++;
        }
        VTSS_RC(vtss_cmn_vcap_res_check(obj, &chg));
    }

    /* Return here if only checking if entry can be added */
    if (data == NULL || dont_add)
        return VTSS_RC_OK;

    /* Read counter */
    if (old == NULL) {
        key_size = key_size_new; /* Just to please Lint */
    } else {
        key_size = old->data.key_size;
        ndx_old = ndx_old_key[key_size];
        idx.key_size = key_size;
        vtss_vcap_pos_get(obj, &idx, ndx_old);
        if (!vtss_state->warm_start_cur) {
            /* No need to read counter in warm start mode */
            VTSS_RC(obj->entry_get(vtss_state, &idx, &cnt, 0));
        }
    }

    if (old == NULL || key_size != key_size_new || (ndx_old + 1) != ndx_ins) {
        /* New entry or changed key size/position, delete/add is required */
        if (old == NULL) {
            VTSS_D("new rule, ndx_ins: %u", ndx_ins);
        } else {
            VTSS_D("changed key_size/position");
            VTSS_RC(vtss_vcap_del_rule(vtss_state, obj, old, old_prev, ndx_old));
            if (key_size == key_size_new) {
                VTSS_D("new position, ndx_ins: %u, ndx_old: %u", ndx_ins, ndx_old);
                if (ndx_ins > ndx_old) {
                    /* The deleted old entry was before the new index, adjust for that */
                    ndx_ins--;
                }
            } else {
                VTSS_D("new key_size, ndx_ins: %u", ndx_ins);
            }
            if (ins_prev == old) {
                /* Old entry was just deleted, adjust for that */
                ins_prev = old_prev;
            }
        }

        /* Insert new rule in used list */
#if defined(VTSS_FEATURE_VCAP_SUPER)
        if (obj->vcap_super != NULL) {
            /* Use VCAP_SUPER free list if valid */
            free_list = &obj->vcap_super->free;
            rule_count = &obj->vcap_super->rule_count;
        }
#endif /* VTSS_FEATURE_VCAP_SUPER */
        if ((cur = *free_list) == NULL) {
            VTSS_E("VCAP %s: No more free rules", obj->name);
            return VTSS_RC_ERROR;
        }
        *free_list = cur->next;
        *rule_count = (*rule_count + 1);
        if (ins_prev == NULL) {
            cur->next = obj->used;
            obj->used = cur;
        } else {
            cur->next = ins_prev->next;
            ins_prev->next = cur;
        }
        cur->user = user;
        cur->id = id;

        /* Get position of the entry after the last entry in block */
        key_size = key_size_new;
        idx.key_size = key_size;
        vtss_vcap_pos_get(obj, &idx, key_size == VTSS_VCAP_KEY_SIZE_FULL ? ndx_ins :
                          obj->key_count[key_size]);
        if (idx.col == 0) {
#if defined(VTSS_FEATURE_VCAP_SUPER)
            VTSS_RC(vtss_vcap_super_add(vtss_state, obj));
#endif /* VTSS_FEATURE_VCAP_SUPER */
            if (!vtss_state->warm_start_cur && idx.row < obj->count) {
                /* Move rows down */
                idx.key_size = VTSS_VCAP_KEY_SIZE_FULL;
                VTSS_RC(obj->entry_move(vtss_state, &idx, obj->count - idx.row, 0));
            }
            obj->count++;
        }

        /* Move rules down */
        if (!vtss_state->warm_start_cur && key_size != VTSS_VCAP_KEY_SIZE_FULL &&
            obj->key_count[key_size] > ndx_ins) {
            idx.key_size = key_size;
            vtss_vcap_pos_get(obj, &idx, ndx_ins);
            VTSS_RC(obj->entry_move(vtss_state, &idx, obj->key_count[key_size] - ndx_ins, 0));
        }
        obj->key_count[key_size]++;
    } else {
        VTSS_D("rule unchanged");
        cur = old;
        ndx_ins = ndx_old;
    }

    cur->data = *data;

    /* Save a copy if storage is provided. Used for warm start and key size changes */
    data = &cur->data;
    if (obj->type == VTSS_VCAP_TYPE_IS0) {
#if defined(VTSS_FEATURE_IS0)
        vtss_is0_entry_t *copy = cur->copy;
        if (copy) {
            *copy = *data->u.is0.entry;
        }
#endif /* VTSS_FEATURE_IS0 */
    } else if (obj->type == VTSS_VCAP_TYPE_IS1) {
#if defined(VTSS_FEATURE_IS1)
        vtss_is1_entry_t *copy = cur->copy;
        if (copy) {
            *copy = *data->u.is1.entry;
        }
#endif /* VTSS_FEATURE_IS1 */
    } else if (obj->type == VTSS_VCAP_TYPE_IS2) {
#if defined(VTSS_FEATURE_IS2)
        vtss_is2_entry_t *copy = cur->copy;
        if (copy) {
            *copy = *data->u.is2.entry;
        }
#endif /* VTSS_FEATURE_IS2 */
    } else if (obj->type == VTSS_VCAP_TYPE_ES0) {
#if defined(VTSS_FEATURE_ES0)
        vtss_es0_entry_t *copy = cur->copy;
        if (copy) {
            *copy = *data->u.es0.entry;
        }
#endif /* VTSS_FEATURE_ES0 */
    }

    /* Write entry */
    if (vtss_state->warm_start_cur) {
        return VTSS_RC_OK;
    } else {
        idx.key_size = key_size_new;
        vtss_vcap_pos_get(obj, &idx, ndx_ins);
        return obj->entry_add(vtss_state, &idx, data, cnt);
    }
}

/* Get next ID for one user based on another user (special function for PTP) */
vtss_rc vtss_vcap_get_next_id(vtss_vcap_obj_t *obj, int user1, int user2,
                              vtss_vcap_id_t id, vtss_vcap_id_t *ins_id)
{
    vtss_vcap_entry_t *cur, *next;

    /* Look for entry in user1 list */
    *ins_id = VTSS_VCAP_ID_LAST;
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->user == user1 && cur->id == id) {
            /* Found entry */
            next = cur->next;
            break;
        }
    }

    if (cur == NULL) {
        VTSS_E("VCAP %s: ID not found", obj->name);
        return VTSS_RC_ERROR;
    }

    /* Look for entry in user2 list */
    for (next = cur->next; next != NULL && next->user == user1; next = next->next) {
        for (cur = obj->used; cur != NULL; cur = cur->next) {
            if (cur->user == user2 && cur->id == next->id) {
                *ins_id = cur->id;
                return VTSS_RC_OK;
            }
        }
    }
    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_IS0)
void vtss_vcap_is0_init(vtss_vcap_data_t *data, vtss_is0_entry_t *entry)
{
    vtss_is0_data_t *is0 = &data->u.is0;

    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    is0->entry = entry;
}
#endif /* VTSS_FEATURE_IS0 */

#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
vtss_vcap_obj_t *vtss_vcap_is1_obj_get(vtss_state_t *vtss_state)
{
#if defined(VTSS_FEATURE_IS1)
    return &vtss_state->vcap.is1.obj;
#endif /* VTSS_FEATURE_IS1 */
#if defined(VTSS_FEATURE_CLM)
    return &vtss_state->vcap.clm_b.obj;
#endif /* VTSS_FEATURE_CLM */
}

void vtss_vcap_is1_init(vtss_vcap_data_t *data, vtss_is1_entry_t *entry)
{
    vtss_is1_data_t *is1 = &data->u.is1;

    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    is1->vid_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->dscp_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->sport_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->dport_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->port_no = VTSS_PORT_NO_NONE;
    is1->entry = entry;
}

#if defined(VTSS_ARCH_LAN966X)
vtss_rc vtss_vcap_is1_update(vtss_state_t *vtss_state, vtss_is1_action_t *act)
{
    vtss_vcap_obj_t      *obj = &vtss_state->vcap.is1.obj;
    vtss_vcap_entry_t    *cur;
    vtss_vcap_data_t     *data;
    vtss_vcap_key_size_t key_size;
    vtss_vcap_idx_t      idx;
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];

    VTSS_MEMSET(ndx, 0, sizeof(ndx));
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        data = &cur->data;
        key_size = data->key_size;
        if (data->u.is1.isdx == act->isdx) {
            idx.key_size = key_size;
            vtss_vcap_pos_get(obj, &idx, ndx[key_size]);
            VTSS_FUNC_RC(vcap.is1_entry_update, &idx, act);
        }
        ndx[key_size]++;
    }
    return VTSS_RC_OK;
}
#endif

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
vtss_rc vtss_vcap_clm_update(vtss_state_t *vtss_state, const vtss_qos_egress_map_id_t id)
{
    u32                  i, ndx[VTSS_VCAP_KEY_SIZE_MAX];
    vtss_vcap_obj_t      *obj;
    vtss_vcap_type_t     type;
    vtss_vcap_entry_t    *cur;
    vtss_is1_data_t      *data;
    vtss_vcap_key_size_t key_size;
    vtss_vcap_idx_t      idx;

    /* Avoid updating CLM in warm start mode */
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    /* Update CLM_A, CLM_B and CLM_C */
    for (i = 0; i < 3; i++) {
        switch (i) {
        case 0:
            obj = &vtss_state->vcap.clm_a.obj;
            type = VTSS_VCAP_TYPE_CLM_A;
            break;
        case 1:
            obj = &vtss_state->vcap.clm_b.obj;
            type = VTSS_VCAP_TYPE_CLM_B;
            break;
        case 2:
            obj = &vtss_state->vcap.clm_c.obj;
            type = VTSS_VCAP_TYPE_CLM_C;
            break;
        }
        VTSS_MEMSET(ndx, 0, sizeof(ndx));
        for (cur = obj->used; cur != NULL; cur = cur->next) {
            key_size = cur->data.key_size;
            data = &cur->data.u.is1;
            if ((data->flags & VTSS_IS1_FLAG_MAP_ID) && data->map_id == id) {
                idx.key_size = key_size;
                vtss_vcap_pos_get(obj, &idx, ndx[key_size]);
                VTSS_FUNC_RC(vcap.clm_entry_update, type, &idx, data);
            }
            ndx[key_size]++;
        }
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_CLM) && defined(VTSS_ARCH_JAGUAR_2)
vtss_rc vtss_vcap_clm_update_masq_hit_ena(vtss_state_t *vtss_state,
                                          vtss_vcap_obj_t *obj, int user, vtss_vcap_id_t id, BOOL enable)
{
    vtss_vcap_entry_t    *cur;
    vtss_vcap_key_size_t key_size;
    vtss_vcap_type_t     type;
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];
    vtss_vcap_idx_t      idx;

    VTSS_D("VCAP %s, id: %s  enable %u", obj->name, vtss_vcap_id_txt(vtss_state, id), enable);

    if (obj == &vtss_state->vcap.clm_a.obj) {
        type = VTSS_VCAP_TYPE_CLM_A;
    } else if (obj == &vtss_state->vcap.clm_b.obj) {
        type = VTSS_VCAP_TYPE_CLM_B;
    } else if (obj == &vtss_state->vcap.clm_c.obj) {
        type = VTSS_VCAP_TYPE_CLM_C;
    } else {
        type = VTSS_VCAP_TYPE_CLM_B;
        VTSS_E("VCAP %s, id: %s  VCAP type not detected", obj->name, vtss_vcap_id_txt(vtss_state, id));
    }
    VTSS_MEMSET(ndx, 0, sizeof(ndx));
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        key_size = cur->data.key_size;
        if (cur->user == user && cur->id == id) {
            /* Found rule */
            idx.key_size = key_size;
            vtss_vcap_pos_get(obj, &idx, ndx[key_size]);
            VTSS_FUNC_RC(vcap.clm_entry_update_masq_hit_ena, type, &idx, &cur->data, enable);
        }
        ndx[key_size]++;
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_CLM */
#endif /* VTSS_FEATURE_IS1/CLM */

#if defined(VTSS_FEATURE_IS2)
void vtss_vcap_is2_init(vtss_vcap_data_t *data, vtss_is2_entry_t *entry)
{
    vtss_is2_data_t *is2 = &data->u.is2;

    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    is2->srange = VTSS_VCAP_RANGE_CHK_NONE;
    is2->drange = VTSS_VCAP_RANGE_CHK_NONE;
    is2->entry = entry;
}
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_ES0)
void vtss_vcap_es0_init(vtss_vcap_data_t *data, vtss_es0_entry_t *entry)
{
    VTSS_MEMSET(data, 0, sizeof(*data));
    VTSS_MEMSET(entry, 0, sizeof(*entry));
    data->u.es0.entry = entry;
    entry->key.rx_port_no = VTSS_PORT_NO_NONE;
}

/* Update ES0 action fields based on VLAN and QoS port configuration */
void vtss_cmn_es0_action_get(vtss_state_t *vtss_state, vtss_es0_data_t *es0)
{
    vtss_es0_action_t *action = &es0->entry->action;

    if (es0->flags & (VTSS_ES0_FLAG_OT_VLAN | VTSS_ES0_FLAG_IT_VLAN)) {
        /* Update VLAN action */
        vtss_vlan_port_conf_t *conf = &vtss_state->l2.vlan_port_conf[es0->port_no];
        vtss_vid_t            uvid = conf->untagged_vid;
        vtss_vlan_port_type_t type = conf->port_type;
        vtss_es0_tag_t        tag = (uvid == VTSS_VID_ALL || uvid == es0->vid ? VTSS_ES0_TAG_NONE : VTSS_ES0_TAG_ES0);
        vtss_es0_tpid_t       tpid = (type == VTSS_VLAN_PORT_TYPE_S ? VTSS_ES0_TPID_S :
                                      type == VTSS_VLAN_PORT_TYPE_S_CUSTOM ? VTSS_ES0_TPID_PORT : VTSS_ES0_TPID_C);

#if defined(VTSS_ARCH_LUTON26)
        if (es0->flags & VTSS_ES0_FLAG_OT_UVID) {
            action->tag = tag;
        }
        if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
            action->tpid = tpid;
        }
#else
        if (es0->flags & VTSS_ES0_FLAG_OT_UVID) {
            action->outer_tag.tag = tag;
        }
        if (es0->flags & VTSS_ES0_FLAG_OT_TPID) {
            action->outer_tag.tpid = tpid;
        }
        if (es0->flags & VTSS_ES0_FLAG_IT_TPID) {
            action->inner_tag.tpid = tpid;
        }
        if (es0->flags & VTSS_ES0_FLAG_IT_UVID) {
            action->inner_tag.tag = tag;
        }
#endif
    }

#if defined(VTSS_ARCH_JAGUAR_2)
    /* Default values for PCP/DEI selection, may be overwritten by port or QoS mapping */
    action->outer_tag.pcp.sel = es0->ot.pcp;
    action->outer_tag.dei.sel = es0->ot.dei;
    action->inner_tag.pcp.sel = es0->it.pcp;
    action->inner_tag.dei.sel = es0->it.dei;
#endif

    if (es0->flags & (VTSS_ES0_FLAG_OT_QOS | VTSS_ES0_FLAG_IT_QOS)) {
        /* Update QoS action */
        vtss_qos_port_conf_t   *conf = &vtss_state->qos.port_conf[es0->port_no];
        vtss_tag_remark_mode_t mode = conf->tag_remark_mode;

#if defined(VTSS_ARCH_LUTON26)
        if (es0->flags & VTSS_ES0_FLAG_OT_QOS) {
            action->qos = (mode == VTSS_TAG_REMARK_MODE_CLASSIFIED ? VTSS_ES0_QOS_CLASS :
                           mode == VTSS_TAG_REMARK_MODE_MAPPED ? VTSS_ES0_QOS_MAPPED : VTSS_ES0_QOS_ES0);
        }
        if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
            action->pcp = conf->tag_default_pcp;
        }
        if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
            action->dei = conf->tag_default_dei;
        }
#else
        vtss_es0_pcp_t pcp;
        vtss_es0_dei_t dei;

        switch (mode) {
        case VTSS_TAG_REMARK_MODE_CLASSIFIED:
            pcp.sel = VTSS_ES0_PCP_CLASS;
            dei.sel = VTSS_ES0_DEI_CLASS;
            break;
        case VTSS_TAG_REMARK_MODE_MAPPED:
            pcp.sel = VTSS_ES0_PCP_MAPPED;
            dei.sel = VTSS_ES0_DEI_MAPPED;
            break;
        default:
            pcp.sel = VTSS_ES0_PCP_ES0;
            dei.sel = VTSS_ES0_DEI_ES0;
            break;
        }
        pcp.val = conf->tag_default_pcp;
        dei.val = conf->tag_default_dei;

        if (es0->flags & VTSS_ES0_FLAG_OT_PCP) {
            action->outer_tag.pcp = pcp;
        }
        if (es0->flags & VTSS_ES0_FLAG_OT_DEI) {
            action->outer_tag.dei = dei;
        }
        if (es0->flags & VTSS_ES0_FLAG_IT_PCP) {
            action->inner_tag.pcp = pcp;
        }
        if (es0->flags & VTSS_ES0_FLAG_IT_DEI) {
            action->inner_tag.dei = dei;
        }
#endif
    }
}

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
vtss_rc vtss_vcap_es0_emap_update(vtss_state_t *vtss_state, vtss_qos_egress_map_id_t map_id)
{
    vtss_vcap_entry_t *cur;
    vtss_es0_data_t   *data;
    vtss_vcap_idx_t   idx;
    vtss_es0_entry_t  entry;

    /* Avoid updating ES0 in warm start mode */
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = vtss_state->vcap.es0.obj.used; cur != NULL; cur = cur->next, idx.row++) {
        data = &cur->data.u.es0;
        if (((data->flags & VTSS_ES0_FLAG_MAP_ID_OT) && data->map_id_ot == map_id) ||
            ((data->flags & VTSS_ES0_FLAG_MAP_ID_IT) && data->map_id_it == map_id) ||
            ((data->flags & (VTSS_ES0_FLAG_OT_QOS | VTSS_ES0_FLAG_IT_QOS)) &&
             vtss_state->qos.port_conf[data->port_no].egress_map == map_id)) {
            data->entry = &entry;
            vtss_cmn_es0_action_get(vtss_state, data);
            VTSS_FUNC_RC(vcap.es0_entry_update, &idx, data);
        }
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

vtss_rc vtss_vcap_es0_update(vtss_state_t *vtss_state,
                             const vtss_port_no_t port_no, u16 flags)
{
    vtss_vcap_entry_t *cur;
    vtss_es0_data_t   *data;
    vtss_vcap_idx_t   idx;
    vtss_es0_entry_t  entry;

    /* Avoid updating ES0 in warm start mode */
    if (vtss_state->warm_start_cur)
        return VTSS_RC_OK;

    VTSS_MEMSET(&idx, 0, sizeof(idx));
    for (cur = vtss_state->vcap.es0.obj.used; cur != NULL; cur = cur->next, idx.row++) {
        data = &cur->data.u.es0;
        if ((data->port_no == port_no && (data->flags & flags & VTSS_ES0_FLAG_MASK_PORT)) ||
            (data->nni == port_no && (data->flags & flags & VTSS_ES0_FLAG_MASK_NNI))) {
            data->entry = &entry;
            vtss_cmn_es0_action_get(vtss_state, data);
            VTSS_FUNC_RC(vcap.es0_entry_update, &idx, data);
        }
    }
    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_ES0 */

/* - ACL ----------------------------------------------------------- */

/* Update ACL port redirect */
vtss_rc vtss_vcap_is2_update(vtss_state_t *vtss_state)
{
    vtss_vcap_state_t    *vcap = &vtss_state->vcap;
    vtss_vcap_obj_t      *obj = &vcap->is2.obj;
    vtss_port_no_t       port_no;
    vtss_acl_port_conf_t *conf;
    vtss_vcap_entry_t    *cur;
    vtss_is2_data_t      *is2;
    vtss_vcap_idx_t      idx;
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];

    /* Update port actions */
    for (port_no = 0; port_no < vtss_state->port_count; port_no++) {
        conf = &vcap->acl_port_conf[port_no];
        if (conf->action.port_action == VTSS_ACL_PORT_ACTION_REDIR) {
            VTSS_I("update port_no: %u", port_no);
            vcap->acl_old_port_conf = *conf;
            VTSS_FUNC_RC(vcap.acl_port_set, port_no);
        }
    }

    /* Update IS2 rules */
    VTSS_MEMSET(ndx, 0, sizeof(ndx));
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        idx.key_size = cur->data.key_size;
        is2 = &cur->data.u.is2;
        if (is2->action.redir) {
            vtss_vcap_pos_get(obj, &idx, ndx[idx.key_size]);
            VTSS_I("update row: %u, col: %u", idx.row, idx.col);
            VTSS_FUNC_RC(vcap.is2_entry_update, &idx, is2);
        }
        ndx[idx.key_size]++;
    }
    return VTSS_RC_OK;
}

/* Add ACE check */
vtss_rc vtss_cmn_ace_add(vtss_state_t *vtss_state,
                         const vtss_ace_id_t ace_id, const vtss_ace_t *const ace)
{
    /* Check ACE ID */
    if (ace->id == VTSS_ACE_ID_LAST || ace->id == ace_id) {
        VTSS_E("illegal ace id: %u", ace->id);
        return VTSS_RC_ERROR;
    }

    /* Check frame type */
    if (ace->type > VTSS_ACE_TYPE_IPV6) {
        VTSS_E("illegal type: %d", ace->type);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

/* Delete ACE */
vtss_rc vtss_cmn_ace_del(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    vtss_vcap_obj_t  *obj = &vtss_state->vcap.is2.obj;
    vtss_vcap_data_t data;

    if (vtss_vcap_lookup(vtss_state, obj, vtss_state->vcap.acl_user, ace_id, &data, NULL) != VTSS_RC_OK) {
        VTSS_E("ace_id: %u not found", ace_id);
        return VTSS_RC_ERROR;
    }

    /* Delete range checkers and main entry */
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, data.u.is2.srange));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, data.u.is2.drange));
    VTSS_RC(vtss_vcap_del(vtss_state, obj, vtss_state->vcap.acl_user, ace_id));

    return VTSS_RC_OK;
}

/* Get/clear ACE counter */
static vtss_rc vtss_cmn_ace_get(vtss_state_t *vtss_state,
                                const vtss_ace_id_t ace_id,
                                vtss_ace_counter_t *const counter,
                                BOOL clear)
{
    vtss_vcap_idx_t idx;
    vtss_vcap_obj_t *obj = &vtss_state->vcap.is2.obj;

    if (vtss_vcap_lookup(vtss_state, obj, vtss_state->vcap.acl_user, ace_id, NULL, &idx) != VTSS_RC_OK) {
        VTSS_E("ace_id: %u not found", ace_id);
        return VTSS_RC_ERROR;
    }
    VTSS_RC(obj->entry_get(vtss_state, &idx, counter, clear));

    return VTSS_RC_OK;
}

/* Get ACE counter */
vtss_rc vtss_cmn_ace_counter_get(vtss_state_t *vtss_state,
                                 const vtss_ace_id_t ace_id, vtss_ace_counter_t *const counter)
{
    return vtss_cmn_ace_get(vtss_state, ace_id, counter, 0);
}

/* Clear ACE counter */
vtss_rc vtss_cmn_ace_counter_clear(vtss_state_t *vtss_state, const vtss_ace_id_t ace_id)
{
    vtss_ace_counter_t counter;

    return vtss_cmn_ace_get(vtss_state, ace_id, &counter, 1);
}

char *vtss_acl_policy_no_txt(vtss_acl_policy_no_t policy_no, char *buf)
{
    if (policy_no == VTSS_ACL_POLICY_NO_NONE)
        VTSS_STRCPY(buf, "None");
    else
        VTSS_SPRINTF(buf, "%u", policy_no);
    return buf;
}

/* - Access Control Lists ------------------------------------------ */

static vtss_rc vtss_acl_policer_no_check(const vtss_acl_policer_no_t  policer_no)
{
    if (policer_no >= VTSS_ACL_POLICERS) {
        VTSS_E("illegal policer_no: %u", policer_no);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_acl_policer_conf_get(const vtss_inst_t            inst,
                                  const vtss_acl_policer_no_t  policer_no,
                                  vtss_acl_policer_conf_t      *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("policer_no: %u", policer_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_acl_policer_no_check(policer_no)) == VTSS_RC_OK)
        *conf = vtss_state->vcap.acl_policer_conf[policer_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_acl_policer_conf_set(const vtss_inst_t              inst,
                                  const vtss_acl_policer_no_t    policer_no,
                                  const vtss_acl_policer_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("policer_no: %u", policer_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK &&
        (rc = vtss_acl_policer_no_check(policer_no)) == VTSS_RC_OK) {
        vtss_state->vcap.acl_policer_conf[policer_no] = *conf;
        rc = VTSS_FUNC_COLD(vcap.acl_policer_set, policer_no);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
vtss_rc vtss_acl_sip_conf_set(const vtss_inst_t          inst,
                              const vtss_acl_sip_idx_t   idx,
                              const vtss_acl_sip_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("idx: %u", idx);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        if (idx < VTSS_ACL_SIP_CNT && (conf->sip.type == VTSS_IP_TYPE_IPV4 || (idx % 4) == 0)) {
            vtss_state->vcap.acl_sip_table[idx] = *conf;
            rc = VTSS_FUNC_COLD(vcap.acl_sip_set, idx);
        } else {
            VTSS_E("illegal idx: %u", idx);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}
#endif

vtss_rc vtss_acl_port_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_acl_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        *conf = vtss_state->vcap.acl_port_conf[port_no];
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_acl_port_conf_set(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no,
                               const vtss_acl_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        vtss_state->vcap.acl_old_port_conf = vtss_state->vcap.acl_port_conf[port_no];
        vtss_state->vcap.acl_port_conf[port_no] = *conf;
        rc = VTSS_FUNC_COLD(vcap.acl_port_set, port_no);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_acl_port_counter_get(const vtss_inst_t        inst,
                                  const vtss_port_no_t     port_no,
                                  vtss_acl_port_counter_t  *const counter)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_port_counter_get, port_no, counter);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_acl_port_counter_clear(const vtss_inst_t     inst,
                                    const vtss_port_no_t  port_no)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_port_counter_clear, port_no);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ace_init(const vtss_inst_t      inst,
                      const vtss_ace_type_t  type,
                      vtss_ace_t             *const ace)
{
    VTSS_D("type: %d", type);

    VTSS_MEMSET(ace, 0, sizeof(*ace));
    ace->type = type;
    ace->action.learn = 1;

    switch (type) {
    case VTSS_ACE_TYPE_ANY:
    case VTSS_ACE_TYPE_ETYPE:
    case VTSS_ACE_TYPE_LLC:
    case VTSS_ACE_TYPE_SNAP:
    case VTSS_ACE_TYPE_ARP:
        break;
    case VTSS_ACE_TYPE_IPV4:
        ace->frame.ipv4.sport.high = 0xffff;
        ace->frame.ipv4.sport.in_range = 1;
        ace->frame.ipv4.dport.high = 0xffff;
        ace->frame.ipv4.dport.in_range = 1;
        break;
    case VTSS_ACE_TYPE_IPV6:
        ace->frame.ipv6.sport.high = 0xffff;
        ace->frame.ipv6.sport.in_range = 1;
        ace->frame.ipv6.dport.high = 0xffff;
        ace->frame.ipv6.dport.in_range = 1;
        break;
    default:
        VTSS_E("unknown type: %d", type);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_ace_add(const vtss_inst_t    inst,
                     const vtss_ace_id_t  ace_id,
                     const vtss_ace_t     *const ace)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("ace_id: %u before %u %s",
           ace->id, ace_id, ace_id == VTSS_ACE_ID_LAST ? "(last)" : "");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_ace_add, ace_id, ace);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ace_del(const vtss_inst_t    inst,
                     const vtss_ace_id_t  ace_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("ace_id: %u", ace_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_ace_del, ace_id);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ace_counter_get(const vtss_inst_t    inst,
                             const vtss_ace_id_t  ace_id,
                             vtss_ace_counter_t   *const counter)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("ace_id: %u", ace_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_ace_counter_get, ace_id, counter);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_ace_counter_clear(const vtss_inst_t    inst,
                               const vtss_ace_id_t  ace_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("ace_id: %u", ace_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_ace_counter_clear, ace_id);
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_LUTON26)
vtss_rc vtss_ace_status_get(const vtss_inst_t    inst,
                            const vtss_ace_id_t  ace_id,
                            vtss_ace_status_t    *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("ace_id: %u", ace_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.acl_ace_status_get, ace_id, status);
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_ARCH_LUTON26 */
#endif // VTSS_FEATURE_VCAP

/* - Hierarchical ACLs --------------------------------------------- */

void vtss_rleg_list_set(vtss_rleg_list_t *l, vtss_l3_rleg_id_t rleg, BOOL val)
{
    u32 i = (rleg / 8);
    u8  m = (1 << (rleg % 8));

    if (i < VTSS_RLEG_LIST_ARRAY_SIZE) {
        if (val) {
            l->_private[i] |= m;
        } else {
            l->_private[i] &= ~m;
        }
    }
}

BOOL vtss_rleg_list_get(const vtss_rleg_list_t *l, vtss_l3_rleg_id_t rleg)
{
    u32 i = (rleg / 8);
    u8  m = (1 << (rleg % 8));

    return (i < VTSS_RLEG_LIST_ARRAY_SIZE && (l->_private[i] & m) ? 1 : 0);
}

#if defined(VTSS_FEATURE_VCAP)
#if defined(VTSS_FEATURE_HACL)
vtss_rc vtss_hace_init(const vtss_inst_t     inst,
                       const vtss_ace_type_t type,
                       vtss_hace_t           *const hace)
{
    vtss_hace_key_t *key = &hace->key;

    VTSS_D("type: %d", type);

    VTSS_MEMSET(hace, 0, sizeof(*hace));
    key->type = type;

    switch (type) {
    case VTSS_ACE_TYPE_ANY:
    case VTSS_ACE_TYPE_ETYPE:
    case VTSS_ACE_TYPE_LLC:
    case VTSS_ACE_TYPE_SNAP:
    case VTSS_ACE_TYPE_ARP:
        break;
    case VTSS_ACE_TYPE_IPV4:
        key->ipv4.sport.high = 0xffff;
        key->ipv4.sport.in_range = 1;
        key->ipv4.dport.high = 0xffff;
        key->ipv4.dport.in_range = 1;
        break;
    case VTSS_ACE_TYPE_IPV6:
        key->ipv6.sport.high = 0xffff;
        key->ipv6.sport.in_range = 1;
        key->ipv6.dport.high = 0xffff;
        key->ipv6.dport.in_range = 1;
        break;
    default:
        VTSS_E("unknown type: %d", type);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

const char *vtss_hacl_type_txt(const vtss_hacl_type_t type)
{
    return (type == VTSS_HACL_TYPE_IPACL ? "I-PACL" :
            type == VTSS_HACL_TYPE_IVACL ? "I-VACL" :
            type == VTSS_HACL_TYPE_IRACL ? "I-RACL" :
            type == VTSS_HACL_TYPE_ERACL ? "E-RACL" :
            type == VTSS_HACL_TYPE_EVACL ? "E-VACL" :
            type == VTSS_HACL_TYPE_EPACL ? "E-PACL" : "?");
}

vtss_rc vtss_hace_add(const vtss_inst_t      inst,
                      const vtss_hacl_type_t type,
                      const vtss_ace_id_t    ace_id_next,
                      const vtss_hace_t      *const hace)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("type: %s, id: %u before %u %s",
           vtss_hacl_type_txt(type), hace->id, ace_id_next, ace_id_next == VTSS_ACE_ID_LAST ? "(last)" : "");
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.hace_add, type, ace_id_next, hace);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_hace_del(const vtss_inst_t      inst,
                      const vtss_hacl_type_t type,
                      const vtss_ace_id_t    ace_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("type: %s, ace_id: %u", vtss_hacl_type_txt(type), ace_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.hace_del, type, ace_id);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_hace_counter_get(const vtss_inst_t      inst,
                              const vtss_hacl_type_t type,
                              const vtss_ace_id_t    ace_id,
                              vtss_ace_counter_t     *const counter)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("type: %s, ace_id: %u", vtss_hacl_type_txt(type), ace_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.hace_counter_get, type, ace_id, counter);
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_hace_counter_clear(const vtss_inst_t      inst,
                                const vtss_hacl_type_t type,
                                const vtss_ace_id_t    ace_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("type: %s, ace_id: %u", vtss_hacl_type_txt(type), ace_id);
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK)
        rc = VTSS_FUNC(vcap.hace_counter_clear, type, ace_id);
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_HACL */

/* - Warm start synchronization ------------------------------------ */

static vtss_rc vtss_vcap_sync_obj(vtss_state_t *vtss_state, vtss_vcap_obj_t *obj)
{
#if defined(VTSS_OPT_WARM_START)
    vtss_vcap_entry_t    *cur;
    vtss_vcap_data_t     *data;
    vtss_vcap_idx_t      idx;
    vtss_vcap_key_size_t key_size;
    u32                  ndx[VTSS_VCAP_KEY_SIZE_MAX];

    VTSS_I("VCAP %s", obj->name);

    /* Add/update entries */
    VTSS_MEMSET(ndx, 0, sizeof(ndx));
    for (cur = obj->used; cur != NULL; cur = cur->next) {
        if (cur->copy == NULL) {
            VTSS_E("VCAP %s: No saved copy", obj->name);
            return VTSS_RC_ERROR;
        }
        data = &cur->data;
        key_size = data->key_size;
        if (obj->type == VTSS_VCAP_TYPE_IS0) {
#if defined(VTSS_FEATURE_IS0)
            data->u.is0.entry = (vtss_is0_entry_t *)cur->copy;
#endif /* VTSS_FEATURE_IS0 */
        } else if (obj->type == VTSS_VCAP_TYPE_IS1) {
#if defined(VTSS_FEATURE_IS1)
            data->u.is1.entry = (vtss_is1_entry_t *)cur->copy;
#endif /* VTSS_FEATURE_IS1 */
        } else if (obj->type == VTSS_VCAP_TYPE_IS2) {
#if defined(VTSS_FEATURE_IS2)
            data->u.is2.entry = (vtss_is2_entry_t *)cur->copy;
#endif /* VTSS_FEATURE_IS2 */
        } else if (obj->type == VTSS_VCAP_TYPE_ES0) {
#if defined(VTSS_FEATURE_ES0)
            data->u.es0.entry = (vtss_es0_entry_t *)cur->copy;
#endif /* VTSS_FEATURE_ES0 */
        }
        idx.key_size = key_size;
        vtss_vcap_pos_get(obj, &idx, ndx[key_size]);
        VTSS_RC(obj->entry_add(vtss_state, &idx, data, 0));
        ndx[key_size]++;
    }

    /* Delete trailing entries */
    for (key_size = VTSS_VCAP_KEY_SIZE_FULL; key_size <= VTSS_VCAP_KEY_SIZE_LAST; key_size++) {
        idx.key_size = key_size;
        while (1) {
            vtss_vcap_pos_get(obj, &idx, ndx[key_size]);
            if (idx.row >= obj->max_count || (key_size != VTSS_VCAP_KEY_SIZE_FULL && idx.col == 0))
                break;
            VTSS_RC(obj->entry_del(vtss_state, &idx));
            ndx[key_size]++;
        }
    }
#endif /* VTSS_OPT_WARM_START */

    return VTSS_RC_OK;
}

#if defined(VTSS_FEATURE_WARM_START)
vtss_rc vtss_vcap_restart_sync(vtss_state_t *vtss_state)
{
    vtss_port_no_t        port_no;
    vtss_acl_policer_no_t policer_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        VTSS_FUNC_RC(vcap.acl_port_set, port_no);
    }

    for (policer_no = 0; policer_no <  VTSS_ACL_POLICERS; policer_no++) {
        VTSS_FUNC_RC(vcap.acl_policer_set, policer_no);
    }

#if defined(VTSS_FEATURE_IS0)
    VTSS_RC(vtss_vcap_sync_obj(vtss_state, &vtss_state->vcap.is0.obj));
#endif /* VTSS_FEATURE_IS0 */
#if defined(VTSS_FEATURE_IS1)
    VTSS_RC(vtss_vcap_sync_obj(vtss_state, &vtss_state->vcap.is1.obj));
#endif /* VTSS_FEATURE_IS1 */
#if defined(VTSS_FEATURE_IS2)
    VTSS_RC(vtss_vcap_sync_obj(vtss_state, &vtss_state->vcap.is2.obj));
#endif /* VTSS_FEATURE_IS2 */
#if defined(VTSS_FEATURE_ES0)
    VTSS_RC(vtss_vcap_sync_obj(vtss_state, &vtss_state->vcap.es0.obj));
#endif /* VTSS_FEATURE_ES0 */

    /* Commit range checkers */
    return VTSS_FUNC_0(vcap.range_commit);
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_vcap_inst_create(vtss_state_t *vtss_state)
{
    vtss_port_no_t    port_no;
    vtss_acl_action_t *action;
    vtss_vcap_entry_t *entry;
    vtss_vcap_obj_t   *obj;
    u32               i;

    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        action = &vtss_state->vcap.acl_port_conf[port_no].action;
        action->learn = 1;
    }

#if defined(VTSS_FEATURE_VCAP_SUPER)
    {
        vtss_vcap_super_obj_t *vcap_super = &vtss_state->vcap.vcap_super;

        vcap_super->block.max_count = VTSS_VCAP_SUPER_BLK_CNT;
        vcap_super->row_count = VTSS_VCAP_SUPER_ROW_CNT;

        /* Add VCAP_SUPER entries to free list */
        vcap_super->max_rule_count = VTSS_VCAP_SUPER_RULE_CNT;
        for (i = 0; i < vcap_super->max_rule_count; i++) {
            entry = &vcap_super->table[i];
            entry->next = vcap_super->free;
            vcap_super->free = entry;
        }
    }
#endif /* VTSS_FEATURE_VCAP_SUPER */

#if defined(VTSS_FEATURE_IS0)
    {
        vtss_is0_info_t *is0 = &vtss_state->vcap.is0;

        /* Add IS0 entries to free list */
        obj = &is0->obj;
        obj->type = VTSS_VCAP_TYPE_IS0;
        obj->name = "IS0";
        if (obj->max_rule_count == 0)
            obj->max_rule_count = obj->max_count;
        for (i = 0; i < obj->max_rule_count; i++) {
            entry = &is0->table[i];
            entry->next = obj->free;
            obj->free = entry;
#if defined(VTSS_OPT_WARM_START)
            entry->copy = &is0->copy[i];
#endif /* VTSS_OPT_WARM_START */
        }
    }
#endif /* VTSS_FEATURE_IS0 */

#if defined(VTSS_FEATURE_IS1)
    {
        vtss_is1_info_t *is1 = &vtss_state->vcap.is1;

        /* Add IS1 entries to free list */
        obj = &is1->obj;
        obj->type = VTSS_VCAP_TYPE_IS1;
        obj->name = "IS1";
        if (obj->max_rule_count == 0)
            obj->max_rule_count = obj->max_count;
        for (i = 0; i < obj->max_rule_count; i++) {
            entry = &is1->table[i];
            entry->next = obj->free;
            obj->free = entry;
#if defined(VTSS_OPT_WARM_START) || defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
            entry->copy = &is1->copy[i];
#endif
        }
    }
#endif /* VTSS_FEATURE_IS1 */

    vtss_state->vcap.acl_user = VTSS_IS2_USER_ACL;
#if defined(VTSS_FEATURE_IS2)
    {
        vtss_is2_info_t *is2 = &vtss_state->vcap.is2;

        /* Add IS2 entries to free list */
        obj = &is2->obj;
        obj->type = VTSS_VCAP_TYPE_IS2;
        obj->name = "IS2";
        if (obj->max_rule_count == 0)
            obj->max_rule_count = obj->max_count;
        for (i = 0; i < obj->max_rule_count; i++) {
            entry = &is2->table[i];
            entry->next = obj->free;
            obj->free = entry;
#if defined(VTSS_OPT_WARM_START)
            entry->copy = &is2->copy[i];
#endif /* VTSS_OPT_WARM_START */
        }
    }
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_IS2_B)
    obj = &vtss_state->vcap.is2_b.obj;
    obj->type = VTSS_VCAP_TYPE_IS2_B;
    obj->name = "IS2_B";
#endif /* VTSS_FEATURE_IS2_B */

#if defined(VTSS_FEATURE_ES0)
    {
        vtss_es0_info_t *es0 = &vtss_state->vcap.es0;

        /* Add ES0 entries to free list */
        obj = &es0->obj;
        obj->type = VTSS_VCAP_TYPE_ES0;
        obj->name = "ES0";
        if (obj->max_rule_count == 0)
            obj->max_rule_count = obj->max_count;
        for (i = 0; i < obj->max_rule_count; i++) {
            entry = &es0->table[i];
            entry->next = obj->free;
            obj->free = entry;
#if defined(VTSS_OPT_WARM_START)
            entry->copy = &es0->copy[i];
#endif /* VTSS_OPT_WARM_START */
        }
    }
#endif /* VTSS_FEATURE_ES0 */

#if defined(VTSS_FEATURE_ES2)
    {
        vtss_es2_info_t *es2 = &vtss_state->vcap.es2;

        /* Add ES2 entries to free list */
        obj = &es2->obj;
        obj->type = VTSS_VCAP_TYPE_ES2;
        obj->name = "ES2";
        if (obj->max_rule_count == 0)
            obj->max_rule_count = obj->max_count;
        for (i = 0; i < obj->max_rule_count; i++) {
            entry = &es2->table[i];
            entry->next = obj->free;
            obj->free = entry;
#if defined(VTSS_OPT_WARM_START)
            entry->copy = &es2->copy[i];
#endif /* VTSS_OPT_WARM_START */
        }
    }
#endif /* VTSS_FEATURE_ES2 */

#if defined(VTSS_FEATURE_CLM)
    vtss_state->vcap.clm_a.obj.type = VTSS_VCAP_TYPE_CLM_A;
    vtss_state->vcap.clm_a.obj.name = "CLM_A";
    vtss_state->vcap.clm_b.obj.type = VTSS_VCAP_TYPE_CLM_B;
    vtss_state->vcap.clm_b.obj.name = "CLM_B";
    vtss_state->vcap.clm_c.obj.type = VTSS_VCAP_TYPE_CLM_C;
    vtss_state->vcap.clm_c.obj.name = "CLM_C";
#endif /* VTSS_FEATURE_CLM */

#if defined(VTSS_FEATURE_LPM)
    vtss_state->vcap.lpm.obj.type = VTSS_VCAP_TYPE_LPM;
    vtss_state->vcap.lpm.obj.name = "LPM";
#endif /* VTSS_FEATURE_LPM */

    return VTSS_RC_OK;
}

/* - Debug print --------------------------------------------------- */

void vtss_vcap_debug_print_range_checkers(vtss_state_t *vtss_state,
                                          const vtss_debug_printf_t pr,
                                          const vtss_debug_info_t   *const info)
{
    u32                   i;
    vtss_vcap_range_chk_t *entry;

    vtss_debug_print_header(pr, "Range Checkers");
    pr("Index  Type  Count  Range\n");
    for (i = 0; i < VTSS_VCAP_RANGE_CHK_CNT; i++) {
        entry = &vtss_state->vcap.range.entry[i];
        pr("%-5u  %-4s  %-5u  %u-%u\n",
           i,
           entry->type == VTSS_VCAP_RANGE_TYPE_IDLE ? "IDLE" :
           entry->type == VTSS_VCAP_RANGE_TYPE_SPORT ? "S" :
           entry->type == VTSS_VCAP_RANGE_TYPE_DPORT ? "D" :
           entry->type == VTSS_VCAP_RANGE_TYPE_SDPORT ? "SD" :
           entry->type == VTSS_VCAP_RANGE_TYPE_VID ? "VID" :
           entry->type == VTSS_VCAP_RANGE_TYPE_DSCP ? "DSCP" : "?",
           entry->count,
           entry->min,
           entry->max);
    }
    pr("\n");
}

#if defined(VTSS_FEATURE_VCAP_SUPER)
const char *vtss_vcap_type_txt(vtss_vcap_type_t type)
{
    return (type == VTSS_VCAP_TYPE_NONE ? "NONE" :
            type == VTSS_VCAP_TYPE_IS0 ? "IS0" :
            type == VTSS_VCAP_TYPE_IS1 ? "IS1" :
            type == VTSS_VCAP_TYPE_IS2 ? "IS2" :
            type == VTSS_VCAP_TYPE_IS2_B ? "IS2_B" :
            type == VTSS_VCAP_TYPE_ES0 ? "ES0" :
            type == VTSS_VCAP_TYPE_ES2 ? "ES2" :
            type == VTSS_VCAP_TYPE_CLM_A ? "CLM-A" :
            type == VTSS_VCAP_TYPE_CLM_B ? "CLM-B" :
            type == VTSS_VCAP_TYPE_CLM_C ? "CLM-C" :
            type == VTSS_VCAP_TYPE_LPM ? "LPM" : "?");
}
#endif /* VTSS_FEATURE_VCAP_SUPER */

static void vtss_vcap_debug_print(const vtss_debug_printf_t pr,
                                  const vtss_debug_info_t   *const info,
                                  vtss_vcap_obj_t           *obj,
                                  u32                       data_size,
                                  u32                       obj_size)
{
    u32                   i, low, high;
    vtss_vcap_entry_t     *cur;
    BOOL                  header = 1, resources = FALSE;
    vtss_vcap_user_t      user;
    const char            *name;
    vtss_vcap_key_size_t  key_size;
#if defined(VTSS_FEATURE_VCAP_SUPER)
    vtss_vcap_super_obj_t *vcap_super = obj->vcap_super;

    if (info->has_action) { /* Action parameter is present */
        resources = (info->action == 5) ? TRUE : FALSE;
    }

    if (vcap_super != NULL) {
        vtss_debug_print_header(pr, "VCAP_SUPER");

        pr("obj_size       : %zu\n", sizeof(*vcap_super));
        pr("row_count      : %u\n", vcap_super->row_count);
        pr("max_rule_count : %u\n", vcap_super->max_rule_count);
        pr("rule_count     : %u\n", vcap_super->rule_count);
        pr("block.max_count: %u\n", vcap_super->block.max_count);
        pr("block.count    : %u\n", vcap_super->block.count);
        pr("\n");

        pr("Block  Type\n");
        for (i = 0; i < vcap_super->block.max_count; i++) {
            pr("%-7u%s\n", i, vtss_vcap_type_txt(vcap_super->block_type[i]));
        }
        pr("\n");
    }
#endif /* VTSS_FEATURE_VCAP_SUPER */

    vtss_debug_print_header(pr, obj->name);

    pr("obj_size        : %u\n", obj_size);
    pr("data_size       : %u\n", data_size);
    pr("max_count       : %u\n", obj->max_count);
    pr("count           : %u\n", obj->count);
    pr("max_rule_count  : %u\n", obj->max_rule_count);
    pr("rule_count      : %u\n", obj->rule_count);
    pr("full_count      : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_FULL]);
    pr("half_count      : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_HALF]);
    pr("quarter_count   : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_QUARTER]);
    pr("eighth_count    : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_EIGHTH]);
    pr("twelfth_count   : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_TWELFTH]);
    pr("sixteenth_count : %u\n", obj->key_count[VTSS_VCAP_KEY_SIZE_SIXTEENTH]);

    if (resources) {    /* Only VCAP SUPER and CLM_C resources must be printed */
        return;
    }

    for (cur = obj->used, i = 0; cur != NULL; cur = cur->next, i++) {
        if (header)
            pr("\nIndex  Key Size  User  Name      ID\n");
        header = 0;
        low = (cur->id & 0xffffffff);
        high = ((cur->id >> 32) & 0xffffffff);
        name = "?";
        user = cur->user;
        name = (user == VTSS_IS0_USER_EVC ? "EVC" :
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
                user == VTSS_IS1_USER_MCE_0 ? "MCE_0" :
#else
                user == VTSS_IS1_USER_TT_LOOP_0 ? "TT_LOOP0" :
#endif
                user == VTSS_IS1_USER_VCL ? "VCL" :
                user == VTSS_IS1_USER_VLAN ? "VLAN" :
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
                user == VTSS_IS1_USER_MCE_1 ? "MCE_1" :
                user == VTSS_IS1_USER_MCE_2 ? "MCE_2" :
#else
                user == VTSS_IS1_USER_MEP ? "MEP" :
                user == VTSS_IS1_USER_TT_LOOP_1 ? "TT_LOOP1" :
#endif
                user == VTSS_IS1_USER_ECE ? "ECE" :
                user == VTSS_IS1_USER_EVC ? "EVC" :
                user == VTSS_IS1_USER_EVC_CPU ? "EVC_CPU" :
                user == VTSS_IS1_USER_QOS ? "QoS" :
                user == VTSS_IS1_USER_SSM ? "SSM" :
                user == VTSS_IS1_USER_ACL ? "ACL" :
                user == VTSS_IS1_USER_RCL ? "RCL" :
                user == VTSS_IS2_USER_IGMP ? "IGMP" :
                user == VTSS_IS2_USER_SSM ? "SSM" :
                user == VTSS_IS2_USER_ASM ? "ASM" :
                user == VTSS_IS2_USER_IGMP_ANY ? "IGMP_ANY" :
                user == VTSS_IS2_USER_EEE ? "EEE" :
                user == VTSS_IS2_USER_ACL_PTP ? "ACL_PTP" :
                user == VTSS_IS2_USER_ACL ? "ACL" :
                user == VTSS_IS2_USER_ACL_SIP ? "ACL_SIP" :
                user == VTSS_IS2_USER_IPACL ? "I-PACL" :
                user == VTSS_IS2_USER_IVACL ? "I-VACL" :
                user == VTSS_IS2_USER_IRACL ? "I-RACL" :
                user == VTSS_IS2_USER_ERACL ? "E-RACL" :
                user == VTSS_ES0_USER_TCL ? "TCL" :
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
                user == VTSS_ES0_USER_MCE_0 ? "MCE_0" :
#else
                user == VTSS_ES0_USER_TT_LOOP ? "TT_LOOP" :
#endif
                user == VTSS_ES0_USER_VLAN ? "VLAN" :
#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
                user == VTSS_ES0_USER_MCE_1 ? "MCE_1" :
                user == VTSS_ES0_USER_MCE_2 ? "MCE_2" :
#else
                user == VTSS_ES0_USER_MEP ? "MEP" :
#endif
                user == VTSS_ES0_USER_EVC ? "EVC" :
                user == VTSS_ES0_USER_EFE ? "EFE" :
                user == VTSS_ES0_USER_TX_TAG ? "TX_TAG" :
                user == VTSS_ES0_USER_MPLS ? "MPLS" :
                user == VTSS_ES2_USER_EVACL ? "E-VACL" :
                user == VTSS_ES2_USER_EPACL ? "E-PACL" :
                user == VTSS_LPM_USER_ACL ? "ACL" :
                user == VTSS_LPM_USER_L3 ? "L3_UC" :
                user == VTSS_LPM_USER_L3_MC ? "L3_MC" : "?");
        key_size = cur->data.key_size;
        pr("%-7u%-10s%-6d%-10s0x%08x:0x%08x (%u:%u)\n",
           i, vtss_vcap_key_size2txt(key_size), user, name, high, low, high, low);
    }
    pr("\n");
}

#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
void vtss_vcap_debug_print_is1(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
#if defined(VTSS_FEATURE_IS1)
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.is1.obj,
                          sizeof(vtss_is1_data_t), sizeof(vtss_is1_info_t));
#endif /* VTSS_FEATURE_IS1 */
#if defined(VTSS_FEATURE_CLM)
    vtss_vcap_debug_print_clm_b(vtss_state, pr, info);
#endif /* VTSS_FEATURE_CLM */
}
#endif /* VTSS_FEATURE_IS1/CLM */

#if defined(VTSS_FEATURE_CLM)
void vtss_vcap_debug_print_clm_a(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.clm_a.obj, sizeof(vtss_is1_data_t), sizeof(vtss_clm_info_t));
}

void vtss_vcap_debug_print_clm_b(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.clm_b.obj, sizeof(vtss_is1_data_t), sizeof(vtss_clm_info_t));
}

void vtss_vcap_debug_print_clm_c(vtss_state_t *vtss_state,
                                 const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info)
{
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.clm_c.obj, sizeof(vtss_is1_data_t), sizeof(vtss_clm_info_t));
}
#endif /* VTSS_FEATURE_CLM */

#if defined(VTSS_FEATURE_IS2)
void vtss_vcap_debug_print_is2(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.is2.obj,
                          sizeof(vtss_is2_data_t), sizeof(vtss_is2_info_t));
}
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_ES0)
void vtss_vcap_debug_print_es0(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.es0.obj,
                          sizeof(vtss_es0_data_t), sizeof(vtss_es0_info_t));
}
#endif /* VTSS_FEATURE_ES0 */

static const char *vtss_acl_key_txt(vtss_acl_key_t key)
{
    return (key == VTSS_ACL_KEY_DEFAULT ? "DEF" :
            key == VTSS_ACL_KEY_EXT ? "EXT" :
            key == VTSS_ACL_KEY_ETYPE ? "ETYPE" : "?");
}

void vtss_vcap_debug_print_acl(vtss_state_t *vtss_state,
                               const vtss_debug_printf_t pr,
                               const vtss_debug_info_t   *const info)
{
    vtss_port_no_t        port_no;
    BOOL                  header = 1;
    vtss_acl_port_conf_t  *conf;
    vtss_acl_action_t     *act;
    vtss_acl_policer_no_t policer_no;
    char                  buf[64];

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_ACL))
        return;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        if (!info->port_list[port_no])
            continue;
        conf = &vtss_state->vcap.acl_port_conf[port_no];
        act = &conf->action;
        if (header) {
            header = 0;
            pr("Port  Policy  CPU  Once  Queue  Policer  Learn  IPV4/IPV6/ARP      ");
            vtss_debug_print_port_header(vtss_state, pr, "Mirror  PTP  Port  ", 0, 0);
            pr("\n");
        }
        pr("%-6u%-8s%-5u%-6u%-7u",
           port_no, vtss_acl_policy_no_txt(conf->policy_no, buf),
           act->cpu, act->cpu_once, act->cpu_queue);
        if (act->police)
            VTSS_SPRINTF(buf, "%u (ACL)", act->policer_no);
#if defined(VTSS_ARCH_LUTON26) && defined(VTSS_FEATURE_QOS_POLICER_DLB)
        else if (act->evc_police)
            VTSS_SPRINTF(buf, "%u (EVC)", act->evc_policer_id);
#endif /* VTSS_ARCH_LUTON26 && VTSS_FEATURE_QOS_POLICER_DLB */
        else
            VTSS_STRCPY(buf, "Disabled");
        pr("%-9s%-7u", buf, act->learn);
        VTSS_SPRINTF(buf, "%s/%s/%s",
                vtss_acl_key_txt(conf->key.ipv4),
                vtss_acl_key_txt(conf->key.ipv6),
                vtss_acl_key_txt(conf->key.arp));
        pr("%-19s", buf);
        pr("%-8u%-5s%-6s",
           act->mirror,
           act->ptp_action == VTSS_ACL_PTP_ACTION_NONE ? "None" :
           act->ptp_action == VTSS_ACL_PTP_ACTION_ONE_STEP ? "One" :
           act->ptp_action == VTSS_ACL_PTP_ACTION_TWO_STEP ? "Two" : "?",
           act->port_action == VTSS_ACL_PORT_ACTION_NONE ? "None" :
           act->port_action == VTSS_ACL_PORT_ACTION_FILTER ? "Filt" :
           act->port_action == VTSS_ACL_PORT_ACTION_REDIR ? "Redir" : "?");
        vtss_debug_print_port_members(vtss_state, pr, act->port_list, 0);
        pr("\n");
    }
    if (!header)
        pr("\n");

    pr("Policer  Rate        ");
#if defined(VTSS_ARCH_LUTON26)
    pr("Count  L26 Policer");
#endif /* VTSS_ARCH_LUTON26 */
    pr("\n");
    for (policer_no = VTSS_ACL_POLICER_NO_START; policer_no < VTSS_ACL_POLICER_NO_END; policer_no++) {
        vtss_acl_policer_conf_t *pol_conf = &vtss_state->vcap.acl_policer_conf[policer_no];
        vtss_packet_rate_t      rate;

        if (pol_conf->bit_rate_enable) {
            rate = pol_conf->bit_rate;
            if (rate == VTSS_BITRATE_DISABLED) {
                VTSS_STRCPY(buf, "Disabled");
            } else if (rate < 100000) {
                VTSS_SPRINTF(buf, "%u kbps", rate);
            } else if (rate < 100000000) {
                VTSS_SPRINTF(buf, "%u Mbps", rate/1000);
            } else {
                VTSS_SPRINTF(buf, "%u Gbps", rate/1000000);
            }
        } else {
            rate = pol_conf->rate;
            if (rate == VTSS_PACKET_RATE_DISABLED) {
                VTSS_STRCPY(buf, "Disabled");
            } else if (rate < 100000) {
                VTSS_SPRINTF(buf, "%u pps", rate);
            } else if (rate < 100000000) {
                VTSS_SPRINTF(buf, "%u kpps", rate/1000);
            } else {
                VTSS_SPRINTF(buf, "%u Mpps", rate/1000000);
            }
        }
        pr("%-9u%-12s", policer_no, buf);
#if defined(VTSS_ARCH_LUTON26)
        {
            vtss_policer_alloc_t *pol_alloc = &vtss_state->vcap.acl_policer_alloc[policer_no];
            pr("%-7u%u", pol_alloc->count, pol_alloc->policer);
        }
#endif /* VTSS_ARCH_LUTON26 */
        pr("\n");
    }
    pr("\n");

#if defined(VTSS_FEATURE_VCAP)
    vtss_vcap_debug_print_range_checkers(vtss_state, pr, info);
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_ARCH_JAGUAR_2)
    {
        u32            i, j;
        vtss_ip_addr_t *sip;

        vtss_debug_print_header(pr, "SIP Table");
        pr("IDX  Address\n");
        for (i = 0; i < VTSS_ACL_SIP_CNT; i++) {
            sip = &vtss_state->vcap.acl_sip_table[i].sip;
            if (sip->type == VTSS_IP_TYPE_IPV4) {
                pr("0x%08x", sip->addr.ipv4);
            } else {
                for (j = 0; j < 16; j++) {
                    pr("%02x%s", sip->addr.ipv6.addr[j], (j & 1) && j != 15 ? ":" : "");
                }
            }
            pr("\n");
        }
        pr("\n");
    }
#endif /* VTSS_ARCH_JAGUAR_2 */

#if defined(VTSS_ARCH_LUTON26)
    vtss_vcap_debug_print_is1(vtss_state, pr, info);
#endif /* VTSS_ARCH_LUTON26 */

#if defined(VTSS_FEATURE_IS2)
    vtss_vcap_debug_print_is2(vtss_state, pr, info);
#endif /* VTSS_FEATURE_IS2 */

#if defined(VTSS_FEATURE_LPM)
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.lpm.obj, sizeof(vtss_lpm_data_t), sizeof(vtss_lpm_info_t));
#endif /* VTSS_FEATURE_LPM */

#if defined(VTSS_FEATURE_IS2_B)
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.is2_b.obj,
                          sizeof(vtss_is2_data_t), sizeof(vtss_is2_info_t));
#endif /* VTSS_FEATURE_IS2_B */

#if defined(VTSS_FEATURE_ES2)
    vtss_vcap_debug_print(pr, info, &vtss_state->vcap.es2.obj,
                          sizeof(vtss_is2_data_t), sizeof(vtss_is2_info_t));
#endif /* VTSS_FEATURE_ES2 */
}

#endif /* VTSS_FEATURE_VCAP */
