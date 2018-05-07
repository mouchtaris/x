require 'erb'
require_relative 'type_comparisons'

class RendererManager
  include TypeComparisons

  class Renderer
    include TypeComparisons

    def initialize(template_filepath)
      @erb = ERB.new(Fie.read(template_filepath))
        .tap { |erb| erb.location = template_filepath }
    end

    def render(file)
      type_check(SourceFile) { :file }
      @erb.run \
        path: file.path.to_s.dup.freeze,
        dependencies: file.dependencies.dup.freeze
    end
  end

  class Renderers
    include TypeComparisons

    def initialize(renderers)
      type_check(Symbol => Renderer) { :renderers }
      @renderers = renderers.dup.freeze
    end

    def render(file)
      type_check(SourceFile) { :file }
      @renderers[file.category.name]&.render(file)
    end
  end

  def initialize(root)
    type_check(Pathname) { :root }
    @root = root
  end

  def new_renderer(category_name)
    Renderer.new @root + "#{category_name}.erb"
  end

  def renderers(category_names)
    Renderers.new(
      category_names
        .map { |name| [name, new_renderer(name)] }
        .to_h
        .freeze
    )
  end
end
