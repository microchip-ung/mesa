// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _MSCC_ETHERNET_SWITCH_API_MRP_
#define _MSCC_ETHERNET_SWITCH_API_MRP_

#include <microchip/ethernet/switch/api/types.h>
#include <microchip/ethernet/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

// MRP ring role.
typedef enum {
    MESA_MRP_RING_ROLE_DISABLED,
    MESA_MRP_RING_ROLE_CLIENT,
    MESA_MRP_RING_ROLE_MANAGER,
} mesa_mrp_ring_role_t  CAP(MRP);

// MRP instance create configuration.
typedef struct {
    mesa_mrp_ring_role_t  ring_role;    // MRP ring role
    mesa_mrp_ring_role_t  in_ring_role; // MRP Interconnect ring role
    mesa_bool_t           mra;          // MRP is MRA. The actual roles is given by 'role' and mesa_mrp_ring_role_set()
    uint32_t              mra_priority; // MRA priority
    mesa_port_no_t        p_port;       // Port with Primary port role
    mesa_port_no_t        s_port;       // Port with Secondary port role
    mesa_port_no_t        i_port;       // Port with Interconnect port role
    mesa_mac_t            p_mac;        // Primary port MAC address used to determine own or other Test PDU received*/
    mesa_mac_t            s_mac;        // Secondary port MAC address used to determine own or other Test PDU received */
    mesa_mac_t            i_mac;        // Interconnect port MAC address used to determine own or other Test PDU received */
} mesa_mrp_conf_t CAP(MRP);

// Add a MRP instance with configuration.
// Resources in HW are allocated.
// The ring state is defaulted to MESA_MRP_RING_STATE_OPEN.
// All the MRP frames are forwarded according to IEC 62439-2 depending on ring role.
// MRP PDUs required for protocol processing are copied to CPU.
// Test and ITest Loss Of Continuity is calculated according to IEC 62439-2.
//
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// conf     [IN] Configuration parameters for MRP.
mesa_rc mesa_mrp_add(const mesa_inst_t      inst,
                     const mesa_mrp_idx_t   mrp_idx,
                     const mesa_mrp_conf_t  *const conf)  CAP(MRP);

mesa_rc mesa_mrp_get(const mesa_inst_t      inst,
                     const mesa_mrp_idx_t   mrp_idx,
                     mesa_mrp_conf_t        *const conf)  CAP(MRP);

// Delete a MRP instance.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the deleted MRP instance.
mesa_rc mesa_mrp_del(const mesa_inst_t      inst,
                     const mesa_mrp_idx_t   mrp_idx)  CAP(MRP);

// Set a MRP instance ring role.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// role     [IN] The MRP ring role.
mesa_rc mesa_mrp_ring_role_set(const mesa_inst_t           inst,
                               const mesa_mrp_idx_t        mrp_idx,
                               const mesa_mrp_ring_role_t  role)  CAP(MRP);

mesa_rc mesa_mrp_ring_role_get(const mesa_inst_t     inst,
                               const mesa_mrp_idx_t  mrp_idx,
                               mesa_mrp_ring_role_t  *const role)  CAP(MRP);

// Set a MRP instance Interconnected ring role.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// role     [IN] The MRP ring role.
mesa_rc mesa_mrp_in_ring_role_set(const mesa_inst_t           inst,
                                  const mesa_mrp_idx_t        mrp_idx,
                                  const mesa_mrp_ring_role_t  role)  CAP(MRP);

mesa_rc mesa_mrp_in_ring_role_get(const mesa_inst_t     inst,
                                  const mesa_mrp_idx_t  mrp_idx,
                                  mesa_mrp_ring_role_t  *const role)  CAP(MRP);

// MRP ports
typedef struct {
    mesa_port_no_t   p_port;       // Port with Primary port role
    mesa_port_no_t   s_port;       // Port with Secondary port role
} mesa_mrp_ports_t  CAP(MRP);

// Set a MRP instance ring port numbers.
// The Primary and Secondary ring port numbers can only be swapped.
// After swapping ports mesa_mrp_port_state_set() must be called with updated port state.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// ports     [IN] The ports.
mesa_rc mesa_mrp_ports_set(const mesa_inst_t       inst,
                           const mesa_mrp_idx_t    mrp_idx,
                           const mesa_mrp_ports_t  *const ports)  CAP(MRP);

mesa_rc mesa_mrp_ports_get(const mesa_inst_t       inst,
                           const mesa_mrp_idx_t    mrp_idx,
                           mesa_mrp_ports_t        *const ports)  CAP(MRP);

