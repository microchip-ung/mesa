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

#include <stddef.h>
#include <stdint.h>

// TODO!!!
#define VTSS_PORTS 5
#include "catch.hpp"
#include "mscc/ethernet/switch/api/utils.h"
#include "mscc/ethernet/switch/api/capability.h"

TEST_CASE("caparray 1d", "[CapArray]") {
    CapArray<int, MESA_CAP_PORT_CNT> a1;
    a1.init();

    REQUIRE(a1.size() > 4);

    a1[0] = 1;
    a1[1] = 2;
    a1[2] = 3;
    a1[3] = 4;

    REQUIRE(a1[0] == 1);
    REQUIRE(a1[1] == 2);
    REQUIRE(a1[2] == 3);
    REQUIRE(a1[3] == 4);

    const CapArray<int, MESA_CAP_PORT_CNT> a2;
    a2.init();

    REQUIRE(a2[0] == 0);
    REQUIRE(a2[1] == 0);
    REQUIRE(a2[2] == 0);
    REQUIRE(a2[3] == 0);
}

TEST_CASE("caparray 2d", "[CapArray]") {
    CapArray<int, MESA_CAP_PORT_CNT, MESA_CAP_PORT_CNT> a1;
    a1.init();

    REQUIRE(a1.size() > 4);
    REQUIRE(a1[0].size() > 4);

    a1[0][0] = 1;
    a1[1][1] = 2;
    a1[2][2] = 3;
    a1[3][3] = 4;

    REQUIRE(a1[0][0] == 1);
    REQUIRE(a1[1][1] == 2);
    REQUIRE(a1[2][2] == 3);
    REQUIRE(a1[3][3] == 4);

    const CapArray<int, MESA_CAP_PORT_CNT, MESA_CAP_PORT_CNT> a2;
    a2.init();

    REQUIRE(a2.size() > 4);
    REQUIRE(a2[0].size() > 4);

    REQUIRE(a2[0][0] == 0);
    REQUIRE(a2[1][1] == 0);
    REQUIRE(a2[2][2] == 0);
    REQUIRE(a2[3][3] == 0);
}



