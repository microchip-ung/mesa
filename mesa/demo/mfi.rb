#!/usr/bin/env ruby

# Copyright (c) 2004-2020 Microchip Technology Inc. and its subsidiaries.
# SPDX-License-Identifier: MIT


require 'zlib'     # For CRC
require 'logger'
require 'openssl'  # For RSA Signing
require 'optparse' # For command line parsing

$public_key_file = nil
$shaFile = nil
$shaToFingerprint = {}
$dumpfileindex = 0

def bin_to_hex(s)
  s.each_byte.map { |b| b<16?("0"+b.to_s(16)):b.to_s(16) }.join
end

def hex_to_bin(s)
 s.scan(/../).map { |x| x.hex.chr }.join
end

class MyLogger < Logger
  def fatal txt
    super(txt)
    exit
  end
end

class Signature
  # Signature types
  MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5       = 1
  MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256    = 2
  MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512    = 3

  attr_accessor :key
  attr_accessor :type
  attr_accessor :fingerprint
  attr_accessor :checksum_validated

  def initialize t
    @type = t
    @fingerprint = ""
    @checksum_validated = "(not validated)"
  end

  def size
    sz = 0
    case @type
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
      sz = 16
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
      sz = 256
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
      sz = 256
    else
      $v.fatal("Unknown hash type: #{@type}")
    end
    return sz
  end

  def update d
    case @type
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
      @digest = OpenSSL::Digest::MD5.new(d)
      @fingerprint = @digest.digest
      $v.debug("Updated hash signature, type: #{@type}, length: #{@digest.digest.length}")
      return

    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
      @digest = OpenSSL::Digest::SHA256.new
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
      @digest = OpenSSL::Digest::SHA512.new
    else
      $v.fatal("Unknown hash type: #{@type}")
      return
    end

    if @key.nil?
        raise "Can not sign without a key"
    end

    checksum_validated = "(updated)"
    @fingerprint = @key.sign(@digest, d)
    $v.debug("Updated signature, type: #{@type}, length: #{size}")
  end

  def shaFileLookup d
    case @type
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
      @digest = OpenSSL::Digest::MD5.new(d)
      @fingerprint = @digest.digest
      $v.debug("Updated hash signature, type: #{@type}, length: #{@digest.digest.length}")
      return

    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
      @digest = OpenSSL::Digest::SHA256.new
    when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
      @digest = OpenSSL::Digest::SHA512.new
    else
      $v.fatal("Unknown hash type: #{@type}")
      return
    end

    sha = bin_to_hex(@digest.digest(d))
    signature = $shaToFingerprint[sha]

    return (signature.nil?)?nil:hex_to_bin(signature)
  end

  def readkey f
    if f == nil
      $v.fatal("Keyfile must be given")
    end
    @key = OpenSSL::PKey::RSA.new File.read f
  end

  def sig_str
      return @fingerprint.bytes.collect{|x| "%02x" % x}.join("")
  end

  def dump
      case @type
      when MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
          puts "  MD5(#{@type}), Length:#{@fingerprint.size} Data: #{sig_str} #{checksum_validated}"
      when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
          puts "  SHA256(#{@type}), Length:#{@fingerprint.size} #{checksum_validated}"
      when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
          puts "  SHA512(#{@type}), Length:#{@fingerprint.size} #{checksum_validated}"
      else
          puts "  Unknown signature(#{@type}), Length:#{@fingerprint.size} Data: #{sig_str} #{checksum_validated}"
      end
      if (size > 0)
          $v.debug("  SHA Fingerprint: #{@fingerprint.bytes.collect{|x| "%02x" % x}.join("")}")
      end
  end

  def validate_pub data
      _digest = nil
      case @type
      when MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
          _digest = OpenSSL::Digest::MD5.new(data)
          if _digest.digest == @fingerprint
              @checksum_validated = "(validated)"
          else
              @checksum_validated = "(invalid)"
          end
          return @checksum_validated

      when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
          _digest = OpenSSL::Digest::SHA256.new
      when MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
          _digest = OpenSSL::Digest::SHA512.new
      else
          raise "Unknown hash type: #{@type}"
      end

      if $public_key_file.nil?
          $v.debug("SHA = #{bin_to_hex _digest.digest(data)}")
          if $shaToFingerprint[bin_to_hex _digest.digest(data)].nil?
            $shaToFingerprint[bin_to_hex _digest.digest(data)] = nil
          end
          if $v.level==Logger::DEBUG
            f = File.open("dump#{$dumpfileindex}",'wb')
            $dumpfileindex = $dumpfileindex+1
            f.write(data)
          end
          @checksum_validated = "(not validated)"
          return @checksum_validated
      end

      pub_key = OpenSSL::PKey::RSA.new File.read $public_key_file
      if pub_key.verify(_digest, @fingerprint, data)
          @checksum_validated = "(validated)"
      else
          @checksum_validated = "(invalid)"
      end
      return @checksum_validated
  end
end

