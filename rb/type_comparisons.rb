module TypeComparisons
  def type_comparison(val, typ)
    case typ
    when Array
      array_type_comparison(val, typ)
    when Hash
      hash_type_comparison(val, typ)
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

  #
  # @param hash_type [{KeyType: Module => ValueType: Module}]
  #
  def hash_key_type(hash_type)
    hash_type.to_a.first.first
  end

  def hash_value_type(hash_type)
    hash_type.to_a.first.last
  end

  def array_type_comparison(vals, typ)
    return false unless direct_type_comparison(vals, Array)
    elem_t = array_element_type(typ)
    vals.all? do |val|
      type_comparison(val, elem_t)
    end
  end

  def hash_type_comparison(vals, typ)
    return false unless direct_type_comparison(vals, Hash)
    key_t = hash_key_type(typ)
    value_t = hash_value_type(typ)
    vals.all? do |key, val|
      type_comparison(key, key_t) &&
        type_comparison(val, value_t)
    end
  end
end
