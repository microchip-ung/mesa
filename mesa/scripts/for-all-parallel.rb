#!/usr/bin/env ruby
# Copyright (c) 2004-2017 Microsemi Corporation "Microsemi".
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

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
