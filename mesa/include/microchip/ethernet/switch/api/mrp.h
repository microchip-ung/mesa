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
    mesa_mrp_ring_role_t ring_role;    // MRP ring role
    mesa_mrp_ring_role_t in_ring_role; // MRP Interconnect ring role
    mesa_bool_t          mra;          // MRP is MRA. The actual role is given by 'ring_role' and can be changed with mesa_mrp_ring_role_set()
    uint32_t             mra_priority; // MRA priority
    mesa_bool_t          in_rc_mode;   // Is interconnection in RC-mode (TRUE) or LC-mode (FALSE)?
    mesa_port_no_t       p_port;       // Port with Primary port role
    mesa_port_no_t       s_port;       // Port with Secondary port role
    mesa_port_no_t       i_port;       // Port with Interconnect port role
    mesa_mac_t           mac;          // MAC address used to determine whether own or other MRP_Test/MRP_InTest PDU is received
} mesa_mrp_conf_t CAP(MRP);

// Add an MRP instance with configuration.
// Resources in HW are allocated.
// The ring state is defaulted to MESA_MRP_RING_STATE_OPEN.
// All the MRP frames are forwarded according to IEC 62439-2 depending on ring role.
// MRP PDUs required for protocol processing are copied to CPU.
// Test and ITest Loss Of Continuity is calculated according to IEC 62439-2.
//
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// conf     [IN] Configuration parameters for MRP.
mesa_rc mesa_mrp_add(const mesa_inst_t     inst,
                     const mesa_mrp_idx_t  mrp_idx,
                     const mesa_mrp_conf_t *const conf)  CAP(MRP);

mesa_rc mesa_mrp_get(const mesa_inst_t    inst,
                     const mesa_mrp_idx_t mrp_idx,
                     mesa_mrp_conf_t      *const conf)  CAP(MRP);

// Delete an MRP instance.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the deleted MRP instance.
mesa_rc mesa_mrp_del(const mesa_inst_t    inst,
                     const mesa_mrp_idx_t mrp_idx)  CAP(MRP);

// Set an MRP instance ring role. Requires MRP instance is configured as MRA.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// role     [IN] The MRP ring role.
mesa_rc mesa_mrp_ring_role_set(const mesa_inst_t          inst,
                               const mesa_mrp_idx_t       mrp_idx,
                               const mesa_mrp_ring_role_t role)  CAP(MRP);

mesa_rc mesa_mrp_ring_role_get(const mesa_inst_t    inst,
                               const mesa_mrp_idx_t mrp_idx,
                               mesa_mrp_ring_role_t *const role)  CAP(MRP);

// Set the port number of the primary port. This is used to swap the port roles
// of the two ring ports.
// After swapping ports, mesa_mrp_port_state_set() must be called with updated
// port state.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// port_no  [IN] The new primary port. Must be one of the already configured ports.
mesa_rc mesa_mrp_primary_port_set(const mesa_inst_t    inst,
                                  const mesa_mrp_idx_t mrp_idx,
                                  const mesa_port_no_t port_no)  CAP(MRP);

mesa_rc mesa_mrp_primary_port_get(const mesa_inst_t    inst,
                                  const mesa_mrp_idx_t mrp_idx,
                                  mesa_port_no_t       *const port_no) CAP(MRP);

// MRP ring state.
typedef enum {
    MESA_MRP_RING_STATE_CLOSED,
    MESA_MRP_RING_STATE_OPEN
} mesa_mrp_ring_state_t  CAP(MRP);

// Set an MRP instance ring state. This is the ring state inserted in the transmitted TST frames
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// state    [IN] The ring state.
mesa_rc mesa_mrp_ring_state_set(const mesa_inst_t           inst,
                                const mesa_mrp_idx_t        mrp_idx,
                                const mesa_mrp_ring_state_t state)  CAP(MRP);

mesa_rc mesa_mrp_ring_state_get(const mesa_inst_t     inst,
                                const mesa_mrp_idx_t  mrp_idx,
                                mesa_mrp_ring_state_t *const state)  CAP(MRP);

// Set an MRP instance Interconnected ring state. This is the ring state inserted in the transmitted INTST frames
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// state    [IN] The ring state.
mesa_rc mesa_mrp_in_ring_state_set(const mesa_inst_t           inst,
                                   const mesa_mrp_idx_t        mrp_idx,
                                   const mesa_mrp_ring_state_t state)  CAP(MRP);

mesa_rc mesa_mrp_in_ring_state_get(const mesa_inst_t     inst,
                                   const mesa_mrp_idx_t  mrp_idx,
                                   mesa_mrp_ring_state_t *const state)  CAP(MRP);

