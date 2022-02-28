#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'cgi'

$lang = {
    :s_root => [
        [/^\/\/.*/,           :sym_comment,        :s_root],
        [/^\/\*/,             :sym_comment_start,  :s_comment],
        [/^\s+/,              :sym_spaces,         :s_root],

        [/^(0x|0X)[a-fA-F0-9]+/,  :sym_num,        :s_root],
        [/^\d+/,              :sym_num,            :s_root],

        [/^\w+/,              :sym_word,           :s_root],
        [/^[\[\]{},.*();<>=\-^%!+&?:|~\/]/,
                              :sym_single_char,    :s_root],
        [/^"/,                :sym_string_start,   :s_string],
    ],

    :s_string => [
        [/^(?:[^"\\]|\\.)+/,  :sym_string_data,   :s_string],
        [/"/,                 :sym_string_end,    :s_root],
        [/\\$/,               :sym_string_multi,  :s_string]
    ],

    :s_comment => [
        [/^.+?(?=\*\/)/,      :sym_comment,       :s_comment],
        [/^\*\//,             :sym_comment_end,   :s_root],
        [/.*/,                :sym_comment,       :s_comment],
    ]
}

KEYWORDS = [ "char", "const", "double", "float", "int", "long", "register",
             "short", "signed", "unsigned", "void", "volatile", "uint8_t",
             "uint16_t", "uint32_t", "uint64_t", "int8_t", "int16_t", "int32_t",
             "int64_t", "__FILE__", "__LINE__", "__DATE__", "__TIME__",
             "__TIMESTAMP__", "__cplusplus", "__func__", "__PRETTY_FUNCTION__"]

KEYWORDS_BOLD = ["for", "while", "if", "else", "auto", "break", "case",
                 "continue", "default", "do", "else", "enum", "extern", "for",
                 "goto", "if", "inline", "restrict", "return", "sizeof",
                 "static", "struct", "switch", "typedef", "union", "volatile",
                 "while"]

$pp_lang = {
    :s_pp_root => [
        [/^\/\/.*/,           :pp_sym_comment,        :s_pp_root],
        [/^\/\*/,             :pp_sym_comment_start,  :s_pp_comment],
        [/^\s+/,              :pp_sym_spaces,         :s_pp_root],

        [/^\\$/,              :pp_sym_esc_nl,         :s_pp_root],

        [/^(0x|0X)[a-fA-F0-9]+/,  :pp_sym_num,        :s_pp_root],
        [/^\d+/,              :pp_sym_num,            :s_pp_root],

        [/^include(?:\s)/,    :pp_sym_include,        :s_pp_include],
        [/^\w+/,              :pp_sym_word,           :s_pp_root],
        [/^##/,               :pp_sym_word,           :s_pp_root],
        [/^[\[\]{},.*();<>=\-^%!+&?:|~\/]/,
                              :pp_sym_single_char,    :s_pp_root],
        [/^"/,                :pp_sym_string_start,   :s_pp_string],
    ],

    :s_pp_include => [
        [/^\s+/,              :pp_sym_spaces,         :s_pp_include],
        [/^("|<)/,            :pp_include_start,      :s_pp_include_path],
    ],

    :s_pp_include_path => [
        [/^("|>)/,            :pp_include_end,        :s_pp_root],
        [/^[^">]+/,           :pp_include_path,       :s_pp_include_path],
    ],

    :s_pp_string => [
        [/^(?:[^"\\]|\\.)+/,  :pp_sym_string_data,    :s_pp_string],
        [/"/,                 :pp_sym_string_end,     :s_pp_root],
        [/\\$/,               :pp_sym_string_multi,   :s_pp_string]
    ],

    :s_pp_comment => [
        [/^.+?(?=\*\/)/,      :pp_sym_comment,        :s_pp_comment],
        [/^\*\//,             :pp_sym_comment_end,    :s_pp_root],
        [/.*/,                :pp_sym_comment,        :s_pp_comment],
    ]
}

PP_KEYWORDS = ["include", "pragma", "define", "error", "warning", "undef", "if",
               "else", "elif", "endif", "ifdef", "ifndef", "line" ]


class CLexer
    attr_reader :root
    def initialize
        @root         = []
        @stack        = []

        @stack << @root

        @state        = :s_root
        @line_state   = :LINE_STATE_ROOT

        @pp_state     = :s_pp_root
    end

    def process_element l, file, line
        $lang[@state].each do |e|
            m = e[0].match(l)
            #puts "Try match #{e[0].to_s} #{l}"
            if m
                #puts "MATCH #{line} #{@stack.size} #{e[1].to_s} #{m[0]}"
                @state = e[2]
                obj = {:sym => e[1], :match_txt => m[0], :line => line, :file => file}
                @stack[-1] << obj

                if m[0] == "{" or m[0] == "(" or m[0] == "[" or m[0] == "/*"
                    obj[:kids] = []
                    @stack << obj[:kids]
                elsif m[0] == "}" or m[0] == ")" or m[0] == "]" or m[0] == "*/"
                    @stack.pop
                end

                return m
            end
        end

        raise "#{__LINE__}> NO MATCH: line: #{line}: #{l}"
    end

    def process_elements l, file, line
        l.chomp!
        while l.size > 0
            m = process_element(l, file, line)
            l = m.post_match
        end

        @stack[-1] << {:sym => :sym_new_line, :match_txt => "\n", :line => line, :file => file}
    end

    def pp_process_element l, file, line
        #puts "#{__LINE__}> PP #{line} #{l}"
        $pp_lang[@pp_state].each do |e|
            m = e[0].match(l)
            #puts "Try match #{e[0].to_s} #{l}"
            if m
                #puts "MATCH #{line} #{@stack.size} #{e[1].to_s} #{m[0]}"
                @pp_state = e[2]
                obj = {:sym => e[1], :match_txt => m[0], :line => line, :file => file}
                @stack[-1] << obj

                if m[0] == "{" or m[0] == "(" or m[0] == "[" or m[0] == "/*"
                    obj[:kids] = []
                    @stack << obj[:kids]
                elsif m[0] == "}" or m[0] == ")" or m[0] == "]" or m[0] == "*/"
                    @stack.pop
                end

                return m
            end
        end

        raise "#{__LINE__}> NO PP MATCH: #{l}"
    end

    def pp_process_elements l, file, line
        l.chomp!
        while l.size > 0
            m = pp_process_element(l, file, line)
            l = m.post_match
        end

        @stack[-1] << {:sym => :pp_sym_new_line, :match_txt => "\n", :line => line, :file => file}
    end

    def process_line l, file, line
        #puts "#{__LINE__}> #{line}:#{l}"
        l.chomp!
        case @line_state
        when :LINE_STATE_ROOT
            case l
            when /^(\s*#)(.*)/
                if l[-1] == '\\'
                    @line_state = :LINE_STATE_PP
                end

                obj = {:sym => :sym_pp, :match_txt => $1, :line => line, :file => file, :kids => []}
                @stack[-1] << obj
                @stack << obj[:kids];
                pp_process_elements $2, file, line
                @stack.pop if @line_state != :LINE_STATE_PP
            else
                process_elements l, file, line
            end

        when :LINE_STATE_PP
            pp_process_elements l, file, line

            if l[-1] != '\\'
                @line_state = :LINE_STATE_ROOT
                @stack.pop
            end

        else
            raise
        end
    end

end

$lexer_cache = {}
$include_index = {}

def get_symbol_sequence path
    b = $lexer_cache[path]
    return b if b

    if path =~ /.*include\/(.*)/
        $include_index[$1] = path
    end

    cl = CLexer.new

    l = 0
    File.readlines(path).each do |line|
        l += 1
        cl.process_line line, path, l # TODO, too hacky...
    end

    $lexer_cache[path] = cl.root
    return $lexer_cache[path]
end

def block_has_anyof b, type, words
    b.each do |e|
        return e if e[:sym] == type and words.include?(e[:match_txt])
    end

    return nil
end

def sc_match e, m
    if e[:sym] == :sym_single_char and e[:match_txt] == m
        return true
    else
        return false
    end
end

def block_has_not_anyof b, type, words
    if block_has_anyof b, type, words
        return false
    else
        return true
    end
end

def block_has b, type, word
    return block_has_anyof b, type, [word]
end

def block_get_last b, type
    b.reverse_each do |e|
        return e if e[:sym] == type
    end
    return nil
end

$symbol_index = {}

def symbol_obj_push name, cat, obj
    x = $symbol_index[name]
    if x.nil?
        $symbol_index[name] = { :decl => {}, :impl => {}, :use => {}, :articles => {}}
        x = $symbol_index[name]
    end

    if x[cat][obj[:file]].nil?
        x[cat][obj[:file]] = [ obj ]
    else
        x[cat][obj[:file]] << obj
    end

end

def record_symbols symbols
    block_sequence = []

    symbols.each do |x|
        next if [:sym_new_line, :sym_comment, :sym_comment_start, :sym_spaces].include? x[:sym]

        block_sequence << x

        consume = false
        is_pp = false

        if x[:match_txt] == ";"
            consume = true
        end

        # This is a complete function block
        if x[:match_txt] == "{" and block_has_not_anyof(block_sequence, :sym_word, ["typedef", "struct", "enum", "union"])
            consume = true
        end

        if x[:sym] == :sym_pp
            consume = true
            is_pp = true
        end

        next if not consume

        #puts "-----------------------------------"
        #pp block_sequence
        #puts "-----------------------------------"

        is_typedef = block_has(block_sequence, :sym_word, "typedef")
        is_sue = block_has_anyof(block_sequence, :sym_word, ["struct", "enum", "union"])
        has_block = block_has(block_sequence, :sym_single_char, "{")
        has_semi  = block_has(block_sequence, :sym_single_char, ";")
        has_args  = block_has(block_sequence, :sym_single_char, "(")


        if is_sue and not has_args
            #puts "SUE: #{x[:line]} #{x[:match_txt]}"
            name = nil
            typedef_name = nil
            found_start_point = false
            block_sequence.each do |e|
                next if e[:sym] != :sym_word and e[:sym] != :sym_single_char
                if found_start_point
                    if e[:sym] == :sym_word
                        name = e
                    end
                    break
                else
                    if e[:sym] == :sym_word and ["struct", "enum", "union"].include?(e[:match_txt])
                        found_start_point = true

                    end
                end
            end

            if is_typedef
                typedef_name = block_get_last block_sequence, :sym_word
            end

            #puts "name: #{name}"
            #puts "sue: #{is_sue[:match_txt]}"
            #puts "is_typedef: #{is_typedef}"
            #puts "typedef_name: #{typedef_name}"

            if name and typedef_name
                #puts "#{__LINE__} #{name[:line]} Declaration of #{is_sue[:match_txt]} #{name[:match_txt]} typedefed to #{typedef_name[:match_txt]}"
                symbol_obj_push name[:match_txt], :decl, { :type => is_sue[:match_txt], :file => name[:file], :line => name[:line] }
                symbol_obj_push typedef_name[:match_txt], :decl, { :type => is_sue[:match_txt], :file => name[:file], :line => name[:line] }

            elsif name
                #puts "#{__LINE__} #{name[:line]} Declaration of #{is_sue[:match_txt]} #{name[:match_txt]}"
                symbol_obj_push name[:match_txt], :decl, { :type => is_sue[:match_txt], :file => name[:file], :line => name[:line] }

            elsif typedef_name
                #puts "#{__LINE__} #{typedef_name[:line]} Declaration of #{typedef_name[:match_txt]} as #{is_sue[:match_txt]}"
                symbol_obj_push typedef_name[:match_txt], :decl, { :type => is_sue[:match_txt], :file => typedef_name[:file], :line => typedef_name[:line] }

            else
                #puts "#{__LINE__} #{is_sue[:line]} Ano of #{is_sue[:match_txt]}"
            end

            if has_block
                #puts "#{__LINE__} has block"

                case is_sue[:match_txt]
                when "enum"
                    has_block[:kids].each do |x|
                        next if x[:sym] != :sym_word
                        symbol_obj_push x[:match_txt], :decl, { :type => "enum_value", :file => x[:file], :line => x[:line] }
                    end
                when "struct"
                    last_sym_word = nil
                    has_block[:kids].each do |x|
                        if x[:sym] == :sym_word
                            last_sym_word = x
                        end

                        if x[:sym] == :sym_single_char and x[:match_txt] == ";" and last_sym_word

                            if typedef_name
                                #puts "#{typedef_name[:match_txt]}::#{last_sym_word[:match_txt]} at #{last_sym_word[:file]}:#{last_sym_word[:line]}"
                                symbol_obj_push("#{typedef_name[:match_txt]}::#{last_sym_word[:match_txt]}",
                                                :decl,
                                                { :type => "struct_field",
                                                  :file => last_sym_word[:file],
                                                  :line => last_sym_word[:line] })
                            end

                            if name
                                #puts "#{name[:match_txt]}::#{last_sym_word[:match_txt]} at #{last_sym_word[:file]}:#{last_sym_word[:line]}"
                                symbol_obj_push("#{name[:match_txt]}::#{last_sym_word[:match_txt]}",
                                                :decl,
                                                { :type => "struct_field",
                                                  :file => last_sym_word[:file],
                                                  :line => last_sym_word[:line] })
                            end

                            last_sym_word = nil
                        end
                    end
                end
            end

        elsif is_typedef
            ps = []
            funcptr_name = nil

            block_sequence.each do |e|
                if sc_match e, "("
                    ps << e
                end
            end

            if ps.size >= 2
                if ps[0][:kids].size == 3 and sc_match(ps[0][:kids][0], "*") and ps[0][:kids][1][:sym] == :sym_word and sc_match(ps[0][:kids][2], ")")
                    funcptr_name = ps[0][:kids][1]
                end
            end

            if funcptr_name
                name = funcptr_name
            else
                name = block_get_last block_sequence, :sym_word
            end

            #puts "#{name[:line]} Declaration of #{name[:match_txt]}"
            symbol_obj_push name[:match_txt], :decl, { :type => "typedef", :file => name[:file], :line => name[:line] }

        elsif is_pp

            block_sequence.each do |b|
                next if b[:sym] != :sym_pp
                next if b[:kids].size < 3
                next if b[:kids][0][:sym] != :pp_sym_word
                next if b[:kids][0][:match_txt] != "define"
                next if b[:kids][1][:sym] != :pp_sym_spaces
                next if b[:kids][2][:sym] != :pp_sym_word

                s = b[:kids][2]
                symbol_obj_push s[:match_txt], :decl, { :type => "pp_define", :file => s[:file], :line => s[:line] }
            end

        elsif has_args
            name = block_get_last block_sequence, :sym_word

            #puts "This is a function called: #{name}"

            if has_block and not has_semi
                symbol_obj_push name[:match_txt], :impl, { :type => "function", :file => name[:file], :line => name[:line] }

            elsif has_semi
                #puts "#{name[:line]} Function prototype #{name[:match_txt]}"
                symbol_obj_push name[:match_txt], :decl, { :type => "function", :file => name[:file], :line => name[:line] }

            end

        end

        block_sequence = []
    end
end

def declared_once decls
    cnt = 0

    decls[:decl].each do |k, v|
        cnt += v.size
    end

    return cnt == 1
end

def declared_here decls, sym
    f = decls[:decl][sym[:file]]

    return false if f.nil?

    f.each do |e|
        if e[:line] == sym[:line]
            return true
        end
    end

    return false
end

def print_html obj, symbols
    symbols.each do |x|
        ss = CGI.escapeHTML(x[:match_txt])

        sym_idx = $symbol_index[x[:match_txt]]

        if x[:sym] == :sym_word and KEYWORDS_BOLD.include?(x[:match_txt])
            s = "<span style=\"color:red;font-weight:bold;\">#{ss}</span>"
            obj[:html] += s

        elsif x[:sym] == :sym_word and KEYWORDS.include?(x[:match_txt])
            s = "<span style=\"color:red;\">#{ss}</span>"
            obj[:html] += s

        elsif [:sym_comment, :sym_comment_end, :sym_comment_start,
               :pp_sym_comment, :pp_sym_comment_start, :pp_sym_spaces].include?(x[:sym])
            s = "<span style=\"color:green;font-style:italic;\">#{ss}</span>"
            obj[:html] += s

        elsif [:sym_string_data].include?(x[:sym])
            s = "<span style=\"color:Maroon;\">#{ss}</span>"
            obj[:html] += s

        elsif [:sym_string_start, :sym_string_end].include?(x[:sym])
            s = "<span style=\"color:Maroon;font-weight:bold;\">#{ss}</span>"
            obj[:html] += s


        elsif x[:sym] == :sym_word and sym_idx
            # When browsing the code, we should jump directly the definition,
            # unless we are at the definition already, in that case we should go
            # to the sym-index page
            s = ""

            if declared_here sym_idx, x
                s = "<a href=\"#sym:#{x[:match_txt]}\">#{ss}</a>"
            else
                # We only go directly is there is only 1 uniq match
                if declared_once sym_idx
                    s = "<a href=\"#symd:#{x[:match_txt]}\">#{ss}</a>"
                else
                    s = "<a href=\"#sym:#{x[:match_txt]}\">#{ss}</a>"
                end
                symbol_obj_push x[:match_txt], :use, { :type => "use", :file => x[:file], :line => x[:line] }
            end
            obj[:html] += s

        elsif x[:sym] == :sym_pp or x[:sym] == :pp_sym_esc_nl
            s = "<span style=\"color:Purple;font-weight:bold;\">#{ss}</span>"
            obj[:html] += s

        elsif (x[:sym] == :pp_sym_word and PP_KEYWORDS.include?(x[:match_txt])) or x[:sym] == :pp_sym_include
            s = "<span style=\"color:Purple;font-weight:bold;\">#{ss}</span>"
            obj[:html] += s

        elsif x[:sym] == :pp_include_path
            p = $include_index[x[:match_txt]]
            if p
                s = "<a style=\"color:Purple;\" href=\"##{p}\">#{ss}</a>"
            else
                s = "<span style=\"color:Purple;\">#{ss}</span>"
            end
            obj[:html] += s

        elsif [:pp_sym_single_char, :pp_sym_string_start, :pp_sym_string_data, :pp_sym_string_end,
               :pp_include_start, :pp_include_end].include?(x[:sym])
            s = "<span style=\"color:Purple;\">#{ss}</span>"
            obj[:html] += s

        elsif x[:sym] == :pp_sym_word and $symbol_index[x[:match_txt]]
            s = "<a style=\"color:Purple;\" href=\"#sym:#{x[:match_txt]}\">#{ss}</a>"
            symbol_obj_push x[:match_txt], :use, { :type => "use", :file => x[:file], :line => x[:line] }
            obj[:html] += s

        elsif [:pp_sym_string_multi, :sym_string_multi].include?(x[:sym])
            s = "<span style=\"color:Purple;font-weight:bold;\">#{ss}</span>"
            obj[:html] += s

        elsif [:pp_sym_word].include?(x[:sym])
            s = "<span style=\"color:Purple;\">#{ss}</span>"
            obj[:html] += s


        else
            obj[:html] += ss

        end
        print_html(obj, x[:kids]) if x[:kids]
    end
end

def seq_to_html s, link
    html = ""
    obj = {:html => "" }
    print_html(obj, s)

    if true
        #html += "<table style=\"white-space: nowrap; padding: 0px; font-family: Menlo,Monaco,Consolas,\"Courier New\",monospace;\"><tr><td><pre>"
        html += "<table class=\"code\"><tr><td><pre class=\"lineno\">"
        obj[:html].lines.count.times do |l|
            html += "<a name=\"l#{l + 1}\" href=\"##{link}@l#{l + 1}\">#{l + 1}</a>\n"
        end
        html += "</pre></td><td><pre>"
        html += obj[:html]
        html += "</pre></td><tr></table>"

    else
        html += "<pre><table style=\"white-space: nowrap; font-family: Menlo,Monaco,Consolas,\"Courier New\",monospace;\">"
        i = 0;
        obj[:html].lines.each do |l|
            i += 1
            html += "<tr>"
            html += "<td><a name=\"l#{i}\" href=\"##{link}@l#{i}\">#{i}</a></td>"
            html += "<td>#{l}</td>"
            html += "</tr>"
        end
        html += "</table></pre>"

    end

    return html

end
