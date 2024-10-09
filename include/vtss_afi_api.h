// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


/**
 * \file vtss_afi_api.h
 * \brief AFI API
 * \details This header file describes Automatic Frame Injector functions.
 */

#ifndef _VTSS_AFI_API_H_
#define _VTSS_AFI_API_H_

#include <vtss/api/options.h>

#if defined(VTSS_FEATURE_AFI_SWC)

#include <vtss/api/types.h>

// Define checks
#if !defined(VTSS_AFI_V1) && !defined(VTSS_AFI_V2)
#error Neither VTSS_AFI_V1 nor VTSS_AFI_V2 defined
#endif

#if defined(VTSS_AFI_V1) && defined(VTSS_AFI_V2)
#error Both VTSS_AFI_V1 and VTSS_AFI_V2 defined
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief AFI identifier. Identifies the resources allocated for a periodically injected frame.
 */
typedef u32 vtss_afi_id_t;

#define VTSS_AFI_ID_NONE (0xFFFFFFFF) /**< Use this to encode Tx headers for non-AFI frame */

#if defined(VTSS_AFI_V1)
#define VTSS_AFI_SLOT_CNT 1024 /**< Maximum number of AFI flows */

/** \page AFI Automatic Frame Injector.
 *
 * The automatic frame injector allows for periodic
 * transmission of frames from within the switch core.
 *
 * The flow for setting up a frame to be periodically
 * injected is as follows for external CPUs:\n
 *
 * 1) Allocate resources for the frame using vtss_afi_alloc().
 *    This function takes a structure in which the application
 *    must specify properties, like transmissions per seconds.\n
 *
 * 2) The vtss_afi_alloc() function returns a unique ID, which
 *    must be transferred in vtss_packet_tx_info_t::afi_id of the
 *    structure that is passed to vtss_packet_tx_hdr_encode().\n
 *
 * 3) Transmit the frame with the injection header that came
 *    out of vtss_packet_tx_hdr_encode().\n
 *
 * 4) Optionally call vtss_afi_hijack() to check that the frame indeed got
 *    all the way to the AFI H/W.
 *    Calling this function is a must if you attempt to send more traffic to a
 *    port from the AFI than the port's speed allows for.
 *
 * 5) In order to cancel the frame transmission, call vtss_afi_free()
 *    with the ID returned originally by vtss_afi_alloc().\n
 *
 * 6) If the port onto which the frame is transmitted gets a link-down event,
 *    the Vitesse API will autonomously pause frame transmission.
 *    When the link comes back up, the external CPU will have to re-transmit
 *    the frame with the ID retrieved in the original call to vtss_afi_alloc(),
 *    because internally in the API, the frame is seen as paused, not cancelled.
 */

/**
 * \brief AFI Frame description structure.
 *
 * Contains properties that describe how a frame should be
 * injected periodically.
 * Upon exit from vtss_afi_alloc() it contains additional
 * information about the injection.
 * For future compatibility, memset() this structure
 * to 0 before filling it in.
 */
typedef struct {
    /**
     * [IN]
     * Frame rate (in frames per second) at which a frame
     * should be transmitted.
     */
    u32 fps;

    /**
     * [OUT]
     * On some platforms, it may not be possible to achieve
     * the requested frame rate in one single go. A work-around
     * for this is to inject the same frame with different
     * frame rates. Typically, a particular desired frame rate
     * can be obtained by transmitting the same frame a number
     * of times.
     * vtss_afi_alloc() fills in #actual_fps with the number
     * of frames that the AFI will actually send.
     * It is guaranteed that #actual_fps <= #fps, so that
     * vtss_afi_alloc() can be called repeatedly with the
     * missing frame count.
     *
     * The API supports two different allocation methods.
     * Which one is currently active depends on
     * the value of the VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS compile-
     * time flag.
     *
     * If VTSS_OPT_AFI_OPTIMIZE_FOR_TIMERS is 0 (default/legacy), the
     * AFI code attempts to use as few frame-slots as possible
     * to achieve the desired rate. This is at the expense of
     * timers.
     * Setting VTSS_OPT_AFI_CAL_TYPE to 1 causes the AFI code
     * to optimize for timers rather than frame-slots.
     * This might be a better solution, because there are much
     * more frame-slots than timers.
     * When optimizing for timers, each timer is pre-configured
     * to provide a fixed number of frames per second. In this mode
     * the application may have to call into the vtss_afi_alloc()
     * function more times than had it been in the "optimize-for-
     * frame-slots" mode.
     */
    u32 actual_fps;

} vtss_afi_frm_dscr_t;

