require_relative 'workspace_definition'

class ConfigurationManager
  def srcfile_rx(ext)
    /(?<name>.*\.#{ext})$/
  end

  def srcfile_include_rx
    /^\s*\#\s*include\s*"(?<name>[^"]+)".*$/
  end

  def make_file_cat_def_from_ext(ext)
    FileCategoryDefinition.new \
      name: ext.to_s,
      file_rx: srcfile_rx(ext),
      dependency_rx: srcfile_include_rx
  end

  def categories
    %i[h hpp cpp]
  end

  def file_category_definitions
    categories.map(&method(:make_file_cat_def_from_ext))
  end

  def workspace_definition
    root = Pathname.new(Dir.pwd)
    src = Pathname.new('src')
    WorkspaceDefinition.new \
      root: root,
      src: src,
      file_category_definitions: file_category_definitions
  end
end

