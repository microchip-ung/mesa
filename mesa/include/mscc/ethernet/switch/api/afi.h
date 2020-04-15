/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#ifndef _MSCC_ETHERNET_SWITCH_API_AFI_
#define _MSCC_ETHERNET_SWITCH_API_AFI_

#include <mscc/ethernet/switch/api/types.h>
#include <mscc/ethernet/switch/api/capability.h>
#include <mscc/ethernet/switch/api/hdr_start.h>  // ALL INCLUDE ABOVE THIS LINE

/**
 * \brief AFI identifier. Identifies the resources allocated for a periodically injected frame.
 */
typedef uint32_t mesa_afi_id_t;

#define MESA_AFI_ID_NONE (0xFFFFFFFF) /**< Use this to encode Tx headers for non-AFI frame */

/**
 * \brief AFI Frame description structure.
 *
 * Contains properties that describe how a frame should be
 * injected periodically.
 * For future compatibility, memset() this structure
 * to 0 before filling it in.
 */
typedef struct {
    /**
     * Frame rate (in frames per second) at which a frame
     * should be transmitted.
     */
    uint32_t fps;
} mesa_afi_frm_dscr_t CAP(AFI_V1);

/**
 * \brief AFI Frame description structure.
 *
 * Contains properties that describe how a frame should be
 * injected periodically.
 * For future compatibility, memset() this structure
 * to 0 before filling it in.
 */
typedef struct {
    /**
     * On some platforms, it may not be possible to achieve
     * the requested frame rate in one single go. A work-around
     * for this is to inject the same frame with different
     * frame rates. Typically, a particular desired frame rate
     * can be obtained by transmitting the same frame a number
     * of times.
     * mesa_afi_alloc() fills in #actual_fps with the number
     * of frames that the AFI will actually send.
     * It is guaranteed that #actual_fps <= #fps, so that
     * mesa_afi_alloc() can be called repeatedly with the
     * missing frame count.
     *
     * The API supports two different allocation methods.
     * Which one is currently active depends on
     * the value of the MESA_OPT_AFI_OPTIMIZE_FOR_TIMERS compile-
     * time flag.
     *
     * If MESA_OPT_AFI_OPTIMIZE_FOR_TIMERS is 0 (default/legacy), the
     * AFI code attempts to use as few frame-slots as possible
     * to achieve the desired rate. This is at the expense of
     * timers.
     * Setting MESA_OPT_AFI_CAL_TYPE to 1 causes the AFI code
     * to optimize for timers rather than frame-slots.
     * This might be a better solution, because there are much
     * more frame-slots than timers.
     * When optimizing for timers, each timer is pre-configured
     * to provide a fixed number of frames per second. In this mode
     * the application may have to call into the mesa_afi_alloc()
     * function more times than had it been in the "optimize-for-
     * frame-slots" mode.
     */
    uint32_t fps;

} mesa_afi_frm_dscr_actual_t CAP(AFI_V1);

/**
 * \brief Allocate resources for an AFI frame.
 *
 * This function allocates resources required for a frame subject to
 * automatic frame injection.
 *
 * The function returns an ID that can be used in subsequent calls to
 * mesa_packet_tx_hdr_encode() and mesa_afi_free(). The ID is only valid
 * for one single frame.
 *
 * \param inst   [IN]    Target instance reference.
 * \param dscr   [IN]    Pointer to structure describing how the frame should be injected.
 * \param actual [OUT]   Pointer to structure describing how the actual frame rate.
 * \param id     [OUT]   Pointer receiving a unique ID that identifies the allocated resources for this frame.
 *
 * \return MESA_RC_OK on success. MESA_RC_ERROR on error.
 */
mesa_rc mesa_afi_alloc(const mesa_inst_t          inst,
                       const mesa_afi_frm_dscr_t  *const dscr,
                       mesa_afi_frm_dscr_actual_t *const actual,
                       mesa_afi_id_t              *const id)
    CAP(AFI_V1);

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
 * \return MESA_RC_OK on success. MESA_RC_ERROR on error.
 */
mesa_rc mesa_afi_free(const mesa_inst_t inst,
                      mesa_afi_id_t     id)
    CAP(AFI_V1);

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
 * \return MESA_RC_OK on success. MESA_RC_ERROR on error.
 */
mesa_rc mesa_afi_hijack(const mesa_inst_t inst, mesa_afi_id_t id) CAP(AFI_V1);

// ========================================
// Fast injections
// ----------------------------------------

typedef uint32_t mesa_afi_fastid_t CAP(AFI_V2); /**< Opaque type for IDs of fast injections */

/**
 * Structure defining properties of a fast injection.
 */
