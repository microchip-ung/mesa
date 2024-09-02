#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'pp'
require 'optparse'
require 'fileutils'
require_relative './hdr_parser.rb'

# TODO: safe-cast functions
# TODO: get-before-set
# TODO: some kind of checksum for manual implemented methods
# TODO: auto skip if manual implemented

$options = {
    :base_dir => ".",
    :output_dir => ".",
}

OptionParser.new do |opts|
    opts.banner = "Usage: ag.rb [arguments] <header files>"

    opts.on("-b", "--base-dir DIR", "Base dir, input and output files are relative to this dir.") do |v|
        $options[:base_dir] = v.to_s.strip
    end

    opts.on_tail("-o", "--output-dir DIT", "Where to store the generated files (sources and cache files)") do |v|
        $options[:output_dir] = v.to_s.strip
    end

    opts.on_tail("--cache-only", "Only generate cache files") do
        $options[:cache_only] = true
    end

    opts.on_tail("-h", "--help", "Show this message") do
        puts opts
        exit
    end
end.parse!

if $options[:base_dir]
    Dir.chdir($options[:base_dir])
end

$options[:input_files] = ARGV

$do_trace = false
FileUtils.mkdir_p($options[:output_dir])
$log = File.open("#{$options[:output_dir]}/log.txt", "w")
if not $options[:cache_only]
    $rename = File.open("#{$options[:output_dir]}/rename", "w")
    $pp_rename = File.open("#{$options[:output_dir]}/mesa_pp_rename.h", "w")
    $c_hdr = File.open("#{$options[:output_dir]}/mesa.h", "w")
    $c_src = File.open("#{$options[:output_dir]}/mesa.c", "w")
    $c_hdr.puts "#include \"vtss_api.h\""
    $c_hdr.puts "#include <microchip/ethernet/switch/api.h>"
    $c_hdr.puts ""
    $c_hdr.puts "#ifndef __MESA_H__"
    $c_hdr.puts "#define __MESA_H__"

    $c_hdr.puts "#ifdef __cplusplus"
    $c_hdr.puts "extern \"C\" {"
    $c_hdr.puts "#endif"

    $pp_rename.puts "#ifndef __MESA_PP_RENAME__"
    $pp_rename.puts "#define __MESA_PP_RENAME__"

    $c_src.puts "#include \"mesa.h\""
    $c_src.puts ""
    $c_src.puts "#define __RC(expr) { vtss_rc __rc__ = (expr); if (__rc__ < VTSS_RC_OK) return __rc__; }"
    $c_src.puts "#pragma GCC diagnostic push"
    $c_src.puts "#pragma GCC diagnostic ignored \"-Wstrict-aliasing\""
    $c_src.puts "#pragma GCC diagnostic ignored \"-Wformat-security\""
end

def trace s = ""
    $log.puts s
    #puts s
end

$pp_stack = []
$types_blacklist = []
$types = {
    # hardcoded type aliases
    "BOOL"         => {:type_fam=>:type_alias, :type_name=>"BOOL",         :type_next=>"uint8_t",      :type_resolved=>{:type=>"uint8_t",      :abi=>:abi_stable}},
    "u8"           => {:type_fam=>:type_alias, :type_name=>"u8",           :type_next=>"uint8_t",      :type_resolved=>{:type=>"uint8_t",      :abi=>:abi_stable}},
    "u16"          => {:type_fam=>:type_alias, :type_name=>"u16",          :type_next=>"uint16_t",     :type_resolved=>{:type=>"uint16_t",     :abi=>:abi_stable}},
    "u32"          => {:type_fam=>:type_alias, :type_name=>"u32",          :type_next=>"uint32_t",     :type_resolved=>{:type=>"uint32_t",     :abi=>:abi_stable}},
    "u64"          => {:type_fam=>:type_alias, :type_name=>"u64",          :type_next=>"uint64_t",     :type_resolved=>{:type=>"uint64_t",     :abi=>:abi_stable}},
    "i8"           => {:type_fam=>:type_alias, :type_name=>"i8",           :type_next=>"int8_t",       :type_resolved=>{:type=>"int8_t",       :abi=>:abi_stable}},
    "i16"          => {:type_fam=>:type_alias, :type_name=>"i16",          :type_next=>"int16_t",      :type_resolved=>{:type=>"int16_t",      :abi=>:abi_stable}},
    "i32"          => {:type_fam=>:type_alias, :type_name=>"i32",          :type_next=>"int32_t",      :type_resolved=>{:type=>"int32_t",      :abi=>:abi_stable}},
    "i64"          => {:type_fam=>:type_alias, :type_name=>"i64",          :type_next=>"int64_t",      :type_resolved=>{:type=>"int64_t",      :abi=>:abi_stable}},
    "mesa_inst_t"  => {:type_fam=>:type_alias, :type_name=>"mesa_inst_t",  :type_next=>"mesa_inst_t",  :type_resolved=>{:type=>"mesa_inst_t",  :abi=>:abi_stable}},

    # terminal types
    "void"         => {:type_fam=>:type_alias, :type_name=>"void",         :type_next=>"void",         :type_resolved=>{:type=>"void",         :abi=>:abi_stable}},
    "void *"       => {:type_fam=>:type_alias, :type_name=>"void *",       :type_next=>"void *",       :type_resolved=>{:type=>"void *",       :abi=>:abi_stable}},

    "char"         => {:type_fam=>:type_alias, :type_name=>"char",         :type_next=>"char",         :type_resolved=>{:type=>"char",         :abi=>:abi_stable}},
    "char *"       => {:type_fam=>:type_alias, :type_name=>"char *",       :type_next=>"char *",       :type_resolved=>{:type=>"char *",       :abi=>:abi_stable}},
    "const char *" => {:type_fam=>:type_alias, :type_name=>"const char *", :type_next=>"const char *", :type_resolved=>{:type=>"const char *", :abi=>:abi_stable}},

    "int"          => {:type_fam=>:type_alias, :type_name=>"int",          :type_next=>"int",          :type_resolved=>{:type=>"int",          :abi=>:abi_stable}},
    "uint8_t"      => {:type_fam=>:type_alias, :type_name=>"uint8_t",      :type_next=>"uint8_t",      :type_resolved=>{:type=>"uint8_t",      :abi=>:abi_stable}},
    "uint16_t"     => {:type_fam=>:type_alias, :type_name=>"uint16_t",     :type_next=>"uint16_t",     :type_resolved=>{:type=>"uint16_t",     :abi=>:abi_stable}},
    "uint32_t"     => {:type_fam=>:type_alias, :type_name=>"uint32_t",     :type_next=>"uint32_t",     :type_resolved=>{:type=>"uint32_t",     :abi=>:abi_stable}},
    "uint64_t"     => {:type_fam=>:type_alias, :type_name=>"uint64_t",     :type_next=>"uint64_t",     :type_resolved=>{:type=>"uint64_t",     :abi=>:abi_stable}},
    "int8_t"       => {:type_fam=>:type_alias, :type_name=>"int8_t",       :type_next=>"int8_t",       :type_resolved=>{:type=>"int8_t",       :abi=>:abi_stable}},
    "int16_t"      => {:type_fam=>:type_alias, :type_name=>"int16_t",      :type_next=>"int16_t",      :type_resolved=>{:type=>"int16_t",      :abi=>:abi_stable}},
    "int32_t"      => {:type_fam=>:type_alias, :type_name=>"int32_t",      :type_next=>"int32_t",      :type_resolved=>{:type=>"int32_t",      :abi=>:abi_stable}},
    "int64_t"      => {:type_fam=>:type_alias, :type_name=>"int64_t",      :type_next=>"int64_t",      :type_resolved=>{:type=>"int64_t",      :abi=>:abi_stable}},
    "uintptr_t"    => {:type_fam=>:type_alias, :type_name=>"uintptr_t",    :type_next=>"uintptr_t",    :type_resolved=>{:type=>"uintptr_t",    :abi=>:abi_stable}},
    "vtss_inst_t"  => {:type_fam=>:type_alias, :type_name=>"vtss_inst_t",  :type_next=>"vtss_inst_t",  :type_resolved=>{:type=>"vtss_inst_t",  :abi=>:abi_stable}},
    "mesa_port_list_t" => {:type_fam=>:type_alias, :type_name=>"mesa_port_list_t",  :type_next=>"mesa_port_list_t",  :type_resolved=>{:type=>"mesa_port_list_t",  :abi=>:abi_stable}},
}
$methods = {}

$methods_impl_no_auto = []

