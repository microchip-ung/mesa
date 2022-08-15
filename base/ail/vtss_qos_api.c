// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#define VTSS_TRACE_GROUP VTSS_TRACE_GROUP_QOS
#include "vtss_api.h"
#include "vtss_state.h"
#include "vtss_common.h"
#include "vtss_util.h"

#if defined(VTSS_FEATURE_QOS)

#define QOS_DEFAULT_BURST_LEVEL (4096 * 5) /* Default burst level in bytes */
#define QOS_DEFAULT_BIT_RATE    500        /* Default bit rate in kbps */

/* - QoS configuration --------------------------------------------- */

#if defined(VTSS_ARCH_CARACAL)
vtss_rc vtss_mep_policer_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  const vtss_prio_t       prio,
                                  vtss_dlb_policer_conf_t *const conf)
{
    VTSS_D("port: %u, prio: %u", port_no, prio);
    VTSS_MEMSET(conf, 0, sizeof(*conf));
    return VTSS_RC_OK;
}

vtss_rc vtss_mep_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_prio_t             prio,
                                  const vtss_dlb_policer_conf_t *const conf)
{
    VTSS_D("port: %u, prio: %u", port_no, prio);
    return VTSS_RC_OK;
}
#endif /* defined(VTSS_ARCH_CARACAL) */

vtss_rc vtss_qos_conf_get(const vtss_inst_t  inst,
                          vtss_qos_conf_t    *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        *conf = vtss_state->qos.conf;
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_conf_set(const vtss_inst_t      inst,
                          const vtss_qos_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;
    vtss_prio_t  prios = conf->prios;
    BOOL         changed;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        /* Verify that prios is a power of two and not greater than prio_count (which must also be a power of two) */
        if ((prios != 0) &&  !(prios & (prios - 1)) && (prios <= vtss_state->qos.prio_count)) {
            changed = (vtss_state->qos.conf.prios != prios);
            vtss_state->qos.conf = *conf;
            rc = VTSS_FUNC_COLD(qos.conf_set, changed);
        } else {
            VTSS_E("illegal prios: %u", prios);
            rc = VTSS_RC_ERROR;
        }
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_port_conf_get(const vtss_inst_t     inst,
                               const vtss_port_no_t  port_no,
                               vtss_qos_port_conf_t  *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        *conf = vtss_state->qos.port_conf[port_no];
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_port_conf_set(const vtss_inst_t           inst,
                               const vtss_port_no_t        port_no,
                               const vtss_qos_port_conf_t  *const conf)
{
    vtss_state_t         *vtss_state;
    vtss_rc              rc;
    vtss_qos_port_conf_t *port_conf;

    VTSS_D("Enter - port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        port_conf = &vtss_state->qos.port_conf[port_no];
        vtss_state->qos.port_conf_old = *port_conf;
        *port_conf = *conf;
        if ((rc = VTSS_FUNC_COLD(qos.port_conf_set, port_no)) != VTSS_RC_OK) {
            *port_conf = vtss_state->qos.port_conf_old;
        }
    }
    VTSS_EXIT();
    VTSS_D("Exit");
    return rc;
}


vtss_rc vtss_qos_status_get(const vtss_inst_t      inst,
                            vtss_qos_status_t      *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.status_get, status);
    }
    VTSS_EXIT();
    return rc;
}

#if defined(VTSS_ARCH_OCELOT)
vtss_rc vtss_qos_shaper_calibrate(const vtss_inst_t inst)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC_0(qos.shaper_calibrate);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* defined(VTSS_ARCH_OCELOT) */

/* - QCL configuration --------------------------------------------- */

#if defined(VTSS_FEATURE_QCL)
vtss_rc vtss_qce_init(const vtss_inst_t      inst,
                      const vtss_qce_type_t  type,
                      vtss_qce_t             *const qce)
{
    VTSS_D("type: %d", type);

    VTSS_MEMSET(qce, 0, sizeof(*qce));
    qce->key.type = type;

    return VTSS_RC_OK;
}

vtss_rc vtss_qce_add(const vtss_inst_t    inst,
                     const vtss_qcl_id_t  qcl_id,
                     const vtss_qce_id_t  qce_id,
                     const vtss_qce_t     *const qce)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("qce_id: %u before %u %s",
           qce->id, qce_id, qce_id == VTSS_QCE_ID_LAST ? "(last)" : "");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.qce_add, qcl_id, qce_id, qce);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qce_del(const vtss_inst_t    inst,
                     const vtss_qcl_id_t  qcl_id,
                     const vtss_qce_id_t  qce_id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("qce_id: %u", qce_id);

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.qce_del, qcl_id, qce_id);
    }
    VTSS_EXIT();
    return rc;
}
#endif // VTSS_FEATURE_QCL

/* - Common Ingress/Egress map functionality ----------------------- */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP)
static void vtss_cmn_qos_map_adm_init(vtss_qos_map_adm_t *m)
{

    int i, res;

    /* Initialize id table */
    for (i = 0; i < m->id.entry_len; i++) {
        m->id.entry[i].ix  = VTSS_QOS_MAP_ID_NONE; /* Mark id as unused */
        m->id.entry[i].res = 0;                    /* Resource A */
    }

    /* Initialize ix table(s) */
    for (res = 0; res < VTSS_QOS_MAP_RESOURCES; res++) {
        if (m->ix[res].entry == NULL) {
            continue; /* Resource not present */
        }
        for (i = 0; i < m->ix[res].entry_len; i++) {
            m->ix[res].entry[i].id  = VTSS_QOS_MAP_ID_NONE;  /* Mark ix as unused */
            m->ix[res].entry[i].key = VTSS_QOS_MAP_KEY_NONE; /* No key assigned */
        }
        m->ix[res].free = 0;
    }
}

static int vtss_qos_map_compact(vtss_state_t       *vtss_state,
                                vtss_qos_map_adm_t *m,
                                const u16           res,
                                const u16           first_used,
                                const u16           first_free)
{
    u16 id, final_src, tmp_dst, src, dst = first_free;
    int i, len, free_cnt = 0;

    VTSS_D("%s Map: res %u, first_free %u, first_used %u", m->name, res, first_free, first_used);

    if (first_used == VTSS_QOS_MAP_ID_NONE) { /* No indexes after first_free are in use. Nothing needs to be moved. */
        if (m->ix[res].free >= first_free) {
            free_cnt = m->ix[res].free - first_free;  /* Prepare a later reinitialization of table. */
            VTSS_D("%s Map: Prepare freeing %u entries", m->name, free_cnt);
        } else {
            VTSS_E("%s Map: first_free (%u) is greater than m->ix[res].free (%u)!", m->name, first_free, m->ix[res].free);
        }
    } else {
        for (src = first_used; src < m->ix[res].free; src += len) {
            if (dst >= src) {
                VTSS_E("%s Map: Invalid move operation from %u to %u!", m->name, dst, src);
                return 0; /* Bail out */
            }

            id  = m->ix[res].entry[src].id;
            len = m->key2len(m->ix[res].entry[src].key);

            if (id != VTSS_QOS_MAP_ID_NONE) { /* Index is in use */

                if ((src - len) < dst) { /* Overlapping regions. Copy temporary to area reserved for this purpose */
                    tmp_dst = m->ix[res].reserved; /* Temporary destination */

                    VTSS_D("%s Map: MOVE TO RES: id %u, src %u, dst %u, len %u", m->name, id, src, tmp_dst, len);
                    if (m->hw_copy(vtss_state, res, src, tmp_dst, len) != VTSS_RC_OK) {
                        VTSS_E("%s Map: Unable to copy from %u to %u!", m->name, src, tmp_dst);
                        return 0; /* Bail out */
                    }

                    /* Update tables before updating vcap */
                    m->id.entry[id].ix = tmp_dst;
                    for (i = 0; i < len; i++) {
                        m->ix[res].entry[tmp_dst + i] = m->ix[res].entry[src + i];
                    }

                    /* Update references in vcap rules */
                    if (m->vcap_update(vtss_state, id) != VTSS_RC_OK) {
                        VTSS_E("%s Map: Unable to update vcap for id %u!", m->name, id);
                        return 0; /* Bail out */
                    }

                    final_src = tmp_dst; /* Final source is from temporary destination */
                } else { /* Regions do not overlap. Copy directly from source to destination */
                    tmp_dst   = VTSS_QOS_MAP_ID_NONE; /* Temporary destination is not used */
                    final_src = src; /* Final source is from original source */
                }

                VTSS_D("%s Map: MOVE: id %u, src %u, dst %u, len %u", m->name, id, final_src, dst, len);
                if (m->hw_copy(vtss_state, res, final_src, dst, len) != VTSS_RC_OK) {
                    VTSS_E("%s Map: Unable to copy from %u to %u!", m->name, final_src, dst);
                    return 0; /* Bail out */
                }

                /* Update tables before updating vcap */
                m->id.entry[id].ix = dst;
                for (i = 0; i < len; i++) {
                    m->ix[res].entry[dst + i] = m->ix[res].entry[final_src + i];
                }

                /* Update references in vcap rules */
                if (m->vcap_update(vtss_state, id) != VTSS_RC_OK) {
                    VTSS_E("%s Map: Unable to update vcap for id %u!", m->name, id);
                    return 0; /* Bail out */
                }

                if (tmp_dst != VTSS_QOS_MAP_ID_NONE) {
                    /* Clear reserved area in hardware. Not really needed but eases debugging */
                    (void)m->hw_update(vtss_state, res, tmp_dst, len, NULL);

                    /* Clear the used part of the temporary area */
                    for (i = 0; i < len; i++) {
                        m->ix[res].entry[tmp_dst + i].id  = VTSS_QOS_MAP_ID_NONE;
                        m->ix[res].entry[tmp_dst + i].key = VTSS_QOS_MAP_KEY_NONE;
                    }
                }

                free_cnt = src - dst; /* Number of freed indexes is always the same as the last move */
                dst += len;
            } else {
                VTSS_D("%s Map: IGNORE: id %u, src %u, dst %u, len %u", m->name, id, src, dst, len);
            }
        }
    }

    if ((m->ix[res].free - free_cnt) >= 0) {
        m->ix[res].free -= free_cnt;
        /* Clear the freed part of the table */
        for (i = 0; i < free_cnt; i++) {
            m->ix[res].entry[m->ix[res].free + i].id  = VTSS_QOS_MAP_ID_NONE;
            m->ix[res].entry[m->ix[res].free + i].key = VTSS_QOS_MAP_KEY_NONE;
        }
    } else {
        VTSS_E("%s Map: Corrupted table: m->ix.free %u, free_cnt %d!", m->name, m->ix[res].free, free_cnt);
        return 0; /* Bail out */
    }

    return free_cnt;
}

