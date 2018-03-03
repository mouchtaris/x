#include <iostream>
#include <tuple>

#include "equal.h"
#include "is_numeric.h"
#include "next.h"

#include "equal_numeric.hpp"
#include "next_numeric.hpp"

template <typename T>
struct Range;

template <typename T, typename C>
void range(T self, C callback)
{
    Range<T> { }(std::move(self), std::move(callback));
}

template <typename T>
struct Range<std::tuple<T, T>> {

    using Self = std::tuple<T, T>;

    template <typename C>
    void operator()(const Self& self, const C callback) const {
        auto&& from = std::get<0>(self);
        auto&& to = std::get<1>(self);

        callback(from);

        if (equal(from, to))
            return;

        std::optional<T> maybeNext = next(std::move(from));

        if (maybeNext.has_value()) {
            Self nextSelf = {
                std::move(maybeNext.value()),
                std::move(to)
            };
            (*this)(std::move(nextSelf), std::move(callback));
        }
    }

};

int main(int, char**) {
    auto println = [](auto&& any) { std::cout << any << '\n'; };
    // range(std::make_tuple(2, 5), println);
    std::tuple<int, int> self = { 2, 5 };
    Range<std::tuple<int, int>> r;
    r(self, println);
    return 0;
}