$methods_blacklist = [
    "mesa_callout_trace_hex_dump",
    "mesa_callout_trace_printf",
    "mesa_callout_lock",
    "mesa_callout_unlock",
    "mesa_vlan_trans_group_to_port_get",
    "mesa_vlan_trans_group_to_port_set",
]

$conv_methods = {}

$error_suppress = [
    "impl-conv: mesa_cap_t",
    "impl-conv: mesa_cap_callback_t",


    # skipped for now...
    "impl-conv: mesa_serdes_fields_t",
    "impl-conv: mesa_mac_table_sr_t",
]

$allowed_array_indexes = [
    "VTSS_PORT_ARRAY_SIZE",
    "VTSS_PORTS"
]

$error_suppress = [
    #"NO-PEER-TYPE",
    #"TYPE-NOT-DECLARED",
    #"ENUM-NO-OVERLAP",
    #"FUNC-ARG",
    ##"FUNC-ARG-ARRAY",
    #"TYPE-RESOLVE",
    #"COMPAT-UNKNOWN",
]

$conv_skip_data = {}

def rename_sym a, b
    $rename.puts "s/\\b#{a}\\b/#{b}/g"
    $pp_rename.puts "#define #{a} #{b}"
end

def print_error err, str_error
    return if $error_suppress.include? str_error

    if /^([A-Z0-9\-_]+):.*/ =~ err.to_s
        if $error_suppress.include? $1
            return
        end
    end

    trace "--------------------------------------------------------------------"
    trace "ERROR: [#{str_error}] - #{err.to_s}"
    trace err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
    trace "--------------------------------------------------------------------"
end

def type_resolve t
    t_next = t
    while true
        tt = $types[t_next]

        if tt.nil?
            #puts "Can not resolve type: #{t}"
            return {:type => nil, :abi => :abi_unknown }
        end

        case tt[:type_fam]
        when :type_alias
            if tt[:type_name] == tt[:type_resolved][:type]
                # We found a terminal type
                #puts "#{t_next} -> #{tt[:type_next]}"
                #puts ""
                return {:type => tt[:type_name], :abi => tt[:type_resolved][:abi] }
            else
                #puts "#{t_next} -> #{tt[:type_next]} (again)"
                t_next = tt[:type_next]
                next
            end

        when :type_struct, :type_enum, :type_fptr
            # structs and enums are considered type terminals
            return {:type => tt[:type_name], :abi => tt[:type_resolved][:abi] }

        else
            raise # todo, unions??
        end
    end
end

def type_resolve_type t
    x = type_resolve t
    return nil if x.nil? or x[:type].nil?
    return $types[x[:type]]
end

def type_to_s t
    case t[:type_fam]
    when :type_alias
        if t[:type_array]
            "#{t[:type_name]} -> #{t[:type_next]}/#{t[:type_resolved][:type]} [#{t[:type_array].join(", ")}] (#{t[:type_resolved][:abi]})"
        else
            "#{t[:type_name]} -> #{t[:type_next]}/#{t[:type_resolved][:type]} (#{t[:type_resolved][:abi]})"
        end
    when :type_struct
        "struct #{t[:type_name]} (#{t[:type_resolved][:abi]})"
    when :type_enum
        "enum #{t[:type_name]} (#{t[:type_resolved][:abi]})"
    else
        raise t
    end
end

def resolve_all_types
    cnt_resolved = 1

    while cnt_resolved > 0
        cnt_resolved = 0
        $types.each do |k, v|
            next if v[:type_resolved][:abi] != :abi_unknown

            case v[:type_fam]
            when :type_alias
                v[:type_resolved] = type_resolve(v[:type_name])

            when :type_struct
                has_abi_unknown = false
                has_abi_unstable = false
                v[:members].each do |m|
                    next if m[:type_resolved][:abi] != :abi_unknown
                    m[:type_resolved] = type_resolve(m[:member_type])
                    case m[:type_resolved][:abi]
                    when :abi_unknown
                        has_abi_unknown = true
                    when :abi_unstable
                        has_abi_unstable = true
                    when :abi_stable
                    else
                        raise
                    end
                end

                if has_abi_unknown
                    v[:type_resolved][:abi] = :abi_unknown
                elsif has_abi_unstable or v[:properties].include?(:pp)
                    v[:type_resolved][:abi] = :abi_unstable
                else
                    v[:type_resolved][:abi] = :abi_stable
                end


            when :type_enum
                raise # enums are type terminals, they should always be resolved

            when :type_fptr
                has_abi_unknown = false
                has_abi_unstable = false
                v[:args].each do |m|
                    if m[:type_resolved][:abi] != :abi_unknown
                        has_abi_unknown = true
                        next
                    end
                    m[:type_resolved] = type_resolve(m[:arg_type][:type_base])
                    case m[:type_resolved][:abi]
                    when :abi_unknown
                        has_abi_unknown = true
                    when :abi_unstable
                        has_abi_unstable = true
                    when :abi_stable
                    else
                        raise
                    end
                end

                v[:return_type] = analyze_return_type(v[:type_ast][:typedef_fptr][:return_type])
                v[:return_type][:type_resolved] = type_resolve(v[:return_type][:type_base])

                case v[:return_type][:type_resolved][:abi]
                when :abi_unknown
                    has_abi_unknown = true
                when :abi_unstable
                    has_abi_unstable = true
                when :abi_stable
                else
                    raise
                end

                if has_abi_unknown
                    v[:type_resolved][:abi] = :abi_unknown
                elsif has_abi_unstable
                    v[:type_resolved][:abi] = :abi_unstable
                else
                    v[:type_resolved][:abi] = :abi_stable
                end
            else
                raise # todo
            end

            #puts type_to_s v
            cnt_resolved += 1 if v[:type_resolved][:abi] != :abi_unknown
        end
    end
end

def ast_type_to_str s
    return nil if s.nil?
    s.to_s.split(/\s+/).collect{|x| x.strip}.join(" ")
end

def handle_extern_c ast
    return if ast[:keyword] != "extern"
    return if ast[:string].nil?
    return if ast[:string] != "\"C\""
    return if ast[:root].nil?
    handle_root__ ast[:root]
end

def handle_typedef_alias t, ast
    a = ast_type_to_str(ast[:type_alias])
    r = type_resolve(a)
    x = {
        :type_fam => :type_alias,
        :type_name => t,
        :type_next => a,
        :type_resolved => r,
        :type_ast => ast,
        :pp_stack => $pp_stack.select{|e| e[:ignore].nil? }
    }
    if ast[:array] and ast[:array].size > 0
        x[:type_array] = ast[:array].collect{|x| x[:expr]}
    end

    $types[t] = x
    #puts "#{t}: #{type_to_s x}"
end

class HandleTypedefStruct
    def initialize ast, t
        @has_pp = false
        @has_abi_unstable_member = false
        @has_abi_unknown = false
        @has_unsupported = false
        @has_union = false
        @has_fptr = false
        @pp_stack_size_before = $pp_stack.size
        @members = []
        @struct_type_name = t

        if ast[:struct_type_declare]
            process_members ast[:struct_type_declare][:struct_members], []
        elsif ast[:union_type_declare]
            @has_union = true
            #process_members ast[:union_type_declare][:union_members], []
        else
            raise
        end

        process ast, t
    end

    def process_members member_list, mname
        member_list.each do |m|
            if m[:member] and m[:member][:normal]
                m = m[:member][:normal]
                raise if m.nil?
                tt = ast_type_to_str(m[:type])
                r = type_resolve(tt)
                mname << m[:name].to_s.strip
                x = {
                    :member_name => mname.join("."),
                    :member_type => tt,
                    :type_resolved => r,
                    :pp_stack => $pp_stack[@pp_stack_size_before..-1]
                }
                mname.pop
                if m[:array] and m[:array].size > 0
                    x[:type_array] = m[:array].collect{|x| x[:expr]}
                end

                case r[:abi]
                when :abi_unknown
                    @has_abi_unknown = true
                when :abi_unstable
                    @has_abi_unstable_member = true
                when :abi_stable
                else
                    raise "UNEXPECTED: Unexpected ABI: #{r[:abi]}"
                end

                @members << x

            elsif m[:member] and m[:member][:fptr]
                @has_fptr = true;
                # It is so much easer to handled "named" typedef, because then
                # we can guess the name of the "other" typedef to run the
                # compatibility analysis against
                raise "ANO-FUNC-PTR: Member function pointers must be declared as a typedef: #{@struct_type_name}:#{m[:member][:fptr][:fptr_name]}"

            elsif m[:pp]
                @has_pp = true;
                handle_pp m # handle pp-statements inlined in structs

            elsif m[:member_union]
                @has_union = true
                #begin
                #  mname << m[:member_union][:name]
                #  process_members m[:member_union][:union_type_declare][:union_members], mname
                #  mname.pop
                #rescue RuntimeError => err
                #    pp m
                #    raise
                #end

            elsif m[:member_struct]
                mname << m[:member_struct][:name]
                process_members m[:member_struct][:struct_type_declare][:struct_members], mname
                mname.pop
            else
                pp ast
                raise "UNEXPECTED: Unexpected element when processing #{t}"
            end
        end
    end

    def process ast, t
        @x = {
            :type_fam => :type_struct,
            :properties => [],
            :type_name => t,
            :type_resolved => {:type => t, :abi => nil},
            :members => @members,
            :type_ast => ast
        }

        @x[:properties] << :pp if @has_pp
        @x[:properties] << :abi_unstable_member if @has_abi_unstable_member
        @x[:properties] << :union if @has_union
        @x[:properties] << :fptr if @has_fptr

        if @has_abi_unknown
            @x[:type_resolved][:abi] = :abi_unknown
        elsif @has_pp or @has_abi_unstable_member
            @x[:type_resolved][:abi] = :abi_unstable
        else
            @x[:type_resolved][:abi] = :abi_stable
        end
    end

    def res
        return @x
    end

