#pragma once
#include "exp/memsql.h"

namespace memsqlrepo
{
    template <
        typename _table>
    struct repo
    {
        using value_type = typename memsql::table<_table>::value::rec;
    };
}