#############################################################################
# Stage1
#############################################################################
class Stage1Tlv
  attr_accessor :type
  attr_accessor :p

  KERNEL_TLV     = 0
  SIGNATURE_TLV  = 1
  INITRD_TLV     = 2
  KERNEL_CMD_TLV = 3
  METADATA_TLV   = 4
  LICENSES_TLV   = 5
  STAGE2_TLV     = 6
  FDT_TLV        = 7
  MAX_TLV        = 7            # Keep name, update value when adding new TLVs

  # constructor
  def initialize type, data
    @type = type
    @p = data
  end

  def payloadSet d
    @p = d
  end

  def payload
    return @p
  end

  def octet_string
    d =  [@type].pack("V")
    padLen = 4 - ((@p.size) % 4)
    d += [12 + @p.size + padLen].pack("V")
    d += [@p.size].pack("V")
    d += @p
    d += ["\x00"].pack("a#{padLen}") if padLen
    return d
  end

  def write f
    f.write octet_string
  end

  def dump extra
    if extra.nil?
        extra = ""
    end

    if extra.size > 0
        extra = " " + extra
    end

    case @type
    when KERNEL_TLV
        puts "  Tlv Type:Kernel(#{@type}), Data Length:#{@p.length}#{extra}"
    when SIGNATURE_TLV
        puts "  Tlv Signature(#{@type}),   Data Length:#{@p.length}#{extra}"
    when INITRD_TLV
        puts "  Tlv Initrd(#{@type}),      Data Length:#{@p.length}#{extra}"
    when KERNEL_CMD_TLV
        puts "  Tlv KernelCmd(#{@type}),   Data Length:#{@p.length}#{extra}"
    when METADATA_TLV
        puts "  Tlv Metadata(#{@type}),    Data Length:#{@p.length}#{extra}"
    when LICENSES_TLV
        puts "  Tlv License(#{@type}),     Data Length:#{@p.length}#{extra}"
    when STAGE2_TLV
        puts "  Tlv Stage2(#{@type}),      Data Length:#{@p.length}#{extra}"
    when FDT_TLV
        puts "  Tlv FDT(#{@type}),         Data Length:#{@p.length}#{extra}"
    else
        puts "  Tlv Unknown(#{@type}),     Data Length:#{@p.length}#{extra}"
    end
  end
end

#############################################################################
# Stage2
#############################################################################
class Stage2Tlv
  STAGE2_MAGIC = 0xa7b263fe
  STAGE2_DATA_OFFSET = 20

  BOOTLOADER_TLV = 1
  ROOTFS_TLV = 2 # Section 2.2.2

  # TODO, make private
  attr_accessor :type

  # constructor
  def initialize type
    @type = type
    @p = ""
    @signature = Signature.new(Signature::MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5)
    @signature_needs_update = true
  end

  def checksum_validated s
      @signature.checksum_validated = s
  end

  def payloadSet d
    if @p != d
        @p = d
        @signature_needs_update = true
        $v.debug("#{self} S2TLV: payloadSet Key=#{@signature.key.nil?} signature_needs_update=#{@signature_needs_update}")
    end
  end

  def sig_set type, file
      @signature = Signature.new(type)
      @signature.readkey file
      @signature_needs_update = true
  end

  def force_signature type, data
    @signature.type = type
    @signature.fingerprint = data
    if @signature.key.nil?
        @signature_needs_update = false
    end
    $v.debug("#{self} S2TLV: force_signature type=#{type} Key=#{@signature.key.nil?} signature_needs_update=#{@signature_needs_update}")
  end

  def validate_signature data
      @signature.validate_pub data
  end

  def payload
    return @p
  end

  def octet_string
    # Offset 0, size 4 - MAGIC
    d =  [STAGE2_MAGIC].pack("V")

    # Offset 4, size 4, TLV-Type
    d += [@type].pack("V")

    # Offset 8, size 4, TLV-Complete-size
    tlv_size = @p.size + STAGE2_DATA_OFFSET + @signature.size
    $v.debug("S2TLV: Payload size: %d, Hdr size: %d, Signature size: %d, tlv_size: %d" % [@p.size, STAGE2_DATA_OFFSET, @signature.size, tlv_size])
    d += [tlv_size].pack("V")

    # Offset 12, size 4, Payload-size
    d += [@p.size].pack("V")

    # Offset 16, size 4, Signature type
    d += [@signature.type].pack("V")

    # Offset 20, size @p.size
    raise "S2TLV: BAD INVARIANT: Unexpected offset: #{d.size} != #{STAGE2_DATA_OFFSET}" if d.size != STAGE2_DATA_OFFSET
    d += @p

    # Offset 20 + size @p.size, size ?
    $v.debug("S2TLV: Signature needs update? #{@signature_needs_update}")
    if @signature_needs_update
        @signature.update(d)
    end
    d += @signature.fingerprint

    if @signature.fingerprint.size != @signature.size
        raise "S2TLV: BAD INVARIANT: Unexpected signature-size: #{@signature.fingerprint.size} != #{@signature.size}"
    end

    if d.size != tlv_size
        raise "S2TLV: BAD INVARIANT: Unexpected tlv-size: #{d.size} != #{tlv_size}"
    end

    return d
  end

  def write f
    f.write octet_string
  end

  def getData
    return @p
  end

  def dump
      case @type
      when Stage2Tlv::BOOTLOADER_TLV
          puts "  Tlv Bootloader(#{@type}), Data Length:#{@p.length}"
      when Stage2Tlv::ROOTFS_TLV
          puts "  Tlv FsElement(#{@type}), Data Length:#{@p.length}"
      else
          puts "  Tlv Unknown(#{@type}), Data Length:#{@p.length}"
      end
      @signature.dump
  end
