#ifndef __BOB_H__
#define __BOB_H__
#include "exp/sql.h"
#include "exp/memsql.h"
#include <functional>

namespace bob
{
    using namespace sql::sdl;

    struct account
    {
        struct id;
        struct email;

        using t = table<account,
            column<id       , col::Int      , primary_key   >,
            column<email    , col::String                   >
        >;
    };

    struct user
    {
        struct id;
        struct account_id;
        struct name;

        using t = table<user,
            column< id          , col::Int      , primary_key   >,
            column< account_id  , col::Int                      >,
            column< name        , col::String                   >
        >;
    };

    template <
        typename _table,
        size_t _col_i>
    auto _shortcut(typename memsql::table<_table>::value::rec const& t)
        -> typename memsql::table<_table>::template get_column<_col_i>::tagged_t
    {
        using table_t = memsql::table<_table>;
        using column_t = typename table_t::template get_column<_col_i>;
        return memsql::gett<column_t>(t);
    }

    //inline decltype(auto) id(memsql::table<user::t>::value::rec const& u)
    //{
    //    return _shortcut<user::t, 0>(u);
    //}
}
#endif // __BOB_H__
