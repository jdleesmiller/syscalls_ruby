# -*- encoding: utf-8 -*-
lib = File.expand_path('../lib/', __FILE__)
$:.unshift lib unless $:.include?(lib)
 
require 'syscalls/version'
 
Gem::Specification.new do |s|
  s.name              = 'syscalls'
  s.version           = Syscalls::VERSION
  s.platform          = Gem::Platform::RUBY
  s.authors           = ['John Lees-Miller']
  s.email             = ['jdleesmiller@gmail.com']
  s.homepage          = 'https://github.com/jdleesmiller/syscalls_ruby'
  s.summary           = %q{Constants for syscall numbers}
  s.description       = %q{An extension that lists the system's supported syscalls (e.g. SYS_open, SYS_write, etc.)}

  s.rubyforge_project = ''

  s.files       = Dir.glob('lib/**/*.rb') +
                  Dir.glob('ext/**/*.inc') + %w(README.rdoc)
  s.test_files  = Dir.glob('test/*_test.rb')
  s.extensions = ["ext/syscalls/extconf.rb"]

  s.rdoc_options = [
    "--main",    "README.rdoc",
    "--title",   "#{s.full_name} Documentation"]
  s.extra_rdoc_files << "README.rdoc"
end

