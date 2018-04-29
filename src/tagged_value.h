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
    };
}
