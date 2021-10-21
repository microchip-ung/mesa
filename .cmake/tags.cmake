# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

add_custom_target(tags etags `find ./include/ ./base/ ./mesa/ ./linux_support/ ./meba/ ./me/ ./mepa/  -name \".*\" -prune -o -type f -print`
                  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR} COMMENT "Generate tag file for Emacs...")

