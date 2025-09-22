// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef VTSS_MISC_STATE_H
#define VTSS_MISC_STATE_H

#if defined(VTSS_FEATURE_MISC)

/* Number of chips per instance */
#define VTSS_CHIP_CNT 2

#if defined(VTSS_FEATURE_SERIAL_GPIO)
typedef struct {
    BOOL enable[VTSS_SGPIO_PORTS][4]; /* each port has four bits */
} vtss_sgpio_event_enable_t;
#endif /* VTSS_FEATURE_SERIAL_GPIO */

/* CIL function pointers */
vtss_rc vtss_cil_misc_reg_read(struct vtss_state_s *vtss_state,
                               const vtss_chip_no_t chip_no,
                               const u32            addr,
                               u32 *const           value);
vtss_rc vtss_cil_misc_reg_write(struct vtss_state_s *vtss_state,
                                const vtss_chip_no_t chip_no,
                                const u32            addr,
                                const u32            value);

vtss_rc vtss_cil_misc_chip_id_get(struct vtss_state_s *vtss_state, vtss_chip_id_t *const chip_id);
vtss_rc vtss_cil_misc_poll_1sec(struct vtss_state_s *vtss_state);
vtss_rc vtss_cil_misc_ptp_event_poll(struct vtss_state_s         *vtss_state,
                                     vtss_ptp_event_type_t *const ev_mask);
vtss_rc vtss_cil_misc_ptp_event_enable(struct vtss_state_s  *vtss_state,
                                       vtss_ptp_event_type_t ev_mask,
                                       BOOL                  enable);
vtss_rc vtss_cil_misc_dev_all_event_poll(struct vtss_state_s             *vtss_state,
                                         vtss_dev_all_event_poll_t        poll_type,
                                         vtss_dev_all_event_type_t *const ev_mask);
vtss_rc vtss_cil_misc_dev_all_event_enable(struct vtss_state_s      *vtss_state,
                                           vtss_port_no_t            port,
                                           vtss_dev_all_event_type_t ev_mask,
                                           BOOL                      enable);

vtss_rc vtss_cil_misc_mdio_conf_set(struct vtss_state_s          *vtss_state,
                                    const u8                      ctrl_id,
                                    const vtss_mdio_conf_t *const conf);

#if defined(VTSS_FEATURE_SERIAL_GPIO)
vtss_rc vtss_cil_misc_sgpio_conf_set(struct vtss_state_s           *vtss_state,
                                     const vtss_chip_no_t           chip_no,
                                     const vtss_sgpio_group_t       group,
                                     const vtss_sgpio_conf_t *const conf);
vtss_rc vtss_cil_misc_sgpio_read(struct vtss_state_s     *vtss_state,
                                 const vtss_chip_no_t     chip_no,
                                 const vtss_sgpio_group_t group,
                                 vtss_sgpio_port_data_t   data[VTSS_SGPIO_PORTS]);
vtss_rc vtss_cil_misc_sgpio_event_enable(struct vtss_state_s     *vtss_state,
                                         const vtss_chip_no_t     chip_no,
                                         const vtss_sgpio_group_t group,
                                         const vtss_port_no_t     port,
                                         const u32                bit,
                                         const BOOL               enable);
vtss_rc vtss_cil_misc_sgpio_event_poll(struct vtss_state_s     *vtss_state,
                                       const vtss_chip_no_t     chip_no,
                                       const vtss_sgpio_group_t group,
                                       const u32                bit,
                                       BOOL *const              events);
#endif /* VTSS_FEATURE_SERIAL_GPIO */
#if defined(VTSS_GPIOS)
vtss_rc vtss_cil_misc_gpio_mode(struct vtss_state_s   *vtss_state,
                                const vtss_chip_no_t   chip_no,
                                const vtss_gpio_no_t   gpio_no,
                                const vtss_gpio_mode_t mode);
vtss_rc vtss_cil_misc_gpio_read(struct vtss_state_s *vtss_state,
                                const vtss_chip_no_t chip_no,
                                const vtss_gpio_no_t gpio_no,
                                BOOL *const          value);
