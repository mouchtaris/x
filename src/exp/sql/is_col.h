#pragma once
#include <type_traits>
#include "exp/sql/sdl.h"

namespace sql
{
    template <typename T>
    struct _is_col_detail
    {
        template <typename... cols>
        using with_cols = std::disjunction<
            std::is_same<T, cols> ...
        >;
    };

    template <typename T>
    struct is_col:
        public sdl::col::apply_cols_t<_is_col_detail<T>::template with_cols>
    { };
}
