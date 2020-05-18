// Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
// SPDX-License-Identifier: MIT


#include "mscc/ethernet/board/api.h"

#include "meba_aux.h"
#include "meba_common.h"
// Declare all the terminals in the graph

//      NAME                             TYPE                    DEV-ID   INDEX
#define eth_port_0                       MESA_SYNCE_DEV_PORT(         0,      0)
#define eth_port_1                       MESA_SYNCE_DEV_PORT(         1,      0)
#define eth_port_2                       MESA_SYNCE_DEV_PORT(         2,      0)
#define eth_port_3                       MESA_SYNCE_DEV_PORT(         3,      0)
#define eth_port_4                       MESA_SYNCE_DEV_PORT(         4,      0)
#define eth_port_5                       MESA_SYNCE_DEV_PORT(         5,      0)
#define eth_port_6                       MESA_SYNCE_DEV_PORT(         6,      0)
#define eth_port_7                       MESA_SYNCE_DEV_PORT(         7,      0)
#define eth_port_8                       MESA_SYNCE_DEV_PORT(         8,      0)
#define eth_port_9                       MESA_SYNCE_DEV_PORT(         9,      0)
#define eth_port_10                      MESA_SYNCE_DEV_PORT(        10,      0)
#define eth_port_11                      MESA_SYNCE_DEV_PORT(        11,      0)
#define eth_port_12                      MESA_SYNCE_DEV_PORT(        12,      0)
#define eth_port_13                      MESA_SYNCE_DEV_PORT(        13,      0)
#define eth_port_14                      MESA_SYNCE_DEV_PORT(        14,      0)
#define eth_port_15                      MESA_SYNCE_DEV_PORT(        15,      0)
#define eth_port_16                      MESA_SYNCE_DEV_PORT(        16,      0)
#define eth_port_17                      MESA_SYNCE_DEV_PORT(        17,      0)
#define eth_port_18                      MESA_SYNCE_DEV_PORT(        18,      0)
#define eth_port_19                      MESA_SYNCE_DEV_PORT(        19,      0)
#define eth_port_20                      MESA_SYNCE_DEV_PORT(        20,      0)
#define eth_port_21                      MESA_SYNCE_DEV_PORT(        21,      0)
#define eth_port_22                      MESA_SYNCE_DEV_PORT(        22,      0)
#define eth_port_23                      MESA_SYNCE_DEV_PORT(        23,      0)
#define eth_port_24                      MESA_SYNCE_DEV_PORT(        24,      0)
#define eth_port_25                      MESA_SYNCE_DEV_PORT(        25,      0)
#define eth_port_26                      MESA_SYNCE_DEV_PORT(        26,      0)
#define eth_port_27                      MESA_SYNCE_DEV_PORT(        27,      0)
#define eth_port_28                      MESA_SYNCE_DEV_PORT(        28,      0)
#define eth_port_29                      MESA_SYNCE_DEV_PORT(        29,      0)
#define eth_port_30                      MESA_SYNCE_DEV_PORT(        30,      0)
#define eth_port_31                      MESA_SYNCE_DEV_PORT(        31,      0)
#define eth_port_32                      MESA_SYNCE_DEV_PORT(        32,      0)
#define eth_port_33                      MESA_SYNCE_DEV_PORT(        33,      0)
#define eth_port_34                      MESA_SYNCE_DEV_PORT(        34,      0)
#define eth_port_35                      MESA_SYNCE_DEV_PORT(        35,      0)
#define eth_port_36                      MESA_SYNCE_DEV_PORT(        36,      0)
#define eth_port_37                      MESA_SYNCE_DEV_PORT(        37,      0)
#define eth_port_38                      MESA_SYNCE_DEV_PORT(        38,      0)
#define eth_port_39                      MESA_SYNCE_DEV_PORT(        39,      0)
#define eth_port_40                      MESA_SYNCE_DEV_PORT(        40,      0)
#define eth_port_41                      MESA_SYNCE_DEV_PORT(        41,      0)
#define eth_port_42                      MESA_SYNCE_DEV_PORT(        42,      0)
#define eth_port_43                      MESA_SYNCE_DEV_PORT(        43,      0)
#define eth_port_44                      MESA_SYNCE_DEV_PORT(        44,      0)
#define eth_port_45                      MESA_SYNCE_DEV_PORT(        45,      0)
#define eth_port_46                      MESA_SYNCE_DEV_PORT(        46,      0)
#define eth_port_47                      MESA_SYNCE_DEV_PORT(        47,      0)
#define eth_port_48                      MESA_SYNCE_DEV_PORT(        48,      0)
#define eth_port_49                      MESA_SYNCE_DEV_PORT(        49,      0)
#define eth_port_50                      MESA_SYNCE_DEV_PORT(        50,      0)
#define eth_port_51                      MESA_SYNCE_DEV_PORT(        51,      0)
#define eth_port_52                      MESA_SYNCE_DEV_PORT(        52,      0)
#define eth_port_53                      MESA_SYNCE_DEV_PORT(        53,      0)
#define eth_port_54                      MESA_SYNCE_DEV_PORT(        54,      0)
#define eth_port_55                      MESA_SYNCE_DEV_PORT(        55,      0)
#define eth_port_56                      MESA_SYNCE_DEV_PORT(        56,      0)

