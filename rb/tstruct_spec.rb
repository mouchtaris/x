require_relative 'test::expect'

module TStructSpec
  class << self
    include Expect

    def f1_name
      :id
    end

    def f1_type
      Integer
    end

    def tstruct 
      TStructClass.new({
        f1_name => f1_type
      })
    end

    def run
      expect { tstruct }.to :respond, :id
      expect { tstruct }.to :respond, :id=
      expect { tstruct }.to :respond, :unset_id
      expect { tstruct.id = 12 }.to :eq, 12
      expect { tstruct.tap { |s| s.id = 12 }.id }.to :eq, 12
      expect { tstruct.id = '12' }.to :fail, ArgumentError
      expect { tstruct.id = nil }.to :fail, ArgumentError
      expect { tstruct.tap { |s| s.id = 12 }.tap { |s| s.unset_id }.id }.to :eq, nil
      expect { tstruct.idd }.to :fail, NameError
    end
  end
end
