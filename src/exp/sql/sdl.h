#pragma once

namespace sql {
namespace sdl {
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

        template <template <typename...> class F>
        using apply_cols_t = F<
            Int,
            String
        >;
    }
}}
