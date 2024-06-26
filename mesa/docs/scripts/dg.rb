#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'yaml'
require 'json'
require 'base64'
require 'logger'
require 'nokogiri'
require 'optparse'
require 'fileutils'
require 'asciidoctor'
require_relative './parse.rb'

$opt = { }
global = OptionParser.new do |opts|
    opts.banner = "Usage: #{$0}"

    opts.on("-r", "--revision [REV]", "Revision") do |r|
        $opt[:rev] = r
    end

    opts.on("-s", "--sha [SHA]", "SHA") do |s|
        $opt[:sha] = s
    end
end.order!

$log = Logger.new(STDOUT)
$log.level = Logger::DEBUG

$top = File.expand_path(__FILE__)
4.times do
    $top = File.dirname($top)
end

Dir.chdir($top)

begin
    if !$opt[:sha]
        $opt[:sha] = %x(git rev-parse --short HEAD).chop
    end
rescue
end

$doc_top = "#{$top}/mesa/docs/"
$html_out = "#{$doc_top}/html"
system "rm -rf #{$html_out}"
system "mkdir #{$html_out}"
system "cp -r #{$doc_top}/resources/* #{$html_out}/."

$conf = YAML::load(File.open('mesa/docs/sitemap.yaml'))

$log.info "Loading capabilities"
$chipcapdb = YAML::load(File.open('mesa/docs/capdb.yaml'))
$capdb = {}

$chipcapdb.each do |chip, cap_list|
    cap_list.each do |cap|
        $capdb[cap[:str]] = [] if $capdb[cap[:str]].nil?
        $capdb[cap[:str]] << cap
    end
end
$log.info "Loading capabilities - DONE"

$id = 0
$tree_conf = []
$pages = {}

def href_page page, anc = nil
    l = "href=\"##{page}\""
    if anc
        l += "@#{anc}"
    end

    return l
end

def href_sym page, anc = nil
    l = "#href=\"#{page}\""
    if anc
        l += "@#{anc}"
    end

    return l
end

# TODO, only progress included files
#puts "Processing headers"
#Dir.glob("../include/microchip/ethernet/switch/api/*.h").each do |f|
#    begin
#        old_size = $symbol_index.size
#        record_symbols get_symbol_sequence(f)
#        puts "Parsed: #{f} #{$symbol_index.size - old_size} symbols added"
#    rescue
#        puts "Failed parsing #{f}"
#    end
#end

def build_cross_index_single src_file
    return nil if src_file.nil?

    #puts src_file
    #project_base = File.expand_path "#{Dir.getwd}/.."
    #puts project_base
    #src_file = File.expand_path src_file
    #puts src_file
    #src_file = (File.expand_path src_file)[(project_base.size + 1)..-1]
    #puts src_file

    dir = File.dirname(src_file)
    ext = File.extname(src_file)
    base = File.basename(src_file, ext)

    case File.extname(src_file)
    when ".h", ".c"
        begin
            old_size = $symbol_index.size
            record_symbols get_symbol_sequence(src_file)
            $log.info "Parsed: #{src_file} #{$symbol_index.size - old_size} symbols added"
        rescue
            $log.error "Failed parsing #{src_file}"
            $log.error $!
        end
    end
end

def build_cross_index conf_pages
    return nil if conf_pages.nil?

    conf_pages.each do |p|
        build_cross_index_single(p["src"])
        build_cross_index(p["pages"])
    end
end