// MRP instance best MRM information.
typedef struct {
    mesa_mac_t  mac;  // Best MAC address
    uint32_t    prio; // Best priority
} mesa_mrp_best_mrm_t CAP(MRP);

// Set an MRP instance's best received priority and MAC.
// This information can be received by MRP_TestMgrNAck or MRP_TestPropagate.
// It is used to check for TST reception from current best MRM.
// Can only be called if configured as an MRA.
//
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// best     [IN] Best parameters for MRP.
mesa_rc mesa_mrp_best_mrm_set(const mesa_inst_t         inst,
                              const mesa_mrp_idx_t      mrp_idx,
                              const mesa_mrp_best_mrm_t *const best)  CAP(MRP);

mesa_rc mesa_mrp_best_mrm_get(const mesa_inst_t    inst,
                              const mesa_mrp_idx_t mrp_idx,
                              mesa_mrp_best_mrm_t  *const best)  CAP(MRP);

// MRP port state.
typedef enum {
    MESA_MRP_PORT_STATE_DISABLED,
    MESA_MRP_PORT_STATE_BLOCKED,
    MESA_MRP_PORT_STATE_FORWARDING
} mesa_mrp_port_state_t  CAP(MRP);

// Set an MRP instance ring port state.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// port     [IN] The port.
// state    [IN] The port state.
mesa_rc mesa_mrp_port_state_set(const mesa_inst_t           inst,
                                const mesa_mrp_idx_t        mrp_idx,
                                const mesa_port_no_t        port,
                                const mesa_mrp_port_state_t state)  CAP(MRP);

mesa_rc mesa_mrp_port_state_get(const mesa_inst_t     inst,
                                const mesa_mrp_idx_t  mrp_idx,
                                const mesa_port_no_t  port,
                                mesa_mrp_port_state_t *const state)  CAP(MRP);

// MRP TST LOC configuration.
typedef struct {
    uint32_t  tst_interval;    // The expected TST frame reception interval in microseconds
    uint32_t  tst_mon_count;   // The TST monitoring count of intervals without TST generating TST LOC

    uint32_t  itst_interval;   // The expected ITST frame reception interval in microseconds
    uint32_t  itst_mon_count;  // The ITST monitoring count of intervals without ITST generating ITST LOC
} mesa_mrp_tst_loc_conf_t CAP(MRP);

// Set an MRP instance TST LOC configuration.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// conf     [IN] The TST LOC configuration.
mesa_rc mesa_mrp_tst_loc_conf_set(const mesa_inst_t             inst,
                                  const mesa_mrp_idx_t          mrp_idx,
                                  const mesa_mrp_tst_loc_conf_t *const conf)  CAP(MRP);

mesa_rc mesa_mrp_tst_loc_conf_get(const mesa_inst_t       inst,
                                  const mesa_mrp_idx_t    mrp_idx,
                                  mesa_mrp_tst_loc_conf_t *const conf)  CAP(MRP);

// This function causes the next MRP_Test PDU that causes the LoC miss counter
// to be cleared to be copied to the CPU.
// This is needed after a LoC interrupt, to indicate to the application software
// that valid MRP_Test PDUs are arriving again.
// This only works for MIM-RC instances.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
mesa_rc mesa_mrp_tst_hitme_once(const mesa_inst_t    inst,
                                const mesa_mrp_idx_t mrp_idx);

// This function causes the next MRP_InTest PDU that causes the LoC miss counter
// to be cleared to be copied to the CPU.
// This is needed after a LoC interrupt, to indicate to the application software
// that valid MRP_InTest PDUs are arriving again.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
mesa_rc mesa_mrp_itst_hitme_once(const mesa_inst_t   inst,
                                 const mesa_mrp_idx_t mrp_idx);

// Copy of remote MRP_Test/MRP_InTest PDUs to the CPU.
typedef struct {
    mesa_bool_t tst_to_cpu;  // Copy MRP_Test PDUs from remote MRM to CPU if we are currently MRM.
    mesa_bool_t itst_to_cpu; // Copy MRP_InTest PDUs from remote MIM to CPU if we are MIM-RC.
} mesa_mrp_tst_copy_conf_t;

// Configure copying of MRP_Test and MRP_InTest PDUs from remote MRMs and/or
// MIMs to the CPU.
// This is usually needed if the application wishes to detect multiple MRMs/MIMs
// on the (interconnection) ring if it's currently operating as an MRM/MIM
// itself. In order not to be overwhelmed with remote MRP_[In]Test PDUs this can
// be turned on and off periodically. It does not affect H/W-based forwarding in
// any way.
// It only takes effect if operating as an MRM/MIM.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// copy     [IN] The copy configuration.
mesa_rc mesa_mrp_tst_copy_conf_set(const mesa_inst_t              inst,
                                   const mesa_mrp_idx_t           mrp_idx,
                                   const mesa_mrp_tst_copy_conf_t *const copy);

