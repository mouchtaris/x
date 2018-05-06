require_relative 'tstruct'

FileCategoryDefinition = TStruct.new \
  name: String,
  file_rx: Regexp,
  dependency_rx: Regexp