end


##################################################################
## Misc
##################################################################
def checkForMissingOutputFile outputFile
  $v.fatal("You must specific a output file with --output") if outputFile.nil?
end

def checkForMissingInputFile
  $v.fatal("Image file required (--input global option)") if !$Image.imageParsed
end

##################################################################
## Stage1
##################################################################
class Stage1
  MAGIC1 = 0xedd4d5de
  MAGIC2 = 0x987b4c4d

  MACHINE_LEN    = 32   #See C header file
  SOC_NAME_LEN   = 32   #See C header file

  def initialize
    @magic1       = MAGIC1
    @magic2       = MAGIC2
    @version      = 2
# 1: Original version
# 2: NAND stage2 may hold stage1 as well. (No change to layout)
    @machine      = ""
    @socName      = ""
    @socNo        = 0
    @sig          = Signature::new(Signature::MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5)
    @tlvs         = []
    @signature_needs_update = true
  end

  def dump
    puts "Stage1"
    if (@magic1 != MAGIC1) && (@magic2 != MAGIC2)
      puts "  No Stage1 information."
      return
    end

    puts "  Version:#{@version}"
    puts "  Magic1:0x#{@magic1.to_s(16)}, Magic2:0x#{@magic2.to_s(16)}, HdrLen:#{@hdrLen}, ImgLen:#{@imgLen}"
    puts "  Machine:#{@machine}, SocName:#{@socName}, SocNo:#{@socNo}, SigType:#{@sig.type}"

    @tlvs.each do |tt|
      if tt
        if tt.type == Stage1Tlv::SIGNATURE_TLV
          tt.dump @sig.checksum_validated
        else
          tt.dump ""
        end
      end
    end
  end

  def socNoSet i
      @socNo = i
      @signature_needs_update = true
  end

  def socNoGet
      return @socNo
  end

  def nameSet type, newName
    case type
    when :machine
      $v.fatal("Machine name must not exceed #{MACHINE_LEN} characters") if newName.length > MACHINE_LEN
      @machine = newName
      @signature_needs_update = true

    when :socName
      $v.fatal("Soc name must not exceed #{SOC_NAME_LEN} characters") if newName.length > SOC_NAME_LEN
      @socName = newName
      @signature_needs_update = true

    end
  end

  def nameGet type
    case type
    when :machine
      return @machine

    when :socName
      return @socName

    end
  end

  def getData type
    case type
    when :kernel
      return @kernel.getData

    when :initrd
      return @initrd.getData

    when :metadata
      return @metadata.getData

    else
      $v.fatal("Unknown stage1 type:#{type}")
    end
  end

  def SetTlv type, data
    tlv = Stage1Tlv.new(type, data)
    $v.debug("Set TLV type #{type} to #{data}")
    @tlvs[type] = tlv
    @signature_needs_update = true
  end

  def GetTlv type
    return @tlvs[type]
  end

  def ReadTlv type, fileName
    tlv = Stage1Tlv.new(type, IO.binread(fileName))
    $v.debug("Read TLV type #{type} from #{fileName}")
    @tlvs[type] = tlv
  end

  def SetKey type, fileName
    $v.debug("Set key type #{type} keyfile #{fileName}")
    @sig = Signature::new(type)
    @sig.readkey(fileName)
    @signature_needs_update = true
  end

  def write f
    d = [MAGIC1, MAGIC2, @version].pack("VVV")
    d += [0, 0].pack("VV")      # length placeholders
    d += [@machine, @socName, @socNo].pack("a#{MACHINE_LEN}a#{SOC_NAME_LEN}V")
    d += [@sig.type].pack("V")      # Signature placeholder

    d[12,4] = [d.length].pack("V")

    $v.debug("Stage1 hdr len : #{d.length}")

    t = Stage1Tlv.new(Stage1Tlv::SIGNATURE_TLV, [""].pack("a#{@sig.size}"))
    sigOff = d.length                       # Save location for later update
    d += t.octet_string

    @tlvs.each do |tt|
      if tt != nil && tt.type != Stage1Tlv::SIGNATURE_TLV
        d += tt.octet_string
     end
    end

    # Update length
    d[16,4] = [d.length].pack("V")

    # Update signature
    if @signature_needs_update
        @sig.update(d)
    end
    $v.fatal("STAGE1: Signature length error #{@sig.size} vs. #{@sig.fingerprint.length} ") if(@sig.size != @sig.fingerprint.length)
    d[sigOff+12, @sig.fingerprint.length] = @sig.fingerprint
    $v.debug("STAGE1: Insert signature #{@sig.type} at #{sigOff}, length #{@sig.fingerprint.length}")

    if f.nil?
      puts d
    else
      $v.debug("STAGE1: Write raw data #{d.size}")
      f.write d
    end
  end

  def validate sigtype, offset, data
    $v.debug("validate at offset #{offset} length #{data.length} siglen #{@sig.size}")
    data[offset + 12, @sig.size] = [""].pack("a#{@sig.size}")
    @sig.validate_pub(data)
  end

  def shaFileLookup sigtype, offset, data
    $v.debug("validate at offset #{offset} length #{data.length} siglen #{@sig.size}")
    data[offset + 12, @sig.size] = [""].pack("a#{@sig.size}")
    @sig.shaFileLookup(data)
  end

  def parse d
    # See vtss_appl/firmware/firmware_vimage.h for understanding the below
    @magic1, @magic2, @version, @hdrLen, @imgLen = d.unpack("V5")

    if (@magic1 != MAGIC1) && (@magic2 != MAGIC2)
      puts "Magic numbers not correct - continue as there is no stage 1"
      return d
    end

    hdr = d.byteslice(0, @hdrLen)

    #Skip the part of the header we have already parsed.
    skip, hdr = hdr.unpack("a20a#{@hdrLen}")

    @machine, @socName, @socNo, @sig.type, hdr = hdr.unpack("a#{MACHINE_LEN}a#{SOC_NAME_LEN}VVa*")
    $v.debug("%s %s %d %d" % [@machine, @socName, @socNo, @sig.type])

    # Parse TLVs
    @tlvs.clear
    if @sig.key.nil?
        @signature_needs_update = false
    end
    tdata = d.byteslice(@hdrLen..@imgLen-1)
    while tdata.length > 0
      $v.debug("Have data #{tdata.length}")
      tt, tl, tdl = tdata.unpack("V3")
      $v.debug("Have TLV type #{tt}, totlen #{tl}, dlen #{tdl}")
      if tt >= Stage1Tlv::KERNEL_TLV && tt <= Stage1Tlv::MAX_TLV
        tlv = Stage1Tlv.new(tt, tdata.byteslice(12, tdl))
        @tlvs[tt] = tlv
      else
        $v.fatal("Invalid TLV, type #{tt}, length #{tl}")
      end
      tdata = tdata.byteslice(tl..-1)
    end

    if @tlvs[Stage1Tlv::SIGNATURE_TLV]
      # Update existing fingerprint
      @sig.fingerprint = nil
      if ($shaFile)
        @sig.fingerprint = shaFileLookup(@sig.type, @hdrLen, d.byteslice(0, @imgLen))
      end
      if @sig.fingerprint.nil?
        @sig.fingerprint = @tlvs[Stage1Tlv::SIGNATURE_TLV].p
      end

      #validate signature
      $v.debug("Fingerprint: #{bin_to_hex @sig.fingerprint}")
      validate @sig.type, @hdrLen, d.byteslice(0, @imgLen)

    else
      $v.fatal("No signature present - need at least a MD5 hash")
    end

    return d.byteslice(@imgLen..-1)
  end
