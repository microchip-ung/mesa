#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

Dir.chdir(File.dirname(File.dirname(File.expand_path(__FILE__))))

$err = 0
$year = Time.new.year

def check f
  f_in = File.readlines(f)
  copyright_ok = false
  license_ok = false

  # Do not care about empty files
  return if f_in.size < 1

  # Allow hash-bang in sctipts
  if f_in.size >= 1 and f_in[0] =~ /^#!\s*\//
    f_in.shift
  end

  # Allow optional empty line
  if f_in.size >= 1 and f_in[0] == "\n"
    f_in.shift
  end

  if f_in.size >= 2 and f_in[0] =~ /^(\#|\/\/|\/\*)?\s*Copyright \(c\) 2004-(\d\d\d\d) Microchip Technology Inc. and its subsidiaries.\s*(\*\/)?$/
    y = $2.to_i
    if y >= 2020 and y <= $year
      copyright_ok = true

      # In agreement with Brian Harlow from Legal, we only issue a warning if
      # we are 25 years off. This will still leave us at least 25 years year
      # to react.
      if $year - y > 25
        $stderr.puts "Warning: Copyright year has not been bumped in 25 years in #{f} - check if this is right"
        $err += 1
      end
    end
  end

  if f_in.size >= 2 and f_in[1] =~ /^(#|\/\/|\/\*)?\s*SPDX-License-Identifier: MIT\s*(\*\/)?$/
    license_ok = true
  end

  return if copyright_ok and license_ok

  raise f
end

%x{git ls-files}.split.each do |f|
  ext = File.extname(f)
  base = File.basename(f)
  next if /mepa.aqr/ =~ f # TODO, we should actually check that all third-party code is MIT licensed, but we need not to check the copyright
  next if /mepa.intel/ =~ f
  next if "mesa/docs/resources/asciidoctor-default.css" == f
  next if "mesa/docs/capdb.yaml" == f
  next if "mesa/docs/resources/pygments.css" == f

  next if /mesa.docs.resources.font/ =~ f
  next if /mesa.docs.resources.jquery/ =~ f
  next if /mesa.docs.resources.bootstrap/ =~ f

  next if "mepa/docs/resources/asciidoctor-default.css" == f
  next if "mepa/docs/resources/pygments.css" == f
  next if /mepa.docs.resources.font/ =~ f
  next if /mepa.docs.resources.jquery/ =~ f
  next if /mepa.docs.resources.bootstrap/ =~ f
  next if /.cmake\/docker\/SimpleGridClient/ =~ f

  next if [".vsd", ".svg", ".png", ".graphml", ".xls", ".txt"].include? ext
  next if [".gitattributes", ".gitignore", "Gemfile.lock", "catch.hpp", "TODO"].include? base

  begin
    check f
  rescue => e
    $stderr.puts "License/copyright not found/match in #{f}"
    $err += 1
  end
end

exit 1 if $err > 0
