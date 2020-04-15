/*
 Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".

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
