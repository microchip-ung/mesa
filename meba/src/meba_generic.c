// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <mscc/ethernet/board/api.h>

#include "meba_generic.h"

mesa_ptp_event_type_t meba_generic_ptp_source_to_event(meba_inst_t inst, meba_event_t event_id)
{
    switch (event_id) {
        case MEBA_EVENT_SYNC:
            return MESA_PTP_SYNC_EV;
        case MEBA_EVENT_EXT_SYNC:
            return MESA_PTP_EXT_SYNC_EV;
        case MEBA_EVENT_EXT_1_SYNC:
            return MESA_PTP_EXT_1_SYNC_EV;
        case MEBA_EVENT_CLK_ADJ:
            return MESA_PTP_CLK_ADJ_EV;
        case MEBA_EVENT_CLK_TSTAMP:
            return MESA_PTP_TX_TSTAMP_EV;
        case MEBA_EVENT_PTP_PIN_0:
            return MESA_PTP_PIN_0_SYNC_EV;
        case MEBA_EVENT_PTP_PIN_1:
            return MESA_PTP_PIN_1_SYNC_EV;
        case MEBA_EVENT_PTP_PIN_2:
            return MESA_PTP_PIN_2_SYNC_EV;
        case MEBA_EVENT_PTP_PIN_3:
            return MESA_PTP_PIN_3_SYNC_EV;
        default:
            T_E(inst, "Unknown event %d", event_id);
            MEBA_ASSERT(0);

    }
    return (mesa_ptp_event_type_t)0;
}

mesa_phy_ts_event_t meba_generic_phy_ts_source_to_event(meba_inst_t inst, meba_event_t event_id)
{
    switch (event_id) {
        case MEBA_EVENT_INGR_ENGINE_ERR:
            return MESA_PHY_TS_INGR_ENGINE_ERR;
        case MEBA_EVENT_INGR_RW_PREAM_ERR:
            return MESA_PHY_TS_INGR_RW_PREAM_ERR;
        case MEBA_EVENT_INGR_RW_FCS_ERR:
            return MESA_PHY_TS_INGR_RW_FCS_ERR;
        case MEBA_EVENT_EGR_ENGINE_ERR:
            return MESA_PHY_TS_EGR_ENGINE_ERR;
        case MEBA_EVENT_EGR_RW_FCS_ERR:
            return MESA_PHY_TS_EGR_RW_FCS_ERR;
        case MEBA_EVENT_EGR_TIMESTAMP_CAPTURED:
            return MESA_PHY_TS_EGR_TIMESTAMP_CAPTURED;
        case MEBA_EVENT_EGR_FIFO_OVERFLOW:
            return MESA_PHY_TS_EGR_FIFO_OVERFLOW;
        default:
            T_E(inst, "Unknown event %d", event_id);
            MEBA_ASSERT(0);
    }

    return (mesa_phy_ts_event_t)0;
}

