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

require 'json'
require 'pp'
require 'erb'

class ResultNode
   TMPL = <<EOF
<!DOCTYPE html>
<html>
<head>
 <title>Build status</title>
 <link rel="stylesheet" type="text/css" href="http://w2ui.com/src/w2ui-1.4.2.min.css" />
 <script src="http://ajax.googleapis.com/ajax/libs/jquery/2.1.0/jquery.min.js"></script>
 <script type="text/javascript" src="http://w2ui.com/src/w2ui-1.4.2.min.js"></script>
 <style>
  .w2ui-icon-cross:before{color:red;}
  .w2ui-icon-check:before{color:green;}
 </style>
</head>
<body>
<div id="main" style="position: absolute; top: 10px; left: 10px; bottom: 10px; right: 10px;"></div>
<script type="text/javascript">

var config = <%= tree_view_config %>

function sidebar_onclick(e) {
    c = {
        name: "meta",
        columns: [
            { field: 'k', caption: 'Key', size: '200px' },
            { field: 'v', caption: 'Value', size: '100%' }
        ]
    }
    c.records = config.data[e.target]["records"]

    cc = {
        name: "meta_sib"
    }
    cc.columns = config.data[e.target]["sibs_cols"]
    cc.records = config.data[e.target]["sibs_records"]

    $().w2destroy("meta")
    $().w2destroy("meta_sib")
    w2ui.layout.content('main',
        "<h1>" + config.data[e.target]["absname"] + ": " + config.data[e.target]["status"] + "</h1>" +
        "<hr />" +
        "<h2>Metadata:</h2>" +
        "<div style=\\\"height: 300px\\\" id=\\\"main_meta\\\"></div>" +
        "<h2>Siblings:</h2>" +
        "<div style=\\\"height: 800px\\\" id=\\\"main_meta_sib\\\"></div>");
    $('#main_meta').w2grid(c);
    $('#main_meta_sib').w2grid(cc);
}

$(function () {
    config.sidebar.onClick = sidebar_onclick
    $('#main').w2layout(config.layout);
    w2ui.layout.content('left', $().w2sidebar(config.sidebar));
});

