// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "catch.hpp"
#include <assert.h>
#include <string.h>
#include "microchip/ethernet/switch/api/port_list.h"
#include <type_traits>

TEST_CASE("port_list get", "[port_list]") {
    mesa_port_list_t l;
    memset(&l, 0x0, sizeof(l));

    for (size_t i = 0; i < l.max_size(); ++i) {
        REQUIRE(!l[i]);
    }

    memset(&l, 0xff, sizeof(l));

    for (size_t i = 0; i < l.max_size(); ++i) {
        REQUIRE(l[i]);
    }
}


TEST_CASE("port_list const", "[port_list]") {
    const mesa_port_list_t l;

    for (size_t i = 0; i < l.max_size(); ++i) {
        REQUIRE(!l[i]);
    }

}

TEST_CASE("array size", "[port_list]") {
    // TODO
    int x[10];
    mesa_port_list_t l;

    REQUIRE(sizeof(l) == sizeof(mesa_port_list_t));
    REQUIRE(sizeof(l[0]) == sizeof(mesa_port_list_ref));

    REQUIRE(MESA_ARRSZ(l) == 5);
    REQUIRE(MESA_ARRSZ(x) == 10);

    int y[MESA_ARRSZ(l)];
    REQUIRE(sizeof(y) == 5 * 4);
}

TEST_CASE("port_list get/set", "[port_list]") {
    mesa_port_list_t l;

    for (size_t i = 0; i < l.max_size(); ++i) {
        REQUIRE(!l[i]);
    }

    l[0] = true;
    REQUIRE(l[0]);
    REQUIRE(l._private[0] == 1);
    l[0] = false;
    REQUIRE(!l[0]);
    REQUIRE(l._private[0] == 0);

    l[1] = true;
    REQUIRE(l[1]);
    REQUIRE(l._private[0] == 2);
    l[1] = false;
    REQUIRE(!l[1]);
    REQUIRE(l._private[0] == 0);

    l[2] = true;
    REQUIRE(l[2]);
    REQUIRE(l._private[0] == 4);
    l[2] = false;
    REQUIRE(!l[2]);
    REQUIRE(l._private[0] == 0);

    l[3] = true;
    REQUIRE(l[3]);
    REQUIRE(l._private[0] == 8);
    l[3] = false;
    REQUIRE(!l[3]);
    REQUIRE(l._private[0] == 0);

    l[4] = true;
    REQUIRE(l[4]);
    REQUIRE(l._private[0] == 16);
    l[4] = false;
    REQUIRE(!l[4]);
    REQUIRE(l._private[0] == 0);

    l[5] = true;
    REQUIRE(l[5]);
    REQUIRE(l._private[0] == 32);
    l[5] = false;
    REQUIRE(!l[5]);
    REQUIRE(l._private[0] == 0);

    l[6] = true;
    REQUIRE(l[6]);
    REQUIRE(l._private[0] == 64);
    l[6] = false;
    REQUIRE(!l[6]);
    REQUIRE(l._private[0] == 0);

    l[7] = true;
    REQUIRE(l[7]);
    REQUIRE(l._private[0] == 128);
    l[7] = false;
    REQUIRE(!l[7]);
    REQUIRE(l._private[0] == 0);

    /////////////////////////////
    memset(&l, 0xff, sizeof(l));
    uint8_t x;
    l[0] = false;
    REQUIRE(!l[0]);
    REQUIRE(l._private[0] == (uint8_t)0xfe);
    l[0] = true;
    REQUIRE(l[0]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[1] = false;
    REQUIRE(!l[1]);
    REQUIRE(l._private[0] == (uint8_t)0xfd);
    l[1] = true;
    REQUIRE(l[1]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[2] = false;
    REQUIRE(!l[2]);
    REQUIRE(l._private[0] == (uint8_t)0xfb);
    l[2] = true;
    REQUIRE(l[2]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[3] = false;
    REQUIRE(!l[3]);
    REQUIRE(l._private[0] == (uint8_t)0xf7);
    l[3] = true;
    REQUIRE(l[3]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[4] = false;
    REQUIRE(!l[4]);
    REQUIRE(l._private[0] == (uint8_t)0xef);
    l[4] = true;
    REQUIRE(l[4]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[5] = false;
    REQUIRE(!l[5]);
    REQUIRE(l._private[0] == (uint8_t)0xdf);
    l[5] = true;
    REQUIRE(l[5]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[6] = false;
    REQUIRE(!l[6]);
    REQUIRE(l._private[0] == (uint8_t)0xbf);
    l[6] = true;
    REQUIRE(l[6]);
    REQUIRE(l._private[0] == (uint8_t)0xff);

    l[7] = false;
    REQUIRE(!l[7]);
    REQUIRE(l._private[0] == (uint8_t)0x7f);
    l[7] = true;
    REQUIRE(l[7]);
    REQUIRE(l._private[0] == (uint8_t)0xff);
}

TEST_CASE("port_list assign", "[port_list]") {
    mesa_port_list_t l;
    l[0] = true;
    l[1] = false;
    l[0] = l[1];
    REQUIRE(!l[0]);
    REQUIRE(!l[1]);

    l[0] = false;
    l[1] = true;
    l[0] = l[1];
    REQUIRE(l[0]);
    REQUIRE(l[1]);
}