#define VTSS_AFI_FPS_MAX (3800000)    /**< Maximum number of frames per second we support (corresponds to wirespeed 2.5Gbps 64 byte frames) */

/**
 * \brief Allocate resources for an AFI frame.
 *
 * This function allocates resources required for a frame subject to
 * automatic frame injection.
 *
 * The function returns an ID that can be used in subsequent calls to
 * vtss_packet_tx_hdr_encode() and vtss_afi_free(). The ID is only valid
 * for one single frame.
 *
 * \param inst [IN]    Target instance reference.
 * \param dscr [INOUT] Pointer to structure describing how the frame should be injected.
 * \param id   [OUT]   Pointer receiving a unique ID that identifies the allocated resources for this frame.
 *
 * \return VTSS_RC_OK on success. VTSS_RC_ERROR on error.
 */
vtss_rc vtss_afi_alloc(const vtss_inst_t inst, vtss_afi_frm_dscr_t *const dscr, vtss_afi_id_t *const id);

/**
 * \brief Free resources associated with an AFI frame.
 *
 * This function cancels any ongoing transmissions of the frame
 * associated with the ID passed to this function, and frees the
 * allocated resources.
 *
 * \param inst [IN] Target instance reference.
 * \param id   [IN] ID of AFI frame to cancel and free resources for.
 *
 * \return VTSS_RC_OK on success. VTSS_RC_ERROR on error.
 */
vtss_rc vtss_afi_free(const vtss_inst_t inst, vtss_afi_id_t id);

/**
 * \brief Check that the frame just transmitted to the AFI indeed gets to get
 * known by the AFI.
 *
 * After the frame is injected, make sure it gets known by H/W by calling this
 * function.
 * Especially if the already-applied AFI rate on the port this frame is supposed
 * to egress is very high (higher than the port's link rate), will there be a
 * chance that subsequent frames sent from S/W to the AFI won't make it to the
 * AFI, because all B/W from the queue system towards the port is in use by
 * the AFI itself, which has higher Tx priority than other frames from the
 * queue system.
 * You will not need to call this function if you know that the rate towards
 * a given port is lower than the link speed of that port.
 *
 * \param inst [IN] Target instance reference.
 * \param id   [IN] ID of AFI frame to cancel and free resources for.
 *
 * \return VTSS_RC_OK on success. VTSS_RC_ERROR on error.
 */
vtss_rc vtss_afi_hijack(const vtss_inst_t inst, vtss_afi_id_t id);

#endif /* defined(VTSS_AFI_V1) */

#if defined(VTSS_AFI_V2)

// Chip specific properties
#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C)
#define VTSS_AFI_SLOW_INJ_CNT     4096           /**< Maximum number of simultaneous slow injections */
#define VTSS_AFI_FAST_INJ_BPS_MIN 1000ULL        /**< Min rate in bits per second: 1kbps (including IFG and preamble) */
#define VTSS_AFI_FAST_INJ_BPS_MAX 10000000000ULL /**< Max rate in bits per second: 10Gbps (including IFG and preamble) */
#endif

#if defined(VTSS_ARCH_SPARX5) || defined(VTSS_ARCH_LAN969X)
#if defined(VTSS_ARCH_SPARX5)
#define VTSS_AFI_SLOW_INJ_CNT     4096           /**< Maximum number of simultaneous slow injections */
#else
#define VTSS_AFI_SLOW_INJ_CNT     512            /**< Maximum number of simultaneous slow injections */
#endif
#define VTSS_AFI_FAST_INJ_BPS_MIN 1000ULL        /**< Min rate in bits per second: 1kbps (including IFG and preamble) */
#define VTSS_AFI_FAST_INJ_BPS_MAX 25000000000ULL /**< Max rate in bits per second: 25Gbps (including IFG and preamble) */
#endif

#if defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_LAN966X)
#define VTSS_AFI_SLOW_INJ_CNT     2048           /**< Maximum number of simultaneous slow injections */
#define VTSS_AFI_FAST_INJ_BPS_MIN 1000ULL        /**< Min rate in bits per second: 1kbps (including IFG and preamble) */
#define VTSS_AFI_FAST_INJ_BPS_MAX 10000000000ULL /**< Max rate in bits per second: 10Gbps (including IFG and preamble) */
#endif

#define VTSS_AFI_SLOW_INJ_FPH_MAX (60 * 60 * 300) /**< Maximum number of frames per hour supported by slow injections */

