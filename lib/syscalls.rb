require 'syscalls.so'
require 'syscalls/version'

#
# System call constants (e.g. SYS_open). 
#
# The constant names and values in this module are system-dependent. They are
# read in from <tt>sys/syscall.h</tt> when this gem is built.
#
# The {SYS_NUMBER} and {SYS_NAME} hashes provide an easy way of converting from
# names to numbers.
#
module Syscalls
  #
  # Hash from system call names (as symbols) to system call numbers.
  #
  SYS_NUMBER = Hash[self.constants.grep(/SYS_/).map{|c| [c, self.const_get(c)]}]

  #
  # Hash from system call numbers to system call names (as symbols).
  #
  SYS_NAME = SYS_NUMBER.invert
end
