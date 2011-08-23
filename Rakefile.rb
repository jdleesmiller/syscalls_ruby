require 'rake/testtask'
require 'rake/clean'

desc 'build extension'
task :ext do
  Dir.chdir('ext') do
    ruby "extconf.rb"
    sh "make"
  end
end

task :build do
  sh "gem build *.gemspec"
  sh "mkdir -p pkg; mv *.gem pkg"
end

Rake::TestTask.new(:test) do |t|
  t.libs << %w(lib ext)
  t.pattern = 'test/**/*_test.rb'
end

CLEAN.include('ext/*{.o,.log,.c}')
CLEAN.include('ext/Makefile')
CLOBBER.include('ext/*.so')
CLOBBER.include('pkg')

task :default => :test