mesa_rc meba_generic_ptp_handler(meba_inst_t inst, meba_event_signal_t signal_notifier)
{
    mesa_ptp_event_type_t ptp_events;
    mesa_rc               rc;

    if ((rc = mesa_ptp_event_poll(NULL, &ptp_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_ptp_event_poll = %d", rc);
    } else {
        int handled = 0;
        if (ptp_events) {
            if ((rc = mesa_ptp_event_enable(NULL, ptp_events, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_ptp_event_enable = %d", rc);
            }

            // Fan out
            if (ptp_events & MESA_PTP_SYNC_EV) {
                signal_notifier(MEBA_EVENT_SYNC, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_EXT_SYNC_EV) {
                signal_notifier(MEBA_EVENT_EXT_SYNC, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_CLK_ADJ_EV) {
                signal_notifier(MEBA_EVENT_CLK_ADJ, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_PIN_0_SYNC_EV) {
                signal_notifier(MEBA_EVENT_PTP_PIN_0, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_PIN_1_SYNC_EV) {
                signal_notifier(MEBA_EVENT_PTP_PIN_1, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_PIN_2_SYNC_EV) {
                signal_notifier(MEBA_EVENT_PTP_PIN_2, 0);
                handled++;
            }

            if (ptp_events & MESA_PTP_PIN_3_SYNC_EV) {
                signal_notifier(MEBA_EVENT_PTP_PIN_3, 0);
                handled++;
            }
        }
        rc = handled ? MESA_RC_OK : MESA_RC_ERROR;
    }

    return rc;
}

mesa_rc meba_generic_phy_timestamp_check(meba_inst_t inst,
                                         mesa_port_no_t port_no,
                                         meba_event_signal_t signal_notifier)
{
    mesa_rc                 rc;
    mesa_phy_ts_init_conf_t ts_init_conf;
    mesa_bool_t             port_ts_init_done = false;

    // poll for TS interrupt only after ts_init is done
    if ((rc = mesa_phy_ts_init_conf_get(PHY_INST, port_no, &port_ts_init_done, &ts_init_conf) == MESA_RC_OK) &&
        port_ts_init_done) {
        mesa_phy_ts_event_t ts_events = 0;
        if ((rc = mesa_phy_ts_event_poll(PHY_INST, port_no, &ts_events)) == MESA_RC_OK &&
            ts_events) {
            int handled = 0;

            T_I(inst, "ts_events: 0x%x, port = %u", ts_events, port_no);

            if ((rc = mesa_phy_ts_event_enable_set(PHY_INST, port_no, false, ts_events)) != MESA_RC_OK) {
                T_E(inst, "mesa_phy_ts_event_enable_set = %d", rc);
            }

            if (ts_events & MESA_PHY_TS_INGR_ENGINE_ERR) {
                signal_notifier(MEBA_EVENT_INGR_ENGINE_ERR, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_INGR_RW_PREAM_ERR) {
                signal_notifier(MEBA_EVENT_INGR_RW_PREAM_ERR, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_INGR_RW_FCS_ERR) {
                signal_notifier(MEBA_EVENT_INGR_RW_FCS_ERR, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_EGR_ENGINE_ERR) {
                signal_notifier(MEBA_EVENT_EGR_ENGINE_ERR, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_EGR_RW_FCS_ERR) {
                signal_notifier(MEBA_EVENT_EGR_RW_FCS_ERR, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_EGR_TIMESTAMP_CAPTURED) {
                signal_notifier(MEBA_EVENT_EGR_TIMESTAMP_CAPTURED, port_no);
                handled++;
            }

            if (ts_events & MESA_PHY_TS_EGR_FIFO_OVERFLOW) {
                signal_notifier(MEBA_EVENT_EGR_FIFO_OVERFLOW, port_no);
                handled++;
            }

            rc = handled ? MESA_RC_OK : MESA_RC_ERROR;
        }
    }

    return rc;
}

mesa_rc meba_generic_phy_event_check(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_event_signal_t signal_notifier)
{
    mesa_phy_event_t phy_events;
    mesa_rc          rc;

    if ((rc = mesa_phy_event_poll(PHY_INST, port_no, &phy_events)) != MESA_RC_OK) {
        T_E(inst, "mesa_phy_event_poll = %d", rc);
    } else {
        int handled = 0;
        if (phy_events) {

            T_I(inst, "Port %u, PHY event: 0x%x", port_no, phy_events);

            if ((rc = mesa_phy_event_enable_set(PHY_INST, port_no, phy_events, false)) != MESA_RC_OK) {
                T_E(inst, "mesa_phy_event_enable_set = %d", rc);
            }

            if (phy_events & MESA_PHY_LINK_FFAIL_EV) {
                signal_notifier(MEBA_EVENT_FLNK, port_no);
                handled++;
            }

            if (phy_events & MESA_PHY_LINK_LOS_EV) {
                signal_notifier(MEBA_EVENT_LOS, port_no);
                handled++;
            }

            if (phy_events & MESA_PHY_LINK_AMS_EV) {
                signal_notifier(MEBA_EVENT_AMS, port_no);
                handled++;
            }
        }
        rc = handled ? MESA_RC_OK : MESA_RC_ERROR;
    }

    return rc;
}
