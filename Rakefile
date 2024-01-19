require "rake/extensiontask"
require "rubygems"

# somewhere in your Rakefile, define your gem spec
spec = Gem::Specification.load('millibil.gemspec')

# add your default gem packing task
Gem::PackageTask.new(spec) do |pkg|
end

# feed the ExtensionTask with your spec
Rake::ExtensionTask.new('millibil', spec) do |ext|
  ext.lib_dir = "lib/millibil"
end