def get_snippet file, snippet
    l = 0
    start_line = nil
    lines = []
    leading_spaces = 10000
    File.readlines(file).each do |line|
        l += 1

        #puts line
        case line
        when /\bsnippet_begin\s+(#{snippet})/
            #puts "MATCH #{snippet}"
            start_line = l

        when /\bsnippet_endbegin\s+(#{snippet})/
            #puts "MATCH2 #{snippet}"
            start_line = l
            start_line = l

        when /\bsnippet_endbegin\b/
            if start_line
                #puts "MATCH-END #{snippet}"
                break
            end

        when /\bsnippet_end\b/
            if start_line
                #puts "MATCH2-END #{snippet}"
                break
            end

        else
            if start_line
                #puts "ADDING LINE #{snippet}"
                lines << line
                if line.size > 1
                    leading_spaces_ = line[/\A */].size
                    if leading_spaces_ < leading_spaces
                        leading_spaces = leading_spaces_
                    end
                end
            end
        end
    end

    raise "Snippet not found!" if start_line.nil?

    lines.map!{|l| l[leading_spaces..-1]}

    cl = CLexer.new
    l = start_line
    lines.each do |line|
        l += 1
        line = "" if line.nil?
        cl.process_line line, "some_file", l
    end
    html = seq_to_html cl.root


    return {
        :line_start => start_line,
        :line_cnt => lines.size,
        :snippet => html
    }

end

build_cross_index $conf["pages"]

def process_adoc dir, base, ext, content
    images = []

    doc = Asciidoctor::Document.new(content, {
        :header_footer => false,
        :safe => Asciidoctor::SafeMode::UNSAFE,
        :attributes => {
            "backend" => "xhtml5",
            "sectnums" => true,
            "sectnumlevels" => "5",
            "sectanchors" => true,
            "sectlinks" => true,
            "outfilesuffix" => "/",
            #"source-highlighter" => "pygments",
            #"pygments-linenums-mode" => "inline",
            "icons" => "font",
        }
    })

    xml = Nokogiri::HTML::DocumentFragment.parse(doc.render)

    # Find all images
    xml.css("img[src]").each do |e|
        p = "#{dir}/#{e["src"]}"

        begin
            data = nil

            case File.extname(p)
            when ".svg"
                svg = Nokogiri::XML(File.open(p))
                data = "data:image/svg+xml;base64,#{Base64.encode64(svg.root().to_xml())}"
            when ".png"
                data = "data:image/png;base64,#{Base64.encode64(IO.binread(p))}"
            when ".jpg", ".jpeg"
                data = "data:image/jpeg;base64,#{Base64.encode64(IO.binread(p))}"
            else
                raise "Image type #{File.extname(p)} not supported (#{p})"
            end

            e.remove_attribute("src")
            e["src"] = data
        rescue
            $log.error "Failed to inline #{p}"
        end
    end

    # Find all icons
    xml.css(".admonitionblock td.icon [class^=\"fa icon-\"]").each do |e|
        begin
            case e["class"]
            when "fa icon-important"
                i = "fas fa-exclamation-circle"
                c = "#bf0000"
            when "fa icon-warning"
                i = "fas fa-exclamation-triangle"
                c = "#bf6900"
            when "fa icon-caution"
                i = "fas fa-fire"
                c = "#bf3400"
            when "fa icon-note"
                i = "fas fa-info-circle"
                c = "#19407c"
            when "fa icon-tip"
                i = "far fa-lightbulb"
                c = "color:#111"
            else
                raise "No match for #{e["class"]}"
            end

            e["class"] = "#{i} fa-2x"
            #e["style"] = "color=#{c};"

            #e.parent.replace("<span style=\"color:#{c};\"><i title=\"#{e["title"]}\" class=\"#{i} fa-2x\"></i></span>")

        rescue
            $log.error "Failed to update icon #{e}"
        end
    end

    # expand snipets
    xml.css(".language-snippet").each do |e|
        begin
            snip_req = e.inner_text.split(":")
            snip = get_snippet "../#{dir}/#{snip_req[0]}", snip_req[1]
            e.parent.replace(snip[:snippet])
        rescue
            $log.error "Failed to find snippet #{snip_req[1]} in ../#{dir}/#{snip_req[0]}"
        end
    end

    # expand mscc-sym
    xml.css("code").each do |e|
        case e.inner_text
        when /^mscc-sym:CAP\((\w+)\)$/
            cap = $capdb["MESA_CAP_#{$1}"]
            if cap
                snip = "<code><a href=\"#sym:MESA_CAP_#{$1}\">CAP(#{$1})</a></code>"
                e.replace(snip)
            else
                $log.error "Failed to find capability #{$1}"
            end

        # TODO, delete this
        when /^mscc-sym:(\w+)$/
            sym = $symbol_index[$1]
            if sym.nil?
                $log.error "Failed to find symbol #{$1}"
            else
                snip = "<code><a href=\"#sym:#{$1}\">#{$1}</a></code>"
                e.replace(snip)
            end

        when /^(MESA_CAP_\w+)$/
            cap = $capdb[$1]
            cap_name = $1

            if cap
                snip = "<code><a href=\"#sym:#{cap_name}\">#{cap_name}</a></code>"
                e.replace(snip)
            else
                $log.error "Failed to find capability #{cap_name}"
            end

        when /^(mesa_\w+)$/, /^(mesa_\w+)\([^\)]*\)$/, /^(MESA_\w+)$/,
             /^(meba_\w+)$/, /^(meba_\w+)\([^\)]*\)$/, /^(MEBA_\w+)$/
            sym = $symbol_index[$1]
            sym_name = $1

            if sym
                symbol_obj_push($1, :articles, { :type => "not sure", :file => "#{dir}/#{base}", :line => 0 })
                snip = "<code><a href=\"#symd:#{sym_name}\">#{e.inner_text}</a></code>"
                e.replace(snip)
            else
                $log.error "Failed to find symbol #{sym_name}"
            end

        # Members in structures
        when /^(mesa_\w+)::(\w+)$/, /^(mesa_\w+)::(\w+)\([^\)]*\)$/,
             /^(meba_\w+)::(\w+)$/, /^(meba_\w+)::(\w+)\([^\)]*\)$/
            sym_name = "#{$1}::#{$2}"
            idx = $1.size + 2
            sym_text = e.inner_text[idx..-1]
            sym = $symbol_index[sym_name]

            if sym
                symbol_obj_push($1, :articles, { :type => "not sure", :file => "#{dir}/#{base}", :line => 0 })
                snip = "<code><a href=\"#symd:#{sym_name}\">#{sym_text}</a></code>"
                e.replace(snip)
            else
                $log.error "Failed to find symbol #{sym_name}"
            end

        when /^mscc-sym:/
            $log.error "Did not understand #{sym_name}"

        end
    end

    # expand href
    xml.css("a").each do |e|
        next if e["href"].nil?

        case e["class"]
        when "bare"
            # This is a link to something outside api-doc - do nothing
        when "link", "anchor"
            # This is an autogenerated local link when sectlinks and/or sectanchors attribute is true
            # Prepend with path and base and replace original '#' with '@':
            # '#_usb' -> '#docs/peripherals@_usb'
            org_href = e["href"]
            new_href = "##{dir}/#{base}@#{org_href[1..-1]}"
            e["href"] = new_href
        when nil
            # This is a link to another page - do nothing
            # The landing page and the id, separated by @, must be included in the adoc xref like this:
            # "See the xref:docs/peripherals@_usb[USB] section"
            # Id's are created automatically for section headers but you can also define them manually with:
            # [[this_is_an_id]] or [#this_is_an_id]
        else
            raise "Unknown hyperlink class '#{e["class"]}' in #{e}"
        end
    end

    html = xml.to_html

    return {
        :name => base,
        :dir => dir,
        :content => html,
        :images => images,
        #:content => Asciidoctor.convert(content, :header_footer => false, safe: :unsafe),
    }
