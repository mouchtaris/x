#pragma once
#include <utility>

template <
    std::size_t ...Is,
    typename F,
    typename Tuple
    >
void for_each(
    Tuple&& t,
    F f,
    std::index_sequence<Is...>)
{
    ( f(std::get<Is>(t), Is == sizeof...(Is) - 1) , ... );
}

template <typename ...Ts>
struct apply_elements
{
    template <template <typename...> class F>
    using type = F<Ts...>;
};

template <typename Tuple> struct apply_tuple_elements;
template <typename ...Ts>
struct apply_tuple_elements<std::tuple<Ts...>>:
    public apply_elements<Ts...>
{ };

template <
    typename F,
    typename Tuple
    >
void for_each(Tuple&& t, F f)
{
    using tuple_t = std::decay_t<Tuple>;

    for_each(
        std::forward<Tuple>(t),
        std::move(f),
        std::make_index_sequence<std::tuple_size<tuple_t>::value> { }
    );
}
