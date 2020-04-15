/*
 Copyright (c) 2004-2018 Microsemi Corporation "Microsemi".

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

#include "mscc/ethernet/board/api.h"

#include "meba_aux.h"

mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

mesa_rc meba_synce_mux_set(meba_inst_t  inst,
                           uint32_t     dev_id,
                           uint32_t     input,
                           uint32_t     output)
{
    T_I(inst, "TBD");
    return MESA_RC_NOT_IMPLEMENTED;
}

static meba_api_synce_t public_functions = {
#define X(name) . name = name,
    MEBA_LIST_OF_API_SYNCE_CALLS
#undef X
};

meba_api_synce_t *meba_synce_get()
{
    return &public_functions;
}
