require 'erb'
require_relative 'type_comparisons'

#
# RendererManager
#
class RendererManager
  include TypeComparisons

  #
  # Renderer
  #
  class Renderer
    include TypeComparisons

    def initialize(find_file, template_filepath)
      type_check(Proc) { :find_file }
      type_check(Pathname) { :template_filepath }

      @find_file = find_file
      @erb = ERB.new(File.read(template_filepath))
        .tap { |erb| erb.location = template_filepath.to_s }
    end

    def full_path_dependencies(file)
      file
        .dependencies
        .map(&@find_file)
        .map(&:path)
        .map(&:to_s)
    end

    def render(file)
      type_check(SourceFile) { :file }

      @erb.result_with_hash(
        path: file.path,
        dependencies: full_path_dependencies(file)
      )
    end
  end

  #
  #
  #

  #
  # @param find_file [FileName: String => SourceFile]
  #
  def initialize(root, find_file, category_names)
    type_check(Pathname) { :root }
    @root = root
    @renderers = 
      category_names
        .map { |name| [name, new_renderer(find_file, name)] }
        .to_h
        .freeze
    type_check(String => Renderer) { :@renderers }
  end

  def new_renderer(find_file, category_name)
    Renderer.new find_file, @root + "#{category_name}.erb"
  end

  def render(file)
    type_check(SourceFile) { :file }
    @renderers[file.category.name]&.render(file)
  end

  def render_prelude
    path = @root + '__prelude.erb'
    ERB
      .new(File.read(path))
      .tap { |e| e.location = path.to_s }
      .result
  end
end
