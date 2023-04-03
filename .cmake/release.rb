#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'open3'
require 'thread'
require 'optparse'
require 'fileutils'
require 'yaml'
require_relative "./resultnode.rb"

$have_internal_tools = true
$do_internal_checks = false
$do_compile = true
begin
    require_relative "./licenses.rb"
rescue
    $have_internal_tools = false
rescue LoadError
    $have_internal_tools = false
end

$rvm_ruby = "ruby"
$rvm_ruby = "#{ENV["HOME"]}/.rvm/wrappers/ruby-2.6.2/ruby" if File.file?("#{ENV["HOME"]}/.rvm/wrappers/ruby-2.6.2/ruby")
$rvm_ruby = "/usr/local/rvm/wrappers/ruby-2.6.2/ruby" if File.file?("/usr/local/rvm/wrappers/ruby-2.6.2/ruby")

$mutex = Mutex.new

$top = File.dirname(File.dirname(File.expand_path(__FILE__)))
Dir.chdir($top)

$yaml = YAML.load_file("#{$top}/.cmake/release.yaml")
$presets = (YAML.load_file("#{$top}/.cmake/cmake-presets.yaml"))["presets"]

def run_(cmd)
    system cmd
    raise "Running '#{cmd}' failed" if $? != 0
end

$ws = "release_ws"
run_ "rm -rf #{$ws} images"
run_ "mkdir -p #{$ws} images"

def log(msg)
    system "#{$top}/.cmake/logcmd.rb --log images/build.log --trace \"#{msg}\""
end

