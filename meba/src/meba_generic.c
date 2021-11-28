// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include <vtss_phy_api.h>
#include <microchip/ethernet/board/api.h>

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

mepa_ts_event_t meba_generic_phy_ts_source_to_event(meba_inst_t inst, meba_event_t event_id)
{
    switch (event_id) {
        case MEBA_EVENT_INGR_ENGINE_ERR:
            return MEPA_TS_INGR_ENGINE_ERR;
        case MEBA_EVENT_INGR_RW_PREAM_ERR:
            return MEPA_TS_INGR_RW_PREAM_ERR;
        case MEBA_EVENT_INGR_RW_FCS_ERR:
            return MEPA_TS_INGR_RW_FCS_ERR;
        case MEBA_EVENT_EGR_ENGINE_ERR:
            return MEPA_TS_EGR_ENGINE_ERR;
        case MEBA_EVENT_EGR_RW_FCS_ERR:
            return MEPA_TS_EGR_RW_FCS_ERR;
        case MEBA_EVENT_EGR_TIMESTAMP_CAPTURED:
            return MEPA_TS_EGR_TIMESTAMP_CAPTURED;
        case MEBA_EVENT_EGR_FIFO_OVERFLOW:
            return MEPA_TS_EGR_FIFO_OVERFLOW;
        default:
            T_E(inst, "Unknown event %d", event_id);
            MEBA_ASSERT(0);
    }

    return (mepa_ts_event_t)0;
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
    mesa_rc             rc;
    mepa_ts_init_conf_t ts_init_conf;

    // poll for TS interrupt only after ts_init is done
    if ((rc = meba_phy_ts_init_conf_get(inst, port_no, &ts_init_conf)) == MESA_RC_OK) {
        mepa_ts_event_t ts_events = 0;
        if ((rc = meba_phy_ts_event_poll(inst, port_no, &ts_events)) == MESA_RC_OK) {
            int handled = 0;

            T_I(inst, "ts_events: 0x%x, port = %u", ts_events, port_no);

            if ((rc = meba_phy_ts_event_set(inst, port_no, false, ts_events)) != MESA_RC_OK) {
                T_E(inst, "meba_phy_ts_event_enable_set = %d", rc);
            }

            if (ts_events & MEPA_TS_INGR_ENGINE_ERR) {
                signal_notifier(MEBA_EVENT_INGR_ENGINE_ERR, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_INGR_RW_PREAM_ERR) {
                signal_notifier(MEBA_EVENT_INGR_RW_PREAM_ERR, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_INGR_RW_FCS_ERR) {
                signal_notifier(MEBA_EVENT_INGR_RW_FCS_ERR, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_EGR_ENGINE_ERR) {
                signal_notifier(MEBA_EVENT_EGR_ENGINE_ERR, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_EGR_RW_FCS_ERR) {
                signal_notifier(MEBA_EVENT_EGR_RW_FCS_ERR, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_EGR_TIMESTAMP_CAPTURED) {
                signal_notifier(MEBA_EVENT_EGR_TIMESTAMP_CAPTURED, port_no);
                handled++;
            }

            if (ts_events & MEPA_TS_EGR_FIFO_OVERFLOW) {
                signal_notifier(MEBA_EVENT_EGR_FIFO_OVERFLOW, port_no);
                handled++;
            }

            rc = handled ? MESA_RC_OK : MESA_RC_ERROR;
        }
        T_I(inst, "ts_events: 0x%x, port = %u", ts_events, port_no);
    }

    return rc;
}

mesa_rc meba_generic_phy_event_check(meba_inst_t inst,
                                     mesa_port_no_t port_no,
                                     meba_event_signal_t signal_notifier)
{
    mepa_event_t events;
    mesa_rc      rc;

    if ((rc = meba_phy_event_poll(inst, port_no, &events)) != MESA_RC_OK) {
        T_E(inst, "meba_phy_event_poll = %d", rc);
    } else {
        int handled = 0;
        if (events) {
            T_I(inst, "Port %u, event: 0x%x", port_no, events);

            if ((rc = meba_phy_event_enable_set(inst, port_no, events, false)) != MESA_RC_OK) {
                T_E(inst, "meba_phy_event_enable_set = %d", rc);
            }

            if (events & VTSS_PHY_LINK_FFAIL_EV) {
                signal_notifier(MEBA_EVENT_FLNK, port_no);
                handled++;
            }

            if (events & VTSS_PHY_LINK_LOS_EV) {
                signal_notifier(MEBA_EVENT_LOS, port_no);
                handled++;
            }

            if (events & VTSS_PHY_LINK_AMS_EV) {
                signal_notifier(MEBA_EVENT_AMS, port_no);
                handled++;
            }
        }
        rc = handled ? MESA_RC_OK : MESA_RC_ERROR;
    }
    return rc;
}

mepa_rc meba_mmd_read(struct mepa_callout_cxt           *cxt,
                      const uint8_t                      mmd,
                      const uint16_t                     addr,
                      uint16_t                          *const value)
{
    return mesa_mmd_read(cxt->inst, cxt->chip_no, cxt->miim_controller,
                         cxt->miim_addr, mmd, addr, value);
}

mepa_rc meba_mmd_read_inc(struct mepa_callout_cxt       *cxt,
                          const uint8_t                  mmd,
                          const uint16_t                 addr,
                          uint16_t                       *const buf,
                          uint8_t                        count)
{
    return mesa_port_mmd_read_inc(cxt->inst, cxt->port_no,
                                  mmd, addr, buf, count);
}

mepa_rc meba_mmd_write(struct mepa_callout_cxt          *cxt,
                       const uint8_t                     mmd,
                       const uint16_t                    addr,
                       const uint16_t                    value)
{
    return mesa_mmd_write(cxt->inst, cxt->chip_no, cxt->miim_controller,
                          cxt->miim_addr, mmd, addr, value);
}

mepa_rc meba_miim_read(struct mepa_callout_cxt          *cxt,
                       const uint8_t                     addr,
                       uint16_t                         *const value)
{
    return mesa_miim_read(cxt->inst, cxt->chip_no, cxt->miim_controller,
                          cxt->miim_addr, addr, value);
}

mepa_rc meba_miim_write(struct mepa_callout_cxt         *cxt,
                        const uint8_t                    addr,
                        const uint16_t                   value)
{
    return mesa_miim_write(cxt->inst, cxt->chip_no, cxt->miim_controller,
                           cxt->miim_addr, addr, value);
}

void meba_phy_driver_init(meba_inst_t inst)
{
    mepa_rc             rc;
    mesa_port_no_t      port_no;
    meba_port_entry_t   entry;
    mepa_device_t       *phy_dev;

    inst->phy_device_cxt = calloc(inst->phy_device_cnt, sizeof(mepa_callout_cxt_t));
    inst->mepa_callout.mmd_read = meba_mmd_read;
    inst->mepa_callout.mmd_read_inc = meba_mmd_read_inc;
    inst->mepa_callout.mmd_write = meba_mmd_write;
    inst->mepa_callout.miim_read = meba_miim_read;
    inst->mepa_callout.miim_write = meba_miim_write;
    inst->mepa_callout.lock_enter = inst->iface.lock_enter;
    inst->mepa_callout.lock_exit = inst->iface.lock_exit;

    memset(&entry, 0, sizeof(meba_port_entry_t));
    for (port_no = 0; port_no < inst->phy_device_cnt; port_no++) {

        // Identify and initialize PHYs (no CuSFPs at this point)
        // This PHY initialization needs to take place before the
        // port interface is initialized.
        // Reason for that is that some PHYs perform calibration
        // steps during their initialization that require no
        // activity on the MAC interface as it interferes with
        // the calibration.
        inst->api.meba_port_entry_get(inst, port_no, &entry);
        meba_port_cap_t port_cap = entry.cap;

        if ((port_cap & (MEBA_PORT_CAP_COPPER | MEBA_PORT_CAP_DUAL_COPPER)) ||
            (port_cap & MEBA_PORT_CAP_VTSS_10G_PHY)) {

            mepa_board_conf_t board_conf = {};
            board_conf.numeric_handle = port_no;

            inst->phy_device_cxt[port_no].inst = 0;
            inst->phy_device_cxt[port_no].port_no = port_no;
            inst->phy_device_cxt[port_no].meba_inst = inst;
            inst->phy_device_cxt[port_no].miim_controller = entry.map.miim_controller;
            inst->phy_device_cxt[port_no].miim_addr = entry.map.miim_addr;
            inst->phy_device_cxt[port_no].chip_no = entry.map.chip_no;


            inst->phy_devices[port_no] = mepa_create(&(inst->mepa_callout),
                                                     &(inst->phy_device_cxt[port_no]),
                                                     &board_conf);

            if (inst->phy_devices[port_no]) {
                T_I(inst, "Phy has been probed on port %d", port_no);
                rc = mepa_if_set(inst->phy_devices[port_no], entry.mac_if);
                if (rc != MESA_RC_OK) {
                    T_E(inst, "Failed to set MAC interface on PHY: %d", port_no);
                }

            } else {
                T_I(inst, "Probe failed on %d", port_no);
            }
        }
    }

    // Enable accessing the shared resources by linking the base port on each port
    for (port_no = 0; port_no < inst->phy_device_cnt; port_no++) {
        inst->api.meba_port_entry_get(inst, port_no, &entry);
        phy_dev = inst->phy_devices[port_no];
        if (phy_dev && inst->phy_devices[entry.phy_base_port]) {
            (void)mepa_link_base_port(phy_dev,
                                      inst->phy_devices[entry.phy_base_port],
                                      entry.map.miim_addr % 4);
        }
    }
}
