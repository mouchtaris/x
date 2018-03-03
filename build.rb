# frozen-string-literal: true

require 'pathname'
require 'find'
require 'pp'
require 'json'

CXX = 'g++'
CXXFLAGS = %w[-pedantic -std=c++1z -Wall -Wextra -O0 -Isrc].freeze

def cxxflags
  CXXFLAGS.join ' '
end

CPPEXT = '.cpp'
HEXT = '.h'

ROOT = Pathname.new('.')
REAL_ROOT = ROOT.realpath

def file?
  :file?.to_proc
end

def cpp?
  ->(f) { f.to_s.end_with? CPPEXT }
end

def header?
  ->(f) { f.to_s.end_with? HEXT }
end

def source_ext?
  ->(f) { cpp?.call(f) || header?.call(f) }
end

def source?
  ->(f) { file?.call(f) && source_ext?.call(f) }
end

def stem(source)
  parent = source.dirname
  basename =
    case source
    when cpp? then source.basename CPPEXT
    when header? then source.basename HEXT
    else raise "What is this #{source.inspect}"
    end
  parent + basename
end

def find_in_and_add_if(root, pred)
  lambda { |builder|
    add_if_ok = ->(f) { builder << f if pred.call(f) }
    root.find(&add_if_ok)
  }
end

def sources(root)
  [].tap(&find_in_and_add_if(root, source?))
end

def object_file(source)
  "#{stem source}.o"
end

SOURCES = sources(ROOT)
CPPS = SOURCES.select(&cpp?)
OBJECTS = CPPS.map(&method(:object_file))

pp SOURCES
pp OBJECTS

def build_arguments(source)
  src = source.to_s
  obj = object_file(source)
  [
    src,
    obj,
    [CXX] + CXXFLAGS + ['-c', '-o', obj, src]
  ]
end

def genmake(into)
  objects = OBJECTS.join ' '

  pline = ->(*a) { into.puts(*a) }

  pline.call "all: main\n\t./main"
  pline.call "clean:\n\trm -rfv main #{objects}"
  pline.call "main: #{objects}\n\t#{CXX} -o main #{objects}"
  CPPS
    .map(&method(:build_arguments))
    .map { |_source, object, args| "#{object}:\n\t#{args.join ' '}" }
    .each(&pline)
  pline.call '.PHONY: clean all'
end

def compiledb_entry(*args)
  source, _object, command_args = args
  {
    arguments: command_args,
    directory: REAL_ROOT.to_s,
    file: source.to_s
  }
end

def gencompiledb(into)
  db = SOURCES
       .map(&method(:build_arguments))
       .map(&method(:compiledb_entry))
  JSON.dump(db, into)
end

File.open('GNUmakefile', 'w', &method(:genmake))
File.open('compile_commands.json', 'w', &method(:gencompiledb))