static u16 vtss_qos_map_new_ix(vtss_state_t       *vtss_state,
                               vtss_qos_map_adm_t *m,
                               const u16           res,
                               int                 key)
{
    u16 ix, id;
    u16 first_free_ix = VTSS_QOS_MAP_ID_NONE;
    u16 first_used_ix = VTSS_QOS_MAP_ID_NONE;
    int free_cnt = 0;
    int len, new_len = m->key2len(key);

    /* Algorithm:
     *  1) Use first unused entry with correct length, located before the free index, or
     *  2) Use free space at bottom, or
     *  3) Compact list and use free space at bottom, or
     *  4) No more room for mapping!
     */

    /* 1) */
    for (ix = 0; ix < m->ix[res].free; ix += len) {
        id  = m->ix[res].entry[ix].id;
        len = m->key2len(m->ix[res].entry[ix].key);

        VTSS_D("%s Map: id %u, ix %u, len %u, new_len %u, free %u", m->name, id, ix, len, new_len, m->ix[res].free);

        if (len == 0) {
            VTSS_E("%s Map: Corrupted table: len is 0!", m->name);
            return VTSS_QOS_MAP_ID_NONE; /* No more room */
        }

        if (id == VTSS_QOS_MAP_ID_NONE) { /* Index is free */
            if (len == new_len) {
                VTSS_D("%s Map: Returning unused ix %u, new_len %u", m->name, ix, new_len);
                return ix;
            }
            free_cnt += len; /* Count the number of free indexes */
            if (first_free_ix == VTSS_QOS_MAP_ID_NONE) {
                first_free_ix = ix; /* Remember the first free index we have found. */
            }
        } else { /* Index is used */
            if ((first_free_ix != VTSS_QOS_MAP_ID_NONE) &&
                (first_used_ix == VTSS_QOS_MAP_ID_NONE)) {
                first_used_ix = ix; /* Remember the first used index after the first free we have found. */
            }
        }
    }

    /* 2) */
    if ((m->ix[res].free + new_len) <= m->ix[res].reserved) { /* We have found enough space at the bottom */
        ix = m->ix[res].free;
        m->ix[res].free += new_len;
        VTSS_D("%s Map: Returning free ix %u, new_len %u", m->name, ix, new_len);
        return ix;
    }

    /* 3) */
    VTSS_D("%s Map: Compacting should get us %u free indexes", m->name, free_cnt);
    if ((m->ix[res].free + new_len - free_cnt) <= m->ix[res].reserved) { /* Compacting will give us enough space at the bottom */
        int actual_cnt = vtss_qos_map_compact(vtss_state, m, res, first_used_ix, first_free_ix);
        if (actual_cnt == free_cnt) { /* Compact gave us what we expected */
            ix = m->ix[res].free;
            m->ix[res].free += new_len;
            VTSS_D("%s Map: Returning free ix %u after compacting, new_len %u", m->name, ix, new_len);
            return ix;
        } else {
            VTSS_E("%s Map: Compact gave us %d but we expected %d!", m->name, actual_cnt, free_cnt);
        }
    }

    /* 4) */
    return VTSS_QOS_MAP_ID_NONE; /* No more room */
}

vtss_rc vtss_cmn_qos_map_add(struct vtss_state_s *vtss_state,
                             vtss_qos_map_adm_t  *m,
                             const u16            id,
                             const int            key,
                             const u8             flags,
                             const void          *const map)
{
#if VTSS_OPT_TRACE
    u16     old_free;
#endif
    u16     old_res, res, old_ix, new_ix;
    int     old_key   = 0;
    int     old_len   = 0;
    u8      old_flags = 0;
    int     len = m->key2len(key);
    vtss_rc rc;

    VTSS_D("%s Map: id %u, key %u, len %u", m->name, id, key, len);

    old_ix  = m->id.entry[id].ix;
    old_res = m->id.entry[id].res;

    if (old_ix != VTSS_QOS_MAP_ID_NONE) { /* Id is in use */

        if (id != m->ix[old_res].entry[old_ix].id) {
            VTSS_E("%s Map: Inconsistent tables id: %u, old_ix: %u, m->ix[%u].entry[old_ix].id: %u!", m->name, id, old_ix, old_res, m->ix[old_res].entry[old_ix].id);
            return VTSS_RC_ERROR;
        }

        old_key   = m->ix[old_res].entry[old_ix].key;
        old_len   = m->key2len(old_key);
        old_flags = m->ix[old_res].entry[old_ix].flags;
        if (old_key == key) {
            /* If old and new keys are the same, the entry is reused, hw tables are updated and we are done.
             * Note that when we reuse an entry, we do not need to update the vcap tables unless flags have changed.
             */
            VTSS_D("%s Map: Reused entry! id %u, ix %u", m->name, id, old_ix);
            rc = m->hw_update(vtss_state, old_res, old_ix, old_len, map);

            if ((rc == VTSS_RC_OK) && (old_flags != flags)) {
                m->ix[old_res].entry[old_ix].flags = flags;
                /* Update references in vcap rules */
                rc = m->vcap_update(vtss_state, id);
            }
            return rc;
        }
    }

    /* If we get here, we will need to create a new entry and possible remove the old one. */
    for (res = 0; res < VTSS_QOS_MAP_RESOURCES; res++) {
        if (m->ix[res].entry == NULL) {
            continue; /* Resource not present */
        }
#if VTSS_OPT_TRACE
        old_free = m->ix[res].free;
#endif
        if ((new_ix = vtss_qos_map_new_ix(vtss_state, m, res, key)) != VTSS_QOS_MAP_ID_NONE) {
            /* If vtss_qos_map_compact() has been called by vtss_qos_map_new_ix() then old_ix could move. Read it again */
            old_ix = m->id.entry[id].ix;

            m->id.entry[id].ix             = new_ix;
            m->id.entry[id].res            = res;
            m->ix[res].entry[new_ix].id    = id;
            m->ix[res].entry[new_ix].key   = key;
            m->ix[res].entry[new_ix].flags = flags;

            /* Add in hw tables. */
            rc = m->hw_update(vtss_state, res, new_ix, len, map);

            if (rc == VTSS_RC_OK) {
                /* Update references in vcap rules */
                rc = m->vcap_update(vtss_state, id);
            }

            if (rc == VTSS_RC_OK) {
                if (old_ix != VTSS_QOS_MAP_ID_NONE) {
                    /* Try to delete old ix in hw tables. Actually not needed as the hw tables are not used if they are not referenced by any rule. */
                    (void)m->hw_update(vtss_state, old_res, old_ix, old_len, NULL);

                    /* Mark the entry as unused. NEVER init the key unless it is the last entry. It is needed in order to traverse the table. */
                    m->ix[old_res].entry[old_ix].id    = VTSS_QOS_MAP_ID_NONE;
                    m->ix[old_res].entry[old_ix].flags = 0;

                    /* Update 'free' and end of table if entry was the last one */
                    if (m->ix[old_res].free == (old_ix + old_len)) {
                        int i;
                        VTSS_D("%s Map: Update free in res %u from %u to %u", m->name, old_res, m->ix[old_res].free, old_ix);
                        m->ix[old_res].free = old_ix;
                        for (i = 0; i < old_len; i++) {
                            m->ix[old_res].entry[old_ix + i].id    = VTSS_QOS_MAP_ID_NONE;
                            m->ix[old_res].entry[old_ix + i].key   = VTSS_QOS_MAP_KEY_NONE;
                            m->ix[old_res].entry[old_ix + i].flags = 0;
                        }
                    }

                }
            }
            VTSS_D("%s Map: New entry! id %u, res %u, oix %u, nix %u, of %u, nf %u", m->name, id, res, old_ix, new_ix, old_free, m->ix[res].free);
            return rc;
        }
    }

    VTSS_I("%s Map: No more resources!", m->name);
    return VTSS_RC_ERROR;
}

vtss_rc vtss_cmn_qos_map_del(struct vtss_state_s *vtss_state,
                             vtss_qos_map_adm_t  *m,
                             const u16            id)
{
    u16 ix, res;
    int len;

    VTSS_D("id: %u", id);

    ix = m->id.entry[id].ix;

    if (ix == VTSS_QOS_MAP_ID_NONE) {
        VTSS_N("%s Map: Id not in use: %u!", m->name, id);
        return VTSS_RC_ERROR;
    }

    res = m->id.entry[id].res;

    if (ix >= m->ix[res].reserved) {
        VTSS_E("%s Map: Invalid map ix: %u!", m->name, ix);
        return VTSS_RC_ERROR;
    }

    if (id != m->ix[res].entry[ix].id) {
        VTSS_E("%s Map: Inconsistent tables id %u, ix %u, m->ix[%u].entry[ix].id %u!", m->name, id, ix, res, m->ix[res].entry[ix].id);
        return VTSS_RC_ERROR;
    }

    /* Save length for later use */
    len = m->key2len(m->ix[res].entry[ix].key);

    /* Mark the entry as unused. */
    m->id.entry[id].ix = VTSS_QOS_MAP_ID_NONE;
    m->id.entry[id].res = 0;

    /* Mark the entry as unused. NEVER init the key unless it is the last entry. It is needed in order to traverse the table. */
    m->ix[res].entry[ix].id    = VTSS_QOS_MAP_ID_NONE;
    m->ix[res].entry[ix].flags = 0;

    /* Update 'free' and end of table if entry was the last one */
    if (m->ix[res].free == (ix + len)) {
        int i;
        VTSS_D("%s Map: Update free in res %u from %u to %u", m->name, res, m->ix[res].free, ix);
        m->ix[res].free = ix;
        for (i = 0; i < len; i++) {
            m->ix[res].entry[ix + i].id    = VTSS_QOS_MAP_ID_NONE;
            m->ix[res].entry[ix + i].key   = VTSS_QOS_MAP_KEY_NONE;
            m->ix[res].entry[ix + i].flags = 0;
        }
    }

    VTSS_D("%s Map: Deleted entry! id %u, res %u, ix %u, free %u", m->name, id, res, ix, m->ix[res].free);

    /* Remove references in vcap rules */
    VTSS_RC(m->vcap_update(vtss_state, id));

    /* Delete in hw tables. Actually not needed as the hw tables are not used if they are not referenced by any rule. */
    VTSS_RC(m->hw_update(vtss_state, res, ix, len, NULL));

    return VTSS_RC_OK;
}
#endif /* defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP) */

/* - Ingress map configuration ------------------------------------- */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
static int vtss_qos_ingress_map_key2len(int key)
{
    switch ((vtss_qos_ingress_map_key_t)key) {
    case VTSS_QOS_INGRESS_MAP_KEY_PCP:
        return 1;
    case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
        return 2;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
        return 8;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
        return 10;
    case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
        return 1;
    default:
        return 0;
    }
}

