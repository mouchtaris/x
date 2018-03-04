#pragma once

#include <iostream>
#include <optional>

template <typename T>
std::ostream& operator << (std::ostream& o, std::optional<T> opt)
{
    o << "optional[";
    if (opt.has_value())
        o << opt.value();
    else
        o << "None";
    return o << ']';
}
