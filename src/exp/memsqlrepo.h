#ifndef __MEMSQLREPO_H__
#define __MEMSQLREPO_H__
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
#endif // __MEMSQLREPO_H__