#define station_clock_fireant_20             MESA_SYNCE_DEV_CLOCK_IN(    21,      0)
#define station_clock_fireant_56             MESA_SYNCE_DEV_CLOCK_IN(    57,      0)
#define station_clock_fireant_8              MESA_SYNCE_DEV_CLOCK_IN(     9,      0)

#define divider_switch_mux_port_0_in      MESA_SYNCE_DEV_DIVIDER(      200,      MESA_SYNCE_DEV_INPUT | 0)
#define divider_switch_mux_port_0_out     MESA_SYNCE_DEV_DIVIDER(      200,      0)
#define divider_switch_mux_port_1_in      MESA_SYNCE_DEV_DIVIDER(      201,      MESA_SYNCE_DEV_INPUT | 1)
#define divider_switch_mux_port_1_out     MESA_SYNCE_DEV_DIVIDER(      201,      1)
#define divider_switch_mux_port_2_in      MESA_SYNCE_DEV_DIVIDER(      202,      MESA_SYNCE_DEV_INPUT | 2)
#define divider_switch_mux_port_2_out     MESA_SYNCE_DEV_DIVIDER(      202,      2)
#define divider_switch_mux_port_3_in      MESA_SYNCE_DEV_DIVIDER(      203,      MESA_SYNCE_DEV_INPUT | 3)
#define divider_switch_mux_port_3_out     MESA_SYNCE_DEV_DIVIDER(      203,      3)
#define divider_switch_mux_port_4_in      MESA_SYNCE_DEV_DIVIDER(      204,      MESA_SYNCE_DEV_INPUT | 4)
#define divider_switch_mux_port_4_out     MESA_SYNCE_DEV_DIVIDER(      204,      4)
#define divider_switch_mux_port_5_in      MESA_SYNCE_DEV_DIVIDER(      205,      MESA_SYNCE_DEV_INPUT | 5)
#define divider_switch_mux_port_5_out     MESA_SYNCE_DEV_DIVIDER(      205,      5)
#define divider_switch_mux_port_6_in      MESA_SYNCE_DEV_DIVIDER(      206,      MESA_SYNCE_DEV_INPUT | 6)
#define divider_switch_mux_port_6_out     MESA_SYNCE_DEV_DIVIDER(      206,      6)
#define divider_switch_mux_port_7_in      MESA_SYNCE_DEV_DIVIDER(      207,      MESA_SYNCE_DEV_INPUT | 7)
#define divider_switch_mux_port_7_out     MESA_SYNCE_DEV_DIVIDER(      207,      7)
#define divider_switch_mux_port_8_in      MESA_SYNCE_DEV_DIVIDER(      208,      MESA_SYNCE_DEV_INPUT | 8)
#define divider_switch_mux_port_8_out     MESA_SYNCE_DEV_DIVIDER(      208,      8)
#define divider_switch_mux_port_9_in      MESA_SYNCE_DEV_DIVIDER(      209,      MESA_SYNCE_DEV_INPUT | 9)
#define divider_switch_mux_port_9_out     MESA_SYNCE_DEV_DIVIDER(      209,      9)
#define divider_switch_mux_port_10_in     MESA_SYNCE_DEV_DIVIDER(      210,      MESA_SYNCE_DEV_INPUT | 10)
#define divider_switch_mux_port_10_out    MESA_SYNCE_DEV_DIVIDER(      210,      10)
#define divider_switch_mux_port_11_in     MESA_SYNCE_DEV_DIVIDER(      211,      MESA_SYNCE_DEV_INPUT | 11)
#define divider_switch_mux_port_11_out    MESA_SYNCE_DEV_DIVIDER(      211,      11)
#define divider_switch_mux_port_12_in     MESA_SYNCE_DEV_DIVIDER(      212,      MESA_SYNCE_DEV_INPUT | 12)
#define divider_switch_mux_port_12_out    MESA_SYNCE_DEV_DIVIDER(      212,      12)
#define divider_switch_mux_port_13_in     MESA_SYNCE_DEV_DIVIDER(      213,      MESA_SYNCE_DEV_INPUT | 13)
#define divider_switch_mux_port_13_out    MESA_SYNCE_DEV_DIVIDER(      213,      13)
#define divider_switch_mux_port_14_in     MESA_SYNCE_DEV_DIVIDER(      214,      MESA_SYNCE_DEV_INPUT | 14)
#define divider_switch_mux_port_14_out    MESA_SYNCE_DEV_DIVIDER(      214,      14)
#define divider_switch_mux_port_15_in     MESA_SYNCE_DEV_DIVIDER(      215,      MESA_SYNCE_DEV_INPUT | 15)
#define divider_switch_mux_port_15_out    MESA_SYNCE_DEV_DIVIDER(      215,      15)
#define divider_switch_mux_port_16_in     MESA_SYNCE_DEV_DIVIDER(      216,      MESA_SYNCE_DEV_INPUT | 16)
#define divider_switch_mux_port_16_out    MESA_SYNCE_DEV_DIVIDER(      216,      16)
#define divider_switch_mux_port_17_in     MESA_SYNCE_DEV_DIVIDER(      217,      MESA_SYNCE_DEV_INPUT | 17)
#define divider_switch_mux_port_17_out    MESA_SYNCE_DEV_DIVIDER(      217,      17)
#define divider_switch_mux_port_18_in     MESA_SYNCE_DEV_DIVIDER(      218,      MESA_SYNCE_DEV_INPUT | 18)
#define divider_switch_mux_port_18_out    MESA_SYNCE_DEV_DIVIDER(      218,      18)
#define divider_switch_mux_port_19_in     MESA_SYNCE_DEV_DIVIDER(      219,      MESA_SYNCE_DEV_INPUT | 19)
#define divider_switch_mux_port_19_out    MESA_SYNCE_DEV_DIVIDER(      219,      19)