static vtss_rc vtss_qos_ingress_map_values_check(const vtss_qos_ingress_map_values_t *const values)
{
    if (values->cos >= VTSS_PRIO_END) {
        VTSS_E("Invalid cos: %u!", values->cos);
        return VTSS_RC_ERROR;
    }
    if (values->dpl >= VTSS_DPL_END) {
        VTSS_E("Invalid dpl: %u!", values->dpl);
        return VTSS_RC_ERROR;
    }
    if (values->pcp >= VTSS_PCP_END) {
        VTSS_E("Invalid pcp: %u!", values->pcp);
        return VTSS_RC_ERROR;
    }
    if (values->dei >= VTSS_DEI_END) {
        VTSS_E("Invalid dei: %u!", values->dei);
        return VTSS_RC_ERROR;
    }
    if (values->dscp > 63) {
        VTSS_E("Invalid dscp: %u!", values->dscp);
        return VTSS_RC_ERROR;
    }
    if (values->cosid > 7) {
        VTSS_E("Invalid cosid: %u!", values->cosid);
        return VTSS_RC_ERROR;
    }
    if (values->path_cosid > 7) {
        VTSS_E("Invalid path_cosid: %u!", values->path_cosid);
        return VTSS_RC_ERROR;
    }
    if (values->mpls_tc > 7) {
        VTSS_E("Invalid tc: %u!", values->mpls_tc);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_qos_ingress_map_check(const vtss_qos_ingress_map_t *const map)
{
    int i, j;

    if (map == FALSE) {
        VTSS_E("NULL map!");
        return VTSS_RC_ERROR;
    }
    if ((map->id < VTSS_QOS_INGRESS_MAP_ID_START) || (map->id >= VTSS_QOS_INGRESS_MAP_ID_END)) {
        VTSS_E("Invalid ingress map id: %u!", map->id);
        return VTSS_RC_ERROR;
    }

    switch (map->key) {
    case VTSS_QOS_INGRESS_MAP_KEY_PCP:
        for (i = 0; i < 8; i++) {
            VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.pcp[i]));
        }
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI:
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.pcp_dei[i][j]));
            }
        }
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP:
        for (i = 0; i < 64; i++) {
            VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.dscp[i]));
        }
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI:
        for (i = 0; i < 64; i++) {
            VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.dpd.dscp[i]));
        }
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.dpd.pcp_dei[i][j]));
            }
        }
        break;
    case VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC:
        for (i = 0; i < 8; i++) {
            VTSS_RC(vtss_qos_ingress_map_values_check(&map->maps.mpls_tc[i]));
        }
        break;
    default:
        VTSS_E("Invalid ingress map key: %u!", map->key);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_qos_ingress_map_init(const vtss_inst_t                inst,
                                  const vtss_qos_ingress_map_key_t key,
                                  vtss_qos_ingress_map_t           *const map)
{
    VTSS_D("key: %d", key);

    if ((key != VTSS_QOS_INGRESS_MAP_KEY_PCP)          &&
        (key != VTSS_QOS_INGRESS_MAP_KEY_PCP_DEI)      &&
        (key != VTSS_QOS_INGRESS_MAP_KEY_DSCP)         &&
        (key != VTSS_QOS_INGRESS_MAP_KEY_DSCP_PCP_DEI) &&
        (key != VTSS_QOS_INGRESS_MAP_KEY_MPLS_TC)) {
        VTSS_E("Invalid key: %u!", key);
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(map, 0, sizeof(*map));
    map->id  = VTSS_QOS_INGRESS_MAP_ID_NONE;
    map->key = key;

    return VTSS_RC_OK;
}

vtss_rc vtss_qos_ingress_map_add(const vtss_inst_t            inst,
                                 const vtss_qos_ingress_map_t *const map)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("map_id: %u", map->id);
    VTSS_RC(vtss_qos_ingress_map_check(map));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.ingress_map_add, map);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_ingress_map_del(const vtss_inst_t               inst,
                                 const vtss_qos_ingress_map_id_t id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("map_id: %u", id);

    if ((id < VTSS_QOS_INGRESS_MAP_ID_START) || (id >= VTSS_QOS_INGRESS_MAP_ID_END)) {
        VTSS_E("Invalid ingress map id: %u!", id);
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.ingress_map_del, id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_ingress_map_del_all(const vtss_inst_t inst)
{
    vtss_state_t              *vtss_state;
    vtss_qos_ingress_map_id_t id;
    vtss_rc                   rc;

    VTSS_D("enter");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (id = VTSS_QOS_INGRESS_MAP_ID_START; id < VTSS_QOS_INGRESS_MAP_ID_END; id++) {
            (void)VTSS_FUNC(qos.ingress_map_del, id);
        }
        vtss_cmn_qos_map_adm_init(&vtss_state->qos.imap);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

/* - Egress map configuration ------------------------------------- */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
static int vtss_qos_egress_map_key2len(int key)
{
    switch ((vtss_qos_egress_map_key_t)key) {
    case VTSS_QOS_EGRESS_MAP_KEY_COSID:
        return 1;
    case VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL:
        return 4;
    case VTSS_QOS_EGRESS_MAP_KEY_DSCP:
        return 8;
    case VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL:
        return 32;
    case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC:
        return 1;
    case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL:
        return 4;
    default:
        return 0;
    }
}

static vtss_rc vtss_qos_egress_map_values_check(const vtss_qos_egress_map_values_t *const values)
{
    if (values->pcp >= VTSS_PCP_END) {
        VTSS_E("Invalid pcp: %u!", values->pcp);
        return VTSS_RC_ERROR;
    }
    if (values->dei >= VTSS_DEI_END) {
        VTSS_E("Invalid dei: %u!", values->dei);
        return VTSS_RC_ERROR;
    }
    if (values->dscp > 63) {
        VTSS_E("Invalid dscp: %u!", values->dscp);
        return VTSS_RC_ERROR;
    }
    if (values->path_cosid > 7) {
        VTSS_E("Invalid path_cosid: %u!", values->path_cosid);
        return VTSS_RC_ERROR;
    }
    if (values->mpls_tc > 7) {
        VTSS_E("Invalid tc: %u!", values->mpls_tc);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

static vtss_rc vtss_qos_egress_map_check(const vtss_qos_egress_map_t *const map)
{
    int i, j;

    if (map == FALSE) {
        VTSS_E("NULL map!");
        return VTSS_RC_ERROR;
    }
    if ((map->id < VTSS_QOS_EGRESS_MAP_ID_START) || (map->id >= VTSS_QOS_EGRESS_MAP_ID_END)) {
        VTSS_E("Invalid egress map id: %u!", map->id);
        return VTSS_RC_ERROR;
    }

    switch (map->key) {
    case VTSS_QOS_EGRESS_MAP_KEY_COSID:
        for (i = 0; i < 8; i++) {
            VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.cosid[i]));
        }
        break;
    case VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL:
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 4; j++) {
                VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.cosid_dpl[i][j]));
            }
        }
        break;
    case VTSS_QOS_EGRESS_MAP_KEY_DSCP:
        for (i = 0; i < 64; i++) {
            VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.dscp[i]));
        }
        break;
    case VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL:
        for (i = 0; i < 64; i++) {
            for (j = 0; j < 4; j++) {
                VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.dscp_dpl[i][j]));
            }
        }
        break;
    case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC:
        for (i = 0; i < 8; i++) {
            VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.mpls_tc[i]));
        }
        break;
    case VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL:
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 4; j++) {
                VTSS_RC(vtss_qos_egress_map_values_check(&map->maps.mpls_tc_dpl[i][j]));
            }
        }
        break;
    default:
        VTSS_E("Invalid egress map key: %u!", map->key);
        return VTSS_RC_ERROR;
    }

    return VTSS_RC_OK;
}

vtss_rc vtss_qos_egress_map_init(const vtss_inst_t               inst,
                                 const vtss_qos_egress_map_key_t key,
                                 vtss_qos_egress_map_t           *const map)
{
    VTSS_D("key: %d", key);

    if ((key != VTSS_QOS_EGRESS_MAP_KEY_COSID)     &&
        (key != VTSS_QOS_EGRESS_MAP_KEY_COSID_DPL) &&
        (key != VTSS_QOS_EGRESS_MAP_KEY_DSCP)      &&
        (key != VTSS_QOS_EGRESS_MAP_KEY_DSCP_DPL)  &&
        (key != VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC)   &&
        (key != VTSS_QOS_EGRESS_MAP_KEY_MPLS_TC_DPL)) {
        VTSS_E("Invalid key: %u!", key);
        return VTSS_RC_ERROR;
    }

    VTSS_MEMSET(map, 0, sizeof(*map));
    map->id  = VTSS_QOS_EGRESS_MAP_ID_NONE;
    map->key = key;

    return VTSS_RC_OK;
}

vtss_rc vtss_qos_egress_map_add(const vtss_inst_t           inst,
                                const vtss_qos_egress_map_t *const map)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("map_id: %u", map->id);
    VTSS_RC(vtss_qos_egress_map_check(map));
    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.egress_map_add, map);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_egress_map_del(const vtss_inst_t              inst,
                                const vtss_qos_egress_map_id_t id)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("map_id: %u", id);

    if ((id < VTSS_QOS_EGRESS_MAP_ID_START) || (id >= VTSS_QOS_EGRESS_MAP_ID_END)) {
        VTSS_E("Invalid egress map id: %u!", id);
        return VTSS_RC_ERROR;
    }

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        rc = VTSS_FUNC(qos.egress_map_del, id);
    }
    VTSS_EXIT();
    return rc;
}

vtss_rc vtss_qos_egress_map_del_all(const vtss_inst_t inst)
{
    vtss_state_t             *vtss_state;
    vtss_qos_egress_map_id_t id;
    vtss_rc                  rc;

    VTSS_D("enter");

    VTSS_ENTER();
    if ((rc = vtss_inst_check(inst, &vtss_state)) == VTSS_RC_OK) {
        for (id = VTSS_QOS_EGRESS_MAP_ID_START; id < VTSS_QOS_EGRESS_MAP_ID_END; id++) {
            (void)VTSS_FUNC(qos.egress_map_del, id);
        }
        vtss_cmn_qos_map_adm_init(&vtss_state->qos.emap);
    }
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

/* - DLB policers -------------------------------------------------- */

#if defined(VTSS_FEATURE_EVC_POLICERS)
vtss_rc vtss_evc_policer_id_check(vtss_state_t *vtss_state,
                                  const vtss_evc_policer_id_t policer_id, BOOL resv)
{
#if defined(VTSS_ARCH_OCELOT)
    /* Allow reserved policers */
    if (resv &&
        (policer_id == VTSS_EVC_POLICER_ID_DISCARD || policer_id == VTSS_EVC_POLICER_ID_NONE)) {
        return VTSS_RC_OK;
    }
#endif /* VTSS_ARCH_OCELOT */

    if (policer_id >= vtss_state->qos.evc_policer_max) {
        VTSS_E("illegal policer_id: %u", policer_id);
        return VTSS_RC_ERROR;
    }
    return VTSS_RC_OK;
}

vtss_rc vtss_evc_policer_conf_get(const vtss_inst_t           inst,
                                  const vtss_evc_policer_id_t policer_id,
                                  vtss_evc_policer_conf_t     *const conf)
{
    vtss_state_t *vtss_state;

    VTSS_D("policer_id: %u", policer_id);
    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_evc_policer_id_check(vtss_state, policer_id, 0));
    VTSS_ENTER();
    *conf = vtss_state->qos.evc_policer_conf[policer_id];
    VTSS_EXIT();
    return VTSS_RC_OK;
}

vtss_rc vtss_evc_policer_conf_set(const vtss_inst_t             inst,
                                  const vtss_evc_policer_id_t   policer_id,
                                  const vtss_evc_policer_conf_t *const conf)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("policer_id: %u", policer_id);
    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_RC(vtss_evc_policer_id_check(vtss_state, policer_id, 0));
    VTSS_ENTER();
    vtss_state->qos.evc_policer_conf[policer_id] = *conf;
    rc = VTSS_FUNC_COLD(qos.evc_policer_conf_set, policer_id);
    VTSS_EXIT();
    return rc;
}
#endif /* VTSS_FEATURE_EVC_POLICERS */

