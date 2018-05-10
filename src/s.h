#ifndef __S_H__
#define __S_H__
#include <utility>
#include "printf.h"

namespace __s
{
    extern void __s(char const*);

    constexpr auto BS = 1024;

    template <typename ...Args>
    void s(Args&&... args)
    {
        auto buf = sprint::buf_t<BS> { };
        auto v = sprint::view(buf);
        bool ok = sprint::s(v, std::forward<Args>(args)...);
        if (!ok)
            blackout(v);
        __s(data(v));
    }

    const auto fwd = [](auto&&... args)
    {
        s(std::forward<decltype(args)>(args)...);
    };

    template <typename ...Ts>
    void s(std::tuple<Ts...>&& t)
    {
        std::apply(fwd, t);
    }
}

inline void s() { }

template <
    typename T,
    typename ...Ts
    >
void s(T&& t, Ts&&... ts)
{
    __s::s(std::forward<T>(t));
    s(std::forward<Ts>(ts)...);
}
#endif // __S_H__
