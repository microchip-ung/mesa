/* AQ_ReturnCodes.h */

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
*   This file defines the AQ_API functions' integral return codes.
*
*
************************************************************************************/

/*! \file
  This file defines the AQ_API functions' integral return codes.
*/

#ifndef AQ_RETURNCODES_TOKEN
#define AQ_RETURNCODES_TOKEN


/*! \defgroup ReturnCodes
  @{
*/

/*! Most AQ_API functions return AQ_Retcode to report success or failure.
 * The values used are defined as preprocessor symbols in AQ_ReturnCodes.h. 
 * Callers should prefer to test the return values by equivalence to these
 * symbols, rather than using the integer values directly, as these may 
 * not be stable across releases.  The set of possible return codes that may 
 * be returned by a particular API function can be found in the function's 
 * documentation, as well as information on how to interpret each of the 
 * possible return codes. */
typedef unsigned int AQ_Retcode;

/*! \defgroup Success 
  @{ */
#define AQ_RET_OK 0
/*@}*/


/*! \defgroup GeneralErrors 
  @{ */
#define AQ_RET_ERROR 100
#define AQ_RET_UP_BUSY_TIMEOUT 101
/*@}*/

/*! \defgroup FunctionSpecificResults 
  @{ */
#define AQ_RET_FLASH_READY             200
#define AQ_RET_FLASH_READINESS_TIMEOUT 204

#define AQ_RET_FLASHINTF_READY             201
#define AQ_RET_FLASHINTF_READINESS_TIMEOUT 203

#define AQ_RET_FLASH_TYPE_UNKNOWN 205
#define AQ_RET_FLASH_TYPE_BAD     206

#define AQ_RET_FLASH_IMAGE_CORRUPT   207
#define AQ_RET_FLASH_IMAGE_TOO_LARGE 208
#define AQ_RET_FLASH_IMAGE_MISMATCH  209

#define AQ_RET_FLASH_PAGE_SIZE_NEED_CHANGE  202
#define AQ_RET_FLASH_PAGE_SIZE_CHANGED      210
#define AQ_RET_FLASH_ERASE_SIZE_UNSUPPORTED 243

#define AQ_RET_BOOTLOAD_PROVADDR_OOR        211
#define AQ_RET_BOOTLOAD_NONUNIFORM_REGVALS  212
#define AQ_RET_BOOTLOAD_CRC_MISMATCH        213
#define AQ_RET_BOOTLOAD_PROVTABLE_TOO_LARGE 228

#define AQ_RET_LOOPBACK_BAD_ENTRY_STATE 214

#define AQ_RET_DEBUGTRACE_FREEZE_TIMEOUT   215
#define AQ_RET_DEBUGTRACE_UNFREEZE_TIMEOUT 216

#define AQ_RET_CABLEDIAG_ALREADY_RUNNING          217
#define AQ_RET_CABLEDIAG_STILL_RUNNING            218
#define AQ_RET_CABLEDIAG_BAD_PAIRSTATUS           219
#define AQ_RET_CABLEDIAG_RESULTS_ALREDY_COLLECTED 220
#define AQ_RET_CABLEDIAG_BAD_NUM_SAMPLES          221
#define AQ_RET_CABLEDIAG_REPORTEDPAIR_MISMATCH    222
#define AQ_RET_CABLEDIAG_REPORTEDPAIR_OOR         223
#define AQ_RET_CABLEDIAG_STARTED_PAIR_B           224
#define AQ_RET_CABLEDIAG_STARTED_PAIR_C           225
#define AQ_RET_CABLEDIAG_STARTED_PAIR_D           226
#define AQ_RET_CABLEDIAG_TXENABLE_MISMATCH        227

#define AQ_RET_SERDESEYE_BAD_SERDES_MODE 229
#define AQ_RET_SERDESEYE_BAD_MEAS_COUNT  230
#define AQ_RET_SERDESEYE_MEAS_TIMEOUT    231
#define AQ_RET_SERDESEYE_LANE_OOR        232
#define AQ_RET_SERDESEYE_COORD_OOR       233

#define AQ_RET_PIFMAILBOX_ERROR   234
#define AQ_RET_PIFMAILBOX_TIMEOUT 235

#define AQ_RET_SEC_TABLE_INDEX_OOR 236

#define AQ_RET_TXPHASE_PROV_CHECK_FAILED    237
#define AQ_RET_TXPHASE_SANITYCHECK_FAILED   238
#define AQ_RET_TXPHASE_PROV_PREPARE_FAILED  239
#define AQ_RET_TXPHASE_PROV_SET_FAILED      240
#define AQ_RET_TXPHASE_PROV_APPLY_FAILED    241
#define AQ_RET_TXPHASE_LINK_FAILED          242

#define AQ_RET_FLASH_INVALID_PARAMETERS     244
#define AQ_RET_FLASH_ERASE_NOT_SUPPORTED    245

#define AQ_RET_LAST_ERROR                   245 /* AQ_RET_FLASH_ERASE_SIZE_UNSUPPORTED */

/*@}*/

/*@}*/
 
#endif
