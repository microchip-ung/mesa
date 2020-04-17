#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT

class Log
    @@error_cnt = 0
    @@time_start = Time.now
    @@mutex = Mutex.new
    @@error_exit = false

    def self.error_cnt
        @@error_cnt
    end

    def self.error_exit=(value)
        @@error_exit = value
    end

    def self.error(txt)
        t_e txt
        @@error_cnt = (@@error_cnt + 1)
        if (@@error_exit)
            self.info("Exiting due to error")
            exit
        end
    end
    
    def self.warning(txt)
        t_w txt
    end

    def self.info(txt)
        t_i txt
    end

    def self.debug(txt)
        t_d txt
    end

    def self.noise(txt)
        t_n txt
    end

    def self.msg(txt, error = false)
        if (error)
            self.error(txt)
        else
            self.info(txt)
        end
    end
end
