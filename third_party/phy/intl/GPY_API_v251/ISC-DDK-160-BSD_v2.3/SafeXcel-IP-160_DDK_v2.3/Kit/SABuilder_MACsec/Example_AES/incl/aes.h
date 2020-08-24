/* aes.h
*
* Include file for AES definitions
*
* Derived from example code written by Brad Conte.
* Changes with respect to the original:
*   - Removed all non-required function.
*   - Added a single block AES encrypt function (that includes key setup).
*   - Eliminated compiler warnings.
*
* These are basic implementations of standard cryptography algorithms,
* written by Brad Conte (brad@bradconte.com) from scratch and without
* any cross-licensing. They exist to provide publically accessible,
* restriction-free implementations of popular cryptographic
* algorithms, like AES and SHA-1. These are primarily intended for
* educational and pragmatic purposes (such as comparing a
* specification to actual implementation code, or for building an
* internal application that computes test vectors for a product). The
* algorithms have been tested against standard test vectors.
*
* This code is released into the public domain free of any
* restrictions. The author requests acknowledgement if the code is
* used, but does not require it. This code is provided free of any
* liability and without any quality claims by the author
*
*/

/*****************************************************************************
* Copyright (c) 2017 INSIDE Secure B.V. All Rights Reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*****************************************************************************/
#ifndef AES_H
#define AES_H

/*************************** HEADER FILES ***************************/
#include <stddef.h>

//#include "basic_defs.h"

/****************************** MACROS ******************************/
#define AES_BLOCK_SIZE 16               // AES operates on 16 bytes at a time

/**************************** DATA TYPES ****************************/
typedef unsigned char BYTE;// 8-bit byte
typedef unsigned int WORD; // 32-bit word, change to "long" for 16-bit machines

/*********************** FUNCTION DECLARATIONS **********************/
///////////////////
// AES
///////////////////
// Key setup must be done before any AES en/de-cryption functions can be used.
void aes_key_setup(const BYTE key[],          // The key, must be 128, 192, or 256 bits
                   WORD w[],                  // Output key schedule to be used later
                   int keysize);              // Bit length of the key, 128, 192, or 256

void aes_encrypt(const BYTE in[],             // 16 bytes of plaintext
                 BYTE out[],                  // 16 bytes of ciphertext
                 const WORD key[],            // From the key setup
                 int keysize);                // Bit length of the key, 128, 192, or 256


/*----------------------------------------------------------------------------
* AES_Encrypt
*
* Wrapper function as required by the SA Builder. Encrypts a single
* data block using AES.
*
* pInput
*     Pointer to a 16 byte buffer with the plain data.
*
* pOutput
*     Pointer to a 16 bytes buffer with received the encrypted data.
*
* pKey
*     Pointer to the encryption key.
*
* nKeyLen
*     The length of the encryption key in bytes.
*     This must be a value if 16, 24 or 32.
*
* Return Value:
*     No return value.
*/
void
AES_Encrypt(
        const unsigned char * const pInput,
        unsigned char * const pOutput,
        const unsigned char * const pKey,
        unsigned int nKeyLen);


#endif   // AES_H

/* end of file aes.h */
