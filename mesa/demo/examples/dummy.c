/*
 Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".

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

#include <unistd.h>
#include <stdio.h>
#include "cli.h"
#include "example.h"
#include "mscc/ethernet/switch/api.h"

const char *dummy_help_txt = "\
This is a dummy test.\n\
\n\
There are two required parameters and one optional.\n\
The test result is the sum of all parameters.\n\
";

// Internal state - maybe information needed to clean up
static struct {
    uint32_t    param1;
    uint32_t    param2;
    uint32_t    opt1;
} state;

static int dummy_init(int argc, const char *argv[])
{
    uint32_t    param1 = ARGV_INT("param1", "Value to be added");
    uint32_t    param2 = ARGV_INT("param2", "Value to be added");
    uint32_t    opt1 = ARGV_OPT_INT("opt1", "Optional value to be added. Default is 3", 3);
    uint32_t    var=0;

    EXAMPLE_BARRIER(argc);

    memset(&state, 0, sizeof(state));
    state.param1 = param1;
    state.param2 = param2;
    state.opt1 = opt1;

    // snippet_begin x-dummy-param1
    // some snippet code
    var = var + param1;

    // snippet_endbegin ex-dummy-param2
    // some snippet code
    var = var + param2;

    // snippet_endbegin ex-dummy-opt1
    // some snippet code
    var = var + opt1;
    // snippet_end

    cli_printf("Dummy test result is sum of param1 + param2 + opt1: %u\n", var);

    return 0;
}

static int dummy_clean()
{
    return 0;
}

static const char* dummy_help()
{
    return dummy_help_txt;
}

EXAMPLE(dummy, dummy_init, NULL, dummy_clean, dummy_help);
