// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_TC10_API_H_
#define _MEPA_TC10_API_H_

#include <microchip/ethernet/phy/api/types.h>
#include <microchip/ethernet/hdr_start.h>  /**< ALL INCLUDE ABOVE THIS LINE */

/** \brief  TC10 PIN types */
typedef enum mepa_tc10_pin {
    MEPA_TC10_WAKE_IN,  /**< Wake in pin */
    MEPA_TC10_WAKE_OUT, /**< Wake out pin */
    MEPA_TC10_INH,      /**< INH pin */
} mepa_tc10_pin_t;

/** \brief  TC10 sleep modes */
typedef enum mepa_tc10_sleep_request {
    MEPA_TC10_LPS,          /**< LPS pulse */
    MEPA_TC10_FORCE_SLEEP,  /**< Force sleep */
} mepa_tc10_sleep_request_t;

/** \brief  TC10 wakeup modes */
typedef enum mepa_tc10_wakeup_mode {
    MEPA_TC10_WAKEUP_DISABLE,           /**< PHY wakeup disable, will not wakeup for WUP and WAKE-IN request */
    MEPA_TC10_WAKEUP_WUP_ENABLE,        /**< PHY will wakeup only for WUP request */
    MEPA_TC10_WAKEUP_WAKEIN_ENABLE,     /**< PHY will wakeup only via WAKE-IN pin request */
    MEPA_TC10_WAKEUP_WUP_WAKEIN_ENABLE, /**< PHY will wakeup with WUP/WAKE-IN request */
} mepa_tc10_wakeup_mode_t;

/** \brief  TC10 wakeup forward modes */
typedef enum mepa_tc10_wakeup_fwd_mode {
    MEPA_TC10_WAKEUP_FWD_DISABLE,               /**< PHY wakeup forward disable */
    MEPA_TC10_WAKEUP_FWD_WUP_ENABLE,            /**< Enable WUP forward for WAKEIN request */
    MEPA_TC10_WAKEUP_FWD_WAKEOUT_ENABLE,        /**< Enable WAKEOUT forward for WUP/WAKEIN request */
    MEPA_TC10_WAKEUP_FWD_WUP_WAKEOUT_ENABLE,    /**< Enable WUP and WAKEOUT forward for WUP/WAKEIN requests */
} mepa_tc10_wakeup_fwd_mode_t;

/** \brief  TC10 states */
typedef enum mepa_tc10_sleep_state {
    MEPA_TC10_START,        /**< TC10 START or RESET state */
    MEPA_TC10_NORMAL,       /**< TC10 NORMAL state */
    MEPA_TC10_SLEEP_ACK,    /**< TC10 SLEEP ACK state */
    MEPA_TC10_SLEEP_REQ,    /**< TC10 SLEEP REQ state */
    MEPA_TC10_SLEEP_FAIL,   /**< TC10 SLEEP FAIL state */
    MEPA_TC10_SLEEP_SILENT, /**< TC10 SLEEP SILENT state */
    MEPA_TC10_SLEEP,        /**< TC10 SLEEP state */
} mepa_tc10_state_t;


/**
 * \brief Enable/Disable tc10 sleep function.
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN]  Enable/Disable the tc10 sleep function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_set_sleep_support(struct mepa_device          *dev,
                                    const mepa_bool_t           enable);

/**
 * \brief Enable/Disable tc10 sleep function.
 *
 * \param dev    [IN]   Driver instance.
 * \param enable [OUT]  Enable/Disable the tc10 sleep function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_sleep_support(struct mepa_device        *dev,
                                    mepa_bool_t               *const enable);

/**
 * \brief Enable/Disable tc10 wake function.
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN]  Enable/Disable the tc10 wake function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_set_wakeup_support(struct mepa_device                 *dev,
                                     const mepa_tc10_wakeup_mode_t      mode);

/**
 * \brief Enable/Disable tc10 wake function.
 *
 * \param dev    [IN]   Driver instance.
 * \param enable [OUT]  Enable/Disable the tc10 wake function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_wakeup_support(struct mepa_device                 *dev,
                                     mepa_tc10_wakeup_mode_t            *const mode);

/**
 * \brief Enable/Disable tc10 wake forward function.
 *
 * \param dev    [IN]  Driver instance.
 * \param enable [IN]  Enable/Disable the tc10 wake forward function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_set_wakeup_fwd_support(struct mepa_device                     *dev,
                                         const mepa_tc10_wakeup_fwd_mode_t      mode);

/**
 * \brief Enable/Disable tc10 wake forward function.
 *
 * \param dev    [IN]   Driver instance.
 * \param enable [OUT]  Enable/Disable the tc10 wake forward function.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_wakeup_fwd_support(struct mepa_device                     *dev,
                                         mepa_tc10_wakeup_fwd_mode_t            *const mode);

/**
 * \brief configure tc10 wake pin polarity.
 *
 * \param dev       [IN]    Driver instance.
 * \param pin       [IN]    PIN type to be configured.
 * \param polarity  [IN]    PIN polarity to be configured.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_set_wake_pin_polarity(struct mepa_device          *dev,
                                        const mepa_tc10_pin_t       pin,
                                        const mepa_gpio_mode_t      polarity);

/**
 * \brief configure tc10 wake pin polarity.
 *
 * \param dev       [IN]    Driver instance.
 * \param pin       [IN]    PIN type to be configured.
 * \param polarity  [OUT]   PIN polarity to be configured.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_wake_pin_polarity(struct mepa_device          *dev,
                                        const mepa_tc10_pin_t       pin,
                                        mepa_gpio_mode_t            *const polarity);

/**
 * \brief configure tc10 pin mode of operation.
 *
 * \param dev   [IN]    Driver instance.
 * \param pin   [IN]    PIN type to be configured.
 * \param mode  [IN]    PIN  mode of operation to be configured.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_set_pin_mode(struct mepa_device           *dev,
                               const mepa_tc10_pin_t        pin,
                               const mepa_gpio_mode_t       mode);

/**
 * \brief configure tc10 pin mode of operation.
 *
 * \param dev   [IN]    Driver instance.
 * \param pin   [IN]    PIN type to be configured.
 * \param mode  [OUT]   PIN  mode of operation to be configured.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_pin_mode(struct mepa_device           *dev,
                               const mepa_tc10_pin_t        pin,
                               mepa_gpio_mode_t             *const mode);

/**
 * \brief sends TC10 sleep request.
 *
 * \param dev   [IN]  Driver instance.
 * \param req   [IN]  TC10 Sleep request type
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_send_sleep_request(struct mepa_device                     *dev,
                                     const mepa_tc10_sleep_request_t        req);

/**
 * \brief provides TC10 state.
 *
 * \param dev   [IN]    Driver instance.
 * \param state [OUT]   TC10 state.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_get_state(struct mepa_device      *dev,
                            mepa_tc10_state_t       *const state);

/**
 * \brief sends TC10 wakeup request.
 *
 * \param dev   [IN]  Driver instance.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
mepa_rc mepa_tc10_send_wake_request(struct mepa_device *dev);

#include <microchip/ethernet/hdr_end.h>
#endif /**< _MEPA_TC10_API_H_ */
