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
HPPEXT = '.hpp'
SOURCE_EXTS = [ CPPEXT, HEXT, HPPEXT ].freeze
SOURCE_EXT_PREDICATES = SOURCE_EXTS.map { |ext| [ext, -> (f) { f.to_s.end_with?(ext) }] }.to_h.freeze

def cpp?
  SOURCE_EXT_PREDICATES[CPPEXT]
end

ROOT = Pathname.new('.')
REAL_ROOT = ROOT.realpath

def file?
  :file?.to_proc
end

def source_ext?
  ->(f) { SOURCE_EXT_PREDICATES.any? { |_, pred| pred.call(f) } }
end

def source?
  ->(f) { file?.call(f) && source_ext?.call(f) }
end

def stem(source)
  parent = source.dirname
  basename =
    SOURCE_EXT_PREDICATES
      .select { |_, pred| pred.call(source) }
      .map { |ext, _| source.basename(ext) }
      .first
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

def compiledb_entry(source, _object, command_args)
  {
    arguments: command_args,
    directory: REAL_ROOT.to_s,
    file: source.to_s
  }
end

def gencompiledb(into)
  db = SOURCES
       .map(&method(:build_arguments))
       .map { |s, o, a| compiledb_entry(s, o, a) }
  into.write(JSON.pretty_generate(db))
end

File.open('GNUmakefile', 'w', &method(:genmake))
File.open('compile_commands.json', 'w', &method(:gencompiledb))