#define divider_switch_mux_port_52_in     MESA_SYNCE_DEV_DIVIDER(      252,      MESA_SYNCE_DEV_INPUT | 52)
#define divider_switch_mux_port_52_out    MESA_SYNCE_DEV_DIVIDER(      252,      52)
#define divider_switch_mux_port_53_in     MESA_SYNCE_DEV_DIVIDER(      253,      MESA_SYNCE_DEV_INPUT | 53)
#define divider_switch_mux_port_53_out    MESA_SYNCE_DEV_DIVIDER(      253,      53)
#define divider_switch_mux_port_54_in     MESA_SYNCE_DEV_DIVIDER(      254,      MESA_SYNCE_DEV_INPUT | 54)
#define divider_switch_mux_port_54_out    MESA_SYNCE_DEV_DIVIDER(      254,      54)
#define divider_switch_mux_port_55_in     MESA_SYNCE_DEV_DIVIDER(      255,      MESA_SYNCE_DEV_INPUT | 55)
#define divider_switch_mux_port_55_out    MESA_SYNCE_DEV_DIVIDER(      255,      55)

#define switch_mux_port_in_0              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 0)
#define switch_mux_port_in_1              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 1)
#define switch_mux_port_in_2              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 2)
#define switch_mux_port_in_3              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 3)
#define switch_mux_port_in_4              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 4)
#define switch_mux_port_in_5              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 5)
#define switch_mux_port_in_6              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 6)
#define switch_mux_port_in_7              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 7)
#define switch_mux_port_in_8              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 8)
#define switch_mux_port_in_9              MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 9)
#define switch_mux_port_in_10             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 10)
#define switch_mux_port_in_11             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 11)
#define switch_mux_port_in_12             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 12)
#define switch_mux_port_in_13             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 13)
#define switch_mux_port_in_14             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 14)
#define switch_mux_port_in_15             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 15)
#define switch_mux_port_in_16             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 16)
#define switch_mux_port_in_17             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 17)
#define switch_mux_port_in_18             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 18)
#define switch_mux_port_in_19             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 19)
#define switch_mux_port_in_52             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 52)
#define switch_mux_port_in_53             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 53)
#define switch_mux_port_in_54             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 54)
#define switch_mux_port_in_55             MESA_SYNCE_DEV_MUX_SWITCH(   600,      MESA_SYNCE_DEV_INPUT | 55)

#define switch_mux_port_out_0             MESA_SYNCE_DEV_MUX_SWITCH(   600,      0)
#define switch_mux_port_out_1             MESA_SYNCE_DEV_MUX_SWITCH(   600,      1)
#define switch_mux_port_out_2             MESA_SYNCE_DEV_MUX_SWITCH(   600,      2)
#define switch_mux_port_out_3             MESA_SYNCE_DEV_MUX_SWITCH(   600,      3)