/* - 802.1Qbv (Enhancements for Scheduled Traffic) ----------------- */
#if defined(VTSS_FEATURE_QOS_TAS)
vtss_rc vtss_qos_tas_conf_get(const vtss_inst_t    inst,
                              vtss_qos_tas_conf_t  *const conf)
{
    vtss_state_t *vtss_state;

    VTSS_D("Enter");

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_ENTER();
    *conf = vtss_state->qos.tas.global_conf;
    VTSS_EXIT();

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_qos_tas_conf_set(const vtss_inst_t         inst,
                              const vtss_qos_tas_conf_t *const conf)
{
    vtss_state_t        *vtss_state;
    vtss_rc             rc;
    vtss_qos_tas_conf_t *tas_conf;

    VTSS_D("Enter");

    VTSS_RC(vtss_inst_check(inst, &vtss_state));
    VTSS_ENTER();
    tas_conf = &vtss_state->qos.tas.global_conf;
    *tas_conf = *conf;
    rc = VTSS_FUNC_COLD(qos.tas_conf_set);
    VTSS_EXIT();

    VTSS_D("Exit");
    return rc;
}

vtss_rc vtss_qos_tas_port_conf_get(const vtss_inst_t        inst,
                                   const vtss_port_no_t     port_no,
                                   vtss_qos_tas_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;

    VTSS_D("Enter - port_no: %u", port_no);

    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_ENTER();
    *conf = vtss_state->qos.tas.port_conf[port_no];
    VTSS_EXIT();

    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_qos_tas_port_conf_set(const vtss_inst_t              inst,
                                   const vtss_port_no_t           port_no,
                                   const vtss_qos_tas_port_conf_t *const conf)
{
    vtss_state_t             *vtss_state;
    vtss_rc                  rc;
    vtss_qos_tas_port_conf_t *tas_port_conf;

    VTSS_D("Enter - port_no: %u", port_no);

    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_ENTER();
    tas_port_conf = &vtss_state->qos.tas.port_conf[port_no];
    *tas_port_conf = *conf;
    rc = VTSS_FUNC_COLD(qos.tas_port_conf_set, port_no);
    VTSS_EXIT();

    VTSS_D("Exit");
    return rc;
}

vtss_rc vtss_qos_tas_port_status_get(const vtss_inst_t          inst,
                                     const vtss_port_no_t       port_no,
                                     vtss_qos_tas_port_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter - port_no: %u", port_no);

    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_ENTER();
    rc = VTSS_FUNC(qos.tas_port_status_get, port_no, status);
    VTSS_EXIT();

    VTSS_D("Exit");
    return rc;
}
#endif /* defined(VTSS_FEATURE_QOS_TAS) */

/* - 802.1Qbu and 802.3br (Frame Preemption) ----------------------- */
#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
vtss_rc vtss_qos_fp_port_conf_get(const vtss_inst_t       inst,
                                  const vtss_port_no_t    port_no,
                                  vtss_qos_fp_port_conf_t *const conf)
{
    vtss_state_t *vtss_state;

    VTSS_D("Enter - port_no: %u", port_no);
    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_ENTER();
    *conf = vtss_state->qos.fp.port_conf[port_no];
    VTSS_EXIT();
    VTSS_D("Exit");
    return VTSS_RC_OK;
}

vtss_rc vtss_qos_fp_port_conf_set(const vtss_inst_t             inst,
                                  const vtss_port_no_t          port_no,
                                  const vtss_qos_fp_port_conf_t *const conf)
{
    vtss_state_t            *vtss_state;
    vtss_rc                 rc;
    vtss_qos_fp_port_conf_t *fp_conf, fp_conf_old;

    VTSS_D("Enter - port_no: %u", port_no);
    VTSS_ENTER();
    if ((rc = vtss_inst_port_no_check(inst, &vtss_state, port_no)) == VTSS_RC_OK) {
        fp_conf = &vtss_state->qos.fp.port_conf[port_no];
        fp_conf_old = *fp_conf;
        *fp_conf = *conf;
        if ((rc = VTSS_FUNC_COLD(qos.fp_port_conf_set, port_no)) != VTSS_RC_OK) {
            *fp_conf = fp_conf_old;
        }
    }
    VTSS_EXIT();
    VTSS_D("Exit");
    return rc;
}

vtss_rc vtss_qos_fp_port_status_get(const vtss_inst_t         inst,
                                    const vtss_port_no_t      port_no,
                                    vtss_qos_fp_port_status_t *const status)
{
    vtss_state_t *vtss_state;
    vtss_rc      rc;

    VTSS_D("Enter - port_no: %u", port_no);

    VTSS_RC(vtss_inst_port_no_check(inst, &vtss_state, port_no));
    VTSS_ENTER();
    rc = VTSS_FUNC(qos.fp_port_status_get, port_no, status);
    VTSS_EXIT();

    VTSS_D("Exit");
    return rc;
}
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */

/* - Warm start synchronization ------------------------------------ */

#if defined(VTSS_FEATURE_WARM_START)
vtss_rc vtss_qos_restart_sync(vtss_state_t *vtss_state)
{
    vtss_port_no_t port_no;

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_state->qos.port_conf_old = vtss_state->qos.port_conf[port_no];
        VTSS_FUNC_RC(qos.port_conf_set, port_no);
    }

    VTSS_FUNC_RC(qos.conf_set, 1);

#if defined(VTSS_FEATURE_EVC_POLICERS)
    {
        vtss_evc_policer_id_t policer_id;

        for (policer_id = 0; policer_id < vtss_state->qos.evc_policer_max; policer_id++) {
            VTSS_FUNC_RC(qos.evc_policer_conf_set, policer_id);
        }
    }
#endif /* VTSS_FEATURE_EVC_POLICERS */

    return VTSS_RC_OK;
}
#endif /* VTSS_FEATURE_WARM_START */

/* - Instance create and initialization ---------------------------- */

vtss_rc vtss_qos_inst_create(struct vtss_state_s *vtss_state)
{
    vtss_port_no_t     port_no;
    u32                i;

    if ((vtss_state->arch == VTSS_ARCH_CU_PHY) || (vtss_state->arch == VTSS_ARCH_10G_PHY)) {
        return VTSS_RC_OK; /* No need to initialize QoS state on a PHY */
    }

    /* Global configuration initialization begin */
    {
        vtss_qos_conf_t *qos = &vtss_state->qos.conf;

        qos->prios = vtss_state->qos.prio_count;

        for (i = 0; i < 64; i++) {
            qos->dscp_remark[i] = FALSE;
            qos->dscp_translate_map[i] = i;
            qos->dscp_remap[i] = i;
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
            qos->dscp_remap_dp1[i] = i;
#endif /* VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE */
        }

        qos->policer_uc            = VTSS_PACKET_RATE_DISABLED;
        qos->policer_uc_frame_rate = TRUE;
        qos->policer_uc_mode       = VTSS_STORM_POLICER_MODE_PORTS_AND_CPU;
        qos->policer_mc            = VTSS_PACKET_RATE_DISABLED;
        qos->policer_mc_frame_rate = TRUE;
        qos->policer_mc_mode       = VTSS_STORM_POLICER_MODE_PORTS_AND_CPU;
        qos->policer_bc            = VTSS_PACKET_RATE_DISABLED;
        qos->policer_bc_frame_rate = TRUE;
        qos->policer_bc_mode       = VTSS_STORM_POLICER_MODE_PORTS_AND_CPU;

#if defined(VTSS_FEATURE_QOS_WRED_V2)
        {
            int queue, dpl;

            for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
                for (dpl = 0; dpl < 2; dpl++) {
                    qos->red_v2[queue][dpl].enable   = FALSE;
                    qos->red_v2[queue][dpl].min_fl   = 0;
                    qos->red_v2[queue][dpl].max      = 50;
                    qos->red_v2[queue][dpl].max_unit = VTSS_WRED_V2_MAX_DP; /* Defaults to 50% drop probability at 100% fill level */
                }
            }
        }
#endif /* VTSS_FEATURE_QOS_WRED_V2 */

#if defined(VTSS_FEATURE_QOS_WRED_V3)
        {
            int group, queue, dpl;

            for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
                for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
                    for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                        qos->red_v3[queue][dpl][group].enable   = FALSE;
                        qos->red_v3[queue][dpl][group].min_fl   = 0;
                        qos->red_v3[queue][dpl][group].max      = 50;
                        qos->red_v3[queue][dpl][group].max_unit = VTSS_WRED_V2_MAX_DP; /* Defaults to 50% drop probability at 100% fill level */
                    }
                }
            }
        }
#endif /* VTSS_FEATURE_QOS_WRED_V3 */
    }
    /* Global configuration initialization end */

    /* Port configuration initialization begin */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        vtss_qos_port_conf_t *qos   = &vtss_state->qos.port_conf[port_no];
        vtss_burst_level_t    level = QOS_DEFAULT_BURST_LEVEL; /* Default burst level configuration */

        for (i = 0; i < VTSS_PORT_POLICERS; i++) {
            qos->policer_port[i].level                    = level;
            qos->policer_port[i].rate                     = VTSS_BITRATE_DISABLED;

            qos->policer_ext_port[i].frame_rate           = FALSE;
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL)
            qos->policer_ext_port[i].dp_bypass_level      = 0;
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_DPBL */
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM)
            qos->policer_ext_port[i].unicast              = TRUE;
            qos->policer_ext_port[i].multicast            = TRUE;
            qos->policer_ext_port[i].broadcast            = TRUE;
            qos->policer_ext_port[i].uc_no_flood          = FALSE;
            qos->policer_ext_port[i].mc_no_flood          = FALSE;
            qos->policer_ext_port[i].flooded              = TRUE;
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM */
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
            qos->policer_ext_port[i].known_unicast        = TRUE;
            qos->policer_ext_port[i].known_multicast      = TRUE;
            qos->policer_ext_port[i].known_broadcast      = TRUE;
            qos->policer_ext_port[i].unknown_unicast      = TRUE;
            qos->policer_ext_port[i].unknown_multicast    = TRUE;
            qos->policer_ext_port[i].unknown_broadcast    = TRUE;
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2 */
#if defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM) || defined(VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2)
            qos->policer_ext_port[i].learning             = TRUE;
            qos->policer_ext_port[i].to_cpu               = TRUE;
            {
                int q;
                for (q = 0; q < VTSS_PORT_POLICER_CPU_QUEUES; q++) {
                    qos->policer_ext_port[i].cpu_queue[q]     = TRUE;
                }
            }
            qos->policer_ext_port[i].limit_noncpu_traffic = TRUE;
            qos->policer_ext_port[i].limit_cpu_traffic    = FALSE;
#endif /* VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM || VTSS_FEATURE_QOS_PORT_POLICER_EXT_TTM_V2 */
            qos->policer_ext_port[i].flow_control         = FALSE;
        }

        for (i = VTSS_QUEUE_START; i < VTSS_QUEUE_END; i++) {
            qos->policer_queue[i].level = level;
            qos->policer_queue[i].rate  = VTSS_BITRATE_DISABLED;
        }

        qos->shaper_port.rate  = VTSS_BITRATE_DISABLED;
        qos->shaper_port.level = level;
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
        qos->shaper_port.eir   = VTSS_BITRATE_DISABLED;
        qos->shaper_port.ebs   = level;
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */

        for (i = VTSS_QUEUE_START; i < VTSS_QUEUE_END; i++) {
            qos->shaper_queue[i].rate  = VTSS_BITRATE_DISABLED;
            qos->shaper_queue[i].level = level;
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
            qos->shaper_queue[i].eir   = VTSS_BITRATE_DISABLED;
            qos->shaper_queue[i].ebs   = level;
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
            qos->excess_enable[i] = FALSE;
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
            qos->cut_through_enable[i] = FALSE;
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH */
        }

        qos->default_dpl = 0;
        qos->default_dei = 0;
        qos->tag_class_enable = FALSE;
        for (i = VTSS_PCP_START; i < VTSS_PCP_ARRAY_SIZE; i++) {
            int dei;
            for (dei = VTSS_DEI_START; dei < VTSS_DEI_ARRAY_SIZE; dei++) {
                qos->qos_class_map[i][dei] = vtss_cmn_pcp2qos(i);
                qos->dp_level_map[i][dei] = dei; // Defaults to same value as DEI
            }
        }

        qos->dwrr_enable = FALSE;
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
        qos->dwrr_cnt = 6;
#endif /* VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT */
        for (i = VTSS_QUEUE_START; i < VTSS_QUEUE_END; i++) {
            qos->queue_pct[i] = 17; // Queues have equal weights initially
        }

        qos->tag_remark_mode = VTSS_TAG_REMARK_MODE_CLASSIFIED;
        qos->tag_default_pcp = 0;
        qos->tag_default_dei = 0;
        for (i = VTSS_PRIO_START; i < VTSS_PRIO_END; i++) {
            int dpl;
            for (dpl = 0; dpl < 2; dpl++) {
                qos->tag_pcp_map[i][dpl] = vtss_cmn_pcp2qos(i);
                qos->tag_dei_map[i][dpl] = dpl; // Defaults to same value as DP level
            }
        }

#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
        qos->ingress_map = VTSS_QOS_INGRESS_MAP_ID_NONE;
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
        qos->egress_map = VTSS_QOS_EGRESS_MAP_ID_NONE;
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */
    }
    /* Port configuration initialization end */

#if defined(VTSS_FEATURE_QOS_TAS)
    /* Scheduled traffic global configuration initialization begin */
    {
        vtss_qos_tas_conf_t *conf = &vtss_state->qos.tas.global_conf;

        // By default, all queues (unprotected and protected) will
        // be implementing guard band. See also 'sch_traffic_queues'
        // configuration per port below.
        conf->always_guard_band = TRUE;
    }
    /* Scheduled traffic global configuration initialization end */

    /* Scheduled traffic port configuration initialization begin */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        vtss_qos_tas_port_conf_t *conf = &vtss_state->qos.tas.port_conf[port_no];

        // All queues are open by default.
        for (i = 0; i < VTSS_QUEUE_ARRAY_SIZE; i++) {
            conf->gate_open[i] = TRUE;
        }
    }
    /* Scheduled traffic port configuration initialization end */
