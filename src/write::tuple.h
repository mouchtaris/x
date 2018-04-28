#pragma once
#include <tuple>
#include <ostream>

namespace write {
namespace {
namespace __detail {

    template <typename T>
    struct tuple_element
    {
        std::reference_wrapper<const T> element;
    };

    template <typename T>
    std::ostream& operator <<(
        std::ostream& o,
        tuple_element<T> tupel)
    {
        return o << ' ' << tupel.element.get() << ',';
    }

    template <
        size_t ...Is,
        typename ...Ts
        >
    std::ostream& write_tuple(
        std::index_sequence<Is...>,
        std::ostream& o,
        std::tuple<Ts...> const& t)
    {
        return (
            (o << '{')
            << ... <<
                tuple_element<
                    std::tuple_element_t<Is, std::tuple<Ts...>>
                > { std::get<Is>(t) }
            ) << " }"
            ;
    }
}}

template <
    typename ...Ts
    >
std::ostream& tuple(std::ostream& o, std::tuple<Ts...> const& t)
{
    return __detail::write_tuple(
        std::make_index_sequence<sizeof...(Ts)>(),
        o,
        t);
}

}

template <
    typename ...Ts
    >
std::ostream& operator <<(std::ostream& o, std::tuple<Ts...> const& t)
{
    return write::tuple(o, t);
}
