require 'pp'
require 'ostruct'

def debug(*msg)
  STDERR.puts(msg.join "\n")
end

module State
  def self.new_state(name)
    klass = Class.new
    const_set name.capitalize.to_sym, klass
    klass.new
      .tap do |s|
        debug " --- Creating state #{klass}, object #{s}"
      end
  end

  def self.method_missing(name, *args)
    @state = @states[name] ||= new_state(name)
  end

  def self.now
    @state
  end

  @states = {}
  @state = self.init
end

class LineParser
  def initialize(line)
    @line = line.dup
  end

  def update!(match_data)
    @line = @line[match_data[0].length .. -1]
  end

  def pre!
    debug " --- eating space as pre! ..."
    space!
  end

  def post!(match_data)
    return nil unless match_data

    debug " --- MATCH: #{match_data[0].inspect}"
    update!(match_data)
    debug " --- rest #{@line.inspect}"

    match_data[0]
  end

  def match!(rx)
    pre!
    post! rx.match(@line)
  end

  Space = /^\s+/
  def space!
    debug " --- TRY space"
    # NO PRE! HERE!!!
    post! Space.match(@line)
  end

  Ident = /^\w+/
  def ident!
    debug ' --- TRY ident'
    match! Ident
  end

  Next = /^./
  def next!
    debug ' --- Getting next'
    match! Next
  end
end

max = 1
i = 0

visitor = OpenStruct.new


STDIN.each_line do |line|
  break if i > max
  i += 1

  case State.now
  when State::Init
    if visitor.ident = LineParser.new(line).ident!
      State.ident
    end
  else
    debug " ---[!!!] Don't know what to do in state #{State.now.class}"
  end

end
