module Control
  def category_names
    @workspace_definition.file_category_definitions.map(&:name)
  end
end