end


##################################################################
## Image
##################################################################

def parse_stage2_tlv d
  magic, type, length, dataLength, signatureType, data = d.unpack("V5a*")

  raise Exception.new("Datalength unexpect 0 bytes long ???") if dataLength == 0

  $v.debug("d.size = #{d.size} length = #{length} dataLength = #{dataLength}")
  p = data.byteslice(0, dataLength)

  if (magic != Stage2Tlv::STAGE2_MAGIC)
    $v.debug("%08x %d %d %d %d" % [magic, type, length, dataLength, signatureType])
    $v.fatal("ERROR Wrong magic: %08x != %08x" % [magic, Stage2Tlv::STAGE2_MAGIC])
  end

  # Return the rest of the TLVs
  res = d.byteslice(length, d.length)
  if res.nil?
    res = ""
  end

  tlv = nil
  case type
  when Stage2Tlv::ROOTFS_TLV
    tlv = Stage2Rootfs.new
    tlv.parse p
  else
    tlv = Stage2Tlv.new type
    tlv.payloadSet(p)
  end

  parsed_sigoff = dataLength + Stage2Tlv::STAGE2_DATA_OFFSET
  parsed_siglen = length - parsed_sigoff
  sig_check_data = d.byteslice(0, length - Signature.new(signatureType).size)

  parsed_fingerprint = nil
  if ($shaFile)
    parsed_fingerprint = Signature.new(signatureType).shaFileLookup(sig_check_data)
  end
  if parsed_fingerprint.nil?
    parsed_fingerprint = d.byteslice(parsed_sigoff, parsed_siglen)
  end
  tlv.force_signature(signatureType, parsed_fingerprint)

  tlv.validate_signature(sig_check_data)

  return res, tlv