end

def handle_typedef_struct t, ast
    h = HandleTypedefStruct.new ast, t
    h.res[:pp_stack] = $pp_stack.select{|e| e[:ignore].nil? }
    $types[t] = h.res
    #puts "#{t}: #{type_to_s(h.res)}"
end

def handle_typedef_enum t, ast
    a = ast[:enum_type_declare]

    has_pp = false
    members = []

    pp_stack_size_before = $pp_stack.size
    a[:enums].each do |m|
        if m[:enum]
            m = m[:enum]
            raise if m.nil?
            x = {
                :enum_name => m[:enum_name].to_s.strip,
                :enum_expr => nil
            }

            if m[:expr]
                x[:enum_expr] = m[:expr].to_s.strip
            end

            x[:pp_stack] = $pp_stack[pp_stack_size_before..-1]

            members << x

        elsif m[:pp]
            has_pp = true;
            handle_pp m # handle pp-statements inlined in enums

        else
            raise "UNEXPECTED: Unexpected element when processing #{t}"
        end
    end

    x = {
        :type_fam => :type_enum,
        :properties => [],
        :type_name => t,
        :type_resolved => {
            :type => t,
            :abi => nil
        },
        :members => members,
        :type_ast => ast,
        :pp_stack => $pp_stack.select{|e| e[:ignore].nil? }
    }

    x[:properties] << :pp if has_pp

    if has_pp
        x[:type_resolved][:abi] = :abi_unstable
    else
        x[:type_resolved][:abi] = :abi_stable
    end

    $types[t] = x
end

def type_check_black_list t
    # Black list of types that are defined multiple places. We just want to ignore these types for now
    return false if $types_blacklist.include? t

    if not $types[t].nil?
        # this indicate that this is not a ABI stable type
        trace "Type #{t} defined multiple times"
        $types.delete t
        $types_blacklist << t
        return false
    end

    return true
end

def handle_typedef ast
    return if ast[:keyword] != "typedef"
    return if ast[:typedef_name].nil?

    t = ast[:typedef_name].to_s.strip

    return if ["i8", "i16", "i32", "i64",
               "u8", "u16", "u32", "u64",
               "BOOL", "uintptr_t",
               "vtss_inst_t", "mesa_inst_t"].include? t

    return if not type_check_black_list t

    if ast[:type_alias]
        handle_typedef_alias t, ast

    elsif ast[:struct_type_declare]
        handle_typedef_struct t, ast

    elsif ast[:enum_type_declare]
        handle_typedef_enum t, ast

    elsif ast[:union_type_declare]
        handle_typedef_struct t, ast

    else
        #pp ast if t == "vtss_packet_rx_port_conf_t"
        pp ast
        raise
    end
end

def analyze_return_type t
    t = ast_type_to_str(t)
    tt = t.split(/\s+|(?<=\*)/)  # split on spaces and '*', but include '*' as split token

    value_const = false
    ptr = false
    ptr_const = false
    base_type = []

    tt.each do |x|
        if x == "const"
            if ptr
                ptr_const = true
            else
                value_const = true
            end
        elsif x == "*"
            ptr = true
        else
            if ptr
                pp ast
                raise # type names not allowed after '*'
            end

            base_type << x
        end
    end

    base_type = base_type.join(" ") # Yes, base type can be several words, consider "unsigned int"

    return {
        :type_str => t,
        :ptr => ptr,
        :value_const => value_const,
        :ptr_const => ptr_const,
        :type_base => base_type,
        :type_resolved => $types[base_type],
    }
end

def analyze_arg ast
    t = ast[:normal]
    res = analyze_return_type(t[:type])

    dir = nil
    if res[:ptr] and !res[:value_const]
        dir = :DIR_OUT
    else
        dir = :DIR_IN
    end

    res[:direction] = dir
    res[:arg_name] = t[:name].to_s.strip
    res[:array] = t[:array].collect{|x| x[:expr].to_s.strip}

    return res


    ##a << "#{ast_type_to_str(e[:normal][:type])} #{e[:normal][:name].to_s.strip}"

    #t = ast[:normal]
    #tt = ast_type_to_str(t[:type]).split(/\s+|(?<=\*)/)  # split on spaces and '*', but include '*' as split token

    ##pp ast

    #value_const = false
    #ptr = false
    #ptr_const = false
    #base_type = []
    #direction = nil

    #tt.each do |x|
    #    if x == "const"
    #        if ptr
    #            ptr_const = true
    #        else
    #            value_const = true
    #        end
    #    elsif x == "*"
    #        ptr = true
    #    else
    #        if ptr
    #            pp ast
    #            raise # type names not allowed after '*'
    #        end

    #        base_type << x
    #    end
    #end

    #base_type = base_type.join(" ")

    #if ptr and !value_const
    #    direction = :DIR_OUT
    #else
    #    direction = :DIR_IN
    #end

    #return {
    #    :type_str => ast_type_to_str(t[:type]),
    #    :ptr => ptr,
    #    :value_const => value_const,
    #    :ptr_const => ptr_const,
    #    :type_base => base_type,
    #    :type_resolved => $types[base_type],
    #    :direction => direction,
    #    :arg_name => t[:name].to_s.strip,
    #    :array => t[:array].collect{|x| x[:expr].to_s.strip}
    #}
end

def analyze_args ast
    return [] if ast.size == 1 and ast[0][:keyword] and ast[0][:keyword] == "void"

    args = []
    ast.each do |e|
        a = analyze_arg(e)
        #puts ">>>>>>"
        args << a
        #pp a
        #puts "<<<<<<"
    end

    return args
end


def handle_typedef_fptr ast
    return if ast[:keyword] != "typedef"
    return if ast[:typedef_fptr].nil?

    a = ast[:typedef_fptr]
    t = a[:fptr_name].to_s.strip

    return if not type_check_black_list t

    args = []
    a[:args].each do |m|
        next if a[:args].size == 1 and m[:keyword] and m[:keyword] == "void"

        arg_type = analyze_arg m

        x = {
            :arg_name => m[:normal][:name].to_s.strip,
            :arg_type => arg_type,
            :type_resolved => type_resolve(arg_type[:type_base])
        }

        if m[:array] and m[:array].size > 0
            x[:type_array] = m[:array].collect{|x| x[:expr]}
        end

        args << x
    end

    res = {
        :type_fam => :type_fptr,
        :type_name => t,
        :args => args,
        :type_ast => ast,
        :type_resolved => {:type => t, :abi => :abi_unknown},
        :pp_stack => $pp_stack.select{|e| e[:ignore].nil? }
    }

    $types[t] = res
end

def handle_func_proto ast
    #pp ast
    return if ast[:func_proto].nil?
    return if ast[:func_proto][:normal].nil?
    f = ast[:func_proto]
    f[:pp_stack] = []

    $pp_stack.each do |e|
        next if not e[:ignore].nil?
        f[:pp_stack] << e
    end

    n = f[:normal][:name].to_s.strip

    $methods[n] = f

#    r = ast_type_to_str(f[:normal][:type])
#    a = []
#
#    handle_args f[:args]
#    #f[:args].each do |e|
#    #    next if e[:keyword] && e[:keyword] == "void"
#    #    a << "#{ast_type_to_str(e[:normal][:type])} #{e[:normal][:name].to_s.strip}"
#    #end
#
#    #puts "-----------------> #{r} #{n}(#{a.join(", ")})"
#
#    return
#
#    puts """#{r} #{n}(#{a.join(", ")})
#{
#    return -1;
#}
#
#"""
end