#endif /* defined(VTSS_FEATURE_QOS_TAS) */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    /* Frame Preemption port configuration initialization begin */
    for (port_no = VTSS_PORT_NO_START; port_no < VTSS_PORT_NO_END; port_no++) {
        vtss_qos_fp_port_conf_t *conf = &vtss_state->qos.fp.port_conf[port_no];

        conf->verify_disable_tx = TRUE;
        conf->verify_time = 10;
    }
    /* Frame Preemption port configuration initialization end */
#endif /* defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION) */

    /* State initialization begin */
#if defined(VTSS_FEATURE_EVC_POLICERS)
    vtss_state->qos.evc_policer_max = VTSS_EVC_POLICERS;
#endif /* VTSS_FEATURE_EVC_POLICERS */

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    {
        vtss_qos_map_adm_t *m = &vtss_state->qos.imap;

        m->kind = VTSS_QOS_MAP_KIND_INGRESS;
        strncpy(m->name, "Ingress", sizeof(m->name));

        /* Id table */
        m->id.entry     = vtss_state->qos.imap_id;
        m->id.entry_len = VTSS_QOS_INGRESS_MAP_IDS;

        /* Ix table. Ingress mapping has only one resource */
        m->ix[0].entry     = vtss_state->qos.imap_ix;
        m->ix[0].entry_len = VTSS_QOS_INGRESS_MAP_ROWS;
        m->ix[0].reserved  = VTSS_QOS_INGRESS_MAP_IX_RESERVED;

        /* Store function pointers locally. Check for missing function pointers here and not every time they are called */
        m->key2len = vtss_qos_ingress_map_key2len;
        if (vtss_state->qos.ingress_map_vcap_update) {
            m->vcap_update = vtss_state->qos.ingress_map_vcap_update;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.ingress_map_vcap_update");
        }
        if (vtss_state->qos.ingress_map_hw_update) {
            m->hw_update = vtss_state->qos.ingress_map_hw_update;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.ingress_map_hw_update");
        }
        if (vtss_state->qos.ingress_map_hw_copy) {
            m->hw_copy = vtss_state->qos.ingress_map_hw_copy;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.ingress_map_hw_copy");
        }

        vtss_cmn_qos_map_adm_init(m);
    }
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    {
        vtss_qos_map_adm_t *m = &vtss_state->qos.emap;

        m->kind = VTSS_QOS_MAP_KIND_EGRESS;
        strncpy(m->name, "Egress", sizeof(m->name));

        /* Id table */
        m->id.entry     = vtss_state->qos.emap_id;
        m->id.entry_len = VTSS_QOS_EGRESS_MAP_IDS;

        /* Ix table resource A */
        m->ix[0].entry     = vtss_state->qos.emap_ix_a;
        m->ix[0].entry_len = VTSS_QOS_EGRESS_MAP_ROWS;
        m->ix[0].reserved  = VTSS_QOS_EGRESS_MAP_IX_RESERVED;

        /* Ix table resource B */
        m->ix[1].entry     = vtss_state->qos.emap_ix_b;
        m->ix[1].entry_len = VTSS_QOS_EGRESS_MAP_ROWS;
        m->ix[1].reserved  = VTSS_QOS_EGRESS_MAP_IX_RESERVED;

        /* Store function pointers locally. Check for missing function pointers here and not every time they are called */
        m->key2len = vtss_qos_egress_map_key2len;
        if (vtss_state->qos.egress_map_vcap_update) {
            m->vcap_update = vtss_state->qos.egress_map_vcap_update;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.egress_map_vcap_update");
        }
        if (vtss_state->qos.egress_map_hw_update) {
            m->hw_update = vtss_state->qos.egress_map_hw_update;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.egress_map_hw_update");
        }
        if (vtss_state->qos.egress_map_hw_copy) {
            m->hw_copy = vtss_state->qos.egress_map_hw_copy;
        } else {
            VTSS_E("Missing function pointer: vtss_state->qos.egress_map_hw_copy");
        }

        vtss_cmn_qos_map_adm_init(m);
    }
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

    /* State initialization end */
    return VTSS_RC_OK;
}

/* - QoS utilities ------------------------------------------------- */

u32 vtss_cmn_qos_chip_prio(vtss_state_t *vtss_state, const vtss_prio_t prio)
{
    if (prio < vtss_state->qos.prio_count) {
        return (prio * vtss_state->qos.conf.prios) / vtss_state->qos.prio_count;
    } else {
        VTSS_E("illegal prio: %u  prio_count: %u", prio, vtss_state->qos.prio_count);
        return 0;
    }
}

vtss_rc vtss_cmn_qos_port_conf_set(vtss_state_t *vtss_state, const vtss_port_no_t port_no)
{
    vtss_rc                  rc   = VTSS_RC_ERROR;
#if defined(VTSS_FEATURE_ES0)
    vtss_qos_port_conf_t     *old = &vtss_state->qos.port_conf_old;
    vtss_qos_port_conf_t     *new = &vtss_state->qos.port_conf[port_no];
    u8                       pcp;
    u16                      flags = 0;
#endif /* VTSS_FEATURE_ES0 */

    VTSS_D("Enter - port_no: %u", port_no);
    rc = vtss_state->qos.port_conf_update(vtss_state, port_no);

#if defined(VTSS_FEATURE_ES0)
    if (old->tag_remark_mode != new->tag_remark_mode ||
#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
        old->egress_map != new->egress_map ||
#endif
        old->tag_default_pcp != new->tag_default_pcp ||
        old->tag_default_dei != new->tag_default_dei) {
        /* PCP/DEI remark mode changed, update QOS */
        flags |= (VTSS_ES0_FLAG_OT_QOS | VTSS_ES0_FLAG_IT_QOS);
    }
    for (pcp = 0; pcp < 8; pcp++) {
        if (old->qos_class_map[pcp][0] != new->qos_class_map[pcp][0]) {
            flags |= VTSS_ES0_FLAG_PCP_MAP;
            break;
        }
    }
    if (flags) {
        /* Update ES0 rules */
        VTSS_RC(vtss_vcap_es0_update(vtss_state, port_no, flags));
    }
#endif /* VTSS_FEATURE_ES0 */

    VTSS_D("Exit");
    return rc;
}

/**
 * \brief Convert QoS scheduler weight to cost.
 *
 * \param weight [IN]    Array of weights. Range is 1..100.
 * \param cost [OUT]     Array of costs. Range is 0..(2^bit_width - 1).
 * \param num [IN]       Number of entries in weight and cost.
 * \param bit_width [IN] Bit-width of resulting cost. Range is 4..8. E.g. 5 corresponds to a cost between 0 and 31.
 *
 * \return Return code.
 **/
vtss_rc vtss_cmn_qos_weight2cost(const vtss_pct_t *weight, u8 *cost, u32 num, u8 bit_width)
{
    u32 i, c_max;
    vtss_pct_t w_min = 100;
    if ((bit_width < 4) || (bit_width > 8)) {
        VTSS_E("illegal bit_width: %u", bit_width);
        return VTSS_RC_ERROR;
    }
    c_max = 1 << bit_width;
    for (i = 0; i < num; i++) {
        if ((weight[i] < 1) || (weight[i] > 100)) {
            VTSS_E("illegal weight: %u", weight[i]);
            return VTSS_RC_ERROR;
        }
        w_min = MIN(w_min, weight[i]);
    }
    for (i = 0; i < num; i++) {
        // Round half up: Multiply with 16 before division, add 8 and divide result with 16 again
        u32 c = (((c_max << 4) * w_min / weight[i]) + 8) >> 4;
        cost[i] = MAX(1, c) - 1; // Force range to be 0..(c_max - 1)
    }
    return VTSS_RC_OK;
}

u32 vtss_cmn_qos_storm_mode(vtss_packet_rate_t rate, vtss_storm_policer_mode_t mode)
{
    if (rate == VTSS_PACKET_RATE_DISABLED) {
        return 0; /* Disabled */
    }

    switch (mode) {
    case VTSS_STORM_POLICER_MODE_PORTS_AND_CPU:
        return 3; /* Police both CPU and front port destinations */
    case VTSS_STORM_POLICER_MODE_PORTS_ONLY:
        return 2; /* Police front port destinations only */
    case VTSS_STORM_POLICER_MODE_CPU_ONLY:
        return 1; /* Police CPU destination only */
    default:
        return 0; /* Disabled */
    }
}

u32 vtss_cmn_qos_packet_rate(vtss_packet_rate_t rate, u32 *unit)
{
    int i;
    u32 new_rate;

    if (rate > 512) {
        /* Supported rate = 1k, 2k, 4k, 8k, 16k, 32k, 64k, 128k, 256k, 512k and 1024k frames per second*/
        new_rate = VTSS_DIV_ROUND_UP(rate, 1000);
        *unit = 0; /* Base unit is 1 kiloframes per second */
    } else {
        /* Supported rate = 1, 2, 4, 8, 16, 32, 64, 128, 256 and 512 frames per second */
        new_rate = rate;
        *unit = 1; /* Base unit is 1 frame per second */
    }

    for (i = 0; i < 10; i++) {
        if ((u32)(1 << i) >= new_rate) { /* 2^i is equal to or higher than new_rate */
            break;
        }
    }

    /*
     * Note that we return 10 if there is no match in the for loop above.
     * This is the maximum allowed rate of 2^10 = 1024 kiloframes per second
     */
    return i;
}

#if defined(VTSS_FEATURE_QCL)
/* Add QCE */
vtss_rc vtss_cmn_qce_add(vtss_state_t *vtss_state,
                         const vtss_qcl_id_t  qcl_id,
                         const vtss_qce_id_t  qce_id,
                         const vtss_qce_t     *const qce)
{
    vtss_vcap_obj_t             *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t            user = VTSS_IS1_USER_QOS;
    vtss_vcap_data_t            data;
    vtss_is1_data_t             *is1 = &data.u.is1;
    vtss_is1_entry_t            entry;
    vtss_is1_action_t           *action = &entry.action;
    vtss_is1_key_t              *key = &entry.key;
    vtss_res_chg_t              res_chg;
    vtss_vcap_key_size_t        key_size = VTSS_VCAP_KEY_SIZE_FULL;
    vtss_vcap_range_chk_table_t range_new = vtss_state->vcap.range; /* Make a temporary working copy of the range table */

    /* Check QCE ID */
    if (qce->id == VTSS_QCE_ID_LAST || qce->id == qce_id) {
        VTSS_E("illegal qce id: %u", qce->id);
        return VTSS_RC_ERROR;
    }

    /* Initialize entry data */
    vtss_vcap_is1_init(&data, &entry);

    is1->lookup = 1; /* Second lookup */

#if defined(VTSS_ARCH_OCELOT) || defined(VTSS_ARCH_LAN966X)
    /* For Serval, the configured key of the first port is used */
    {
        vtss_port_no_t port_no;
        is1->lookup = 2; /* Third lookup */

        key->key_type = VTSS_VCAP_KEY_TYPE_DOUBLE_TAG; /* Default if no ports assigned */
        for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
            if (qce->key.port_list[port_no]) {
                key->key_type = vtss_state->qos.port_conf[port_no].key_type;
                VTSS_D("Using key_type %u from port %u", key->key_type, port_no);
                break; /* Stop after first port */
            }
        }
        key_size = vtss_vcap_key_type2size(key->key_type);
    }
#endif