end

class Image
  attr_accessor :imageParsed
  attr_accessor :stage1

  def initialize
    @stage1 = Stage1.new
    @stage2 = []
    @imageParsed = false
  end

  def write file
    if @stage1
      @stage1.write file
    end
    @stage2.each do |e|
      e.write file
    end
  end

  def parse data
    $v.debug("Parsing image file. Size: #{data.size}")
    data = @stage1.parse data

    $v.debug("Stage 1 parsed. Size left: #{data.size}")
    #begin
        while data and data.size > 0
            (data, s) = parse_stage2_tlv data

            $v.debug("Adding stage 2 TLV. Size left: #{data.size}")
            @stage2 << s
        end
    #rescue Exception => e
    #    $v.info("Parse error: #{e.message}")
    #    $v.info("Input file parsed partly!")
    #end

    @imageParsed = true
  end

  # Stage 1 ###########################
  def stage1_machine_set newName
    @stage1.nameSet :machine, newName
  end

  def stage1_socname_set newName
    @stage1.nameSet :socName, newName
  end

  def stage1_socno_set newNo
    $v.fatal("Soc Number must be an integer.") if (Integer(newNo) rescue true) == true
    @stage1.socNoSet(newNo.to_i)
  end

  def stage1_output type, file
    if file
      data = @stage1.getData type
      IO.write(file, data)
    else
      puts @stage1.getData
    end
  end

  # Stage2 ############################
  def stage2_delete i
    @stage2.delete_at i
  end

  def stage2_append t
    @stage2 << t
  end

  def stage2_insert i, t
    @stage2.insert i, t
  end

  def stage2_replace i, t
    @stage2[i] = t
  end

  def stage2_get i
    return @stage2[i]
  end

  def stage2_set tlv, t
    stage2_replace_or_append tlv, t
  end

  def stage2_output i, file
    t = stage2_get i

    $v.fatal("No file found for index:#{i}") if t.nil?

    if file
      IO.write(file, t.getData)
    else
      puts t.getData
    end
  end

  # Calling stage2_output with the index of the first stage2 with TLV type = tlv
  def stage2_output_first_tlv tlv, file
    stage2_output find_first_index(tlv), file
  end

  # Deleting stage2 entry with the index of the first stage2 entry with TLV type = tlv
  def stage2_delete_first_tlv tlv
    stage2_delete find_first_index(tlv)
  end

  # Check if a TLV with type = tlv exist. If it exist the TLV is replaced by "t", else "t" is appended
  def stage2_replace_or_append tlv, t
    i = find_first_index(tlv)
    if i >= 0
      stage2_replace i,t
    else
      stage2_append t
    end
  end

  def stage2_action i, file, t, action
    case action
    when :get
      stage2_output  i, file

    when :set
      stage2_set t.type, t

    when :delete
      stage2_delete i

    when :append
      stage2_append t

    when :insert
      stage2_insert i, t

    when :replace
      stage2_replace i ,t
    end
  end

  def dump
    @stage1.dump

    i = 0
    @stage2.each do |d|
      puts "Stage2 - Index:#{i}"
      d.dump
      i += 1
    end
  end

  private

  # Find the index of the first stage2 with TLV type = tlv
  def find_first_index tlv
    i = 0
    indexFound = -1 # Use -1 to indicate no TLV found
    @stage2.each do |e|
      if e.type == tlv
        indexFound = i
        break
      end
      i += 1
    end

    return indexFound
  end


end

##################################################################
## Rootfs
##################################################################