def handle_pp ast
    return if ast[:pp].nil?
    p = ast[:pp].to_s.strip

    case p
    when /^\s*#\s*ifndef\s+(.*)/
        $pp_stack << { :type => :ifndef, :expr => $1 }
        #puts $pp_stack.last

    when /^\s*#\s*ifdef\s+(.*)/
        $pp_stack << { :type => :ifdef, :expr => $1 }
        $pp_stack.last[:ignore] = :cplusplus if $1 == "__cplusplus"
        #puts $pp_stack.last

    when /^\s*#\s*endif/
        $pp_stack.pop

    when /^\s*#\s*define\s+(.*)/
        if ($pp_stack.size == 1 and
            $pp_stack[0][:type] == :ifndef and
            $pp_stack[0][:expr] == $1)
            $pp_stack[0][:ignore] = :file_guard
        end

    when /^\s*#\s*else/
        last = $pp_stack.pop
        seq = []
        seq = last[:seq] if not last[:seq].nil?
        last.delete :seq
        seq << last
        $pp_stack << { :type => :else, :seq=> seq }
        #puts $pp_stack.last

    when /^\s*#\s*elif\s+(.*)/
        last = $pp_stack.pop
        seq = []
        seq = last[:seq] if not last[:seq].nil?
        last.delete :seq
        seq << last
        $pp_stack << { :type => :elif, :expr => $1, :seq => seq }
        #puts $pp_stack.last

    when /^\s*#\s*if\s+(.*)/
        $pp_stack << { :type => :if, :expr => $1 }
        #puts $pp_stack.last

    when /^\s*#\s*error /
    when /^\s*#\s*include/
    when /^\s*#\s*undef/
    else
        pp ast
        #puts ">#{p}<"
        raise
    end

    #puts $pp_stack.size
end

def handle_root__ ast
    ast.each do |e|
        #begin
            handle_extern_c e
            handle_typedef e
            handle_typedef_fptr e
            handle_func_proto e
            handle_pp e
        #rescue RuntimeError => err
        #    puts "Parse error!!!"
        #    pp e
        #    puts err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
        #end
    end
end

def handle_root ast
    #puts "-------------------------------------------------"
    #pp ast
    #puts "-------------------------------------------------"

    handle_root__ ast

    if $pp_stack.size != 0
        pp $pp_stack
        raise "UNEXPECTED: PP-Stack not empty at EOF!!!" if $pp_stack.size != 0
    end

end

#parser = CParser.new()
#ast = parser.parse("""
#enum {
#    VTSS_RC_OK                                  =  0,  /**< Success */
#    VTSS_RC_ERROR                               = -1,  /**< Unspecified error */
#};
#""", :reporter => Parslet::ErrorReporter::Deepest.new)
#pp ast

$options[:input_files].each do |x|
    begin
        next if x == "./mesa/include/microchip/ethernet/switch/api/utils.h"
        next if x == "./mesa/include/microchip/ethernet/hdr_end.h"
        next if x == "./mesa/include/microchip/ethernet/hdr_start.h"
        next if x == "./mesa/include/microchip/ethernet/switch/api/port_list.h"
        next if x == "./include/vtss_os_ecos.h"
        next if x == "./include/vtss_os_linux.h"
        next if not (/.*\.h$/ =~ x)

        o_dir = "#{$options[:output_dir]}/#{File.dirname(x)}"
        FileUtils.mkdir_p(o_dir)

        ast = nil
        cache_file = "#{$options[:output_dir]}/#{x}.cache"
        if File.exist?(cache_file) and File.mtime(cache_file) > File.mtime(x)
            trace "Loading cache #{cache_file}"
            File.open(cache_file, "r"){|f| ast = Marshal.load(f)}

        else
            trace "Parsing #{x}"
            parser = CParser.new()
            ast = parser.parse(IO.binread(x), :reporter => Parslet::ErrorReporter::Deepest.new)
            File.open(cache_file, "w"){|f| Marshal.dump(ast, f)}
        end

        $pp_stack = []
        handle_root ast[:root]

    rescue Parslet::ParseFailed => error
        trace error.cause.ascii_tree
        trace "Failed #{x}"

    rescue RuntimeError => err
        trace "Failed #{x}"
        trace err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
    end
end

if $options[:cache_only]
    exit
end

def abi_compatibility_check_alias_conv x
    return x if x[:type_fam] != :type_alias
    return nil if x[:type_resolved][:type].nil?
    return $types[x[:type_resolved][:type]]
end

def abi_compatibility_check_enum _m, _v
    return :COMPATIBILITY_CONV_NEEDED if _m[:type_resolved][:abi] != :abi_stable
    return :COMPATIBILITY_CONV_NEEDED if _v[:type_resolved][:abi] != :abi_stable
    return :COMPATIBILITY_CONV_NEEDED if _m[:members].size != _v[:members].size

    _m[:members].size.times do |i|
        em = _m[:members][i][:enum_name]
        ev = _v[:members][i][:enum_name]

        em_ = nil
        ev_ = nil

        if /MESA_(.*)/ =~ em
            em_ = $1
        end

        if /VTSS_(.*)/ =~ ev
            ev_ = $1
        end

        # check that the value of the enumerated symbols matches
        return :COMPATIBILITY_CONV_NEEDED if _m[:members][i][:enum_expr] != _v[:members][i][:enum_expr]

        # check that the enumerated values has the same names (except for prefix)
        return :COMPATIBILITY_CONV_NEEDED if em_.nil? or ev_.nil?
        return :COMPATIBILITY_CONV_NEEDED if em_ != ev_
    end

    return :COMPATIBILITY_CAST
end

def abi_compatibility_check_struct _m, _v
    return :COMPATIBILITY_CONV_NEEDED if _m[:type_resolved][:abi] != :abi_stable
    return :COMPATIBILITY_CONV_NEEDED if _v[:type_resolved][:abi] != :abi_stable
    return :COMPATIBILITY_CONV_NEEDED if _m[:members].size != _v[:members].size

    # TODO, union

    _m[:members].size.times do |i|
        mm = _m[:members][i]
        mv = _v[:members][i]

        # Array indexes must match
        if mm[:type_array] != mv[:type_array]
            # if one is array, and the other is not - then give-up
            return :COMPATIBILITY_CONV_NEEDED if mm[:type_array].nil? or mv[:type_array].nil?

            # if the two arrays has different dimentions - then give-up
            return :COMPATIBILITY_CONV_NEEDED if mm[:type_array].size != mv[:type_array].size

            # if a PP-symbol is used to specify the array length, then see if it matches
            mm[:type_array].size.times do |j|
                arr_m = mm[:type_array][j].to_s.strip
                arr_v = mv[:type_array][j].to_s.strip

                if arr_m != arr_v
                    if /^MESA_(.*)$/ =~ arr_m
                        return :COMPATIBILITY_CONV_NEEDED if "VTSS_#{$1}" != arr_v
                    else
                        return :COMPATIBILITY_CONV_NEEDED
                    end
                end
            end
        end

        # recursive check of member types
        x = abi_compatibility_check($types[mm[:member_type]], $types[mv[:member_type]])
        case x
        when :COMPATIBILITY_CAST, :COMPATIBILITY_SAME
            # do nothing

        when :COMPATIBILITY_CONV_NEEDED
            return x
        else
            raise x
        end
    end

    return :COMPATIBILITY_CAST
end

