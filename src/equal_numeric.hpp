#pragma once

#include <type_traits>

#include "equal.h"

template <typename T>
struct Equal {
    using _enabled = std::enable_if_t<is_numeric<T>::value, T>;
    bool operator () (const T a, const T b)
    {
        return a == b;
    }
};
