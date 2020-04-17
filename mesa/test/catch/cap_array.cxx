// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


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