/** \page Automatic Frame Injector (AFI)
 *
 * Two types of AFI injections are supported:
 * a) Fast injections
 *    Injection of a sequence of frames consisting of one or more frames with rates of up to several Gbps.
 *    IFG proportional to frame size are inserted between frames.
 *    This is known as Delay-Triggered Injections (DTI).
 * b) Slow injections
 *    Typically used for injecting single frames with an interval of ~3.3ms or slower.
 *    This is known as Timer-Triggered Injections (TTI).
 *
 * Fast injections are used as follows:
 * 1) Allocate resources identified by a 'fastid' using vtss_afi_fast_inj_alloc().
 * 2) Transmit frame with IFH.AFI_INJ = 1.
 * 3) Call vtss_afi_fast_inj_frm_hijack() to configure the frame for injection.
 *    Repeat steps 2-3 to configure a sequence of frames for injection.
 * 4) Call vtss_afi_fast_inj_start() to select bandwidth and start injection.
 * 5) Call vtss_afi_fast_inj_stop() to stop injection.
 *    vtss_afi_fast_inj_seq_cnt_get() can be called to check the remaining number
 *    of injections.
 *    Repeat 4-5 as desired.
 *    Note that fast injections, which are started with seq_cnt set to a
 *    non-zero value must also be stopped with vtss_afi_fast_inj_stop() before
 *    it can be started again.
 * 6) Call vtss_afi_fast_inj_free() to free allocated resources.
 *
 * Slow injections are used as follows:
 * 1) Allocate resources identified by a 'slowid' using vtss_afi_slow_inj_alloc().
 * 2) Transmit frame with IFH.AFI_INJ=1.
 * 3) Call vtss_afi_slow_inj_frm_hijack() to configure the frame for injection.
 * 4) Call vtss_afi_slow_inj_start() to start injection.
 * 5) Call vtss_afi_slow_inj_stop() to stop injection.
 *    Repeat 4-5 as desired.
 * 6) Call vtss_afi_slow_inj_free() to free allocated resources.
 *
 * During link down, all injections (slow as well as fast) are automatically stopped
 * and upon link up, injections are restarted.
 *
 * Maximum one frame (with AFI_INJ=1) can be setup at a time. I.e. another frame
 * must not be injected with AFI_INJ=1 until the previous such frame has been hijacked
 * using vtss_afi_slow_inj_frm_hijack() or vtss_afi_fast_inj_frm_hijack().
 */

// TOETBD - Jaguar2a:
// Note that if port is disabled when freeing (slow or fast), then AFI
// API must do the following:
// a) Disable all other injections on same port.
// b) Enable injections for port (FRM_OUT_MAX>0)
// c) Configure removals.
// d) Wait for removal injections to complete.
// e) Disable injections for port (FRM_OUT_MAX=0)
// f) Reenable the injections, which were disable in a).
//
// With PORT_TBL:PORT_CFG.FRM_RM_ONLY this can be done simpler for ServalT.

// ========================================
// Fast injections
// ----------------------------------------

/**
 * Maximum number of frames in fast injection sequence.
 * The recommended default EMIX in ITU-T Y.1564 consists of 5 frames
 * of sizes 1518, 1518, 1024, 64, 64.
 */
#define VTSS_AFI_FAST_INJ_FRM_CNT_MAX 8

#if defined(VTSS_ARCH_JAGUAR_2_B) || defined(VTSS_ARCH_JAGUAR_2_C) || defined(VTSS_ARCH_SPARX5)
#define VTSS_AFI_FAST_INJ_CNT 32 /**< Maximum number of simultaneous fast injections */
#elif defined(VTSS_ARCH_SERVAL_T) || defined(VTSS_ARCH_LAN966X) || defined(VTSS_ARCH_LAN969X)
#define VTSS_AFI_FAST_INJ_CNT 16 /**< Maximum number of simultaneous fast injections */
#else
#error "Unsupported architecture"
#endif

typedef u32 vtss_afi_fastid_t; /**< Opaque type for IDs of fast injections */

/**
 * Structure defining properties of a fast injection.
 */
