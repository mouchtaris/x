# frozen-string-literal: true

require 'pathname'
require 'find'
require 'pp'
require 'json'

require 'pry'

require_relative 'rb/configuration_manager'
require_relative 'rb/renderer_manager'

### Official specs
require_relative 'rb/tstruct_spec'
#TStructSpec.run
require_relative 'rb/workspace_definition_spec'
WorkspaceDefinitionSpec.run

cm = ConfigurationManager.new
wsd = cm.workspace_definition
rdm = RendererManager.new wsd.root + 'rb/templates'
renderers = rdm.renderers
pp \
  wsd
    .find_all
    .flat_map(&:dependencies)
    .map(&wsd.method(:new_file))
  .each do |file|
    renderers.render(file)
  end
