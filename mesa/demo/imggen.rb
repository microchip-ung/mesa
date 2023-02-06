#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'optparse'
require 'open3'
require 'pp'


$mfi = "#{File.expand_path(File.dirname(__FILE__))}/mfi.rb"

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

$p_mesa = File.expand_path "#{$o[:src]}/../../"
$bsp = File.expand_path $o[:bsp]
#puts "BSP-TOP: #{$bsp}"
#puts "MESA-TOP: #{$p_mesa}"

$machines = {
    "ls1046a" => {
        :arch => "arm64",
        :kernel => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/mscc-linux-kernel.bin.xz",
        :kerneladdr => "<0x80080000>",
        :kernelentry => "<0x80080000>",
        :ramdiscaddr => "<0x88080000>",
        :kcomp => "gzip",
        :dt => [
          {
            :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/mchp-ls1046a-lan966x_vtss.dtb",
            :overlays => [
                { :name => "6813_0@ls1046a", :file => "#{$p_mesa}/meba/dt/meba_lan966x_6813_0.dtso"},
                # { :name => "6849_0@ls1046a", :file => "#{$p_mesa}/meba/dt/meba_lan966x_6849_0.dtso"},
                { :name => "8290_0@ls1046a", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8290_0.dtso"},
                { :name => "8291_0@ls1046a", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8291_0.dtso"},
                { :name => "8309_0@ls1046a", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8309_0.dtso"},
            ]
          },
        ],
        :fdtaddr => "<0x90000000>",
        :rootfs => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/rootfs.tar",
    },

    "lan966x" => {
        :arch => "arm",
        :kernel => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/mscc-linux-kernel.bin.gz",
        :kerneladdr  => "<0x60208000>",
        :kernelentry => "<0x60208000>",
        :ramdiscaddr => "<0x68000000>",
        :kcomp => "gzip",
        :dt => [
          {
            :file => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/lan966x-mesa-pcb8291.dtb",
            :overlays => [
                { :name => "lan9662_ung8291_0_at_lan966x", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8291_0.dtso"},
            ]
          },
          {
            :file => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/lan966x-mesa-pcb8309.dtb",
            :overlays => [
                { :name => "lan9662_ung8309_0_at_lan966x", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8309_0.dtso"},
            ]
          },
          {
            :file => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/lan966x-mesa-pcb8290.dtb",
            :overlays => [
                { :name => "lan9668_ung8290_0_at_lan966x", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8290_0.dtso"},
            ]
          },
          {
            :file => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/lan966x-mesa-pcb8281.dtb",
            :overlays => [
                { :name => "lan9668_ung8281_0_at_lan966x", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8281_0.dtso"},
            ]
          },
        ],
        :fdtaddr => "<0x67e00000>",
        :rootfs => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/rootfs.tar",
    },

    "fireant" => {
        :arch => "arm64",
        :kernel => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/mscc-linux-kernel.bin.gz",
        :kerneladdr => "/bits/ 64 <0x700080000>",
        :kernelentry => "/bits/ 64 <0x700080000>",
        :kcomp => "gzip",
        :dt => [
            { :name => "pcb125",        :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/sparx5_pcb125.dtb"},
            { :name => "pcb134",        :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/sparx5_appl_pcb134.dtb"},
            { :name => "pcb134_emmc",   :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/sparx5_appl_pcb134_emmc.dtb"},
            { :name => "pcb135",        :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/sparx5_appl_pcb135.dtb"},
            { :name => "pcb135_emmc",   :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/sparx5_appl_pcb135_emmc.dtb"},
            { :name => "ls1046_pcb134", :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/ls1046_pcb134.dtb"},
        ],
        :fw_env => "/dev/mtd1 0x0000 0x2000 0x40000\n/dev/mtd2 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/rootfs.tar",
    },

    "ocelot_pcb121" => {
        :arch => "arm64",
        :kernel => "#{$bsp}/arm64-armv8_a-linux-gnu/standalone/release/mscc-linux-kernel.bin.gz",
        :kerneladdr => "<0x80080000>",
        :kernelentry => "<0x80080000>",
        :ramdiscaddr => "<0x88080000>",
        :kcomp => "gzip",
        :dt => [
            { :name => "ls1046_pcb121", :file => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/ls1046_pcb121.dtb"},
        ],
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :fdtaddr => "<0x90000000>",
        :rootfs => "#{$bsp}/arm64-armv8_a-linux-gnu/xstax/release/rootfs.tar",
    },

    "BeagleBoneBlack" => {
        :arch        => "arm",
        :kernel      => "#{$bsp}/arm-cortex_a8-linux-gnu/standalone/release/mscc-linux-kernel.bin.gz",
        :kerneladdr  => "<0x80080000>",
        :kernelentry => "<0x80080000>",
        :ramdiscaddr => "<0x88080000>",
        :kcomp => "gzip",
        :dt => [
            {
              :name => "pcb134",
              :file => "#{$bsp}/arm-cortex_a8-linux-gnu/standalone/release/am335x-boneblack-mscc.dtb"
            },
            {
              :file => "#{$bsp}/arm-cortex_a8-linux-gnu/standalone/release/am335x-boneblack-mscc.dtb",
              :overlays => [
                  { :name => "6813_0@bbb", :file => "#{$p_mesa}/meba/dt/meba_lan966x_6813_0.dtso"},
                  { :name => "6849_0@bbb", :file => "#{$p_mesa}/meba/dt/meba_lan966x_6849_0.dtso"},
                  { :name => "8290_0@bbb", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8290_0.dtso"},
                  { :name => "8291_0@bbb", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8291_0.dtso"},
                  { :name => "8309_0@bbb", :file => "#{$p_mesa}/meba/dt/meba_lan966x_8309_0.dtso"},
              ]
            },
        ],
        :fw_env => "/dev/mmcblk1 0x260000 0x20000\n/dev/mmcblk1 0x280000 0x20000\n",
        :rootfs => "#{$bsp}/arm-cortex_a8-linux-gnu/xstax/release/rootfs.tar",
    },

    "luton_pcb090" => {
        :socfam => "luton26",
        :chipno => "2",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/luton_pcb090.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "luton_pcb091" => {
        :socfam => "luton26",
        :chipno => "2",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/luton_pcb091.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "serval2_pcb112" => {
        :socfam => "jaguar2",
        :chipno => "7",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/serval2_pcb112.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "servalt_pcb116" => {
        :socfam => "servalt",
        :chipno => "6",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/servalt_pcb116.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "jaguar2_pcb110" => {
        :socfam => "jaguar2",
        :chipno => "7",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/jaguar2_pcb110.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "jaguar2_pcb111" => {
        :socfam => "jaguar2",
        :chipno => "7",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/jaguar2_pcb111.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "ocelot_pcb120" => {
        :socfam => "ocelot",
        :chipno => "8",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/ocelot_pcb120.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },

    "ocelot_pcb123" => {
        :socfam => "ocelot",
        :chipno => "8",
        :kernel => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/mscc-linux-kernel.bin",
        :dtb    => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/ocelot_pcb123.dtb",
        :fw_env => "/dev/mtd2 0x0000 0x2000 0x40000\n/dev/mtd3 0x0000 0x2000 0x40000\n",
        :rootfs => "#{$bsp}/mipsel-mips32r2-linux-gnu/xstax/release/rootfs.tar",
    },
}


if $o[:machine]
    $m = $machines[$o[:machine]]
end


if $o[:name].nil? or $o[:machine].nil? or $o[:bsp].nil? or $o[:type].nil? or $m.nil?
    puts "Invalid options"
    exit 1
end

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

def dts path, machine, machine_name, ramdisk
    kernel = "#{machine[:kernel]}"
    if File.extname(kernel) == ".xz"
        o = "./#{File.basename(kernel)}.gz"
        sys "xz -d -c #{kernel} | gzip -f -c > #{o}"
        kernel = o
    end

    s  = "/dts-v1/\n;"
    s += "/ {\n"
    s += "        description = \"Image file for the MESA SDK Demo on target #{machine_name}\";\n"
    s += "\n"
    s += "        images {\n"
    s += "                kernel {\n"
    s += "                        description = \"Linux kernel\";\n"
    s += "                        data = /incbin/(\"#{kernel}\");\n"
    s += "                        type = \"kernel\";\n"
    s += "                        arch = \"#{machine[:arch]}\";\n"
    s += "                        os = \"linux\";\n"
    s += "                        compression = \"#{machine[:kcomp]}\";\n"
    s += "                        load = #{machine[:kerneladdr]};\n"
    s += "                        entry = #{machine[:kernelentry]};\n"
    s += "                };\n"
    s += "                ramdisk {\n"
    s += "                        description = \"ramdisk\";\n"
    s += "                        data = /incbin/(\"#{ramdisk}\");\n"
    s += "                        type = \"ramdisk\";\n"
    s += "                        arch = \"#{machine[:arch]}\";\n"
    s += "                        os = \"linux\";\n"
    s += "                        load = #{machine[:ramdiscaddr]};\n" if machine[:ramdiscaddr]
    s += "                        compression = \"none\";\n"
    s += "                };\n"
    machine[:dt].each do |d|
        s += "                fdt_#{d[:name]} {\n"
        s += "                        description = \"Flattened Device Tree blob\";\n"
        s += "                        data = /incbin/(\"#{d[:file]}\");\n"
        s += "                        type = \"flat_dt\";\n"
        s += "                        arch = \"#{machine[:arch]}\";\n"
        s += "                        load = #{machine[:fdtaddr]};\n" if machine[:fdtaddr]
        s += "                        compression = \"none\";\n"
        s += "                };\n"
    end
    s += "        };\n"
    s += "        configurations {\n"
    s += "                default = \"#{machine[:dt][0][:name]}\";\n"
    machine[:dt].each do |d|
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

def dts_process_overlays name, machine
    return machine if machine[:dt].nil?

    new_dt_array = []
    machine[:dt].each do |dt_entry|
        dtb = dt_entry[:file]
        dtb_basename = File.basename(dtb)

        if dt_entry[:overlays]
            dt_entry[:overlays].each do |dto_entry|
                out_dtbo = "#{$o[:name]}_#{name}_#{File.basename(dto_entry[:file], ".dtso")}.dtbo"
                out = "#{$o[:name]}_#{dtb_basename}_#{File.basename(dto_entry[:file], ".dtso")}.dtb"
                sys "dtc -o #{out_dtbo} #{dto_entry[:file]}"
                sys "fdtoverlay -i #{dtb} -o #{out} #{out_dtbo}"
                new_dt_array << { :name => dto_entry[:name], :file => out }
            end
        else
            new_dt_array << dt_entry
        end

    end

    m = machine.clone
    m[:dt] = new_dt_array

    return m
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
    tar("#{$m[:rootfs]}", install_dir)

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
    sys "mksquashfs #{install_dir}/* #{$o[:name]}.squashfs -no-progress -quiet -all-root"

    m = dts_process_overlays $o[:machine], $m
    dts "#{$o[:name]}.its", m, $o[:machine], "#{$o[:name]}.squashfs"
    puts "mkimage -q -f #{$o[:name]}.its #{$o[:name]}.itb"
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

    m = dts_process_overlays $o[:machine], $m
    sys "mksquashfs #{stage1_dir}/* #{$o[:name]}_initrd.squashfs -no-progress -quiet -comp xz -all-root"
    dts "#{$o[:name]}_ext4.its", m, $o[:machine], "#{$o[:name]}_initrd.squashfs"
    sys "mkimage -q -f #{$o[:name]}_ext4.its #{install_dir}/Image.itb"

    t1 = Thread.new {
        sys "touch #{$o[:name]}.ext4"
        sys "truncate -s 1G #{$o[:name]}.ext4"
        sys "mkfs.ext4 -q -E root_owner -d #{install_dir} #{$o[:name]}.ext4"
        sys "resize2fs -M #{$o[:name]}.ext4"
        sys "gzip #{$o[:name]}.ext4"
    }

    t2 = Thread.new {
        sys "mkfs.ubifs -r #{install_dir} -m 2048 -e 124KiB -c 512 -o #{$o[:name]}.ubifs"
    }

    t1.join
    t2.join

when "mfi"
    install_dir = "install_#{$o[:name]}"
    basic_rootfs install_dir
    sys "rm -rf #{$o[:name]}.squashfs"
    sys "mksquashfs #{install_dir}/* #{$o[:name]}.squashfs -no-progress -quiet -comp xz -all-root"
    sys "cp #{$m[:kernel]} kernel_#{$o[:name]}"
    sys "rm -f kernel_#{$o[:name]}.xz"
    sys "cat #{$m[:dtb]} >> kernel_#{$o[:name]}"
    sys "xz --check=crc32 --lzma2=preset=6e,dict=64KiB kernel_#{$o[:name]}"

    c = $mfi
    c += " -o #{$o[:name]}.mfi"
    c += " stage1"
    c += " --kernel-set kernel_#{$o[:name]}.xz"
    c += " --initrd-set #{$o[:name]}.squashfs"
    c += " --kernel-command \"init=/sbin/init loglevel=4\""
    c += " --machine #{$o[:machine]}"
    c += " --soc-name #{$m[:socfam]} ${MFI_SOCFAM}"
    c += " --soc-no #{$m[:chipno]} ${MFI_CHIPNO}"

    sys c
else
    raise "Image type: #{$o[:type]} not supported"

end

