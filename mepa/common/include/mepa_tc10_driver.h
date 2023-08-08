// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _MEPA_TC10_DRV_API_H_
#define _MEPA_TC10_DRV_API_H_

#include <microchip/ethernet/phy/api.h>

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
typedef mepa_rc (*mepa_tc10_set_sleep_support_t)(struct mepa_device *dev,
                                                 const mepa_bool_t enable);

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
typedef mepa_rc (*mepa_tc10_get_sleep_support_t)(struct mepa_device *dev,
                                                 mepa_bool_t *const enable);

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
typedef mepa_rc (*mepa_tc10_set_wakeup_support_t)(struct mepa_device *dev,
                                                  const  mepa_tc10_wakeup_mode_t mode);

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
typedef mepa_rc (*mepa_tc10_get_wakeup_support_t)(struct mepa_device *dev,
                                                  mepa_tc10_wakeup_mode_t *const mode);

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
typedef mepa_rc (*mepa_tc10_set_wakeup_fwd_support_t)(struct mepa_device *dev,
                                                      const  mepa_tc10_wakeup_fwd_mode_t mode);

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
typedef mepa_rc (*mepa_tc10_get_wakeup_fwd_support_t)(struct mepa_device *dev,
                                                      mepa_tc10_wakeup_fwd_mode_t *const mode);

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
typedef mepa_rc (*mepa_tc10_set_wake_pin_polarity_t)(struct mepa_device *dev,
                                                     const mepa_tc10_pin_t pin,
                                                     const mepa_gpio_mode_t polarity);

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
typedef mepa_rc (*mepa_tc10_get_wake_pin_polarity_t)(struct mepa_device *dev,
                                                     const mepa_tc10_pin_t pin,
                                                     mepa_gpio_mode_t *const polarity);

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
typedef mepa_rc (*mepa_tc10_set_pin_mode_t)(struct mepa_device *dev,
                                            const mepa_tc10_pin_t pin,
                                            const mepa_gpio_mode_t mode);

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
typedef mepa_rc (*mepa_tc10_get_pin_mode_t)(struct mepa_device *dev,
                                            const mepa_tc10_pin_t pin,
                                            mepa_gpio_mode_t *const polarity);

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
typedef mepa_rc (*mepa_tc10_send_sleep_request_t)(struct mepa_device *dev,
                                                  const mepa_tc10_sleep_request_t req);

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
typedef mepa_rc (*mepa_tc10_get_state_t)(struct mepa_device *dev,
                                         mepa_tc10_state_t *const state);

/**
 * \brief sends TC10 wakeup request.
 *
 * \param dev   [IN]  Driver instance.
 *
 * \return
 *   MEPA_RC_OK on success.\n
 *   MEPA_RC_ERROR on error.
 **/
typedef mepa_rc (*mepa_tc10_send_wake_request_t)(struct mepa_device *dev);

/** \brief PHY TC10 Driver */
typedef struct mepa_tc10_driver {
    mepa_tc10_set_sleep_support_t           mepa_tc10_set_sleep_support;
    mepa_tc10_get_sleep_support_t           mepa_tc10_get_sleep_support;
    mepa_tc10_set_wakeup_support_t          mepa_tc10_set_wakeup_support;
    mepa_tc10_get_wakeup_support_t          mepa_tc10_get_wakeup_support;
    mepa_tc10_set_wakeup_fwd_support_t      mepa_tc10_set_wakeup_fwd_support;
    mepa_tc10_get_wakeup_fwd_support_t      mepa_tc10_get_wakeup_fwd_support;
    mepa_tc10_set_wake_pin_polarity_t       mepa_tc10_set_wake_pin_polarity;
    mepa_tc10_get_wake_pin_polarity_t       mepa_tc10_get_wake_pin_polarity;
    mepa_tc10_set_pin_mode_t                mepa_tc10_set_pin_mode;
    mepa_tc10_get_pin_mode_t                mepa_tc10_get_pin_mode;
    mepa_tc10_send_sleep_request_t          mepa_tc10_send_sleep_request;
    mepa_tc10_get_state_t                   mepa_tc10_get_state;
    mepa_tc10_send_wake_request_t           mepa_tc10_send_wake_request;
} mepa_tc10_driver_t;

#endif  /* _MEPA_TC10_DRV_API_H_ */