// MRP ring state.
typedef enum {
    MESA_MRP_RING_STATE_CLOSED,
    MESA_MRP_RING_STATE_OPEN
} mesa_mrp_ring_state_t  CAP(MRP);

// Set a MRP instance ring state. This is the ring state inserted in the transmitted TST frames
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// state    [IN] The ring state.
mesa_rc mesa_mrp_ring_state_set(const mesa_inst_t            inst,
                                const mesa_mrp_idx_t         mrp_idx,
                                const mesa_mrp_ring_state_t  state)  CAP(MRP);

mesa_rc mesa_mrp_ring_state_get(const mesa_inst_t      inst,
                                const mesa_mrp_idx_t   mrp_idx,
                                mesa_mrp_ring_state_t  *const state)  CAP(MRP);

// Set a MRP instance Interconnected ring state. This is the ring state inserted in the transmitted INTST frames
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// state    [IN] The ring state.
mesa_rc mesa_mrp_in_ring_state_set(const mesa_inst_t            inst,
                                   const mesa_mrp_idx_t         mrp_idx,
                                   const mesa_mrp_ring_state_t  state)  CAP(MRP);

mesa_rc mesa_mrp_in_ring_state_get(const mesa_inst_t      inst,
                                   const mesa_mrp_idx_t   mrp_idx,
                                   mesa_mrp_ring_state_t  *const state)  CAP(MRP);

// MRP instance best information.
typedef struct {
    mesa_mac_t  mac;       // Best MAC address */
} mesa_mrp_best_t CAP(MRP);

// Set a MRP instance best received priority and MAC.
// This information can be received by MRP_TestMgrNAck or MRP_TestPropagate.
// It is used to check for TST reception from currently best MRM.
//
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// best     [IN] Best parameters for MRP.
mesa_rc mesa_mrp_best_set(const mesa_inst_t      inst,
                          const mesa_mrp_idx_t   mrp_idx,
                          const mesa_mrp_best_t  *const best)  CAP(MRP);

mesa_rc mesa_mrp_best_get(const mesa_inst_t      inst,
                          const mesa_mrp_idx_t   mrp_idx,
                          mesa_mrp_best_t        *const best)  CAP(MRP);

// MRP port state.
typedef enum {
    MESA_MRP_PORT_STATE_DISABLED,
    MESA_MRP_PORT_STATE_BLOCKED,
    MESA_MRP_PORT_STATE_FORWARDING
} mesa_mrp_port_state_t  CAP(MRP);

// Set a MRP instance ring port state.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// port     [IN] The port.
// state    [IN] The port state.
mesa_rc mesa_mrp_port_state_set(const mesa_inst_t            inst,
                                const mesa_mrp_idx_t         mrp_idx,
                                const mesa_port_no_t         port,
                                const mesa_mrp_port_state_t  state)  CAP(MRP);

mesa_rc mesa_mrp_port_state_get(const mesa_inst_t      inst,
                                const mesa_mrp_idx_t   mrp_idx,
                                const mesa_port_no_t   port,
                                mesa_mrp_port_state_t  *const state)  CAP(MRP);

// MRP TST LOC configuration.
typedef struct {
    uint32_t  tst_interval;    // The expected TST frame reception interval in microseconds
    uint32_t  tst_mon_count;   // The TST monitoring count of intervals without TST generating TST LOC

    uint32_t  itst_interval;   // The expected ITST frame reception interval in microseconds
    uint32_t  itst_mon_count;  // The ITST monitoring count of intervals without ITST generating ITST LOC
} mesa_mrp_tst_loc_t CAP(MRP);

// Set a MRP instance TST LOC configuration.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// conf     [IN] The TST LOC configuration.
mesa_rc mesa_mrp_tst_loc_set(const mesa_inst_t         inst,
                             const mesa_mrp_idx_t      mrp_idx,
                             const mesa_mrp_tst_loc_t  *const conf)  CAP(MRP);

mesa_rc mesa_mrp_tst_loc_get(const mesa_inst_t     inst,
                             const mesa_mrp_idx_t  mrp_idx,
                             mesa_mrp_tst_loc_t    *const conf)  CAP(MRP);

// MRP TST copy configuration.
typedef struct {
    mesa_bool_t  tst_low_prio;    // Copy TST with lower MRA priority to CPU
    mesa_bool_t  tst_clear_loc;   // Copy next Test that clear TST LOC to CPU

    mesa_bool_t  itst_clear_loc;  // Copy next InTest that clear ITST LOC to CPU
} mesa_mrp_copy_tst_t CAP(MRP);