#define phy_mux_0_port_in_0                 MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 0)
#define phy_mux_0_port_in_1                 MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 1)
#define phy_mux_0_port_in_2                 MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 2)
#define phy_mux_0_port_in_3                 MESA_SYNCE_DEV_MUX_PHY(    400,      MESA_SYNCE_DEV_INPUT | 3)
#define phy_mux_1_port_in_4                 MESA_SYNCE_DEV_MUX_PHY(    401,      MESA_SYNCE_DEV_INPUT | 4)
#define phy_mux_1_port_in_5                 MESA_SYNCE_DEV_MUX_PHY(    401,      MESA_SYNCE_DEV_INPUT | 5)
#define phy_mux_1_port_in_6                 MESA_SYNCE_DEV_MUX_PHY(    401,      MESA_SYNCE_DEV_INPUT | 6)
#define phy_mux_1_port_in_7                 MESA_SYNCE_DEV_MUX_PHY(    401,      MESA_SYNCE_DEV_INPUT | 7)
#define phy_mux_2_port_in_8                 MESA_SYNCE_DEV_MUX_PHY(    402,      MESA_SYNCE_DEV_INPUT | 8)
#define phy_mux_2_port_in_9                 MESA_SYNCE_DEV_MUX_PHY(    402,      MESA_SYNCE_DEV_INPUT | 9)
#define phy_mux_2_port_in_10                MESA_SYNCE_DEV_MUX_PHY(    402,      MESA_SYNCE_DEV_INPUT | 10)
#define phy_mux_2_port_in_11                MESA_SYNCE_DEV_MUX_PHY(    402,      MESA_SYNCE_DEV_INPUT | 11)
#define phy_mux_3_port_in_12                MESA_SYNCE_DEV_MUX_PHY(    403,      MESA_SYNCE_DEV_INPUT | 12)
#define phy_mux_3_port_in_13                MESA_SYNCE_DEV_MUX_PHY(    403,      MESA_SYNCE_DEV_INPUT | 13)
#define phy_mux_3_port_in_14                MESA_SYNCE_DEV_MUX_PHY(    403,      MESA_SYNCE_DEV_INPUT | 14)
#define phy_mux_3_port_in_15                MESA_SYNCE_DEV_MUX_PHY(    403,      MESA_SYNCE_DEV_INPUT | 15)
#define phy_mux_4_port_in_16                MESA_SYNCE_DEV_MUX_PHY(    404,      MESA_SYNCE_DEV_INPUT | 16)
#define phy_mux_4_port_in_17                MESA_SYNCE_DEV_MUX_PHY(    404,      MESA_SYNCE_DEV_INPUT | 17)
#define phy_mux_4_port_in_18                MESA_SYNCE_DEV_MUX_PHY(    404,      MESA_SYNCE_DEV_INPUT | 18)
#define phy_mux_4_port_in_19                MESA_SYNCE_DEV_MUX_PHY(    404,      MESA_SYNCE_DEV_INPUT | 19)
#define phy_mux_5_port_in_20                MESA_SYNCE_DEV_MUX_PHY(    405,      MESA_SYNCE_DEV_INPUT | 20)
#define phy_mux_5_port_in_21                MESA_SYNCE_DEV_MUX_PHY(    405,      MESA_SYNCE_DEV_INPUT | 21)
#define phy_mux_5_port_in_22                MESA_SYNCE_DEV_MUX_PHY(    405,      MESA_SYNCE_DEV_INPUT | 22)
#define phy_mux_5_port_in_23                MESA_SYNCE_DEV_MUX_PHY(    405,      MESA_SYNCE_DEV_INPUT | 23)
#define phy_mux_6_port_in_24                MESA_SYNCE_DEV_MUX_PHY(    406,      MESA_SYNCE_DEV_INPUT | 24)
#define phy_mux_6_port_in_25                MESA_SYNCE_DEV_MUX_PHY(    406,      MESA_SYNCE_DEV_INPUT | 25)
#define phy_mux_6_port_in_26                MESA_SYNCE_DEV_MUX_PHY(    406,      MESA_SYNCE_DEV_INPUT | 26)
#define phy_mux_6_port_in_27                MESA_SYNCE_DEV_MUX_PHY(    406,      MESA_SYNCE_DEV_INPUT | 27)
#define phy_mux_7_port_in_28                MESA_SYNCE_DEV_MUX_PHY(    407,      MESA_SYNCE_DEV_INPUT | 28)
#define phy_mux_7_port_in_29                MESA_SYNCE_DEV_MUX_PHY(    407,      MESA_SYNCE_DEV_INPUT | 29)
#define phy_mux_7_port_in_30                MESA_SYNCE_DEV_MUX_PHY(    407,      MESA_SYNCE_DEV_INPUT | 30)
#define phy_mux_7_port_in_31                MESA_SYNCE_DEV_MUX_PHY(    407,      MESA_SYNCE_DEV_INPUT | 31)
#define phy_mux_8_port_in_32                MESA_SYNCE_DEV_MUX_PHY(    408,      MESA_SYNCE_DEV_INPUT | 32)
#define phy_mux_8_port_in_33                MESA_SYNCE_DEV_MUX_PHY(    408,      MESA_SYNCE_DEV_INPUT | 33)
#define phy_mux_8_port_in_34                MESA_SYNCE_DEV_MUX_PHY(    408,      MESA_SYNCE_DEV_INPUT | 34)
#define phy_mux_8_port_in_35                MESA_SYNCE_DEV_MUX_PHY(    408,      MESA_SYNCE_DEV_INPUT | 35)
#define phy_mux_9_port_in_36                MESA_SYNCE_DEV_MUX_PHY(    409,      MESA_SYNCE_DEV_INPUT | 36)
#define phy_mux_9_port_in_37                MESA_SYNCE_DEV_MUX_PHY(    409,      MESA_SYNCE_DEV_INPUT | 37)
#define phy_mux_9_port_in_38                MESA_SYNCE_DEV_MUX_PHY(    409,      MESA_SYNCE_DEV_INPUT | 38)
#define phy_mux_9_port_in_39                MESA_SYNCE_DEV_MUX_PHY(    409,      MESA_SYNCE_DEV_INPUT | 39)
#define phy_mux_10_port_in_40               MESA_SYNCE_DEV_MUX_PHY(    410,      MESA_SYNCE_DEV_INPUT | 40)
#define phy_mux_10_port_in_41               MESA_SYNCE_DEV_MUX_PHY(    410,      MESA_SYNCE_DEV_INPUT | 41)
#define phy_mux_10_port_in_42               MESA_SYNCE_DEV_MUX_PHY(    410,      MESA_SYNCE_DEV_INPUT | 42)
#define phy_mux_10_port_in_43               MESA_SYNCE_DEV_MUX_PHY(    410,      MESA_SYNCE_DEV_INPUT | 43)
#define phy_mux_11_port_in_44               MESA_SYNCE_DEV_MUX_PHY(    411,      MESA_SYNCE_DEV_INPUT | 44)
#define phy_mux_11_port_in_45               MESA_SYNCE_DEV_MUX_PHY(    411,      MESA_SYNCE_DEV_INPUT | 45)
#define phy_mux_11_port_in_46               MESA_SYNCE_DEV_MUX_PHY(    411,      MESA_SYNCE_DEV_INPUT | 46)
#define phy_mux_11_port_in_47               MESA_SYNCE_DEV_MUX_PHY(    411,      MESA_SYNCE_DEV_INPUT | 47)

