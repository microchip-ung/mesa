#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

def sys cmd
    puts cmd
    system cmd
    raise "Running '#{cmd}' failed" if $? != 0
end

raise if ARGV.size != 1

$v = ARGV[0]
$dest_dir = path = File.expand_path(File.dirname(__FILE__))

if File.exist? "/easytest/local/install/ef/#{$v}/usr/local/bin/ef"
    sys "ln -fs /easytest/local/install/ef/#{$v}/usr/local/bin/ef #{$dest_dir}/ef"
    sys "ln -fs /easytest/local/install/ef/#{$v}/usr/local/bin/ef /usr/local/bin/ef"
    exit 0
end

# TODO, lock file to ensure 1-at-a-time

$git_cache = "/easytest/local/git-cache/ef"
$src_dir = "/easytest/local/git/ef"

sys "mkdir -p /easytest/local/git-cache/"
sys "mkdir -p /easytest/local/git/"

def ef_clone_
    if File.exist?($git_cache)
        sys "cd #{$git_cache} && git fetch"
    else
        sys "cd /easytest/local/git-cache/ && git clone --quiet --bare --mirror https://github.com/microchip-ung/easyframes.git ef"
    end

    sys "git clone --quiet #{$git_cache} #{$src_dir}" if not File.exist?($src_dir)
    sys "cd #{$src_dir} && git reset --hard #{$v}"
    sys "cd #{$src_dir} && git clean -ffdx"
end

def ef_clone
    begin
        ef_clone_
        return
    rescue
        sys "rm -rf #{$git_cache} #{$src_dir}"
    end

    ef_clone_
end

ef_clone

sys "mkdir -p #{$src_dir}/build"
Dir.chdir "#{$src_dir}/build"

sys "cmake .."
sys "make -j12"
sys "make DESTDIR=/easytest/local/install/ef/#{$v} install"
sys "ln -fs /easytest/local/install/ef/#{$v}/usr/local/bin/ef #{$dest_dir}/ef"
sys "ln -fs /easytest/local/install/ef/#{$v}/usr/local/bin/ef /usr/local/bin/ef"

exit 0

