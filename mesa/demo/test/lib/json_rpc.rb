#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

require 'net/http'
require 'json'
require 'optparse'

$s = TCPSocket.open($dut.ip_addr, 1234)
$s_mutex = Mutex.new

$json_error_disble = false

def send_req(method, *params)
    req = {'method' => method, 'params' => params, 'id' => 'jsonrpc'}.to_json
    Log.info "Request: #{method} #{params}"

    resp_txt = nil
    begin
        # Messages start with a 4 byte length field
        $s_mutex.synchronize {
            $s.write([req.length].pack('N'))
            $s.write(req)
            hdr = $s.read(4)
            len = hdr.unpack('N')[0]
            resp_txt = $s.read(len)
        }
    rescue Exception => e
        Log.error("#{method} #{e.message}")
        Log.info("Request: #{req}")
        raise e
    end
    Log.info("Response: #{resp_txt}")
    resp = JSON.parse(resp_txt)
    error = resp["error"]
    Log.msg("#{error}", !$json_error_disable) unless error.nil?
    return resp["result"]
end

def get_req(method, *params)
    result = send_req(method, *params)
    return result if result.nil?
    result.each {|res| return res unless res.nil?}
    Log.error("result not found")
    return nil
end

def cap_get cap
    return get_req("mesa_capability", "MESA_CAP_" + cap)
end

class MesaJson
    attr_accessor :error_disable

    def initialize(name)
        @name = "mesa_#{name}"
        @error_disable = false
    end

    def get(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = get_req("#{@name}_get", *params)
        $json_error_disable = old
        res
    end

    def get_all(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = send_req("#{@name}_get", *params)
        $json_error_disable = old
        res
    end

    def get_next(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = get_req("#{@name}_get_next", *params)
        $json_error_disable = old
        res
    end

    def set(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = send_req("#{@name}_set", *params)
        $json_error_disable = old
        res
    end

    def clear(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = send_req("#{@name}_clear", *params)
        $json_error_disable = old
        res
    end

    def init(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = get_req("#{@name}_init", *params)
        $json_error_disable = old
        res
    end

    def add(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = send_req("#{@name}_add", *params)
        $json_error_disable = old
        res
    end

    def del(*params)
        old = $json_error_disable
        $json_error_disable = true if @error_disable
        res = send_req("#{@name}_del", *params)
        $json_error_disable = old
        res
    end

    def set_value(*params)
        len = params.length
        fld = params[len - 2]
        value = params[len - 1]
        p = []
        for i in 0..(len - 3)
            p << params[i]
        end
        conf = get(*p)
        conf[fld] = value
        set(*p, conf)
    end

    def set_check(*params)
        set(*params)
        conf = get(params[0..-1])
    end
end

