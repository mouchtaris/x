#pragma once
#include <array>

template <
    std::size_t ...n,
    typename C>
constexpr auto __make_array__impl(
    std::index_sequence<n...>,
    C&& construct
)
    ->  std::array<
            std::invoke_result_t<C, std::size_t>,
            sizeof...(n)>
{
    return { construct(n) ... , };
}

template <
    std::size_t n,
    typename C>
constexpr auto make_array(
    C&& construct
)
{
    return __make_array__impl(
        std::make_index_sequence<n>(),
        std::forward<C>(construct)
    );
}
