/*AQ_PlatformRoutines.h*/

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
*   Declares the platform interface functions that will be called by AQ_API 
*   functions.  The platform integrator must provide the implementation of 
*   these functions.
*
************************************************************************************/

/*! \file 
 * Declares the platform interface functions that will be called by AQ_API 
 * functions.  The platform integrator must provide the implementation of 
 * these functions. */


#ifndef AQ_PHY_PLATFORMROUTINES_TOKEN
#define AQ_PHY_PLATFORMROUTINES_TOKEN

#include <stdint.h>

#include "AQ_API.h"
#include <AQ_User.h>
#include "AQ_ReturnCodes.h"

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************
                         Time Delay
*******************************************************************/

/*! \defgroup delay Time Delay
  @{
*/

/*! Returns after at least milliseconds have elapsed.  This must be implemented
 * in a platform-approriate way. AQ_API functions will call this function to 
 * block for the specified period of time. If necessary, PHY register reads
 * may be performed on port to busy-wait. */
void AQ_API_Wait
(
  uint32_t milliseconds,     /*!< The delay in milliseconds */
  AQ_API_Port* port          /*!< The PHY to use if delay reads are necessary*/
);

/*@}*/


#ifdef __cplusplus
}
#endif

#endif