def abi_compatibility_check _m, _v
    m = abi_compatibility_check_alias_conv _m
    v = abi_compatibility_check_alias_conv _v

    return :COMPATIBILITY_UNKNOWN if m.nil? or v.nil?  # types could not be resolved!
    return :COMPATIBILITY_CONV_NEEDED if m[:type_fam] != v[:type_fam]
    return :COMPATIBILITY_SAME if m[:type_name] == v[:type_name] # if the underlaying type is the same (int, uint32_t etc)
    return :COMPATIBILITY_CAST if m[:type_name] == "mesa_inst_t" and v[:type_name] == "vtss_inst_t"

    case m[:type_fam]
    when :type_enum
        return abi_compatibility_check_enum m, v
    when :type_struct
        return abi_compatibility_check_struct m, v

    when :type_fptr
        comp_unknown = false;
        comp_conv_needed = false;
        comp_same = false;
        comp_cast = false;

        # Check compatibility for return types
        return_m = $types[m[:return_type][:type_base]]
        return_v = $types[v[:return_type][:type_base]]
        return_compatibility = abi_compatibility_check return_m, return_v

        case return_compatibility
        when :COMPATIBILITY_UNKNOWN
            comp_unknown = true
        when :COMPATIBILITY_CONV_NEEDED
            comp_conv_needed = true
        when :COMPATIBILITY_SAME
            comp_same = true
        when :COMPATIBILITY_CAST
            comp_cast = true
        else
            raise return_compatibility
        end

        mesa_args = m[:args]
        vtss_args = v[:args]

        if mesa_args.size != vtss_args.size
            return :COMPATIBILITY_CONV_NEEDED
        end

        # check if arguments are compatible
        mesa_args.size.times do |i|
            arg_m = $types[mesa_args[i][:arg_type][:type_base]]
            arg_v = $types[vtss_args[i][:arg_type][:type_base]]

            arg_compatibility = abi_compatibility_check arg_m, arg_v

            case arg_compatibility
            when :COMPATIBILITY_UNKNOWN
                comp_unknown = true
            when :COMPATIBILITY_CONV_NEEDED
                comp_conv_needed = true
            when :COMPATIBILITY_SAME
                comp_same = true
            when :COMPATIBILITY_CAST
                comp_cast = true
            else
                raise return_compatibility
            end
        end

        # aggegrate the results
        res = :COMPATIBILITY_UNKNOWN
        if comp_conv_needed
            res = :COMPATIBILITY_CONV_NEEDED
        elsif comp_cast
            res = :COMPATIBILITY_CAST
        elsif comp_same
            res = :COMPATIBILITY_SAME
        end

        return res

    when :type_alias
        if m[:type_name] == m[:type_next] and v[:type_name] == v[:type_next]
            # different base types is often an error!!!
            return :COMPATIBILITY_UNKNOWN
        else
            return abi_compatibility_check $types[m[:type_next]], $types[v[:type_next]]
        end

    else
        pp m[:type_fam]
        raise
    end
end

def abi_compatibility_check_str a, b
    t_a = type_resolve_type a
    t_b = type_resolve_type b

    if t_a.nil?
        raise "TYPE-NOT-DECLARED: Type not found in database: #{a}"
    end

    if t_b.nil?
        raise "TYPE-NOT-DECLARED: Type not found in database: #{b}"
    end

    if /^MESA_.*/i =~ a and /^VTSS_.*/i =~ b
         /^MESA_(.*)/i =~ a
        p_a = $1

         /^VTSS_(.*)/i =~ b
        p_b = $1

        if p_a != p_b
            return :COMPATIBILITY_UNKNOWN
        end

        return abi_compatibility_check t_a, t_b

    elsif /^MESA_.*/i =~ b and /^VTSS_.*/i =~ a
        abi_compatibility_check_str b, a
    elsif (not /^MESA_.*/i =~ a) and (not /^VTSS_.*/i =~ b)
        return abi_compatibility_check t_a, t_b
    else
        return abi_compatibility_check t_a, t_b
    end
end

def map_types
    resolve_all_types

    $types.each do |k, v|
        mesa = k;
        vtss = ""
        if /mesa_(.*)/ =~ k
            vtss = "vtss_#{$1}";
        else
            next
        end

        x = $types[vtss]
        next if x.nil? # no peer type

        c = abi_compatibility_check v, x
        #puts "#{c}(#{mesa}, #{vtss})"

        $types[vtss][:peer] = { :type_name => mesa, :compatibility => c }
        $types[mesa][:peer] = { :type_name => vtss, :compatibility => c }
    end
end

def impl_pp_stack_begin stack
    code = []

    stack.each do |p|
        if not p[:seq].nil?
            code.concat(impl_pp_stack_begin(p[:seq]))
            #p[:seq].each do |x|
            #    code << "##{x[:type].to_s} #{x[:expr]}"
            #end
        end
        if (p[:expr] and p[:expr].size > 0)
            code << "##{p[:type].to_s} #{p[:expr]}"
        else
            code << "##{p[:type].to_s}"
        end
    end

    return code
end

def impl_pp_stack_end stack
    code = []

    stack.reverse.each do |p|
        if (p[:expr] and p[:expr].size > 0)
            code << "#endif  // #{p[:expr]}"
        else
            code << "#endif"
        end
    end

    return code
end

def impl_conv_function_body_enum from, to, do_renames = false
    x = []
    code = []
    sym_used = []
    sym_skipped = []

    def build_hash enum
        h = {} # key => [ vals ]
        enum[:members].each do |e|
            base = e
            if /^(VTSS_|MESA_)(.*)/ =~ e[:enum_name]
                base = $2
            end

            if h[base].nil?
                h[base] = [e]
            else
                h[base] << e
            end
        end
        return h
    end

    hash_from = build_hash from
    hash_to = build_hash to

    hash_from.each do |base, from_|
        to_ = hash_to[base]
        next if to_.nil?

        # The same enum value may be defined multiple time (guarded by different
        # if'defs)
        from_.each do |from|
            to_.each do |to|
                x << { :f => from[:enum_name], :t => to[:enum_name], :pp => (from[:pp_stack] + to[:pp_stack])}
                sym_used << from[:enum_name]
                sym_used << to[:enum_name]

                if do_renames
                    if /^(MESA_)(.*)/ =~ from[:enum_name]
                        rename_sym to[:enum_name], from[:enum_name]
                    elsif /^(MESA_)(.*)/ =~ to[:enum_name]
                        rename_sym from[:enum_name], to[:enum_name]
                    end
                end

            end
        end
    end

    from[:members].each do |from_e|
        sym_skipped << from_e[:enum_name] if not sym_used.include? from_e[:enum_name]
    end

    to[:members].each do |to_e|
        sym_skipped << to_e[:enum_name] if not sym_used.include? to_e[:enum_name]
    end

    raise "ENUM-NO-OVERLAP: Enum has no overlapping symbols!" if x.size == 0

    code << "switch (*in) {"
    sym_skipped.each do |e|
        code << "    // skipped: #{e}"
    end
    x.each do |e|
        code.concat(impl_pp_stack_begin(e[:pp]))
        code << "    case #{e[:f]}:"
        code << "        *out = #{e[:t]};"
        code << "        return VTSS_RC_OK;"
        code.concat(impl_pp_stack_end(e[:pp]))
    end
    code << "    default:"
    code << "        return VTSS_RC_ERROR;"
    code << "}"

    return code
end

