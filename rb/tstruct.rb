class TStruct

  def __accessor_name(name)
    name.to_sym
  end

  def __modifier_name(name)
    :"#{name}="
  end

  def __deleter_name(name)
    :"unset_#{name}"
  end

  def __accessor_impl(name)
    ->() { @values[name] }
  end

  def __modifier_impl(name, type)
    ->(val) do
      if val.is_a? type
        @values[name] = val
      else
        raise ArgumentError, "#{name} must be #{type}"
      end
    end
  end

  def __deleter_impl(name)
    ->() { @values.delete name }
  end

  def __define_accessor(name)
    define_singleton_method(__accessor_name(name), &__accessor_impl(name))
  end

  def __define_modifier(name, type)
    define_singleton_method(__modifier_name(name), &__modifier_impl(name, type))
  end

  def __define_deleter(name)
    define_singleton_method(__deleter_name(name), &__deleter_impl(name))
  end

  def initialize(fields)
    @values = {}
    fields.each do |name, type|
      __define_accessor(name)
      __define_modifier(name, type)
      __define_deleter(name)
    end
  end
end
