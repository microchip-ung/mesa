// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT

/**
 * \file
 * \brief OS Layer API
 * \details This header file includes the OS specific header file
 */

#ifndef _VTSS_OS_H_
#define _VTSS_OS_H_

#if defined(VTSS_OPSYS_ECOS)
 #include <vtss_os_ecos.h>
#elif defined(VTSS_OPSYS_LINUX)
 #include <vtss_os_linux.h>
#elif defined(VTSS_OPSYS_LMSTAX)
 #include <vtss_os_lmstax.h>
#elif defined(VTSS_OS_CUSTOM)
 #include <vtss_os_custom.h>
#else
 #error "Operating system not supported".
#endif

/*
 * Don't add default VTSS_xxx() macro implementations here,
 * since that might lead to uncaught problems on new platforms.
 */

#endif /* _VTSS_OS_H_ */
