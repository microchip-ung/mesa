#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'open3'
require_relative "./resultnode.rb"

top = File.expand_path(File.dirname(File.dirname(__FILE__)))

x = Dir.glob "images/mesa-*.tar.gz"
if x.size != 1
    puts "Unexpected API count: [#{x.join(", ")}]"
    exit 1
else
    $api = x[0]
end

puts "Using API: #{$api}"

$checks = []
def check name, appl, cfgs
    base_name  = "#{name}-#{appl}"
    out = "images/#{base_name}"
    ws = "backwards-check-ws/#{base_name}"
    %x{mkdir -p #{out}}
    %x{mkdir -p backwards-check-ws}

    c = "./.cmake/backwards-compatibility-check_.rb "
    c += "-w #{ws} "
    c += "-a #{$api} "
    c += "-b webstax2-internal-#{appl}.tar.gz "
    c += "-c #{cfgs} -o #{out} "
    #c += "> #{out}/log"

    $checks << { :cmd => c, :dir => out, :name => base_name }
end

# Default set of configurations to build
$default_configs = "istax_multi.mk"

# List all APPL-revs/configurations to run backwards compatibility checks against

# DO NEVER DELETE ENTRIES HERE!!
# Instead, if you break backwards compatibility, then comment out the check that
# can not pass any more, write a comment explaining why and mention last
# commit where a given test did pass AND add a new check that do pass!
#
# Here are the steps to create a new backwards compatibility check point:
# - Notice, this can (should) be done with MESA changes on a branch - the final
#   step is to merge the branch.
# - Make WebStaX compile with the new API build in-tree.
# - Commit changes locally, but do not push (yet).
# - In WebStaX, run the ./build/tools/internal-src-rel script.
# - In MESA, open '.cmake/backwards-compatibility-check.rb' comment out the old
#   reference, and add a new one.
# - Push MESA, and wait for Jenkins to give you green light. Go to Jenkins,
#   select the API-Promote project, and promote your new build.
# - In WebStaX, edit 'build/make/paths-api.mk' and point to your new API. Commit
#   and push.
# - If your MESA changes was on a branch, then now is time to merge your branch
#   to master - but do use the '--no-ff' flag ensure that the SHAs are not
#   changed.

# Backwards compatibility with 6bf6a82@4-dev was broken in commit
# e86bb9328c0eaadd6d2e7d83b4bb8b3c2bd3dbd8 where the CapArries was moved out of
# the API and into the WebStaX2 repository instead.
#check("backwards-check",        # Name of check
#      "6bf6a82@4-dev",          # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with ae50741@4-dev was broken in commit
# f4a3fd92cf320d6a4c96d72ef63f5f03b4a5909f where MESA_CAP_AFI_FAST_INJ_BPS_MAX
# was changed/renamed to MESA_CAP_AFI_FAST_INJ_KBPS_MAX.
#check("backwards-check",        # Name of check
#      "ae50741@4-dev",          # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with 16f3e31@4-dev was broken in commit
# 6df72668c9816aa99c0182d38b21621d21186874 where many API targets
# were renamed to show whether Aquantia PHYs are supported or not
# (see also BZ#22586 comment #7).
#check("backwards-check",        # Name of check
#      "16f3e31@4-dev",          # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with d285e7c@4-dev was broken in commit
# b20434f07705cece2f8308cb5099be350511d783 where the MEBA irq was
# started.
#check("backwards-check",        # Name of check
#      "d285e7c@4-dev",          # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with 4d203cc@4-dev was broken in commit
# 78c90a405e8b1ff871143cfadae439736162095d where VLAN translation
# was changed.
#check("backwards-check",        # Name of check
#      "4d203cc@4-dev",          # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with 83df42a@4-dev.vlan-translate was broken in commit
# 5016f3415427aa17e8ef08454d91f238adc5ee90 where the Viper B OOS API was modified.
#check("backwards-check",        # Name of check
#      "83df42a@4-dev.vlan-translate", # Appl release to use
#      $default_configs)         # Configs to build

#check("backwards-check",        # Name of check
#      "8b026dbc3b@4-dev.bz23852", # Appl release to use
#      $default_configs)         # Configs to build

# Backwards compatibility with 8b026dbc3b@4-dev.bz23852 was broken in commit
# e24a98d. The reason was a cleanup in the 10G PHY API.
#
# These functions was deleted:
# - vtss_phy_10g_base_kr_training_get
# - vtss_phy_10g_base_kr_training_set
# - vtss_phy_10g_base_kr_ld_adv_ability_set
# - vtss_phy_10g_base_kr_ld_adv_abil_get
#
# The functionallity was replaced by:
# - vtss_phy_10g_base_host_kr_train_aneg_set
# - vtss_phy_10g_kr_status_get
#check("backwards-check",          # Name of check
#      "49a34937e3@4-dev.bz23305", # Appl release to use
#      $default_configs)           # Configs to build

# Bumping the backwards compatibility check to 4.3.0.
#check("backwards-check",          # Name of check
#      "46cc7c871b@4-rel",         # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with 46cc7c871b@4-rel was broken, because Seville
# and Seville2 support was removed from the API, so vtss_board_type() can no
# longer return e.g. VTSS_BOARD_SEVILLE2_REF.
#check("backwards-check",          # Name of check
#      "f5852c7@4-dev",            # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with 46cc7c871b@4-rel was broken in commit
# 3ac9954413c40b5fbb5d7490781cc70f2416a93c. The reason was add new
# SPF Module Event (MEBA_EVENT_MOD_DET) in event structure.
#check("backwards-check",          # Name of check
#      "39648addcf@4-dev.bz11118-2", # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with 39648addcf@4-dev.bz11118-2 was broken in commit
# c66de1e2aa64bae0c20c3d344b9d42a8c616da3d . The reason was moving AQR drivers out of the API
# and into trhird-party drivers, and then re renamed the API targets to not contain AQR in the name.
#check("backwards-check",          # Name of check
#      "a532b8c1b8@4-dev.port_refactor2.aqr", # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with a532b8c1b8@4-dev.port_refactor2.aqr was broken in commit
# e72a4c41b58d23d88826af5725a7ffdb96664413. The reason was that the application used
# positioned initialization of a structure.
#check("backwards-check",          # Name of check
#      "01d6d2a@4-dev",            # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with 01d6d2a@4-dev was broken in commit
# fbf4e35be1543b1fdf36fc03db0dfebfb328b3e2. The reason was that the Fireant API
# was merged to 4-dev.
#check("backwards-check",          # Name of check
#      "610df82@4-dev",            # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with 610df82@4-dev was broken in commit
# 0c7bf3c499d4684e48f4bcee549930dd3806565a. The reason was that the signature of
# mesa_debug_printf_t was changed to resemble that of printf().
# check("backwards-check",          # Name of check
#       "663920a@4-dev",            # Appl release to use
#       $default_configs)           # Configs to build

# Backwards compatibility with 663920a@4-dev was broken in commit
# b1a1fc37030d61cf24cdf836b6260b05a797fcec. The reason is that we wanted to
# update the TAS API before it becase widely used.
#check("backwards-check",          # Name of check
#      "c183be9666@2019.09-soak.tas-hdr",   # Appl release to use
#      $default_configs)           # Configs to build

# Backwards compatibility with c183be9666@2019.09-soak.tas-hdr was broken in
# commit 4b37272056618e713eb9f5e43b4bfce9d8ef9a12.
# The reason is that we wanted to reduce the number of API flavors to have one
# per SKU independent of number of ports (always using max number of ports).
#check("backwards-check",              # Name of check
#      "3f0030a@master.meba_port_cnt", # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with 3f0030a@master.meba_port_cnt was broken in
# commit f01f8392e0a41d98e8748b6424f6f7f8c765bcb1.
# The reason is that MESA_CAP_QOS_QBV_XXXX was changed to MESA_CAP_QOS_TAS_XXXX
#check("backwards-check",              # Name of check
#      "d37c351ea1@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken in
# commit a3481d94877e9ae179ebfd19776623cd08f57e2f
# The reason is that the packet API was updated.
#check("backwards-check",              # Name of check
#      "a3481d9@master",               # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken when moving to new
# unifed BSP, as this did nothave the kernel modules (which the application
# insisted on building)
#check("backwards-check",              # Name of check
#      "8c88dda92b@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because Serval1 has
# been removed.
# check("backwards-check",              # Name of check
#       "85b60baa43@master",            # Appl release to use
#       $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because the JR2
# KR API has been updated to be compatible with FA
#check("backwards-check",              # Name of check
#      "4245df640b@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because of KR updates
#check("backwards-check",              # Name of check
#      "b44a6ccf33@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because of MEPA updates
#check("backwards-check",              # Name of check
#      "0c82a739d8@master.mepa",       # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because of change in
# MEPA library names
#check("backwards-check",              # Name of check
#      "1aa78aaf02@master.mepa",       # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because of addition of
# the PUSH_BUTTON IRQ source
#check("backwards-check",              # Name of check
#      "8aa7926f19@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because of MEPA
#check("backwards-check",              # Name of check
#      "562a234fb3@master.port.mepa",  # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken because master.mas merge
#check("backwards-check",              # Name of check
#      "eaa1d31e72@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken due to MEPA-TS and
# MEPA-SPLIT
#check("backwards-check",              # Name of check
#      "004db027bb@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken due to change
# directories in MEPA
#check("backwards-check",              # Name of check
#      "e5a4eed5a4@master",            # Appl release to use
#      $default_configs)               # Configs to build

# Backwards compatibility with previous build was broken due to change
# of MESA-PHY functions to VTSS-PHY functions
#check("backwards-check",              # Name of check
#      "ed80b69366@master.mesa-phy-remove", # Appl release to use
#      $default_configs)               # Configs to build

# As part of the MEPA clean-up a trance init has changed, and a few types has
# been renamed.
#check("backwards-check",              # Name of check
#      "8071441ea6@master.mepa-init-cleanup", # Appl release to use
#      $default_configs)               # Configs to build

# As part of the PoE upgrade, a few types has been modified
#check("backwards-check",              # Name of check
#      "e365359205@master.pds-family", # Appl release to use
#      $default_configs)               # Configs to build
# More PoE updates
#check("backwards-check",              # Name of check
#      "27e2ceb283@master", # Appl release to use
#      $default_configs)               # Configs to build
# Yet another round of PoE updates
#check("backwards-check",              # Name of check
#      "4716b2d3a4@2022.09-poe-integration", # Appl release to use
#      $default_configs)               # Configs to build

# PoE bt support requires yet another type modifications
#check("backwards-check",              # Name of check
#      "b90a3945c6@poe-update", # Appl release to use
#      $default_configs)               # Configs to build

#Support for I2C argument changes in read/write APIs
check("backwards-check",              # Name of check
      "4b8386abbf@master.viper", # Appl release to use
      $default_configs)               # Configs to build

# This will be activated when we get to the 4.2 release
# This is the backwards compability check against 4.2.0
# DO NOT COMMENT OUT / DELETE THIS ENTRY - IF YOU BELIEVE IT IS NEEDED, ASK
# ALLAN W. NIELSEN TO DO IT FOR YOU!
#check("backwards-check",        # Name of check
#      "xxxxxxx@4-rel",          # Appl release to use
#      $default_configs)         # Configs to build

# Add more checks as needed

res = ResultNode.new("API-Backwards check", "OK", {"api-release" => $api})

$checks.each do |c|
    puts "Running: #{c[:cmd]}"
    o, e, s = Open3.capture3(c[:cmd])

    r = ResultNode.from_file("#{c[:dir]}/status.json")
    r.name = c[:name]

    if o.chomp.size > 0
        puts "STDOUT:"
        puts o
    end

    if e.chomp.size > 0
        puts "STDERR:"
        puts e
    end

    puts "Status: #{c[:name]} -> #{r.status}"
    res.addSibling(r)
end

root = ResultNode.from_file("images/status.json");
root.addSibling(res)

root.to_file("images/status.json")
File.write("images/status.html", root.tree_view_render)

puts "combined status: #{root.status}"

if root.status == "OK"
    exit 0
else
    exit -1
end

