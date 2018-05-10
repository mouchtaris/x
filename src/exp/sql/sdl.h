#ifndef __SQL__SDL_H__
#define __SQL__SDL_H__

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

    struct primary_key;

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
#endif // __SQL__SDL_H__