typedef struct {
    /**
     * [IN]
     * Port number onto which the frame sequence shall be transmitted.
     *
     * Set to MESA_PORT_NO_NONE to use Virtual Device #1 (VD1) (for Up-MEPs)
     * and fill in \p masquerade_port_no with the masqueraded port.
     *
     * The reason that the destination port number must be conveyed
     * to the AFI in addition to conveying it in the IFH is that
     * once the AFI starts injection, it doesn't have access to the IFH.
     */
    mesa_port_no_t port_no;

    /**
     * [IN]
     * Priority on which the frame sequence shall be transmitted.
     *
     * Valid values are in the range [0; MESA_PRIO_END] and
     * [MESA_PRIO_SUPER; MESA_PRIO_SUPER + 1].
     */
    mesa_prio_t prio;

    /**
     * [IN]
     * Number of frames in sequence, i.e. number of frames to be hijacked
     * using mesa_afi_fast_inj_frm_hijack().
     * Maximum is MESA_AFI_FAST_INJ_FRM_CNT_MAX.
     */
    uint32_t frm_cnt;

    /**
     * [IN]
     * For up-flows, that is, when setting \p port_no to MESA_PORT_NO_NONE,
     * convey the port number on which the flow ingresses, that is, the
     * masquerade port.
     *
     * It is not used unless \p port_no is set to MESA_PORT_NO_NONE.
     */
    mesa_port_no_t masquerade_port_no;
} mesa_afi_fast_inj_alloc_cfg_t CAP(AFI_V2);

/**
 * \brief Allocate AFI fast injection resource
 *
 * \param inst   [IN]  Target instance reference.
 * \param cfg    [IN]  Injection descriptor.
 * \param fastid [OUT] ID used for referencing the allocated resource.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_fast_inj_alloc(const mesa_inst_t                          inst,
                                const mesa_afi_fast_inj_alloc_cfg_t *const cfg,
                                      mesa_afi_fastid_t             *const fastid)
    CAP(AFI_V2);

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
mesa_rc mesa_afi_fast_inj_free(const mesa_inst_t       inst,
                                     mesa_afi_fastid_t fastid)
    CAP(AFI_V2);

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
    uint32_t frm_size;
} mesa_afi_fast_inj_frm_cfg_t CAP(AFI_V2);

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
mesa_rc mesa_afi_fast_inj_frm_hijack(const mesa_inst_t                        inst,
                                           mesa_afi_fastid_t                  fastid,
                                     const mesa_afi_fast_inj_frm_cfg_t *const cfg)
    CAP(AFI_V2);

/**
 * Structure defining properties of a fast injection.
 */
typedef struct {
    /**
     * Requested injection rate. Bits per second (type = Layer1/Line rate)
     * Maximum value is MESA_AFI_FAST_INJ_BPS_MAX.
     * bps = 0 => Injection at line speed (for ports with speed <= MESA_AFI_FAST_INJ_BPS_MAX).
     */
    uint64_t bps;

    /**
     * Number of sequences to inject. 0 => inject until stopped.
     * Maximum value is 2^31-1
     */
    uint32_t seq_cnt;
} mesa_afi_fast_inj_start_cfg_t CAP(AFI_V2);

/**
 * Structure defining properties of a fast injection.
 */
typedef struct {
    /**
     * Actual injection rate. Bits per second.
     * bps_actual is always <= bps.
     * For rates close to MESA_AFI_FAST_INJ_BPS_MAX precision is 1%, or better.
     * For lower rates precision is better than 0.1%.
     * The actual rate will always be at or lower than the requested rate.
     * If bps is set to 0, then bps_actual is also set to 0.
     */
    uint64_t bps;
} mesa_afi_fast_inj_start_actual_t CAP(AFI_V2);

/**
 * \brief Start fast injection.
 *
 * \param inst   [IN]  Target instance reference.
 * \param fastid [IN]  Fast injection ID.
 * \param cfg    [IN]  Fast injection configuration.
 * \param actual [OUT] Actual fast injection rate.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_fast_inj_start(const mesa_inst_t                   inst,
                                const mesa_afi_fastid_t             fastid,
                                const mesa_afi_fast_inj_start_cfg_t *const cfg,
                                mesa_afi_fast_inj_start_actual_t    *const actual)
    CAP(AFI_V2);

/**
 * \brief Stop fast injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param fastid [IN] Fast injection ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_fast_inj_stop(const mesa_inst_t       inst,
                                     mesa_afi_fastid_t fastid)
    CAP(AFI_V2);

/**
 * \brief Get seq_cnt for fast injection.
 *        If seq_cnt is set to 0 in mesa_afi_fast_inj_start() then the value
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
mesa_rc mesa_afi_fast_inj_seq_cnt_get(const mesa_inst_t              inst,
                                            mesa_afi_fastid_t        fastid,
                                            uint32_t               *const seq_cnt)
    CAP(AFI_V2);

// ========================================
// Slow injections
// ----------------------------------------
typedef uint32_t mesa_afi_slowid_t; /**< Opaque type for IDs of slow injections */

