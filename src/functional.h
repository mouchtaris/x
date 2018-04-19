#pragma once
#include <utility>
#include <functional>

namespace functional {

    template <
        typename F
        >
    F compose(F f) { return f; }

    template <
        typename F,
        typename ...Gs
        >
    auto compose(F f, Gs&&... gs) {
        const auto g = compose(std::forward<Gs>(gs)...);
        return [f, g](auto&& x) {
            return g(f(x));
        };
    }

    template <
        typename R,
        typename ...Args
        >
    auto fn(std::function<R (Args...)> f)
        { return f; }

    template <
        typename ...Args
        >
    void ignore(Args&&...) { }

    template <
        typename ...Fs
        >
    auto seq(Fs... fs) {
        return [fs...] () {
            (fs(), ...);
        };
    }

}