def impl_conv_function_body_struct from, to
    x = [] # list of all conversion lines (common members for all ifdef-passes)
    code = []
    sym_used_from = []
    sym_used_to = []
    sym_skipped = []

    def build_hash struct
        h = {} # key => [ vals ]
        struct[:members].each do |e|
            n = e[:member_name]
            if h[n].nil?
                h[n] = [e]
            else
                h[n] << e
            end
        end
        return h
    end

    hash_from = build_hash from
    hash_to = build_hash to

    hash_from.each do |base, from_|
        to_ = hash_to[base]
        next if to_.nil?

        # The same member may be defined multiple time (guarded by different
        # if'defs)
        from_.each do |from|
            to_.each do |to|
                x << {
                    :f => from,
                    :t => to,
                    :pp => (from[:pp_stack] + to[:pp_stack])
                }
                sym_used_from << from[:member_name]
                sym_used_to << to[:member_name]
            end
        end
    end

    from[:members].each do |m|
        sym_skipped << { :member_name => m[:member_name], :type_name => from[:type_name] } if not sym_used_from.include? m[:member_name]
    end

    to[:members].each do |m|
        sym_skipped << { :member_name => m[:member_name], :type_name => to[:type_name] } if not sym_used_to.include? m[:member_name]
    end

    raise "STRUCT-NO-OVERLAP: No matching symbols" if x.size == 0

    skipping_mesa_symbols = false
    skipping_vtss_symbols = false
    skipping_unknown_symbols = false
    sym_skipped.each do |e|
        if /^mesa_.*/i =~ e[:type_name]
            skipping_mesa_symbols = true
        elsif /^vtss_.*/i =~ e[:type_name]
            skipping_vtss_symbols = true
        else
            trace "None-prefixed type: #{e[:type_name]}"
            skipping_unknown_symbols = true
            skipping_vtss_symbols = true
            skipping_mesa_symbols = true
        end

        code << "// skipped: #{e[:member_name]}@#{e[:type_name]}"
    end

    if from[:properties].include? :union or to[:properties].include? :union
        skipping_mesa_symbols = true
    end

    $conv_skip_data[from[:type_name]] = { :skip_mesa => skipping_mesa_symbols, :skip_vtss => skipping_vtss_symbols }
    if skipping_mesa_symbols
        reg_conv from[:type_name], to[:type_name], (from[:pp_stack] + to[:pp_stack]), nil, nil, "conv2"
    end

    x.each do |e|
        code.concat(impl_pp_stack_begin(e[:pp]))

        call_conv_on_array = false

        if e[:t][:type_array] != e[:f][:type_array]
            if ((e[:t][:type_array].nil? or e[:f][:type_array].nil?) or
               (e[:t][:type_array].size != e[:f][:type_array].size))

                # Arrays dimnetions does not match - but if this is one of the
                # many arrays that is using 'VTSS_PORT_ARRAY_SIZE', then we are
                # going to support it any way...

                arr_size = nil
                arr_type = nil
                if (e[:t][:type_array].nil? and
                    e[:t][:member_type] == "mesa_port_list_t" and
                    e[:f][:type_array] and
                    e[:f][:type_array].size == 1)
                    arr_size = e[:f][:type_array][0]
                    arr_type = e[:f][:type_resolved][:type]
                elsif (e[:f][:type_array].nil? and
                       e[:f][:member_type] == "mesa_port_list_t" and
                       e[:t][:type_array] and
                       e[:t][:type_array].size == 1)
                    arr_size = e[:t][:type_array][0]
                    arr_type = e[:t][:type_resolved][:type]
                end

                if $allowed_array_indexes.include? arr_size
                    # TODO, manual conversion function needed!
                    call_conv_on_array = true
                    tt = $types[arr_type]
                    reg_conv e[:f][:member_type], e[:t][:member_type], tt[:pp_stack], e[:f][:type_array], e[:t][:type_array]

                else
                    #pp e
                    raise "ARRAY-DIM: Array dimentions does not match: #{e[:t][:member_name]}/#{e[:f][:member_name]}"
                end
            end
        end

        array = false
        pre_space = ""
        array_accessor = ""
        from_accessor = "&"
        to_accessor = "&"
        array_idx = 0
        array_loop_vars = ["i", "j", "k", "l", "m"]
        if not call_conv_on_array
            if e[:t][:type_array] and e[:t][:type_array].size
                e[:t][:type_array].each do |x|
                    loop_var = array_loop_vars[array_idx]
                    array_accessor << "[#{loop_var}]"
                    accessor = ""
                    code << "#{pre_space}for (size_t #{loop_var} = 0; #{loop_var} < #{x}; ++#{loop_var}) {"
                    array_idx += 1
                    pre_space += "    "
                end
            end

        else
            to_accessor   = "" if e[:t][:type_array]
            from_accessor = "" if e[:f][:type_array]

        end

        c = abi_compatibility_check_str e[:t][:member_type], e[:f][:member_type]
        c = :COMPATIBILITY_CONV_NEEDED if call_conv_on_array
        case c
        when :COMPATIBILITY_UNKNOWN
            raise "COMPAT-UNKNOWN: Compatibility unknown. member: #{e[:f][:member_name]} member-type: #{e[:t][:member_type]}/#{e[:f][:member_type]} in structure: #{to[:type_name]}/#{from[:type_name]}"
        when :COMPATIBILITY_CONV_NEEDED
            code << "#{pre_space}__RC(#{conv_function_name("conv", e[:f][:member_type], e[:t][:member_type])}(#{from_accessor}in->#{e[:f][:member_name]}#{array_accessor}, #{to_accessor}out->#{e[:t][:member_name]}#{array_accessor})); /* ag.rb:#{__LINE__} */"


            #m = conv_function_name("conv", e[:f][:member_type], e[:t][:member_type])
            #if m == "mesa_conv_uint8_t_to_mesa_port_list_t"
            #    puts "call_conv_on_array: #{call_conv_on_array}"
            #    pp e
            #    exit
            #end

        when :COMPATIBILITY_CAST
            if pre_space == ""
                code << "{"
                code << "    const #{e[:t][:member_type]} *tmp = (const #{e[:t][:member_type]} *)&in->#{e[:f][:member_name]}#{array_accessor};"
                code << "#ifdef __cplusplus"
                code << "    static_assert(sizeof(out.#{e[:t][:member_name]}#{array_accessor}) == sizeof(*tmp), \"size check\");"
                code << "#endif // __cplusplus"
                code << "    out->#{e[:t][:member_name]}#{array_accessor} = *tmp;"
                code << "}"
            else
                code << "const #{pre_space}#{e[:t][:member_type]} *tmp = (const #{e[:t][:member_type]} *)&in->#{e[:f][:member_name]}#{array_accessor};"
                code << "#{pre_space}out->#{e[:t][:member_name]}#{array_accessor} = *tmp;"
            end
        when :COMPATIBILITY_SAME
            code << "#{pre_space}out->#{e[:t][:member_name]}#{array_accessor} = in->#{e[:f][:member_name]}#{array_accessor};"
        else
            raise c
        end

        if not call_conv_on_array
            if e[:t][:type_array] and e[:t][:type_array].size
                e[:t][:type_array].each do |x|
                    if /^    (.*)/ =~ pre_space
                        pre_space = $1
                    end
                    code << "#{pre_space}}"
                end
            end
        end

        code.concat(impl_pp_stack_end(e[:pp]))
    end

    code << ""
    if skipping_mesa_symbols
        code << "return #{conv_function_name("conv2", from[:type_name], to[:type_name])}(in, out); /* ag.rb:#{__LINE__} */"
    else
        code << "return VTSS_RC_OK;"
    end

    #puts "----------------------------------------------------"
    #pp from
    #puts "----------------------------------------------------"
    #pp to
    #puts "----------------------------------------------------"

    return code
end

def impl_conv_function_body from, to
    raise "TYPE-FAM: Family mis-match: #{from[:type_fam]} != #{to[:type_fam]}" if from[:type_fam] != to[:type_fam]

    case from[:type_fam]
    when :type_enum
        return impl_conv_function_body_enum from, to
    when :type_struct
        return impl_conv_function_body_struct from, to
    else
        raise "UNEXPECTED: Unsupported family: #{from[:type_fam]}"
    end
end

def conv_function_name name, from, to
    #return "conv_#{from[:type_resolved][:type]}_to_#{to[:type_resolved][:type]}"
    f = type_resolve from
    t = type_resolve to

    return "mesa_#{name}_#{f[:type]}_to_#{t[:type]}"
end

def reg_conv f, t, pp = nil, f_ar = nil, t_ar = nil, conv_method = "conv"
    from_accessor = ""
    from_arr = ""
    to_accessor = ""
    to_arr = ""

    if pp.nil?
        pp1 = $types[f]
        pp2 = $types[t]

        pp = []
        pp.concat pp1[:pp_stack] if pp1 and pp1[:pp_stack]
        pp.concat pp2[:pp_stack] if pp2 and pp2[:pp_stack]
    end

    if t_ar and t_ar.size > 0
        t_ar.each do |a|
            to_arr += "[#{a.to_s.strip}]"
        end
    else
        to_accessor = "*"
    end

    if f_ar and f_ar.size > 0
        f_ar.each do |a|
            from_arr += "[#{a.to_s.strip}]"
        end
    else
        from_accessor = "*"
    end

    res = { :from => f, :to => t }
    res[:pp_begin] = impl_pp_stack_begin(pp) if pp
    res[:pp_end] = impl_pp_stack_end(pp) if pp
    res[:sig_arg] = "const #{f} #{from_accessor}in#{from_arr}, #{t} #{to_accessor}out#{to_arr}"
    res[:conv_name] = conv_method
    res[:conv_func_name] = conv_function_name(conv_method, f, t)

    $conv_methods["mesa_rc #{res[:conv_func_name]}(#{res[:sig_arg]})"] = res
end

def reg_conv_functions_hdr
    $types.each do |k, mesa|
        next if not /mesa_(.*)/ =~ k
        next if mesa[:peer].nil?

        vtss = $types[mesa[:peer][:type_name]]
        comp = mesa[:peer][:compatibility]

        case comp
        when :COMPATIBILITY_CONV_NEEDED, :COMPATIBILITY_CAST
            reg_conv(vtss[:type_resolved][:type], mesa[:type_resolved][:type], vtss[:pp_stack])
            reg_conv(mesa[:type_resolved][:type], vtss[:type_resolved][:type], vtss[:pp_stack])
        else
        end
    end
end