/**
 * Structure defining properties of a slow injection.
 */
typedef struct {
    /**
     * [IN]
     * Port number onto which the frame shall be transmitted periodically.
     *
     * Set to MESA_PORT_NO_NONE to use Virtual Device #1 (VD1) (for Up-MEPs)
     * and fill in \p masquerade_port_no with the masqueraded port.
     */
    mesa_port_no_t port_no;

    /**
     * [IN]
     * Priority on which the frame sequence shall be transmitted.
     *
     * Valid values are in the range [0; MESA_PRIO_END] and
     * [MESA_PRIO_SUPER; MESA_PRIO_SUPER + 1].
     */
    mesa_prio_t prio;

    /**
     * [IN]
     * For up-flows, that is, when setting \p port_no to MESA_PORT_NO_NONE,
     * convey the port number on which the flow ingresses, that is, the
     * masquerade port.
     *
     * It is not used unless \p port_no is set to MESA_PORT_NO_NONE.
     */
    mesa_port_no_t masquerade_port_no;
} mesa_afi_slow_inj_alloc_cfg_t CAP(AFI_V2);

/**
 * \brief Allocate AFI slow injection resource
 *
 * \param inst   [IN]  Target instance reference.
 * \param cfg    [IN]  Injection descriptor.
 * \param slowid [OUT] ID used for referencing the allocated resource.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_slow_inj_alloc(const mesa_inst_t                          inst,
                                const mesa_afi_slow_inj_alloc_cfg_t *const cfg,
                                      mesa_afi_slowid_t             *const slowid)
    CAP(AFI_V2);

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
mesa_rc mesa_afi_slow_inj_free(const mesa_inst_t       inst,
                                     mesa_afi_slowid_t slowid)
    CAP(AFI_V2);

/**
 * \brief Setup frame for slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_slow_inj_frm_hijack(const mesa_inst_t       inst,
                                           mesa_afi_slowid_t slowid)
    CAP(AFI_V2);

/**
 * Structure defining properties of a slow injection.
 */
typedef struct {
    /**
     * [IN]
     * Frames per hour.
     */
    uint64_t fph;

    /**
     * [IN]
     * 0: No injection time jitter.
     * 1: Injection delta time is randomized in interval [0.75*60*60/fph; 60/fph] secs
     * 2: Injection delta time is randomized in interval [0.50*60*60/fph; 60/fph] secs
     * 3: Injection delta time is randomized in interval [1 tick; 60*60/fph secs]
     *
     * E.g. to be used for PTP Delay Request, ref IEEE1588-2008, 9.5.11.2.
     */
    uint8_t jitter_mode;

    /**
     * [IN]
     * If FALSE, first frame is transmitted a randomized number of timer ticks
     * after call to mesa_afi_slow_inj_start() to minimize risk of bursting in
     * case many flows are started "simultaneously".
     * If TRUE, first frame must be transmitted ASAP.
     */
    mesa_bool_t first_frame_urgent;
} mesa_afi_slow_inj_start_cfg_t CAP(AFI_V2);

/**
 * \brief Start slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 * \param cfg    [IN] Slow injection configuration.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_slow_inj_start(const mesa_inst_t                          inst,
                                      mesa_afi_slowid_t                    slowid,
                                const mesa_afi_slow_inj_start_cfg_t *const cfg)
    CAP(AFI_V2);

/**
 * \brief Stop slow injection.
 *
 * \param inst   [IN] Target instance reference.
 * \param slowid [IN] Slow injection ID.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_slow_inj_stop(const mesa_inst_t       inst,
                                     mesa_afi_slowid_t slowid)
    CAP(AFI_V2);

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
 * \param port_no [IN] Port number. MESA_PORT_NO_NONE for VD1.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_port_start(const mesa_inst_t    inst,
                                  mesa_port_no_t port_no)
    CAP(AFI_V2);

/**
 * <\brief Stop all injections for specific port
 *
 * \param inst    [IN] Target instance reference.
 * \param port_no [IN] Port number. MESA_PORT_NO_NONE for VD1.
 *
 * \return Return code.
 **/
mesa_rc mesa_afi_port_stop(const mesa_inst_t    inst,
                                 mesa_port_no_t port_no)
    CAP(AFI_V2);

#include <mscc/ethernet/switch/api/hdr_end.h>
#endif // _MSCC_ETHERNET_SWITCH_API_AFI_