typedef struct {
    /**
     * [IN]
     * Port number onto which the frame sequence shall be transmitted.
     *
     * Set to VTSS_PORT_NO_NONE to use Virtual Device #1 (VD1) (for Up-MEPs)
     * and fill in \p masquerade_port_no with masqueraded port.
     *
     * The reason that the destination port number must be conveyed
     * to the AFI in addition to conveying it in the IFH is that
     * once the AFI starts injection, it doesn't have access to the IFH.
     */
    vtss_port_no_t port_no;

    /**
     * [IN]
     * Priority on which the frame sequence shall be transmitted.
     *
     * Valid values are in the range [0; VTSS_PRIO_END] and
     * [VTSS_PRIO_SUPER; VTSS_PRIO_SUPER + 1].
     */
    vtss_prio_t prio;

    /**
     * [IN]
     * Number of frames in sequence, i.e. number of frames to be hijacked
     * using vtss_afi_fast_inj_frm_hijack().
     * Maximum is VTSS_AFI_FAST_INJ_FRM_CNT_MAX.
     */
    u32 frm_cnt;

    /**
     * [IN]
     * For up-flows, that is, when setting \p port_no to VTSS_PORT_NO_NONE,
     * convey the port number on which the flow ingresses, that is, the
     * masquerade port.
     *
     * It is not used unless \p port_no is set to VTSS_PORT_NO_NONE.
     */
    vtss_port_no_t masquerade_port_no;
} vtss_afi_fast_inj_alloc_cfg_t;

/**
 * \brief Allocate AFI fast injection resource
 *
 * \param inst   [IN]  Target instance reference.
 * \param cfg    [IN]  Injection descriptor.
 * \param fastid [OUT] ID used for referencing the allocated resource.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_alloc(const vtss_inst_t                          inst,
                                const vtss_afi_fast_inj_alloc_cfg_t *const cfg,
                                      vtss_afi_fastid_t             *const fastid);

/**
 * \brief Free AFI fast injection resource
 *
 * Before resources are freed, fast injection must be stopped.
 *
 * \param inst   [IN] Target instance reference.
 * \param fastid [IN] Fast injection ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_free(const vtss_inst_t       inst,
                                     vtss_afi_fastid_t fastid);

/**
 * Structure needed when hijacking frame.
 */
typedef struct {
    /**
     * [IN]
     * Frame size in bytes.
     * frm_size is only used for calculating bandwidth and need not match
     * the actual frame size. If IFG and preamble shall be included in the
     * bandwidth calculation, then this must be added to frm_size.
     */
    u32 frm_size;
} vtss_afi_fast_inj_frm_cfg_t;

/**
 * \brief Setup frame for fast injection.
 *
 * When a sequence of frames is configured, then the frame order
 * is the order in which frames are setup.
 *
 * \param inst   [IN] Target instance reference.
 * \param fastid [IN] Fast injection ID.
 * \param cfg    [IN] Frame setup configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_frm_hijack(const vtss_inst_t                        inst,
                                           vtss_afi_fastid_t                  fastid,
                                     const vtss_afi_fast_inj_frm_cfg_t *const cfg);

/**
 * Structure defining properties of a fast injection.
 */
typedef struct {
    /**
     * [IN]
     * Requested injection rate. Bits per second (type = Layer1/Line rate)
     * Maximum value is VTSS_AFI_FAST_INJ_BPS_MAX.
     * bps = 0 => Injection at line speed (for ports with speed <= VTSS_AFI_FAST_INJ_BPS_MAX).
     */
    u64 bps;

    /**
     * [IN]
     * Number of sequences to inject. 0 => inject until stopped.
     * Maximum value is 2^31-1
     */
    u32 seq_cnt;

    /**
     * [OUT]
     * Actual injection rate. Bits per second.
     * bps_actual is always <= bps.
     * For rates close to VTSS_AFI_FAST_INJ_BPS_MAX precision is 1%, or better.
     * For lower rates precision is better than 0.1%.
     * The actual rate will always be at or lower than the requested rate.
     * If bps is set to 0, then bps_actual is also set to 0.
     */
    u64 bps_actual;
} vtss_afi_fast_inj_start_cfg_t;

/**
 * \brief Start fast injection.
 *
 * \param inst   [IN]    Target instance reference.
 * \param fastid [IN]    Fast injection ID.
 * \param cfg    [INOUT] Fast injection configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_start(const vtss_inst_t                          inst,
                                      vtss_afi_fastid_t                    fastid,
                                      vtss_afi_fast_inj_start_cfg_t *const cfg);

/**
 * \brief Stop fast injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param fastid [IN] Fast injection ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_stop(const vtss_inst_t       inst,
                                     vtss_afi_fastid_t fastid);

/**
 * \brief Get seq_cnt for fast injection.
 *        If seq_cnt is set to 0 in vtss_afi_fast_inj_start() then the value
 *        read will be the number of frames injected.
 *        Otherwise the value read will be the remaining number of sequences
 *        to inject.
 *
 * \param inst    [IN]  Target instance reference.
 * \param fastid  [IN]  Fast injection ID.
 * \param seq_cnt [OUT] Sequence/frame count read.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_fast_inj_seq_cnt_get(const vtss_inst_t              inst,
                                            vtss_afi_fastid_t        fastid,
                                            u32               *const seq_cnt);

// ========================================
// Slow injections
// ----------------------------------------
typedef u32 vtss_afi_slowid_t; /**< Opaque type for IDs of slow injections */

