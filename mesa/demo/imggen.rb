#!/usr/bin/env ruby
# Copyright (c) 2004-2019 Microsemi Corporation "Microsemi".
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

require 'optparse'
require 'open3'
require 'pp'

$machines = {
    "ls1046a" => {
        :bsp_base => "../../ls1046",
        :arch => "arm64",
        :kernel => "ls1046-kernel.img",
        :kerneladdr => "<0x80080000>",
        :kernelentry => "<0x80080000>",
        :ramdiscaddr => "<0x88080000>",
        :kcomp => "gzip",
        :dt => [
            { :name => "pcb134", :file => "mscc-ls1046a-jaguar2-pcb110.dtb"},
        ],
        :fdtaddr => "<0x90000000>",
        :rootfs => "rootfs.tar",
    },

    "fireant" => {
        :bsp_base => "../../fireant",
        :arch => "arm64",
        :kernel => "fireant-kernel.img",
        :kerneladdr => "/bits/ 64 <0x700080000>",
        :kernelentry => "/bits/ 64 <0x700080000>",
        :kcomp => "gzip",
        :dt => [
            { :name => "pcb134",      :file => "fireant_pcb134.dtb"},
            { :name => "pcb135",      :file => "fireant_pcb135.dtb"},
            { :name => "pcb135_emmc", :file => "fireant_pcb135_emmc.dtb"},
        ],
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :rootfs => "rootfs.tar",
    },

    "BeagleBoneBlack" => {
        :bsp_base => "../../bbb",
        :arch => "arm",
        :kernel => "bbb-kernel.img",
        :kerneladdr => "<0x80080000>",
        :kernelentry => "<0x80080000>",
        :ramdiscaddr => "<0x88080000>",
        :kcomp => "gzip",
        :dt => [
            { :name => "pcb134", :file => "am335x-boneblack-mscc.dtb"},
        ],
        :fw_env => "/dev/mmcblk1 0x260000 0x20000\n/dev/mmcblk1 0x280000 0x20000\n",
        :rootfs => "rootfs.tar",
    },

    "luton10" => {
        :socfam => "luton26",
        :chipno => "2",
        :kernel => "mipsel-mips32r2-linux-uclibc/luton26/mscc-linux-luton26.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "luton26" => {
        :socfam => "luton26",
        :chipno => "2",
        :kernel => "mipsel-mips32r2-linux-uclibc/luton26/mscc-linux-luton26.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "serval1" => {
        :socfam => "serval1",
        :chipno => "4",
        :kernel => "mipsel-mips32r2-linux-uclibc/serval1/mscc-linux-serval1.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "jaguar2" => {
        :socfam => "jaguar2",
        :chipno => "5",
        :kernel => "mipsel-mips32r2-linux-uclibc/jaguar2/mscc-linux-jaguar2.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "serval2" => {
        :socfam => "jaguar2",
        :chipno => "7",
        :kernel => "mipsel-mips32r2-linux-uclibc/serval2/mscc-linux-serval2.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "servalt" => {
        :socfam => "servalt",
        :chipno => "6",
        :kernel => "mipsel-mips32r2-linux-uclibc/servalt/mscc-linux-servalt.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "jaguar2c" => {
        :socfam => "jaguar2",
        :chipno => "7",
        :kernel => "mipsel-mips32r2-linux-uclibc/jaguar2c/mscc-linux-jaguar2c.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },

    "ocelot" => {
        :socfam => "ocelot",
        :chipno => "8",
        :kernel => "mipsel-mips32r2-linux-uclibc/ocelot/mscc-linux-ocelot.bin.xz",
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :bsp_base => "../../..",
        :rootfs => "mipsel-mips32r2-linux-gnu/smb/rootfs.tar",
    },
}

$o = {
    :install => [],
    :symlink => [],
}

$op = OptionParser.new do |opts|
    opts.banner = "Usage: ..."

    opts.on("-n,--name NAME", "Name") do |n|
        $o[:name] = n
    end

    opts.on("-m,--machine MACHINE-NAME", "Machine name") do |m|
        $o[:machine] = m
        $m = $machines[m]
    end

    opts.on("-b,--bsp PATH", "BSP Path") do |p|
        $o[:bsp] = p
    end

    opts.on("-t,--type IMAGE-TYPE", "Image type to install") do |t|
        $o[:type] = t
    end

    opts.on("-i,--install FILE", "Install target") do |i|
        $o[:install] << i
    end

    opts.on("-s,--strip FILE", "strip command") do |i|
        $o[:strip] = i
    end

    opts.on("-l,--symlink LINK", "Create symlink on target") do |i|
        $o[:symlink] << i
    end

    opts.on("-p,--src-path PATH", "Source path") do |i|
        $o[:src] = i
    end

    opts.on("-h", "--help", "Prints this help") do
        puts opts
        exit
    end
end.parse!

#pp $o

if $o[:name].nil? or $o[:machine].nil? or $o[:bsp].nil? or $o[:type].nil? or $m.nil?
    puts "Invalid options"
    exit 1
end

$bsp = "#{$o[:bsp]}/#{$m[:bsp_base]}"

def sys cmd, input = nil
    exception = nil
    raise "IMGGEN: #{$o[:name]}> Input file: #{input} does not exists!!!" if input and (not File.exists? input)

    begin
      stdout, stderr, status = Open3.capture3(cmd)
    rescue => e
        exception = e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t")
    end

    if status.to_i != 0
        s = "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n"
        s += "TARGET #{$o[:name]}\n"
        begin
            wstdout, wstderr, wstatus = Open3.capture3("which #{cmd.split(" ")[0]}")
            s += "WHICH-OUT: #{wstdout.chomp}\n" if wstdout.chomp.size > 0
            s += "WHICH-ERR: #{wstderr.chomp}\n" if wstderr.chomp.size > 0
        rescue
        end

        begin
            wstdout, wstderr, wstatus = Open3.capture3("ls -la")
            s += "LS-OUT: #{wstdout.chomp}\n" if wstdout.chomp.size > 0
            s += "LS-ERR: #{wstderr.chomp}\n" if wstderr.chomp.size > 0
        rescue
        end

        s += "CMD: #{cmd}\n"
        if exception
            s += "BACKTRACE:\n"
            s += exception
            s += "\n"
        else
            s += "CMD FAILED (#{status})\n"
            s += "STDOUT:\n"
            s += "#{stdout}\n"
            s += "STDERR:\n"
            s += "#{stderr}\n"
        end
        if input
            if File.exists? input
                s += "INPUT-FILE-EXISTS: #{input}\n"
            else
                s += "INPUT-FILE-NO-EXISTS: #{input}\n"
            end
        else
            s += "NO-INPUT-FILE\n"
        end
        s += "PATH: #{ENV["PATH"]}\n"
        s += "PWD: #{Dir.pwd}\n"
        s += ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n\n"


        # Try to get the message out on the console without mix it with other
        # annoying output...
        begin
            n = File.expand_path(__FILE__) + ".lock"
            f = File.open(n, File::CREAT)
            f.flock(File::LOCK_EX)
        rescue
        end

        STDERR.puts s
        sleep 1

        begin
            f.flock(File::LOCK_UN)
        rescue
        end

        raise s
    end
end

def dts path, machine, ramdisk
    s  = "/dts-v1/\n;"
    s += "/ {\n"
    s += "        description = \"Image file for the MESA SDK Demo on target #{machine}\";\n"
    s += "\n"
    s += "        images {\n"
    s += "                kernel {\n"
    s += "                        description = \"Linux kernel\";\n"
    s += "                        data = /incbin/(\"#{$m[:kernel]}\");\n"
    s += "                        type = \"kernel\";\n"
    s += "                        arch = \"#{$m[:arch]}\";\n"
    s += "                        os = \"linux\";\n"
    s += "                        compression = \"#{$m[:kcomp]}\";\n"
    s += "                        load = #{$m[:kerneladdr]};\n"
    s += "                        entry = #{$m[:kernelentry]};\n"
    s += "                };\n"
    s += "                ramdisk {\n"
    s += "                        description = \"ramdisk\";\n"
    s += "                        data = /incbin/(\"#{ramdisk}\");\n"
    s += "                        type = \"ramdisk\";\n"
    s += "                        arch = \"#{$m[:arch]}\";\n"
    s += "                        os = \"linux\";\n"
    s += "                        load = #{$m[:ramdiscaddr]};\n" if $m[:ramdiscaddr]
    s += "                        compression = \"none\";\n"
    s += "                };\n"
    $m[:dt].each do |d|
        s += "                fdt_#{d[:name]} {\n"
        s += "                        description = \"Flattened Device Tree blob\";\n"
        s += "                        data = /incbin/(\"#{$bsp}/#{d[:file]}\");\n"
        s += "                        type = \"flat_dt\";\n"
        s += "                        arch = \"#{$m[:arch]}\";\n"
        s += "                        load = #{$m[:fdtaddr]};\n" if $m[:fdtaddr]
        s += "                        compression = \"none\";\n"
        s += "                };\n"
    end
    s += "        };\n"
    s += "        configurations {\n"
    s += "                default = \"#{$m[:dt][0][:name]}\";\n"
    $m[:dt].each do |d|
        s += "                #{d[:name]} {\n"
        s += "                        description = \"Boot Linux kernel with DT #{d[:name]}\";\n"
        s += "                        kernel = \"kernel\";\n"
        s += "                        fdt = \"fdt_#{d[:name]}\";\n"
        s += "                        ramdisk = \"ramdisk\";\n"
        s += "                };\n"
    end
    s += "        };\n"
    s += "};\n"

    IO.write path, s
end

def strip from, to
    sys "mkdir -p #{File.dirname(to)}"
    sys "#{$o[:strip]} -o #{to} #{from}", from
end

def tar from, to
    sys "tar -C #{to} -xf #{from}", from
end

def install file, base_dir
    dst_d = nil
    dst_f = nil
    src_f = ""

    if file =~ /(.*)@(.*)/
        src_f = $1
        dst = $2

        if dst.include? '/'
            if dst[-1] == '/'
                dst_f = File.basename(src_f)
                dst_d = dst

            elsif dst[-2..-1] == "/."
                dst_f = File.basename(src_f)
                dst_d = "#{File.dirname(dst)}/"

            else
                dst_f = File.basename(dst)
                dst_d = "#{File.dirname(dst)}/"

            end

        else
            dst_f = dst
        end
    else
        src_f = file
        dst_f = File.basename(src_f)
    end

    if dst_d.nil?
        case File.extname(dst_f)
        when ".so"
            dst_d = "/usr/lib"

        else
            if File.executable? src_f
                dst_d = "/usr/bin/"
            else
                raise "Not sure where to put #{file}"
            end

        end
    end

    if File.directory?(src_f)
        #puts "INSTALL_DIR: #{src_f}  ->  #{base_dir}"
        sys "tar -C #{src_f} -cf - . | tar -C #{base_dir} -xf -"
    else
        #puts "INSTALL: #{src_f}  ->  #{base_dir}/#{dst_d}/#{dst_f}"
        sys "mkdir -p #{base_dir}/#{dst_d}"
        if File.executable? src_f
            strip src_f, "#{base_dir}/#{dst_d}/#{dst_f}"
        else
            sys "cp #{src_f} #{base_dir}/#{dst_d}/#{dst_f}", src_f
        end
    end
end

def basic_rootfs install_dir
    sys "rm -rf #{install_dir}"
    sys "mkdir -p #{install_dir}"
    tar("#{$bsp}/#{$m[:rootfs]}", install_dir)

    IO.write("#{install_dir}/etc/fw_env.config", $m[:fw_env]) if $m[:fw_env]

    sys "mkdir -p #{install_dir}/etc/init.pool"
    sys "mv #{install_dir}/etc/init.d/*             #{install_dir}/etc/init.pool/."
    sys "mv #{install_dir}/etc/init.pool/rcS        #{install_dir}/etc/init.d/."
    sys "mv #{install_dir}/etc/init.pool/rcK        #{install_dir}/etc/init.d/."
    sys "mv #{install_dir}/etc/init.pool/S01syslogd #{install_dir}/etc/init.d/."
    sys "mv #{install_dir}/etc/init.pool/S02klogd   #{install_dir}/etc/init.d/."

    $o[:install].each do |i|
        install i, install_dir
    end

    $o[:symlink].each do |l|
        if l =~ /(.*)@(.*)/
            sys "ln -s #{$1} #{install_dir}/#{$2}"
        end
    end
end

case $o[:type]
when "fit"
    # This is a simple DTB with a kernel, DT(s) and rootfs
    install_dir = "install_#{$o[:name]}"
    basic_rootfs install_dir
    sys "rm -rf #{$o[:name]}.squashfs"
    sys "mksquashfs #{install_dir}/* #{$o[:name]}.squashfs -no-progress -quiet -comp xz -all-root"

    dts "#{$o[:name]}.its", $o[:machine], "#{$o[:name]}.squashfs"
    sys "mkimage -q -f #{$o[:name]}.its #{$o[:name]}.itb"

when "ext4"
    # The rootfs is prepated, and converted to an ext4 image. Inside the ext4
    # image, we create a /boot folder with a fit image. This fit image contains
    # the kernel, DT(s) and a initrd to do the initial mounting.
    install_dir = "install_#{$o[:name]}_ext4"
    stage1_dir = "install_#{$o[:name]}_initrd"
    sys "rm -rf #{stage1_dir} #{$o[:name]}.ext4 #{$o[:name]}.ext4.gz #{$o[:name]}_initrd.squashfs"

    basic_rootfs install_dir
    sys "mkdir -p #{install_dir}/boot"

    sys "mkdir -p #{stage1_dir}/sbin"
    sys "mkdir -p #{stage1_dir}/dev"
    sys "mkdir -p #{stage1_dir}/proc"
    sys "mkdir -p #{stage1_dir}/sys"
    sys "mkdir -p #{stage1_dir}/mnt"
    strip "init", "#{stage1_dir}/sbin/init"

    sys "mksquashfs #{stage1_dir}/* #{$o[:name]}_initrd.squashfs -no-progress -quiet -comp xz -all-root"
    dts "#{$o[:name]}_ext4.its", $o[:machine], "#{$o[:name]}_initrd.squashfs"
    sys "mkimage -q -f #{$o[:name]}_ext4.its #{install_dir}/boot/img.itb"

    sys "touch #{$o[:name]}.ext4"
    sys "truncate -s 1G #{$o[:name]}.ext4"
    sys "mkfs.ext4 -q -E root_owner -d #{install_dir} #{$o[:name]}.ext4"
    sys "resize2fs -M #{$o[:name]}.ext4"
    sys "gzip #{$o[:name]}.ext4"

when "mfi"
    install_dir = "install_#{$o[:name]}"
    basic_rootfs install_dir
    sys "rm -rf #{$o[:name]}.squashfs"
    sys "mksquashfs #{install_dir}/* #{$o[:name]}.squashfs -no-progress -quiet -comp xz -all-root"

    c = "#{$bsp}/mipsel-mips32r2-linux-uclibc/serval1/x86_64-linux/bin/mfi.rb"
    c += " -o #{$o[:name]}.mfi"
    c += " stage1"
    c += " --kernel-set #{$bsp}/#{$m[:kernel]}"
    c += " --initrd-set #{$o[:name]}.squashfs"
    c += " --kernel-command \"init=/sbin/init loglevel=4\""
    c += " --machine #{$o[:machine]}"
    c += " --soc-name #{$m[:socfam]} ${MFI_SOCFAM}"
    c += " --soc-no #{$m[:chipno]} ${MFI_CHIPNO}"

    sys c
else
    raise "Image type: #{$o[:type]} not supported"

end

