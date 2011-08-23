require 'syscalls'
require 'test/unit'

class TestSyscalls < Test::Unit::TestCase
  include Syscalls

  def test_syscalls
    assert_equal SYS_open, SYS_NUMBER[:SYS_open]
    assert_equal :SYS_open, SYS_NAME[SYS_open]
  end

  def test_getpid
    assert_equal Process.pid, syscall(SYS_getpid)
  end
end