def step node, desc
    begin
        yield
        $mutex.synchronize do
            node.addSibling(ResultNode.new(desc, "OK"))
        end
    rescue => e
        $mutex.synchronize do
            node.addSibling(ResultNode.new(desc, "Failed"))
        end

        bt = e.backtrace.join("\n\t").sub("\n\t", ": #{e}#{e.class ? " (#{e.class})" : ''}\n\t")
        puts("Step #{desc} failed -> #{e.message}\n#{bt}\n")
    end
end

def run cmd, comp = nil
    if comp.nil?
        system "#{$top}/.cmake/logcmd.rb --log images/build.log  -- \"#{cmd}\""
    else
        system "#{$top}/.cmake/logcmd.rb --log images/build-#{comp}.log  -- \"#{cmd}\""
    end
    raise "Running '#{cmd}' failed" if $? != 0
end

def get_cmake_toolchain conf
    raise "No toolchain attribute" if conf[:toolchainfile].nil?

    base = "/opt/mscc/"
    if conf[:brsdk]
        base += "mscc-brsdk-#{conf[:arch]}-#{conf[:brsdk]}"
        base += "-#{conf[:brsdk_branch]}" if conf[:brsdk_branch] and conf[:brsdk_branch] != "brsdk"
    else
        base += "mscc-toolchain-bin-#{conf[:toolchain]}"
        base += "-#{conf[:toolchain_branch]}" if conf[:toolchain_branch] != "toolchain"
    end

    return "-DCMAKE_TOOLCHAIN_FILE=/#{base}/#{conf[:toolchainfile]}"
end

def get_cmake conf
    raise "No cmake attribute" if conf[:cmake].nil?

    base = "/opt/mscc/"
    if conf[:brsdk]
        base += "mscc-brsdk-#{conf[:arch]}-#{conf[:brsdk]}"
        base += "-#{conf[:brsdk_branch]}" if conf[:brsdk_branch] and conf[:brsdk_branch] != "brsdk"
    else
        base += "mscc-toolchain-bin-#{conf[:toolchain]}"
        base += "-#{conf[:toolchain_branch]}" if conf[:toolchain_branch] != "toolchain"
    end

    return "#{base}/#{conf[:cmake]}"
end

def get_cmake_options conf
    return "#{conf[:cmake_flags]} -DBUILD_ALL=on "
end

$opt = { }
global = OptionParser.new do |opts|
    opts.banner = "Usage: #{$0}"

    opts.on("-j", "--parallel", "Enable parallel builds for each target") do
        $opt[:parallel] = true
    end

    opts.on("-s", "--simplegrid", "Compile using MSCC simplegrid distributed tool. Enables --parallel also") do
        $opt[:simplegrid] = true
        $opt[:parallel] = true
    end

    opts.on("--no-compile", "Skip the actual compilation - just run all other tests. Implies internal checks") do
      if $have_internal_tools
           $do_internal_checks = true
           $do_compile = false
      end
    end

    if $have_internal_tools
        opts.on("-i", "--internal-checks", "Do checks that requires internal resources") do
            $do_internal_checks = true
        end
    end
end.order!

git_sha = %x(git rev-parse --short HEAD).chop
git_sha_long = %x(git rev-parse HEAD).chop
begin
    git_id = %x(git describe --tags --long).chop
rescue
    git_id = git_sha
end
if ENV['BRANCH_NAME']
    git_branch = ENV['BRANCH_NAME']
else
    git_branch = %x(git symbolic-ref --short -q HEAD).chop
end

out_name = "mesa-#{git_id}@#{git_branch}"

File.open("#{$ws}/.mscc-version", 'w') do |version|
    version.puts(%Q(mesa_sha="#{git_sha}"))
    version.puts(%Q(mesa_id="#{git_id}"))
    version.puts(%Q(mesa_branch="#{git_branch}"))
end

$res = ResultNode.new("API", "OK", {"branch" => git_branch, "sha" => git_sha_long, "name" => git_id})
$res_bin = ResultNode.new("binaries")
$res_lic = ResultNode.new("binaries-licenses")

def compile(ws, odir, preset, c)
    arch = c[:arch]
    cmake = get_cmake(c)
    cmake = "cmake" if cmake.nil? # use system cmake as fallback
    bcmd = "(cd #{ws}; mkdir -p #{odir}; cd #{odir}; "
    if c[:brsdk]
        dw_file = "mscc-brsdk-#{arch}-#{c[:brsdk]}"
        dw_file += "-#{c[:brsdk_branch]}" if c[:brsdk_branch] and c[:brsdk_branch] != "brsdk"
        if c[:brsdk_branch]
            bcmd += "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]}-#{c[:brsdk_branch]} #{dw_file}; "
        else
            bcmd += "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]} #{dw_file}; "
        end
        bcmd += "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{c[:tc_folder]} mscc-toolchain-bin-#{c[:tc]};"
    else
        tc_name = "mscc-toolchain-bin-#{c[:toolchain]}"
        tc_name += "-#{c[:toolchain_branch]}" if c[:toolchain_branch] != "toolchain"
        bcmd += "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{c[:toolchain]}-#{c[:toolchain_branch]} #{tc_name}; "
    end
    if $do_compile
        bcmd += "#{cmake} #{get_cmake_toolchain(c)} #{get_cmake_options(c)} ../.. && #{cmake} ../.. && make -j 10)"
    else
        bcmd += ")"
    end

    if $opt[:simplegrid]
        cmd = "SimpleGridClient -l webstax "
        cmd << "-e MCHP_DOCKER_NAME=\"ghcr.io/microchip-ung/bsp-buildenv\" -e MCHP_DOCKER_TAG=\"1.9\" "
        cmd << "-w #{$tar} "
        cmd << "-c '#{bcmd}' "
        cmd << "-a #{ws}/#{odir} "
        cmd << "-o #{ws}/#{preset}.tar "
        cmd << "--log #{ws}/sg-#{preset}.log "
        cmd << "--meta type=mesa --meta config=#{preset} "
        bcmd = cmd
    end

    step $res_bin, preset do
        run bcmd, preset
        if $opt[:simplegrid]
            otar = "#{ws}/#{preset}.tar"
            run "tar -xf #{otar}"
            run "rm -f #{otar}"
            run "cp #{ws}/sg-#{preset}.log ./images/."
        end
    end

    if $do_internal_checks
        step $res_lic, preset do
            legal_bsp = nil
            legal_tc = nil

            if c[:brsdk] and c[:legal]
                v  = "mscc-brsdk-#{c[:arch]}-#{c[:brsdk]}"
                v += "-#{c[:brsdk_branch]}" if c[:brsdk_branch] and c[:brsdk_branch] != "brsdk"
                p  = "/opt/mscc/#{v}/#{c[:legal]}/manifest.csv"
                legal_bsp = {:path => p, :ver => v}

                tc = c[:tc_conf]
                v  = "mscc-toolchain-bin-#{tc["toolchain"]}"
                v += "-#{tc[:toolchain_branch]}" if tc["toolchain_branch"] and tc["toolchain_branch"] != "toolchain"
                p = "/opt/mscc/#{v}/#{c[:brsdk_arch]}/legal-info/manifest.csv"
                legal_tc = {:path => p, :ver => v}
            else
                v = "mscc-toolchain-bin-#{c[:toolchain]}"
                v += "-#{c[:toolchain_branch]}" if c[:toolchain_branch] and c[:toolchain_branch] != "toolchain"
                p = "/opt/mscc/#{v}/#{c[:legal]}/manifest.csv"
                legal_tc = {:path => p, :ver => v}
            end

            licenses_bin(ws, preset, "#{ws}/#{odir}/licenses.txt", legal_bsp, legal_tc, $yaml['conf']['friendly_name_cur'])
        end
    end
end

# Create release note
def release_note()
    run "#{$top}/.cmake/release_note.rb", "release_note"
    $res.addSibling(ResultNode.from_file("#{$top}/#{$yaml['conf']['output_dir']}/#{$yaml['conf']['json_status_release_note']}"))
end

# Check copyrights/licenses
def copyright()
    run "#{$top}/.cmake/copyright.rb", "copyright_check"
    $res.addSibling(ResultNode.new("Copyright", "OK"))
end

# Create licenses.txt file
def licenses_create(ws)
    # Use workspace as top, or the licenses.rb script will find both the
    # .module_info files in the normal repo and the copied repo in #{ws}.
    licenses(ws, "#{ws}/LICENSE", $yaml['conf']['friendly_name_prv'], $yaml['conf']['friendly_name_cur'])
end


# Make source-archive
$tar = "#{$ws}/#{$ws}.tar"
run "git archive --prefix=./#{$ws}/ --format=tar HEAD > #{$tar}"
# Unpack sources for removal of unwanted files into temporary folder
# because we are going to make a tar ball in the parent folder,
# which results in a warning if the source files were in the same folder.
run "mkdir -p #{$ws}/tmp"
run "tar -xmf #{$tar} -C #{$ws}/tmp"

# Make easytest source copy
run "tar -C #{$ws}/tmp/release_ws/mesa/demo/ -cz test -f images/et.tar.gz"

tmp = "#{$ws}/tmp/release_ws"
run "mkdir #{tmp}/build_src"
run "cd #{tmp}/build_src; cmake .."
run "cd #{tmp}/build_src; make -j12 mesa_src mesa_rpc_src"
run "mkdir #{tmp}/mesa/ag"
run "mkdir #{tmp}/mesa/demo/ag"
run "cp #{tmp}/build_src/mesa-ag/mesa.c #{tmp}/build_src/mesa-ag/mesa.h #{tmp}/mesa/ag/."
run "cp #{tmp}/build_src/mesa/demo/mesa-ag/mesa-rpc.c #{tmp}/build_src/mesa/demo/mesa-ag/mesa-rpc.h #{tmp}/mesa/demo/ag/."

# Delete unwanted files
run "rm -rf #{$ws}/tmp/release_ws/.cmake/release* #{$tar}"
run "rm -rf #{$ws}/tmp/release_ws/.cmake/licenses.rb"
run "rm -rf #{$ws}/tmp/release_ws/.cmake/backwards*"
run "rm -rf #{$ws}/tmp/release_ws/.cmake/copyright*"
run "rm -rf #{$ws}/tmp/release_ws/mesa/demo/test"
run "rm -rf #{tmp}/build_src"

# Re-pack
run "tar -C #{$ws}/tmp -cf #{$tar} ./#{$ws}"
run "tar --append -f #{$tar} #{$ws}/.mscc-version"
# And put the sources back where they belong.
# Can't do "mv #{$ws}/tmp/release_ws/* #{$ws}", because that will omit hidden files and folders.
# Can't do "mv #{$ws}/tmp/release_ws/{.,}* #{$ws}" because it will generate warnings.
# Copy everything and rm afterwards works.
run "cp -r #{$ws}/tmp/release_ws/. #{$ws}"
run "rm -rf #{$ws}/tmp"

begin
    copyright()
rescue
    $res.addSibling(ResultNode.new("Copyright", "Failed"))
end

if $do_internal_checks
    begin
        release_note()
        run "cp images/release_note_*.txt #{$ws}"
    rescue
        $res.addSibling(ResultNode.new("Release note", "Failed"))
    end

    begin
        licenses_create($ws)
    rescue
        $res.addSibling(ResultNode.new("LicenseFile", "Failed"))
    end
end

# Build each architecture
FileUtils.mkdir_p($ws)
$workers = []

$presets.each do |preset, c|
    next if not c[:release_artifact]
    arch = c[:arch]
    dw_file = "mscc-brsdk-#{arch}-#{c[:brsdk]}"
    dw_file += "-#{c[:brsdk_branch]}" if c[:brsdk_branch] and c[:brsdk_branch] != "brsdk"

    if c[:brsdk]
        if c[:brsdk_branch]
            run "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]}-#{c[:brsdk_branch]} #{dw_file};"
        else
            run "sudo /usr/local/bin/mscc-install-pkg -t brsdk/#{c[:brsdk]} #{dw_file};"
        end
        tc_conf = YAML.load_file("/opt/mscc/#{dw_file}/.mscc-version")
        tc_folder = tc_conf["toolchain"]
        tc_folder = "#{tc_conf["toolchain"]}-toolchain" if not tc_conf["toolchain"].include? "toolchain"
        c[:tc] = tc_conf["toolchain"]
        c[:tc_conf] = tc_conf
        c[:tc_folder] = tc_folder
        run "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{tc_folder} mscc-toolchain-bin-#{tc_conf["toolchain"]};"

    else
        tc_name = "mscc-toolchain-bin-#{c[:toolchain]}"
        run "sudo /usr/local/bin/mscc-install-pkg -t toolchains/#{c[:toolchain]}-#{c[:toolchain_branch]} #{tc_name}; "
    end

    dir = "bin/#{preset}"
    if($opt[:parallel])
        $workers << Thread.new do
            compile($ws, dir, preset, c)
        end
    else
        compile($ws, dir, preset, c)
    end
end

if($opt[:parallel])
    $workers.map(&:join)
end

$res.addSibling($res_bin)
$res.addSibling($res_lic) if $do_internal_checks

step $res, "Update CapDB" do
    run "./mesa/docs/scripts/capdump.rb -o mesa/docs/capdb.yaml -c mesa/include/microchip/ethernet/switch/api/capability.h -C #{$ws}/bin/x86/capability_dumper #{$ws}/bin/x86/libvsc*.so", "capdb"
    # TODO, check if equal to the one checked into git
    run "cp mesa/docs/capdb.yaml #{$ws}/mesa/docs/capdb.yaml", "capdb"
    run "cp mesa/docs/capdb.yaml images/.", "capdb"
end

step $res, "API Doc" do
    # TODO, check for errors
    rev = $yaml['conf']['friendly_name_cur']
    if /MESA-(.*)/ =~ rev
        rev = $1
    end

    #MESA-Doc
    run "cd mesa/docs/scripts; #{$rvm_ruby} ./dg.rb -r #{rev} -s #{git_sha}", "doc"
    run "cp ./mesa-doc.html images/.", "doc"
    run "cp ./mesa-doc.html #{$ws}/.", "doc"

    #MEPA-Doc
    run "cd mepa/docs/scripts; #{$rvm_ruby} ./dg.rb -r #{rev} -s #{git_sha}", "doc"
    run "cp ./mepa/mepa-doc.html images/.", "doc"
    run "cp ./mepa/mepa-doc.html #{$ws}/.", "doc"

    run "ls", "doc"
end

if File.exists? "./mesa-doc.html"
    %x{"cp -r ./mesa-doc.html images/."}
end

# Clean up the binary artifacts
FileUtils.rm("#{$tar}")
Dir["#{$ws}/bin/**/"].reverse_each do |d|
    n = File.basename(d)

    %x{rm -rf #{d}} if n == "CMakeFiles"
    %x{rm -rf #{d}} if n == "mesa-ag"

    # No sub-directories in mesa/demo
    %x{rm -rf #{d}} if d =~ /mesa\/demo\/./
end

Dir["#{$ws}/bin/**/*"].reverse_each do |e|
    next if File.directory?(e)
    n = File.basename(e)
    ext = File.extname(n)

    if e.include? "linux_kernel_modules"
        if File.extname(n) != ".ko"
            %x{rm #{e}}
        end
    end

    %x{rm -f #{e}} if ext == ".log"
    %x{rm -f #{e}} if ext == ".ar"
    %x{rm -f #{e}} if ext == ".in"
    %x{rm -f #{e}} if n == "Jenkinsfile"
    %x{rm -f #{e}} if n == "CMakeCache.txt"
    %x{rm -f #{e}} if n == "CMakeFiles"
    %x{rm -f #{e}} if n == "cmake_install.cmake"
    %x{rm -f #{e}} if n == "Makefile"
    %x{rm -f #{e}} if n =~ /libmeba_only/

    if e.include? "mesa\/demo"
        case e
        when /\.mfi$/, /\.itb$/, /\.ubifs/, /\.ext4.gz$/
            # Keep it
        else
            %x{rm #{e}}
        end
    end
end

Dir["#{$ws}/**/*"].reverse_each do |e|
    next if File.directory?(e)
    n = File.basename(e)
    ext = File.extname(n)

    %x{rm #{e}} if ext == ".log"
    %x{rm #{e}} if n == "Jenkinsfile"
end

# Preserve backwards compatibility with application
run("ln -s mipsel #{$ws}/bin/mips")

$res.to_file("#{$ws}/status.json")
run("tar -czf images/#{out_name}.tar.gz --exclude '*_workspace' --transform 's,^./#{$ws},./#{out_name},' ./#{$ws}")

$res.to_file("images/status.json")
File.write("images/status.html", $res.tree_view_render)

puts "combined status: #{$res.status}"

# Make MFI and FIT images easier to access for SQA
$presets.each do |arch, c|
    next if not c[:release_artifact]
    run("mkdir -p images")
    Dir["#{$ws}/bin/#{arch}/mesa/demo/*"].each do |e|
        next if File.directory?(e)
        ext = File.extname(e)

        case e
        when /\.mfi$/, /\.itb$/, /\.ext4.gz$/, /\.ubifs$/
            run("cp #{e} images/.")
        end
    end
end

$res.dump2

if $res.status == "OK"
    exit 0
else
    exit -1
end