#define phy_mux_0_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    400,      0)
#define phy_mux_0_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    400,      1)
#define phy_mux_1_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    401,      0)
#define phy_mux_1_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    401,      1)
#define phy_mux_2_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    402,      0)
#define phy_mux_2_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    402,      1)
#define phy_mux_3_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    403,      0)
#define phy_mux_3_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    403,      1)
#define phy_mux_4_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    404,      0)
#define phy_mux_4_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    404,      1)
#define phy_mux_5_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    405,      0)
#define phy_mux_5_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    405,      1)
#define phy_mux_6_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    406,      0)
#define phy_mux_6_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    406,      1)
#define phy_mux_7_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    407,      0)
#define phy_mux_7_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    407,      1)
#define phy_mux_8_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    408,      0)
#define phy_mux_8_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    408,      1)
#define phy_mux_9_port_out_0                MESA_SYNCE_DEV_MUX_PHY(    409,      0)
#define phy_mux_9_port_out_1                MESA_SYNCE_DEV_MUX_PHY(    409,      1)
#define phy_mux_10_port_out_0               MESA_SYNCE_DEV_MUX_PHY(    410,      0)
#define phy_mux_10_port_out_1               MESA_SYNCE_DEV_MUX_PHY(    410,      1)
#define phy_mux_11_port_out_0               MESA_SYNCE_DEV_MUX_PHY(    411,      0)
#define phy_mux_11_port_out_1               MESA_SYNCE_DEV_MUX_PHY(    411,      1)

