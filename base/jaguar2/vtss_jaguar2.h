// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

#ifndef _VTSS_JAGUAR2_H_
#define _VTSS_JAGUAR2_H_

vtss_rc vtss_jaguar2_inst_create(struct vtss_state_s *vtss_state);

#if defined(VTSS_FEATURE_AFI_SWC)
#define VTSS_AFI_SLOT_CNT 1024 // JR2-TBD: Update to correct value
#endif                         /* VTSS_FEATURE_AFI_SWC */

#endif /* _VTSS_JAGUAR2_H_ */