#if defined(VTSS_ARCH_JAGUAR_2) || defined(VTSS_ARCH_SPARX5)
    if (vtss_state->arch == VTSS_ARCH_JR2 || vtss_state->arch == VTSS_ARCH_ANT) {
        /* Jaguar-2 consumes full row */
        key->key_type = VTSS_VCAP_KEY_TYPE_MAC_IP_ADDR;
    }
#endif

    /* Check if main entry exists */
    VTSS_MEMSET(&res_chg, 0, sizeof(res_chg));
    if (vtss_vcap_lookup(vtss_state, obj, user, qce->id, &data, NULL) == VTSS_RC_OK) {
        is1->entry = &entry; /* NOTE: Restore entry pointer which was overwritten by vtss_vcap_lookup() */
        res_chg.del_key[key_size] = 1;
        /* Free eventually old range checkers */
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->vid_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->dscp_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->sport_range));
        VTSS_RC(vtss_vcap_range_free(&range_new, is1->dport_range));
        is1->vid_range = VTSS_VCAP_RANGE_CHK_NONE;
        is1->dscp_range = VTSS_VCAP_RANGE_CHK_NONE;
        is1->sport_range = VTSS_VCAP_RANGE_CHK_NONE;
        is1->dport_range = VTSS_VCAP_RANGE_CHK_NONE;
    }

    /* Check that the entry can be added */
    res_chg.add_key[key_size] = 1;
    VTSS_RC(vtss_cmn_vcap_res_check(obj, &res_chg));
    data.key_size = key_size;

    /* Copy action data */
    action->dscp_enable    = qce->action.dscp_enable;
    action->dscp           = qce->action.dscp;
    action->dp_enable      = qce->action.dp_enable;
    action->dp             = qce->action.dp;
    action->prio_enable    = qce->action.prio_enable;
    action->prio           = qce->action.prio;
    action->pcp_dei_enable = qce->action.pcp_dei_enable;
    action->pcp_enable     = qce->action.pcp_dei_enable;
    action->dei_enable     = qce->action.pcp_dei_enable;
    action->pcp            = qce->action.pcp;
    action->dei            = qce->action.dei;
    action->pag_enable     = qce->action.policy_no_enable;
    action->pag            = qce->action.policy_no;
#if (defined VTSS_FEATURE_QCL_MAP_ACTION)
    if (qce->action.map_id_enable) {
        is1->map_id = qce->action.map_id;
        is1->flags = VTSS_IS1_FLAG_MAP_ID;
    }
#endif /* VTSS_FEATURE_QCL_MAP_ACTION */

    /* Copy key data */
    VTSS_MEMCPY(key->port_list, qce->key.port_list, sizeof(key->port_list));

    key->mac.dmac_mc = qce->key.mac.dmac_mc;
    key->mac.dmac_bc = qce->key.mac.dmac_bc;
    if (key->mac.dmac_bc == VTSS_VCAP_BIT_1) {
        key->mac.dmac_mc = VTSS_VCAP_BIT_1; /* mc must be 1 or don't care in order to match on a bc frame */
    }
#if defined(VTSS_FEATURE_QCL_KEY_DMAC)
    key->mac.dmac = qce->key.mac.dmac;
#endif /* defined(VTSS_FEATURE_QCL_KEY_DMAC) */
    key->mac.smac = qce->key.mac.smac; /* Only the 24 most significant bits (OUI) are supported on Jaguar1, rest are wildcards */

    key->tag.vid    = qce->key.tag.vid;
    VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->vid_range, VTSS_VCAP_RANGE_TYPE_VID, &key->tag.vid));
    key->tag.pcp    = qce->key.tag.pcp;
    key->tag.dei    = qce->key.tag.dei;
    key->tag.tagged = qce->key.tag.tagged;
    key->tag.s_tag  = qce->key.tag.s_tag;

#if defined(VTSS_FEATURE_QCL_KEY_INNER_TAG)
    key->inner_tag.vid    = qce->key.inner_tag.vid;
    (void)vtss_vcap_vr_rng2vm(&key->inner_tag.vid); /* Value/mask is required here! */
    key->inner_tag.pcp    = qce->key.inner_tag.pcp;
    key->inner_tag.dei    = qce->key.inner_tag.dei;
    key->inner_tag.tagged = qce->key.inner_tag.tagged;
    key->inner_tag.s_tag  = qce->key.inner_tag.s_tag;
#endif /* defined(VTSS_FEATURE_QCL_KEY_INNER_TAG) */

    switch (qce->key.type) {
    case VTSS_QCE_TYPE_ANY:
        key->type = VTSS_IS1_TYPE_ANY;
        break;
    case VTSS_QCE_TYPE_ETYPE:
        key->type              = VTSS_IS1_TYPE_ETYPE;
        key->frame.etype.etype = qce->key.frame.etype.etype;
        key->frame.etype.data  = qce->key.frame.etype.data;
        break;
    case VTSS_QCE_TYPE_LLC:
        key->type           = VTSS_IS1_TYPE_LLC;
        key->frame.llc.data = qce->key.frame.llc.data;
        break;
    case VTSS_QCE_TYPE_SNAP:
        key->type            = VTSS_IS1_TYPE_SNAP;
        key->frame.snap.data = qce->key.frame.snap.data;
        break;
    case VTSS_QCE_TYPE_IPV4:
        key->type                = VTSS_IS1_TYPE_IPV4;
        key->frame.ipv4.fragment = qce->key.frame.ipv4.fragment;
        key->frame.ipv4.dscp     = qce->key.frame.ipv4.dscp;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dscp_range, VTSS_VCAP_RANGE_TYPE_DSCP, &key->frame.ipv4.dscp));
        key->frame.ipv4.proto    = qce->key.frame.ipv4.proto;
        key->frame.ipv4.sip      = qce->key.frame.ipv4.sip;
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
        key->frame.ipv4.dip      = qce->key.frame.ipv4.dip;
#endif /* defined(VTSS_FEATURE_QCL_KEY_DIP) */
        key->frame.ipv4.sport    = qce->key.frame.ipv4.sport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->sport_range, VTSS_VCAP_RANGE_TYPE_SPORT, &key->frame.ipv4.sport));
        key->frame.ipv4.dport    = qce->key.frame.ipv4.dport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dport_range, VTSS_VCAP_RANGE_TYPE_DPORT, &key->frame.ipv4.dport));
        break;
    case VTSS_QCE_TYPE_IPV6:
        key->type                = VTSS_IS1_TYPE_IPV6;
        key->frame.ipv6.dscp     = qce->key.frame.ipv6.dscp;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dscp_range, VTSS_VCAP_RANGE_TYPE_DSCP, &key->frame.ipv6.dscp));
        key->frame.ipv6.proto    = qce->key.frame.ipv6.proto;
        key->frame.ipv6.sip      = qce->key.frame.ipv6.sip;
#if defined(VTSS_FEATURE_QCL_KEY_DIP)
        key->frame.ipv6.dip      = qce->key.frame.ipv6.dip;
#endif /* defined(VTSS_FEATURE_QCL_KEY_DIP) */
        key->frame.ipv6.sport    = qce->key.frame.ipv6.sport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->sport_range, VTSS_VCAP_RANGE_TYPE_SPORT, &key->frame.ipv6.sport));
        key->frame.ipv6.dport    = qce->key.frame.ipv6.dport;
        VTSS_RC(vtss_vcap_vr_alloc(&range_new, &is1->dport_range, VTSS_VCAP_RANGE_TYPE_DPORT, &key->frame.ipv6.dport));
        break;
    default:
        VTSS_E("illegal type: %d", qce->key.type);
        return VTSS_RC_ERROR;
    }

    /* Commit range checkers */
    VTSS_RC(vtss_vcap_range_commit(vtss_state, &range_new));

    /* Add main entry */
    VTSS_RC(vtss_vcap_add(vtss_state, obj, user, qce->id, qce_id, &data, 0));
    return VTSS_RC_OK;
}

/* Delete QCE */
vtss_rc vtss_cmn_qce_del(vtss_state_t *vtss_state,
                         const vtss_qcl_id_t  qcl_id,
                         const vtss_qce_id_t  qce_id)
{
    vtss_vcap_obj_t  *obj = vtss_vcap_is1_obj_get(vtss_state);
    vtss_vcap_user_t user = VTSS_IS1_USER_QOS;
    vtss_vcap_data_t data;
    vtss_is1_data_t  *is1 = &data.u.is1;

    if (vtss_vcap_lookup(vtss_state, obj, user, qce_id, &data, NULL) != VTSS_RC_OK) {
        VTSS_E("qce_id: %u not found", qce_id);
        return VTSS_RC_ERROR;
    }

    /* Delete range checkers and main entry */
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->vid_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dscp_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->sport_range));
    VTSS_RC(vtss_vcap_range_free(&vtss_state->vcap.range, is1->dport_range));
    is1->vid_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->dscp_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->sport_range = VTSS_VCAP_RANGE_CHK_NONE;
    is1->dport_range = VTSS_VCAP_RANGE_CHK_NONE;
    VTSS_RC(vtss_vcap_del(vtss_state, obj, user, qce_id));

    return VTSS_RC_OK;
}
#endif // VTSS_FEATURE_QCL

/* - Debug print --------------------------------------------------- */

#if VTSS_OPT_DEBUG_PRINT
#if defined(VTSS_FEATURE_EVC_POLICERS)
void vtss_qos_debug_print_dlb(vtss_state_t *vtss_state,
                              const vtss_debug_printf_t pr,
                              const vtss_debug_info_t   *const info)
{
    u32                     i;
    vtss_evc_policer_conf_t *pol_conf;
    BOOL                    cm = 1, header = 1;

    for (i = 0; i < VTSS_EVC_POLICERS; i++) {
#if defined(VTSS_ARCH_LUTON26)
        vtss_policer_alloc_t *pol_alloc = &vtss_state->qos.evc_policer_alloc[i];
#endif /* VTSS_ARCH_LUTON26 */
        pol_conf = &vtss_state->qos.evc_policer_conf[i];
        if (pol_conf->enable == 0
#if defined(VTSS_ARCH_LUTON26)
            && pol_alloc->count == 0
#endif /* VTSS_ARCH_LUTON26 */
           ) {
            continue;
        }
        if (header) {
            header = 0;
            vtss_debug_print_header(pr, "Policers");
            pr("Policer  Type    CM  CF  Rate  CIR         CBS         EIR         EBS         ");
#if defined(VTSS_ARCH_LUTON26)
            pr("Count  L26 Policer");
#endif /* VTSS_ARCH_LUTON26 */
            pr("\n");
        }
#if defined(VTSS_ARCH_JAGUAR_2)
        cm = pol_conf->cm;
#endif /* VTSS_ARCH_JAGUAR_2 */
        pr("%-9u%-8s%-4u%-4u%-6s%-12u%-12u%-12u%-12u",
           i,
           pol_conf->type == VTSS_POLICER_TYPE_MEF ? "MEF" :
           pol_conf->type == VTSS_POLICER_TYPE_SINGLE ? "SINGLE" : "?",
           cm, pol_conf->cf, pol_conf->line_rate ? "Line" : "Data",
           pol_conf->cir, pol_conf->cbs, pol_conf->eir, pol_conf->ebs);
#if defined(VTSS_ARCH_LUTON26)
        pr("%-7u%u", pol_alloc->count, pol_alloc->policer);
#endif /* VTSS_ARCH_LUTON26 */
        pr("\n");
    }
    if (!header) {
        pr("\n");
    }
}
#endif /* VTSS_FEATURE_EVC_POLICERS */