</script>
</body>
</html>
EOF

  attr_accessor :name, :status, :meta, :siblings
  def initialize(name, status = "", meta = {})
    @name = name
    @status = status
    @meta = meta
    @siblings = []
  end
  def addSibling(node)
    @siblings << node
  end
  def q q
    x = self
    (q_node, q_meta) = q.split "@"

    if q_meta.nil?
      q_meta = q
      q_node = nil
    end

    #puts "#{q} #{q_node} #{q_meta}"

    if not q_node.nil?
      q_nodes = q_node.split(".")
      q_nodes.push q_node if q_nodes.size == 0

      #puts q_nodes.join(", ")
      q_nodes.each do |n|
        found_sib = false

        x.siblings.each do |s|
          if s.name == n
            x = s
            #puts "Match"
            found_sib = true
            break
          end
        end

        raise "Node not found" if not found_sib

      end
    end

    if q_meta == "status"
        res = x.status
    else
        res = x.meta[q_meta]
    end
    raise "Meta data #{q_meta} not found" if res.nil?

    return res
  end
  def reCalc
    if @siblings.length == 0
      return @status
    end
    sub_status = []
    @siblings.each do |s|
      sub_status << s.reCalc()
    end
    # Finde unique values
    sub_status.uniq!

    # Failed unless all status are OK
    if sub_status.length == 1 and sub_status[0] == "OK"
      @status = "OK"
    else
      @status = "Failed"
    end

    return @status
  end
  # General conversion
  def to_hash
    n = { 'name' => @name, 'status' => @status, 'meta' => @meta, 'siblings' => [] }
    @siblings.each do |s|
      n['siblings'] << s.to_hash()
    end
    n
  end
  def self.from_hash(h)
    h.each do |i,n|
      return nil if !(i =~ /name|status|meta|siblings/i)
    end
    n = ResultNode.new(h['name'], h['status'], h['meta'])
    h['siblings'].each do |s|
      n.addSibling(ResultNode.from_hash(s))
    end
    n
  end
  # JSON support
  def to_json(state)
    to_hash().to_json
  end
  # File IO
  def self.from_file(f)
    r = from_hash(JSON.parse(File.read(f)))
    r.reCalc
    return r
  end
  def to_file(f)
    reCalc()
    File.write(f, JSON.dump(to_hash))
  end
  # Debug
  def dump(p = '>')
    %W{name status}.each do |i,n|
      puts "#{p} @#{i}: #{instance_variable_get('@'+i)}"
    end
    puts p + " metadata: " + JSON.dump(@meta) if !@meta.nil?
    @siblings.each do |s|
      s.dump(p+'>')
    end
    puts p+"---"
  end
  # ERB/render formatting
  def render(template)
    ERB.new(template).result(binding)
  end
  def render_xml()
    render(<<END
<% def draw_node(node, _erbout) %>
<node name="<%= node.name %>" status="<%= node.status %>" >
 <% if node.meta %>
 <metadata>
   <% node.meta.each do |k,v| %>
   <meta key="<%= k %>" value="<%= v %>"/>
   <% end %>
 </metadata>
 <% end %>
 <% if node.siblings.length > 0 %>
 <siblings>
   <% for i in node.siblings %>
   <% draw_node(i, _erbout) %>
   <% end %>
 </siblings>
 <% end %>
</node>
 <% end %>
<%= draw_node(self, "") %>}
END
          )
  end

  def __dump2(p)
    n = "#{p}.#{@name}" if p.size > 0
    n = "#{@name}" if p.size == 0
    puts "%-100s %s" % [n + ":", @status]
    @siblings.each { |s| s.__dump2(n) }
  end

  def dump2
    reCalc
    __dump2 ""
  end

  def __dump_tree_view prefix, siblings_in, dump_tree_view_details
    reCalc
    res = {}
    if prefix.size == 0
      prefix = @name
    else
      prefix = "#{prefix}.#{@name}"
    end

    id = "leaf#{@@dump_tree_view_cnt}"
    @@dump_tree_view_cnt += 1
    res["id"] = id
    if @siblings.size == 0 and @status != "OK"
      res["text"] = "#{@name} <em style='color: red'>#{@status}</em>"
    else
      res["text"] = @name
    end


    if @status == "OK"
      res["icon"] = "w2ui-icon-check"
    else
      res["icon"] = "w2ui-icon-cross"
      res["expanded"] = true
    end
    res["icon-folder"] = "icon-folder"

    cnt_meta = 0
    mm = { :Node => @name, :Status => @status }
    dump_tree_view_details[id] = {}
    dump_tree_view_details[id]["status"] = @status
    dump_tree_view_details[id]["absname"] = prefix

    if @meta and @meta.size > 0
      cnt_meta = @meta.size
      cnt = 0
      m = []
      @meta.each do |k, v|
        m << { :recid => cnt, :k => k, :v => v }
        mm[k] = v
        cnt += 1
      end
      dump_tree_view_details[id]["records"] = m
    end

    siblings_in << mm
    siblings_this = []

    if @siblings.size > 0
      res["nodes"] = []
      @siblings.each do |s|
        res["nodes"] << s.__dump_tree_view(prefix, siblings_this, dump_tree_view_details)
      end
    end

    cols = []
    siblings_this.each do |r|
      r.each do |k, v|
        if not cols.include? k
          cols << k
        end
      end
    end

    sib_col = []
    cols.each_index do |i|
      sib_col << { :field => i.to_s, :caption => cols[i], :size => "10%" }
    end

    cnt = 0
    sib_rec = []
    siblings_this.each do |r|
      m = {:recid => cnt}

      cols.each_index do |i|
        c = cols[i]
        if r[c].nil?
          m[i] = ""
        else
          m[i] = r[c]
        end
      end

      cnt += 1
      sib_rec << m
    end


    dump_tree_view_details[id]["sibs_cols"] = sib_col
    dump_tree_view_details[id]["sibs_records"] = sib_rec

    if cnt_meta > 0 or @siblings.size > 0
      res["count"] = "#{cnt_meta}/#{@siblings.size}"
    end

    return res
  end

  def dump_tree_view dump_tree_view_details
    @@dump_tree_view_cnt = 0

    res = {}
    res["name"] = "sidebar"
    res["nodes"] = []
    res["nodes"] << __dump_tree_view("", [], dump_tree_view_details)

    return res
  end

  def tree_view_config
    dump_tree_view_details = {}
    s = dump_tree_view dump_tree_view_details
    pstyle = "'border: 1px solid #dfdfdf; padding: 5px;'"
    c = {
      "layout" => {
        "name" => 'layout',
        "padding" => 4,
        "panels" => [
          #{ "type" => 'top',  "size" => 50,  "resizable" => false, "style" => pstyle, "content" => 'top' },
          { "type" => 'left', "size" => 500, "resizable" => true,  "style" => pstyle, "content" => 'left' },
          { "type" => 'main',                                      "style" => pstyle, "content" => 'main' }
        ]
      },
      "sidebar" => s,
      "data" => dump_tree_view_details
    }

    return JSON.pretty_generate(c)
  end

  def tree_view_render
    reCalc
    return render(TMPL)
  end
end