// Set a MRP instance TST copy to CPU configuration.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// copy     [IN] The TST copy configuration.
mesa_rc mesa_mrp_copy_tst_set(const mesa_inst_t          inst,
                              const mesa_mrp_idx_t       mrp_idx,
                              const mesa_mrp_copy_tst_t  *const copy)  CAP(MRP);

mesa_rc mesa_mrp_copy_tst_get(const mesa_inst_t     inst,
                              const mesa_mrp_idx_t  mrp_idx,
                              mesa_mrp_copy_tst_t   *const copy)  CAP(MRP);

// MRP status.
// xxx_seen are indications cleared during _get() call
typedef struct {
    mesa_bool_t  tst_loc;        // The TST LOC state.
    mesa_bool_t  itst_loc;       // The ITST LOC state.

    mesa_bool_t  mrp_seen;       // MRP frame received
    mesa_bool_t  mrp_proc_seen;  // MRP frame received and processed
    mesa_bool_t  dmac_err_seen;  // MRP frame received with DMAC error
    mesa_bool_t  vers_err_seen;  // MRP frame received with version error
    mesa_bool_t  seq_err_seen;   // MRP frame received with sequence error
} mesa_mrp_port_status_t CAP(MRP);

typedef struct {
    mesa_mrp_port_status_t p_status;
    mesa_mrp_port_status_t s_status;
    mesa_mrp_port_status_t i_status;
} mesa_mrp_status_t CAP(MRP);

// Get a MRP instance status.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// status   [IN] The MRP status.
mesa_rc mesa_mrp_status_get(const mesa_inst_t     inst,
                            const mesa_mrp_idx_t  mrp_idx,
                            mesa_mrp_status_t     *const status)  CAP(MRP);

// MRP counters.
typedef struct {
    uint64_t   tst_rx_count;   // Number of received valid TST frames subject to MRP_Test processing.
    uint64_t   itst_rx_count;  // Number of received valid ITST frames subject to MRP_Test processing.
} mesa_mrp_port_counters_t;

typedef struct {
    mesa_mrp_port_counters_t p_counters;
    mesa_mrp_port_counters_t s_counters;
    mesa_mrp_port_counters_t i_counters;
} mesa_mrp_counters_t;

// Get a MRP instance counters.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// counters [IN] The MRP counters.
mesa_rc mesa_mrp_counters_get(const mesa_inst_t     inst,
                              const mesa_mrp_idx_t  mrp_idx,
                              mesa_mrp_counters_t   *const counters);

// Clear the MRP instance status counters.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
mesa_rc mesa_mrp_counters_clear(const mesa_inst_t     inst,
                                const mesa_mrp_idx_t  mrp_idx)  CAP(MRP);

// MRP Event indication flags.
// Different events can be enabled/disabled and polled.
// The events are represented by a bit in an event mask.
// MESA_CAP(MESA_CAP_MRP_EVENT_SUPPORTED) will return an event mask with the
// events supported on a given platform.
#define MESA_MRP_EVENT_MASK_NONE               0x00
// Change in ITST frame Loss of Continuity (LOC) state
#define MESA_MRP_EVENT_MASK_ITST_LOC           0x01
// Change in TST frame Loss of Continuity (LOC) state
#define MESA_MRP_EVENT_MASK_TST_LOC            0x02
#define MESA_MRP_EVENT_MASK_ALL                0x0F

// MRP event generation enable/disable.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRPE instance.
// mask     [IN] Mask of events to either enable or disable.
// enable   [IN] Whether to enable or disable the events specified in the mask.
mesa_rc mesa_mrp_event_mask_set(const mesa_inst_t     inst,
                                const mesa_mrp_idx_t  mrp_idx,
                                const uint32_t        mask,
                                const mesa_bool_t     enable)  CAP(MRP);

mesa_rc mesa_mrp_event_mask_get(const mesa_inst_t     inst,
                                const mesa_mrp_idx_t  mrp_idx,
                                uint32_t              *const mask)  CAP(MRP);

// MRP events
typedef struct {
    uint32_t p_mask;
    uint32_t s_mask;
    uint32_t i_mask;
} mesa_mrp_event_t;

// MRP event polling.
// Mask is returned indicating pending events. Pending event are cleared after get.
// inst      [IN]  Target instance reference.
// mrp_idx   [IN]  Index of polled MRPE instance.
// mask      [OUT] Mask of detected pending events during get.
mesa_rc mesa_mrp_event_get(const mesa_inst_t     inst,
                           const mesa_mrp_idx_t  mrp_idx,
                           mesa_mrp_event_t      *const events)  CAP(MRP);
#include <microchip/ethernet/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_MRP_

