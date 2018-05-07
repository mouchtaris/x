#pragma once
#include "record.h"

namespace sql
{
    template <
        char const* name,
        typename columns
        >
    struct table;
}
