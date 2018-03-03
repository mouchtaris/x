#include <iostream>
#include <optional>
#include <limits>
#include <functional>

#include "is_numeric.h"
#include "next.h"
#include "equal.h"
#include "range.hpp"

using std::optional;

//
// is_numeric.h
//


//
// next.h
//

//
// equal.h
//


//
// range.h
//

//
// next_numeric.h
//
template <typename T>
struct Next {
    using _enabled = std::enable_if_t<is_numeric<T>::value, T>;
    std::optional<T> operator () (const T n)
    {
        if (n == std::numeric_limits<T>::max())
            return std::nullopt;
        return n + 1;
    }
};

//
// equal_numeric.h
//
template <typename T>
struct Equal {
    using _enabled = std::enable_if_t<is_numeric<T>::value, T>;
    bool operator () (const T a, const T b)
    {
        return a == b;
    }
};

int main(int, char**) {
    range(2, 5, [](int n) { std::cout << n << '\n'; });
    return 0;
}
