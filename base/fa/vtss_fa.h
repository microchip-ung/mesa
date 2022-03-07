// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#ifndef _VTSS_FA_H_
#define _VTSS_FA_H_

vtss_rc vtss_fa_inst_create(struct vtss_state_s *vtss_state);
vtss_voe_idx_t vtss_fa_service_voe_alloc(vtss_state_t *vtss_state, vtss_voe_function_t function);
vtss_rc vtss_fa_service_voe_free(vtss_state_t         *vtss_state,
                                 vtss_voe_function_t  function,
                                 vtss_voe_idx_t       voe_idx);

#endif /* _VTSS_FA_H_ */

