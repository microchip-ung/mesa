#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require_relative 'log'

Dir["./*.rb"].sort.each do |file|
    puts("----------------------------------------------------")
    Log.info("executing file #{file}")
    puts("----------------------------------------------------")
    system("#{file}")
end
