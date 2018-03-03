#pragma once
#include <type_traits>
#include <list>

template <typename T>
struct is_numeric {
    using _enabled = std::enable_if_t<
        std::is_same<T, short int>::value |
        std::is_same<T, unsigned short int>::value |
        std::is_same<T, int>::value |
        std::is_same<T, unsigned int>::value |
        std::is_same<T, long int>::value |
        std::is_same<T, unsigned long int>::value |
        std::is_same<T, long long int>::value |
        std::is_same<T, unsigned long long int>::value |
        true
        ,
        void
    >;
    static constexpr bool value = true;
};

