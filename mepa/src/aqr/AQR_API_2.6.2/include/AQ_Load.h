/* AQ_Load.h */

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
*   This file defines the image load related constants.
*
*
************************************************************************************/

/*! \file
  This file defines the image load related constants.
*/

#ifndef _AQ_LOAD_H
#define _AQ_LOAD_H

#ifdef __cplusplus
extern "C" {
#endif

/*! FW image version string maximum length. */
#define AQ_VERSION_STRING_SIZE 0x40

/*! The byte offset from top of DRAM to the FW image version string. */
#define AQ_VERSION_STRING_BLOCK_OFFSET 0x0200

/*! The byte offset from the top of the PHY image to the header content (HHD & EUR devices). */
#define AQ_PHY_IMAGE_HEADER_CONTENT_OFFSET_HHD 0x300

/*! The byte offset from the top of the PHY image to the header content (APPIA devices). */
#define AQ_PHY_IMAGE_HEADER_CONTENT_OFFSET_APPIA 0

/*! The table used to compute CRC's within the PHY. */
extern const uint16_t AQ_CRC16Table[256];

#ifdef __cplusplus
}
#endif

#endif