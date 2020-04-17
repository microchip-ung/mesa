#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'thread'
sem = Mutex.new

files = Queue.new
Dir.glob("vtss_appl/**/*.{c,cxx,h,hxx,icli}") do |f|
    files << f
end

Dir.glob("vtss_basics/**/*.{c,cxx,h,hxx,icli}") do |f|
    files << f
end

Dir.glob("vtss_api/boards/**/*.{c,cxx,h,hxx,icli}") do |f|
    files << f
end

cnt = 0
size = files.size
workers = (0...15).map do
    Thread.new do
        begin
            while x = files.pop(true) and !$stop
                %x{sed -f ./build/obj/mesa-ag/rename -i #{x}}
                sem.synchronize {
                    cnt += 1
                    puts "#{cnt}/#{size} #{x}"
                }
            end
        rescue ThreadError
        end
    end
end;

workers.map(&:join);
