Either   <L, R> struct
    _is_left:   bool
    _data   :   std::aligned_union<0, L, R>

    data()          => std::addressof(_data)
    left_data()     => reinterpret_cast<L*>(data())
    right_data()    => reinterpret_cast<R*>(data())

    ctors
    () = delete
    copy = delete
    (bool l) : is_left { l }, data { } { }
    move : is_left { other.is_left } {
        if (is_left)
            new(left_data()) L(std::move(*other.left_data()));
        else
            new(right_data()) R(std::move(*other.right_data()));
    }
    destroy {
        std::destroy_at( is_left ? left_data() : right_data() );
    }
