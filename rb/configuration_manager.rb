require_relative 'workspace_definition'

class ConfigurationManager
  Fields = TStruct.new(
    project_root: Pathname,
    source_dir: Pathname,
    category_names: Array[Symbol],
    file_category_definitions: Array[FileCategoryDefinition]
  )

  def initialize
    @fields = Fields.new(
      project_root: Pathname.new(Dir.pwd),
      source_dir: Pathname.new('src'),
      category_names: %i[h hpp cpp].freeze
    )
    @fields.file_category_definitions = @fields.category_names.map(&method(:new_file_cat_def_from_ext))
  end

  def new_srcfile_rx(ext)
    /(?<name>.*\.#{ext})$/
  end

  def new_srcfile_include_rx
    /^\s*\#\s*include\s*"(?<name>[^"]+)".*$/
  end

  def new_file_cat_def_from_ext(ext)
    FileCategoryDefinition.new \
      name: ext.to_s,
      file_rx: new_srcfile_rx(ext),
      dependency_rx: new_srcfile_include_rx
  end

  def workspace_definition
    WorkspaceDefinition.new \
      root: @fields.project_dir,
      src: @fields.source_dir,
      file_category_definitions: @fields.file_category_definitions
  end
end

