require 'pathname'
require_relative 'tstruct'
require_relative 'file_category_definition'
require_relative 'type_comparisons'
require_relative 'source_file'

module WorkspaceDefinitionApi
  include TypeComparisons

  def find_all(&block)
    file_category_definitions.to_a.flat_map do |cat|
      find_category(cat, &block).to_a
    end
  end

  def find_category(category)
    return enum_for(:find_category, category).lazy unless block_given?
    type_check(FileCategoryDefinition) { :category }
    (root + src).find do |file_path|
      in_project = file_path.relative_path_from(root)
      in_src = in_project.relative_path_from(src)
      md = category.file_rx.match(in_src.to_s)
      yield registry_add(name: md[:name], path: in_project, category: category) if md
    end
  end

  def registry
    @__workspace_definition__registry ||= {}
  end

  def registry_add(**params)
    sf = SourceFile.new(**params)
    registry[sf.name] = sf
  end

  def new_file(name)
    registry[name]
  end
end

WorkspaceDefinition = TStruct.with_base WorkspaceDefinitionApi,
  root: Pathname,
  src: Pathname,
  file_category_definitions: Array[FileCategoryDefinition]