end

def process_c dir, base, ext, content
    p = "#{dir}/#{base}#{ext}"
    html = seq_to_html(get_symbol_sequence(p), p)
    return {
        :name => "#{base}#{ext}",
        :dir => dir,
        :content => html,
    }
end

def process_txt dir, base, ext, content
    return {
        :name => base,
        :dir => dir,
        :content => content,
    }

end

def process_src src_file, id
    return nil if src_file.nil?

    dir = File.dirname(src_file)
    ext = File.extname(src_file)
    base = File.basename(src_file, ext)
    content = IO.binread(src_file)

    $log.info "Processing #{src_file}"
    process_src = nil
    icon = "far fa-file"
    case File.extname(src_file)
    when ".adoc"
        process_src = process_adoc dir, base, ext, content
        icon = "far fa-file-alt"
    when ".h", ".c"
        process_src = process_c dir, base, ext, content
        icon = "far fa-file-code"
    else
        process_src = process_txt dir, base, ext, content
        icon = "far fa-file-alt"
    end

    html_file_name = "#{process_src[:dir]}/#{process_src[:name]}"

    $pages[html_file_name] = {
        :icon    => icon,
        :content => process_src[:content],
        :dir     => process_src[:dir],
        :id      => id,
        :images => process_src[:images],
    }

    return {
        :name      => process_src[:name],
        :html_path => html_file_name,
        :id        => id,
        :icon      => icon,
    }

end

