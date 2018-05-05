# frozen-string-literal: true

module FDB
  class File
    def initialize(path)
      raise ArgumentError, 'path' unless path.is_a? Pathname
      @path = path
    end
  end

  class Workspace 
    def initialize(root)
      raise ArgumentError, 'root' unless root.is_a? Pathname
      @root = root
    end
    attr_accessor :definition
    attr_writer :definition

    def find
      return enum_for(:find) unless block_given?
      raise ArgumentError, 'definition' unless definition.is_a? Definition

      file_rx   = definition.file_rx
      callback  = ->(file) {
        md = file_rx.match(file.to_s)
        name = md&.[](:name)
        path = name && Pathname.new(name)
        result = path && File.new(path)
        yield result if result
      }

      @root.find(&callback)
    end

    def scan
    end
  end
end
