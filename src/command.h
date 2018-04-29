#pragma once
#include <tuple>
#include <string>
#include <functional>
#include <ostream>
#include "write::tuple.h"
#include "tagname.h"

namespace command
{

    template <
        typename _tag,
        typename ..._args
        >
    struct data:
        public std::tuple<_args...>
    {
        using tag = _tag;
        using base_t = std::tuple<_args...>;
        using base_t::tuple;

        base_t& as_tuple() & { return *this; }
        base_t const& as_tuple() const& { return *this; }
    };

    template <
        typename tag,
        typename ...args
        >
    struct const_api_t
    {
        std::reference_wrapper<const data<tag, args...>> d;

        std::string name() const { return tagname::of<tag>().at(0); }
    };

    template <
        typename tag,
        typename ...args
        >
    const_api_t<tag, args...> api(data<tag, args...> const& d)
    {
        return { std::ref(d) };
    }

    template <
        typename tag,
        typename ...args
        >
    std::ostream& operator << (std::ostream& o, data<tag, args...> const& d)
    {
        return write::tuple(
            o << api(d).name() << ' ',
            d
        );
    }
}

template <
    typename tag,
    typename ...args
    >
using command_t = command::data<tag, args...>;
