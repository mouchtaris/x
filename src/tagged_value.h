#pragma once
#include "tagname.h"
#include "tagged_value/fwd.h"
#include "tagged_value/write.h"

namespace tagged_value
{
    template <
        typename _tag,
        typename _value_type>
    struct data
    {
        using Tag = _tag;
        using value_t = _value_type;
        static_assert(std::is_move_constructible_v<value_t>, "");

        value_t value;

        explicit data(value_t&& value):
            value { std::move(value) }
        { }

        ///
        /// For descendants
        ///
        using base_t = data<Tag, value_t>;
        base_t& as_base() & { return *this; }
        base_t const& as_base() const& { return *this; }
    };

    template <
        typename tag,
        typename value_type>
    decltype(auto) get(data<tag, value_type>& d)
    {
        return d.value;
    }

    template <
        typename tag,
        typename value_type>
    decltype(auto) get(data<tag, value_type> const& d)
    {
        return (d.value);
    }

    template <
        typename tag,
        typename value_type>
    auto get(data<tag, value_type>&& d)
    {
        return d.value;
    }

    template <
        typename tag,
        typename value_type>
    std::string name(data<tag, value_type> const&)
    {
        return tagname::of<tag>().at(0);
    }

    //////
    //
    //
    //
    template <
        typename _tv,
        typename ...Args>
    _tv make(Args&&... args)
    {
        return {
            typename _tv::base_t {
                std::forward<Args>(args)...
            }
        };
    }

}