def process_pages conf_pages
    return nil if conf_pages.nil?

    res = []

    conf_pages.each do |p|
        $id += 1
        id = $id
        page_entry = {
            :name  => p["name"],
            :src   => process_src(p["src"], id),
            :pages => process_pages(p["pages"]),
            :id    => id
        }

        page_entry[:name] = page_entry[:src][:name] if page_entry[:name].nil?

        res << page_entry
    end

    return res
end

$data = process_pages $conf["pages"]

IO.binwrite("#{$html_out}/symdb.json", JSON.pretty_generate($symbol_index))

def cap_cross_index
    $id += 1

    menu_chip_idx = {
        :name => "List of APIs",
        :pages => []
    }

    menu_cap_idx = {
        :name => "List of capabilities",
        :pages => []
    }

    menu_root = {
        :name => "Capability DB",
        :id   => $id,
        #:src => {
        #    :name => "capdb",
        #    :html_path => "index/capdb.html",
        #    :id => $id,
        #},
        :pages => [
            menu_chip_idx,
            menu_cap_idx
        ]
    }

    $data << menu_root

    #begin
    #    list_of_chips = $chipcapdb.keys
    #    list_of_cap = $capdb.keys
    #    html = "<h1>Capability DB</h1><table><thead><tr><th>Capabilities</th>\n"
    #    html += "#{list_of_chips.map{|x| "<th><a href=\"../index/#{x}.html\">#{x}</a></th>\n"}.join("")}\n"
    #    html += "</thead><tbody>"

    #    list_of_cap.each do |cap|
    #        html += "<tr>\n"
    #        html += "<td><a href=\"../index/#{cap}.html\">#{cap}</a></td>\n"
    #        list_of_chips.each do |chip, chip_list|
    #            ref = {}

    #            $capdb[cap].each do |x|
    #                ref[x[:chip]] = x[:val]
    #            end

    #            if ref[chip]
    #                html += "<td>#{ref[chip]}</td>\n"
    #            else
    #                html += "<td>unknown</td>\n"
    #            end
    #        end

    #        html += "</tr>\n"
    #    end

    #    html += "</table>\n"

    #    $pages["index/capdb.html"] = {
    #        :content => html,
    #            :dir     => "index/",
    #            :id      => $id,
    #    }
    #end


    $capdb.each do |cap, chip_list|
        $id += 1
        html = "<h1>#{cap}</h1><table><thead><tr><th>API/Chip name</th><th>Capability value</th></thead><tbody>"

        chip_list.each do |chip|
            html += "<tr>"
            html += "<td><a href=\"../index/#{chip[:chip]}.html\">#{chip[:chip]}</a></td>"
            html += "<td>#{chip[:val]}</td>"
            html += "</tr>"
        end

        html += "</table>"

        $pages["index/#{cap}.html"] = {
            :content => html,
            :dir     => "index/",
            :id      => $id,
        }

        menu_cap_idx[:pages] << {
            :name => cap,
            :id   => $id,
            :src => {
                :name => cap,
                :html_path => "index/#{cap}.html",
                :id => $id,
            }
        }
    end

    $chipcapdb.each do |chip, cap_list|
        $id += 1
        html = "<h1>#{chip}</h1><table><thead><tr><th>Capability name</th><th>Capability value</th></thead><tbody>"

        cap_list.each do |cap|
            html += "<tr>"
            html += "<td><a href=\"../index/#{cap[:str]}.html\">#{cap[:str]}(#{cap[:int]})</a></td>"
            html += "<td>#{cap[:val]}</td></tr>"
            html += "</tr>"
        end

        html += "</table>"

        $pages["index/#{chip}.html"] = {
            :content => html,
                :dir     => "index/",
                :id      => $id,
        }

        menu_chip_idx[:pages] << {
            :id => $id,
            :name => chip,
            :src => {
                :name => chip,
                :html_path => "index/#{chip}.html",
                :id => $id,
            }
        }
    end


end

$log.info "Calculate cross index"
cap_cross_index()

def gen_menu_list list, indent = "", id_ = nil
    id_ = " id=\"#{id_}\"" if id_
    s = "#{indent}<ul#{id_}>\n"
    list.each do |e|
        s += gen_menu_element(e, "#{indent}  ")
    end
    s += "#{indent}</ul>\n"
end