# Root file system element (Section 2.2.2 In TN1299)
class Stage2Rootfs < Stage2Tlv
  # Sub TLVs
  NAME     = 1
  VERSION  = 2
  LICENSE  = 3
  PREEXEC  = 4
  TARXZ    = 5
  POSTEXE  = 6
  FILENAME = 7
  SQUASHFS = 8

  SUB_TLV_HDR_LEN = 8 # Type + Length fields  Section 2.2.2

  attr_accessor :name
  attr_accessor :version
  attr_accessor :license
  attr_accessor :preexec
  attr_accessor :content_tar
  attr_accessor :content_squash
  attr_accessor :postexec
  attr_accessor :filename

  alias_method  :super_dump, :dump
  def dump
    super_dump
    puts "    Name:                           #{@name}" if @name
    puts "    Version:                        #{@version}" if @version
    puts "    License:                        Found" if @license # We can not print License text, since it is base64 packed.
    puts "    Preexec file length:            #{@preexec.length}" if @preexec
    puts "    Content file name:              #{@filename}" if @filename
    puts "    Content (tar) file length:      #{@content_tar.length}" if @content_tar
    puts "    Content (squashfs) file length: #{@content_squash.length}" if @content_squash
    puts "    Postexec file length:           #{@postexec.length}" if @postexec
  end

  def initialize
    super Stage2Tlv::ROOTFS_TLV
    @name = nil
    @version = nil
    @license = nil
    @preexec = nil
    @content_tar = nil
    @postexec = nil
    @filename = nil
    @content_squash = nil
  end

  alias_method  :super_write, :write

  def serialize
    data = ""
    data += put_sub_tlv NAME, @name
    data += put_sub_tlv VERSION, @version
    data += put_sub_tlv LICENSE, @license
    data += put_sub_tlv PREEXEC, @preexec
    data += put_sub_tlv TARXZ, @content_tar
    data += put_sub_tlv SQUASHFS, @content_squash
    data += put_sub_tlv POSTEXE, @postexec
    data += put_sub_tlv FILENAME, @filename
    payloadSet data
  end

  def getData
    if @content_tar
        return @content_tar
    end
    if @content_squash
        return @content_squash
    end

    return nil
  end

  def write f
    serialize
    super_write f
  end

  # Add a Root file system element
  def put_sub_tlv(subTlvType, data)
    return "" if data.nil?
    outputData =  [subTlvType].pack("V")
    outputData += [data.size + SUB_TLV_HDR_LEN].pack("V")
    outputData += [data].pack("a*")
    return outputData
  end

  def getSubTlv d
    type, length, data = d.unpack("VVa*")
    data = data.byteslice(0, length - SUB_TLV_HDR_LEN)
    d = d.byteslice(length, d.size)
    return type, data, d
  end

  def parse d
    while d.length > 0
      type, data, d = getSubTlv d
      case type
      when NAME
        @name = data
      when VERSION
        @version = data
      when LICENSE
        @license = data
      when PREEXEC
        @preexec = data
      when TARXZ
        @content_tar = data
      when POSTEXE
        @postexec = data
      when FILENAME
        @filename = data
      when SQUASHFS
        @content_squash = data
      else
        raise "Unkown type"
      end
    end

    serialize
  end
end
##################################################################
## Input arguments parser
##################################################################

##################################################################
## Bootloader
##################################################################

def bootloaderOptions(outputFile)
  subOptions = {}
  OptionParser.new do |opts|
    opts.banner = "Usage: bootloader [options]"

    opts.on("-f", "--file <file>", "File to read/write to/from depending on the action.") do |file|
      subOptions[:file] = file
    end

    signatureOption(subOptions, opts)
  end.parse!

  #
  # Action
  #
  t = nil
  $v.fatal("File required (--file option)") if subOptions[:file].nil?
  checkForMissingOutputFile(outputFile)

  # Create, read from file
  t = Stage2Tlv.new(Stage2Tlv::BOOTLOADER_TLV)
  t.payloadSet IO.binread(subOptions[:file])

  # Signature
  if subOptions[:signatureKeyFile]
    t.sig_set(subOptions[:signatureType], subOptions[:signatureKeyFile])
  end

  # Insert into image
  $Image.stage2_action 0, subOptions[:file], t, :set
end

#rootfs
def rootfsOptions(outputFile, contentType)
  subOptions = {}
  OptionParser.new do |opts|
    opts.banner = "Usage: rootfs [options]"

    subOptions[:name] = nil
    opts.on("-n", "--name <string>", "Update the name of a given rootfs TLV entry.") do |string|
      subOptions[:name] = string
    end

    opts.on("-v", "--version <string>", "Update the version string of a given rootfs TLV entry.") do |string|
      subOptions[:version] = string
    end

    opts.on("-l", "--license-terms <file>", "Update the license terms of a given rootfs TLV entry.") do |string|
      subOptions[:licenseFile] = string
    end

    opts.on("-a", "--action <cmd>", [:get, :delete, :append, :insert, :replace], "Action to perform. Valid actions are: get|delete|append|insert|replace.") do |string|
      subOptions[:action] = string
    end

    opts.on("-f", "--file <file>", "File to read/write to/from depending on the action.") do |file|
      subOptions[:rootfsFile] = file
    end

    opts.on("-p", "--pre-exec <file>", "Update the executable that is invoked before the root element is extracted.") do |file|
      subOptions[:preExecFile] = file
    end

    opts.on("-o", "--post-exec <file>", "Update the executable that is invoked after the root element is extracted.") do |file|
      subOptions[:postExecFile] = file
    end

    signatureOption(subOptions, opts)

    subOptions[:index] = 0
    opts.on("-i", "--index <integer>", "TLV index to operate on. Starting from 0. If not specificed index 0 is used") do |index|
      subOptions[:index] = index
    end
  end.parse!

  checkForMissingInputFile if subOptions[:action] == :get

  # Make a rootfs eleement
  t = Stage2Rootfs.new

  #
  # Append, insert, replace
  #
  if [:append, :insert, :replace].include?(subOptions[:action])
  # Check that user doesn't specify both --file and --folder.
    checkForMissingOutputFile(outputFile)

    $v.fatal("Root file MUST be given with the -f option") if subOptions[:rootfsFile].nil?
    if contentType == Stage2Rootfs::TARXZ
        t.content_tar = IO.binread(subOptions[:rootfsFile]) if subOptions[:rootfsFile]
    elsif contentType == Stage2Rootfs::SQUASHFS
        t.content_squash = IO.binread(subOptions[:rootfsFile]) if subOptions[:rootfsFile]
    else
        $v.fatal("Unsupported type")
    end

    t.filename      = subOptions[:rootfsFile]

    t.name          = subOptions[:name]
    t.version       = subOptions[:version]
    t.license       = IO.binread(subOptions[:licenseFile]) if subOptions[:licenseFile]
    t.preexec       = IO.binread(subOptions[:preExecFile]) if subOptions[:preExecFile]
    t.postexec      = IO.binread(subOptions[:postExecFile]) if subOptions[:postExecFile]

    if subOptions[:signatureKeyFile]
        t.sig_set(subOptions[:signatureType], subOptions[:signatureKeyFile])
    end
  end

  $Image.stage2_action subOptions[:index].to_i, subOptions[:rootfsFile], t, subOptions[:action]
