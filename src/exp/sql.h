#pragma once
#include "record.h"

namespace sql
{
    namespace sdl
    {
        template <
            typename name,
            typename ...columns>
        struct table { };

        template <
            typename name,
            typename ...attributes>
        struct column { };

        namespace col
        {
            struct Int { };
            struct String { };
        }
    }

    template <typename T> struct create_impl;
    template <typename T, typename ...Args>
    decltype(auto) create(Args&&... args)
    {
        return create_impl<T> { }(std::forward<Args>(args)...);
    }

}
