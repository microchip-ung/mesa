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
$log = File.open("#{$options[:output_dir]}/log-rpc.txt", "w")
$c_hdr = File.open("#{$options[:output_dir]}/mesa-rpc.h", "w")
$c_src = File.open("#{$options[:output_dir]}/mesa-rpc.c", "w")

def trace s = ""
    $log.puts s
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
    "meba_inst_t"  => {:type_fam=>:type_alias, :type_name=>"meba_inst_t",  :type_next=>"meba_inst_t",  :type_resolved=>{:type=>"meba_inst_t",  :abi=>:abi_stable}},
    "mesa_bool_t"  => {:type_fam=>:type_alias, :type_name=>"mesa_bool_t",  :type_next=>"mesa_bool_t",  :type_resolved=>{:type=>"mesa_bool_t",  :abi=>:abi_stable}},

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
    "mesa_symreg_data_get",
    "mesa_debug_info_get",
    "mesa_debug_info_print",
    "mesa_macsec_dbg_reg_dump",
    "mesa_macsec_dbg_fcb_block_reg_dump",
    "mesa_macsec_dbg_frm_match_handling_ctrl_reg_dump",
    "mesa_packet_tx_frame",
    "mesa_init_conf_get",
    "mesa_init_conf_set",
    "mesa_spi_slave_init",
    "mesa_tx_timestamp_idx_alloc",
    "mesa_tod_set_ns_cnt_cb",
    "mesa_cap_callback_add",
    "meba_phy_debug_info_print",
    "meba_phy_macsec_dbg_fcb_block_reg_dump",
    "meba_phy_macsec_dbg_fcb_block_reg_dump",
    "meba_phy_macsec_dbg_reconfig",
    "meba_phy_macsec_dbg_reg_dump",
    "meba_phy_ts_fifo_read_install",
    "meba_ts_test_config",
    "meba_phy_macsec_dbg_frm_match_handling_ctrl_reg_dump",
    "meba_phy_ts_fifo_get",
]

