#pragma once
#include "tagname.h"

namespace tagged_value
{
    template <
        typename _tag,
        typename _value_type>
    struct data
    {
        using Tag = _tag;
        using value_t = _value_type;

        value_t value;

        explicit data(value_t value):
            value { std::move(value) }
        { }
    };

    template <
        typename tag,
        typename value_type>
    decltype(auto) get(data<tag, value_type>& d)
    {
        return d.value;
    }
}
