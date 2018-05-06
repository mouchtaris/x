# frozen-string-literal: true

class TestError < Exception
end

class Subject
  RunResult = Struct.new(:v, :ex)

  def initialize(run)
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
    value&.is_a? c
  end

  def respond?(n)
    value&.respond_to? n
  end

  def to(check_type, *args)
    pred = method :"#{check_type}?"
    holds = pred.call(*args)
    binding.pry unless holds
    if holds
      puts "|| #{description} ||: ok"
    else
      puts "|| #{description} ||: FAIL"
    end
    # raise (value&.ex || TestError) unless holds
  end

end

module Expect
  def expect
    Subject.new(Proc.new)
  end
end
