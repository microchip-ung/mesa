#!/usr/bin/env ruby
# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

# Parts of this file is borrowed from https://github.com/mrcsparker/kalc v0.3,
# also MIT-licensed.
# Copyright (c) 2012-2018 Chris Parker

require 'parslet'

class CParser < Parslet::Parser
    rule(:new_line) { match('[\n\r]').repeat(1) }

    rule(:space) { match('[ \t\v\n\f]') }
    rule(:spaces) { space.repeat(1) }
    rule(:space?) { space.maybe }
    rule(:spaces?) { space.repeat }

    rule(:digit) { match('[0-9]') }
    rule(:digits) { digit.repeat(1) }
    rule(:digits?) { digit.repeat }

    rule(:alpha) { match('[a-zA-Z_]') }
    rule(:xdigit) { digit | match('[a-fA-F]') }

    rule(:e) { match('[eE]') >> match('[+-]').maybe >> digit.repeat(1) }
    rule(:float_size) { match('[fFlL]') }
    rule(:int_size) { match('[uUlL]').repeat }

    rule(:e?) { e.maybe }
    rule(:float_size?) { float_size.maybe }
    rule(:int_size?) { int_size.maybe }

    rule(:comment) {
        #((spaces? >> str('/*') >> spaces? >> ((str('*/').absent? >> any).repeat).as(:comment) >> str('*/') >> spaces? ) |
        # (spaces? >> str('//') >> spaces? >> ((new_line.absent? >> any).repeat).as(:comment) >> new_line))
        ((spaces? >> str('/*') >> spaces? >> ((str('*/').absent? >> any).repeat) >> str('*/') >> spaces? ) |
         (spaces? >> str('//') >> spaces? >> ((new_line.absent? >> any).repeat) >> new_line))
    }

    rule(:comments) { comment.repeat(1)}
    rule(:comment?) { comment.maybe }
    rule(:comments?) { comments.maybe }


    rule(:left_brace) { (str('{') | str('<%')) >> spaces? }
    rule(:right_brace) { (str('}') | str('%>')) >> spaces? }

    rule(:left_bracket) { (str('[') | str('<:')) >> spaces? }
    rule(:right_bracket) { (str(']') | str(':>')) >> spaces? }

    def self.operators(operators={})
        trailing_chars = Hash.new { |hash,symbol| hash[symbol] = [] }

        operators.each_value do |symbol|
            operators.each_value do |op|
                if op[0,symbol.length] == symbol
                    char = op[symbol.length,1]

                    unless (char.nil? || char.empty?)
                        trailing_chars[symbol] << char
                    end
                end
            end
        end

        operators.each do |name,symbol|
            trailing = trailing_chars[symbol]

            if trailing.empty?
                rule(name) { str(symbol).as(:operator) >> spaces? }
            else
                pattern = "[#{Regexp.escape(trailing.join)}]"

                rule(name) {
                    (str(symbol) >> match(pattern).absent?).as(:operator) >> spaces?
                }
            end
        end
    end

    operators :right_shift_assign => '>>=', :left_shift_assign => '<<=', :add_assign => '+=',
              :subtract_assign => '-=',     :multiply_assign => '*=',    :divide_assign => '/=',
              :modulus_assign => '%=',      :binary_and_assign => '&=',  :xor_assign => '^=',
              :binary_or_assign => '|=',    :inc => '++',                :dec => '--',
              :pointer_access => '->',      :logical_and => '&&',        :logical_or => '||',
              :less_equal => '<=',          :greater_equal => '>=',      :equal => '==',
              :not_equal => '!=',           :assign => '=',              :add => '+',
              :subtract => '-',             :multiply => '*',            :divide => '/',
              :modulus => '%',              :less => '<',                :greater => '>',
              :negate => '!',               :binary_or => '|',           :binary_and => '&',
              :xor => '^',                  :left_shift => '<<',         :right_shift => '>>',
              :inverse => '~'

    rule(:esc_newline) {
        str("\\\n")
    }

    rule(:preprocessor_line) {
        (str('#') >> (
            esc_newline |
            (new_line.absent? >> any)
        ).repeat >> new_line).as(:pp) >> spaces?
    }

    def self.keywords(*names)
        names.each do |name|
            rule("#{name}_keyword") { str(name.to_s).as(:keyword) >> spaces? }
        end
    end

    keywords :auto, :break, :case, :continue, :default, :do, :double, :else,
        :enum, :extern, :for, :goto, :if, :register, :return, :sizeof, :static,
        :switch, :typedef, :union, :void, :volatile, :while

    def self.keywords_(*names)
        names.each do |name|
            rule("#{name}_keyword") { str(name.to_s) >> spaces? }
        end
    end

    keywords_ :char, :const, :float, :int, :long, :short, :signed, :struct, :unsigned

    def self.symbols(symbols)
        symbols.each do |name,symbol|
            rule(name) { str(symbol) >> spaces? }
        end
    end

    symbols :ellipsis => '...',
        :semicolon => ';',
        :comma => ',',
        :colon => ':',
        :left_paren => '(',
        :right_paren => ')',
        :member_access => '.',
        :question_mark => '?'


    rule(:identifier) { (alpha >> (alpha | digit).repeat) >> spaces?  }
    rule(:identifier_type) {
        (signed_keyword >> short_keyword >> int_keyword) |
        (signed_keyword >> long_keyword >> int_keyword) |
        (signed_keyword >> long_keyword >> long_keyword) |

        (signed_keyword >> char_keyword) |
        (signed_keyword >> short_keyword) |
        (signed_keyword >> int_keyword) |
        (signed_keyword >> long_keyword) |

        (unsigned_keyword >> short_keyword >> int_keyword) |
        (unsigned_keyword >> long_keyword >> int_keyword) |
        (unsigned_keyword >> long_keyword >> long_keyword) |

        (unsigned_keyword >> char_keyword) |
        (unsigned_keyword >> short_keyword) |
        (unsigned_keyword >> int_keyword) |
        (unsigned_keyword >> long_keyword) |

        (short_keyword >> int_keyword) |
        (long_keyword >> int_keyword) |
        (long_keyword >> long_keyword) |

        identifier
    }

    rule(:expr) { (str('/*').absent? >> match('[a-zA-Z_0-9 \n\t\-<>()|/+]')).repeat.as(:expr) }

    rule(:enum_type_declare) {
        (
            enum_keyword >> comments? >> identifier.maybe >> comments? >>
            (
                left_brace >> enumerator_list >> right_brace
            )
        ).as(:enum_type_declare)
    }
    rule(:enumerator) {
        spaces |
        comment |
        preprocessor_line |
        (
            (
                identifier.as(:enum_name) >> (assign >> expr).maybe
            ) >> spaces? >> cap.maybe.as(:cap) >> spaces? >> comma.maybe
        ).as(:enum)
    }
    rule(:enumerator_list) { enumerator.repeat.as(:enums) }

    rule(:array) {
        (left_bracket >> expr >> right_bracket) |
        comments
    }

    rule(:cap) {
        (str("CAP") >> left_paren >> identifier >> right_paren) |
        (str("CAPF") >> left_paren >> identifier >> right_paren) |
        (str("CAPA") >> left_paren >> identifier >> right_paren)
    }

    rule(:ptr_annotation) {
        str("MEPA_SHARED_PTR")
    }

    rule(:mesa_attr) {
        (spaces? >> str("MESA_ATTR_PRINTF") >> left_paren >> digits >> comma >> digits >> right_paren) |
        (spaces? >> str("VTSS_ATTR_PRINTF") >> left_paren >> digits >> comma >> digits >> right_paren) |
        (spaces? >> str("VTSS_OS_COMPILER_ATTRIBUTE_ALIGNED") >> left_paren >> identifier >> right_paren)
    }

    rule(:qualifier) {
        struct_keyword |
        static_keyword |
        const_keyword |
        ptr_annotation |
        str('*') |
        spaces
    }

    rule(:function_ptr) {
        type.as(:return_type) >>
        left_paren >>
        str('*') >>
        spaces? >>
        identifier.as(:fptr_name) >>
        right_paren >>
        left_paren >>
        arg_list.as(:args) >>
        right_paren >>
        cap.maybe.as(:cap) >>
        mesa_attr.maybe
    }

    rule(:type) {
        qualifier.repeat >> identifier_type >> qualifier.repeat
    }

    rule(:type_and_name) {
        (
            type.as(:type) >>
            identifier.as(:name) >>
            spaces? >>
            array.repeat.as(:array) >>
            spaces? >>
            cap.maybe.as(:cap) >>
            mesa_attr.maybe >>
            spaces?
        ).as(:normal) | function_ptr.as(:fptr)

        #(identifier.repeat(2) >> array.repeat).as(:type_and_name)
    }

    rule(:union_type_declare) {
        (union_keyword >> identifier.maybe >> (left_brace >> union_member_list >> right_brace)).as(:union_type_declare)
    }
    rule(:union_member) {
        spaces |
        comment |
        preprocessor_line |
        (struct_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_struct) |
        (union_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_union) |
        (enum_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_union) |
        (type_and_name >> semicolon).as(:member)
    }
    rule(:union_member_list) { union_member.repeat.as(:union_members) }

    rule(:struct_proto) {
        struct_keyword >> identifier >> spaces? >> semicolon
    }

    rule(:struct_type_declare) {
        (struct_keyword >> identifier.maybe >> (left_brace >> struct_member_list >> right_brace)).as(:struct_type_declare)
    }
    rule(:struct_member) {
        spaces |
        comment |
        preprocessor_line |
        (struct_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_struct) |
        (union_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_union) |
        (enum_type_declare >> identifier.as(:name) >> array.repeat.as(:array) >> semicolon).as(:member_union) |
        (type_and_name >> semicolon).as(:member)
    }
    rule(:struct_member_list) { struct_member.repeat.as(:struct_members) }

    rule(:type_decl) {
        typedef_keyword >>
        (
            (
                (
                    enum_type_declare |
                    struct_type_declare |
                    union_type_declare |
                    type.as(:type_alias)
                ) >> identifier.as(:typedef_name) >> spaces? >> array.repeat.as(:array) >> spaces? >> cap.maybe.as(:cap)
            ) | function_ptr.as(:typedef_fptr)
        ) >> semicolon
    }

    rule(:arg) {
        spaces |
        comment |
        preprocessor_line |
        (type_and_name >> comma.maybe) |
        str("...") |
        void_keyword
    }
    rule(:arg_list) { arg.repeat }

    rule(:func_base) {
        extern_keyword.maybe >>
        type_and_name >>
        left_paren >>
        arg_list.as(:args) >>
        right_paren >>
        spaces? >>
        cap.maybe.as(:cap) >>
        mesa_attr.maybe
    }

    rule(:func_proto) {
        (func_base >> semicolon).as(:func_proto)
    }

    rule(:translation_unit) { external_declaration_ext.repeat.as(:root) }

    rule(:extern_c) {
        extern_keyword >> string_literal >> left_brace >> external_declaration_ext.repeat.as(:root) >> right_brace
    }

    rule(:external_declaration_ext) {
        comment           |
        spaces            |
        preprocessor_line |
        extern_c          |
        type_decl         |
        func_proto        |
        struct_proto      |
        (extern_keyword >> type_and_name >> semicolon) |
        (enum_type_declare >> semicolon)
    }

    rule(:string_literal) {
        (str('"') >> (match("\\.") | match('[^\\"]')).repeat >> str('"')).as(:string) >> spaces?
    }

    root :translation_unit
end

