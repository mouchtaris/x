# frozen-string-literal: true

require 'pathname'
require 'find'
require 'pp'
require 'json'

require 'pry'

require_relative 'rb/configuration_manager'

### Official specs
require_relative 'rb/tstruct_spec'
#TStructSpec.run
require_relative 'rb/workspace_definition_spec'
WorkspaceDefinitionSpec.run

pp \
  ConfigurationManager
    .new
    .workspace_definition
    .find_all
    .flat_map(&:dependencies)
    .map(&:to_a)