vtss_rc vtss_cil_misc_gpio_write(struct vtss_state_s *vtss_state,
                                 const vtss_chip_no_t chip_no,
                                 const vtss_gpio_no_t gpio_no,
                                 const BOOL           value);
vtss_rc vtss_cil_misc_gpio_event_poll(struct vtss_state_s *vtss_state,
                                      const vtss_chip_no_t chip_no,
                                      BOOL *const          events);
vtss_rc vtss_cil_misc_gpio_event_enable(struct vtss_state_s *vtss_state,
                                        const vtss_chip_no_t chip_no,
                                        const vtss_gpio_no_t gpio_no,
                                        const BOOL           enable);
#endif /* GPIOS */
#if defined(VTSS_FEATURE_INTERRUPTS)
vtss_rc vtss_cil_misc_intr_cfg(struct vtss_state_s *vtss_state,
                               const u32            mask,
                               const BOOL           polarity,
                               const BOOL           enable);
vtss_rc vtss_cil_misc_intr_pol_negation(struct vtss_state_s *vtss_state);
vtss_rc vtss_cil_misc_intr_status_get(struct vtss_state_s *vtss_state, vtss_intr_t *status);
vtss_rc vtss_cil_misc_intr_mask_set(struct vtss_state_s *vtss_state, vtss_intr_t *mask);
#endif // VTSS_FEATURE_INTERRUPTS
#ifdef VTSS_FEATURE_IRQ_CONTROL
vtss_rc vtss_cil_misc_irq_cfg(struct vtss_state_s         *vtss_state,
                              const vtss_irq_t             irq,
                              const vtss_irq_conf_t *const conf);
vtss_rc vtss_cil_misc_irq_status(struct vtss_state_s *vtss_state, vtss_irq_status_t *status);
vtss_rc vtss_cil_misc_irq_enable(const vtss_inst_t inst, const vtss_irq_t irq, BOOL enable);
#endif /* VTSS_FEATURE_IRQ_CONTROL */
#if defined(VTSS_FEATURE_VSCOPE)
vtss_rc vtss_cil_misc_vscope_conf_set(struct vtss_state_s            *vtss_state,
                                      const vtss_port_no_t            chip_port,
                                      const vtss_vscope_conf_t *const conf);

vtss_rc vtss_cil_misc_vscope_scan_status_get(struct vtss_state_s             *vtss_state,
                                             const vtss_port_no_t             chip_port,
                                             vtss_vscope_scan_status_t *const conf);
#endif /* VTSS_FEATURE_VSCOPE */

typedef struct {
    /* Configuration/state */
    vtss_chip_id_t chip_id;
    BOOL           jr2_a; /* Jaguar-2 revision A */
#if defined(VTSS_FEATURE_SERIAL_GPIO)
    vtss_sgpio_conf_t         sgpio_conf[VTSS_CHIP_CNT][VTSS_SGPIO_GROUPS];
    vtss_sgpio_event_enable_t sgpio_event_enabled[VTSS_CHIP_CNT][VTSS_SGPIO_GROUPS];
#endif /* VTSS_FEATURE_SERIAL_GPIO */
#ifdef VTSS_FEATURE_IRQ_CONTROL
    vtss_irq_conf_t irq_conf[VTSS_IRQ_MAX];
#if defined(VTSS_ARCH_LUTON26)
    u32 irq_user_space_owned_mask; /**< Mask indicating whether an IRQ is owned
                                      by user space or another entity */
#endif                             /* VTSS_ARCH_LUTON26 */
#endif                             /* defined(VTSS_FEATURE_IRQ_CONTROL) */
#if defined(VTSS_FEATURE_VSCOPE)
    vtss_vscope_conf_t vscope_conf[20];
#endif /* VTSS_FEATURE_VSCOPE */
} vtss_misc_state_t;

vtss_rc vtss_misc_inst_create(struct vtss_state_s *vtss_state);
void    vtss_misc_debug_print(struct vtss_state_s           *vtss_state,
                              lmu_ss_t                      *ss,
                              const vtss_debug_info_t *const info);

#endif /* VTSS_FEATURE_MISC */

#endif /* VTSS_MISC_STATE_H */
