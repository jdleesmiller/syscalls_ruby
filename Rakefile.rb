require 'rake/testtask'
require 'rake/clean'

NAME = 'syscalls'

# rule to build the extension: this says 
# that the extension should be rebuilt
# after any change to the files in ext
file "lib/#{NAME}/#{NAME}.so" =>
    Dir.glob("ext/#{NAME}/*{.rb,.c}") do
  Dir.chdir("ext/#{NAME}") do
    ruby "extconf.rb"
    sh "make"
  end
  cp "ext/#{NAME}/#{NAME}.so", "lib/#{NAME}"
end

# make the :test task depend on the shared
# object, so it will be built automatically
# before running the tests
task :test => "lib/#{NAME}/#{NAME}.so"

Rake::TestTask.new(:test) do |t|
  t.pattern = 'test/**/*_test.rb'
end

task :build do
  sh "gem build *.gemspec"
  sh "mkdir -p pkg; mv *.gem pkg"
end

CLEAN.include('ext/**/*{.o,.log,.so,.c}')
CLEAN.include('ext/**/Makefile')
CLOBBER.include('lib/**/*.so')
CLOBBER.include('pkg')

task :default => :test
