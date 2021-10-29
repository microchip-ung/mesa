/*AQ_User.h*/

/************************************************************************************
*
* Copyright (c) 2017 Aquantia Corp.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*
************************************************************************************/

/************************************************************************************
*                      Copyright Aquantia Corp.
*                              Freeware
*
* Description:
*
*   This file contains preprocessor symbol definitions and type definitions
*   for the platform-integrator controlled compile-time AQ_API options.
*
************************************************************************************/

/*! \file
  This file contains preprocessor symbol definitions and type definitions
  for the platform-integrator controlled compile-time AQ_API options.
*/

#ifndef AQ_USER_TOKEN
#define AQ_USER_TOKEN

#include <stdint.h>
#include <microchip/ethernet/phy/api.h>

/*! \defgroup User User Definitions
This module contains the definitions used to configure AQ_API behavior as desired. */
/*@{*/


/*! Specify the proper data type for AQ_Port. This will depend on the
 * platform-specific implementation of the PHY register read/write functions.*/
//typedef unsigned int AQ_Port;
/*! Vitesse CIL api layer needs vtss_state and port_no */

typedef struct{
    mscc_phy_driver_address_t mscc;
} AQ_Port;


/*! If defined, AQ_API functions will print various error and info messages
 * to stdout.  If not, nothing will be printed and AQ_API.c will NOT include
 * stdio.h. */
//#define AQ_VERBOSE
/*! Defines whether flash progress should be verbosed every page or rarely */
//#define AQ_VERBOSE_FLASH_PROGRESS 1

/*! If defined, the PHY interface supports block (asynchronous) read/write
 * operation. If AQ_PHY_SUPPORTS_BLOCK_READ_WRITE is defined, then
 * the API will call the block-operation functions and so implementations
 * for each must be provided. If AQ_PHY_SUPPORTS_BLOCK_READ_WRITE is not
 * defined, they will not be called, and need not be implemented. */
// commented out for VTSS
//#define AQ_PHY_SUPPORTS_BLOCK_READ_WRITE


/*! If defined, time.h exists, and so the associated functions wil be used to
 * compute the elapsed time spent in a polling loop, to ensure that the
 * maximum time-out period will not be exceeded.  If not defined, then
 * AQ_MDIO_READS_PER_SECOND will be used to calculate the minimum possible
 * elapsed time. */
#define AQ_TIME_T_EXISTS


/*! The maximum number of synchronous PHY register reads that can be performed
 * per second. A worst case number can be derived as follows:
 *
 * AQ_MDIO_READS_PER_SECOND = MDIO Clock Frequency / 64
 *
 * If using MDIO preamble suppression, multiply this number by 2
 *
 * For instance, if a 5MHz MDIO clock is being used without preamble supression
 * AQ_MDIO_READS_PER_SECOND = 78125
 *
 * If AQ_TIME_T_EXISTS is defined, this will be ignored and need not be
 * defined.  If AQ_TIME_T_EXISTS is not defined, this must be defined. */
#define AQ_MDIO_READS_PER_SECOND 78125

/*! If defined, NVR Busy bit will be polling between NVR Operations */
/* #define AQ_MDIO_CLOCK_EXCEEDS_NVR */

/*! Defines whether full chip erase should be used for Adesto flashes */
/* #define AQ_FLASH_ADESTO_FULL_ERASE */

/*! If defined, after writing to one of the registers that can trigger a
 * processor-intensive MDIO operation, AQ_API functions will poll the
 * the "processor intensive MDIO operation in progress" bit and wait for it
 * to be zero before proceeding. */
#define AQ_ENABLE_UP_BUSY_CHECKS


/*! If defined, the register map header files containing reverse-packed
 * structs will be included.  If not, the register map header files containing
 * non-reverse-packed structs will be included.  The proper choice is typically
 * a function of the endianness of the platform; on big-endian systems the
 * reverse-packed structs should be used, and on little-endian systems the
 * non-reverse-packed structs should be used. */
/*#define AQ_REVERSED_BITFIELD_ORDERING*/

/*@}*/
#endif

