# frozen-string-literal: true
require_relative 'type_comparisons'

class TestError < Exception
end

class Subject
  include TypeComparisons
  RunResult = Struct.new(:v, :ex)

  def initialize(out, run)
    @out = out
    @run = run
  end

  def description
    file_path_str, line_num = @run.source_location
    File.open(file_path_str, 'r') do |fin|
      lines = fin.each_line.lazy.drop(line_num - 1)
      lines.first.strip
    end
  end

  def run!
    return if @result
    begin
      RunResult.new(@run.call(), nil)
    rescue => ex
      RunResult.new(nil, ex)
    end
  end

  def result
    @result ||= run!
  end

  def value
    result.v
  end

  def error
    result.ex
  end

  def eq?(v)
    value == v
  end

  def fail?(c)
    error&.is_a? c
  end

  def be?(c)
    type_comparison(value, c) if value
  end

  def respond?(n)
    value&.respond_to? n
  end

  def to(check_type, *args)
    pred = method :"#{check_type}?"
    holds = pred.call(*args)
    binding.pry unless holds
    if holds
      @out.puts "|| #{description} ||: ok"
    else
      @out.puts "|| #{description} ||: FAIL"
    end
    # raise (value&.ex || TestError) unless holds
  end

end

module Expect
  def expect
    Subject.new(@__expect__out, Proc.new)
  end
end