def impl_conv_functions_hdr
    $conv_methods.each do |k, v|
        if v[:pp_begin]
            v[:pp_begin].each do |l|
                $c_hdr.puts l
            end
        end

        f = $types[v[:from]]
        t = $types[v[:to]]

        if (f and t and f[:peer] and
            f[:peer][:compatibility] == :COMPATIBILITY_CAST and
            f[:peer][:type_name] == t[:type_resolved][:type])
            code = []
            $c_hdr.puts "inline static mesa_rc #{v[:conv_func_name]}(#{v[:sig_arg]}) { /* ag.rb:#{__LINE__} */"
            $c_hdr.puts "#ifdef __cplusplus"
            $c_hdr.puts "    static_assert(sizeof(out) == sizeof(in), \"size check\");"
            $c_hdr.puts "#endif // __cplusplus"
            $c_hdr.puts "    const #{t[:type_resolved][:type]} *tmp = (const #{t[:type_resolved][:type]} *)in;"
            $c_hdr.puts "    *out = *tmp;"
            $c_hdr.puts "    return VTSS_RC_OK;"
            $c_hdr.puts "}"
            v[:implemented] = true
        else
            $c_hdr.puts "mesa_rc #{v[:conv_func_name]}(#{v[:sig_arg]}); /* ag.rb:#{__LINE__} */"
        end


        if v[:pp_end]
            v[:pp_end].each do |l|
                $c_hdr.puts l
            end
        end
    end
end