/**
 * Structure defining properties of a slow injection.
 */
typedef struct {
    /**
     * [IN]
     * Port number onto which the frame shall be transmitted periodically.
     *
     * Set to VTSS_PORT_NO_NONE to use Virtual Device #1 (VD1) (for Up-MEPs)
     * and fill in \p masquerade_port_no with the masqueraded port.
     */
    vtss_port_no_t port_no;

    /**
     * [IN]
     * Priority on which the frame sequence shall be transmitted.
     *
     * Valid values are in the range [0; VTSS_PRIO_END] and
     * [VTSS_PRIO_SUPER; VTSS_PRIO_SUPER + 1].
     */
    vtss_prio_t prio;

    /**
     * [IN]
     * For up-flows, that is, when setting \p port_no to VTSS_PORT_NO_NONE,
     * convey the port number on which the flow ingresses, that is, the
     * masquerade port.
     *
     * It is not used unless \p port_no is set to VTSS_PORT_NO_NONE.
     */
    vtss_port_no_t masquerade_port_no;
} vtss_afi_slow_inj_alloc_cfg_t;

/**
 * \brief Allocate AFI slow injection resource
 *
 * \param inst   [IN]  Target instance reference.
 * \param cfg    [IN]  Injection descriptor.
 * \param slowid [OUT] ID used for referencing the allocated resource.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_slow_inj_alloc(const vtss_inst_t                          inst,
                                const vtss_afi_slow_inj_alloc_cfg_t *const cfg,
                                      vtss_afi_slowid_t             *const slowid);

/**
 * \brief Free AFI slow injection resource
 *
 * Before resources are freed, slow injection must be stopped.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_slow_inj_free(const vtss_inst_t       inst,
                                     vtss_afi_slowid_t slowid);

/**
 * \brief Setup frame for slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_slow_inj_frm_hijack(const vtss_inst_t       inst,
                                           vtss_afi_slowid_t slowid);

/**
 * Structure defining properties of a slow injection.
 */
typedef struct {
    /**
     * [IN]
     * Frames per hour.
     */
    u64 fph;

    /**
     * [IN]
     * 0: No injection time jitter.
     * 1: Injection delta time is randomized in interval [0.75*60*60/fph; 60/fph] secs
     * 2: Injection delta time is randomized in interval [0.50*60*60/fph; 60/fph] secs
     * 3: Injection delta time is randomized in interval [1 tick; 60*60/fph secs]
     *
     * E.g. to be used for PTP Delay Request, ref IEEE1588-2008, 9.5.11.2.
     */
    u8 jitter_mode;

    /**
     * [IN]
     * If FALSE, first frame is transmitted a randomized number of timer ticks
     * after call to vtss_afi_slow_inj_start() to minimize risk of bursting in
     * case many flows are started "simultaneously".
     * If TRUE, first frame must be transmitted ASAP.
     */
    BOOL first_frame_urgent;
} vtss_afi_slow_inj_start_cfg_t;

/**
 * \brief Start slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 * \param cfg    [IN] Slow injection configuration.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_slow_inj_start(const vtss_inst_t                          inst,
                                      vtss_afi_slowid_t                    slowid,
                                const vtss_afi_slow_inj_start_cfg_t *const cfg);

/**
 * \brief Stop slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_slow_inj_stop(const vtss_inst_t       inst,
                                     vtss_afi_slowid_t slowid);

// ========================================
// Other functions
// ----------------------------------------

// Stopping and starting all injections for port.
// Note that during link down, injections are automatically stopped and
// (re)started upon link up.

/**
 * \brief (Re)start all injections for specific port
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number. VTSS_PORT_NO_NONE for VD1.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_port_start(const vtss_inst_t    inst,
                                  vtss_port_no_t port_no);

/**
 * \brief Stop all injections for specific port
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number. VTSS_PORT_NO_NONE for VD1.
 *
 * \return Return code.
 **/
vtss_rc vtss_afi_port_stop(const vtss_inst_t    inst,
                                 vtss_port_no_t port_no);

#endif // VTSS_AFI_V2

#ifdef __cplusplus
}
#endif

#endif // VTSS_FEATURE_AFI_SWC
#endif // _VTSS_AFI_API_H_
