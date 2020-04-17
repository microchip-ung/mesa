#!/bin/sh
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

# Generate html and latex
doxygen Doxyfile

# Generate pdf
cd doxygen/latex
sed -i -- "s/latex_count=8/latex_count=40/g" Makefile
make
