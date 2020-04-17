#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'nokogiri'

doc = Nokogiri.XML(IO.read(ARGV[0])) do |config|
  config.default_xml.noblanks
end

IO.write(ARGV[0], doc.to_xml(:indent => 4))
