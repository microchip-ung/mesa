/************************************************************************************
*                    Copyright Aquantia Corporation
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

//#include <stdint.h>

#include "AQ_PlatformRoutines.h"
#include <unistd.h>

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
)
{
    usleep(milliseconds * 1000);
}

