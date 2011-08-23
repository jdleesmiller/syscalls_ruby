# the Makefile should pass us the name of the compiler to use
# we assume that it behaves sufficiently like gcc
cc = ARGV.shift
raise unless cc

cmd = "#{cc} -E -dD -"
lines = IO.popen(cmd, 'r+') {|io|
  io.puts "#include <sys/syscall.h>"
  io.close_write
  io.readlines
}

p lines