mesa_rc mesa_mrp_tst_copy_conf_get(const mesa_inst_t        inst,
                                   const mesa_mrp_idx_t     mrp_idx,
                                   mesa_mrp_tst_copy_conf_t *const copy);
// MRP status.
// xxx_seen are indications cleared during _get() call
typedef struct {
    mesa_bool_t  tst_loc;       // The TST LOC state.
    mesa_bool_t  itst_loc;      // The ITST LOC state.

    mesa_bool_t  mrp_seen;      // MRP frame received
    mesa_bool_t  mrp_proc_seen; // MRP frame received and processed
    mesa_bool_t  dmac_err_seen; // MRP frame received with DMAC error
    mesa_bool_t  vers_err_seen; // MRP frame received with version error
} mesa_mrp_port_status_t CAP(MRP);

typedef struct {
    mesa_mrp_port_status_t p_status;
    mesa_mrp_port_status_t s_status;
    mesa_mrp_port_status_t i_status;
} mesa_mrp_status_t CAP(MRP);

// Get an MRP instance status.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// status   [IN] The MRP status.
mesa_rc mesa_mrp_status_get(const mesa_inst_t    inst,
                            const mesa_mrp_idx_t mrp_idx,
                            mesa_mrp_status_t    *const status)  CAP(MRP);

// MRP counters.
typedef struct {
    uint64_t tst_rx_count; // Number of received valid MRP_Test frames subject to MRP_Test processing.
    uint64_t itst_rx_count;// Number of received valid MRP_InTest frames subject to MRP_InTest processing.
} mesa_mrp_port_counters_t;

typedef struct {
    mesa_mrp_port_counters_t p_counters;
    mesa_mrp_port_counters_t s_counters;
    mesa_mrp_port_counters_t i_counters;
} mesa_mrp_counters_t;

// Get an MRP instance counters.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
// counters [IN] The MRP counters.
mesa_rc mesa_mrp_counters_get(const mesa_inst_t    inst,
                              const mesa_mrp_idx_t mrp_idx,
                              mesa_mrp_counters_t  *const counters);

// Clear the MRP instance status counters.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRP instance.
mesa_rc mesa_mrp_counters_clear(const mesa_inst_t    inst,
                                const mesa_mrp_idx_t mrp_idx)  CAP(MRP);

// MRP Event indication flags.
// Different events can be enabled/disabled and polled.
// The events are represented by a bit in an event mask.
// MESA_CAP(MESA_CAP_MRP_EVENT_SUPPORTED) will return an event mask with the
// events supported on a given platform.
#define MESA_MRP_EVENT_MASK_NONE      0x00
// Change in TST frame Loss of Continuity (LOC) state
#define MESA_MRP_EVENT_MASK_TST_LOC   0x01
// Change in ITST frame Loss of Continuity (LOC) state
#define MESA_MRP_EVENT_MASK_ITST_LOC  0x02
#define MESA_MRP_EVENT_MASK_ALL       0x0F

// MRP event generation enable/disable.
// inst     [IN] Target instance reference.
// mrp_idx  [IN] Index of the configured MRPE instance.
// mask     [IN] Mask of events to either enable or disable.
// enable   [IN] Whether to enable or disable the events specified in the mask.
mesa_rc mesa_mrp_event_mask_set(const mesa_inst_t    inst,
                                const mesa_mrp_idx_t mrp_idx,
                                const uint32_t       mask,
                                const mesa_bool_t    enable)  CAP(MRP);

mesa_rc mesa_mrp_event_mask_get(const mesa_inst_t    inst,
                                const mesa_mrp_idx_t mrp_idx,
                                uint32_t             *const mask)  CAP(MRP);

// MRP events
typedef struct {
    uint32_t p_mask;
    uint32_t s_mask;
    uint32_t i_mask;
} mesa_mrp_event_t;

// MRP event polling.
// Mask is returned indicating pending events. Pending event are cleared after
// get.
// Notice that both LoC and clear of a LoC condition (through reception of
// MRP_Test/MRP_InTest PDUs) cause events.
// inst      [IN]  Target instance reference.
// mrp_idx   [IN]  Index of polled MRPE instance.
// mask      [OUT] Mask of detected pending events during get.
mesa_rc mesa_mrp_event_get(const mesa_inst_t     inst,
                           const mesa_mrp_idx_t  mrp_idx,
                           mesa_mrp_event_t      *const events)  CAP(MRP);
#include <microchip/ethernet/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_MRP_

