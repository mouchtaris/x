#pragma once

#include <limits>
#include <type_traits>
#include <optional>

#include "next.h"

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
