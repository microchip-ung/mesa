#!/usr/bin/env bash

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

# NOTE: Do not derive the toolchain version from deps-bsp.json - it will trigger
# a re-download everytime the BSP changes (despite it is the same toolchain)

set -e

TC_PATH=$(jq -r '.[] | select(.id == "toolchain") | ."build-artifact-url"' deps-toolchain.json)
TC_VER=$(jq -r '.[] | select(.id == "toolchain") | ."build-artifact-version-string"' deps-toolchain.json)

wget -O- $TC_PATH/mchp-toolchain-bin-$TC_VER.tar.gz | tar -xz -C /opt/mchp
