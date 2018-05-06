module TypeComparisons
  def type_comparison(val, typ)
    case typ
    when Array
      array_type_comparison(val, typ)
    else
      default_type_comparison(val, typ)
    end
  end

  def type_check(typ, &block)
    var_name = block.call
    var_val = block.binding.eval(var_name.to_s)
    binding.pry unless type_comparison(var_val, typ)
    raise ArgumentError, "#{var_name} must be #{typ} but is #{var_val.inspect}" \
      unless type_comparison(var_val, typ)
  end

  private

  def default_type_comparison(val, typ)
    direct_type_comparison(val, typ)
  end

  def direct_type_comparison(val, typ)
    val.is_a? typ
  end

  def array_element_type(array_type)
    array_type.first
  end

  def array_type_comparison(vals, typ)
    return false unless direct_type_comparison(vals, Array)
    vals.all? do |val|
      type_comparison(val, array_element_type(typ))
    end
  end
end
