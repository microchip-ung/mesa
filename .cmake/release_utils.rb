#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

# This installs a given version of the mscc-release-utils GIT repository in
# /opt/mscc.
# The mscc-release-utils repo is used for generating release-notes and checking
# copyrights.
#
# To clone the real stuff, do a
# git clone ssh://git@bitbucket.microchip.com/unge/sw-tools-mscc-release-utils.git

MSCC_RELEASE_UTILS_VER     = 'v0.153'
MSCC_RELEASE_UTILS_PACKAGE = 'mscc-sw-release-utils'
MSCC_RELEASE_UTILS_SUBDIR  = "#{MSCC_RELEASE_UTILS_PACKAGE}-#{MSCC_RELEASE_UTILS_VER}"
MSCC_RELEASE_UTILS_DIR     = "/opt/mscc/#{MSCC_RELEASE_UTILS_SUBDIR}"

if !system("sudo /usr/local/bin/mscc-install-pkg -t #{MSCC_RELEASE_UTILS_PACKAGE} #{MSCC_RELEASE_UTILS_SUBDIR}")
    STDERR.puts("Error: Unable to install version #{MSCC_RELEASE_UTILS_VER} of #{MSCC_RELEASE_UTILS_PACKAGE}")
	exit(-1)
end

