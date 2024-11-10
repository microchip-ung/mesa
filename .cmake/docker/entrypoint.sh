#!/usr/bin/env bash

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

if [[ -z $BLD_USER ]]; then
    BLD_USER=jenkins
fi

if [[ -z $BLD_UID ]]; then
    BLD_ID=1000
fi

# Remove any pre-created users such taht we can add a user with same ID as the
# one currently used
deluser jenkins 2> /dev/null 1>/dev/null || true
deluser ubuntu 2> /dev/null 1>/dev/null || true

# Add new user (if not running as root)
if [[ "$BLD_USER" != "root" ]]; then
    # Add user as specified in environment.
    adduser --no-create-home \
            --disabled-password \
            --home /mapped_home \
            --uid $BLD_UID \
            --ingroup users \
            --gecos "Docker user representing $BLD_USER" $BLD_USER > /dev/null
fi

# sodu expect to be able to resolve the hostname
echo "127.0.0.1 ${HOSTNAME}" >> /etc/hosts

# Allow user to sudo without password (TODO, remove once backwards compatibility
# is not needed any longer)
echo "$BLD_USER ALL=(ALL:ALL) NOPASSWD: ALL" > /etc/sudoers.d/$BLD_USER
chmod 0440 /etc/sudoers.d/$BLD_USER

# Unset IFS to make "$*" put a space between each argument.
unset IFS

# Jenkins will not provide the command when running
if [[ "$#" -eq "0" ]]; then
    exec runuser --pty "$BLD_USER" --command="cat"
else
    # Run command as user.
    # Create pseudo-terminal for better security on interactive sessions.
    # Note that "$*" is used here to put all parameter into a single string.
    exec runuser --pty "$BLD_USER" --command="$*"
fi