def prepend_array sp, a
    res = []
    a.each do |x|
        if (/^\s*#.*/ =~ x)
            res << x
        else
            res << "#{sp}#{x}"
        end
    end

    return res
end

$impl_conv_cnt_ok = 0
$impl_conv_cnt_err = 0
def impl_conv_functions
    trace "BEGIN: impl conv"
    $types.each do |k, mesa|
        next if not /mesa_(.*)/ =~ k
        begin
            code = []
            raise "NO-PEER-TYPE: No peer type for #{k}" if mesa[:peer].nil?

            vtss = $types[mesa[:peer][:type_name]]
            rename_sym vtss[:type_name], mesa[:type_name]
            comp = mesa[:peer][:compatibility]

            if vtss[:type_fam] == :type_enum
                begin
                    impl_conv_function_body_enum vtss, mesa, true
                rescue RuntimeError => err
                    print_error err, "#{mesa}/#{vtss}"
                end
            end

            case comp
            when :COMPATIBILITY_CONV_NEEDED
                if vtss[:type_fam] == :type_alias
                    trace "Skipping conv-impl for type aliases: #{vtss[:type_name]}"
                    next
                end
                if mesa[:type_fam] == :type_alias
                    trace "Skipping conv-impl for type aliases: #{mesa[:type_name]}"
                    next
                end

                code.concat(impl_pp_stack_begin(vtss[:pp_stack]))

                key_1 = "mesa_rc #{conv_function_name("conv", vtss[:type_name], mesa[:type_name])}(const #{vtss[:type_name]} *in, #{mesa[:type_name]} *out)"
                code << "#{key_1} /* ag.rb:#{__LINE__} */"
                code << "{"
                #code.concat(impl_conv_function_body(vtss, mesa).collect{|x| if /^\s*#/ =~ x { "    #{x}"})
                code.concat(prepend_array("    ", impl_conv_function_body(vtss, mesa)))
                code << "}"
                code << ""

                key_2 = "mesa_rc #{conv_function_name("conv", mesa[:type_name], vtss[:type_name])}(const #{mesa[:type_name]} *in, #{vtss[:type_name]} *out)"
                code << "#{key_2} /* ag.rb:#{__LINE__} */"
                code << "{"
                code.concat(prepend_array("    ", impl_conv_function_body(mesa, vtss)))
                code << "}"

                code.concat(impl_pp_stack_end(vtss[:pp_stack]))

                code << ""

                code.each do |l|
                    if /^\s*$/ =~ l
                        $c_src.puts ""
                    else
                        $c_src.puts l
                    end
                end
                $impl_conv_cnt_ok += 1
                $conv_methods[key_1][:implemented] = true if $conv_methods[key_1]
                $conv_methods[key_2][:implemented] = true if $conv_methods[key_2]

            when :COMPATIBILITY_CAST, :COMPATIBILITY_SAME
                key_1 = "mesa_rc #{conv_function_name("conv", vtss[:type_name], mesa[:type_name])}(const #{vtss[:type_name]} *in, #{mesa[:type_name]} *out)"
                key_2 = "mesa_rc #{conv_function_name("conv", mesa[:type_name], vtss[:type_name])}(const #{mesa[:type_name]} *in, #{vtss[:type_name]} *out)"
                $conv_methods[key_1][:implemented] = true if $conv_methods[key_1]
                $conv_methods[key_2][:implemented] = true if $conv_methods[key_2]

            else
                pp comp
                raise
            end

        rescue RuntimeError => err
            str_error = "impl-conv: #{k}"
            print_error err, str_error

            #puts "--------------------------------------------------------------------"
            #puts "ERROR: [#{k}] - #{err.to_s}"
            #puts err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
            #puts "--------------------------------------------------------------------"
        end
    end
    trace "END: impl conv"
end

map_types
reg_conv_functions_hdr
impl_conv_functions

def method_arg_compatibility_check mesa, vtss
    if mesa[:type_base] == vtss[:type_base]
        return :COMPATIBILITY_SAME
    end

    if mesa[:type_resolved].nil? or vtss[:type_resolved].nil?
        trace "Look: #{mesa[:type_base]} #{vtss[:type_base]}"
        reg_conv mesa[:type_base], vtss[:type_base], nil, mesa[:array], vtss[:array]
        reg_conv vtss[:type_base], mesa[:type_base], nil, vtss[:array], mesa[:array]
        return :COMPATIBILITY_CONV_NEEDED
        #raise "TYPE-RESOLVE: vtss-type #{vtss[:type_base]} could not be resolved"
    end

    if mesa[:type_resolved][:type_resolved][:type] == vtss[:type_resolved][:type_resolved][:type] and mesa[:type_resolved][:type_resolved][:abi] == :abi_stable
        return :COMPATIBILITY_SAME
    end

    if mesa[:type_base] == "mesa_port_list_t" and vtss[:array].size == 1
        reg_conv mesa[:type_base], vtss[:type_base], nil, mesa[:array], vtss[:array]
        reg_conv vtss[:type_base], mesa[:type_base], nil, vtss[:array], mesa[:array]
        return :COMPATIBILITY_CONV_NEEDED
    end

    if mesa[:array] != vtss[:array]
        raise "FUNC-ARG-ARRAY: Array indexes does not match"
    end

    if mesa[:type_resolved][:peer].nil? or mesa[:type_resolved][:peer][:type_name].nil?
        raise "NO-PEER-TYPE: No peer type for #{mesa[:type_base]}"
    end

    if vtss[:type_resolved][:peer].nil? or vtss[:type_resolved][:peer][:type_name].nil?
        raise "NO-PEER-TYPE: No peer type for #{vtss[:type_base]}"
    end

    if mesa[:type_resolved][:peer][:type_name] != vtss[:type_base]
        raise "TYPE-RESOLVE: Peer type does not (seem to) match: #{mesa[:type_resolved][:peer][:type_name]} != #{vtss[:type_base]}"
    end

    return c = mesa[:type_resolved][:peer][:compatibility]
end

impl_err_cnt = 0
impl_mesa_cnt = 0
trace "BEGIN: Implement methods"
$methods.each do |k, v|
    mesa = k;
    vtss = nil
    c_src = ""

    if /mesa_(.*)/ =~ k
        impl_mesa_cnt += 1
        vtss = "vtss_#{$1}";
    else
        next
    end

    x = $methods[vtss]
    if x.nil?
        trace "#{mesa} <-> no-peer-method!"
        next
    end

    rename_sym vtss, mesa
    mesa_args = analyze_args(v[:args])
    vtss_args = analyze_args(x[:args])

    if $methods_blacklist.include? mesa
        trace "#{mesa} blacklisted"
        next
    end

    # todo return type

    begin

        # todo, check that return types are compatible

        if mesa_args.size != vtss_args.size
            raise "FUNC-ARG: Arg count does not match: #{mesa_args.size} != #{vtss_args.size}"
        end

        a = []
        mesa_args.size.times do |i|
            c = method_arg_compatibility_check mesa_args[i], vtss_args[i]
            arg = "#{mesa_args[i][:type_str]} #{mesa_args[i][:arg_name]}#{mesa_args[i][:array].collect{|x| "[#{x}]"}.join("")}"
            a << {
                :compatibility => c,
                :arg_str => arg,
                :ast_mesa => mesa_args[i],
                :ast_vtss => vtss_args[i],
                :is_array => mesa_args[i][:array].size > 0
            }

        end

        impl_pp_stack_begin(x[:pp_stack]).each do |l|
            c_src += "#{l}\n"
        end

        return_type = "#{v[:normal][:type].to_s.strip}"
        rc_end = ")"
        rc_start = "__RC("
        if return_type == "void"
            rc_end = ""
            rc_start = ""
        end

        proto = "#{return_type} #{k}(#{a.collect{|x| x[:arg_str]}.join(", ")})"
        c_src +=  "#{proto}\n"
        c_src +=  "{ /* ag.rb:#{__LINE__} */\n"

        vtss_layer_args = []
        code_vars = []
        code_vars_memset = []
        code_static_cast = []
        code_conv_in = []
        code_conv_out = []
        get_before_set = false
        get_before_set_func = nil

        a.each do |e|
            case e[:compatibility]
            when :COMPATIBILITY_SAME
                vtss_layer_args << e[:ast_mesa][:arg_name]
            when :COMPATIBILITY_CAST
                val_const = e[:ast_vtss][:value_const] ? "const " : ""
                ptr_const = e[:ast_vtss][:ptr_const] ? "const" : ""
                accessor = ""

                if e[:is_array] or e[:ast_vtss][:ptr]
                    # Just cast to a pointer (will not work for multi dimentional arrays)
                    vtss_layer_args << "(#{val_const}#{e[:ast_vtss][:type_base]} *)#{e[:ast_mesa][:arg_name]} /* ag.rb:#{__LINE__} */"
                elsif e[:ast_vtss][:type_base] == "vtss_inst_t"
                    # typedef'ed pointers is not working very well
                    vtss_layer_args << "(#{val_const}#{e[:ast_vtss][:type_base]})#{e[:ast_mesa][:arg_name]} /* ag.rb:#{__LINE__} */"
                else
                    vtss_layer_args << "*((#{val_const}#{e[:ast_vtss][:type_base]} *)&#{e[:ast_mesa][:arg_name]}) /* ag.rb:#{__LINE__} */"
                end

                code_static_cast << "static_assert(sizeof(#{e[:ast_vtss][:type_base]}) == sizeof(#{e[:ast_mesa][:type_base]}), \"Check size\")"


            when :COMPATIBILITY_CONV_NEEDED
                tmp_name = "__#{e[:ast_mesa][:arg_name]}"
                code_vars << "#{e[:ast_vtss][:type_base]} #{tmp_name}#{e[:ast_vtss][:array].collect{|x| "[#{x}]"}.join("")}"

                skip_data = $conv_skip_data[e[:ast_vtss][:type_base]]
                if skip_data.nil?
                    trace "No skip data for #{e[:ast_vtss][:type_base]}"
                end

                code_vars_memset << "memset(&#{tmp_name}, 0, sizeof(#{tmp_name}))"

                # If it's an output parameter and a pointer, clear it.
                code_vars_memset << "memset(#{e[:ast_mesa][:arg_name]}, 0, sizeof(*#{e[:ast_mesa][:arg_name]}))" if e[:ast_mesa][:direction] == :DIR_OUT and e[:ast_mesa][:ptr]

                mesa_conv_arg_access = "&"
                mesa_conv_arg_access = "" if e[:ast_mesa][:ptr]

                vtss_conv_arg_access = "&"
                vtss_conv_arg_access = "" if e[:ast_vtss][:array].size > 0

                vtss_arg_access = ""
                vtss_arg_access = "&" if e[:ast_vtss][:ptr]

                vtss_layer_args << "#{vtss_arg_access}__#{e[:ast_mesa][:arg_name]}"

                conv_in = "#{mesa_conv_arg_access}#{e[:ast_mesa][:arg_name]}"
                conv_out = "#{vtss_conv_arg_access}__#{e[:ast_mesa][:arg_name]}"

                conv_in_t = "#{e[:ast_mesa][:type_base]}"
                conv_out_t = "#{e[:ast_vtss][:type_base]}"

                if e[:ast_mesa][:direction] == :DIR_OUT
                    conv_in,conv_out = conv_out,conv_in  # swap
                    conv_in_t,conv_out_t = conv_out_t,conv_in_t  # swap
                end

                conv_code = ""
                if e[:ast_mesa][:array].size > 0
                    conv_code += "for (int i = 0; i < #{e[:ast_mesa][:array][0]}; ++i)"
                    conv_code += "#{rc_start}#{conv_function_name("conv", conv_in_t, conv_out_t)}(#{conv_in}[i], #{conv_out}[i])#{rc_end} /* ag.rb:#{__LINE__} */"
                else
                    conv_code += "#{rc_start}#{conv_function_name("conv", conv_in_t, conv_out_t)}(#{conv_in}, #{conv_out})#{rc_end} /* ag.rb:#{__LINE__} */"
                end

                case e[:ast_mesa][:direction]
                when :DIR_IN
                    if skip_data and skip_data[:skip_vtss]
                        if /mesa_(.+?)_set/ =~ k and $methods["vtss_#{$1}_get"]
                            get_before_set = true
                            get_before_set_func = "vtss_#{$1}_get"
                            code_vars_memset = [] # No need to memset()
                        end
                    end
                    code_conv_in << conv_code
                when :DIR_OUT
                    code_conv_out << conv_code
                else
                    raise
                end
            else
                #pp e
                #raise
            end
        end

        all_one_or_zero = true
        all_one_or_zero = false if code_vars.size > 1
        all_one_or_zero = false if code_vars_memset.size > 1
        all_one_or_zero = false if code_static_cast.size > 1
        all_one_or_zero = false if code_conv_in.size > 1
        all_one_or_zero = false if code_conv_out.size > 1

        code_vars.each {|e| c_src += "    #{e};\n"}
        c_src += "\n" if code_vars.size > 0 and not all_one_or_zero

        code_vars_memset.each {|e| c_src += "    #{e};\n"}
        c_src += "\n" if code_vars_memset.size > 0 and not all_one_or_zero

        c_src += "#ifdef __cplusplus\n" if code_static_cast.size > 0
        code_static_cast.each do |e|
            c_src += "    #{e}; /* ag.rb:#{__LINE__} */\n"
        end
        c_src += "#endif // __cplusplus\n" if code_static_cast.size > 0
        c_src += "\n" if code_static_cast.size > 0 and not all_one_or_zero

        if get_before_set
            c_src += "    #{get_before_set_func}(#{vtss_layer_args.join(", ")});  /* ag.rb:#{__LINE__} */ // get-before-set\n"
        end

        code_conv_in.each {|e| c_src += "    #{e}; /* ag.rb:#{__LINE__} */\n"}
        c_src += "\n" if code_conv_in.size > 0 and not all_one_or_zero

        call_str = "#{vtss}(#{vtss_layer_args.join(", ")})"
        if code_conv_out.size > 0
            c_src += "    #{v[:normal][:type].to_s.strip} rc = #{call_str}; /* ag.rb:#{__LINE__} */\n"
            c_src += "\n" if not all_one_or_zero
            code_conv_out.each {|e| c_src += "    #{e}; /* ag.rb:#{__LINE__} */\n"}
            c_src += "\n" if not all_one_or_zero
            c_src += "    return rc; /* ag.rb:#{__LINE__} */\n"
        else
            c_src += "    return #{call_str}; /* ag.rb:#{__LINE__}*/ \n"
        end

        c_src += "}\n"
        impl_pp_stack_end(x[:pp_stack]).each do |l|
            # implement - the not implemented body
            if return_type == "mesa_rc"
                c_src += "#else\n"
                c_src +=  "#{proto}\n"
                c_src +=  "{\n"
                c_src +=  "    return MESA_RC_NOT_IMPLEMENTED;\n"
                c_src +=  "}\n"
            end
            c_src += "#{l} /* ag.rb:#{__LINE__} */\n"

        end
        c_src += "\n"

        $c_src.write(c_src);
    rescue RuntimeError => err
        print_error err, "#{mesa}/#{vtss}"
        impl_err_cnt += 1
        $methods_impl_no_auto << mesa
    end
end
trace "END: Implement methods"

trace "// #{impl_mesa_cnt}/#{impl_err_cnt}"

$c_src.puts "#pragma GCC diagnostic pop"
$pp_rename.puts "#endif  // __MESA_PP_RENAME__"

impl_conv_functions_hdr

$c_hdr.puts "#ifdef __cplusplus"
$c_hdr.puts "}"
$c_hdr.puts "#endif"
$c_hdr.puts "#endif // __MESA_H__"


trace
trace
trace "Missing implementations"


$impl_conv_cnt_err = 0
$conv_methods.each do |k, v|
    next if v[:implemented]
    $impl_conv_cnt_err += 1
end

trace "  CONV-Methods (AUTO: #{$impl_conv_cnt_ok} MISSING: #{$impl_conv_cnt_err}):"
$conv_methods.each do |k, v|
    next if v[:implemented]
    trace "    #{k}"
end


trace "  MESA-Methods (AUTO: #{impl_mesa_cnt} MISSING: #{impl_err_cnt}):"
$methods_impl_no_auto.each do |m|
    trace "    #{m}"
end