end

# Function for parsing signature options
def signatureOption(subOptions, opts)
  subOptions[:signatureType] = Signature::MSCC_FIRMWARE_IMAGE_SIGNATURE_MD5
  opts.on("-s", "--sign-data <type> <keyfile>", [:sha256, :sha512], "Sign data with (RSA) key") do |type, file|
    subOptions[:signatureKeyFile] = ARGV[0]
#    raise "No signature file" if subOptions[:signatureKeyFile].nil?

    case type
    when  :sha256
      subOptions[:signatureType] = Signature::MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA256
    when  :sha512
      subOptions[:signatureType] = Signature::MSCC_FIRMWARE_IMAGE_SIGNATURE_SHA512
    else
      raise "Unknown signature type."
    end
  end
end

# Stage1 Option parser
def stage1Options(outputFile)
  subOptions = {}
  OptionParser.new do |opts|
    opts.banner = "Usage: stage1 [options]"

    opts.on("-a", "--kernel-get <file>", "Extract the kernel from the firmware image, and write it to <file>.") do |file|
      subOptions[:kernelGetFile] = file
    end

    opts.on("-b", "--kernel-set <file>", "Update the kernel blob in the firmware image with the raw content of <file>.") do |file|
      subOptions[:kernelSetFile] = file
    end

    opts.on("-F", "--fdt-set <file>", "Update the FDT blob in the firmware image with the raw content of <file>.") do |file|
      subOptions[:fdtSetFile] = file
    end

    opts.on("-c", "--initrd-get <file>", "Extract the initrd from the firmware image and write it to <file>.") do |file|
      subOptions[:initrdGetFile] = file
    end

    opts.on("-d", "--initrd-set <file>", "Update the initrd blob in the firmware image with the raw content of <file>.") do |file|
      subOptions[:initrdSetFile] = file
    end

    opts.on("-e", "--metadata-get <file>", "Extract the metadata blob from the firmware image and write it to <file>.") do |file|
      subOptions[:metaDataGetFile] = file
    end

    opts.on("-f", "--metadata-set <file>", "Update the metadata blob in the firmware image with the raw content of <file>.") do |file|
      subOptions[:metaDataSetFile] = file
    end

    opts.on("-m", "--machine <string>", "Set the machine string in the image..") do |string|
      subOptions[:machine] = string
    end

    opts.on("-w", "--soc-name <string>", "Set the soc-name string in the image..") do |string|
      subOptions[:socName] = string
    end

    opts.on("-n", "--soc-no <string>", "Set the soc-no string in the image..") do |string|
      subOptions[:socNo] = string
    end

    opts.on("-k", "--kernel-command <string>", "Set the kernel command line in the image..") do |string|
      subOptions[:kernelCmd] = string
    end

    opts.on("-l", "--license-terms <file>", "Update the licenses blob in the firmware image with the raw content of <file>.") do |file|
      subOptions[:licenseFile] = file
    end

    signatureOption(subOptions, opts)
  end.parse!

  checkForMissingInputFile if subOptions[:kernelGetFile] || subOptions[:initrdGetFile] || subOptions[:metaDataGetFile]

  $Image.stage1_output :kernel, subOptions[:kernelGetFile] if subOptions[:kernelGetFile]
  $Image.stage1_output :initrd, subOptions[:initrdGetFile] if subOptions[:initrdGetFile]
  $Image.stage1_output :metadata, subOptions[:metaDataGetFile] if subOptions[:metaDataGetFile]
  $Image.stage1_machine_set subOptions[:machine] if subOptions[:machine]
  $Image.stage1_socname_set subOptions[:socName] if subOptions[:socName]
  $Image.stage1_socno_set subOptions[:socNo] if subOptions[:socNo]
  $Image.stage1.SetTlv Stage1Tlv::KERNEL_CMD_TLV, subOptions[:kernelCmd] if subOptions[:kernelCmd]
  $Image.stage1.ReadTlv Stage1Tlv::KERNEL_TLV, subOptions[:kernelSetFile] if subOptions[:kernelSetFile]
  $Image.stage1.ReadTlv Stage1Tlv::FDT_TLV, subOptions[:fdtSetFile] if subOptions[:fdtSetFile]
  $Image.stage1.ReadTlv Stage1Tlv::INITRD_TLV, subOptions[:initrdSetFile] if subOptions[:initrdSetFile]
  $Image.stage1.ReadTlv Stage1Tlv::METADATA_TLV, subOptions[:metaDataSetFile] if subOptions[:metaDataSetFile]
  $Image.stage1.ReadTlv Stage1Tlv::LICENSES_TLV, subOptions[:licenseFile] if subOptions[:licenseFile]
  $Image.stage1.SetKey(subOptions[:signatureType], subOptions[:signatureKeyFile]) if subOptions[:signatureKeyFile]
  $v.debug("Stage1 key type: #{subOptions[:signatureType]}, file: #{subOptions[:signatureKeyFile]}")
