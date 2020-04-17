#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'nokogiri'

x = Nokogiri::XML(File.open("asdf.xml"))

$o = File.open("asdf.html", "w")


$o.write <<~HEREDOC
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<style>

.box {
    padding: 0px;
    margin: 0px;

    outline-width: 0px;
    outline: none;
    border: none;
    border-width: 0px;
    width: 100%;
    overflow: hidden;

}

.pre-line {
    padding: 0px;
    margin: 0px;
}

.hdr-type {
    width: 50px;
    display: inline-block;

    font-size: 12px;
    border-radius: 5px 5px 5px;
    border: 1px solid red;
    position:relative;
}

.collapsible {
    background-color: #777;
    color: white;
    cursor: pointer;

    text-align: left;
    font-size: 15px;
}

.content {
    padding: 0px 0px 0px 10px;
    overflow: hidden;
    background-color: #f1f1f1;
}

</style>
</head>
<body>
<h1>asdf</h1>
<div class=\"box\">
HEREDOC


def xml_colapsible_start o
    $o.puts "<div class=\"box collapsible test-header\">"
    $o.puts "    <span class=\"hdr-type\">test</span>#{o["name"].encode(:xml => :text)}"
    $o.puts "</div>"
    $o.puts "<div class=\"box content test-content\">"
end

def xml_colapsible_end o
    $o.puts "</div>"
end

def visit_test o
    puts "visit_test "
    xml_colapsible_start o
    o.children.each do |c|
        visit c
    end
    xml_colapsible_end o

    #o.each do |k, v|
    #    puts "k; #{k}"
    #    case k
    #    when "trace"
    #        v.each do |t|
    #            $o.puts "<p class=\"box trace-#{t["level"]}\">#{t["content"].encode(:xml => :text)}</p>"
    #        end

    #    when "backtrace"
    #        $o.puts "<div class=\"box collapsible bt-header\"><span class=\"hdr-type\">BT</span></div>"
    #        $o.puts "<div class=\"box content bt-content\">"
    #        $o.puts "<pre>#{v[0].encode(:xml => :text)}</pre>"
    #        $o.puts "</div>"

    #    when "test"
    #        v.each do |e|
    #            visit_test e
    #        end

    #    when "run"
    #        $o.puts "<div class=\"box collapsible cmd-header\"><span class=\"hdr-type\">CMD</span>#{v[0]["cmd"].encode(:xml => :text)}</div>"
    #        $o.puts "<div class=\"box content cmd-content\">"

    #        if v[0]["run-stdout"]
    #            v[0]["run-stdout"].each do |l|
    #                $o.puts "<pre class=\"pre-line\">#{l["content"]}</pre>"
    #            end
    #        end
    #        $o.puts "</div>"

    #    end
    #end
end

def visit_trace o

end

def visit o
    case o.name
    when "root", "document"
        o.children.each do |c|
            visit c
        end

    when "test"
        visit_test o

    when "trace"
        visit_trace o

    when "backtrace"
    when "run"
    end
end

visit x

#visit_test x.root


$o.write <<~HEREDOC
</div>
<script>
var coll = document.getElementsByClassName("collapsible");
var i;

for (i = 0; i < coll.length; i++) {
  coll[i].addEventListener("click", function() {
    var content = this.nextElementSibling;
    if (content.style.display === "none") {
      content.style.display = "block";
    } else {
      content.style.display = "none";
    }
  });
}
</script>

</body>
</html>
HEREDOC