#define board_mux_port_in_0                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 0)
#define board_mux_port_in_1                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 1)
#define board_mux_port_in_2                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 2)
#define board_mux_port_in_3                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 3)
#define board_mux_port_in_4                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 4)
#define board_mux_port_in_5                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 5)
#define board_mux_port_in_6                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 6)
#define board_mux_port_in_7                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 7)
#define board_mux_port_in_8                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 8)
#define board_mux_port_in_9                 MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 9)
#define board_mux_port_in_10                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 10)
#define board_mux_port_in_11                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 11)
#define board_mux_port_in_12                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 12)
#define board_mux_port_in_13                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 13)
#define board_mux_port_in_14                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 14)
#define board_mux_port_in_15                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 15)
#define board_mux_port_in_16                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 16)
#define board_mux_port_in_17                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 17)
#define board_mux_port_in_18                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 18)
#define board_mux_port_in_19                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 19)
#define board_mux_port_in_20                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 20)
#define board_mux_port_in_21                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 21)
#define board_mux_port_in_22                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 22)
#define board_mux_port_in_23                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 23)
#define board_mux_port_in_24                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 24)
#define board_mux_port_in_25                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 25)
#define board_mux_port_in_26                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 26)
#define board_mux_port_in_27                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 27)
#define board_mux_port_in_28                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 28)
#define board_mux_port_in_29                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 29)
#define board_mux_port_in_30                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 30)
#define board_mux_port_in_31                MESA_SYNCE_DEV_MUX_BOARD(  500,      MESA_SYNCE_DEV_INPUT | 31)

#define board_mux_port_out_0             MESA_SYNCE_DEV_MUX_BOARD(   500,      0)
#define board_mux_port_out_1             MESA_SYNCE_DEV_MUX_BOARD(   500,      1)
#define board_mux_port_out_2             MESA_SYNCE_DEV_MUX_BOARD(   500,      2)
#define board_mux_port_out_3             MESA_SYNCE_DEV_MUX_BOARD(   500,      3)

#define dpll_port_0                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 0)
#define dpll_port_1                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 1)
#define dpll_port_2                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 2)
#define dpll_port_3                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 3)
#define dpll_port_4                      MESA_SYNCE_DEV_DPLL(        700,      MESA_SYNCE_DEV_INPUT | 4)

static const meba_synce_graph_element_t synce_graph_elements_fireant_24_w_zls30772_board[] = {    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      divider_switch_mux_port_0_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_0_out,   switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      divider_switch_mux_port_1_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_1_out,   switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      divider_switch_mux_port_2_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_2_out,   switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      divider_switch_mux_port_3_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_3_out,   switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      divider_switch_mux_port_4_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_4_out,   switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      divider_switch_mux_port_5_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_5_out,   switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      divider_switch_mux_port_6_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_6_out,   switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      divider_switch_mux_port_7_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_7_out,   switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                      divider_switch_mux_port_8_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_8_out,   switch_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                      divider_switch_mux_port_9_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_9_out,   switch_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                     divider_switch_mux_port_10_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_10_out,  switch_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                     divider_switch_mux_port_11_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_11_out,  switch_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                     divider_switch_mux_port_12_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_12_out,  switch_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                     divider_switch_mux_port_13_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_13_out,  switch_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                     divider_switch_mux_port_14_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_14_out,  switch_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                     divider_switch_mux_port_15_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_15_out,  switch_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                     divider_switch_mux_port_16_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_16_out,  switch_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                     divider_switch_mux_port_17_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_17_out,  switch_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                     divider_switch_mux_port_18_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_18_out,  switch_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                     divider_switch_mux_port_19_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_19_out,  switch_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_fireant_20,        dpll_port_4),
};

static const meba_synce_terminal_attr_t attr_fireant_24_w_zls30772_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,   3),

    MESA_SYNCE_ATTR(switch_mux_port_in_0,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_0,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_8,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_8,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_9,   MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_9,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_10,  MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_10,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_11,  MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_31_25MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_11,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_12,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_13,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_14,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_15,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_16,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_17,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_18,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_19,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};
