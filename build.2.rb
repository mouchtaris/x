# frozen-string-literal: true

require 'pathname'
require 'find'
require 'pp'
require 'json'

require 'pry'

require_relative 'rb/configuration_manager'
require_relative 'rb/renderer_manager'
require_relative 'rb/control'

### Official specs
require_relative 'rb/tstruct_spec'
#TStructSpec.run
require_relative 'rb/workspace_definition_spec'
WorkspaceDefinitionSpec.run

include Control
cm = ConfigurationManager.new
@workspace_definition = wsd = cm.workspace_definition
rdm = RendererManager.new wsd.root + 'rb/templates', wsd.method(:new_file).to_proc, Control::category_names
pp \
  wsd
    .find_all
    .flat_map(&:dependencies)
    .map(&wsd.method(:new_file))
    .map(&renderers.method(:render))
    .each(&method(:puts))
