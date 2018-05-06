# frozen-string-literal: true

require 'pathname'
require 'find'
require 'pp'
require 'json'

require 'pry'

require_relative 'rb/tstruct'

###
WorkspaceDefinition = Struct.new \
  :root

Definition = Struct.new \
  :name,
  :file_rx,
  :dep_rx

def srcfile_rx(ext)
  /.*src\/(?<name>.*\.#{ext})$/
end

def srcfile_include_rx
  /^\s*\#\s*include\s*"(?<name>[^"]+)".*$/
end

def make_definition_from_ext_func
  ->(ext_i) {
    ext = ext_i.to_s
    [ext_i, Definition.new(ext, srcfile_rx(ext), srcfile_include_rx)]
  }
end

categories = %i[h hpp cpp].freeze
defs = categories.map(&make_definition_from_ext_func).to_h.freeze

### Official specs
require_relative 'rb/tstruct_spec'
TStructSpec.run

