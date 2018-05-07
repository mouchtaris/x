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

    class << self
      def makefile_escape(filepath_str)
        filepath_str
          .gsub(':', '\:')
      end

      def object_files(all_files)
        all_files.map do |file|
          makefile_escape(file.path.to_s + '.o')
        end
      end
    end

    def initialize(all_files, find_file, template_filepath)
      type_check(Proc) { :find_file }
      type_check(Pathname) { :template_filepath }
      type_check(Array[SourceFile]) { :all_files }

      @all_files = all_files.map(&:dup).map(&:freeze).dup.freeze
      @find_file = find_file
      @erb = RendererManager.erb_from(template_filepath)
    end

    def full_path_dependencies(file)
      file
        .dependencies
        .map(&@find_file)
        .map(&:path)
        .map(&:to_s)
        .map(&Renderer.method(:makefile_escape))
    end

    def render(file)
      type_check(SourceFile) { :file }

      @erb.result_with_hash(
        path: Renderer.makefile_escape(file.path.to_s),
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
  def initialize(root, all_files, find_file, category_names)
    type_check(Pathname) { :root }
    @root = root
    @all_files = all_files
    @renderers = 
      category_names
        .map { |name| [name, new_renderer(all_files, find_file, name)] }
        .to_h
        .freeze
    type_check(String => Renderer) { :@renderers }
  end

  def new_renderer(all_files, find_file, category_name)
    Renderer.new all_files, find_file, @root + "#{category_name}.erb"
  end

  def render(file)
    type_check(SourceFile) { :file }
    @renderers[file.category.name]&.render(file)
  end

  def prelude
    path = @root + '__prelude.erb'
    RendererManager.erb_from(path).result_with_hash \
      object_files: Renderer.object_files(@all_files)
  end

  def outro
    path = @root + '__outro.erb'
    RendererManager.erb_from(path).result
  end
end