static void vtss_debug_print_packet_rate(const vtss_debug_printf_t pr,
                                         const vtss_debug_info_t   *const info,
                                         const char                *name,
                                         vtss_packet_rate_t        rate,
                                         BOOL                      frame_rate,
                                         vtss_storm_policer_mode_t mode)
{
    const char *mode_txt;

    switch (mode) {
    case VTSS_STORM_POLICER_MODE_PORTS_AND_CPU:
        mode_txt = "Police ports and CPU destinations";
        break;
    case VTSS_STORM_POLICER_MODE_PORTS_ONLY:
        mode_txt = "Police port destinations only";
        break;
    case VTSS_STORM_POLICER_MODE_CPU_ONLY:
        mode_txt = "Police CPU destination only";
        break;
    default:
        mode_txt = "Invalid mode!";
        break;
    }

    if (rate == VTSS_PACKET_RATE_DISABLED) {
        pr("%-32s: Disabled. %s.\n", name, mode_txt);
    } else {
        pr("%-32s: %u %s. %s.\n", name, rate, frame_rate ? "fps" : "kbps", mode_txt);
    }
}

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP)
static void vtss_debug_print_map(const vtss_debug_printf_t pr,
                                 const vtss_debug_info_t   *const info,
                                 const vtss_qos_map_adm_t  *m)
{
    {
        u16 id, ix, res;
        int len;

        pr("QoS %s Map Id Config:\n\n", m->name);
        pr(" Id  Ix Res\n");
        for (id = 0; id < m->id.entry_len; id++) {
            ix  = m->id.entry[id].ix;
            res = m->id.entry[id].res;
            if (info->full || (ix != VTSS_QOS_MAP_ID_NONE)) {
                if (ix != VTSS_QOS_MAP_ID_NONE) {
                    pr("%3u %3u %3u", id, ix, res);
                    if (id != m->ix[res].entry[ix].id) {
                        pr(" <-- INCONSISTENT TABLES!");
                    }
                } else {
                    pr("%3u   - %3u", id, res);
                }
                pr("\n");
            }
        }
        pr("\n");

        for (res = 0; res < VTSS_QOS_MAP_RESOURCES; res++) {
            if (m->ix[res].entry == NULL) {
                continue; /* Resource not present */
            }
            pr("QoS %s Map Index Config, Res %u:\n\n", m->name, res);
            pr(" Ix  Id Key Len Flg\n");
            for (ix = 0; ix < m->ix[res].entry_len; ix++) {
                id = m->ix[res].entry[ix].id;
                len = m->key2len(m->ix[res].entry[ix].key);
                if (info->full || (id != VTSS_QOS_MAP_ID_NONE) || ((ix < m->ix[res].free) && len)) {
                    if (id != VTSS_QOS_MAP_ID_NONE) {
                        pr("%3u %3u %3u %3d x%02x", ix, id, m->ix[res].entry[ix].key, len, m->ix[res].entry[ix].flags);
                        if ((ix != m->id.entry[id].ix) || (res != m->id.entry[id].res)) {
                            pr(" <-- INCONSISTENT TABLES!");
                        }
                        if (ix >= m->ix[res].free) {
                            pr(" <-- INCONSISTENT FREE!");
                        }
                    } else {
                        pr("%3u   - %3d %3d x%02x", ix,  m->ix[res].entry[ix].key, len, m->ix[res].entry[ix].flags);
                    }
                    pr("\n");
                }
            }
            pr("\n");

            pr("Free    : %u\n", m->ix[res].free);
            pr("Reserved: %u\n", m->ix[res].reserved);
            pr("\n");
        }
#if 0
        {
            size_t adm      = sizeof(vtss_qos_map_adm_t);
            size_t id_adm   = sizeof(vtss_qos_map_id_adm_t);
            size_t id_entry = sizeof(vtss_qos_map_id_entry_t);
            size_t ix_adm   = sizeof(vtss_qos_map_ix_adm_t);
            size_t ix_entry = sizeof(vtss_qos_map_ix_entry_t);

            pr("Memory usage:\n");
            pr(" adm      : %4zu bytes\n", adm);
            pr(" id_adm   : %4zu bytes (part of adm)\n", id_adm);
            pr(" id_entry : %4zu bytes * %u\n", id_entry, m->id.entry_len);
            pr(" ix_adm   : %4zu bytes (part of adm)\n", ix_adm);
            pr(" ix_entry : %4zu bytes * (%u + %u)\n", ix_entry, m->ix[0].entry_len, m->ix[1].entry_len);
            pr(" total    : %4zu bytes (adm + (id_entry * id.entry_len) + (ix_entry * (ix[0].entry_len + ix[1].entry_len))\n",
               adm + (id_entry * m->id.entry_len) + (ix_entry * (m->ix[0].entry_len + m->ix[1].entry_len)));
            pr("\n");
        }
#endif
    }
}
#endif /* defined(VTSS_FEATURE_QOS_INGRESS_MAP) || defined(VTSS_FEATURE_QOS_EGRESS_MAP) */

#if defined(VTSS_FEATURE_QOS_TAS)
static char *debug_gate_operation_string(const vtss_qos_tas_gco_t  gate_operation)
{
    switch (gate_operation) {
        case VTSS_QOS_TAS_GCO_SET_GATE_STATES:     return("SET");
        case VTSS_QOS_TAS_GCO_SET_AND_HOLD_MAC:    return("SET_HOLD");
        case VTSS_QOS_TAS_GCO_SET_AND_RELEASE_MAC: return("SET_RELEASE");
    }
    return("INVALID");
}

static u8 bool8_to_u8(BOOL *array)
{
    u8 i, value = 0, mask = 1;

    for (i = 0; i < 8; i++, mask<<=1) {
        if (array[i]) {
            value |= mask;
        }
    }
    return value;
}
#endif

void vtss_qos_debug_print(vtss_state_t *vtss_state,
                          const vtss_debug_printf_t pr,
                          const vtss_debug_info_t   *const info)
{
    vtss_qos_conf_t *conf = &vtss_state->qos.conf;
    vtss_port_no_t  port_no;

    if (!vtss_debug_group_enabled(pr, info, VTSS_DEBUG_GROUP_QOS)) {
        return;
    }

    vtss_debug_print_value(pr, "Number of priorities", conf->prios);
    vtss_debug_print_packet_rate(pr, info, "Storm Unicast",     conf->policer_uc, conf->policer_uc_frame_rate, conf->policer_uc_mode);
    vtss_debug_print_packet_rate(pr, info, "Storm Multicast",   conf->policer_mc, conf->policer_mc_frame_rate, conf->policer_mc_mode);
    vtss_debug_print_packet_rate(pr, info, "Storm Broadcast",   conf->policer_bc, conf->policer_bc_frame_rate, conf->policer_bc_mode);
    pr("\n");

#if defined(VTSS_FEATURE_QOS_INGRESS_MAP)
    vtss_debug_print_map(pr, info, &vtss_state->qos.imap);
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_EGRESS_MAP)
    vtss_debug_print_map(pr, info, &vtss_state->qos.emap);
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */

#if defined(VTSS_FEATURE_QOS_WRED_V2)
    {
        int queue, dpl;
        pr("QoS WRED Config:\n\n");
        pr("Queue Dpl Ena Min Max Dp or Fl\n");
        for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
            for (dpl = 0; dpl < 2; dpl++) {
                pr("%5d %3d %3d %3d %3d %-s\n",
                   queue,
                   dpl,
                   VTSS_BOOL(conf->red_v2[queue][dpl].enable),
                   conf->red_v2[queue][dpl].min_fl,
                   conf->red_v2[queue][dpl].max,
                   (conf->red_v2[queue][dpl].max_unit == VTSS_WRED_V2_MAX_DP) ? "Drop Probability" : "Fill Level");
            }
        }
        pr("\n");
    }
#endif  /* VTSS_FEATURE_QOS_WRED_V2 */

#if defined(VTSS_FEATURE_QOS_WRED_V3)
    {
        int group, queue, dpl;
        pr("QoS WRED Config:\n\n");
        pr("Group Queue Dpl Ena Min Max Dp or Fl\n");
        for (group = 0; group < VTSS_WRED_GROUP_CNT; group++) {
            for (queue = VTSS_QUEUE_START; queue < VTSS_QUEUE_END; queue++) {
                for (dpl = 0; dpl < VTSS_WRED_DPL_CNT; dpl++) {
                    pr("%5d %5d %3d %3d %3d %3d %-s\n",
                       group,
                       queue,
                       dpl + 1,
                       VTSS_BOOL(conf->red_v3[queue][dpl][group].enable),
                       conf->red_v3[queue][dpl][group].min_fl,
                       conf->red_v3[queue][dpl][group].max,
                       (conf->red_v3[queue][dpl][group].max_unit == VTSS_WRED_V2_MAX_DP) ? "Drop Probability" : "Fill Level");
                }
            }
        }
        pr("\n");
    }
#endif  /* VTSS_FEATURE_QOS_WRED_V3 */

    {
        int i;
        pr("QoS DSCP Classification Config:\n\n");
        pr("DSCP Trust QoS DPL\n");
        for (i = 0; i < 64; i++) {
            pr("%4d %5d %3u %3d\n", i, conf->dscp_trust[i], conf->dscp_qos_class_map[i], conf->dscp_dp_level_map[i]);
        }
        pr("\n");
    }

    {
        int i;
        pr("QoS DSCP Remarking Config:\n\n");
        pr("DSCP I_Remark Translate QoS_Remap");
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
        pr("_DP0 QoS_Remap_DP1");
#endif /* VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE */
        pr("\n");

        for (i = 0; i < 64; i++) {
            pr("%4d %8d ", i, conf->dscp_remark[i]);
            pr("%9d %9d", conf->dscp_translate_map[i], conf->dscp_remap[i]);
#if defined(VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE)
            pr("     %9d", conf->dscp_remap_dp1[i]);
#endif /* VTSS_FEATURE_QOS_DSCP_REMARK_DP_AWARE */
            pr("\n");
        }
        pr("\n");

        pr("QoS DSCP Classification from QoS Config:\n\n");
        pr("QoS DSCP_DP0 DSCP_DP1\n");

        for (i = 0; i < VTSS_PRIO_ARRAY_SIZE; i++) {
            pr("%3d %4d", i, conf->dscp_qos_map[i]);
            pr("     %4d", conf->dscp_qos_map_dp1[i]);
            pr("\n");
        }
        pr("\n");
    }

    pr("QoS Port Classification Config:\n\n");
    pr("Port PCP COS DEI DPL T_EN D_EN ");
#if defined(VTSS_FEATURE_QOS_WRED_V3)
    pr("W_GRP ");
#endif /* VTSS_FEATURE_QOS_WRED_V3 */
#if (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
    pr("COSID ");
#endif /* VTSS_FEATURE_QOS_COSID_CLASSIFICATION */
#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
    pr("I_MAP ");
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */
#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
    pr("O_MAP ");
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */
    pr("\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u ", port_no);
        pr("%3u %3u ", port_conf->usr_prio, port_conf->default_prio);
        pr("%3u %3u %4u %4u ", port_conf->default_dei, port_conf->default_dpl, port_conf->tag_class_enable, port_conf->dscp_class_enable);
#if defined(VTSS_FEATURE_QOS_WRED_V3)
        pr("%5u ", port_conf->wred_group);
#endif /* VTSS_FEATURE_QOS_WRED_V3 */
#if (defined VTSS_FEATURE_QOS_COSID_CLASSIFICATION)
        pr("%5u ", port_conf->cosid);
#endif /* VTSS_FEATURE_QOS_COSID_CLASSIFICATION */
#if (defined VTSS_FEATURE_QOS_INGRESS_MAP)
        pr("%5u ", port_conf->ingress_map);
#endif /* VTSS_FEATURE_QOS_INGRESS_MAP */
#if (defined VTSS_FEATURE_QOS_EGRESS_MAP)
        pr("%5u ", port_conf->egress_map);
