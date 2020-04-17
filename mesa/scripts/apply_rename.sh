#!/usr/bin/env sh
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT


find $1 -type f \
    \( \
        -name "*.c" \
        -or -name "*.h" \
        -or -name "*.cxx" \
        -or -name "*.hxx" \
        -or -name "*.icli" \
    \) \
    -exec sed -i -f $2 {} \;