static const meba_synce_graph_element_t synce_graph_elements_fireant_56_w_zls30772_board[] = {    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                       phy_mux_0_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                       phy_mux_0_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                       phy_mux_0_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                       phy_mux_0_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                       phy_mux_1_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                       phy_mux_1_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                       phy_mux_1_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                       phy_mux_1_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_8,                       phy_mux_2_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_9,                       phy_mux_2_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_10,                      phy_mux_2_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_11,                      phy_mux_2_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_12,                      phy_mux_3_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_13,                      phy_mux_3_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_14,                      phy_mux_3_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_15,                      phy_mux_3_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_16,                      phy_mux_4_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_17,                      phy_mux_4_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_18,                      phy_mux_4_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_19,                      phy_mux_4_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_20,                      phy_mux_5_port_in_20),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_21,                      phy_mux_5_port_in_21),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_22,                      phy_mux_5_port_in_22),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_23,                      phy_mux_5_port_in_23),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_24,                      phy_mux_6_port_in_24),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_25,                      phy_mux_6_port_in_25),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_26,                      phy_mux_6_port_in_26),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_27,                      phy_mux_6_port_in_27),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_28,                      phy_mux_7_port_in_28),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_29,                      phy_mux_7_port_in_29),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_30,                      phy_mux_7_port_in_30),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_31,                      phy_mux_7_port_in_31),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_32,                      phy_mux_8_port_in_32),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_33,                      phy_mux_8_port_in_33),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_34,                      phy_mux_8_port_in_34),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_35,                      phy_mux_8_port_in_35),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_36,                      phy_mux_9_port_in_36),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_37,                      phy_mux_9_port_in_37),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_38,                      phy_mux_9_port_in_38),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_39,                      phy_mux_9_port_in_39),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_40,                      phy_mux_10_port_in_40),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_41,                      phy_mux_10_port_in_41),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_42,                      phy_mux_10_port_in_42),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_43,                      phy_mux_10_port_in_43),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_44,                      phy_mux_11_port_in_44),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_45,                      phy_mux_11_port_in_45),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_46,                      phy_mux_11_port_in_46),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_47,                      phy_mux_11_port_in_47),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_52,                      divider_switch_mux_port_52_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_52_out,   switch_mux_port_in_52),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_53,                      divider_switch_mux_port_53_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_53_out,   switch_mux_port_in_53),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_54,                      divider_switch_mux_port_54_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_54_out,   switch_mux_port_in_54),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_55,                      divider_switch_mux_port_55_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_55_out,   switch_mux_port_in_55),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_0,             board_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_0_port_out_1,             board_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_0,             board_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_1_port_out_1,             board_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_0,             board_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_2_port_out_1,             board_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_0,             board_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_3_port_out_1,             board_mux_port_in_8),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_4_port_out_0,             board_mux_port_in_9),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_4_port_out_1,             board_mux_port_in_10),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_5_port_out_0,             board_mux_port_in_11),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_5_port_out_1,             board_mux_port_in_12),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_6_port_out_0,             board_mux_port_in_13),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_6_port_out_1,             board_mux_port_in_14),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_7_port_out_0,             board_mux_port_in_15),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_7_port_out_1,             board_mux_port_in_16),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_8_port_out_0,             board_mux_port_in_17),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_8_port_out_1,             board_mux_port_in_18),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_9_port_out_0,             board_mux_port_in_19),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_9_port_out_1,             board_mux_port_in_20),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_10_port_out_0,            board_mux_port_in_21),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_10_port_out_1,            board_mux_port_in_22),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_11_port_out_0,            board_mux_port_in_23),
    MESA_SYNCE_GRAPH_CONNECTION(           phy_mux_11_port_out_1,            board_mux_port_in_24),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,            board_mux_port_in_29),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,            board_mux_port_in_30),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_0,             dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           board_mux_port_out_1,             dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_fireant_56,         dpll_port_4),
};
static const meba_synce_terminal_attr_t attr_fireant_56_w_zls30772_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,   3),

    MESA_SYNCE_ATTR(switch_mux_port_in_52,  MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_52,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_78_125MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_53,  MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_53,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_78_125MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_54,  MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_54,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_78_125MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_55,  MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_55,  MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_78_125MHZ),

    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_8,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_9,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_10,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_11,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_12,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_13,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_14,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_15,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_16,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_17,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_18,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_19,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_20,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_21,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_22,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_23,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_24,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_25,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_26,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_27,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_28,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_29,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_30,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_31,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_32,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_33,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_34,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_35,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_36,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_37,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_38,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_39,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_40,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_41,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_42,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_43,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_44,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_45,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_46,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_47,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_52,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_52,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_52,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_52,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_52,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_53,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_53,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_53,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_53,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_53,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_54,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_54,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_54,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_54,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_54,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_55,            MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_55,            MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_55,            MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_55,            MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_55,            MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};