#endif /* VTSS_FEATURE_QOS_EGRESS_MAP */
        pr("\n");
    }
    pr("\n");

    pr("QoS Port Classification PCP, DEI to QoS class, DP level Mapping:\n\n");
    pr("Port QoS class (2*PCP+DEI)           DP level (2*PCP+DEI)\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int pcp, dei, class_ct = 0, dpl_ct = 0;
        char class_buf[40], dpl_buf[40];
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        for (pcp = VTSS_PCP_START; pcp < VTSS_PCP_END; pcp++) {
            for (dei = VTSS_DEI_START; dei < VTSS_DEI_END; dei++) {
                const char *delim = ((pcp == VTSS_PCP_START) && (dei == VTSS_DEI_START)) ? "" : ",";
                class_ct += VTSS_SNPRINTF(class_buf + class_ct, sizeof(class_buf) - class_ct, "%s%u", delim, port_conf->qos_class_map[pcp][dei]);
                dpl_ct   += VTSS_SNPRINTF(dpl_buf   + dpl_ct,   sizeof(dpl_buf)   - dpl_ct,   "%s%u",  delim, port_conf->dp_level_map[pcp][dei]);
            }
        }
        pr("%4u %s %s\n", port_no, class_buf, dpl_buf);
    }
    pr("\n");

    pr("QoS Port Ingress Policer Config:\n\n");
    pr("Port Policer Burst      Rate       FC");
    pr("\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        int policer;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u ", port_no);
        for (policer = 0; policer < VTSS_PORT_POLICERS; policer++) {
            pr("%7d 0x%08x 0x%08x %d\n     ",
               policer,
               port_conf->policer_port[policer].level,
               port_conf->policer_port[policer].rate,
               port_conf->policer_ext_port[policer].flow_control);
        }
        pr("\r");
    }
    pr("\n");

    pr("QoS Queue Ingress Policer Config:\n\n");
    pr("Port Queue Burst      Rate\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        int queue;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u ", port_no);
        for (queue = 0; queue < VTSS_QUEUE_ARRAY_SIZE; queue++) {
            pr("%5d 0x%08x 0x%08x\n     ",
               queue,
               port_conf->policer_queue[queue].level,
               port_conf->policer_queue[queue].rate);
        }
        pr("\r");
    }
    pr("\n");

    pr("QoS Port Scheduler Config:\n\n");
    pr("Port Sch Mode  Cnt Q0  Q1  Q2  Q3  Q4  Q5  Q6  Q7\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        int i;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u %8s ", port_no, port_conf->dwrr_enable ? "Weighted" : "Strict");
        pr("%3u ",
#if defined(VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT)
           port_conf->dwrr_cnt
#else
           6
#endif /* VTSS_FEATURE_QOS_SCHEDULER_DWRR_CNT */
          );
        for (i = 0; i < 8; i++) {
            pr("%3u ", port_conf->queue_pct[i]);
        }
        pr("\n");
    }
    pr("\n");

    pr("QoS Port Egress Shaper Config:\n\n");
    pr("Port CBS        CIR        ");
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    pr("EBS        EIR");
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
    pr("\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u 0x%08x 0x%08x ",
           port_no,
           port_conf->shaper_port.level,
           port_conf->shaper_port.rate);
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
        pr("0x%08x 0x%08x ",
           port_conf->shaper_port.ebs,
           port_conf->shaper_port.eir);
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
        pr("\n");
    }
    pr("\n");

    pr("QoS Queue Egress Shaper Config:\n\n");
    pr("Port Queue CBS        CIR        ");
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
    pr("EBS        EIR        ");
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
    pr("Excess ");
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
    pr("Credit ");
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
    pr("CutThrough ");
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH */
    pr("\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        int queue;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u ", port_no);
        for (queue = 0; queue < VTSS_QUEUE_ARRAY_SIZE; queue++) {
            pr("%5d 0x%08x 0x%08x ",
               queue,
               port_conf->shaper_queue[queue].level,
               port_conf->shaper_queue[queue].rate);
#if defined(VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB)
            pr("0x%08x 0x%08x ",
               port_conf->shaper_queue[queue].ebs,
               port_conf->shaper_queue[queue].eir);
#endif /* VTSS_FEATURE_QOS_EGRESS_SHAPERS_DLB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB)
            pr("%6d ", VTSS_BOOL(port_conf->excess_enable[queue]));
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_EB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB)
            pr("%6d ", VTSS_BOOL(port_conf->shaper_queue[queue].credit_enable));
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_SHAPERS_CRB */
#if defined(VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH)
            pr("%10d ", VTSS_BOOL(port_conf->cut_through_enable[queue]));
#endif /* VTSS_FEATURE_QOS_EGRESS_QUEUE_CUT_THROUGH */
            pr("\n     ");
        }
        pr("\r");
    }
    pr("\n");

    pr("QoS Port Tag Remarking Config:\n\n");
    pr("Port Mode       PCP DEI\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        const char           *mode;
        if (info->port_list[port_no] == 0) {
            continue;
        }

        switch (port_conf->tag_remark_mode) {
        case VTSS_TAG_REMARK_MODE_CLASSIFIED:
            mode = "Classified";
            break;
        case VTSS_TAG_REMARK_MODE_DEFAULT:
            mode = "Default";
            break;
        case VTSS_TAG_REMARK_MODE_MAPPED:
            mode = "Mapped";
            break;
        default:
            mode = "?";
            break;
        }
        pr("%4u %-10s %3d %3d\n",
           port_no,
           mode,
           port_conf->tag_default_pcp,
           port_conf->tag_default_dei);
    }
    pr("\n");

    pr("QoS Port Tag Remarking Map:\n\n");
    pr("Port PCP (2*QoS class+DPL)           DEI (2*QoS class+DPL)\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        int class, dpl, pcp_ct = 0, dei_ct = 0;
        char pcp_buf[40], dei_buf[40];
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        for (class = VTSS_QUEUE_START; class < VTSS_QUEUE_END; class++) {
            for (dpl = 0; dpl < 2; dpl++) {
                const char *delim = ((class == VTSS_QUEUE_START) && (dpl == 0)) ? "" : ",";
                pcp_ct += VTSS_SNPRINTF(pcp_buf + pcp_ct, sizeof(pcp_buf) - pcp_ct, "%s%u", delim, port_conf->tag_pcp_map[class][dpl]);
                dei_ct += VTSS_SNPRINTF(dei_buf + dei_ct, sizeof(dei_buf) - dei_ct, "%s%u",  delim, port_conf->tag_dei_map[class][dpl]);
            }
        }
        pr("%4u %s %s\n", port_no, pcp_buf, dei_buf);
    }
    pr("\n");

    pr("QoS Port DSCP Remarking Config:\n\n");
    pr("Port I_Mode E_Mode T_EN\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u %6d ", port_no, port_conf->dscp_mode);
        pr("%6d %4d", port_conf->dscp_emode, port_conf->dscp_translate);
        pr("\n");
    }
    pr("\n");

#if defined(VTSS_FEATURE_QCL_DMAC_DIP) || defined(VTSS_FEATURE_QCL_KEY_TYPE)
    pr("QoS QCL Port Config:\n\n");
    pr("Port ");
#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
    pr("Address  ");
#endif
#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
    pr("KeyType ");
#endif
    pr("\n");
    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_port_conf_t *port_conf = &vtss_state->qos.port_conf[port_no];
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%4u ", port_no);
#if defined(VTSS_FEATURE_QCL_DMAC_DIP)
        pr("%s ", port_conf->dmac_dip ? "DMAC_DIP" : "SMAC_SIP");
#endif
#if defined(VTSS_FEATURE_QCL_KEY_TYPE)
        pr("%s ", vtss_vcap_key_type2txt(port_conf->key_type));
#endif
        pr("\n");
    }
    pr("\n");
#endif /* defined(VTSS_FEATURE_QCL_DMAC_DIP) || defined(VTSS_FEATURE_QCL_KEY_TYPE) */

#if defined(VTSS_FEATURE_VCAP)
    vtss_vcap_debug_print_range_checkers(vtss_state, pr, info);
#endif /* VTSS_FEATURE_VCAP */

#if defined(VTSS_FEATURE_IS1) || defined(VTSS_FEATURE_CLM)
    vtss_vcap_debug_print_is1(vtss_state, pr, info);
#endif /* VTSS_FEATURE_IS1/CLM */

#if defined(VTSS_FEATURE_QOS_TAS)
    pr("QoS Time Aware Shaper Config:\n\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_tas_port_conf_t *tas_port_conf = &vtss_state->qos.tas.port_conf[port_no];
        u32 i;
        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("Port %u:\n", port_no);
        pr("  GateEnabled      : %d\n",   tas_port_conf->gate_enabled);
        pr("  GateOpen         : 0x%x\n", bool8_to_u8(tas_port_conf->gate_open));
        pr("  CycleTime        : %u\n",   tas_port_conf->cycle_time);
        pr("  cycle_time_ext   : %u\n",   tas_port_conf->cycle_time_ext);
        pr("  BaseTime         : %" PRIu64 " sec, %u nanosec\n", ((u64)tas_port_conf->base_time.sec_msb << 32) + tas_port_conf->base_time.seconds, tas_port_conf->base_time.nanoseconds);
        pr("  ConfigChange     : %d\n",   tas_port_conf->config_change);
        pr("  MaxSDU Q7..0     : ");
        for (i = 0; i < 8; i++) {
            pr("%u ", tas_port_conf->max_sdu[7 - i]);
        }
        pr("\n");
        pr("  GCL              : ");
        for (i = 0; i < MIN(tas_port_conf->gcl_length, VTSS_QOS_TAS_GCL_LEN_MAX); i++) {
            pr("%s, 0x%x, %u ", debug_gate_operation_string(tas_port_conf->gcl[i].gate_operation), bool8_to_u8(tas_port_conf->gcl[i].gate_open), tas_port_conf->gcl[i].time_interval);
        }
        if (!i) {
            pr("(empty)");
        }
        pr("\n");
    }
    pr("\n");
#endif /* VTSS_FEATURE_QOS_TAS */

#if defined(VTSS_FEATURE_QOS_FRAME_PREEMPTION)
    pr("QoS Frame Preemption Config/Status:\n\n");
    pr("Port  EnaTx  EnaQ[0-7]  VDisTx  VTime  AddFragSize  StatusVer  PreemptActive\n");

    for (port_no = VTSS_PORT_NO_START; port_no < vtss_state->port_count; port_no++) {
        vtss_qos_fp_port_conf_t   *conf = &vtss_state->qos.fp.port_conf[port_no];
        vtss_qos_fp_port_status_t status;
        vtss_mm_status_verify_t   v;
        int queue;

        if (info->port_list[port_no] == 0) {
            continue;
        }
        pr("%-6u%-7u", port_no, VTSS_BOOL(conf->enable_tx));
        for (queue = 0; queue < VTSS_QUEUE_ARRAY_SIZE; queue++) {
            pr("%u", conf->admin_status[queue]);
        }
        pr("   %-8u%-7u%-13u", VTSS_BOOL(conf->verify_disable_tx), conf->verify_time, conf->add_frag_size);
        if (VTSS_FUNC(qos.fp_port_status_get, port_no, &status) == VTSS_RC_OK) {
            v = status.status_verify;
            pr("%-11s%u",
               v == VTSS_MM_STATUS_VERIFY_INITIAL ? "INITIAL" :
               v == VTSS_MM_STATUS_VERIFY_IDLE ? "IDLE" :
               v == VTSS_MM_STATUS_VERIFY_SEND ? "SEND" :
               v == VTSS_MM_STATUS_VERIFY_WAIT ? "WAIT" :
               v == VTSS_MM_STATUS_VERIFY_SUCCEEDED ? "SUCCEEDED" :
               v == VTSS_MM_STATUS_VERIFY_FAILED ? "FAILED" :
               v == VTSS_MM_STATUS_VERIFY_DISABLED ? "DISABLED" : "?",
               VTSS_BOOL(status.preemption_active));
        }
        pr("\n");
    }
    pr("\n");
#endif /* VTSS_FEATURE_QOS_FRAME_PREEMPTION */
}
#endif // VTSS_OPT_DEBUG_PRINT

#endif /* VTSS_FEATURE_QOS */
