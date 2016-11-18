Gem::Specification.new do |s|
  s.add_runtime_dependency "rice", ["= 2.1.0"]
  s.name        = 'millibil'
  s.version     = '0.0.3'
  s.date        = '2016-02-01'
  s.summary     = "Intervals-related data structures for Ruby based on C++'s Boost library"
  s.description = "Intervals everywhere !"
  s.authors     = ["Joris Van Hecke"]
  s.email       = "joris@progenda.be"
  s.files       = ["lib/millibil.rb", "ext/millibil/extconf.rb", "ext/millibil/millibil.cpp"]
  s.require_paths = ['lib', 'ext']
  s.homepage    = 'http://rubygems.org/gems/millibil'
  s.license     = 'MIT'
  s.extensions  = %w[ext/millibil/extconf.rb]
end
