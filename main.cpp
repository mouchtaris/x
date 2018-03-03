#include <iostream>
#include <tuple>

#include "equal.h"
#include "is_numeric.h"
#include "next.h"

#include "equal_numeric.hpp"
#include "next_numeric.hpp"
#include "range.hpp"

struct Source {

    const int begin = 2;
    const int last = 5;
    std::optional<int> current = begin;

    std::optional<int> pull() {
        if (current.has_value()) {
            auto result = std::move(current);
            current = next(current.value());
            return result;
        }
        return current;
    }

};

int main(int, char**) {
    Source s;
    range(2, 5, [](int n) { std::cout << n << '\n'; });
    return 0;
}