$methods_greylist = [
    "mesa_qos_dscp_dpl_conf_get",
    "mesa_qos_dscp_dpl_conf_set",
    "mesa_qos_dpl_group_conf_get",
    "mesa_qos_dpl_group_conf_set",
    "mesa_tx_timestamp_idx_alloc",
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
            process_members ast[:struct_type_declare][:struct_members], [], false
        elsif ast[:union_type_declare]
            @has_union = true
            process_members ast[:union_type_declare][:union_members], [], false
        else
            raise
        end

        process ast, t
    end

    def process_members member_list, mname, is_union
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
                    :is_union => is_union,
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
                begin
                  mname << m[:member_union][:name]
                  process_members m[:member_union][:union_type_declare][:union_members], mname, true
                  mname.pop
                rescue
                    pp m
                    raise
                end

            elsif m[:member_struct]
                mname << m[:member_struct][:name]
                process_members m[:member_struct][:struct_type_declare][:struct_members], mname, false
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
    ## Black list of types that are defined multiple places. We just want to ignore these types for now
    #return false if $types_blacklist.include? t

    #if not $types[t].nil?
    #    # this indicate that this is not a ABI stable type
    #    trace "Type #{t} defined multiple times"
    #    puts "type_check_black_list: #{t}"
    #    $types.delete t
    #    $types_blacklist << t
    #    return false
    #end

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

    #pp tt

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

    #puts __LINE__
    #pp base_type
    #pp $types[base_type]

    if base_type == "mesa_bool_t"
        #puts "type-DB: #{__LINE__}"
        #pp $types
    end


    res = {
        :type_str => t,
        :ptr => ptr,
        :value_const => value_const,
        :ptr_const => ptr_const,
        :type_base => base_type,
        :type_resolved => $types[base_type],
    }

    #pp res
    return res
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

$methods_whitelist = [
    "mesa_vlan_port_conf_get",
    "mesa_vlan_port_conf_set",
    "mesa_vlan_port_members_get",
    "mesa_vlan_port_members_set",
    "mesa_port_counters_get",
    "mesa_qos_port_conf_get",
    "mesa_ts_autoresp_dom_cfg_get",
    "mesa_oam_mip_alloc",
    "mesa_ace_add",
    "mesa_phy_conf_get",
    "mesa_phy_conf_set",
    "mesa_phy_status_get"
]

def handle_func_proto ast
    #pp ast
    return if ast[:func_proto].nil?
    return if ast[:func_proto][:normal].nil?
    return if $methods_blacklist.include? ast[:func_proto][:normal][:name]

    n = ast[:func_proto][:normal][:name]
    if $methods_whitelist.include? n
    else
        if n.to_s.include? "mesa_phy"
            return
        end
        if n.to_s.include? "mepa"
            return
        end
    end

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
        #rescue => err
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
        next if /vtss/ =~ x
        next if not (/.*\.h$/ =~ x)

        o_dir = "#{$options[:output_dir]}/#{File.dirname(x)}"
        FileUtils.mkdir_p(o_dir)

        ast = nil
        cache_file = "#{$options[:output_dir]}/#{x}.cache"
        if File.exists?(cache_file) and File.mtime(cache_file) > File.mtime(x)
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
        puts "Failed #{x}"
        puts error
        puts error.parse_failure_cause.ascii_tree
        raise

    rescue => err
        trace "Failed #{x}"
        trace err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
        raise
    end
end

resolve_all_types

$tl = []
$tl_implemented = []

def skip_inst(a)
    str = a[:type_base]
    skip = (str == "mesa_inst_t" or str == "meba_inst_t")
end

$methods.each do |m, o|
    aaa = nil
    #begin
        cap = (m == "mesa_capability")
        aa = analyze_args o[:args]
        aa.each do |a|
            next if skip_inst(a)
            t = (cap ? "mesa_cap_t" : a[:type_resolved][:type_resolved][:type])
            $tl << t
        end
    #rescue => err
    #    puts "Failed #{m}"
    #    pp o
    #    pp aaa
    #    puts err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
    #end
end

$el = []
$sl = []

while $tl.size > 0
    tl_ = []
    $tl.uniq!
    $tl.each do |t|
        tt = type_resolve_type t
        #pp tt
        $el << t if tt[:type_fam] == :type_enum
        next if tt[:type_fam] != :type_struct
        $sl << t

        tt[:members].each do |m|
            #puts "  #{m[:member_name]} #{m[:member_type]}/#{m[:type_resolved][:type]}"
            x = type_resolve_type m[:type_resolved][:type]
            if not x.nil?
                case x[:type_fam]
                when :type_struct
                    tl_ << m[:type_resolved][:type]
                when :type_enum
                    $el << m[:type_resolved][:type]
                end
            end
        end

        $tl_implemented << t
    end

    #puts "Again!!!!!!!!"
    $tl = tl_ - $tl_implemented
end

def add_func name
    $c_hdr.puts "#{name};"
    $c_src.puts "#{name}"
    $c_src.puts "{"
end

def end_func
    $c_src.puts "    return MESA_RC_OK;"
    $c_src.puts "}"
    $c_src.puts ""
end

$c_hdr.puts "#include <json_rpc.h>"
$c_hdr.puts ""

$c_src.puts "#include <mesa-rpc.h>"
$c_src.puts "#pragma GCC diagnostic ignored \"-Wmaybe-uninitialized\""
$c_src.puts ""


$el.uniq!
$el.each do |e|
    #pp e
    x = type_resolve_type e

    $c_src.puts "// Convert from string to enumeration"
    add_func "mesa_rc json_rpc_enum_name_#{x[:type_name]}(json_rpc_req_t *req, const char *str, #{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.print "    "
    x[:members].each do |e|
        n = e[:enum_name]
        $c_src.puts "if (strcmp(str, \"#{n}\") == 0) {"
        $c_src.puts "        *parm = #{n};"
        $c_src.print "    } else "
    end
    $c_src.puts "{"
    $c_src.puts "        sprintf(req->ptr, \"illegal enum '%s'\", str);"
    $c_src.puts "        return MESA_RC_ERROR;"
    $c_src.puts "    }"
    end_func

    $c_src.puts "// Get enumeration from array"
    add_func "mesa_rc json_rpc_get_idx_#{x[:type_name]}(json_rpc_req_t *req, json_object *obj, int *idx, #{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.puts "    const char *str;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_get_idx_json_string(req, obj, idx, &str)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_enum_name_#{x[:type_name]}(req, str, parm)); /* #{__LINE__} */"
    end_func

    $c_src.puts "// Get enumeration from object"
    add_func "mesa_rc json_rpc_get_name_#{x[:type_name]}(json_rpc_req_t *req, json_object *obj, const char *name, #{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.puts "    const char *str;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_get_name_json_string(req, obj, name, &str)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_enum_name_#{x[:type_name]}(req, str, parm)); /* #{__LINE__} */"
    end_func

    $c_src.puts "// Convert enumeration to string"
    add_func "const char *json_rpc_string_#{x[:type_name]}(#{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.puts "    return ("
    n_def = nil
    x[:members].each do |e|
        n = e[:enum_name]
        $c_src.puts "            *parm == #{n} ? \"#{n}\" :"
        if n_def.nil?
            n_def = n
        end
    end
    $c_src.puts "            \"#{n_def}\");"
    $c_src.puts "}"
    $c_src.puts ""

    $c_src.puts "// Add enumeration to array"
    add_func "mesa_rc json_rpc_add_#{x[:type_name]}(json_rpc_req_t *req, json_object *obj, #{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.puts "    return json_rpc_add_json_string(req, obj, json_rpc_string_#{x[:type_name]}(parm));"
    $c_src.puts "}"
    $c_src.puts ""

    $c_src.puts "// Add enumeration to object"
    add_func "mesa_rc json_rpc_add_name_#{x[:type_name]}(json_rpc_req_t *req, json_object *obj, const char *name, #{x[:type_name]} *parm) /* #{__LINE__} */"
    $c_src.puts "    return json_rpc_add_name_json_string(req, obj, name, json_rpc_string_#{x[:type_name]}(parm));"
    $c_src.puts "}"
    $c_src.puts ""
    $c_hdr.puts ""
end

def member_array m
    if m[:member_type] == "mesa_clock_identity"
        # Hardcoded array
        a = ["MESA_CLOCK_IDENTITY_LENGTH"]
    elsif m[:type_array].nil?
        a = []
    else
        a = m[:type_array]
    end
    a
end

def add_member_get_func m
    n = m[:member_name]
    t = (m[:member_type] == "mesa_bool_t" ? "mesa_bool_t" : m[:type_resolved][:type])
    str_parm = "&(parm->#{n})"
    n = "\"#{n}\""

    #$c_src.puts "#if 0"
    #$c_src.puts m.pretty_inspect
    #$c_src.puts "#endif"

    type_array = member_array(m)
    if type_array.size == 0
        $c_src.puts "    MESA_RC(json_rpc_get_name_#{t}(req, obj, #{n}, #{str_parm})); /* #{__LINE__} */"
    else
        str_arr = str_parm
        str_obj = "obj_value"
        str_ind = "    "
        j = 0
        $c_src.puts "#{str_ind}{"
        str_ind += "    "
        $c_src.puts "#{str_ind}json_object *obj_value;"
        $c_src.puts "#{str_ind}MESA_RC(json_rpc_get_name_json_object(req, obj, #{n}, &obj_value)); /* #{__LINE__} */"
        type_array.each do |i|
            $c_src.puts "#{str_ind}for (int i#{j} = 0; i#{j} < #{i}; ) {"
            str_ind += "    "
            if i == type_array.last
                str_parm = str_arr + "[i#{j}]"
            else
                str_parm = "obj#{j}"
                $c_src.puts "#{str_ind}json_object *obj#{j};"
            end
            str_arr += "[i#{j} - 1]"
            if i == type_array.last
                $c_src.puts "#{str_ind}MESA_RC(json_rpc_get_idx_#{t}(req, #{str_obj}, &i#{j}, #{str_parm})); /* #{__LINE__} */"
            else
                $c_src.puts "#{str_ind}MESA_RC(json_rpc_get_idx_json_object(req, #{str_obj}, &i#{j}, &#{str_parm})); /* #{__LINE__} */"
            end
            str_obj = "obj#{j}"
            j += 1
        end
        type_array.each do |i|
            (1..(j + 1)).each {$c_src.print "    "}
            $c_src.puts "}"
            j -= 1
        end
        $c_src.puts "    }"
    end
end

def add_member_add_func m
    n = m[:member_name]
    t = (m[:member_type] == "mesa_bool_t" ? "mesa_bool_t" : m[:type_resolved][:type])
    str_parm = "&(parm->#{n})"
    n = "\"#{n}\""
    type_array = member_array(m)
    if type_array.size == 0
        $c_src.puts "    MESA_RC(json_rpc_add_name_#{t}(req, *obj, #{n}, #{str_parm})); /* #{__LINE__} */"
    else
        str_arr = str_parm
        str_ind = "    "
        j = 0
        n = "*obj, " + n
        nt = "name_json_object"
        type_array.each do |i|
            $c_src.puts "#{str_ind}{"
            str_ind += "    "
            $c_src.puts "#{str_ind}json_object *obj#{j};"
            $c_src.puts "#{str_ind}MESA_RC(json_rpc_array_new(req, &obj#{j})); /* #{__LINE__} */"
            $c_src.puts "#{str_ind}MESA_RC(json_rpc_add_#{nt}(req, #{n}, obj#{j})); /* #{__LINE__} */"
            $c_src.puts "#{str_ind}for (int i#{j} = 0; i#{j} < #{i}; i#{j}++) {"
            str_ind += "    "
            n = "obj#{j}"
            nt = "json_array"
            str_arr += "[i#{j}]"
            if i == type_array.last
                $c_src.puts "#{str_ind}MESA_RC(json_rpc_add_#{t}(req, obj#{j}, #{str_arr})); /* #{__LINE__} */"
            end
            j += 1
        end
        type_array.each do |i|
            n = (2 * j - 1)
            (1..n).each {$c_src.print "    "}
            $c_src.puts "    }"
            (1..n).each {$c_src.print "    "}
            $c_src.puts "}"
            j -= 1
        end
    end
end

def member_is_union(m)
    m[:is_union] or (m[:member_type].end_with? ("map_maps_t"))
end

$sl.uniq!
$sl.each do |s|
    x = type_resolve_type s
    #pp x
    #pp x if s.include? "auto"
    $c_src.puts "// Get struct"
    add_func "mesa_rc json_rpc_get_#{s}(json_rpc_req_t *req, json_object *obj, #{s} *parm) /* #{__LINE__} */"
    is_union = false;
    x[:members].each do |m|
        if member_is_union(m)
            is_union = true
        elsif m[:member_type] != "void *"
            add_member_get_func m
        end
    end
    if is_union
        $c_src.puts "    MESA_RC(json_rpc_get2_#{s}(req, obj, parm)); /* #{__LINE__} */ // Get union"
    end
    end_func

    $c_src.puts "// Get struct from array"
    add_func "mesa_rc json_rpc_get_idx_#{s}(json_rpc_req_t *req, json_object *obj, int *idx, #{s} *parm) /* #{__LINE__} */"
    $c_src.puts "    json_object *obj_value;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_get_idx_json_object(req, obj, idx, &obj_value)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_get_#{s}(req, obj_value, parm)); /* #{__LINE__} */"
    end_func

    $c_src.puts "// Get struct from object"
    add_func "mesa_rc json_rpc_get_name_#{s}(json_rpc_req_t *req, json_object *obj, const char *name, #{s} *parm) /* #{__LINE__} */"
    $c_src.puts "    json_object *obj_value;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_get_name_json_object(req, obj, name, &obj_value)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_get_#{s}(req, obj_value, parm)); /* #{__LINE__} */"
    end_func

    $c_src.puts "// Create struct object"
    add_func "mesa_rc json_rpc_new_#{s}(json_rpc_req_t *req, json_object **obj, #{s} *parm) /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_new(req, obj)); /* #{__LINE__} */"
    is_union = false;
    x[:members].each do |m|
        if member_is_union(m)
            is_union = true
        elsif m[:member_type] != "void *"
            add_member_add_func m
        end
    end
    if is_union
        $c_src.puts "    MESA_RC(json_rpc_add2_#{s}(req, *obj, parm));  /* #{__LINE__} */ // Add union"
    end
    end_func

    $c_src.puts "// Add struct to array"
    add_func "mesa_rc json_rpc_add_#{s}(json_rpc_req_t *req, json_object *obj, #{s} *parm) /* #{__LINE__} */"
    $c_src.puts "    json_object *obj_value;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_new_#{s}(req, &obj_value, parm)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_add_json_array(req, obj, obj_value)); /* #{__LINE__} */"
    end_func
  
    $c_src.puts "// Add struct to object"
    add_func "mesa_rc json_rpc_add_name_#{s}(json_rpc_req_t *req, json_object *obj, const char *name, #{s} *parm) /* #{__LINE__} */"
    $c_src.puts "    json_object *obj_value;"
    $c_src.puts ""
    $c_src.puts "    MESA_RC(json_rpc_new_#{s}(req, &obj_value, parm)); /* #{__LINE__} */"
    $c_src.puts "    MESA_RC(json_rpc_add_name_json_object(req, obj, name, obj_value)); /* #{__LINE__} */"
    end_func
    $c_hdr.puts ""
end

def arg_is_count(method, name)
    (!method.end_with? "alloc" and (name.end_with? "cnt" or name.end_with? "max_len"))
end

$methods.each do |m, o|
    begin
        next if $methods_greylist.include? m
        $c_src.puts "static mesa_rc mesa_rpc_#{m}(json_rpc_req_t *req) /* #{__LINE__} */"
        $c_src.puts "{"
        aa = analyze_args o[:args]

        if m == "mesa_capability"
            $c_src.puts "    mesa_cap_t cap;"
            $c_src.puts "    int val;"
            $c_src.puts "    MESA_RC(json_rpc_get_idx_mesa_cap_t(req, req->params, &req->idx, &cap));"
            $c_src.puts "    val = mesa_capability(NULL, cap);"
            $c_src.puts "    MESA_RC(json_rpc_add_int(req, req->result, &val));"
            $c_src.puts ""
            $c_src.puts "    return MESA_RC_OK;"
            $c_src.puts "}"
            next
        end

        str1 = ""
        aa.each do |a|
            next if skip_inst(a)
            str = a[:type_base]
            str1 = "[#{a[:array][0]}]" if (a[:array].size > 0)
            $c_src.puts "    #{str} #{a[:arg_name]}#{str1};"
            str1 = (arg_is_count(m, a[:arg_name]) ? "[100]" : "")
        end
        $c_src.puts ""
        prev_arg = ""
        aa.each do |a|
            next if skip_inst(a)
            next if a[:direction] == :DIR_OUT
            if (a[:array].size > 0)
                end_str = a[:array][0]
            elsif (arg_is_count(m, prev_arg))
                end_str = prev_arg
            else
                end_str = ""
            end

            #$c_src.puts "#if 0"
            #$c_src.puts a.pretty_inspect
            #$c_src.puts "#endif"

            t = (a[:type_base] == "mesa_bool_t" ? "mesa_bool_t" : type_resolve(a[:type_base])[:type])
            if (end_str.length > 0)
                $c_src.puts "    {"
                $c_src.puts "        json_object *obj;"
                $c_src.puts "        MESA_RC(json_rpc_get_idx_json_object(req, req->params, &req->idx, &obj)); /* #{__LINE__} */"
                $c_src.puts "        for (int i = 0; i < #{end_str}; ) {"
                $c_src.puts "            MESA_RC(json_rpc_get_idx_#{t}(req, obj, &i, &#{a[:arg_name]}[i])); /* #{__LINE__} */"
                $c_src.puts "        }"
                $c_src.puts "    }"
            else
                $c_src.puts "    MESA_RC(json_rpc_get_idx_#{t}(req, req->params, &req->idx, &#{a[:arg_name]})); /* #{__LINE__} */"
            end
            prev_arg = a[:arg_name]
        end

        begin
            str = o[:normal][:type].to_s.strip
            has_rc = (str == "mesa_rc" or str == "mepa_rc")
            $c_src.puts "/* #{__LINE__} */"
            if has_rc
                $c_src.print "    MESA_RC(json_rpc_call(req, #{m}("
            else
                $c_src.print "    #{m}("
            end
            is_array = false
            aa.each do |a|
                $c_src.print ", " if a != aa.first
                str = a[:type_base]
                if str == "mesa_inst_t"
                    $c_src.print "NULL"
                elsif str == "meba_inst_t"
                    $c_src.print "meba_global_inst"
                else
                    $c_src.print "&" if a[:ptr] and !is_array
                    $c_src.print "#{a[:arg_name]}"
                end
                is_array = arg_is_count(m, a[:arg_name])
            end
            if has_rc
                $c_src.print "))"
            end
            $c_src.puts ");"
        end
        prev_arg = ""

        aa.each do |a|
            next if skip_inst(a)

            #$c_src.puts "#if 0"
            #$c_src.puts a.pretty_inspect
            #$c_src.puts "#endif"
            t = (a[:type_base] == "mesa_bool_t" ? "mesa_bool_t" : type_resolve(a[:type_base])[:type])

            if a[:direction] == :DIR_IN
                $c_src.puts "    json_object_array_add(req->result, NULL);  /* #{a[:arg_name]} #{__LINE__} */"

            elsif arg_is_count(m, prev_arg)
                $c_src.puts "    {"
                $c_src.puts "        json_object *obj;"
                $c_src.puts "        MESA_RC(json_rpc_array_new(req, &obj)); /* #{__LINE__} */"
                $c_src.puts "        MESA_RC(json_rpc_add_json_array(req, req->result, obj)); /* #{__LINE__} */"
                $c_src.puts "        for (int i = 0; i < #{prev_arg}; i++) {"
                $c_src.puts "            MESA_RC(json_rpc_add_#{t}(req, obj, &#{a[:arg_name]}[i])); /* #{__LINE__} */"
                $c_src.puts "        }"
                $c_src.puts "    }"
            else
                $c_src.puts "    MESA_RC(json_rpc_add_#{t}(req, req->result, &#{a[:arg_name]})); /* #{__LINE__} */"

            end

            prev_arg = a[:arg_name]
        end
        $c_src.puts ""
        $c_src.puts "    return MESA_RC_OK;"
        $c_src.puts "}"
        $c_src.puts ""
    rescue => err
        puts "Failed #{m}"
        pp o
        puts err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
    end
end
$c_src.puts ""
$c_src.puts "json_rpc_method_t json_rpc_table[] = {"
$methods.each do |m, o|
    begin
        next if $methods_greylist.include? m
        $c_src.puts "    { \"#{m}\", mesa_rpc_#{m} }, "
    rescue => err
        puts "Failed #{m}"
        pp o
        puts err.backtrace.join("\n\t") .sub("\n\t", ": #{err}#{err.class ? " (#{err.class})" : ''}\n\t")
    end
end
$c_src.puts "    { NULL, NULL}"
$c_src.puts "};"

