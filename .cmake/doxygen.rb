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

require 'pp'
require 'optparse'
require 'fileutils'

$TOP = File.expand_path(File.dirname(File.dirname(__FILE__)))

$options = {
    :name => "",
    :target => "",
    :output_dir => ".",
    :files => [],
    :incl => [],
    :defs => []
}

OptionParser.new do |opts|
    opts.banner = "Usage: "

    opts.on_tail("-n", "--name NAME", "Project name") do |v|
        $options[:name] = v.to_s.strip
    end

    opts.on_tail("-t", "--target NAME", "Target name") do |v|
        $options[:target] = v.to_s.strip
    end

    opts.on_tail("-o", "--output-dir DIR", "Where to store the generated files") do |v|
        $options[:output_dir] = v.to_s.strip
    end

    opts.on_tail("-Iincl", "Includes") do |v|
        $options[:incl] << v.to_s.strip
    end

    opts.on_tail("-Ddefine", "defines") do |v|
        $options[:defs] << v.to_s.strip
    end

    opts.on_tail("-h", "--help", "Show this message") do
        puts opts
        exit
    end
end.parse!

$options[:files] = ARGV

$dir = "#{$options[:output_dir]}/#{$options[:target]}_workspace"
$cfg = "#{$dir}/#{$options[:target]}.cfg"
$pdf = "#{$options[:output_dir]}/#{$options[:target]}.pdf"

%x{rm -rf #{$dir}}
%x{mkdir -p #{$dir}}
%x{doxygen -s -g #{$cfg} >/dev/null}
raise "doxygen failed with exit code $?" if $? != 0
%x{sed -i -e "s|\\(\\bPROJECT_NAME\\b.*=\\).*|\\1 \\"#{$options[:name]}\\"|"     #{$cfg}}
%x{sed -i -e "s|\\(\\bINPUT\\b.*=\\).*|\\1 #{$options[:files].join(" ")}|"       #{$cfg}}
%x{sed -i -e 's|\\(\\bPREDEFINED\\b.*=\\).*|\\1 #{$options[:defs].join(" ")}|'   #{$cfg}}
%x{sed -i -e 's|\\(\\bINCLUDE_PATH\\b.*=\\).*|\\1 #{$options[:incl].join(" ")}|' #{$cfg}}
%x{sed -i -e "s|\\(\\bOUTPUT_DIRECTORY\\b.*=\\).*|\\1 #{$dir}|"                  #{$cfg}}
%x{sed -i -e "s|\\(\\bFULL_PATH_NAMES\\b.*=\\).*|\\1 YES|"                       #{$cfg}}
%x{sed -i -e "s|\\(\\bSTRIP_FROM_PATH\\b.*=\\).*|\\1 #{$TOP}|"                   #{$cfg}}
%x{sed -i -e "s|\\(\\bWARN_NO_PARAMDOC\\b.*=\\).*|\\1 YES|"                      #{$cfg}}
%x{sed -i -e "s|\\(\\bOPTIMIZE_OUTPUT_FOR_C\\b.*=\\).*|\\1 YES|"                 #{$cfg}}
%x{sed -i -e "s|\\(\\bSOURCE_BROWSER\\b.*=\\).*|\\1 YES|"                        #{$cfg}}
%x{sed -i -e "s|\\(\\bDISTRIBUTE_GROUP_DOC\\b.*=\\).*|\\1 YES|"                  #{$cfg}}
%x{sed -i -e "s|\\(\\bPDF_HYPERLINKS\\b.*=\\).*|\\1 YES|"                        #{$cfg}}
%x{sed -i -e "s|\\(\\bUSE_PDFLATEX\\b.*=\\).*|\\1 YES|"                          #{$cfg}}
%x{sed -i -e "s|\\(\\bLATEX_BATCHMODE\\b.*=\\).*|\\1 YES|"                       #{$cfg}}
%x{sed -i -e "s|\\(\\bEXTRACT_ALL\\b.*=\\).*|\\1 NO|"                            #{$cfg}}
%x{sed -i -e "s|\\(\\bSORT_MEMBER_DOCS\\b.*=\\).*|\\1 NO|"                       #{$cfg}}
%x{sed -i -e "s|\\(\\bDOT_GRAPH_MAX_NODES\\b.*=\\).*|\\1 200|"                   #{$cfg}}
%x{doxygen #{$cfg} >/dev/null}


# There is a bug in pdflatex that shows itself whenever a
# hyperlink is split across two pages. An example is very long
# enums (e.g. vtss_target_type_t), that are likely to get split.
# To overcome this, a page break is inserted just before the
# troublesome construct directly in the generated tex file.
# When the bug appears, "make" returns Error 2 from "make doxygen".
# Have a look at refman.log to find the page in the PDF (that doesn't get
# created) on which the error occurs. Then create the PDF by using
# the following construct in refman.tex: \usepackage[...,draft,...]{hyperref}
# and look at the generated PDF. Once found, add a rule in the
# insert_pagebreak() "function" below, that inserts \newpage
# at the beginning of the line.
# Useful links:
#   How to debug the problem:                http://tug.org/pipermail/pdftex/2002-February/002216.html
#   How to insert a page break in Tex files: http://stackoverflow.com/questions/22601053/pagebreak-in-markdown-while-creating-pdf
# %x{sed -i -e "s|^\(enum.*vtss\\\\-\\\\_\\\\-target\\\\-\\\\_\\\\-type\\\\-\\\\_\\\\-t\}.*\)|\\\\newpage \1|" #{$dir}/latex/vtss__init__api_8h.tex}

# Seen issue with the the Makefile for Latex just exits with error code 2 (no
# other indication of what is wrong). Changing the latex count is the fix.
%x{sed -i -- "s/latex_count=[0-9]\{1,\}/latex_count=40/g" #{$dir}/latex/Makefile}
%x{make -j1 -C #{$dir}/latex 1>/dev/null 2>/dev/null}
raise "pdflatex failed with exit code $?" if $? != 0
%x{mv #{$dir}/latex/refman.pdf #{$pdf}}
%x{rm -rf #{$dir}}

