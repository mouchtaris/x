# frozen-string-literal: true

class TestError < Exception
end

class Subject
  RunResult = Struct.new(:v, :ex)

  def initialize(run)
    @run = run
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

  def to(check_type, *args)
    pred = method :"#{check_type}?"
    holds = pred.call(*args)
    binding.pry unless holds
    raise (value&.ex || TestError) unless holds
  end

end

module Expect
  def expect
    Subject.new(Proc.new)
  end
end