static const meba_synce_graph_element_t synce_graph_elements_fireant_8_w_zls30772_board[] = {    // type                                source                           destination
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_0,                      divider_switch_mux_port_0_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_0_out,   switch_mux_port_in_0),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_1,                      divider_switch_mux_port_1_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_1_out,   switch_mux_port_in_1),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_2,                      divider_switch_mux_port_2_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_2_out,   switch_mux_port_in_2),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_3,                      divider_switch_mux_port_3_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_3_out,   switch_mux_port_in_3),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_4,                      divider_switch_mux_port_4_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_4_out,   switch_mux_port_in_4),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_5,                      divider_switch_mux_port_5_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_5_out,   switch_mux_port_in_5),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_6,                      divider_switch_mux_port_6_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_6_out,   switch_mux_port_in_6),
    MESA_SYNCE_GRAPH_CONNECTION(           eth_port_7,                      divider_switch_mux_port_7_in),
    MESA_SYNCE_GRAPH_CONNECTION(           divider_switch_mux_port_7_out,   switch_mux_port_in_7),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_2,           dpll_port_0),
    MESA_SYNCE_GRAPH_CONNECTION(           switch_mux_port_out_3,           dpll_port_1),
    MESA_SYNCE_GRAPH_CONNECTION(           station_clock_fireant_8,         dpll_port_4),
};

static const meba_synce_terminal_attr_t attr_fireant_8_w_zls30772_board[] = {
    //              device                 attr-type             attr-value
    MESA_SYNCE_ATTR(dpll_port_0,           MEBA_ATTR_CLOCK_ID,   1),
    MESA_SYNCE_ATTR(dpll_port_1,           MEBA_ATTR_CLOCK_ID,   2),
    MESA_SYNCE_ATTR(dpll_port_4,           MEBA_ATTR_CLOCK_ID,   3),
    MESA_SYNCE_ATTR(switch_mux_port_in_0,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_0,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_1,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_2,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_3,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_4,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_5,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_6,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,   MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(switch_mux_port_in_7,   MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_39_062MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_0,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_1,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_2,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_3,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_4,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_5,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_6,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_25G,       MEBA_SYNCE_CLOCK_FREQ_322_265MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_10G,       MEBA_SYNCE_CLOCK_FREQ_80_565MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_5G,        MEBA_SYNCE_CLOCK_FREQ_40_283MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_2_5G,      MEBA_SYNCE_CLOCK_FREQ_312_5MHZ),
    MESA_SYNCE_ATTR(eth_port_7,             MEBA_ATTR_FREQ_1G,        MEBA_SYNCE_CLOCK_FREQ_125MHZ),
};

mesa_rc meba_synce_graph_get(meba_inst_t inst, const meba_synce_graph_t **const g)
{
    static meba_synce_graph_t synce_graph;
    meba_synce_clock_hw_id_t dpll_type;
    int board_type = inst->props.board_type;
    meba_board_state_t *board = INST2BOARD(inst);

    if (meba_synce_spi_if_get_dpll_type(inst, &dpll_type) != MESA_RC_OK) {
        T_E(inst, "Failure probing DPLL type.");
        return MESA_RC_NOT_IMPLEMENTED;
    } else {
        if (dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30771 || dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30772 ||
                dpll_type == MEBA_SYNCE_CLOCK_HW_ZL_30773) {
            if (board_type == VTSS_BOARD_FIREANT_PCB134_REF) {
                if (board->port_cfg == VTSS_BOARD_CONF_8x25G_NPI) {
                    synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_fireant_8_w_zls30772_board);
                    synce_graph.graph = synce_graph_elements_fireant_8_w_zls30772_board;
                    synce_graph.attr = attr_fireant_8_w_zls30772_board;
                    synce_graph.attr_length = MEBA_ARRSZ(attr_fireant_8_w_zls30772_board);
                } else {
                    synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_fireant_24_w_zls30772_board);
                    synce_graph.graph = synce_graph_elements_fireant_24_w_zls30772_board;
                    synce_graph.attr = attr_fireant_24_w_zls30772_board;
                    synce_graph.attr_length = MEBA_ARRSZ(attr_fireant_24_w_zls30772_board);
                }
            } else if (board_type == VTSS_BOARD_FIREANT_PCB135_REF) {
                synce_graph.graph_length = MEBA_ARRSZ(synce_graph_elements_fireant_56_w_zls30772_board);
                synce_graph.graph = synce_graph_elements_fireant_56_w_zls30772_board;
                synce_graph.attr = attr_fireant_56_w_zls30772_board;
                synce_graph.attr_length = MEBA_ARRSZ(attr_fireant_56_w_zls30772_board);
            }
        }
        *g = &synce_graph;
    }

    return MESA_RC_OK;

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