end

def reSign(outputFile)

end

##
## Global options
##
version = "git-ae6434d20ebe03932a4b2263472c6308d08604f4"

globalOptions = {}
global = OptionParser.new do |opts|
  opts.banner = "Usage: mfi [global-options] [<command> [command-specific-options]]"
  opts.version = version

  opts.on("-i", "--input  <file>", "Firmware image to read. New image is created if not specified.") do |inputImage|
    globalOptions[:inputImage] = inputImage
  end

  opts.on("-o", "--output  <file>", "Firmware image to write.") do |outputImage|
    globalOptions[:outputImage] = outputImage
  end

  opts.on("-k", "--public-key  <file>", "Use public key for validation.") do |keyFile|
    $public_key_file = keyFile
  end

  globalOptions[:verbose] = :err
  opts.on("-v", "--verbose  <lvl>", [:info, :debug], "Set verbose level.") do |lvl|
    globalOptions[:verbose] = lvl
  end

  opts.on("-d", "--dump", "Dump the inventory of TLV(s) in the firmware image.") do |d|
    globalOptions[:dump] = true
  end

  opts.on("-V", "--version", "Print the version of this program and exit.") do |d|
    globalOptions[:version] = true
  end

  opts.on("-c", "--collect-sha  <file>", "Collect sha's to file when doing dump.") do |shaFile|
    $shaFile = shaFile
  end

  opts.separator ""
  opts.separator """Commands:
  help          Prints this help message.
  stage1        Inspect or alter the stage1 area of the firmware image.
  bootloader    Inspect or alter any bootloader tlv in the firmware image.
  rootfs        Inspect or alter the rootfs tlv(s) in the firmware image (assuming tarxz).
  rootfs-tar    Inspect or alter the rootfs tlv(s) in the firmware image (assuming tarxz).
  rootfs-squash Inspect or alter the rootfs tlv(s) in the firmware image (assuming squashfs)"""
end.order!

if globalOptions[:version]
  puts "Version: #{version}"
  exit
end

#
#Setup the trace system
#
$v= MyLogger.new(STDOUT)
case globalOptions[:verbose]
when :info
  $v.level = Logger::INFO
when :debug
  $v.level = Logger::DEBUG
else
  $v.level = Logger::ERROR
end

$v.formatter = proc do |severity, datetime, progname, msg|
  "#{msg}\n"
end

#
# Create Image
#

if $shaFile
  begin
    $shaToFingerprint = Hash[*File.read($shaFile).split(/[, \n]+/)]
  rescue  Exception => e
    f = File.open($shaFile,'w')
    f.close
  end
end

$Image = Image.new
if globalOptions[:inputImage]
  # Create a new image if the input image doesn't exist
  $v.fatal("#{globalOptions[:inputImage]}: No such file") if !File.exist?(globalOptions[:inputImage])
  $Image.parse IO.binread(globalOptions[:inputImage])
end

if globalOptions[:dump]
  checkForMissingInputFile
  t = $Image.dump
  if $shaFile
    f = File.open($shaFile,'w')
    $shaToFingerprint.each do |a,b|
      f.write("#{a}, #{b}\n" )
    end
  end
  exit
end

command =  ARGV[0]
subOptions = {}

case command
when "stage1"
  stage1Options(globalOptions[:outputImage])
when "rootfs"
  rootfsOptions(globalOptions[:outputImage], Stage2Rootfs::TARXZ)
when "rootfs-tar"
  rootfsOptions(globalOptions[:outputImage], Stage2Rootfs::TARXZ)
when "rootfs-squash"
  rootfsOptions(globalOptions[:outputImage], Stage2Rootfs::SQUASHFS)
when "bootloader"
  bootloaderOptions(globalOptions[:outputImage])
when "resign"
else
  $v.fatal("Unknown command: #{command}")
  exit
end

if globalOptions[:outputImage]
  File.open(globalOptions[:outputImage], 'w') { |file| $Image.write file }
end
