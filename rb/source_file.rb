require 'pathname'
require_relative 'tstruct'
require_relative 'file_category_definition'

module SourceFileApi
  def dependencies
    File.open(path.to_s, 'r') do |fin|
      fin
        .each_line
        .lazy
        .map(&category.dependency_rx.method(:match))
        .select(&:itself)
        .to_a
    end
  end
end

SourceFile = TStruct.with_base SourceFileApi,
  name: String,
  path: Pathname,
  category: FileCategoryDefinition
