#pragma once
#include "tagged_value.h"

template <
    typename tag,
    typename ...fields
    >
struct record:
    public tagged_value::data<tag, std::tuple<fields...>>
{ };
