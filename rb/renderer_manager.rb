require 'erb'
require_relative 'type_comparisons'

#
# RendererManager
#
class RendererManager
  include TypeComparisons

  class << self
    def erb_from(file_path)
      ERB.new(File.read(file_path.to_s)).tap do |e|
        e.location = file_path.to_s
      end
    end
  end

  #
  # Renderer
  #
  class Renderer
    include TypeComparisons

    def initialize(find_file, template_filepath)
      type_check(Proc) { :find_file }
      type_check(Pathname) { :template_filepath }

      @find_file = find_file
      @erb = RendererManager.erb_from(template_filepath)
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

  def prelude(object_files)
    path = @root + '__prelude.erb'
    RendererManager.erb_from(path).result_with_hash \
      object_files: object_files
  end

  def outro
    path = @root + '__outro.erb'
    RendererManager.erb_from(path).result
  end
end