def gen_menu_element page, indent = ""
    s  = "#{indent}<li id=\"li#{page[:id]}\">\n"
    if page[:src] and page[:src][:html_path]
        if page[:src][:icon]
            ii = "#{indent}  <i class=\"stm-icon #{page[:src][:icon]} fa-sm\"></i>\n"
        else
            ii = "#{indent}  <i class=\"stm-icon far fa-file fa-sm\"></i>\n"
        end
        i  = "<span class=\"stm-icon\">#{ii}</span>"
        s += "#{indent}  <a class=\"stm-content\" #{href_page(page[:src][:html_path])}>#{i}#{page[:name]}</a>\n"
    else
        ii = "#{indent}  <i class=\"stm-icon far fa-folder fa-sm\"></i>\n"
        i  = "<span class=\"stm-icon\">#{ii}</span>"
        s += "#{indent}  <span class=\"stm-content\">#{i}#{page[:name]}</span>\n"
    end
    s += gen_menu_list(page[:pages], "#{indent}  ") if page[:pages]
    s += "#{indent}</li>\n"
end

$js_pages = {}

$pages.each do |path, p|
    $js_pages[path] = p[:content]
    puts "Page: #{path}"
end

def inline_js path
    buf = "  <script type=\"text/javascript\">"
    buf += IO.binread(path)
    buf += "</script>\n".b
    return buf
end

def inline_css path
    buf = "  <style>".b
    buf += IO.binread(path)
    buf += "</style>\n".b
    return buf
end

$log.info "Write HTML output"
html = "".b

html += "<html lang=\"en\">\n".b
html += "<head>\n".b
html += "  <meta charset=\"UTF-8\">\n".b
html += "  <title>MESA Doc</title>\n".b

# TODO, we should create a style-sheet that is inhireted by the scss asciidoctor
# component, and based on foundation. This should replace all of this
html += inline_css "./mesa/docs/resources/bootstrap.min.css"
html += inline_css "./mesa/docs/resources/jquery-simpleTreeMenu.css"
html += inline_css "./mesa/docs/resources/asciidoctor-default.css"
html += inline_css "./mesa/docs/resources/mesa.css"

html += "  <script type=\"text/javascript\">\n"
html += "      FontAwesomeConfig = {\n"
html += "          autoReplaceSvg: true,\n"
html += "          observeMutations: true,\n"
html += "      }\n"
html += "  </script>\n"

html += inline_js("./mesa/docs/resources/jquery.min.js")
html += inline_js("./mesa/docs/resources/jquery-simpleTreeMenu.js")
html += inline_js("./mesa/docs/resources/fontawesome-free-5.10.1-web/js/solid.min.js")
html += inline_js("./mesa/docs/resources/fontawesome-free-5.10.1-web/js/regular.min.js")
html += inline_js("./mesa/docs/resources/fontawesome-free-5.10.1-web/js/fontawesome.min.js")
html += "  <script type=\"text/javascript\">\n".b
html += "  var pages = #{$js_pages.to_json};\n".b
html += "  var symbol = #{$symbol_index.to_json};\n".b
html += "  </script>\n".b
html += inline_js("./mesa/docs/resources/api-doc.js")

# IO.binwrite("#{$html_out}/symdb.json", JSON.pretty_generate($symbol_index))

html += "</head>\n"
html += "<body>\n"
html += "  <div class=\"container\">\n"
html += "    <div class=\"row\">\n"
html += "      <div class=\"col-lg-12\">\n"
h = "MESA-Doc"
h += " #{$opt[:rev]}" if $opt[:rev]
h += " (#{$opt[:sha]})" if $opt[:sha]
html += "        <h1>#{h}</h1>\n"
html += "      </div>\n"
html += "    </div>\n"
html += "    <div class=\"row\">\n"
html += "      <div class=\"col-lg-3\">\n"
html += "        <div style=\"background-color: white\" class=\"well\">\n"
html += gen_menu_list($data, "          ", "demoTree")
html += "        </div>\n"
html += "      </div>\n"
html += "      <div class=\"col-lg-9\">\n"
html += "        <div style=\"background-color: white\" class=\"well\" id=\"content\">\n"
html += "        </div>\n"
html += "      </div>\n"
html += "    </div>\n"
html += "  </div>\n"
html += "</body>\n"
html += "<script type=\"text/javascript\">\n"
html += "hashChange(null);\n"
html += "$('#demoTree').simpleTreeMenu();\n"
html += "</script>\n"
html += "</html>\n"

IO.binwrite("mesa-doc.html", html)

