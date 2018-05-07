require_relative 'test::expect'
require_relative 'workspace_definition'
include Expect

module WorkspaceDefinitionSpec
  class << self
    def fcds
      [
        FileCategoryDefinition.new
      ]
    end

    def run(out = STDERR)
      @__expect__out = out
      expect { WorkspaceDefinition }.to :respond, :new
      expect { WorkspaceDefinition.new }.to :be, TStructClass

      expect { WorkspaceDefinition.new }.to :respond, :root
      expect { WorkspaceDefinition.new }.to :respond, :root=
      expect { WorkspaceDefinition.new }.to :respond, :src
      expect { WorkspaceDefinition.new }.to :respond, :src=
      expect { WorkspaceDefinition.new }.to :respond, :file_category_definitions
      expect { WorkspaceDefinition.new }.to :respond, :file_category_definitions=

      expect { WorkspaceDefinition.new.root = 12 }.to :fail, ArgumentError
      expect { WorkspaceDefinition.new.file_category_definitions = 12 }.to :fail, ArgumentError
      expect { WorkspaceDefinition.new.file_category_definitions = [12] }.to :fail, ArgumentError

      expect { WorkspaceDefinition.new.root = Pathname.new('/tmp') }.to :be, Pathname
      expect { WorkspaceDefinition.new.file_category_definitions = fcds }.to :be, Array[FileCategoryDefinition]

      expect { WorkspaceDefinition.new(root: Pathname.new('/tmp')).root }.to :be, Pathname
      expect { WorkspaceDefinition.new(file_category_definitions: fcds).file_category_definitions }.to :be, Array[FileCategoryDefinition]

      expect { WorkspaceDefinition.new }.to :respond, :find_all
    end
  end
end
