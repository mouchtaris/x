#pragma once
#include <ostream>
#include "tagged_value/fwd.h"

template <
    typename tag,
    typename value_type>
std::ostream& operator << (
    std::ostream& o,
    tagged_value::data<tag, value_type> const& d
)
{
    return o << name(d) << '['  << get(d) << ']';
}
